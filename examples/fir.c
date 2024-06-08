#include "fir.h"

void fir(int input, int *output, int taps[NUM_TAPS])
{
	static int delay_line[NUM_TAPS] = {};

	int result = 0;
	for (int i = NUM_TAPS - 1; i > 0; i--) {
		delay_line[i] = delay_line[i - 1];
	}
	delay_line[0] = input;
	
	for (int j = 0; j < NUM_TAPS; j++) {
		result += delay_line[j] * taps[j];
	}
	
	*output = result;
}
