#include "video_common.h"

rgb_pixel filter(rgb_pixel window[3][3]) {
	const char h[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	int r = 0, b = 0, g = 0;
 i_loop:
	for (int i = 0; i < 3; i++) {
	j_loop:
		for (int j = 0; j < 3; j++) {
			r += window[i][j].R * h[i][j];
			g += window[i][j].G * h[i][j];
			b += window[i][j].B * h[i][j];
		}
	}
	rgb_pixel output;
	output.R = r / 16;
	output.G = g / 16;
	output.B = b / 16;
	return output;
}

void video_2dfilter_linebuffer_extended(
										rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
										rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH]) {
#pragma HLS interface ap_hs port=pixel_out
#pragma HLS interface ap_hs port=pixel_in
	rgb_pixel window[3][3];
	rgb_pixel line_buffer[2][MAX_WIDTH];
#pragma HLS array_partition variable=line_buffer complete dim=1
row_loop: for(int row = 0; row < MAX_HEIGHT+1; row++) {
	col_loop: for(int col = 0; col < MAX_WIDTH+1; col++) {
#pragma HLS pipeline II=1
			rgb_pixel pixel;
			if(row < MAX_HEIGHT && col < MAX_WIDTH) {
				pixel = pixel_in[row][col];
			}

			for(int i = 0; i < 3; i++) {
				window[i][0] = window[i][1];
				window[i][1] = window[i][2];
			}

			if(col < MAX_WIDTH) {
				window[0][2] = (line_buffer[0][col]);
				window[1][2] = (line_buffer[0][col] = line_buffer[1][col]);
				window[2][2] = (line_buffer[1][col] = pixel);
			}
			if(row >= 1 && col >= 1) {
				int outrow = row-1;
				int outcol = col-1;
				if(outrow == 0 || outcol == 0 ||
				   outrow == (MAX_HEIGHT-1) || outcol == (MAX_WIDTH-1)) {
					pixel_out[outrow][outcol].R = 0;
					pixel_out[outrow][outcol].G = 0;
					pixel_out[outrow][outcol].B = 0;
				} else {
					pixel_out[outrow][outcol] = filter(window);
				}
			}
		}
	}
}
