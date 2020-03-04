// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include <math.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // ensure proper scale value
    if (atoi(argv[1]) > 100 || atof(argv[1]) < 0.1)
    {
        fprintf(stderr, "You can choose scale from 0.1 up to 100\n");
        return 2;
    }

    // remember filenames and number to resize
    char *infile = argv[2];
    char *outfile = argv[3];
    float nTimes = atof(argv[1]);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create helping variables
    int inHeight = abs(bi.biHeight);
    int inWidth = bi.biWidth;
    int outHeight = (roundf(inHeight * nTimes));
    int outWidth = (roundf(inWidth * nTimes));
    float nTimesDecimal = nTimes - (int) nTimes;
    float nthPixel = inWidth / round((inWidth * nTimesDecimal));
    float nthPixelInit = nthPixel;
    float nthScanline = inHeight / round((inHeight * nTimesDecimal));
    float nthScanlineInit = nthPixel;
    int pixelsToCopy = roundf(inWidth * nTimesDecimal);
    int scanlinesToCopy = roundf(inHeight * nTimesDecimal);
    int countPixels = 0;
    int countScanlines = 0;
    int scaleDown = 0;
    
    // set nTimes for scaling down
    if(nTimes < 1)
    {   
        scaleDown = 1;
        nTimes = 1;
    }

    // determine padding for scanlines of input and output file
    int paddingI = (4 - (inWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingO = (4 - (outWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    bi.biWidth = outWidth;
    bi.biHeight = outHeight * -1;
    bf.bfSize = (bi.biWidth * sizeof(RGBTRIPLE) + paddingO) * abs(bi.biHeight) + bf.bfOffBits;
    bi.biSizeImage = bf.bfSize - bf.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i1 = 1; i1 <= inHeight; i1++)
    {
        // multiplicate scanlines n Times
        for(int i2 = 1; i2 <= (int) nTimes; i2++)
        {   
            // check what scanline to extra copy
            if( roundf(nthScanline) == i1 && countScanlines < scanlinesToCopy && scaleDown == 0)
            {
                i2--;
                countScanlines++;
                nthScanline += nthScanlineInit;
            }

            // iterate over pixels in scanline
            for (int j = 1; j <= inWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                if (scaleDown == 0)
                {
                    // write RGB triple to outfile
                    for (int k = 1; k <= (int) nTimes; k++)
                    {
                        // check what pixel to extra copy
                        if(roundf(nthPixel) == j && countPixels < pixelsToCopy)
                        {
                            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                            countPixels++;
                            nthPixel += nthPixelInit;
                        }

                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
                else if(roundf(nthPixel) == j && roundf(nthScanline) == i1 && countPixels < pixelsToCopy)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    nthPixel += nthPixelInit;
                    countPixels++;
                }
            }
            nthPixel = nthPixelInit;
            countPixels = 0;
            if(i2 < (int) nTimes)
            {
            // return to beggining of scanline
            fseek(inptr, inWidth * sizeof(RGBTRIPLE) * -1, SEEK_CUR);
            }
            else
            {
            // skip over padding, if any
                fseek(inptr,paddingI, SEEK_CUR);
            }

            // add padding to outfile
            if (scaleDown == 0)
            {
                for (int l = 0; l < paddingO; l++)
                {
                    fputc(0x00, outptr);
                }
            }
            else if (roundf(nthScanline) == i1 && scaleDown == 1)
            {
                for (int l = 0; l < paddingO; l++)
                {
                    fputc(0x00, outptr);
                }
            }
        }
        if (roundf(nthScanline) == i1 && scaleDown == 1)
        {
            nthScanline += nthScanlineInit;
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}