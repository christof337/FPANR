#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<float.h>
#include<math.h>
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

rm *.ll *.o a.out
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 3 1

or simply with :
gcc utils.c LUFacto.c -o LUFacto -lm -lfpanrio
./LUFacto 4
*/

void mineStrategy(const size_t n, const enum PIVOT_STRATEGY strategy, const int nb_matrix, const int isFpanr) ;

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

    // up to here, files have been generated
    // let's sum them up shall we?

    // looping through strategies looks like a good place to start
    for ( int strategy = PS_MAX ; strategy <= PS_MAX_PRECISION ; ++strategy ) {
        // ok now we have to sum up the 8 matrices that have been computed
        mineStrategy(n, strategy, NB_MATRIX, isFpanr);
    }

    return 0;
}

#define MAX_PREC 51
void mineStrategy(const size_t n, const enum PIVOT_STRATEGY strategy, const int nb_matrix, const int isFpanr) {
    char * fileName;
    int prec;
    // on commence par déclarer le tableau qui contiendra les précisions
    int * arrayPrec = malloc(sizeof(int)*MAX_PREC);
    for ( int k = 0 ; k < MAX_PREC ; ++k ) 
        arrayPrec[k] = 0;

    // chacune des cases du tableau va contenir le nombre d'éléments des matrices qui a la précision de son index

    // parcourons les fichiers shall we?
    double val, absA;
    // first, the reference file
    double matrixRef[n][n], perturbedMatrix[n][n]; // it will be used for comparison THROUGHOUT the rest of this function
    fileName = buildFileName(OM_A_INV, n, -1, strategy);
    strcat(fileName,".fpanr");
    fpanrFileToDMat(n, n, matrixRef, fileName);
    //getMatrixFromFile(n,matrixRef,fileName);
    for ( size_t indMat = 0 ; indMat < nb_matrix ; ++indMat ) {
        fileName = buildFileName(OM_A_INV, n, indMat, strategy);
        strcat(fileName,".fpanr");
        fpanrFileToDMat(n, n, perturbedMatrix, fileName);

        for ( size_t i = 0 ; i < n ; ++i ) {
            for ( size_t j = 0 ; j < n ; ++j ) {
                val =  matrixRef[i][j] - perturbedMatrix[i][j];
                printf("\n[%zu][%zu] : ref:%d,pert:%d,dif:%d",i,j,getPrecFromFpanrDouble(matrixRef[i][j]),getPrecFromFpanrDouble(perturbedMatrix[i][j]),getPrecFromFpanrDouble(val));
                printf("\n\t%.16e - %.16e = %.16e",fpanrToDouble(matrixRef[i][j]),fpanrToDouble(perturbedMatrix[i][j]),fpanrToDouble(matrixRef[i][j]-perturbedMatrix[i][j]));
                absA = isFpanr?myAbs(val):fabs(val);
                printf(" (after abs %d)",getPrecFromFpanrDouble(absA));
                prec = MAX_PREC-getPrecFromFpanrDouble(absA);
                //prec = getPrecFromFpanrDouble(absA);
                arrayPrec[prec]+=1;
            }
        }
        free(fileName);
    }
    
    printf("\n--------\nMine : size=%zu, strategy=%d,nb_matrix=%d,isFpanr=%d :\n",n,strategy,nb_matrix,isFpanr);
    for ( size_t k = 0 ; k < MAX_PREC ; ++k ) {
        printf("\n[%zu]:%d\t",k,arrayPrec[k]);
        for ( int m = 0 ; m < arrayPrec[k] ; ++m) {
            printf(" ||");
        }
    }
    printf("\n\n");
    matrix_print_fpanr (n, n, matrixRef);


    FILE * fp;
    fileName = buildFileName(OM_PREC, n, -1, strategy);
    fp = fopen(fileName, "w");
    if ( fp == NULL ) {
        fprintf(stderr, "\nError while opening file %s. Exiting...\n",fileName);
    } else {
        for ( int k = 0 ; k < MAX_PREC ; ++k ) {
            fprintf(fp, "%d\t%d\n",k,arrayPrec[k]);
        }
        fclose(fp);
    }

    free(fileName);
    free(arrayPrec);

    //printf("mining %d %d %d",strategy, nb_matrix, isFpanr);
}
/*
backup purpose : 
rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o main.o main.1.ll main.2.ll retrieveResults.1.ll retrieveResults.2.ll retrieveResults.o output/*
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c main.c retrieveResults.c  -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c retrieveResults.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c retrieveResults.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo retrieveResults.c main.c utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 4 1

rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o main.o main.1.ll main.2.ll retrieveResults.1.ll retrieveResults.2.ll retrieveResults.o 

rm *.ll *.o a.out
VERIFICARLO_BACKEND=FPANR verificarlo utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo retrieveResults.c LUFacto.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c retrieveResults.c LUFacto.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 3 1
*/