
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"


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
    int index;
    DTYPE gold_R, gold_I;

    FILE * fp = fopen("out.gold.dat","r");

	//Generate input data
	for(int i=0; i<SIZE; i++)	{
		In_R[i] = i;
		In_I[i] = 0.0;
		Out_R[i]=i;
		Out_I[i]=1;
	}
	
	//Perform FFT
	fft(In_R, In_I, Out_R, Out_I);

    
    // comparing with golden output
    for(int i=0; i<SIZE; i++)
    {
        fscanf(fp, "%d %f %f", &index, &gold_R, &gold_I);
        rmse_R.add_value(Out_R[i] - gold_R);
        rmse_I.add_value(Out_I[i] - gold_I);
    }
    fclose(fp);

    // printing error results
    printf("----------------------------------------------\n");
    printf("   RMSE(R)           RMSE(I)\n");
    printf("%0.15f %0.15f\n", rmse_R.error, rmse_I.error);
    printf("----------------------------------------------\n");
    
    if (rmse_R.error > 1 || rmse_I.error > 1 ) {
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
