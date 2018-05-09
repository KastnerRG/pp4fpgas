void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE]) {
	DTYPE temp_R; // temporary storage complex variable
	DTYPE temp_I; // temporary storage complex variable
	int i, j, k;	// loop indexes
	int i_lower;	// Index of lower point in butterfly
	int step, stage, DFTpts;
	int numBF;			// Butterfly Width
	int N2 = SIZE2; // N2=N>>1

	bit_reverse(X_R, X_I);

	step = N2;
	DTYPE a, e, c, s;

stage_loop:
	for (stage = 1; stage <= M; stage++) { // Do M stages of butterflies
		DFTpts = 1 << stage;								 // DFT = 2^stage = points in sub DFT
		numBF = DFTpts / 2;									 // Butterfly WIDTHS in sub-DFT
		k = 0;
		e = -6.283185307178 / DFTpts;
		a = 0.0;
	// Perform butterflies for j-th stage
	butterfly_loop:
		for (j = 0; j < numBF; j++) {
			c = cos(a);
			s = sin(a);
			a = a + e;
		// Compute butterflies that use same W**k
		dft_loop:
			for (i = j; i < SIZE; i += DFTpts) {
				i_lower = i + numBF; // index of lower point in butterfly
				temp_R = X_R[i_lower] * c - X_I[i_lower] * s;
				temp_I = X_I[i_lower] * c + X_R[i_lower] * s;
				X_R[i_lower] = X_R[i] - temp_R;
				X_I[i_lower] = X_I[i] - temp_I;
				X_R[i] = X_R[i] + temp_R;
				X_I[i] = X_I[i] + temp_I;
			}
			k += step;
		}
		step = step / 2;
	}
}
