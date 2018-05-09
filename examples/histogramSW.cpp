void histogram(int in[INPUT_SIZE], int hist[VALUE_SIZE]) {
  int val;
  for(int i = 0; i < INPUT_SIZE; i++) {
    #pragma HLS PIPELINE
    val = in[i];
    hist[val] = hist[val] + 1;
  }
}
