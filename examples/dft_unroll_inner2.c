
...
// Calculate the jth frequency sample sequentially
for (j = 0; j < N; j += 2) {
  // Fetch precomputed sine and cosine values
  c_0 = cos_table[i * j];
  s_0 = sin_table[i * j];
  c_1 = cos_table[i * (j + 1)];
  s_1 = sin_table[i * (j + 1)];

  // Multiply c and s with the appropriate input sample and keep running sum
  temp_real[i] += (sample_real[j] * c_0 - sample_imag[j] * s_0) +
    (sample_real[j + 1] * c_1 - sample_imag[j + 1] * s_1);
  temp_imag[i] += (sample_real[j] * s_0 + sample_imag[j] * c_0) +
    (sample_real[j + 1] * s_1 + sample_imag[j + 1] * c_1);
}
...
