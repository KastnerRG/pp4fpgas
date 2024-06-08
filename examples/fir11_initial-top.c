
#include "stdio.h"

typedef int coef_t;
typedef int data_t;
typedef int acc_t;

const int SIZE = 256;

void fir(data_t *y, data_t x);

int main() {
	int out = 0;
	for (int i = 0; i < SIZE; i++) {
		fir(&out, i);
	}
	printf("result = %d\n", out);
	if (out == 262500) {
		return 0;
	} else {
		return 1;
	}
}
