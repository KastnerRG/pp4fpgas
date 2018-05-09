float mul(int x, int y) { return x * y; }

float top_function(float a, float b, float c, float d) {
	return mul(a, b) + mul(c, d) + mul(b, c) + mul(a, d);
}

float inlined_top_function(float a, float b, float c, float d) {
	return a * b + c * d + b * c + a * d;
}
