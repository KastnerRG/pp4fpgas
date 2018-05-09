// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
THETA_TYPE cordic_phase[NUM_ITERATIONS] = {45, 26.565, 14.036, 7.125,
                                           3.576, 1.790, 0.895, ...};

void cordic(THETA_TYPE theta, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{
  // Set the initial vector that we will rotate
  // current_cos = I; current_sin = Q
  COS_SIN_TYPE current_cos = 0.60735;
  COS_SIN_TYPE current_sin = 0.0;

  // Factor is the 2^(-L) value
  COS_SIN_TYPE factor = 1.0;

  // This loop iteratively rotates the initial vector to find the
  // sine and cosine values corresponding to the input theta angle
  for (int j = 0; j < NUM_ITERATIONS; j++) {
    // Determine if we are rotating by a positive or negative angle
    int sigma = (theta < 0) ? -1 : 1;

    // Save the current_cos, so that it can be used in the sine calculation
    COS_SIN_TYPE temp_cos = current_cos;

    // Perform the rotation
    current_cos = current_cos - current_sin * sigma * factor;
    current_sin = temp_cos * sigma * factor + current_sin;

    // Determine the new theta
    theta = theta - sigma * cordic_phase[j];

    // Calculate next 2^(-L) value
    factor = factor >> 1;
  }

  // Set the final sine and cosine values
  s = current_sin;  c = current_cos;
}
