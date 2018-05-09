#include "insertion_sort.h"
void insertion_sort(DTYPE A[SIZE]) {
 L1:
    for(i = 1; i < SIZE; i++) {
        DTYPE item = A[i];
        j = i;
        DTYPE t = A[j-1];
    L2:
        while(j > 0 && t > item) {
#pragma HLS pipeline II=1
            A[j] = t;
            t = A[j-2];
            j--;
        }
        A[j] = item;
    }
}
