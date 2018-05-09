#include "huffman.h"
// Postcondition: out[x].frequency > 0
void filter(
            /* input  */ Symbol in[INPUT_SYMBOL_SIZE],
            /* output */ Symbol out[INPUT_SYMBOL_SIZE],
            /* output */ int *n) {
#pragma HLS INLINE off
    ap_uint<SYMBOL_BITS> j = 0;
    for(int i = 0; i < INPUT_SYMBOL_SIZE; i++) {
#pragma HLS pipeline II=1
        if(in[i].frequency != 0) {
            out[j].frequency = in[i].frequency;
            out[j].value = in[i].value;
            j++;
        }
    }
    *n = j;
}
