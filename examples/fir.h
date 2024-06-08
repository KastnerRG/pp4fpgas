#ifndef FIR_H
#define FIR_H

#define NUM_TAPS 16

void fir(int input, int *output, int taps[NUM_TAPS]);

#endif // FIR_H