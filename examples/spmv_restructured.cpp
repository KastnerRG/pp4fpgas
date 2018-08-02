#include "spmv.h"
#include <iostream>

const static int S = 4;

void spmv(int row_ptr[NUM_ROWS+1], int columnIndex[NNZ],
       DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE])
{
#pragma HLS ARRAY_PARTITION variable=row_ptr cyclic factor=16 dim=1

int i;
int cnt[4];
int LB[4];
int UB[4];
int element_left[4];
int element_done[4];
int flag[4];

#pragma HLS ARRAY_PARTITION variable=cnt cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=element_left cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=LB cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=UB cyclic factor=4 dim=1
#pragma HLS ARRAY_PARTITION variable=element_done cyclic factor=4 dim=1

 Init:
 for (int i = 0; i < S; i++){
#pragma HLS PIPELINE II=1
	cnt[i] = i;
	LB[i] = row_ptr[i];
	UB[i] = row_ptr[i+1];
	element_left[i] = UB[i] - LB[i];
	element_done[i] = 0;
	flag[i] = 0;
    // std::cout << "starting row " << i << " from " << LB[i] << " to " << UB[i] << "\n";
 }

	int max = S-1;
	int L, K;
	int loop_bound = NNZ+4;

ACC:  for(int i = 0; i < loop_bound/S; i++ )
    for(int j = 0; j < S; j++) {
#pragma HLS DEPENDENCE variable=y array inter false
#pragma HLS DEPENDENCE variable=element_left array inter false
#pragma HLS DEPENDENCE variable=element_done array inter false
#pragma HLS PIPELINE II=1

			if(flag[j] == 1){
				continue;
			}

			L = LB[j] + element_done[j];
			element_left[j] -= 1;
			element_done[j] += 1;
			K = cnt[j];
            // std::cout << "Add NNZ " << L << " for row " << K << "\n";
			y[K] += values[L] * x[columnIndex[L]];

			if(element_left[j] == 0) {
				max += 1;
				cnt[j] = max;
				if(max < NUM_ROWS) {
					LB[j] = row_ptr[max];
					UB[j] = row_ptr[max+1];
					element_left[j] = UB[j] - LB[j];
                    element_done[j] = 0;
                    // std::cout << "starting row " << max << " from " << LB[j] << " to " << UB[j] << "\n";
				} else {
					flag[j] = 1;
				}
			}
	  }
}
