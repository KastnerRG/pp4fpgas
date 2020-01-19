#define TEST_BENCH

#include "cordiccart2pol.h"

#include <math.h>
#include <stdio.h>
#include <ap_fixed.h>

/// Struct to calculate the error
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

int main()
{

	// This part creates the LUTs
	//
	float step = 0.5/MAN_BITS;
	int num_steps = (int) 2/step; // x and y are normalized and are between -1 and 1
	
	/* This part fills the LUTs completely*/
/*
	for(int i=0; i<LUT_SIZE; i++){
		ap_uint<2*(I+MAN_BITS)> index = i;
		ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_x;
		ap_fixed<W, I, AP_RND, AP_WRAP, 1> fixed_y;

		for(int j = 0; j < I+MAN_BITS; j++)
			{
				fixed_x[W-1-j] = index[2*(I+MAN_BITS)-1-j];
				fixed_y[W-1-j] = index[(I+MAN_BITS)-1-j];
			}

		float _x = fixed_x;
		float _y = fixed_y;

		if((_x == 0) & (_y == 0)){
			my_LUT_th[index] = 0;
			my_LUT_r[index]  = 0;
		}
		else{
			my_LUT_th[index] = atan2f(_y, _x);
			my_LUT_r[index]  = sqrtf((_y*_y)+(_x*_x));
		}
	}
*/
	/* This part fills the LUTs partially*/

	data_t _x;
	data_t _y;

	for(int i = 0; i < num_steps+1; i++)
	{
		for(int j = 0; j < num_steps+1; j++)
		{
			_x = -1 + i*step;
			_y = -1 + j*step;

			ap_fixed<W, I, AP_RND_ZERO, AP_WRAP, 1> fixed_x = _x;
			ap_fixed<W, I, AP_RND_ZERO, AP_WRAP, 1> fixed_y = _y;

			ap_uint<2*(I+MAN_BITS)> index;

			for(int i = 0; i < I+MAN_BITS; i++)
			{
				index[2*(I+MAN_BITS)-1-i] = fixed_x[W-1-i];
				index[(I+MAN_BITS)-1-i]   = fixed_y[W-1-i];
			}

			if((_x == 0) & (_y == 0)){
				my_LUT_th[index] = 0;
				my_LUT_r[index]  = 0;
			}
			else{
				my_LUT_th[index] = atan2f(_y, _x);
				my_LUT_r[index]  = sqrtf((_y*_y)+(_x*_x));
			}
		}
	}

	// This part test your code against the ground truth
	//
	data_t x;
	data_t y;
	data_t r;
	data_t theta;

	//step += ERROR; // introduce small error to avoid testing the exact numbers from the LUT

	for(int i = 0; i < num_steps+1; i++)
	{
		for(int j = 0; j < num_steps+1; j++)
		{
			x = -1 + i*step + ERROR;
			y = -1 + j*step + ERROR;

			// Run the Cordic code
			cordiccart2pol(x, y, &r, &theta);
			float golden_r, golden_th;

			if((x == 0) & (y == 0)){
				golden_r  = 0;
				golden_th = 0;
			}
			else{
				golden_r  = sqrtf((y*y) + (x*x));
				golden_th = atan2f(y, x);
			}

			printf("input: x=%.4f, y=%.4f\n"
					"true results: R=%.4f, Theta=%.4f\n"
					"your results: R=%.4f, Theta=%.4f\n\n",
					(float)x, (float)y,
					golden_r, golden_th,
					(float)r, (float)theta);

			// Calculate error from ground truth
			rmse_theta.add_value((float)theta - golden_th);
			rmse_r.add_value((float)r - golden_r);
		}
	}


	printf("   RMSE(R)           RMSE(Theta)\n");
	printf("%0.15f %0.15f\n", rmse_r.error, rmse_theta.error);

	float error_threshold = 0.01;

    int success = (rmse_r.error < error_threshold) && (rmse_theta.error < error_threshold);

    if (success) return 0;
    else return 1;
}
