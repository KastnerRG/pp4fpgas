#include "block_mm.h"
#include <stdlib.h>
using namespace std;

void matmatmul_sw(DTYPE A[SIZE][SIZE], DTYPE B[SIZE][SIZE],
      DTYPE out[SIZE][SIZE]){
 DTYPE sum = 0;
 for(int i = 0; i < SIZE; i++){
  for(int j = 0;j<SIZE; j++){
   sum = 0;
   for(int k = 0; k < SIZE; k++){
    sum = sum + A[i][k] * B[k][j];
   }
   out[i][j] = sum;
  }
 }
}

int main() {
 int fail = 0;
 hls::stream<blockvec> strm_matrix1("strm_matrix1");
 hls::stream<blockvec> strm_matrix2("strm_matrix2");
 blockvec strm_matrix1_element, strm_matrix2_element;
 blockmat block_out;
 DTYPE A[SIZE][SIZE], B[SIZE][SIZE];
 DTYPE matrix_swout[SIZE][SIZE], matrix_hwout[SIZE][SIZE];

 initmatrices: for(int i = 0; i < SIZE; i++){
  for(int j = 0; j < SIZE; j++){
   A[i][j] = rand() % 512;
   B[i][j] = rand() % 512;
   matrix_swout[i][j] = 0;
   matrix_hwout[i][j] = 0;
  }
 }

 //the remainder of this testbench is displayed in the next figure
