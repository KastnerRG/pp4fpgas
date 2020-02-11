#include "cordiccart2pol.h"
// Look-up tables.
// They are filled in the test bench. You could also explicitly write all the numbers.
volatile data_t my_LUT_th[LUT_SIZE];
volatile data_t my_LUT_r[LUT_SIZE];

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta)
{
	// you have to answer to this question: What happens if you uncomment these pragma?
//#pragma HLS RESOURCE variable=my_LUT_th core=RAM_1P_LUTRAM
//#pragma HLS RESOURCE variable=my_LUT_r core=RAM_1P_LUTRAM


	// Convert the floating-point inputs to fixed-point representation
	ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_x = x;
	ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_y = y;

	// Build the index to find the entries in the LUT.
	ap_uint<2*(I+MAN_BITS)> index;

	// Concatenate the bits of (fixed-point) x and y to create the index
	for(int i = 0; i < I+MAN_BITS; i++)
	{
#pragma HLS UNROLL
		index[2*(I+MAN_BITS)-1-i] = fixed_x[W-1-i];
		index[(I+MAN_BITS)-1-i]   = fixed_y[W-1-i];
	}


	// Get the result from the LUT and write it back to the output
	*r     = my_LUT_r[index];
	*theta = my_LUT_th[index];
}
