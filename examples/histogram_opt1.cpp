#include "histogram.h"
void histogram(int in[INPUT_SIZE], int hist[VALUE_SIZE]) {
  int acc = 0;
  int i, val;
  int old = in[0];
  #pragma HLS DEPENDENCE variable=hist intra RAW false
  for(i = 0; i < INPUT_SIZE; i++) {
    #pragma HLS PIPELINE II=1
    val = in[i];
    if(old == val) {
      acc = acc + 1;
    } else {
      hist[old] = acc;
      acc = hist[val] + 1;
    }
    old = val;
  }
  hist[old] = acc;
}
