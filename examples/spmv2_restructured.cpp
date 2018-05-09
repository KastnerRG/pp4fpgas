#include "spmv.h"
#include <stdio.h>

const static int S = 8;

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
       DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE]) {
	int currentrow[S];
	int LB[S];
	int UB[S];
	bool done[S];
	#pragma HLS array_partition variable=done complete
	int row;
 Init:
	for (int i=0; i<S; i++){
#pragma HLS PIPELINE II=1
		LB[i] = rowPtr[i];
		UB[i] = rowPtr[i+1];
		y[i] = 0;
		currentrow[i] = i;
		done[i] = false;
	}
	row = S-1;
	int L, K;

 ACC:
	for(int i=0; i<NNZ * S + NUM_ROWS; i++ ) {
		int j = i % S;
#pragma HLS DEPENDENCE variable=y inter distance=8
#pragma HLS PIPELINE II=1

		if(LB[j] == UB[j]) {
			row++;
			if(row < NUM_ROWS) {
				printf("Engine %d working on row %d\n", j, row);
				LB[j] = rowPtr[row];
				UB[j] = rowPtr[row+1];
				y[row] = 0;
				currentrow[j] = row;
			} else {
				done[j] = true;
				printf("Skipping row update\n");
			}
		} else {
			int k = LB[j];
			if(currentrow[j] < NUM_ROWS) {
				printf("compute value %d on row %d\n", k, currentrow[j]);
				y[currentrow[j]] += values[k] * x[columnIndex[k]];
				LB[j]++;
			} else {
				printf("Skipping compute\n");
			}
		}
		bool alldone = true;
#pragma HLS DEPENDENCE variable=alldone inter false
		for (int i=0; i<S; i++){
			alldone &= done[i];
		}
		if(alldone) break;
	}
}
