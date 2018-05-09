// The beginning of the testbench is shown in the previous figure
int main() {
  int row, col, it = 0;
  for(int it1 = 0; it1 < SIZE; it1 = it1 + BLOCK_SIZE) {
    for(int it2 = 0; it2 < SIZE; it2 = it2 + BLOCK_SIZE) {
      row = it1; //row + BLOCK_SIZE * factor_row;
      col = it2; //col + BLOCK_SIZE * factor_col;
      
      for(int k = 0; k < SIZE; k++) {
        for(int i = 0; i < BLOCK_SIZE; i++) {
          if(it % (SIZE/BLOCK_SIZE) == 0) strm_matrix1_element.a[i] = A[row+i][k];
          strm_matrix2_element.a[i] = B[k][col+i];
        }
        if(it % (SIZE/BLOCK_SIZE) == 0) strm_matrix1.write(strm_matrix1_element);
        strm_matrix2.write(strm_matrix2_element);
      }
      blockmatmul(strm_matrix1, strm_matrix2, block_out, it);
      
      for(int i = 0; i < BLOCK_SIZE; i++)
        for(int j = 0; j < BLOCK_SIZE; j++)
          matrix_hwout[row+i][col+j] = block_out.out[i][j];
      it = it + 1;
    }
  }
  
  matmatmul_sw(A, B, matrix_swout);
  
  for(int i = 0; i<SIZE; i++)
    for(int j = 0; j<SIZE; j++)
      if(matrix_swout[i][j] != matrix_hwout[i][j]) { fail=1; }
  
  if(fail==1) cout << "failed" << endl;
  else cout << "passed" << endl;
  
  return 0;
}
