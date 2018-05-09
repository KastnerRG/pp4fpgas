#ifndef OLD_FILM_H_
#define OLD_FILM_H_
#include "video_settings.h"
#include "bitmap.h"
#include "video_aux.h"

#define ABSDIFF(x, y) ((x > y) ? x - y : y - x)
#define ABS(x) ((x > 0) ? x : -x)

// Arrays to store input image data
static unsigned char R_in[MAX_HEIGHT][MAX_WIDTH];
static unsigned char G_in[MAX_HEIGHT][MAX_WIDTH];
static unsigned char B_in[MAX_HEIGHT][MAX_WIDTH];

// Arrays to store output image data
static unsigned char R_out[MAX_HEIGHT][MAX_WIDTH];
static unsigned char G_out[MAX_HEIGHT][MAX_WIDTH];
static unsigned char B_out[MAX_HEIGHT][MAX_WIDTH];

typedef struct {
	rgb_pixel pix;
	unsigned char edge;
} rgb_edge;

void video_2d_filter_linebuffer(rgb_pixel in_pix[MAX_HEIGHT][MAX_WIDTH],
																rgb_pixel out_pix[MAX_HEIGHT][MAX_WIDTH]);

#endif
