#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <tuple>

void file_to_array(const char *filename, ap_uint<16> *&array, int array_length) {
    printf("Start reading file [%s]\n", filename);
    FILE *file = fopen(filename, "r");
    if(file == NULL) {
        printf("Cannot find the input file\n");
        exit(1);
    }

    int     file_value = 0;
    int     count = 0;
    array = (ap_uint<16> *) malloc(array_length*sizeof(ap_uint<16>));

    while(1) {
        int eof_check = fscanf(file, "%x", &file_value);
        if(eof_check == EOF) break;
        else {
            array[count++] = (ap_uint<16>) file_value ;
        }
    }
    fclose(file);

    if(count != array_length) exit(1);
}

int main() {
    printf("Starting canonical Huffman encoding testbench\n");
    FILE *output_file;
    int return_val = 0;
    ap_uint<16> *frequencies = NULL;
    file_to_array("huffman.random256.txt", frequencies, INPUT_SYMBOL_SIZE);

    Symbol in[INPUT_SYMBOL_SIZE];
    for (int i = 0 ; i <  INPUT_SYMBOL_SIZE; i++) {
        in[i].frequency = frequencies[i];
        in[i].value = i;
    }

    int num_nonzero_symbols;
    PackedCodewordAndLength encoding[INPUT_SYMBOL_SIZE];
    huffman_encoding(in, encoding, &num_nonzero_symbols);

    std::set<std::pair<Codeword, CodewordLength> > unique_set;
    for (int i = 0 ; i < INPUT_SYMBOL_SIZE; i++) {
        // Get the lowest CODEWORD_LENGTH_BITS bits.
        CodewordLength length = encoding[i] & 0x1F;
        Codeword cw = encoding[i] >> CODEWORD_LENGTH_BITS;
        if(length > 0) {
            std::cout << i << ":";
            for(int j = 0; j < length; j++) {
                std::cout << (cw[j]?'1':'0');
            }
            std::cout << " " << length << "\n";
        }
        cw = cw.reverse() >> (MAX_CODEWORD_LENGTH-length);
        assert(unique_set.count(std::make_pair(cw, length)) == 0);
        unique_set.insert(std::make_pair(cw, length));
    }
    // Check that we have a prefix code.
    for (int i = 0 ; i < INPUT_SYMBOL_SIZE; i++) {
        // Get the lowest CODEWORD_LENGTH_BITS bits.
        CodewordLength length = encoding[i] & 0x1F;
        Codeword cw = encoding[i] >> CODEWORD_LENGTH_BITS;

        cw = cw.reverse() >> (MAX_CODEWORD_LENGTH-length);
        for(int j = 1; j < length; j++) {
            std::set<std::pair<Codeword, CodewordLength> >::iterator it =
                unique_set.find(std::make_pair(cw >> j, length-j));
            if(it != unique_set.end()) {
                CodewordLength length2;
                Codeword cw2;
                std::tie(cw2, length2) = *it;
                std::cout << "Checking " << (cw >> j).to_string(2) << " " << (length-j) << "\n";
                std::cout << "with " << (cw2).to_string(2) << " " << length2 << "\n";
                std::cout << "FAIL: not a prefix code!\n";
                return_val = 1;
            }
        }
    }

    output_file = fopen("huffman.random256.out", "w");
    for(int i = 0; i < INPUT_SYMBOL_SIZE; i++)
        fprintf(output_file, "%d, %x\n", i, (unsigned int) encoding[i]);
    fclose(output_file);

    printf ("\n***************Comparing against output data*************** \n\n");
    if (system("diff huffman.random256.out huffman.random256.golden")) {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
        fprintf(stdout, "*******************************************\n");
        return_val = 1;
    } else {
        fprintf(stdout, "*******************************************\n");
        fprintf(stdout, " PASS: The output matches the golden output\n");
        fprintf(stdout, "*******************************************\n");
        return_val = 0;
    }

    printf("Ending canonical Huffman encoding testbench\n");
    return return_val;
}
