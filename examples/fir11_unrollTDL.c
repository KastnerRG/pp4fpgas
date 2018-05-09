TDL:
for (i = N - 1; i > 1; i = i - 2) {
	shift_reg[i] = shift_reg[i - 1];
	shift_reg[i - 1] = shift_reg[i - 2];
}
if (i == 1) {
	shift_reg[1] = shift_reg[0];
}
shift_reg[0] = x;
