
#include "stdio.h"
#include "block_fir.h"

const int SIZE = 256;

int main() {
  int taps[] = {1,2,0,-3,0,4,-5,0,1,-2,0,-3,0,4,-5,0};
  int delay_line[NUM_TAPS] = {0};
  int input[256] = {0}, output[256] = {0};
  for(int i = 0; i < SIZE; i++) {
    input[i] = i;
    printf("input[%d] = %d output %d \n", i, input[i], output[i]);
  }
  block_fir(input, output, taps, delay_line);
  printf("result = %d\n", output[SIZE-1]);
  if(output[SIZE-1] == -1452) {
    return 0;
  } else {
    return 1;
  }
}

