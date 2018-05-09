// BMP file reader and writer routines

// Simple bitmap (.bmp) reader/writer

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bitmap.h"

// Helper functions
bitmap *Get24BitBMP(char *);
bitmap *CreateEmpty24BitBMP(void);
int Write24BitBMP(char *, bitmap *);
void CleanupBMP(bitmap *);
void PrintBMPInfoHeader(BMPInfoHeader *);
void PrintBMPFileHeader(BMPFileHeader *);
int ReadBMPData();
int ReadBMPInfoHeader(FILE *, BMPInfoHeader *);
int ReadBMPFileHeader(FILE *, BMPFileHeader *);
int CloseBMPFile(FILE *);
FILE *OpenBMPOutputFile(const char *);
FILE *OpenBMPInputFile(const char *);

//#define BITMAP_DEBUG

FILE *OpenBMPInputFile(const char *filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		printf("Failed to open bitmap file %s for reading\n", filename);
		return 0;
	} else
		return fp;
}

FILE *OpenBMPOutputFile(const char *filename) {
	FILE *fp = fopen(filename, "wb");
	if (!fp) {
		printf("Failed to open bitmap file %s for writing\n", filename);
		return 0;
	} else
		return fp;
}

int CloseBMPFile(FILE *file) {
	if (file)
		fclose(file);
	return 0;
}

int ReadBMPFileHeader(FILE *fp, BMPFileHeader *header) {
	if (!fp) {
		printf("Invalid file pointer in ReadBMPFileHeader\n");
		return 1;
	}

	if (!fread(header, 1, 14, fp)) {
		printf("Failed to read BMPFileHeader\n");
		return 1;
	} else
		return 0;
}

int ReadBMPInfoHeader(FILE *fp, BMPInfoHeader *info) {
	if (!fp) {
		printf("Invalid file pointer in ReadBMPInfoHeader\n");
		return 1;
	}

	if (!fread(info, 1, 40, fp)) {
		printf("Failed to read BMPInfoHeader\n");
		return 1;
	} else
		return 0;
}

int ReadBMPData(FILE *fp, unsigned char *data, int length) {
	if (!fp) {
		printf("Invalid file pointer in ReadBMPData\n");
		return 1;
	}

	if (!fread(data, 1, length, fp)) {
		printf("Failed to read BMP Data\n");
		return 1;
	} else
		return 0;
}

void PrintBMPFileHeader(BMPFileHeader *header) {
	if (header) {
		printf("BMP File Header:\n");
		printf("\tbfType          = 0x%0x (%i decimal)\n", header->bfType,
					 header->bfType);
		printf("\tbfSize          = 0x%0x (%i decimal)\n", header->bfSize,
					 header->bfSize);
		printf("\tbfReserved1     = 0x%0x (%i decimal)\n", header->bfReserved1,
					 header->bfReserved1);
		printf("\tbfReserved2     = 0x%0x (%i decimal)\n", header->bfReserved2,
					 header->bfReserved2);
		printf("\tbfOffBits       = 0x%0x (%i decimal)\n", header->bfOffBits,
					 header->bfOffBits);
	} else
		printf("Can't print BMPFileHeader - null pointer\n");
}

void PrintBMPInfoHeader(BMPInfoHeader *info) {
	if (info) {
		printf("BMP Info Header:\n");
		printf("\tbiSize          = 0x%0x (%i decimal)\n", info->biSize,
					 info->biSize);
		printf("\tbiWidth         = 0x%0x (%i decimal)\n", info->biWidth,
					 info->biWidth);
		printf("\tbiHeight        = 0x%0x (%i decimal)\n", info->biHeight,
					 info->biHeight);
		printf("\tbiPlanes        = 0x%0x (%i decimal)\n", info->biPlanes,
					 info->biPlanes);
		printf("\tbiBitCount      = 0x%0x (%i decimal)\n", info->biBitCount,
					 info->biBitCount);
		printf("\tbiCompression   = 0x%0x (%i decimal)\n", info->biCompression,
					 info->biCompression);
		printf("\tbiSizeImage     = 0x%0x (%i decimal)\n", info->biSizeImage,
					 info->biSizeImage);
		printf("\tbiXPelsPerMeter = 0x%0x (%i decimal)\n", info->biXPelsPerMeter,
					 info->biXPelsPerMeter);
		printf("\tbiYPelsPerMeter = 0x%0x (%i decimal)\n", info->biYPelsPerMeter,
					 info->biYPelsPerMeter);
		printf("\tbiClrUsed       = 0x%0x (%i decimal)\n", info->biClrUsed,
					 info->biClrUsed);
		printf("\tbiClrImportant  = 0x%0x (%i decimal)\n", info->biClrImportant,
					 info->biClrImportant);
	} else
		printf("Can't print BMPInfoHeader - null pointer\n");
}

bitmap *Get24BitBMP(char *filename) {
	bitmap *bmp = NULL;
	BMPFileHeader *header = NULL;
	BMPInfoHeader *info = NULL;
	unsigned char *data;
	FILE *fp = NULL;
	int i, j;

	header = (BMPFileHeader *)malloc(sizeof(BMPFileHeader));
	if (!header) {
		printf("Failed to malloc BMPFileHeader in Get24BitBMP\n");
		return NULL;
	}

	info = (BMPInfoHeader *)malloc(sizeof(BMPInfoHeader));
	if (!info) {
		printf("Failed to malloc BMPInfoHeader in Get24BitBMP\n");
		if (header)
			free(header);
		return NULL;
	}

	if (!(fp = OpenBMPInputFile(filename))) {
		if (info)
			free(info);
		if (header)
			free(header);
		return NULL;
	}

	if (ReadBMPFileHeader(fp, header) != 0) {
		if (info)
			free(info);
		if (header)
			free(header);
		return NULL;
	}

	if (ReadBMPInfoHeader(fp, info) != 0) {
		if (info)
			free(info);
		if (header)
			free(header);
		return NULL;
	}

	bmp = (bitmap *)malloc(sizeof(bitmap));
	if (!bmp) {
		printf("Failed to malloc bitmap in Get24BitBMP\n");
		if (info)
			free(info);
		if (header)
			free(header);
		return NULL;
	}

	// 24 bit bitmap has no RGBQUAD array, so don't try to read it

	data = (unsigned char *)malloc(info->biSizeImage);
	if (!data) {
		printf("Failed to malloc data storage in Get24BitBMP\n");
		if (info)
			free(info);
		if (header)
			free(header);
		if (bmp)
			free(bmp);
		return NULL;
	}

	if (ReadBMPData(fp, data, info->biSizeImage) != 0) {
		if (info)
			free(info);
		if (header)
			free(header);
		if (data)
			free(data);
		if (bmp)
			free(bmp);
		return NULL;
	}

	bmp->header = header;
	bmp->info = info;
	bmp->data = data;

	// initialize the data arrays
	for (i = 0; i < MAXROWS; i++) {
		for (j = 0; j < MAXCOLS; j++) {
			bmp->r[i][j] = 0;
			bmp->g[i][j] = 0;
			bmp->b[i][j] = 0;
			bmp->y[i][j] = 0;
			bmp->u[i][j] = 0;
			bmp->v[i][j] = 0;
		}
	}

	// copy the data into the r,g,b arrays
	for (i = 0; i < (int)bmp->info->biHeight; i++) {
		for (j = 0; j < (int)bmp->info->biWidth; j++) {

			bmp->r[i][j] = *data++;
			bmp->g[i][j] = *data++;
			bmp->b[i][j] = *data++;

			//      ConvertRGBtoYUV(bmp->r[i][j],bmp->g[i][j],bmp->b[i][j],
			//                    &bmp->y[i][j],&bmp->u[i][j],&bmp->v[i][j]);
		}
	}

	CloseBMPFile(fp);

	return bmp;
}

bitmap *CreateEmpty24BitBMP(void) {
	bitmap *bmp = NULL;
	BMPFileHeader *header = NULL;
	BMPInfoHeader *info = NULL;
	unsigned char *data;
	int i, j;

	header = (BMPFileHeader *)calloc(sizeof(BMPFileHeader), 1);
	if (!header) {
		printf("Failed to calloc BMPFileHeader in CreateEmpty24BitBMP\n");
		return NULL;
	}

	info = (BMPInfoHeader *)calloc(sizeof(BMPInfoHeader), 1);
	if (!info) {
		printf("Failed to calloc BMPInfoHeader in CreateEmpty24BitBMP\n");
		if (header)
			free(header);
		return NULL;
	}

	bmp = (bitmap *)malloc(sizeof(bitmap));
	if (!bmp) {
		if (header)
			free(header);
		if (info)
			free(info);
		printf("Failed to malloc bitmap in CreateEmpty24BitBMP\n");
		return NULL;
	}

	data = (unsigned char *)malloc(MAXROWS * MAXCOLS * 3);
	if (!data) {
		if (header)
			free(header);
		if (info)
			free(info);
		if (data)
			free(data);
		printf("Failed to malloc data storage in CreateEmpty24BitBMP\n");
		return NULL;
	}

	bmp->header = header;
	bmp->info = info;
	bmp->data = data;

	// initialize the data arrays
	for (i = 0; i < MAXROWS; i++) {
		for (j = 0; j < MAXCOLS; j++) {
			bmp->r[i][j] = 0;
			bmp->g[i][j] = 0;
			bmp->b[i][j] = 0;
			bmp->y[i][j] = 0;
			bmp->u[i][j] = 0;
			bmp->v[i][j] = 0;
		}
	}

	return bmp;
}

int Write24BitBMP(char *filename, bitmap *bmp) { return 0; }

void CleanupBMP(bitmap *bmp) {
	if (bmp) {
		if (bmp->header)
			free(bmp->header);
		if (bmp->info)
			free(bmp->info);
		if (bmp->data)
			free(bmp->data);
		free(bmp);
	}
}

//Read the image size
int ReadBMPSize(const char *file, int *row, int *col){
  BMPFileHeader *file_header = NULL;
  BMPInfoHeader *image_header = NULL;

  FILE *bmp_file = NULL;

  int file_open;

  bmp_file = OpenBMPInputFile(file);

  if(!bmp_file){
    printf("ERROR: Can't open file %s\n",file);
    return 1;
  }

  file_header = (BMPFileHeader *)malloc(sizeof(BMPFileHeader));
  if(!file_header){
      printf("ERROR: Can't allocate memory for file header\n");
    return 1;
  }

  image_header = (BMPInfoHeader *)malloc(sizeof(BMPInfoHeader));
  if(!image_header){
      printf("ERROR: Can't allocate memory for image header\n");
      if(file_header) free(file_header);
    return 1;
  }

  int header_read;
  header_read = ReadBMPFileHeader(bmp_file,file_header);

  if(header_read){
    printf("ERROR: Can't read the image header\n");
    if(file_header) free(file_header);
    if(image_header) free(image_header);
    return 1;
  }

  int img_header_read;

  img_header_read = ReadBMPInfoHeader(bmp_file,image_header);
  if(img_header_read){
    printf("ERROR: Can't read the data header\n");
    if(file_header) free(file_header);
    if(image_header) free(image_header);
    return 1;
  }

  *row = (int)image_header->biHeight;
  *col = (int)image_header->biWidth;

  CloseBMPFile(bmp_file);

  if(file_header) free(file_header);
  if(image_header) free(image_header);
  return 0;
}

int ReadBMP(const char *filename, int rows, int cols, unsigned char *r,
						unsigned char *g, unsigned char *b) {
	BMPFileHeader *header = NULL;
	BMPInfoHeader *info = NULL;
	unsigned char *data = NULL;
	FILE *fp = NULL;
	int i, j;

	if (!(fp = OpenBMPInputFile(filename)))
		return 1;

	header = (BMPFileHeader *)malloc(sizeof(BMPFileHeader));
	if (!header) {
		printf("Failed to malloc BMPFileHeader in ReadRGBFromBMP\n");
		return 1;
	}

	info = (BMPInfoHeader *)malloc(sizeof(BMPInfoHeader));
	if (!header) {
		printf("Failed to malloc BMPInfoHeader in ReadRGBFromBMP\n");
		if (header)
			free(header);
		return 1;
	}

	if (ReadBMPFileHeader(fp, header) != 0) {
		if (header)
			free(header);
		if (info)
			free(info);
		return 1;
	}

	if (ReadBMPInfoHeader(fp, info) != 0) {
		if (header)
			free(header);
		if (info)
			free(info);
		return 1;
	}

	// 24 bit bitmap has no RGBQUAD array, so don't try to read it

	data = (unsigned char *)malloc(info->biSizeImage);
	if (!data) {
		printf("Failed to malloc data storage in ReadRGBFromBMP\n");
		if (header)
			free(header);
		if (info)
			free(info);
		if (data)
			free(data);
		return 1;
	}
	if (ReadBMPData(fp, data, info->biSizeImage) != 0) {
		if (header)
			free(header);
		if (info)
			free(info);
		if (data)
			free(data);
		return 1;
	}

	if (rows != (int)info->biHeight) {
		printf(
				"Error:  bitmap file Height (%i) differs from requested height (%i)\n",
				info->biHeight, rows);
		if (header)
			free(header);
		if (info)
			free(info);
		if (data)
			free(data);
		return 1;
	}

	if (cols != (int)info->biWidth) {
		printf(
				"Error:  bitmap file Height (%i) differs from requested height (%i)\n",
				info->biWidth, cols);
		if (header)
			free(header);
		if (info)
			free(info);
		if (data)
			free(data);
		return 1;
	}

	unsigned char *datatmp = data;

	// copy the data into the r,g,b arrays (BMP is stored upside-down)
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			unsigned char rtmp, gtmp, btmp;

			btmp = *datatmp++;
			gtmp = *datatmp++;
			rtmp = *datatmp++;

			r[(rows - 1 - i) * cols + j] = rtmp;
			g[(rows - 1 - i) * cols + j] = gtmp;
			b[(rows - 1 - i) * cols + j] = btmp;
		}
	}

	CloseBMPFile(fp);
	if (header)
		free(header);
	if (info)
		free(info);
	if (data)
		free(data);

	return 0;
}

int WriteBMP(const char *filename, int rows, int cols, unsigned char *r,
						 unsigned char *g, unsigned char *b) {

	int i, j;
	bitmap *bmp = NULL;
	FILE *outfile;
	unsigned char *data;

	bmp = CreateEmpty24BitBMP();
	if (!bmp) {
		printf("Failed to create bitmap in WriteBMPFromRGB\n");
		return 1;
	}

	bmp->header->bfType = 19778;
	bmp->header->bfSize = 0;
	bmp->header->bfReserved1 = 0;
	bmp->header->bfReserved2 = 0;
	bmp->header->bfOffBits = 54;

	bmp->info->biSize = 40;
	bmp->info->biWidth = cols;
	bmp->info->biHeight = rows;
	bmp->info->biPlanes = 1;
	bmp->info->biBitCount = 24;
	bmp->info->biCompression = 0;
	bmp->info->biSizeImage = 3 * rows * cols;
	bmp->info->biXPelsPerMeter = 2835;
	bmp->info->biYPelsPerMeter = 2835;
	bmp->info->biClrUsed = 0;
	bmp->info->biClrImportant = 0;

	data = bmp->data;

	// (BMP is stored upside-down)
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			unsigned char rtmp, gtmp, btmp;

			rtmp = r[(rows - 1 - i) * cols + j];
			gtmp = g[(rows - 1 - i) * cols + j];
			btmp = b[(rows - 1 - i) * cols + j];

			*data++ = btmp;
			*data++ = gtmp;
			*data++ = rtmp;
		}
	}

	outfile = fopen(filename, "wb");
	if (!outfile) {
		printf("Failed to open file %s for writing in WriteBMPFromRGB\n", filename);
		CleanupBMP(bmp);
		return 1;
	}

	fwrite(&bmp->header->bfType, 1, 2, outfile);
	fwrite(&bmp->header->bfSize, 1, 4, outfile);
	fwrite(&bmp->header->bfReserved1, 1, 2, outfile);
	fwrite(&bmp->header->bfReserved2, 1, 2, outfile);
	fwrite(&bmp->header->bfOffBits, 1, 4, outfile);

	fwrite(&bmp->info->biSize, 1, 4, outfile);
	fwrite(&bmp->info->biWidth, 1, 4, outfile);
	fwrite(&bmp->info->biHeight, 1, 4, outfile);
	fwrite(&bmp->info->biPlanes, 1, 2, outfile);
	fwrite(&bmp->info->biBitCount, 1, 2, outfile);
	fwrite(&bmp->info->biCompression, 1, 4, outfile);
	fwrite(&bmp->info->biSizeImage, 1, 4, outfile);
	fwrite(&bmp->info->biXPelsPerMeter, 1, 4, outfile);
	fwrite(&bmp->info->biYPelsPerMeter, 1, 4, outfile);
	fwrite(&bmp->info->biClrUsed, 1, 4, outfile);
	fwrite(&bmp->info->biClrImportant, 1, 4, outfile);

	fwrite(bmp->data, 1, bmp->info->biSizeImage, outfile);
	fclose(outfile);

	CleanupBMP(bmp);
	return 0;
}
