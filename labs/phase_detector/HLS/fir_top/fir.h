/*
	Filename: fir.h
		Header file
		FIR lab wirtten for 237C class at UCSD.

*/
#ifndef FIR_H_
#define FIR_H_

#include <ap_fixed.h>

const int N = 32;

typedef int	  coef_t;
typedef float data_t;
typedef float acc_t;

void fir (
  data_t I,
  data_t Q,

  data_t *X,
  data_t *Y
  );



#endif
