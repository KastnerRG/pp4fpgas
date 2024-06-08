#include "stdio.h"
#define SIZE 128
extern void prefixsum(int in[SIZE], int out[SIZE]);

int main() {
	int in[SIZE];
	int out[SIZE];
	int expected_out = 8128;
	int fail = 0;

	for(int i = 0; i < SIZE; i++) {
		in[i] = i;
	}
	prefixsum(in, out);
    for(int i = 0; i < SIZE; i++) {
		printf("%d ", out[i]);
	}
	printf("\n");

	if (out[SIZE-1] != expected_out) {
		fail = 1;
	} else {
		fail = 0;
	}
	
	if(fail == 1)
		printf("FAILED\n");
	else
		printf("PASS\n");

	return fail;	
}
