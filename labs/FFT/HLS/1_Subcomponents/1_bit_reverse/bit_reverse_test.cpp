/*
 * This is bit reverse part of FFT.
INPUT:
	In[]:

OUTPUT:
	Out[]:
*/

#include <stdio.h>
#include <stdlib.h>
#include "bit_reverse.h"

DTYPE In_R[SIZE], In_I[SIZE];

int main()
{
	FILE *fp;
	for(int i=0; i<SIZE; i++)
	{
		In_R[i] = i;
		In_I[i] = 0.0;

	}
	//Perform Bit Reverse
	bit_reverse(In_R, In_I);

	fp=fopen("out.dat", "w");
	printf("Printing bit reverse output\n");
	for(int i=0; i<SIZE; i++){
		printf("%d, %f, %f\n",i,In_R[i], In_I[i]);
		fprintf(fp, "%d, %f, %f\n",i,In_R[i], In_I[i]);
	}

	fclose(fp);

	//Check against golden output.
	printf ("Comparing against output data \n");
  if (system("diff -w out.dat out.gold.dat")) {
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
