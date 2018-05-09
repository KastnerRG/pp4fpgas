#include "insertion_sort.h"
#include <iostream>
#include "stdio.h"
int main(){
	int fail = 0;
	DTYPE A[SIZE] = {1,6,3,7,2,5,3,0,9,10,11,12,13,14,15,8};

	insertion_sort(A);

    for(int i = 0; i < SIZE; i++)
        std::cout << A[i] << " ";
    std::cout << "\n";

    for(int i = 1; i < SIZE; i++) {
        if(A[i] < A[i-1]) {
            std::cout << i << " " << A[i-1] << ">" << A[i] <<
                "\n";
            fail = 1;
        }
    }

	if(fail == 1)
		printf("FAILED\n");
	else
		printf("PASS\n");

	return fail;
}
