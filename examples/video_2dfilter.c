#include "video_common.h"

rgb_pixel filter(rgb_pixel window[3][3]) {
	const char h[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
	int r = 0, b = 0, g = 0;
i_loop: for (int i = 0; i < 3; i++) {
	j_loop: for (int j = 0; j < 3; j++) {
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
	rgb_pixel window[3][3];
row_loop: for (int row = 0; row < MAX_HEIGHT; row++) {
	col_loop: for (int col = 0; col < MAX_WIDTH; col++) {
#pragma HLS pipeline
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					int wi = row + i - 1;
					int wj = col + j - 1;
					if (wi < 0 || wi >= MAX_HEIGHT || wj < 0 || wj >= MAX_WIDTH) {
						window[i][j].R = 0;
						window[i][j].G = 0;
						window[i][j].B = 0;
					} else
						window[i][j] = pixel_in[wi][wj];
				}
			}
			if (row == 0 || col == 0 || row == (MAX_HEIGHT - 1) || col == (MAX_WIDTH - 1)) {
				pixel_out[row][col].R = 0;
				pixel_out[row][col].G = 0;
				pixel_out[row][col].B = 0;
			} else
				pixel_out[row][col] = filter(window);
		}
	}
}

