#ifndef VIDEO_AUX_H_
#define VIDEO_AUX_H_
#include "video_settings.h"
//#include "ap_int.h"
//#include "ap_stream.h"

/* struct frame_data { */
/* 	ap_uint<11> hcount; */
/* 	ap_uint<11> vcount; */
/* }; */

typedef struct {
	unsigned char R[MAX_WIDTH][MAX_HEIGHT];
	unsigned char G[MAX_WIDTH][MAX_HEIGHT];
	unsigned char B[MAX_WIDTH][MAX_HEIGHT];
} video_data;

typedef struct {
	unsigned char ch1;
	unsigned char ch2;
	unsigned char ch3;
} pixel;

typedef struct {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} rgb_pixel;

#endif
