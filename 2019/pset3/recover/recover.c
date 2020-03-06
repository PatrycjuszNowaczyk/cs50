#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    printf("start\n");
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

    // declare needed variables
    BYTE buffer[512];
    memset(buffer,'\0',512);
    int imageNumber = 1;
    char intToString[10];
    char nameOfAfile[128];
    bzero(nameOfAfile,128);
    char nameConcat1[] = {"./images/image-"};
    char nameConcat2[] = {".jpg"};
    BYTE isNewJpeg = 0;
    BYTE isJpeg = 0;
    BYTE compare[3] = { 255, 216, 255};
    FILE *image;
    
    while (fread(buffer, 512,1,inPointer) == 1)
    {

        // check is it a jpeg
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
            sprintf(intToString, "%i", imageNumber);
            strcpy(nameOfAfile, strcat(strcat(nameConcat1, intToString), nameConcat2));
            // tutaj jest problem z tworzeniem pliku 
            image = fopen(nameOfAfile, "w");
            printf("create new file\n");
            if (image == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", nameOfAfile);
                return 5;
            }
            fwrite(buffer, 512, 1, image);
            imageNumber++;
            isNewJpeg = 0;
            isJpeg = 1;
            bzero(nameOfAfile, 128);
            bzero(nameConcat1, 15);
            bzero(nameConcat2, 4);
            bzero(intToString,10);
            // nameOfAfile[0] = 0;
            // nameConcat1[0] = 0;
            // nameConcat2[0] = 0;
            // intToString[0] = 0;
            // memset(intToString,0,strlen(intToString));
            // memset(nameOfAfile,0,strlen(nameOfAfile));
            // memset(nameConcat1,0,strlen(nameConcat1));
            // memset(nameConcat2,0,strlen(nameConcat2));
            strcpy(nameConcat1,"./images/image-");
            strcpy(nameConcat2,".jpg");
        }
        else if(isJpeg ==1)
        {
            fwrite(buffer, 512, 1, image);
        }

        // check is it an end of a jpeg's file
        if (buffer[0] && !buffer[511] && isJpeg == 1)
        {
            for (int i = 510; i > 0 ; i--)
            {
                if (buffer[i] != EOF)
                {
                    printf("close file\n");
                        isJpeg = 0;
                        fclose(image);
                }
            }
        }

    }

    fclose(inPointer);
    return 0;
}