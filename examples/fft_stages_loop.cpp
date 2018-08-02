#include "fft_streaming.h"
#include "math.h"
#include <iostream>

unsigned int reverse_bits(unsigned int input) {
	int i, rev = 0;
	for (i = 0; i < M; i++) {
		rev = (rev << 1) | (input & 1);
		input = input >> 1;
	}
	return rev;
}

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
		 DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
  unsigned int reversed;
  unsigned int i;
  DTYPE temp;
  
  for (int i = 0; i < SIZE; i++) {
	  reversed = reverse_bits(i); // Find the bit reversed index
		if (i <= reversed) {
			// Swap the real values
			temp = X_R[i];
			OUT_R[i] = X_R[reversed];
			OUT_R[reversed] = temp;

			// Swap the imaginary values
			temp = X_I[i];
			OUT_I[i] = X_I[reversed];
			OUT_I[reversed] = temp;
		}
	}
}

void fft_stage(int stage, DTYPE X_R[SIZE], DTYPE X_I[SIZE],
		     DTYPE Out_R[SIZE], DTYPE Out_I[SIZE]) {
  int DFTpts = 1 << stage;    // DFT = 2^stage = points in sub DFT
  int numBF = DFTpts / 2;     // Butterfly WIDTHS in sub-DFT
  int step = SIZE >> stage;
  // Perform butterflies for j-th stage
 butterfly_loop:
  for (int j = 0; j < numBF; j++) {
    // Compute butterflies that use same W**k
  dft_loop:
      for(int t = 0; t < step; t++) {
          int i = j + t*DFTpts;
          //    for (int i = j; i < SIZE; i += DFTpts) {
#pragma HLS pipeline
          int k = j*step;
      DTYPE c = W_real[k];
      DTYPE s = W_imag[k];
      int i_lower = i + numBF; // index of lower point in butterfly
      DTYPE temp_R = X_R[i_lower] * c - X_I[i_lower] * s;
      DTYPE temp_I = X_I[i_lower] * c + X_R[i_lower] * s;
      Out_R[i_lower] = X_R[i] - temp_R;
      Out_I[i_lower] = X_I[i] - temp_I;
      Out_R[i] = X_R[i] + temp_R;
      Out_I[i] = X_I[i] + temp_I;
    }
  }
}

void fft_streaming(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
  #pragma HLS dataflow
  DTYPE Stage_R[M][SIZE], Stage_I[M][SIZE];
  #pragma HLS array_partition variable=Stage_R dim=1 complete
  #pragma HLS array_partition variable=Stage_I dim=1 complete

  bit_reverse(X_R, X_I, Stage_R[0], Stage_I[0]);
 stage_loop:
  for (int stage = 1; stage < M; stage++) { // Do M-1 stages of butterflies
    #pragma HLS unroll
    fft_stage(stage, Stage_R[stage-1], Stage_I[stage-1], Stage_R[stage], Stage_I[stage]);
  }
  fft_stage(M, Stage_R[M-1], Stage_I[M-1], OUT_R, OUT_I);
}
