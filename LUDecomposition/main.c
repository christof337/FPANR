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
    int isFpanr = 0;
    if (argc == 2) {
        if (strcmp(argv[1],"1")==0) {
            isFpanr = 1;
        }
    }
    int i,j,k;
    size_t n;
    printf("Enter the order of square matrix: ");
    scanf("%zu",&n);

    // déclarations
    double (*A)[n][n], (*L)[n][n], (*U)[n][n], (*P)[n][n];
    double (*B)[n], (*X)[n], (*Y)[n];

    // allocations
    matrix_alloc(n, n, &A);
    matrix_alloc(n, n, &L);
    matrix_alloc(n, n, &U);
    matrix_alloc(n,n,&P);
    array_alloc(n,&B);
    array_alloc(n,&X);
    array_alloc(n,&Y);

    // initialisations
    if(isFpanr) {
        matrix_fill_fpanr(n,n,*A);
        matrix_fill_fpanr(n,n,*L);
        matrix_fill_fpanr(n,n,*U);
        permutation_matrix_fill_fpanr(n,n,*P);   // filling permutation matrix with zeros
        array_fill_fpanr(n, *B);
        array_fill_fpanr(n, *X);
        array_fill_fpanr(n, *Y);
    }else {
        matrix_fill(n,n,*A);
        matrix_fill(n,n,*L);
        matrix_fill(n,n,*U);
        permutation_matrix_fill(n, n, *P);  // filling permutation matrix with zeros
        array_fill(n, *B);
        array_fill(n, *X);
        array_fill(n, *Y);   
    }

    // remplissage
    if(isFpanr) {
        hilbert_fpanr(n,n,*A);
        arrayFillExp_fpanr(n,*B);
    } else {
        hilbert(n,n,*A);
        arrayFillExp(n,*B);
    }

    // affichages initiaux
    printf("[A]: \n");
    if(isFpanr) {
        matrix_print_fpanr(n,n,*A);
    } else {
        matrix_print(n,n,*A);
    }
    printf("\n\n[B]: \n");
    if(isFpanr) {
        array_print_fpanr(n,*B);
    } else {
        array_print(n,*B);
    }

    printf("\n\nDébut du traitement...\n");
    printf(isFpanr?"Using FPANR\n":"");
    fflush(stdout);

    /* ------------------------------- */
    /*      LU decomposition call      */
    LU_decomposition(n, *U, *A, *L, isFpanr, *P);
    /* ------------------------------- */

    printf("\n\nFin du traitement...\n");
    fflush(stdout);

    // résolution
    LUPSolve(n, *L, *U, *Y, *P, *B, *X, isFpanr);

    // affichages finaux
    if(isFpanr) {
        printf("\n[L]: \n");
        matrix_print_fpanr(n,n,*L);

        printf("\n\n[U]: \n");
        matrix_print_fpanr(n,n,*U);

        printf("\n\n[Y]: \n");
        array_print_fpanr(n,*Y);

        printf("\n\n[X]: \n");
        array_print_fpanr(n,*X);
        printf("\n");
    } else {
        printf("\n[L]: \n");
        matrix_print(n,n,*L);

        printf("\n\n[U]: \n");
        matrix_print(n,n,*U);

        printf("\n\n[Y]: \n");
        array_print(n,*Y);

        printf("\n\n[X]: \n");
        array_print(n,*X);
        printf("\n");
    }
    double (*test)[n][n];
    isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *L, *U);
    isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);
    free(*test);

    printf("\n");
    isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *P, *A);
    isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);

    free(A);
    free(L);
    free(U);
    free(B);
    free(X);
    free(Y);
    free(test);

    return 0;
}