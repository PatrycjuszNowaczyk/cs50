#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h> 
#include <errno.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    char *sourceFile = argv[1]; 
    char *pch;

    // check does program was correctly initiated
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else if((pch=strstr(argv[1],".raw")) == NULL )
    {
        printf("The parameter must be a .raw file format\n");
        return 2;
    }
    else if((pch=strstr(argv[1],"./")) == NULL )
    {
        printf("You need to specify a path leding to a .raw file\n");
        return 3;
    }

    // open raw file
    FILE *inPointer = fopen(argv[1], "r");
    if (inPointer == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", sourceFile);
        return 4;
    }

    // create directory if doesn't exist
    mkdir("images", 0777);

    // declare needed variables
    BYTE buffer[512];
    int imageNumber = 1;
    char intToString[10];
    char nameOfAfile[128];
    char nameConcat1[] = {"./images/image-"};
    char nameConcat2[] = {".jpg"};
    BYTE isNewJpeg = 0;
    BYTE isJpeg = 0;
    BYTE compare[3] = { 255, 216, 255};
    FILE *image;
    
    while (fread(buffer, 512,1,inPointer) == 1)
    {

        // check is it start of a new jpeg
        if(buffer[0] == 255)
        {   
            isNewJpeg++;
            for(int i = 1; i < 3; i++)
            {
                if (buffer[i] == compare[i])
                {
                    isNewJpeg++;
                }
            }
            for (BYTE i = 224; i < 240; i++)
            {
                if (buffer[3] == i)
                {
                    isNewJpeg++;
                    break;
                } 
            }
            if (isNewJpeg != 4)
            {
                isNewJpeg = 0;
            }            
        }

        // create jpeg file if was found
        if (isNewJpeg == 4)
        {
            sprintf(nameOfAfile,"./images/image-%i.jpg",imageNumber);
            image = fopen(nameOfAfile, "w");
            if (image == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", nameOfAfile);
                return 5;
            }
            fwrite(buffer, 512, 1, image);
            imageNumber++;
            isNewJpeg = 0;
            isJpeg = 1;
        }
        else if(isJpeg ==1)
        {
            // check is it an end of a jpeg's file
            if (buffer[511] == 0 || (buffer[511] == 0xD9 && buffer[510] == 0xFF))
            {
                // find last byte of a jpeg's file
                for (int i = 511; i > 0 ; i--)
                {
                    if (buffer[i] != 0)
                    {
                        // if found last two closing bytes write down and cloase a file
                        if (buffer[i] == 0xD9 && buffer[i-1] == 0xFF)
                        {
                            fwrite(buffer, i+1, 1, image);
                            printf("%s has been recovered\n", nameOfAfile);
                            isJpeg = 0;
                            fclose(image);
                            break;
                        }
                        // if closing bytes not found just write down whole buffer to a file
                        else
                        {
                            fwrite(buffer, 512, 1, image);
                            break;
                        }
                    
                    }
                    
                }
            }
            // if there is no ending sign just write down buffer
            else
            {
                fwrite(buffer, 512, 1, image);
            }
            
        }


    }
    printf("\nAll images are successfully restored.\n\n");
    fclose(inPointer);
    return 0;
}