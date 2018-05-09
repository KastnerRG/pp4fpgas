// BMP File Reader and Writer

#define WHITE 255
#define BLACK 0
#define MAXROWS 1080
#define MAXCOLS 1920

struct _BMPFileHeader {
	unsigned short bfType;
	unsigned int bfSize;
	unsigned short bfReserved1;
	unsigned short bfReserved2;
	unsigned int bfOffBits;
};
typedef struct _BMPFileHeader BMPFileHeader;

struct _BMPInfoHeader {
	unsigned int biSize;
	unsigned int biWidth;
	unsigned int biHeight;
	unsigned short biPlanes;
	unsigned short biBitCount;
	unsigned int biCompression;
	unsigned int biSizeImage;
	unsigned int biXPelsPerMeter;
	unsigned int biYPelsPerMeter;
	unsigned int biClrUsed;
	unsigned int biClrImportant;
};
typedef struct _BMPInfoHeader BMPInfoHeader;

struct _bitmap {
	BMPFileHeader *header;
	BMPInfoHeader *info;
	unsigned int *colors;
	unsigned char *data;
	unsigned char r[MAXROWS][MAXCOLS];
	unsigned char g[MAXROWS][MAXCOLS];
	unsigned char b[MAXROWS][MAXCOLS];
	unsigned char y[MAXROWS][MAXCOLS];
	char u[MAXROWS][MAXCOLS];
	char v[MAXROWS][MAXCOLS];
};
typedef struct _bitmap bitmap;

// Externally visible procedures
int ReadBMPSize(const char *file, int *row, int *col);
int ReadBMP(const char *filename, int rows, int cols, unsigned char *r,
						unsigned char *g, unsigned char *b);
int WriteBMP(const char *filename, int rows, int cols, unsigned char *r,
						 unsigned char *g, unsigned char *b);
