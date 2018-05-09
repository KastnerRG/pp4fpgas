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

void video_2dfilter(rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
					rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH]) {
#pragma HLS interface ap_hs port = pixel_out
#pragma HLS interface ap_hs port = pixel_in
	rgb_pixel window[3][3];
 row_loop: for (int row = 0; row < MAX_HEIGHT; row++) {
	col_loop: for (int col = 0; col < MAX_WIDTH; col++) {
#pragma HLS pipeline
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int wi = row + i - 1;
					int wj = col + j - 1;
#define CONSTANT_EXTEND
#ifdef ZERO_EXTEND
					rgb_pixel zero = {};
					if (wi < 0) window[i][j] = zero;
					else if (wi >= MAX_HEIGHT) window[i][j] = zero;
					else if (wj < 0) window[i][j] = zero;
					else if (wj >= MAX_WIDTH) window[i][j] = zero;
					else
						window[i][j] = pixel_in[wi][wj];
#endif
#ifdef CONSTANT_EXTEND
					if (wi < 0) wi = 0;
					if (wi >= MAX_HEIGHT) wi = MAX_HEIGHT-1;
					if (wj < 0) wj = 0;
					if (wj >= MAX_WIDTH) wj = MAX_WIDTH-1;

					window[i][j] = pixel_in[wi][wj];
#endif
#ifdef REFLECT_EXTEND
					if (wi < 0) wi = -wi;
					if (wi >= MAX_HEIGHT) wi = MAX_HEIGHT-1-(wi-(MAX_HEIGHT-1));
					if (wj < 0) wj = -wj;
					if (wj >= MAX_WIDTH) wj = MAX_WIDTH-1-(wj-(MAX_WIDTH-1));

					window[i][j] = pixel_in[wi][wj];
#endif
				}
			}
			if(row >= MAX_HEIGHT-2 && col >= MAX_WIDTH-2) {
				printf("%d %d\n", row, col);
				printf("%x %x %x\n", window[0][0], window[0][1], window[0][2]);
				printf("%x %x %x\n", window[1][0], window[1][1], window[1][2]);
				printf("%x %x %x\n", window[2][0], window[2][1], window[2][2]);
			}

			pixel_out[row][col] = filter(window);
		}
	}
}

