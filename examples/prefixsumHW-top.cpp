#include "stdio.h"
#define SIZE 128
extern void prefixsum(int in[SIZE], int out[SIZE]);

int main() {
	int in[SIZE];
	int out[SIZE];
	for(int i = 0; i < SIZE; i++) {
		in[i] = i;
	}
	prefixsum(in, out);
    for(int i = 0; i < SIZE; i++) {
		printf("%d ", out[i]);
	}
	printf("\n");
}
