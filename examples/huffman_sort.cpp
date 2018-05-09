#include "huffman.h"
#include "assert.h"
const unsigned int RADIX = 16;
const unsigned int BITS_PER_LOOP = 4; // should be log2(RADIX)
typedef ap_uint<BITS_PER_LOOP> Digit;

void sort(
    /* input */ Symbol in[INPUT_SYMBOL_SIZE],
    /* input */ int num_symbols,
    /* output */ Symbol out[INPUT_SYMBOL_SIZE]) {
    Symbol previous_sorting[INPUT_SYMBOL_SIZE], sorting[INPUT_SYMBOL_SIZE];
    ap_uint<SYMBOL_BITS> digit_histogram[RADIX], digit_location[RADIX];
#pragma HLS ARRAY_PARTITION variable=digit_location complete dim=1
#pragma HLS ARRAY_PARTITION variable=digit_histogram complete dim=1
    Digit current_digit[INPUT_SYMBOL_SIZE];

    assert(num_symbols >= 0);
    assert(num_symbols <= INPUT_SYMBOL_SIZE);
 copy_in_to_sorting:
    for(int j = 0; j < num_symbols; j++) {
#pragma HLS PIPELINE II=1
        sorting[j] = in[j];
    }

 radix_sort:
    for(int shift = 0; shift < 32; shift += BITS_PER_LOOP) {
    init_histogram:
        for(int i = 0; i < RADIX; i++) {
#pragma HLS pipeline II=1
            digit_histogram[i] = 0;
        }

    compute_histogram:
        for(int j = 0; j < num_symbols; j++) {
#pragma HLS PIPELINE II=1
            Digit digit = (sorting[j].frequency >> shift) & (RADIX - 1); // Extrract a digit
            current_digit[j] = digit;  // Store the current digit for each symbol
            digit_histogram[digit]++;
            previous_sorting[j] = sorting[j]; // Save the current sorted order of symbols
        }

        digit_location[0] = 0;
    find_digit_location:
        for(int i = 1; i < RADIX; i++)
#pragma HLS PIPELINE II=1
            digit_location[i] = digit_location[i-1] + digit_histogram[i-1];

    re_sort:
        for(int j = 0; j < num_symbols; j++) {
#pragma HLS PIPELINE II=1
            Digit digit = current_digit[j];
            sorting[digit_location[digit]] = previous_sorting[j]; // Move symbol to new sorted location
            out[digit_location[digit]] = previous_sorting[j]; // Also copy to output
            digit_location[digit]++; // Update digit_location
        }
    }
}
