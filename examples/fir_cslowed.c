
#define NUM_TAPS 4

void block_fir(int input[256][K], int output[256][K], int taps[NUM_TAPS],
							 int delay_line[NUM_TAPS][K]) {
	int i, j, k for (j = 0; j < 256; j++) {
		for (k = 0; k < K; k++) {
			int result[K] = {};
			for (i = NUM_TAPS - 1; i > 0; i--) {
#pragma HLS unroll
				delay_line[i][k] = delay_line[i - 1][k];
			}
			delay_line[0][k] = input;

			for (i = 0; i < NUM_TAPS; i++) {
#pragma HLS pipeline
				result[k] += delay_line[i][k] * taps[i];
			}
			output[j][k] = result;
		}
	}
}
