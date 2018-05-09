Shift_Accum_Loop:
for (i = N - 1; i > 0; i--) {
	shift_reg[i] = shift_reg[i - 1];
	acc += shift_reg[i] * c[i];
}

acc += x * c[0];
shift_reg[0] = x;
