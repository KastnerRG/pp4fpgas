/*
This is traditional 2-radix DIT FFT algorithm implementation.
It is based on conventional 3-loop structure. 
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"

void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE])
{

	DTYPE temp_R;		/*temporary storage complex variable*/
	DTYPE temp_I;		/*temporary storage complex variable*/


	int i,j,k;			/* loop indexes */
	int i_lower;		/* Index of lower point in butterfly */
	int step;

	int stage;
	int DFTpts;
	int numBF;			/*Butterfly Width*/

	int N2 = SIZE2;	/* N2=N>>1 */

	/*=====================BEGIN BIT REBERSAL===========================*/
	// write your code here

	/*++++++++++++++++++++++END OF BIT REVERSAL++++++++++++++++++++++++++*/

	/*=======================BEGIN: FFT=========================*/
	// Do M stages of butterflies
	step=N2;
	DTYPE a, e, c, s;

	stages:for(stage=1; stage<= M; stage++)
	{
		DFTpts = 1 << stage;		// DFT = 2^stage = points in sub DFT
		numBF = DFTpts/2; 			// Butterfly WIDTHS in sub-DFT
		k=0;

		e = -6.283185307178/DFTpts;

		a = 0.0;
		// Perform butterflies for j-th stage
		butterfly:for(j=0; j<numBF; j++)
		{

			c = cos(a);
			s = sin(a);
			a = a + e;

			// Compute butterflies that use same W**k
			DFTpts:for(i=j; i<SIZE; i += DFTpts)
			{

				i_lower = i + numBF;			//index of lower point in butterfly
				temp_R = X_R[i_lower]*c- X_I[i_lower]*s;
				temp_I = X_I[i_lower]*c+ X_R[i_lower]*s;

				X_R[i_lower] = X_R[i] - temp_R;
				X_I[i_lower] = X_I[i] - temp_I;
				X_R[i] = X_R[i] + temp_R;
				X_I[i] = X_I[i] + temp_I;
			}
			k+=step;
		}
		step=step/2;
	}
}
/*=======================END: FFT=========================*/
