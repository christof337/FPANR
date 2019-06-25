#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<conio.h>

#include "LUFacto.h"

#include "utils.h"
#include "libfpanrio.h"


int computeMatrix(size_t n, short int isFpanr) {
    // déclarations
    int i,j,k;
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
        printf("\nstep1");
        fflush(stdout);
        fpanrDMatToFile(n, n, *L, "output/L.dat");

        printf("\n\n[U]: \n");
        matrix_print_fpanr(n,n,*U);
        fpanrDMatToFile(n, n, *U, "output/U.dat");

        printf("\n\n[Y]: \n");
        array_print_fpanr(n,*Y);
        fpanrDVecToFile(n, *Y, "output/Y.dat");

        printf("\n\n[X]: \n");
        array_print_fpanr(n,*X);
        fpanrDVecToFile(n, *X, "output/X.dat");
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

/**
 * LU Decomposition
 * TODO : need to find the best pivoting strategy
**/
void LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], short int isFpanr, double P[n][n]) {
    int nbPivots = n;
    for(int j=0; j<n; ++j)
    {
        nbPivots += LUPivot(n, A, P, j, isFpanr);
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

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1 
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N, 
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S    
 */
int LUPivot(int n, double A[n][n], /*double tol,*/ double P[n][n], int currentRow, short int isFpanr) {
    int i, j, k, imax; 
    double maxA, ptr[n], absA;
    int hasPivoted = 0;

    maxA = isFpanr?dtfp(0.0):0.0;
    imax = currentRow;

    for (k = currentRow; k < n; k++) {
        // maximum strategy
        absA = isFpanr?myAbs(A[k][currentRow]):fabs(A[k][currentRow]);
        if (absA > maxA) { 
            maxA = absA;
            imax = k;
        }
    }
    //if (maxA < Tol) return 0; //failure, matrix is degenerate

    if (imax != currentRow) {
        //pivoting P
        array_copy(n, P[currentRow], ptr);
        array_copy(n, P[imax], P[currentRow]);
        array_copy(n, ptr, P[imax]);

        //pivoting rows of A
        array_copy(n, A[currentRow], ptr);
        array_copy(n, A[imax], A[currentRow]);
        array_copy(n, ptr, A[imax]);

        //counting pivots starting from N (for determinant)
        hasPivoted=1;
    }

    /*for (j = currentRow + 1; j < N; j++) {
        A[j][currentRow] /= A[currentRow][currentRow];

        for (k = currentRow + 1; k < N; k++)
            A[j][k] -= A[j][currentRow] * A[currentRow][k];
    }*/
    // free(ptr);

    return hasPivoted;  //decomposition done 
}



/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
void LUPSolve(size_t n, double L[n][n], double U[n][n], double Y[n], double P[n][n], double B[n], double X[n], short int isFpanr) {
    int i,j;
    for(i=0; i<n; ++i) {
        int permutedIndex = isFpanr?getOneFpanr(n,P[i]):getOne(n,P[i]);
        Y[i]=B[permutedIndex]; // (*Y)[i] = (*B)[P[i]]
        for(j=0; j<i; ++j) {
            Y[i]-=L[i][j]*Y[j];
        }
    }
    for(i=n-1; i>=0; i--) {
        X[i]= Y[i];
        for(j=i+1; j<n; ++j) {
            X[i]-=U[i][j]*X[j];
        }
        X[i]/=U[i][i];
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension
 * OUTPUT: IA is the inverse of the initial matrix
 */
void LUPInvert(int n, double U[n][n], double L[n][n], double P[n][n], double IA[n][n], short int isFpanr) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            int permut = isFpanr?getOneFpanr(n,P[i]):getOne(n,P[i]);
            if (permut == j) 
                IA[i][j] = isFpanr?dtfp(1.0):1.0;
            else
                IA[i][j] = isFpanr?dtfp(0.0):0.0;

            for (int k = 0; k < i; k++)
                IA[i][j] -= U[i][k] * IA[k][j];
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int k = i + 1; k < n; k++)
                IA[i][j] -= L[i][k] * IA[k][j];

            IA[i][j] = IA[i][j] / L[i][i];
        }
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension. 
 * OUTPUT: Function returns the determinant of the initial matrix
 */
double LUPDeterminant(size_t n, double A[n][n], int nbPivots) {
    double det = A[0][0];

    for (int i = 1; i < n; i++)
        det *= A[i][i];

    if ((nbPivots - n) % 2 == 0)
        return det; 
    else
        return -det;
}
