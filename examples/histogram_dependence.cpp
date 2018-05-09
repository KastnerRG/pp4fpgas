#include <assert.h>
#include "histogram.h"

// Precondition: hist[] is initialized with zeros.
// Precondition: for all x, in[x] != in[x+1]
void histogram(int in[INPUT_SIZE], int hist[VALUE_SIZE]) {
#pragma HLS DEPENDENCE variable=hist inter RAW distance=2
    int val;
    int old = -1;
    for(int i = 0; i < INPUT_SIZE; i++) {
#pragma HLS PIPELINE
        val = in[i];
        assert(old != val);
        hist[val] = hist[val] + 1;
        old = val;
    }
}
