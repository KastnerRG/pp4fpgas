
#include <stdio.h>
#include <stdlib.h>
//#include <fcntl.h>
#include "fft.h"

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE Out_R[SIZE], Out_I[SIZE];

//void demod(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int D[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);

int main()
{
	const int FSIZE=35000;
	DTYPE In_R[FSIZE], In_I[FSIZE];
	FILE *fp;

	fp = fopen("input.dat", "r");

	printf("Reading INPUTS\n");
	for (int i = 0; i < FSIZE; i++) {
		fscanf(fp, "%f %f\n", &In_R[i], &In_I[i]);
	}

	fclose(fp);


	//Perform FFT
	int D[FSIZE] = {0};
	int dindex = 0;
	int iindex = 0;
	DTYPE In_R_block[SIZE], In_I_block[SIZE];
	DTYPE Out_R_block[SIZE], Out_I_block[SIZE];
	DTYPE Out_R[FSIZE], Out_I[FSIZE];

	int j = 0;
	for (int i = 0; i < FSIZE; i++) {
		DTYPE tohw[2];
		uint32_t from_hw[1];

		In_R_block[j] = In_R[i];
		In_I_block[j] = In_I[i];
		tohw[0] = In_R_block[j];
		tohw[1] = In_I_block[j];

		ofdm_receiver( &tohw[0], &from_hw[0] );

		D[dindex] = from_hw[0];
		dindex++;

	}

	printf("Comparing with golden output\n");
	fp = fopen("out.gold.dat", "r");

	int gold, result = 0;
	for( int i=0 ; i < FSIZE ; i++ ){
		fscanf(fp, "%d", &gold );
		if (gold != D[i]){
			printf("miss match: i: %d\tgolden: %d\toutput: %d\n", i, gold, D[i] );
			result = 1;

		}
	}

	fclose(fp);

	//Check against golden output.
	printf ("Comparing against output data \n");

	if (result) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		return result;
	} else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		return result;
	}

}
