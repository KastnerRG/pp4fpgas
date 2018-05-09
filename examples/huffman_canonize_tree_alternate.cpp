int k = 0;
process_symbols:
for(length = TREE_DEPTH; length >= 0; length--) {
    count = codeword_length_histogram[length];
    for(i = 0; i < count; i++) {
#pragma HLS pipeline II=1
        symbol_bits[sorted[k++].value] = length;
    }
 }
