#define SIZE 8
typedef int BaseType;

void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]) {
	BaseType i, j;
data_loop:
	for (i = 0; i < SIZE; i++) {
		BaseType sum = 0;
		V_Out[i] = V_In[0] * M[i][0] + V_In[1] * M[i][1] + V_In[2] * M[i][2] +
							 V_In[3] * M[i][3] + V_In[4] * M[i][4] + V_In[5] * M[i][5] +
							 V_In[6] * M[i][6] + V_In[7] * M[i][7];
	}
}
