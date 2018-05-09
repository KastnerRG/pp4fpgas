acc = 0;
MAC:
for (i = N - 1; i >= 3; i -= 4) {
	acc += shift_reg[i] * c[i] + shift_reg[i - 1] * c[i - 1] +
				 shift_reg[i - 2] * c[i - 2] + shift_reg[i - 3] * c[i - 3];
}

for (; i >= 0; i--) {
	acc += shift_reg[i] * c[i];
}
