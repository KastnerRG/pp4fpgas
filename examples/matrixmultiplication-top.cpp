/*
*/

#include<stdio.h>
#include <stdlib.h>
//#include<iostream>
#include <math.h>
#include "matrixmultiplication.h"

BaseType A[N][M];
BaseType B[M][P];
BaseType AB[N][P];

int main()
{
	FILE *fp;
	printf("INPUTS\n");
	for(int i=0; i<N; i++) {
		for(int j=0;j<M; j++) {
			A[i][j] = i+j;
		}
	}
	for(int i=0; i<M; i++) {
		for(int j=0;j<P; j++) {
			B[i][j] = i+j;
		}
	}
	matrixmul(A,B,AB);

	//Print output
	fp=fopen("matrixmultiplication.out.dat", "w");
	printf("Output:\n");
	for(int i=0; i<N; i++) {
		printf("%4d\t ", i);
		for(int j=0;j<P; j++) {
			printf("%d ",AB[i][j]);
			fprintf(fp, "%4d\t%4d\t%d\n",i,j,AB[i][j]);
		}
		printf("\n");
	}
	fclose(fp);

	//Check against golden output.
#ifdef BIT_ACCURATE
  printf ("Comparing against bit-accurate data \n");
  if (system("diff -w matrixmultiplication.out.dat matrixmultiplication.gold.8.dat")) {
#else
  printf ("Comparing against output data \n");
  if (system("diff -w matrixmultiplication.out.dat matrixmultiplication.gold.dat")) {
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
