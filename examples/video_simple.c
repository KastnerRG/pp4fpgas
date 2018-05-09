#include "video_common.h"

unsigned char rescale(unsigned char val, unsigned char offset, unsigned char scale) {
	return ((val - offset) * scale) >> 4;
}

rgb_pixel rescale_pixel(rgb_pixel p, unsigned char offset, unsigned char scale) {
#pragma HLS pipeline
    p.R = rescale(p.R, offset, scale);
    p.G = rescale(p.G, offset, scale);
    p.B = rescale(p.B, offset, scale);
    return p;
}

void video_filter_rescale(rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
													rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH],
													unsigned char min, unsigned char max) {
#pragma HLS interface ap_hs port = pixel_out
#pragma HLS interface ap_hs port = pixel_in
row_loop:
	for (int row = 0; row < MAX_WIDTH; row++) {
	col_loop:
		for (int col = 0; col < MAX_HEIGHT; col++) {
#pragma HLS pipeline
			rgb_pixel p = pixel_in[row][col];
			p = rescale_pixel(p,min,max);
			pixel_out[row][col] = p;
		}
	}
}
