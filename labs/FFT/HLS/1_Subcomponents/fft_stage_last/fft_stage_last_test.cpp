/* Testbench for  fft_stages_op functions.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft_stage_last.h"

struct Rmse
{
	int num_sq;
	float sum_sq;
	float error;

	Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

	float add_value(float d_n)
	{
		num_sq++;
		sum_sq += (d_n*d_n);
		error = sqrtf(sum_sq / num_sq);
		return error;
	}

};

Rmse rmse_R,  rmse_I;

DTYPE In_R[SIZE], In_I[SIZE];
DTYPE Out_R[SIZE], Out_I[SIZE];

int main()
{
	FILE * fp = fopen("out.gold.dat","r");
	DTYPE gold_R, gold_I;
	int index;

	//Setup input data
	for(int i=0; i<SIZE; i++){
		In_R[i] = i;
		In_I[i] = 0.0;
		Out_R[i] = 0.0;
		Out_I[i] = 0.0;
	}


	//Invoke FFT last stage
	fft_stage_last(In_R, In_I, Out_R, Out_I);

	//Print output
	printf("Printing FFT Output\n");
	for(int i=0; i<SIZE; i++){
		printf("%4d\t%f\t%f\n",i,Out_R[i],Out_I[i]);
	}

	printf ("Comparing against output data \n");
	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R.add_value((float)Out_R[i] - gold_R);
		rmse_I.add_value((float)Out_I[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("----------------------------------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
	printf("----------------------------------------------\n");

	if (rmse_R.error > 0.1 || rmse_I.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
	}
}
