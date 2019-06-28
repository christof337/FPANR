#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//#include<conio.h>

#include "utils.h"
#include "LUFacto.h"
#include "libfpanrio.h"

/*
compile with
rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o main.o main.1.ll main.2.ll output/*
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 4 1

rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o main.o main.1.ll main.2.ll
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 3 1

or simply with :
gcc utils.c LUFacto.c -o LUFacto -lm -lfpanrio
./LUFacto 4
*/

int main(int argc, char *argv[]) {
    const short int NB_MATRIX = 8;

    size_t n = 4;
    short int isFpanr = 0;

    time_t t;
    /* Intializes random number generator */
    srandom((unsigned) time(&t));

    // parsing arguments
    if (argc >= 2) {
        n = ((size_t) atoi(argv[1]));
        if ( argc >= 3 && strcmp(argv[2],"1")==0) {
            isFpanr = 1;
        }
    }

    // 
    //printf("Enter the order of square matrix: ");
    //scanf("%zu",&n);

    // iterating through enum strategies
    for (int strategy = PS_MAX ; strategy <= PS_MAX_PRECISION ; ++strategy ) {
        if ( strategy != PS_MAX_PRECISION || isFpanr ) {
            // 8 matrix need to be computed with perturbations
            for ( short int i = 0 ; i < NB_MATRIX ; ++i ) {
                computeMatrix(n, isFpanr, i, strategy);
            }
            // 1 "clear" is computed as reference
            computeMatrix(n, isFpanr, -1, strategy);
        }
    }

    return 0;
}
