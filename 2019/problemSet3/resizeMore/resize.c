// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // ensure proper scale value
    if (atoi(argv[1]) > 100 || atoi(argv[1]) < 1)
    {
        fprintf(stderr, "You can choose scale from 0 up to 100\n");
        return 2;
    }

    // remember filenames and number to resize
    char *infile = argv[2];
    char *outfile = argv[3];
    int nTimes = atoi(argv[1]);

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
    int biHeight = abs(bi.biHeight);
    int biWidth = bi.biWidth;

    // determine padding for scanlines
    int paddingI = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingO = (4 - (bi.biWidth * nTimes * sizeof(RGBTRIPLE)) % 4) % 4;

    // change outfile's BITMAPFILEHEADER and BITMAPINFOHEADER
    bi.biWidth *= nTimes;
    bi.biHeight *= nTimes;
    bf.bfSize = (bi.biWidth * sizeof(RGBTRIPLE) + paddingO) * abs(bi.biHeight) + bf.bfOffBits;
    bi.biSizeImage = bf.bfSize - bf.bfOffBits;


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i1 = 0; i1 < biHeight; i1++)
    {
        // multiplicate scanlines
        for(int i2 = 0; i2 < nTimes; i2++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                for (int k = 0; k < nTimes; k++)
                {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            if(i2 < nTimes - 1)
            {
            // return to beggining of scanline
            fseek(inptr, biWidth * sizeof(RGBTRIPLE) * -1, SEEK_CUR);
            }
            else
            {
            // skip over padding, if any
                fseek(inptr,paddingI, SEEK_CUR);
            }

            // add padding to outfile
            for (int l = 0; l < paddingO; l++)
            {
                fputc(0x00, outptr);
            }
        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}