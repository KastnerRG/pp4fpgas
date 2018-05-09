#include "spmv.h"

const static int S = 8;

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
       DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE])
{
#pragma HLS ARRAY_PARTITION variable=row_ptr cyclic factor=16 dim=1

int i;
int cnt;
int LB;
int UB;
int flag;

//#pragma HLS ARRAY_PARTITION variable=cnt cyclic factor=4 dim=1
//#pragma HLS ARRAY_PARTITION variable=element_left cyclic factor=4 dim=1
//#pragma HLS ARRAY_PARTITION variable=LB cyclic factor=4 dim=1
//#pragma HLS ARRAY_PARTITION variable=UB cyclic factor=4 dim=1
//#pragma HLS ARRAY_PARTITION variable=element_done cyclic factor=4 dim=1

	LB = rowPtr[0];
	UB = rowPtr[1];

	int row = 0;
	int L, K;
	y[row] = 0;
 ACC:  for(i=0; i<NNZ + NUM_ROWS; i++ ) {
#pragma HLS DEPENDENCE variable=y array inter false
#pragma HLS DEPENDENCE variable=element_left array inter false
#pragma HLS DEPENDENCE variable=element_done array inter false
#pragma HLS PIPELINE II=1

		if(LB == UB) {
			row++;
			UB = rowPtr[row+1];
			y[row] = 0;
			if(row >= NUM_ROWS) break;
		} else {
			int k = LB;
			y[row] += values[k] * x[columnIndex[k]];
			LB++;
		}
	}
}
