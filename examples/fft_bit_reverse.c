#define FFT_BITS 10			// Number of bits of FFT, i.e., log(1024)
#define SIZE 1024				// SIZE OF FFT
#define SIZE2 SIZE >> 1 // SIZE/2
#define DTYPE int

unsigned int reverse_bits(unsigned int input) {
	int i, rev = 0;
	for (i = 0; i < FFT_BITS; i++) {
		rev = (rev << 1) | (input & 1);
		input = input >> 1;
	}
	return rev;
}

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]) {
	unsigned int reversed;
	unsigned int i;
	DTYPE temp;

	for (i = 0; i < SIZE; i++) {
		reversed = reverse_bits(i); // Find the bit reversed index
		if (i < reversed) {
			// Swap the real values
			temp = X_R[i];
			X_R[i] = X_R[reversed];
			X_R[reversed] = temp;

			// Swap the imaginary values
			temp = X_I[i];
			X_I[i] = X_I[reversed];
			X_I[reversed] = temp;
		}
	}
}
