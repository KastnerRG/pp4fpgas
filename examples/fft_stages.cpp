#include "fft_streaming.h"
#include "math.h"

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
  DTYPE k = 0;
  DTYPE e = -6.283185307178 / DFTpts;
  DTYPE a = 0.0;
  // Perform butterflies for j-th stage
 butterfly_loop:
  for (int j = 0; j < numBF; j++) {
    DTYPE c = cos(a);
    DTYPE s = sin(a);
    a = a + e;
    // Compute butterflies that use same W**k
  dft_loop:
    for (int i = j; i < SIZE; i += DFTpts) {
      int i_lower = i + numBF; // index of lower point in butterfly
      DTYPE temp_R = X_R[i_lower] * c - X_I[i_lower] * s;
      DTYPE temp_I = X_I[i_lower] * c + X_R[i_lower] * s;
      Out_R[i_lower] = X_R[i] - temp_R;
      Out_I[i_lower] = X_I[i] - temp_I;
      Out_R[i] = X_R[i] + temp_R;
      Out_I[i] = X_I[i] + temp_I;
    }
    k += step;
  }
}
 
void fft_streaming(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
  #pragma HLS dataflow
  DTYPE Stage1_R[SIZE], Stage1_I[SIZE],
  
  bit_reverse(X_R, X_I, Stage1_R, Stage1_I);
  fft_stage(1, Stage1_R, Stage1_I, Stage2_R, Stage2_I);
}
