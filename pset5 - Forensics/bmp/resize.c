#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }
    
    // remember scale.
    int n = atoi(argv[1]);
    if (n<0 || n>100)
    {
        printf("n must be a positive number smaller than or equal to 100.\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf,bf2;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf2 = bf;
    
    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi,bi2;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi2 = bi;
 
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
       
    //change the width and height of image.
    bi2.biWidth = bi.biWidth*n;
    bi2.biHeight = bi.biHeight*n;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4)%4 ;
    int padding2 =  (4 - (bi2.biWidth * sizeof(RGBTRIPLE)) % 4)%4 ;
    
    //change the size of image.
    bi2.biSizeImage = (bi2.biWidth*abs(bi2.biHeight)*sizeof(RGBTRIPLE)) + abs(bi2.biHeight)*padding2;
    
    //change the BITMAPFILEHEADER
    bf2.bfSize = bi2.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);

    int seek = (bi.biWidth*sizeof(RGBTRIPLE) + padding);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int iScale = 0; iScale < n; iScale++)
        {   
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {       
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(int jScale = 0; jScale < n; jScale++)
                {                    
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

                // skip over padding, if any
                fseek(inptr, padding, SEEK_CUR);
                              
                // then add it back (to demonstrate how)
                for (int k = 0; k < padding2; k++)
                {
                    fputc(0x00, outptr);
                }
            
            if(iScale < n - 1)
            {
                fseek(inptr,-seek,SEEK_CUR);            
            }
            
        }
     }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
