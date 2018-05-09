void insertion_cell_sort(hls::stream<DTYPE> & in, hls::stream<DTYPE> & out)
{
	#pragma HLS DATAFLOW
	hls::stream<DTYPE> out0("out0_stream");
	hls::stream<DTYPE> out1("out1_stream");
	hls::stream<DTYPE> out2("out2_stream");
	hls::stream<DTYPE> out3("out3_stream");
	hls::stream<DTYPE> out4("out4_stream");
	hls::stream<DTYPE> out5("out5_stream");
	hls::stream<DTYPE> out6("out6_stream");

	// Function calls;
	cell0(in, out0);
	cell1(out0, out1);
	cell2(out1, out2);
	cell3(out2, out3);
	cell4(out3, out4);
	cell5(out4, out5);
	cell6(out5, out6);
	cell7(out6, out);
}
