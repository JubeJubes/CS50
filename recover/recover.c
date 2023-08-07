#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
typedef uint16_t WORD;


typedef struct {
    BYTE content[512];
} __attribute__((__packed__))
pic_chunk;
const int BLOCK_SIZE = sizeof(pic_chunk);
int main(int argc, char *argv[])
{
     // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];

        // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // open output file
    int file_num=-1;
    char* outfile = calloc(8,sizeof(char));
    FILE *outptr;



    BYTE *buffer = calloc(1, BLOCK_SIZE);
    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
        (buffer[3] & 0xe0))
        {
            if (file_num>=0){fclose(outptr);}
            file_num++;
            sprintf(outfile, "%03d.jpg", file_num);
            outptr = fopen(outfile, "w");
        }

        if(file_num>=0) {fwrite(buffer, 512, 1,outptr);}
    }

    free(buffer);
    free(outfile);


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;

}