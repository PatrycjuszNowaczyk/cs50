#include <stdio.h>
#include <stdint.h>
#include "bmp.h"
void main()
{
    FILE *inptr = fopen("smiley.bmp", "r");
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;
    fread(&bf,sizeof(BITMAPFILEHEADER),1, inptr);
    fread(&bi,sizeof(BITMAPINFOHEADER),1, inptr);

    printf("bitmapfileheader size in bytes: %li\n", sizeof(BITMAPFILEHEADER));
    printf("bitmapinfoheader size in bytes: %li\n", sizeof(BITMAPINFOHEADER));
    printf("bfSize: %i\n", bf.bfSize);
    printf("bfType: %i\n", bf.bfType);
    printf("bfOffBits: %i\n", bf.bfOffBits);
    printf("biSize: %i\n", bi.biSize);
    printf("biHeight: %i\n", bi.biHeight);
    printf("biWidth: %i\n", bi.biWidth);
    printf("RGBTRIPLE size: %li\n", sizeof(RGBTRIPLE));

}