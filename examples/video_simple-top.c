#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "video_common.h"
#include "bitmap.h"

rgb_pixel in_pix[MAX_HEIGHT][MAX_WIDTH];
rgb_pixel out_pix[MAX_HEIGHT][MAX_WIDTH];
unsigned char R_in[MAX_HEIGHT][MAX_WIDTH];
unsigned char G_in[MAX_HEIGHT][MAX_WIDTH];
unsigned char B_in[MAX_HEIGHT][MAX_WIDTH];
unsigned char R_out[MAX_HEIGHT][MAX_WIDTH];
unsigned char G_out[MAX_HEIGHT][MAX_WIDTH];
unsigned char B_out[MAX_HEIGHT][MAX_WIDTH];

void video_filter_rescale(rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
                          rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH],
                          unsigned char min, unsigned char max);

int main(int argc, char *argv[]) {
	int x, y;
	int width, height;
	char tempbuf[2000];
	char tempbuf1[2000];

	if (argc != 3) {
		printf("usage : %s <inputFile> <outputFile>\n", argv[0]);
		exit(1);
	}

	// Fill a frame with data
	int read_tmp = ReadBMP(argv[1], MAX_HEIGHT, MAX_WIDTH, &R_in[0][0],
												 &G_in[0][0], &B_in[0][0]);
	if (read_tmp != 0) {
		printf("%s Loading image failed\n", tempbuf);
		exit(1);
	}

	// Copy Input Image to pixel data structure
	// Hardware accelerator works on video pixel streams
	for (x = 0; x < MAX_HEIGHT; x++) {
		for (y = 0; y < MAX_WIDTH; y++) {
			in_pix[x][y].R = R_in[x][y];
			in_pix[x][y].G = G_in[x][y];
			in_pix[x][y].B = B_in[x][y];
		}
	}

	// Hardware Function
	video_filter_rescale(in_pix, out_pix, 30, 18);

	// Copy Output video pixel stream to Output Image data structure
	for (x = 0; x < MAX_HEIGHT; x++) {
		for (y = 0; y < MAX_WIDTH; y++) {
			R_out[x][y] = out_pix[x][y].R;
			G_out[x][y] = out_pix[x][y].G;
			B_out[x][y] = out_pix[x][y].B;
		}
	}

	// Write the image back to disk
	int write_tmp = WriteBMP(argv[2], MAX_HEIGHT, MAX_WIDTH, &R_out[0][0],
													 &G_out[0][0], &B_out[0][0]);
	if (write_tmp != 0) {
		printf("WriteBMP %s failed\n", argv[2]);
		exit(1);
	}
}
