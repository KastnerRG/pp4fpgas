#include "spmv.h"

const static int S = 7;

void spmv(int rowPtr[NUM_ROWS+1], int columnIndex[NNZ],
          DTYPE values[NNZ], DTYPE y[SIZE], DTYPE x[SIZE])
{
  L1: for (int i = 0; i < NUM_ROWS; i++) {
	  DTYPE y0 = 0;
    L2_1: for (int k = rowPtr[i]; k < rowPtr[i+1]; k += S) {
#pragma HLS pipeline II=S
		  DTYPE yt = values[k] * x[columnIndex[k]];
	  L2_2: for(int j = 1; j < S; j++) {
			  if(k+j < rowPtr[i+1]) {
				  yt += values[k+j] * x[columnIndex[k+j]];
			  }
		  }
		  y0 += yt;
	  }
    y[i] = y0;
  }
}
