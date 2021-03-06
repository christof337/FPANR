#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<float.h>
#include<math.h>
#include<assert.h>
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
VERIFICARLO_BACKEND=FPANR ./a.out 3 1 hungarian

// normal build with 3x3 matrix, hungarian and FPANR
rm *.ll *.o a.out
VERIFICARLO_BACKEND=FPANR verificarlo utils.c hungarian.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo hungarian.c LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c hungarian.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c hungarian.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 3 1 hungarian

// normal build with the 2nd 3x3 matrix, hungarian and FPANR -------------
rm *.ll *.o a.out
VERIFICARLO_BACKEND=FPANR verificarlo utils.c hungarian.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo hungarian.c LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c hungarian.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c hungarian.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 3 1 hungarian 1 1


// valgrind exec with 3x3 matrix, hungarian and FPANR
rm *.ll *.o a.out
VERIFICARLO_BACKEND=FPANR verificarlo utils.c hungarian.c LUFacto.c main.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo hungarian.c LUFacto.c main.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c main.c utils.c hungarian.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo main.c utils.c hungarian.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR valgrind -v ./a.out 3 1 hungarian

VERIFICARLO_BACKEND=FPANR ./a.out 3 1 LU
VERIFICARLO_BACKEND=FPANR ./a.out 3 1 hungarian

or simply with :
gcc utils.c LUFacto.c hungarian.c main.c -o LUFacto -lm -lfpanrio
./LUFacto 3 0 LU
./LUFacto 3 0 hungarian
./LUFacto 4
*/

#define DEFAULT_MATRIX_SIZE 4
#define MIN_PREC 16
#define MAX_PREC 51

// #define DEBUG

void mineStrategy(const size_t n, const enum PIVOT_STRATEGY strategy, int nb_matrix, const int isFpanr, const enum INVERSION_ALGORITHM algorithm) ;

int main(int argc, char *argv[]) {
    /*double a,b;
    a = doubleToFpanrWithPrec(1.5,48);
    b = doubleToFpanrWithPrec(1.6,49);

    printf("%d", cmpFpanrDouble( a, b) );
    printf("\na : %1.54F, b : %1.54F, a-b : %1.100F ? %d\n", fptd(a),fptd(b), fptd(a)-fptd(b), fptd(a)-fptd(b)==0.0);
    printf("\n? %d\n",fptd(a)==fptd(b));
    printf("\ndoublesub : %1.54F, 0.0 : %1.54F ? %d ?? %d ?? %d",_doublesub(a,b),0.0,_doublesub(a,b)==0.0, fptd(_doublesub(a,b))==0.0, _doublesub(a,b)==dtfp(0.0));

    return 0;*/
    const short int NB_MATRIX = 8;
    enum INVERSION_ALGORITHM algorithm = IA_LU;
    enum INPUT_MATRIX matrix;
    enum INDICATEUR_ENUM indicateur;

    size_t n = DEFAULT_MATRIX_SIZE;
    short int isFpanr = 0;

    time_t t;
    /* Intializes random number generator */
    srandom((unsigned) time(&t));

    // parsing arguments
    if (argc >= 2) {
        n = ((size_t) atoi(argv[1]));
        if ( argc >= 3 ) {
            if (strcmp(argv[2],"1")==0) {
                isFpanr = 1;
            }
            if ( argc >= 4 ) {
                if(strcmp(argv[3],"LU")==0) {
                    // LU
                    algorithm = IA_LU;
                } else if (strcmp(argv[3], "hungarian") == 0) {
                    // hungarian
                    algorithm = IA_HUNG;
                }
                if ( argc >= 5 ) {
                    if(strcmp(argv[4], "1") == 0 ) {
                        matrix = MAT_2;
                    } else if (strcmp(argv[4], "0") == 0 ) {
                        matrix = MAT_1;
                    } else {
                        matrix = MAT_HILBERT;
                    }
                    if ( argc >= 6 ) {
                        // indicateur
                        if(strcmp(argv[5], "1") == 0 ) {
                            indicateur = IE_LOW_PREC;
                        } else {
                            indicateur = IE_PERTURBED;
                        }
                    }
                } else if ( n == 3 ) {
                    matrix = MAT_1;
                } else {
                    matrix = MAT_HILBERT;
                }
            }
        }
    }

    // 
    //printf("Enter the order of square matrix: ");
    //scanf("%zu",&n);

    // iterating through enum strategies
    for (int strategy = PS_MAX_MAG_NOT_IN_S; strategy <= PS_MAX_PRECISION ; ++strategy ) {
        #ifdef DEBUG
        if(strategy == PS_MAX_MAG_NOT_IN_S) {
        #endif
        if ( strategy != PS_MAX_PRECISION || isFpanr ) {
            if (indicateur == IE_PERTURBED) {
                // 8 matrix need to be computed with perturbations
                for ( short int i = 0 ; i < NB_MATRIX ; ++i ) {
                    computeMatrix(n, isFpanr, i, strategy, algorithm, matrix,indicateur,PREC_MAX_DOUBLE);
                }
            } else if (indicateur == IE_LOW_PREC) {
                for ( short int i = MIN_PREC ; i < MAX_PREC ; ++i ) {
                    printf("\nMATRIX LOW PREC");
                    computeMatrix(n, isFpanr, -2, strategy, algorithm, matrix,indicateur,i);
                }
            }
                printf("\nMATRIX REF");
            // 1 "clear" is computed as reference
            computeMatrix(n, isFpanr, -1, strategy, algorithm, matrix, indicateur,PREC_MAX_DOUBLE);
        }
        #ifdef DEBUG
        }
        #endif
    }

    // up to here, files have been generated
    // let's sum them up shall we?
    
    // for(int i = 0 ; i < 4000 ; ++i ) {
    //     printf("*");
    // }

    if ( isFpanr ) {
        // looping through strategies looks like a good place to start
        for ( int strategy = PS_MAX_MAG_NOT_IN_S; strategy <= PS_MAX_PRECISION ; ++strategy ) {
            // ok now we have to sum up the 8 matrices that have been computed
            mineStrategy(n, strategy, indicateur==IE_PERTURBED?NB_MATRIX:1, isFpanr, algorithm);
        }
    }

    printf("\n\nEND SUCCESS\n");
    fflush(stdout);

    return 0;
}

#define USE_DIFF 0
// throughout this function, if nb_matrix==1 then the indicator is low_prec
void mineStrategy(const size_t n, const enum PIVOT_STRATEGY strategy, int nb_matrix, const int isFpanr, const enum INVERSION_ALGORITHM algorithm) {
    char fileName[100];
    char * tmp;
    int prec;
    double val, absA;
    double moydist=FPANR_ZERO;
    double moyDistArray[MAX_PREC-MIN_PREC+1];
    double matrixRef[n][n], perturbedMatrix[n][n]; // it will be used for comparison THROUGHOUT the rest of this function
    printf("\nmineprec\n");
    // on commence par déclarer le tableau qui contiendra les précisions
    int * arrayPrec = malloc(sizeof(int[MAX_PREC+1]));
    for ( size_t k = 0 ; k <= MAX_PREC ; ++k ) {
        arrayPrec[k] = 0;
    }
    matrix_fill_fpanr(n,n,matrixRef);
    matrix_fill_fpanr(n,n,perturbedMatrix);

    // chacune des cases du tableau va contenir le nombre d'éléments des matrices qui a la précision de son index

    // parcourons les fichiers shall we?
    // first, the reference file
    tmp = buildFileName(OM_A_INV, n, -1, strategy, algorithm);
    assert(tmp != NULL);
    strcpy(fileName, tmp);
    free(tmp);
    strcat(fileName,".fpanr");
    fpanrFileToDMat(n, n, matrixRef, fileName);
    //getMatrixFromFile(n,matrixRef,fileName);
    nb_matrix = nb_matrix==1?MAX_PREC:(USE_DIFF?nb_matrix:1);
    for ( size_t indMat = nb_matrix==MAX_PREC?MIN_PREC:0 ; indMat < nb_matrix ; ++indMat ) {
        moydist = FPANR_ZERO;
        tmp = buildFileName(OM_A_INV, n, nb_matrix==1?-2:indMat, strategy, algorithm);
        assert(tmp != NULL);
        strcpy(fileName, tmp);
        strcat(fileName,".fpanr");
        fpanrFileToDMat(n, n, perturbedMatrix, fileName);
        // printf("filename : %s",fileName);

        for ( size_t i = 0 ; i < n ; ++i ) {
            for ( size_t j = 0 ; j < n ; ++j ) {
                if(nb_matrix == MAX_PREC) {
                    if ( cmpFpanrDouble(matrixRef[i][j], dtfp(0.0)) != 0 ) {
                        // printf("\np:(%F-%F)/%F=%F",matrixRef[i][j],perturbedMatrix[i][j],matrixRef[i][j],myAbs((matrixRef[i][j] - perturbedMatrix[i][j])/matrixRef[i][j]));
                        moydist += myAbs((matrixRef[i][j] - perturbedMatrix[i][j])/matrixRef[i][j]);
                    } else {
                        moydist += myAbs(matrixRef[i][j] - perturbedMatrix[i][j]);
                    }
                } else {
                    if ( USE_DIFF ) {
                        val =  matrixRef[i][j] - perturbedMatrix[i][j];
                       // printf("\n[%zu][%zu] : ref:%d,pert:%d,dif:%d",i,j,getPrecFromFpanrDouble(matrixRef[i][j]),getPrecFromFpanrDouble(perturbedMatrix[i][j]),getPrecFromFpanrDouble(val));
                       // printf("\n\t%.16e - %.16e = %.16e",fpanrToDouble(matrixRef[i][j]),fpanrToDouble(perturbedMatrix[i][j]),fpanrToDouble(matrixRef[i][j]-perturbedMatrix[i][j]));
                        absA = isFpanr?myAbs(val):fabs(val);
                    } else {
                        printf("\n\t--loss prec ref %d: \tloss prec perturbed : %d",MAX_PREC-getPrecFromFpanrDouble(matrixRef[i][j]),40-getPrecFromFpanrDouble(perturbedMatrix[i][j]));
                        val = matrixRef[i][j];
                        absA = myAbs(val);
                    }

                   // printf(" (after abs %d)",getPrecFromFpanrDouble(absA));
                    if ( USE_DIFF )
                        prec = MAX_PREC-getPrecFromFpanrDouble(absA);
                    else
                        prec = getPrecFromFpanrDouble(absA);
                    assert(prec<=MAX_PREC && prec >= 0);
                    //prec = getPrecFromFpanrDouble(absA);
                    arrayPrec[prec] = arrayPrec[prec] + 1;
                }
            }
        }
        free(tmp);
        if(nb_matrix == MAX_PREC) {
            moydist /= (n*n);
            char * chaine = fpanrDoubleToStr(moydist);
            assert(chaine != NULL);
            printf("\nMEAN DISTANCE for prec %zu : %s",indMat, chaine);
            free(chaine);
            moyDistArray[indMat-MIN_PREC] = moydist;
        }
    }
    if(nb_matrix != MAX_PREC) {
        // perturbed
        for ( size_t k = 0 ; k < MAX_PREC ; ++k ) {
            printf("\n[%zu]:%d\t",k,arrayPrec[k]);
            for ( int m = 0 ; m < arrayPrec[k] ; ++m) {
                printf(" ||");
            }
        }
        printf("\n\n");

        FILE * fp;
        tmp = buildFileName(OM_PREC, n, -1, strategy, algorithm);
        assert(tmp != NULL);
        strcpy(fileName, tmp);
        fp = fopen(fileName, "w");
        if ( fp == NULL ) {
            fprintf(stderr, "\nError while opening file %s. Exiting...\n",fileName);
        } else {
            printf("\nWriting final strategy mining file to '%s'",fileName);
            for ( size_t k = 0 ; k < MAX_PREC ; ++k ) {
                fprintf(fp, "%zu\t%d\n",k,arrayPrec[k]);
            }
            fclose(fp);
        }
    } else {
        // low prec
        FILE * fp;
        tmp = buildFileName(OM_DIST, n, -2, strategy, algorithm);
        assert(tmp != NULL);
        strcpy(fileName, tmp);
        // fpanrDVecToFile(MAX_PREC-MIN_PREC, moyDistArray, fileName);
        fp = fopen(fileName, "w");
        assert(fp != NULL);
        printf("\nWriting mean distance to file '%s'",fileName);
        for( size_t k = MIN_PREC ; k < nb_matrix ; ++k ) {
            char * chaine = fpanrDoubleToStr(moyDistArray[k-MIN_PREC]);
            assert(chaine != NULL);
            fprintf(fp,"%zu\t%s\n",k,chaine);
            free(chaine);
        }
        fclose(fp);
    }


    free(tmp);
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