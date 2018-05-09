#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "video_common.h"
#include "bitmap.h"

rgb_pixel in_pix[MAX_HEIGHT][MAX_WIDTH];
rgb_pixel out_pix[MAX_HEIGHT][MAX_WIDTH];
unsigned char R_in[MAX_HEIGHT*MAX_WIDTH];
unsigned char G_in[MAX_HEIGHT*MAX_WIDTH];
unsigned char B_in[MAX_HEIGHT*MAX_WIDTH];
unsigned char R_out[MAX_HEIGHT*MAX_WIDTH];
unsigned char G_out[MAX_HEIGHT*MAX_WIDTH];
unsigned char B_out[MAX_HEIGHT*MAX_WIDTH];

void video_2dfilter_linebuffer_extended_constant(rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
                                rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH]);

int main(int argc, char *argv[]) {
	int x, y;
	int width, height;
	char tempbuf[2000];
	char tempbuf1[2000];

	if (argc != 3) {
		printf("usage : %s <inputFile> <outputFile>\n", argv[0]);
		exit(1);
	}

    ReadBMPSize(argv[1], &height, &width);
    printf("height = %d, width = %d\n", height, width);
    assert(height <= MAX_HEIGHT);
    assert(width <= MAX_WIDTH);
    
	// Fill a frame with data
	int read_tmp = ReadBMP(argv[1], height, width,
                           R_in, G_in, B_in);
	if (read_tmp != 0) {
		printf("%s Loading image failed\n", tempbuf);
		exit(1);
	}

	// Copy Input Image to pixel data structure
	// Hardware accelerator works on video pixel streams
	for (x = 0; x < height; x++) {
		for (y = 0; y < width; y++) {
			in_pix[x][y].R = R_in[x*width+y];
			in_pix[x][y].G = G_in[x*width+y];
			in_pix[x][y].B = B_in[x*width+y];
		}
	}

	// Hardware Function
	video_2dfilter_linebuffer_extended_constant(in_pix, out_pix);

	// Copy Output video pixel stream to Output Image data structure
	for (x = 0; x < height; x++) {
		for (y = 0; y < width; y++) {
			R_out[x*width+y] = out_pix[x][y].R;
			G_out[x*width+y] = out_pix[x][y].G;
			B_out[x*width+y] = out_pix[x][y].B;
		}
	}

	// Write the image back to disk
	int write_tmp = WriteBMP(argv[2], height, width,
                             R_out, G_out, B_out);
	if (write_tmp != 0) {
		printf("WriteBMP %s failed\n", argv[2]);
		exit(1);
	}
}
