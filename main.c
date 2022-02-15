#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

/*
 * function protoype for your assembly routine
 */
extern unsigned int fpconvert(unsigned int);

union uf {
    uint32_t i;
    float f;
};
typedef union uf uf_t;


int main(int argc, char *argv[])
{
    uf_t cnvrt_num;
    FILE *infile;
    uint16_t fp_number;

    if (argc != 2) {
        fprintf(stderr, "Useage: convertfp file\n");
        return EXIT_FAILURE;
    }

    /*
     * open the data file
     */
    if ((infile = fopen(argv[1], "r")) == NULL) {
        perror("convertftp fopen()");
        return EXIT_FAILURE;
    }

    /*
     * read until EOF, calling your assembly function to convert
     */
    while (fread(&fp_number, sizeof(fp_number), 1, infile)){
        cnvrt_num.i = fpconvert((uint32_t)fp_number);
        printf("%08x\t", cnvrt_num.i);
        printf("%36.30f\n", cnvrt_num.f);
    }

    fclose(infile);
    return EXIT_SUCCESS;
}
