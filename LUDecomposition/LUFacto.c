#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
//#include<conio.h>

#include "LUFacto.h"

#include "utils.h"
#include "libfpanrio.h"

// #define WRITE_X_IN_FILE
// #define WRITE_Y_IN_FILE
#define WRITE_A_INV_IN_FILE

#define DEBUG 0

#define VERBOSE 1

#define DEFAULT_PERTURBATION 30

int computeMatrix(size_t n, short int isFpanr, short int index, enum PIVOT_STRATEGY strategy) {
    // déclarations
    int i,j,k;
    double (*A)[n][n], (*L)[n][n], (*U)[n][n], (*P)[n][n];
    double (*B)[n], (*X)[n], (*Y)[n];
    double (*Ainv)[n][n];

    // allocations
    matrix_alloc(n, n, &A);
    matrix_alloc(n, n, &L);
    matrix_alloc(n, n, &U);
    matrix_alloc(n,n,&P);
    array_alloc(n,&B);
    matrix_alloc(n,n,&Ainv);
    array_alloc(n,&X);
    array_alloc(n,&Y);

    // initialisations
    if(isFpanr) {
        matrix_fill_fpanr(n,n,*A);
        matrix_fill_fpanr(n,n,*L);
        matrix_fill_fpanr(n,n,*U);
        permutation_matrix_fill_fpanr(n,n,*P);   // filling permutation matrix with zeros
        array_fill(n,*B);
        array_fill_fpanr(n, *X);
        array_fill_fpanr(n, *Y);
        matrix_fill_fpanr(n,n,*Ainv);
    }else {
        matrix_fill(n,n,*A);
        matrix_fill(n,n,*L);
        matrix_fill(n,n,*U);
        permutation_matrix_fill(n, n, *P);  // filling permutation matrix with zeros
        array_fill(n,*B);
        array_fill(n, *X);
        array_fill(n, *Y);   
        matrix_fill(n,n,*Ainv);
    }

    // remplissage
    if(isFpanr) {
        if ( n == 3 )
            fill_fig1_fpanr(*A);
        else 
            hilbert_fpanr(n,n,*A);
        arrayFillExp_fpanr(n,*B);
    } else {
        if ( n == 3 )
            fill_fig1(*A);
        else 
            hilbert(n,n,*A);
        arrayFillExp(n,*B);
    }

    if(index!=-1) {
        // perturbation
        isFpanr?perturbateMatrix_fpanr(n,n,*A,DEFAULT_PERTURBATION):perturbateMatrix(n,n,*A, DEFAULT_PERTURBATION);
    }

    // affichages initiaux
#if VERBOSE
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
#endif // VERBOSE

    printf("\n\nDébut du traitement...\n");
    printf(isFpanr?"Using FPANR\n":"");
    fflush(stdout);

    /* ------------------------------- */
    /*      LU decomposition call      */
    LU_decomposition(n, *U, *A, *L, isFpanr, *P, strategy);
    /* ------------------------------- */

    printf("\n\nFin du traitement...\n");
    fflush(stdout);

    // résolution
    // for ( i = 0 ; i < n ; ++i ) {        
        LUPSolve(n, *L, *U, *Y, *P, *B, *X, isFpanr);
        // int permutedIndex = isFpanr?getOneFpanr(n,(*P)[i]):getOne(n,(*P)[i]);
        // array_copy(n, *X, (*Ainv)[permutedIndex]);
    // }

    char * fileName;
    // affichages finaux
    if(isFpanr) {
#if VERBOSE
        printf("\n[L]: \n");
        matrix_print_fpanr(n,n,*L);
#endif // VERBOSE
        fileName = buildFileName(OM_L, n, index, strategy);
        fpanrDMatToFile(n, n, *L, fileName);
        free(fileName);

#if VERBOSE
        printf("\n\n[U]: \n");
        matrix_print_fpanr(n,n,*U);
#endif // VERBOSE
        fileName = buildFileName(OM_U, n, index, strategy);
        fpanrDMatToFile(n, n, *U, fileName);
        free(fileName);

#if VERBOSE
        printf("\n\n[Y]: \n");
        array_print_fpanr(n,*Y);
#endif // VERBOSE
#ifdef WRITE_Y_IN_FILE
        fileName = buildFileName(OM_Y, n, index, strategy);
        fpanrDVecToFile(n, *Y, fileName);
        free(fileName);
#endif // WRITE_Y_IN_FILE

#if VERBOSE
        printf("\n\n[X]: \n");
        array_print_fpanr(n,*X);
#endif // VERBOSE
#ifdef WRITE_X_IN_FILE
        fileName = buildFileName(OM_X, n, index, strategy);
        fpanrDVecToFile(n, *X, fileName);
        free(fileName);
#endif // WRITE_X_IN_FILE

//#if VERBOSE
        // printf("\n\n[A_INV] with solve: \n");
        // matrix_print_fpanr(n, n, *Ainv);
        LUPInvert(n, *U, *L, *P, *Ainv, isFpanr);
        printf("\n\n[A_INV]: \n");
        matrix_print_fpanr(n, n, *Ainv);
//#endif // VERBOSE
#ifdef WRITE_A_INV_IN_FILE
        fileName = buildFileName(OM_A_INV, n, index, strategy);
        fpanrDMatToFile(n, n, *Ainv, fileName);
        free(fileName);
#endif // WRITE_A_INV_IN_FILE

        printf("\n");
    } else {
#if VERBOSE
        printf("\n[L]: \n");
        matrix_print(n,n,*L);

        printf("\n\n[U]: \n");
        matrix_print(n,n,*U);

        printf("\n\n[Y]: \n");
        array_print(n,*Y);

        printf("\n\n[X]: \n");
        array_print(n,*X);
        printf("\n");
#endif // VERBOSE
    }
#if DEBUG
    double (*test)[n][n];
    isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *L, *U);
    isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);
    free(*test);

    printf("\n");
    isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *P, *A);
    isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);

    free(test);
#endif // DEBUG

    free(A);
    free(L);
    free(U);
    free(B);
    free(X);
    free(Y);

    return 0;
}

/**
 * LU Decomposition
 * TODO : need to find the best pivoting strategy
 * returns the number of pivot made
**/
int LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], short int isFpanr, double P[n][n], enum PIVOT_STRATEGY strategy) {
    int nbPivots = n;
    for(int j=0; j<n; ++j) {
        nbPivots += LUPivot(n, A, P, j, isFpanr, strategy);
        for(int i=0; i<n; ++i) {
            if(i<=j) {
                U[i][j]=A[i][j];
                for(int k=0; k<=i-1; ++k) {
                    U[i][j]-=L[i][k]*U[k][j];
                }
                if(i==j)
                    L[i][j]=isFpanr?dtfp(1.0):1.0;
                else
                    L[i][j]=isFpanr?dtfp(0.0):0;
            } else {
                L[i][j]=A[i][j];
                for(int k=0; k<=j-1; ++k) {
                    L[i][j]-=L[i][k]*U[k][j];
                }
                L[i][j]/=U[j][j];
                U[i][j]=isFpanr?dtfp(0.0):0.0;
            }
            printf(" %d ", getPrecFromFpanrDouble(U[i][j]));
        }
        printf("\n");
    }
    printf("%s %s %d",strategy==PS_MAX?"MAX":"MAX_PREC", isFpanr?"isFpanr":"!isFpanr", nbPivots );
    return nbPivots;
}

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1 
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N, 
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S    
 */
int LUPivot(int n, double A[n][n], /*double tol,*/ double P[n][n], int currentRow, short int isFpanr, enum PIVOT_STRATEGY strategy) {
    int i, j, k, imax; 
    double maxA, ptr[n], absA;
    int hasPivoted = 0;
    int prec = 0, maxPrec = 0;

    maxA = isFpanr?dtfp(0.0):0.0;
    imax = currentRow;

    for (k = currentRow; k < n; k++) {
        switch(strategy) {
            case PS_MAX:
                // maximum strategy
                absA = isFpanr?myAbs(A[k][currentRow]):fabs(A[k][currentRow]);
                if (absA > maxA) { 
                    maxA = absA;
                    imax = k;
                }
                break;
            case PS_MAX_PRECISION:
                if (isFpanr) {
                    prec = getPrecFromFpanrDouble(A[k][currentRow]);
                    if ( prec > maxPrec ) {
                        maxPrec = prec;
                        imax = k;
                    }
                } else {
                    fprintf(stderr, "\nError : should use FPANR when computing max precision pivot strategy");
                    return 0;
                }
                break;
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
                IA[i][j] -= L[i][k] * IA[k][j];
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int k = i + 1; k < n; k++)
                IA[i][j] -= U[i][k] * IA[k][j];

            IA[i][j] = IA[i][j] / U[i][i];
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

#define FILE_FOLDER "output"
#define MAX_FILE_NAME_LENGTH 100
#define FILE_NAME_SUFFIX ".dat"

char * buildFileName(enum OUTPUT_MATRIX OM, size_t n, short int index, enum PIVOT_STRATEGY strategy) {
    char * res;
    char buffer[20];

    res = malloc(MAX_FILE_NAME_LENGTH * sizeof(char));

    // sample file name : U1_n4_MAX.dat
    strcpy(res, FILE_FOLDER);

    strcat(res, "/");

    if ( OM != OM_A_INV ) 
        append(res, OM);
    else
        strcat(res,"A_INV");

    if(index == -1) {
        sprintf(buffer, "ref");
    } else {
        sprintf(buffer, "%hi", index);
    }
    strcat(res, buffer);

    strcat(res, "_n");

    sprintf(buffer, "%zu", n);
    strcat(res, buffer);

    strcat(res, "_");

    switch(strategy) {
        case PS_MAX:
            strcat(res, "MAX");
            break;
        case PS_MAX_PRECISION:
            strcat(res, "MAX_PREC");
            break;
        default:
            break;
    }
    strcat(res, FILE_NAME_SUFFIX);

    return res;
}