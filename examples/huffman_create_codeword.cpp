#include "huffman.h"
#include "assert.h"
#include <iostream>
void create_codeword(
  /* input */ CodewordLength symbol_bits[INPUT_SYMBOL_SIZE],
  /* input */ ap_uint<SYMBOL_BITS> codeword_length_histogram[TREE_DEPTH],
  /* output */ PackedCodewordAndLength encoding[INPUT_SYMBOL_SIZE]
) {
    Codeword first_codeword[MAX_CODEWORD_LENGTH];

    // Computes the initial codeword value for a symbol with bit length i
    first_codeword[0] = 0;
 first_codewords:
    for(int i = 1; i < MAX_CODEWORD_LENGTH; i++) {
#pragma HLS PIPELINE II=1
        first_codeword[i] = (first_codeword[i-1] + codeword_length_histogram[i-1]) << 1;
        Codeword c = first_codeword[i];
        //        std::cout << c.to_string(2) << " with length " << i << "\n";
    }

 assign_codewords:
  for (int i = 0; i < INPUT_SYMBOL_SIZE; ++i) {
#pragma HLS PIPELINE II=5
      CodewordLength length = symbol_bits[i];
      //if symbol has 0 bits, it doesn't need to be encoded
  make_codeword:
      if(length != 0) {
          //          std::cout << first_codeword[length].to_string(2) << "\n";
          Codeword out_reversed = first_codeword[length];
          out_reversed.reverse();
          out_reversed = out_reversed >> (MAX_CODEWORD_LENGTH - length);
          // std::cout << out_reversed.to_string(2) << "\n";
          encoding[i] = (out_reversed << CODEWORD_LENGTH_BITS) + length;
          first_codeword[length]++;
      } else {
          encoding[i] = 0;
      }
  }
}
