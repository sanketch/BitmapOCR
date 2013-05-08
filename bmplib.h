#ifndef BMPLIB_H
#define BMPLIB_H

#define SIZE 256
#define RGB 3

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef struct {
  char signature[2];
} BMPTYPE;

typedef struct {
  uint32 fileSize;
  uint16 rsvd1;
  uint16 rsvd2;
  uint32 pixelOffset;
} BMPFILEHEADER;

typedef struct {
  uint32 dibHeaderSize;
  uint32 width;
  uint32 height;
  uint16 planes;
  uint16 bpp;
  uint32 compression;
  uint32 imageSize;
  uint32 xppm;
  uint32 yppm;
  uint32 colorTableSize;
  uint32 importantColor;
} BITMAPHEADER;

class Character{
	public:
	Character(unsigned char (*myimage1)[256], int ulr, int ulc, int h, int w);
	
	void get_bounding_box(int &sr, int &sc, int &er, int &ec);

	void perform_tests();

	void classify();
//charfound[0].classify

	int get_classification();

	void print_calculations();
	int retuplr();
	int retuplc();
	int reth();
	int retw();
	void getcount(int &counter1);

	private:
	int uplr,uplc;
	int height,width,euler,q1,q3,qd,q2,q4,q0;
	double hsym,vsym;
	unsigned char (*myimage1)[256];
	unsigned char (*myimage)[256];
	double vertical;
	double horizontal;
	double aspRat;
	double horiCent,verCent;
	int actualchar;
	int counter;
};


int readGS_BMP(char *filename, unsigned char image[][SIZE], BMPTYPE &type,  BMPFILEHEADER &fHeader, BITMAPHEADER &bmpHeader);

int writeGS_BMP(char *filename, uint8 outputImage[][SIZE], BMPTYPE &type,  BMPFILEHEADER &fHeader, BITMAPHEADER &bmpHeader );




#endif
