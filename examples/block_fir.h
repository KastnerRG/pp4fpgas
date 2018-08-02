
#define NUM_TAPS 16

void block_fir(int input[256], int output[256], int taps[NUM_TAPS],
               int delay_line[NUM_TAPS]);
