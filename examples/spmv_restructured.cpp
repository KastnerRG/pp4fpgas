#include "spmv.h"

const static int S = 8;

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
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
 for (i=0; i<S; i++){
#pragma HLS PIPELINE II=1
	cnt[i] = i;
	LB[i] = row_ptr[i];
	UB[i] = row_ptr[i+1];
	element_left[i] = UB[i] - LB[i];
	element_done[i] = 0;
	flag[i] = 0;
 }

	int max = 3;
	int L, K;
	int loop_bound = NNZ+4;

ACC:  for(i=0; i<loop_bound/S; i++ )
		for(j=0; j < S; j++) {
#pragma HLS DEPENDENCE variable=y array inter false
#pragma HLS DEPENDENCE variable=element_left array inter false
#pragma HLS DEPENDENCE variable=element_done array inter false
#pragma HLS PIPELINE II=1

			if (flag[j] == 1){
				continue;
			}

			//L = read_idx(LB, UB, j, element_done, element_left);
			L = LB[j] + element_done[j];
			element_left[j] -= 1;
			element_done[j] += 1;
			//K = write_idx(j,cnt);
			K = cnt[j];
			y[K] += values[L] * x[columnIndex[L]];

			//	reset(element_left, j, element_done);
			if ( element_left[j] == 0) {
				//update_counter(element_left, &max, j, cnt);
				max += 1;
				cnt[j] = max;
				if (max < m){
					// row_pointer(LB, UB, j, row_ptr, max, cnt, element_left);
					LB[j] = row_ptr[max];
					UB[j] = row_ptr[max+1];
					element_left[i_mod_4] = UB[i_mod_4] - LB[i_mod_4];
				} else {
					flag[j] = 1;
				}
			}
	  }
}
