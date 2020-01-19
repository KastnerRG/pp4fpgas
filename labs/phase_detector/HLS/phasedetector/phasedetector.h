/*
	Filename: fir.h
		Header file
		FIR lab wirtten for 237C class at UCSD.

*/
#ifndef PHASE_DETECTOR_H_
#define PHASE_DETECTOR_H_


#include <ap_fixed.h>

const int N = 32;

#define NO_ITER 16

typedef int   coef_t;
typedef float data_t;
typedef float acc_t;

void phasedetector (
  data_t *I,
  data_t *Q,

  data_t *R,
  data_t *Theta,

  int length
  );

void cordiccart2pol(data_t x, data_t y, data_t * r, data_t * theta);

void fir (
  data_t I,
  data_t Q,

  data_t *X,
  data_t *Y
  );

#endif
