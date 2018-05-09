#define SIZE 8
typedef int BaseType;

void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]) {
	BaseType i, j;
data_loop:
	for (i = 0; i < SIZE; i++) {
		BaseType sum = 0;
	dot_product_loop:
		for (j = 0; j < SIZE; j++) {
			sum += V_In[j] * M[i][j];
		}
		V_Out[i] = sum;
	}
}
