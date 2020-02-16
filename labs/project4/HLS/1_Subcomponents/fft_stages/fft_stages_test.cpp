/* 
 * Testbench for fft_stages 
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft_stages.h"

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

//stage 2
DTYPE In_R2[SIZE], In_I2[SIZE];
DTYPE Out_R2[SIZE], Out_I2[SIZE];

//stage 3
DTYPE In_R3[SIZE], In_I3[SIZE];
DTYPE Out_R3[SIZE], Out_I3[SIZE];

//stage 4
DTYPE In_R4[SIZE], In_I4[SIZE];
DTYPE Out_R4[SIZE], Out_I4[SIZE];

//stage 5
DTYPE In_R5[SIZE], In_I5[SIZE];
DTYPE Out_R5[SIZE], Out_I5[SIZE];

//stage 6
DTYPE In_R6[SIZE], In_I6[SIZE];
DTYPE Out_R6[SIZE], Out_I6[SIZE];

//stage 7
DTYPE In_R7[SIZE], In_I7[SIZE];
DTYPE Out_R7[SIZE], Out_I7[SIZE];

//stage 8
DTYPE In_R8[SIZE], In_I8[SIZE];
DTYPE Out_R8[SIZE], Out_I8[SIZE];

//stage 9
DTYPE In_R9[SIZE], In_I9[SIZE];
DTYPE Out_R9[SIZE], Out_I9[SIZE];



int main()
{
	FILE *fp;

	//Setup input data
	for(int i=0; i<SIZE; i++){
		//Stage 2
		In_R2[i] = i;
		In_I2[i] = 0.0;
		Out_R2[i] = 0.0;
		Out_I2[i] = 0.0;

		//Stage 3
		In_R3[i] = i;
		In_I3[i] = 0.0;
		Out_R3[i] = 0.0;
		Out_I3[i] = 0.0;

		//Stage 4
		In_R4[i] = i;
		In_I4[i] = 0.0;
		Out_R4[i] = 0.0;
		Out_I4[i] = 0.0;

		//Stage 5
		In_R5[i] = i;
		In_I5[i] = 0.0;
		Out_R5[i] = 0.0;
		Out_I5[i] = 0.0;

		//Stage 6
		In_R6[i] = i;
		In_I6[i] = 0.0;
		Out_R6[i] = 0.0;
		Out_I6[i] = 0.0;

		//Stage 7
		In_R7[i] = i;
		In_I7[i] = 0.0;
		Out_R7[i] = 0.0;
		Out_I7[i] = 0.0;

		//Stage 8
		In_R8[i] = i;
		In_I8[i] = 0.0;
		Out_R8[i] = 0.0;
		Out_I8[i] = 0.0;

		//Stage 9
		In_R9[i] = i;
		In_I9[i] = 0.0;
		Out_R9[i] = 0.0;
		Out_I9[i] = 0.0;

	}

	//Perform FFT
	DTYPE gold_R, gold_I;
	int index;

	//Stage 2
	Rmse rmse_R2,  rmse_I2;
	fp = fopen("out2.gold.dat","r");

	fft_stages(In_R2, In_I2, 2, Out_R2, Out_I2);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R2.add_value((float)Out_R2[i] - gold_R);
		rmse_I2.add_value((float)Out_I2[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 2--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R2.error, rmse_I2.error);
	printf("----------------------------------------------\n");

	if (rmse_R2.error > 0.1 || rmse_I2.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 2 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 2 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 3
	Rmse rmse_R3,  rmse_I3;
	fp = fopen("out3.gold.dat","r");

	fft_stages(In_R3, In_I3, 3, Out_R3, Out_I3);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R3.add_value((float)Out_R3[i] - gold_R);
		rmse_I3.add_value((float)Out_I3[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 3--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R3.error, rmse_I3.error);
	printf("----------------------------------------------\n");

	if (rmse_R3.error > 0.1 || rmse_I3.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 3 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 3 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 4
	Rmse rmse_R4,  rmse_I4;
	fp = fopen("out4.gold.dat","r");

	fft_stages(In_R4, In_I4, 4, Out_R4, Out_I4);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R4.add_value((float)Out_R4[i] - gold_R);
		rmse_I4.add_value((float)Out_I4[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 4--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R4.error, rmse_I4.error);
	printf("----------------------------------------------\n");

	if (rmse_R4.error > 0.1 || rmse_I4.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 4 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 4 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 5
	Rmse rmse_R5,  rmse_I5;
	fp = fopen("out5.gold.dat","r");

	fft_stages(In_R5, In_I5, 5, Out_R5, Out_I5);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R5.add_value((float)Out_R5[i] - gold_R);
		rmse_I5.add_value((float)Out_I5[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 5--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R5.error, rmse_I5.error);
	printf("----------------------------------------------\n");

	if (rmse_R5.error > 0.1 || rmse_I5.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 5 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 5 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 6
	Rmse rmse_R6,  rmse_I6;
	fp = fopen("out6.gold.dat","r");

	fft_stages(In_R6, In_I6, 6, Out_R6, Out_I6);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R6.add_value((float)Out_R6[i] - gold_R);
		rmse_I6.add_value((float)Out_I6[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 6--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R6.error, rmse_I6.error);
	printf("----------------------------------------------\n");

	if (rmse_R6.error > 0.1 || rmse_I6.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 6 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 6 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 7
	Rmse rmse_R7,  rmse_I7;
	fp = fopen("out7.gold.dat","r");

	fft_stages(In_R7, In_I7, 7, Out_R7, Out_I7);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R7.add_value((float)Out_R7[i] - gold_R);
		rmse_I7.add_value((float)Out_I7[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 7--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R7.error, rmse_I7.error);
	printf("----------------------------------------------\n");

	if (rmse_R7.error > 0.1 || rmse_I7.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 7 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 7 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 8
	Rmse rmse_R8,  rmse_I8;
	fp = fopen("out8.gold.dat","r");

	fft_stages(In_R8, In_I8, 8, Out_R8, Out_I8);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R8.add_value((float)Out_R8[i] - gold_R);
		rmse_I8.add_value((float)Out_I8[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 8--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R8.error, rmse_I8.error);
	printf("----------------------------------------------\n");

	if (rmse_R8.error > 0.1 || rmse_I8.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 8 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 8 PASS\n");
		fprintf(stdout, "*******************************************\n");
		//return 0;
	}

	//Stage 9
	Rmse rmse_R9,  rmse_I9;
	fp = fopen("out9.gold.dat","r");

	fft_stages(In_R9, In_I9, 9, Out_R9, Out_I9);

	for(int i=0; i<SIZE; i++)
	{
		fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
		rmse_R9.add_value((float)Out_R9[i] - gold_R);
		rmse_I9.add_value((float)Out_I9[i] - gold_I);
	}
	fclose(fp);

	// printing error results
	printf("-------------------Stage 9--------------------\n");
	printf("   RMSE(R)           RMSE(I)\n");
	printf("%0.15f %0.15f\n", rmse_R9.error, rmse_I9.error);
	printf("----------------------------------------------\n");

	if (rmse_R9.error > 0.1 || rmse_I9.error > 0.1 ) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 9 FAIL\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "Stage 9 PASS\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
	}
}
