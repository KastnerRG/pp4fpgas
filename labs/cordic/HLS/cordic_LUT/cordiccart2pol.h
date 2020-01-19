#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#include <ap_fixed.h>

#define NO_ITER 16

typedef float data_t; // Type of the input/output and LUT values. You can change the bitwidth.

#define W			32 // Total size of fixed-point representation. Must be W >= (I+MAN_BITS)
#define I			2  // Size of integer part of fixed-point (1 bit sign + 1 bit integer)
#define MAN_BITS	5  // Size of fractional part. Vary this number to increase/decrease the resolution.
#define LUT_SIZE	(1 << ((MAN_BITS+I) << 1)) // Size of the LUT. It is 2^(2*(MAN_BITS+I)).

#define ERROR		0.0001 // Used in test bench

#ifdef TEST_BENCH
extern data_t my_LUT_r[LUT_SIZE];
extern data_t my_LUT_th[LUT_SIZE];
#endif

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);

#endif // CORDICCART2POL_H
