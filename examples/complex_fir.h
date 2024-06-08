#ifndef COMPLEX_FIR_H
#define COMPLEX_FIR_H

typedef int data_t;
typedef int coef_t;

#define NUM_TAPS 16

extern "C" {
    #include "fir.h"
}

// Declaration of the complexFIR function
void complexFIR(data_t Iin, data_t Qin, data_t *Iout, data_t *Qout, coef_t Itaps[NUM_TAPS], coef_t Qtaps[NUM_TAPS]);

#endif // COMPLEX_FIR_H