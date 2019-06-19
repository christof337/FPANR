#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>

#include "utils.h"
#include "libfpanrio.h"

/*
compile with
rm a.out LUFacto.1.ll LUFacto.2.ll LUFacto.o utils.1.ll utils.2.ll utils.o
VERIFICARLO_BACKEND=FPANR verificarlo LUFacto.c utils.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR verificarlo utils.c LUFacto.c -lm -lfpanrio
VERIFICARLO_BACKEND=FPANR ./a.out 1

or simply with :
gcc utils.c LUFacto.c -o LUFacto -lm -lfpanrio
./LUFacto 
*/

void LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], int isFpanr) {
    for(int j=0; j<n; ++j)
    {
        for(int i=0; i<n; ++i)
        {
            if(i<=j)
            {
                U[i][j]=A[i][j];
                for(int k=0; k<=i-1; ++k) {
                    U[i][j]-=L[i][k]*U[k][j];
                }
                if(i==j)
                    L[i][j]=isFpanr?dtfp(1.0):1.0;
                else
                    L[i][j]=isFpanr?dtfp(0.0):0;
            }
            else
            {
                L[i][j]=A[i][j];
                for(int k=0; k<=j-1; ++k) {
                    L[i][j]-=L[i][k]*U[k][j];
                }
                L[i][j]/=U[j][j];
                U[i][j]=isFpanr?dtfp(0.0):0.0;
            }
        }
    }
}

/*
void array_fill_fpanr (size_t x, double array[x]);
void arrayFillExp_fpanr(size_t x, double array[x]) ;
void array_print_fpanr (size_t x, double array[x]);
void matrix_fill_fpanr (size_t x, size_t y, double matrix[x][y]);
void hilbert_fpanr(size_t x, size_t y, double matrix[x][y]) ;
void matrix_print_fpanr (size_t x, size_t y, double matrix[x][y]);
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
    double (*A)[n][n], (*L)[n][n], (*U)[n][n];
    double (*B)[n], (*X)[n], (*Y)[n];

    // allocations
    matrix_alloc(n, n, &A);
    matrix_alloc(n, n, &L);
    matrix_alloc(n, n, &U);
    array_alloc(n,&B);
    array_alloc(n,&X);
    array_alloc(n,&Y);

    // initialisations
    if(isFpanr) {
        matrix_fill_fpanr(n,n,*A);
        matrix_fill_fpanr(n,n,*L);
        matrix_fill_fpanr(n,n,*U);
        array_fill_fpanr(n, *B);
        array_fill_fpanr(n, *X);
        array_fill_fpanr(n, *Y);
    }else {
        matrix_fill(n,n,*A);
        matrix_fill(n,n,*L);
        matrix_fill(n,n,*U);
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
    LU_decomposition(n, *U, *A, *L, isFpanr);
    /* ------------------------------- */

    printf("\n\nFin du traitement...\n");
    fflush(stdout);

    for(i=0; i<n; ++i)
    {
        (*Y)[i]=(*B)[i];
        for(j=0; j<i; ++j)
        {
            (*Y)[i]-=(*L)[i][j]*(*Y)[j];
        }
    }
    for(i=n-1; i>=0; i--)
    {
        (*X)[i]= (*Y)[i];
        for(j=i+1; j<n; ++j)
        {
            (*X)[i]-=(*U)[i][j]*(*X)[j];
        }
        (*X)[i]/=(*U)[i][i];
    }

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
    // double (*test)[n][n];
    // matrix_mult(n, n, n, &test, *L, *U);
    // matrix_print(n,n,*test);

    free(A);
    free(L);
    free(U);
    free(B);
    free(X);
    free(Y);
    // free(test);

    return 0;
}