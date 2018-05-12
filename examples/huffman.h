#include "ap_int.h"

// input number of symbols
const static int INPUT_SYMBOL_SIZE = 256;

// upper bound on codeword length during tree construction
const static int TREE_DEPTH = 64;

// maximum codeword tree length after rebalancing
const static int MAX_CODEWORD_LENGTH = 27;

// Should be log2(INPUT_SYMBOL_SIZE)
const static int SYMBOL_BITS = 10;

// Should be log2(TREE_DEPTH)
const static int TREE_DEPTH_BITS = 6;

// number of bits needed to record MAX_CODEWORD_LENGTH value
// Should be log2(MAX_CODEWORD_LENGTH)
const static int CODEWORD_LENGTH_BITS = 5;

// A marker for internal nodes
const static ap_uint<SYMBOL_BITS> INTERNAL_NODE = -1;

typedef ap_uint<MAX_CODEWORD_LENGTH> Codeword;
typedef ap_uint<MAX_CODEWORD_LENGTH + CODEWORD_LENGTH_BITS> PackedCodewordAndLength;
typedef ap_uint<CODEWORD_LENGTH_BITS> CodewordLength;
typedef ap_uint<32> Frequency;

struct Symbol {
	 ap_uint<SYMBOL_BITS> value;
	 ap_uint<32> frequency;
};

void huffman_encoding (
	Symbol in[INPUT_SYMBOL_SIZE],
	PackedCodewordAndLength encoding[INPUT_SYMBOL_SIZE],
	int *num_nonzero_symbols
);






void filter(Symbol in[INPUT_SYMBOL_SIZE],
            Symbol out[INPUT_SYMBOL_SIZE],
            int *num_symbols);
void sort(Symbol in[INPUT_SYMBOL_SIZE],
          int num_symbols,
          Symbol out[INPUT_SYMBOL_SIZE]);
void create_tree (
    Symbol in[INPUT_SYMBOL_SIZE],
    int num_symbols,
    ap_uint<SYMBOL_BITS> parent[INPUT_SYMBOL_SIZE-1],
    ap_uint<SYMBOL_BITS> left[INPUT_SYMBOL_SIZE-1],
    ap_uint<SYMBOL_BITS> right[INPUT_SYMBOL_SIZE-1]);

void compute_bit_length (
  ap_uint<SYMBOL_BITS> parent[INPUT_SYMBOL_SIZE-1],
  ap_uint<SYMBOL_BITS> left[INPUT_SYMBOL_SIZE-1],
  ap_uint<SYMBOL_BITS> right[INPUT_SYMBOL_SIZE-1],
  int num_symbols,
  ap_uint<SYMBOL_BITS> bit_length[TREE_DEPTH]);

void truncate_tree(
	ap_uint<SYMBOL_BITS> input_bit_length[TREE_DEPTH],
	ap_uint<SYMBOL_BITS> truncated_bit_length1[TREE_DEPTH],
	ap_uint<SYMBOL_BITS> truncated_bit_length2[TREE_DEPTH]);

void canonize_tree(
	Symbol sorted[INPUT_SYMBOL_SIZE],
	ap_uint<SYMBOL_BITS> num_symbols,
	ap_uint<SYMBOL_BITS> bit_length[TREE_DEPTH],
	CodewordLength symbol_bits[INPUT_SYMBOL_SIZE]);

void create_codeword(
  CodewordLength symbol_bits[INPUT_SYMBOL_SIZE],
  ap_uint<SYMBOL_BITS> bit_length[TREE_DEPTH],
  PackedCodewordAndLength encoding[INPUT_SYMBOL_SIZE]);


static unsigned int bit_reverse32(unsigned int input) {
	int i, rev = 0;
	for (i = 0; i < 32; i++) {
		rev = (rev << 1) | (input & 1);
		input = input >> 1;
	}
	return rev;
}
