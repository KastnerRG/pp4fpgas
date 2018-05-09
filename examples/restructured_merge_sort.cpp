#include "MergeSort.h"

//divide i into two streams. Every two elements in each of the streams is sorted.
void split(DTYPE i[SIZE], hls::stream<DTYPE>& out1, hls::stream<DTYPE>& out2)
{
	DTYPE a, b, c, d;

	//grab four elements at a time. Sort two of them into out1. Sort the other two into out2
	for(int j = 0; j < SIZE; j += 4)
	{
		#pragma HLS UNROLL factor=2
		a = i[j+0];
		b = i[j+1];
		c = i[j+2];
		d = i[j+3];

		//talk about how ? synthesizes to a mux
		//sort a and b into out1
	    out1.write(a < b ? a : b); //write min(a,b) to out1
	    out1.write(a > b ? a : b); //write max(a,b) to out1

	    //sort c and d into out2
	    out2.write(c < d ? c : d); //write min(c,d) to out2
	    out2.write(c > d ? c : d); //write max(c,d) to out2
	}

	//the last data on both streams is a '0'. Why? Debugging?
	out1.write((DTYPE) 0);
	out2.write((DTYPE) 0);
}


//two input streams; two output streams.
//sets indicates the number of consecutive elements in each stream that will be in sorted order after function completes
void subset_merge(hls::stream<DTYPE>& in1, hls::stream<DTYPE>& in2, hls::stream<DTYPE>& out1, hls::stream<DTYPE>& out2, const int sets){
    #pragma HLS function_instantiate variable=sets //each instance of this function with a different sets value is independently optimized.
	DTYPE a,b;
	INDEX_TYPE subIndex1 = 1, subIndex2 = 1;
    in1.read(a);
    in2.read(b);
	for(int j = 0; j < HALF_SIZE; j += sets) {

		//this first for loop always writes to out1
		for(int i = 0; i < sets; i++){
		#ifdef pipeline
			#pragma HLS PIPELINE II=1
		#endif
			//special case: we have read all the data from in1. write/read from in2
			if(subIndex1 == j + (sets >> 1) + 1)
			{
				out1.write(b);
				in2.read(b);
				subIndex2++;

			}
			//special case: we have read all the data from in2. write/read from in1
			else if (subIndex2 == j + (sets >> 1) + 1)
			{
				out1.write(a);
				in1.read(a);
				subIndex1++;
			}
			else if (a < b)
			{
				out1.write(a);
				in1.read(a);
				subIndex1++;
			}
			else
			{
				out1.write(b);
				in2.read(b);
				subIndex2++;
			}
		}
		//this second for loop always writes to out2
		for(int i = 0; i < sets; i++)
		{
			#ifdef pipeline
			#pragma HLS PIPELINE II=1
			#endif

			//special case: we have already processed all the elements from in1. Write/Read from in2
			if(subIndex1 == j + sets + 1)
			{
				out2.write(b);
				in2.read(b);
				subIndex2++;
			}
			//special case: we have already processed all the elements from in2. Write/Read from in1
			else if (subIndex2 == j + sets + 1)
			{
				out2.write(a);
				in1.read(a);
				subIndex1++;
			}
			else if (a < b)
			{
				out2.write(a);
				in1.read(a);
				subIndex1++;
			}
			else
			{
				out2.write(b);
				in2.read(b);
				subIndex2++;
			}
		}
	}
	out1.write((DTYPE) 0);
	out2.write((DTYPE) 0);
}

void merge(hls::stream<DTYPE>& in1, hls::stream<DTYPE>& in2, DTYPE out[SIZE])
{
	DTYPE a, b;
	INDEX_TYPE subIndex1 = 1, subIndex2 = 1;
	in1.read(a);
	in2.read(b);

	//this is the final merge
	//the elements in in1 and in2 are in sorted order.
	//go through each list and put the smallest into the final output array out
	for(int i = 0; i < SIZE; i++)
	{
		#ifdef pipeline
		#pragma HLS PIPELINE II=1
		#endif

		//special case: we have gone through all the elements in in1
		//write the element from in2, and grab next element from in2
		if(subIndex1 == HALF_SIZE + 1)
		{
			out[i] = b;
			in2.read(b);
			subIndex2++;
		}
		//special case: we have gone through all the elements in in2
		//write the element from in1, and grab next element from in1
		else if (subIndex2 == HALF_SIZE + 1)
		{
			out[i] = a;
			in1.read(a);
			subIndex1++;
		}
		//write a to output array if it is smaller of two elements.
		//get the next element from in1
		else if (a < b)
		{
			out[i] = a;
			in1.read(a);
			subIndex1++;
		}
		//b is smaller than (or equal to) a.
		//write that to the output array and get next element from in2
		else
		{
			out[i] = b;
			in2.read(b);
			subIndex2++;
		}
	}
}

void merge_sort(DTYPE IN[SIZE], DTYPE OUT[SIZE])
{
	#pragma HLS INTERFACE axis port=IN
	#pragma HLS INTERFACE axis port=OUT
	#pragma HLS DATAFLOW

	hls::stream<DTYPE> temp1a, temp1b, temp2a, temp2b, temp3a, temp3b, temp4a, temp4b;
	hls::stream<DTYPE> temp5a, temp5b,  temp6a, temp6b, temp7a, temp7b;

	//how are the depth values calculated?
	#pragma HLS stream depth=20 variable=temp1a
	#pragma HLS stream depth=20 variable=temp1b
	#pragma HLS stream depth=22 variable=temp2a
	#pragma HLS stream depth=22 variable=temp2b
	#pragma HLS stream depth=26 variable=temp3a
	#pragma HLS stream depth=26 variable=temp3b
	#pragma HLS stream depth=34 variable=temp4a
	#pragma HLS stream depth=34 variable=temp4b
	#pragma HLS stream depth=50 variable=temp5a
	#pragma HLS stream depth=50 variable=temp5b
	#pragma HLS stream depth=82 variable=temp6a
	#pragma HLS stream depth=82 variable=temp6b
	#pragma HLS stream depth=146 variable=temp7a
	#pragma HLS stream depth=146 variable=temp7b

	split(IN, temp1a, temp1b);
	subset_merge(temp1a, temp1b, temp2a, temp2b, 4);
	subset_merge(temp2a, temp2b, temp3a, temp3b, 8);
	subset_merge(temp3a, temp3b, temp4a, temp4b, 16);
	subset_merge(temp4a, temp4b, temp5a, temp5b, 32);
	subset_merge(temp5a, temp5b, temp6a, temp6b, 64);
	subset_merge(temp6a, temp6b, temp7a, temp7b, 128);
	merge(temp7a, temp7b, OUT);
}
