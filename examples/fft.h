#ifndef FFT_H_
#define FFT_H_

typedef float DTYPE;
typedef int INTTYPE;
#define M 10 			/* Number of Stages = Log2N */
#define SIZE 1024 		/* SIZE OF FFT */
#define SIZE2 SIZE>>1	/* SIZE/2 */

void fft(DTYPE XX_R[SIZE], DTYPE XX_I[SIZE]);

//W_real and W_image are twiddle factors for 1024 size FFT.
//WW_R[i]=cos(e*i/SIZE);
//WW_I[i]=sin(e*i/SIZE);
//where i=[0,512) and DTYPE	e = -6.283185307178;
#include "tw_r.h"
#include "tw_i.h"

#endif
