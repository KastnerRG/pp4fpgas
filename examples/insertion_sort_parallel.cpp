#include "insertion_sort_parallel.h"
#include "assert.h"
void insertion_sort_parallel(DTYPE A[SIZE], DTYPE B[SIZE]) {
#pragma HLS array_partition variable=B complete
 L1:
    for(int i = 0; i < SIZE; i++) {
#pragma HLS pipeline II=1
        DTYPE item = A[i];
    L2:
        for(int j = SIZE-1; j >= 0; j--) {
            DTYPE t;
            if(j > i) {
                t = B[j];
            } else if(j > 0 && B[j-1] > item) {
                t = B[j-1];
            } else {
                t = item;
                if (j > 0)
                    item = B[j-1];
            }
            B[j] = t;
        }
    }
}
