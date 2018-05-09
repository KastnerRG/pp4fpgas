#define SIZE 128
void prefixsum(int in[SIZE], int out[SIZE]) {
  #pragma HLS ARRAY_PARTITION variable=out cyclic factor=4 dim=1
  #pragma HLS ARRAY_PARTITION variable=in cyclic factor=4 dim=1
  int A = in[0];
  for(int i=0; i < SIZE; i++) {
    #pragma HLS UNROLL factor=4
    #pragma HLS PIPELINE
    out[i] = out[i-1] + in[i];
  }
}
