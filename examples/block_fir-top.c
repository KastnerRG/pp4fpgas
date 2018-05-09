
#include "stdio.h"

#include "fir.c"

const int SIZE = 256;

int main() {
  int taps[] = {1,2,0,-3,0,4,-5,0,1,-2,0,-3,0,4,-5,0};
  int delay_line[4];
  int input[256], output[256];
  for(int i = 0; i < SIZE; i++) {
    input[i] = i;
  } 
  block_fir(i, &out, taps, delay_line);
  for(int i = 0; i < SIZE; i++) {
    printf("result = %d\n", output[i]);
    if(output[i] == -1452) {
      return 0;
    } else {
      return 1;
    }
  }
}
