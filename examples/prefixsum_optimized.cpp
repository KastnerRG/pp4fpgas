#define SIZE 128
void prefixsum(int in[SIZE], int out[SIZE]) {
  int A = in[0];
  for(int i=0; i < SIZE; i++) {
    #pragma HLS PIPELINE
    A = A + in[i];
    out[i] = A;
  }
}
