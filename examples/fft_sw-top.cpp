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
#include <iostream>
#include <fstream>
#include <math.h>
#include "fft.h"

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE WW_R[SIZE], WW_I[SIZE];

int main()
{
	FILE *fp;
	FILE *fp_r, *fp_i;
	printf("GENERATING INPUTS\n");
	for(int i=0; i<SIZE; i++){
		In_R[i] = i;
		In_I[i] = 0.0;
	}
	
	//Twiddle factor is calculated here and saved in fft.h to be used in offline.
		double	e = -6.2831853071795864769;
		printf("GENERATING %d TWIDDLE FACTORS\n", SIZE);
		fp_r=fopen("tw_r.h", "w");
		fp_i=fopen("tw_i.h", "w");
		fprintf(fp_r, "const DTYPE W_real[]={");
		fprintf(fp_i, "const DTYPE W_imag[]={");
		for(int i=0; i<SIZE2; i++)
		{
			//COMPLEX W;	// e^(-j 2 pi/ N)
		  double w = e*double(i)/double(SIZE);
		  WW_R[i]=cos(w);
		  WW_I[i]=sin(w);
		  //printf("%4d\t%f\t%f\n",i,WW_R[i],WW_I[i]);
			fprintf(fp_r, "%.20f,",WW_R[i]);
			fprintf(fp_i, "%.20f,",WW_I[i]);
			if(i%16==0)
				{
					fprintf(fp_r, "\n");
					fprintf(fp_i, "\n");
				}
		}
		fprintf(fp_r, "};\n");	
		fprintf(fp_i, "};\n");
		fclose(fp_r);
		fclose(fp_i);


	//Perform FFT
	fft(In_R, In_I);
	//Print output
	fp=fopen("out.fft.dat", "w");
	printf("Printing FFT Output\n");
	for(int i=0; i<SIZE; i++){
	  //printf("%4d\t%f\t%f\n",i,In_R[i],In_I[i]);
		fprintf(fp, "%4d\t%f\t%f\n",i,In_R[i],In_I[i]);
	}
	fclose(fp);

	
	printf ("Comparing against output data \n");
	std::ifstream golden("out.fft.gold.dat");

	DTYPE error = 0.0;
	DTYPE maxerror = 0.0;
	for(int i=0; i<SIZE; i++) {
	  DTYPE rx, ix;
	  int j;
	  golden >> j >> rx >> ix;
	  DTYPE newerror = fabs(rx-In_R[i]) + fabs(ix-In_I[i]);
	  error += newerror;
	  if(newerror > maxerror) {
	    maxerror = newerror; 
	    fprintf(stdout, "Max Error@%d: %f\n", i, maxerror);
	  }
	}

	fprintf(stdout, "Average Error: %f\n",error/SIZE);
	
	if ((error/SIZE) > .05 || maxerror > 2) { // This is somewhat arbitrary.  Should do proper error analysis.
	  fprintf(stdout, "*******************************************\n");
	  fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
	  fprintf(stdout, "*******************************************\n");
	  return 1;
	} else {
	  fprintf(stdout, "*******************************************\n");
	  fprintf(stdout, "PASS: The output matches the golden output!\n");
	  fprintf(stdout, "*******************************************\n");
	  return 0;
	}
	
}
