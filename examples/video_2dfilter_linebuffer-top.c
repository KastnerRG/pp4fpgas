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

// Golden Reference filtered image
rgb_pixel ref_pix[MAX_HEIGHT][MAX_WIDTH];
unsigned char R_ref[MAX_HEIGHT*MAX_WIDTH];
unsigned char G_ref[MAX_HEIGHT*MAX_WIDTH];
unsigned char B_ref[MAX_HEIGHT*MAX_WIDTH];

void video_2dfilter_linebuffer(rgb_pixel pixel_in[MAX_HEIGHT][MAX_WIDTH],
                                rgb_pixel pixel_out[MAX_HEIGHT][MAX_WIDTH]);

int main(int argc, char *argv[]) {
	int x, y;
	int width, height;
	int width_ref, height_ref;
	char tempbuf[2000];
	char tempbuf1[2000];

	if (argc != 4) {
		printf("usage : %s <inputFile> <inputFilteredGoldenReferenceFile> <outputFile>\n", argv[0]);
		exit(1);
	}

	//
	// Input File 
	//

	printf("Input File: %s\n", argv[1]);

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

	// 
	// Input Golden Filtered Reference File
	//

	printf("Input Golden Filtered Reference File: %s\n", argv[2]);

    ReadBMPSize(argv[2], &height_ref, &width_ref);
    printf("height_ref = %d, width_ref = %d\n", height_ref, width_ref);
    assert(height_ref <= MAX_HEIGHT);
    assert(width_ref <= MAX_WIDTH);
    
	// Fill a frame with data
	read_tmp = ReadBMPUnsafe(argv[2], height_ref, width_ref,
                           R_ref, G_ref, B_ref, 1200);
	if (read_tmp != 0) {
		printf("%s Loading image failed\n", tempbuf);
		exit(1);
	}

	// Copy Image to pixel data structure
	for (x = 0; x < height_ref; x++) {
		for (y = 0; y < width_ref; y++) {
			ref_pix[x][y].R = R_ref[x*width+y];
			ref_pix[x][y].G = G_ref[x*width+y];
			ref_pix[x][y].B = B_ref[x*width+y];
		}
	}

	////////////////////////////////////////////////////////////////

	// Hardware Function
	video_2dfilter_linebuffer(in_pix, out_pix);

	// Copy Output video pixel stream to Output Image data structure
	for (x = 0; x < height; x++) {
		for (y = 0; y < width; y++) {
			R_out[x*width+y] = out_pix[x][y].R;
			G_out[x*width+y] = out_pix[x][y].G;
			B_out[x*width+y] = out_pix[x][y].B;
		}
	}

	// Write the image back to disk
	int write_tmp = WriteBMP(argv[3], height, width,
                             R_out, G_out, B_out);
	if (write_tmp != 0) {
		printf("WriteBMP %s failed\n", argv[3]);
		exit(1);
	}

	// 
	// Compare filtered image with golden reference
	//
	int sum_absdiff = 0;
	int sum_absdiff_expected = 14000;

	for (x = 0; x < height; x++) {
		for (y = 0; y < width; y++) {
			sum_absdiff += abs(out_pix[x][y].R - ref_pix[x][y].R);
			sum_absdiff += abs(out_pix[x][y].G - ref_pix[x][y].G);
			sum_absdiff += abs(out_pix[x][y].B - ref_pix[x][y].B);	
			printf("R = %d, G = %d, B = %d\n", out_pix[x][y].R, out_pix[x][y].G, out_pix[x][y].B);
			printf("R_ref = %d, G_ref = %d, B_ref = %d\n", ref_pix[x][y].R, ref_pix[x][y].G, ref_pix[x][y].B);
		}
	}

	printf("sum_absdiff = %d\n", sum_absdiff);

    if (sum_absdiff < sum_absdiff_expected) {
		printf("PASS\n");
        return 0; // Success
    } else {
		printf("FAIL\n");
        return 1; // Failure
    }	
}
