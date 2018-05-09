
#include "stdio.h"

#define NUM_TAPS 4
void fir(int input, int *output, int taps[NUM_TAPS]);

const int SIZE = 256;

int main() {
	int taps[] = {1, 2, 0, -3, 0, 4, -5, 0, 1, -2, 0, -3, 0, 4, -5, 0};
	int out = 0;
	for (int i = 0; i < SIZE; i++) {
		fir(i, &out, taps);
	}
	printf("result = %d\n", out);
	if (out == -1452) {
		return 0;
	} else {
		return 1;
	}
}
