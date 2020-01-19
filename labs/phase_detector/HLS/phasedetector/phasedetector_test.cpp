/*
	Filename: phasedetector_test.cpp
		Written for CSE/WES 237C class at UCSD.
		Testbench file
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "phasedetector.h"

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


Rmse rmse_theta;
Rmse rmse_r;


int main ()
{
  float rms_error_r, rms_error_th;

  const int SAMPLES = 1024;

  int i;

  float signal_I[SAMPLES];
  float signal_Q[SAMPLES];

  float output_R[SAMPLES];
  float output_Theta[SAMPLES];

  float gold_R[SAMPLES];
  float gold_Theta[SAMPLES];


  FILE * finGold = fopen("out.gold.dat","r");
  for (i = 0; i < SAMPLES; i++)
  {
	  fscanf(finGold, "%f %f", &gold_R[i], &gold_Theta[i]);
	  //printf("%f, %f\n",gold_R[i], gold_Theta[i]);
  }
  fclose(finGold);

  FILE * finI = fopen("input_i.dat","r");
  FILE * finQ = fopen("input_q.dat","r");
  FILE * fp   = fopen("out.dat","w");

  for (i = 0; i < SAMPLES;i++)
  {
	  fscanf(finI,"%f",&signal_I[i]);
	  fscanf(finQ,"%f",&signal_Q[i]);
  }

  //Call the HLS block
  phasedetector(signal_I, signal_Q, output_R, output_Theta, SAMPLES);

  for (i = 0; i < SAMPLES;i++)
  {
	  // Accumulating error
	  rms_error_r  = rmse_r.add_value((float)output_R[i] - gold_R[i]);
	  rms_error_th = rmse_theta.add_value((float)output_Theta[i] - gold_Theta[i]);

	  fprintf(fp, "%f %f\n", (float)output_R[i], (float)output_Theta[i]);
	  //printf("%i, %f, %f, %f, %f,\n",i,signal_I[i], signal_Q[i], output_R[i], output_Theta[i]);
  }

  fclose(fp);
  fclose(finQ);
  fclose(finI);

  printf("----------------------------------------------\n");
  printf("   RMSE(R)           RMSE(Theta)\n");
  printf("%0.15f %0.15f\n", rmse_r.error, rmse_theta.error);
  printf("----------------------------------------------\n");

  float error_threshold = 0.001;

  int success = (rmse_r.error < error_threshold) && (rmse_theta.error < error_threshold);

  if (success) return 0;
  else return 1;
}

