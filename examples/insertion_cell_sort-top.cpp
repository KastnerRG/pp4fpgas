#include "insertion_cell_sort.h"
#include <iostream>
#include <stdlib.h>

const static int DEBUG=1;
const static int MAX_NUMBER=1000;
int main () {
	int fail = 0;
	DTYPE input[SIZE];
	DTYPE cell_output[SIZE] = {0};
	hls::stream<DTYPE> in, out;

	//generate random data to sort
	if(DEBUG) std::cout << "Random Input Data\n";
	srand(20); //change me if you want different numbers
	for(int i = 0; i < SIZE; i++) {
		input[i] = rand() % MAX_NUMBER + 1;
		if(DEBUG) std::cout << input[i] << "\t";
	}

	//process the data through the insertion_cell_sort function
	for(int i = 0; i < SIZE*2; i++) {
		if(i < SIZE) {
			//feed in the SIZE elements to be sorted
			in.write(input[i]);
			insertion_cell_sort(in, out);
			cell_output[i] = out.read();
		} else {
			//then send in dummy data to flush pipeline
			in.write(MAX_NUMBER);
			insertion_cell_sort(in, out);
			cell_output[i-SIZE] = out.read();
		}
	}

	//sort the data using the insertion_sort function
	insertion_sort(input);

	//compare the results of insertion_sort to insertion_cell_sort; fail if they differ
	if(DEBUG) std::cout << "\nSorted Output\n";
	for(int i = 0; i < SIZE; i++) {
		if(DEBUG) std::cout << cell_output[i] << "\t";
	}
	for(int i = 0; i < SIZE; i++) {
		if(input[i] != cell_output[i]) {
			fail = 1;
			std::cout << "golden=" << input[i] << "hw=" << cell_output[i] << "\n";
		}
	}

	if(fail == 0) std::cout << "PASS\n";
	else std::cout << "FAIL\n";
	return fail;
}
