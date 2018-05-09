#ifndef IMAGE_AUX_H_
#define IMAGE_AUX_H_
//#include <autopilot_tech.h>
#include <png.h>
#define WIDTH 1280
#define HEIGHT 720

typedef struct {
	unsigned char ch1[WIDTH][HEIGHT];
	unsigned char ch2[WIDTH][HEIGHT];
	unsigned char ch3[WIDTH][HEIGHT];
} channel_t;
typedef struct {
	channel_t channels;
	unsigned short width;
	unsigned short height;
} image_t;

void image_info(png_structp pngp, png_infop infop);

void image_read(char *in_file, image_t *in_image);

void image_write(char *out_file, image_t *out_image);

#endif
