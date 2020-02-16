#ifndef BITREVERSE_H
#define BITREVERSE_H
typedef float DTYPE;
typedef int INTTYPE;

#define SIZE 1024 		/* SIZE OF FFT */
#define SIZE2 SIZE>>1	/* SIZE OF FFT/2 */
#define M 10			/* Number of Stages = Log2N */


void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);

#endif
