
#define NUM_TAPS 4

void block_fir(int input[256], int output[256], int taps[NUM_TAPS],
							 int delay_line[NUM_TAPS]) {
	int i, j;
	for (j = 0; j < 256; j++) {
		int result = 0;
		for (i = NUM_TAPS - 1; i > 0; i--) {
#pragma HLS unroll
			delay_line[i] = delay_line[i - 1];
		}
		delay_line[0] = input;

		for (i = 0; i < NUM_TAPS; i++) {
#pragma HLS pipeline
			result += delay_line[i] * taps[i];
		}
		output[j] = result;
	}
}
