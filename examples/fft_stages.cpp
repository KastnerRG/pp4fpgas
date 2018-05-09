void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
        DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_one(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
        DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stages_two(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
        DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_three(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
        DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
  #pragma HLS dataflow
  DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
  DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
  DTYPE Stage3_R[SIZE], Stage3_I[SIZE];

  bit_reverse(X_R, X_I, Stage1_R, Stage1_I);
  fft_stage_one(Stage1_R, Stage1_I, Stage2_R, Stage2_I);
  fft_stages_two(Stage2_R, Stage2_I, Stage3_R, Stage3_R);
  fft_stage_three(Stage3_R, Stage3_I, OUT_R, OUT_I);
}
