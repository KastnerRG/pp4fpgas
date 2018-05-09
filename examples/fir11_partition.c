TDL:
for (i = N - 1; i > 0; i--) {
	shift_reg[i] = shift_reg[i - 1];
}
shift_reg[0] = x;

acc = 0;
MAC:
for (i = N - 1; i >= 0; i--) {
	acc += shift_reg[i] * c[i];
}
