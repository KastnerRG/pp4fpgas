/*
*/

#include<stdio.h>
#include <stdlib.h>
//#include<iostream>
#include <math.h>
//#include "dft.h"

#define SIZE 8
typedef int BaseType;

BaseType M[SIZE][SIZE];
BaseType V_In[SIZE];
BaseType V_Out[SIZE];

extern void matrix_vector(BaseType M[SIZE][SIZE], BaseType V_In[SIZE], BaseType V_Out[SIZE]);

int main()
{
	FILE *fp;
	printf("INPUTS\n");
	for(int i=0; i<SIZE; i++)
	{
		V_In[i] = i;
		for(int j=0;j<SIZE; j++)
		  M[i][j] = i+j;
	}
	
	//Perform DFT
	matrix_vector(M,V_In,V_Out);

	//Print output
	fp=fopen("matrix_vector_base.out.dat", "w");
	printf("Printing DFT Output\n");
	for(int i=0; i<SIZE; i++){
		printf("%4d\t%d\n",i,V_Out[i]);
		fprintf(fp, "%4d\t%d\n",i,V_Out[i]);
	}
	fclose(fp);

	//Check against golden output.
#ifdef BIT_ACCURATE
  printf ("Comparing against bit-accurate data \n");
  if (system("diff -w matrix_vector_base.out.dat out.gold.8.dat")) {
#else
  printf ("Comparing against output data \n");
  if (system("diff -w matrix_vector_base.out.dat out.gold.dat")) {
#endif
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
	fprintf(stdout, "*******************************************\n");
     return 1;
  } else {
	fprintf(stdout, "*******************************************\n");
	fprintf(stdout, "PASS: The output matches the golden output!\n");
	fprintf(stdout, "*******************************************\n");
     return 0;
  }

}
