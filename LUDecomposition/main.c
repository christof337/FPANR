#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>

#include "utils.h"
#include "LUFacto.h"
#include "libfpanrio.h"

/*
compile with
rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o main.o main.1.ll main.2.ll
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 1

or simply with :
gcc utils.c LUFacto.c -o LUFacto -lm -lfpanrio
./LUFacto 
*/

int main(int argc, char *argv[])
{
    short int isFpanr = 0;
    if (argc == 2) {
        if (strcmp(argv[1],"1")==0) {
            isFpanr = 1;
        }
    }
    size_t n;
    printf("Enter the order of square matrix: ");
    scanf("%zu",&n);


    computeMatrix(n, isFpanr);

    return 0;
}
