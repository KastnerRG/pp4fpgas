#define SIZE 8
typedef int BaseType;

void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]) {
#pragma HLS array_partition variable=M dim=2 cyclic factor=2
#pragma HLS array_partition variable=V_In cyclic factor=2
	BaseType i, j;
data_loop:
	for (i = 0; i < SIZE; i++) {
		BaseType sum = 0;
	dot_product_loop:
		for (j = 0; j < SIZE; j+=2) {
#pragma HLS pipeline II=1
			sum += V_In[j] * M[i][j];
			sum += V_In[j+1] * M[i][j+1];
		}
		V_Out[i] = sum;
	}
}
