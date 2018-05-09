#include "spmv.h"
#include <stdio.h>

const static int S = 8;

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
       DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE])
{
	//#pragma HLS ARRAY_PARTITION variable=rowPtr cyclic factor=2 dim=1
	int currentrow[S];
	int LB;
	int UB;
	int flag[S];
	int row;

	//#pragma HLS ARRAY_PARTITION variable=currentrow complete
	//#pragma HLS ARRAY_PARTITION variable=LB complete
	//#pragma HLS ARRAY_PARTITION variable=UB complete
	//#pragma HLS ARRAY_PARTITION variable=flag complete

 Init:
 for (int i=0; i<S; i++){
#pragma HLS PIPELINE II=1
	 LB[i] = rowPtr[i];
	 UB[i] = rowPtr[i+1];
	 y[i] = 0;
	 currentrow[i] = i;
 }
 row = S-1;
 int L, K;

 ACC:
 for(int i=0; i<NNZ * S; i++ ) {
	 int j = i % S;
#pragma HLS DEPENDENCE variable=y inter distance=8
	 //#pragma HLS DEPENDENCE variable=UB inter distance=8
	 //#pragma HLS DEPENDENCE variable=LB inter distance=8
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
	}
}
