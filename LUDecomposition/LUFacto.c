#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
//#include<conio.h>

#include "LUFacto.h"

#include "utils.h"
#include "libfpanrio.h"

#include "hungarian.h"


// #define WRITE_X_IN_FILE
// #define WRITE_Y_IN_FILE
#define WRITE_A_INV_IN_FILE

#define DEBUG 0

#define VERBOSE 1

#define DEFAULT_PERTURBATION 40

extern enum PIVOT_STRATEGY strategy;
extern enum OUTPUT_MATRIX OM;

int computeMatrix(const size_t n, const short int isFpanr, const short int index, const enum PIVOT_STRATEGY strategy, const enum INVERSION_ALGORITHM algorithm, const enum INPUT_MATRIX matrix, const enum INDICATEUR_ENUM indicateur, const int precision ) {
    // déclarations
    int bla;
    #if DEBUG
    printf("\n---------COMPUTING MATRIX %d",index);
    // scanf("%d",&bla);
    #endif
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
    matrix_alloc(n, n, &Ainv);
    array_alloc(n,&X);
    array_alloc(n,&Y);

    // initialisations
    if(isFpanr) {
        if(index != -2 ) {
            matrix_fill_fpanr(n,n,*A);
            matrix_fill_fpanr(n,n,*L);
            matrix_fill_fpanr(n,n,*U);
            permutation_matrix_fill_fpanr(n,n,*P);   // filling permutation matrix with zeros
            array_fill_fpanr(n,*B);
            array_fill_fpanr(n, *X);
            array_fill_fpanr(n, *Y);
            matrix_fill_fpanr(n,n,*Ainv);
        } else {
            matrix_fill_fpanr_with_prec(n,n,*A, DEFAULT_LOW_PRECISION);
            matrix_fill_fpanr_with_prec(n,n,*L, DEFAULT_LOW_PRECISION);
            matrix_fill_fpanr_with_prec(n,n,*U, DEFAULT_LOW_PRECISION);
            permutation_matrix_fill_fpanr_with_prec(n,n,*P, DEFAULT_LOW_PRECISION);   // filling permutation matrix with zeros
            array_fill_fpanr_with_prec(n,*B, DEFAULT_LOW_PRECISION);
            array_fill_fpanr_with_prec(n, *X, DEFAULT_LOW_PRECISION);
            array_fill_fpanr_with_prec(n, *Y, DEFAULT_LOW_PRECISION);
            matrix_fill_fpanr_with_prec(n,n,*Ainv, DEFAULT_LOW_PRECISION);
        }
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
        switch(matrix) {
            case MAT_1:
                fill_fig1_fpanr(*A);
                break;
            case MAT_2:
                fill_fig2_fpanr(*A);
                break;
            case MAT_HILBERT:
            default:
                hilbert_fpanr(n,n,*A);
                break;
        }
        arrayFillExp_fpanr(n,*B);
    } else {
        switch(matrix) {
            case MAT_1:
                fill_fig1(*A);
                break;
            case MAT_2:
                fill_fig2(*A);
                break;
            case MAT_HILBERT:
            default:
                hilbert(n,n,*A);
                break;
        }
        arrayFillExp(n,*B);
    }

    if(index>-1) {
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
    int maxI, maxJ, lastLine = 0;
    double max;
    size_t independantSet[n][2];
    /* ------------------------------- */
    #if DEBUG
    // scanf("%d",&bla);
    #endif
    switch ( algorithm ) {
        case IA_LU:
            /*      LU decomposition call      */
            printf("\nLU decomposition :\n");
            LU_decomposition(n, *U, *A, *L, isFpanr, *P, strategy, indicateur, precision);
            break;
        case IA_HUNG:
            printf("\nGaussjordanpivot : ");
            #if DEBUG
            printf("\n-------------------A BEFORE\n");
            matrix_print_fpanr(n,n,*A);
            //gaussJordanPivot(n, n, *A, isFpanr, strategy);
            printf("\n-----------------------A AFTER\n");
            matrix_print_fpanr(n,n,*A);
            // #if DEBUG
            printf("\nend pivot");
            fflush(stdout);
            #endif
            break;
           /* printf("\nHungarian decomposition (Munkres) :\n");
                // scanf("%d",&bla);
            hungarian(n,n,*A, independantSet, isFpanr);
            printf("\nEnd of hung");
            fflush(stdout);
            for(size_t i = 0 ; i < n ; ++i ) {
                printf("\n(%zu) : [%zu,%zu] = %f",i, independantSet[i][0],independantSet[i][1], (*A)[independantSet[i][0]][independantSet[i][1]]);
                fflush(stdout);
            }
                // we got S
            switch ( strategy ) {
                case PS_MAX_MAG_NOT_IN_S:
                    // selecting the pivot of maximum magnitude (not in S)
                    max = FPANR_ZERO;
                    for ( i = 0 ; i < n ; ++i ) {
                        for ( j = 0 ; j < n ; ++j ) {
                            if ( (*A)[i][j] > max && !isInZu(n,independantSet,i,j)) {
                                max = (*A)[i][j];
                                maxI = i;
                                maxJ = j;
                            }
                        }
                    }
                    manualPivoting(n, n, *A, max, maxI, maxJ, lastLine);
                    lastLine = maxI;
                    break;
                case PS_MAX_PRECISION:
                    break;
            }

            break;*/
    }
    /* ------------------------------- */

    printf("\n\nFin du traitement...\n");
    fflush(stdout);

    // TODO : output yet to be smoothed

    // résolution
    // for ( i = 0 ; i < n ; ++i ) {
    char * fileName;
    if (algorithm == IA_LU) {       
        LUPSolve(n, *L, *U, *Y, *P, *B, *X, isFpanr);

        // int permutedIndex = isFpanr?getOneFpanr(n,(*P)[i]):getOne(n,(*P)[i]);
        // array_copy(n, *X, (*Ainv)[permutedIndex]);
    // }

        // affichages finaux
        if(isFpanr) {
            #if VERBOSE
            printf("\n[L]: \n");
            matrix_print_fpanr(n,n,*L);
            #endif // VERBOSE
            fileName = buildFileName(OM_L, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDMatToFile(n, n, *L, fileName);
            free(fileName);

            #if VERBOSE
            printf("\n\n[U]: \n");
            matrix_print_fpanr(n,n,*U);
            #endif // VERBOSE
            fileName = buildFileName(OM_U, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDMatToFile(n, n, *U, fileName);
            free(fileName);

            #if VERBOSE
            printf("\n\n[Y]: \n");
            array_print_fpanr(n,*Y);
            #endif // VERBOSE
              #ifdef WRITE_Y_IN_FILE
            fileName = buildFileName(OM_Y, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDVecToFile(n, *Y, fileName);
            free(fileName);
    #endif // WRITE_Y_IN_FILE

    #if VERBOSE
            printf("\n\n[X]: \n");
            array_print_fpanr(n,*X);
    #endif // VERBOSE
    #ifdef WRITE_X_IN_FILE
            fileName = buildFileName(OM_X, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDVecToFile(n, *X, fileName);
            free(fileName);
    #endif // WRITE_X_IN_FILE

    //#if VERBOSE
            // printf("\n\n[A_INV] with solve: \n");
            // matrix_print_fpanr(n, n, *Ainv);
            LUPInvert(n, *U, *L, *P, *Ainv, isFpanr, indicateur, precision);
            printf("\n\n[A_INV]: \n");
            matrix_print_fpanr(n, n, *Ainv);
    //#endif // VERBOSE
    #ifdef WRITE_A_INV_IN_FILE
            fileName = buildFileName(OM_A_INV, n, index, strategy, algorithm);
            assert(fileName != NULL);
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

            printf("\n\n[A]: \n");
            matrix_print(n,n,*A);
    #endif // VERBOSE
        }
    #if DEBUG
        /*double (*test)[n][n];
        isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *L, *U);
        isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);
        free(test);

        printf("\n");
        isFpanr?matrix_mult_fpanr(n,n,n,&test,*L,*U):matrix_mult(n, n, n, &test, *P, *A);
        isFpanr?matrix_print_fpanr(n,n,*test):matrix_print(n,n,*test);
        free(test);*/
    #endif // DEBUG
    } else if (algorithm == IA_HUNG ) {
        printf("\neventually inverting the matrix : \n");
        fflush(stdout);
        gaussJordanInversion(n, n, *A, *Ainv, isFpanr, strategy, indicateur, precision);
       // affichages finaux
        if(isFpanr) {
    #if VERBOSE
            printf("\n\n[Y]: \n");
            array_print_fpanr(n,*Y);
    #endif // VERBOSE
    #ifdef WRITE_Y_IN_FILE
            fileName = buildFileName(OM_Y, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDVecToFile(n, *Y, fileName);
            free(fileName);
    #endif // WRITE_Y_IN_FILE

    #if VERBOSE
            printf("\n\n[X]: \n");
            array_print_fpanr(n,*X);
    #endif // VERBOSE
    #ifdef WRITE_X_IN_FILE
            fileName = buildFileName(OM_X, n, index, strategy, algorithm);
            assert(fileName != NULL);
            fpanrDVecToFile(n, *X, fileName);
            free(fileName);
    #endif // WRITE_X_IN_FILE

    //#if VERBOSE
            // printf("\n\n[A_INV] with solve: \n");
            // matrix_print_fpanr(n, n, *Ainv);
           // gaussJordanInversion(n, n, *A, *Ainv, isFpanr, strategy);
            printf("\n\n[A_INV]: \n");
            matrix_print_fpanr(n, n, *Ainv);
    //#endif // VERBOSE
    #ifdef WRITE_A_INV_IN_FILE
            fileName = buildFileName(OM_A_INV, n, index, strategy, algorithm);
            assert(fileName != NULL);
            #if DEBUG
            printf("\nwriting A INV to file %s\n",fileName);
            #endif
            fpanrDMatToFile(n, n, *Ainv, fileName);
            free(fileName);  // /!/
    #endif // WRITE_A_INV_IN_FILE

            printf("\n");
        } else {
    #if VERBOSE
            printf("\n\n[Y]: \n");
            array_print(n,*Y);

            printf("\n\n[X]: \n");
            array_print(n,*X);
            printf("\n");

            printf("\n\n[A]: \n");
            matrix_print(n,n,*A);
    #endif // VERBOSE
        }
    }

    free(A);
    free(L);
    free(U);
    free(P);
    free(B);
    free(X);
    free(Y);
    free(Ainv);

    return 0;
}

/**
 * LU Decomposition
 * TODO : need to find the best pivoting strategy
 * returns the number of pivot made
**/
int LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], const short int isFpanr, double P[n][n], const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision) {
    int nbPivots = n;
    for(int j=0; j<n; ++j) {
        nbPivots += LUPivot(n, A, P, j, nbPivots-n, isFpanr, strategy, indicateur, precision);
        for(int i=0; i<n; ++i) {
            if(i<=j) {
                U[i][j]=A[i][j];
                for(int k=0; k<=i-1; ++k) {
                    U[i][j]-=L[i][k]*U[k][j];
                }
                if(i==j)
                    L[i][j]=CPREC(1.0);
                else
                    L[i][j]=CPREC(0.0);
            } else {
                L[i][j]=A[i][j];
                for(int k=0; k<=j-1; ++k) {
                    L[i][j]-=L[i][k]*U[k][j];
                }
                L[i][j]/=U[j][j];
                U[i][j]=CPREC(0.0);
            }
            // printf(" %d ", getPrecFromFpanrDouble(U[i][j]));
        }
        // printf("\n");
    }
    return nbPivots;
}

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1 
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N, 
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S    
 */
int LUPivot(const int n, double A[n][n], /*double tol,*/ double P[n][n], const int currentColumn, const int lastPivotLine, const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision) {
    int i, j, k, imax; 
    double maxA, ptr[n], absA;
    int hasPivoted = 0;
    int prec = 0, maxPrec = 0;
    size_t independantSet[n][2];

    maxA = CPREC(0.0);
    maxPrec = 0;
    imax = lastPivotLine-1;

    hungarian(n,n,A, independantSet, isFpanr, indicateur, precision);

    //for (k = currentRow; k < n; k++) {
    for ( i = 0 ; i < n ; ++i ) {
        k = independantSet[i][0];
        j = independantSet[i][1];
        // TODO : ça n'a pas de sens de faire varier les stratégies de pivot...
        switch(strategy) {
            case PS_MAX_MAG_NOT_IN_S:
                // maximum magnitude strategy not in S
                if (imax == lastPivotLine-1) {
                    for(i = lastPivotLine ; i < n ; ++i ) {
                        absA = isFpanr?myLog(myAbs(A[i][currentColumn])):log(fabs(A[i][currentColumn]));
                        if ( absA > maxA && !isInZu(n,independantSet,i,currentColumn)) {
                            maxA = absA;
                            imax = i;
                        }
                    }
                }
                break;
            case PS_MAX_MAG_IN_S:
                absA = isFpanr?myLog(myAbs(A[k][j])):log(fabs(A[k][j]));
                if (absA > maxA && k >= lastPivotLine /*&& j == currentColumn*/) { 
                    maxA = absA;
                    imax = k;
                }
                break;
            case PS_MAX_PRECISION:
                // maximum precision strategy (in S)
                assert(isFpanr /*Error : should use FPANR when computing max precision pivot strategy*/);
                prec = getPrecFromFpanrDouble(A[k][j]);
                if ( prec > maxPrec && k >= lastPivotLine /*&& j == currentColumn*/) {
                    maxPrec = prec;
                    imax = k;
                }
                break;
                    // prec = getPrecFromFpanrDouble(A[k][currentColumn]);
                    // if ( prec > maxPrec ) {
                    //     maxPrec = prec;
                    //     imax = k;
                    // }
        }
    }
        //if (maxA < Tol) return 0; //failure, matrix is degenerate

    if (imax != lastPivotLine-1) {
            //pivoting P
        array_copy(n, P[lastPivotLine], ptr);
        array_copy(n, P[imax], P[lastPivotLine]);
        array_copy(n, ptr, P[imax]);

            //pivoting rows of A
        array_copy(n, A[lastPivotLine], ptr);
        array_copy(n, A[imax], A[lastPivotLine]);
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
void LUPSolve(const size_t n, double L[n][n], double U[n][n], double Y[n], double P[n][n], double B[n], double X[n], const short int isFpanr) {
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
void LUPInvert(const int n, double U[n][n], double L[n][n], double P[n][n], double IA[n][n], const short int isFpanr, const enum INDICATEUR_ENUM indicateur, const int precision) {
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            int permut = isFpanr?getOneFpanr(n,P[i]):getOne(n,P[i]);
            if (permut == j) 
                IA[i][j] = CPREC(1.0);
            else
                IA[i][j] = CPREC(0.0);

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

char * buildFileName(enum OUTPUT_MATRIX OM, size_t n, short int index, enum PIVOT_STRATEGY strategy, enum INVERSION_ALGORITHM algorithm) {
    char * res;
    char buffer[20];

    res = malloc(MAX_FILE_NAME_LENGTH * sizeof(char));

    // sample file name : U1_n4_MAX.dat
    strcpy(res, FILE_FOLDER);

    strcat(res, "/");

    switch ( algorithm ) {
        case IA_LU:
            strcat(res,"LU");
            break;
        case IA_HUNG:
            strcat(res,"hung");
            break;
    }

    if ( OM != OM_A_INV && OM != OM_PREC ) 
        append(res, OM);
    else if ( OM == OM_A_INV ) 
        strcat(res,"A_INV");
    else
        strcat(res,"PREC");

    if(index == -1) {
        sprintf(buffer, "ref");
    } else if (index == -2) {
        sprintf(buffer, "lp");
    }else {
        sprintf(buffer, "%hi", index);
    }
    strcat(res, buffer);

    strcat(res, "_n");

    sprintf(buffer, "%zu", n);
    strcat(res, buffer);

    strcat(res, "_");

    switch(strategy) {
        case PS_MAX_MAG_NOT_IN_S:
            strcat(res, "MAX_MAG_NOT_IN_S");
            break;
        case PS_MAX_MAG_IN_S:
            strcat(res, "MAX_MAG_IN_S");
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

 /* Gauss-Jordan
     r = 0                                       (r est l'indice de ligne du dernier pivot trouvé)
     Pour j de 1 jusqu'à m                       (j décrit tous les indices de colonnes)
     |   Rechercher max(|A[i,j]|, r+1 ≤ i ≤ n). Noter k l'indice de ligne du maximum
     |                                           (A[k,j] est le pivot)
     |   Si A[k,j]≠0 alors                       (A[k,j] désigne la valeur de la ligne k et de la colonne j)
     |   |   r=r+1                               (r désigne l'indice de la future ligne servant de pivot)
     |   |   Diviser la ligne k par A[k,j]       (On normalise la ligne de pivot de façon que le pivot prenne la valeur 1)
     |   |   Échanger les lignes k et r          (On place la ligne du pivot en position r)
     |   |   Pour i de 1 jusqu'à n               (On simplifie les autres lignes)
     |   |   |   Si i≠r alors
     |   |   |   |   Soustraire à la ligne i la ligne r multipliée par A[i,j] (de façon à annuler A[i,j])
     |   |   |   Fin Si
     |   |   Fin Pour
     |   Fin Si
     Fin Pour
  Fin Gauss-Jordan */
int gaussJordanPivot(const size_t n, const size_t m, double A[n][m], const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision) {
    #if DEBUG
    printf("\ngaussJordanPivot\n");
    fflush(stdout);
    #endif
    int r = -1;
    double val;
    // size_t k;
    double max/*, ptr[m]*/;
    size_t maxI, maxJ;
    int maxPrec, prec;
    size_t independantSet[n][2];
    for ( int j = 0 ; j < m ; ++j ) {
        maxJ = j;
        #if DEBUG
        printf("\n%d : Before hung \n",j);
        fflush(stdout);
        // scanf("%d",&maxPrec);
        #endif
        hungarian(n,m,A, independantSet, isFpanr, indicateur, precision);
        #if DEBUG
        for(size_t i = 0 ; i < n ; ++i ) {
            printf("\n(%zu) : [%zu,%zu] = %f\n",i, independantSet[i][0],independantSet[i][1], A[independantSet[i][0]][independantSet[i][1]]);
            fflush(stdout);
        }
        printf("\nafter hung \n");
        // scanf("%d",&maxPrec);
        printf("\nPSMAXNOTINS?%d",strategy==PS_MAX_MAG_NOT_IN_S);
        printf("\nPSMAXINS?%d",strategy==PS_MAX_MAG_IN_S);
        printf("\nPSMAXPREC?%d",strategy==PS_MAX_PRECISION);
        fflush(stdout);
        #endif
        // we got S
        switch ( strategy ) {
            case PS_MAX_MAG_NOT_IN_S:
                // selecting the pivot of maximum magnitude (not in S)
                max = CPREC(0.0);
                for ( size_t i = r ; i < n ; ++i ) {
                   // for ( size_t j = 0 ; j < m ; ++j ) {
                        if ( A[i][j] > max && !isInZu(n,independantSet,i,j)) {
                            max = A[i][j];
                            maxI = i;
                            maxJ = j;
                        }
                   // }
                }
                // manualPivoting(n, m, A, max, maxI, maxJ, r);
                // r = maxI;
                break;
            case PS_MAX_MAG_IN_S:
                // selecting the pivot of maximum magnitude (in S)
                max = CPREC(0.0);
                for(size_t i = 0 ; i < n ; ++i ) {
                    val = A[independantSet[i][0]][independantSet[i][1]];
                    if ( val > max && ((int)independantSet[i][0]) > r /*&& ((int)independantSet[i][1]) == j*/) {
                        max = val;
                        maxI = independantSet[i][0];
                        maxJ = independantSet[i][1];
                    }
                }
                break;
            case PS_MAX_PRECISION:
                assert(isFpanr /*Error : should use FPANR when computing max precision pivot strategy*/);
                max = CPREC(0.0);
                maxPrec = 0;
                maxI = n+1;
                maxJ = m+1;
                for ( size_t i = 0 ; i < n ; ++i ) {
                    val = A[independantSet[i][0]][independantSet[i][1]];
                     prec = getPrecFromFpanrDouble(val);
                    #if DEBUG
                    printf("\nchecking (%zu,%zu) for [%zu] (lastPivotLine : %d) ; prec = %d\n, j=%d",independantSet[i][0],independantSet[i][1],i,r,prec,j);
                    fflush(stdout);
                    #endif
                   if ( prec > maxPrec && ((int)independantSet[i][0]) > r  /*&& ((int)independantSet[i][1]) == j*/ && cmpFpanrDouble(val, CPREC(0.0)) != 0) {
                        maxPrec = prec;
                        maxI = independantSet[i][0];
                        maxJ = independantSet[i][1];
                        max = A[maxI][maxJ];
                    }
                }
                // manualPivoting(n,m,A, max, maxI, maxJ, r);
                // r = maxI;
                break;
        }
        #if DEBUG
        printf("\nafter switch \n");
        fflush(stdout);
        #endif
        // rechercher max(|A[i,j]|
        // max = FPANR_ZERO;
        // for ( int i = r ; i < n ; ++i ) {
        //     if(A[i][j] > max) {
        //         max = A[i][j];
        //         k = i;
        //     }
        // }

        if ( isFpanr?(cmpFpanrDouble(max, CPREC(0.0)) != 0):(max!=CPREC(0.0))) {
            #if DEBUG
            printf("\nbefore manual Pivoting \n");
            matrix_print_fpanr(n,m,A);
            fflush(stdout);
            #endif
            r = r + 1;
            manualPivoting(n,m,A,max,maxI,maxJ,r);
            #if DEBUG
            printf("\nafter manual pivoting \n");
            matrix_print_fpanr(n,m,A);
            fflush(stdout);
            #endif
           /* r += 1;
            // diviser la ligne K par A[k][j]
            for ( size_t l = 0 ; l < m ; ++l ) {
                A[k][l] /= max;
            }
            // échanger les lignes k et r
            array_copy(n, A[k], ptr);
            array_copy(n, A[r], A[k]);
            array_copy(n, ptr, A[r]);
            for(int i = 0 ; i < n ; ++i ) {
                if ( i != r ) {
                    // Soustraire à la ligne i la ligne r multipliée par A[i,j] (de façon à annuler A[i,j])
                    for ( size_t l = 0 ; l < m ; ++l ) {
                        A[i][l] -= A[r][l]*A[i][j];
                    }
                }
            }*/
        } 
        #if DEBUG 
        else {
            fprintf(stderr,"\n\t no pivoting ............... \n");
        }
        #endif
    }
    return r;
}

void manualPivoting(const size_t n, const size_t m, double A[n][m], const double pivotValue, const size_t currentLine, const size_t currentColumn, const size_t lastPivotLine) {
    assert(lastPivotLine < n && lastPivotLine >= 0);
    assert(currentLine < n && currentLine >= 0);
    assert(currentColumn < m && currentColumn >= 0);
    double ptr[m];
    double tmp;
    #if DEBUG
    printf("\nstepx");
    printf("\nn=%zu, m=%zu, pivotValue=%F, currentLine=%zu, currentColumn=%zu, lastPivotLine=%zu\n",n,m,pivotValue,currentLine,currentColumn,lastPivotLine);
    fflush(stdout);
    #endif
    // diviser la ligne K (currentLine) par A[k][j] (pivotValue)
    for ( size_t l = 0 ; l < m ; ++l ) {
        A[currentLine][l] = A[currentLine][l] / pivotValue;
    }
    // échanger les lignes k (currentLine) et r (lastPivotLine)
    for(size_t l = 0 ; l < m ; ++l ) {
        tmp = A[currentLine][l];
        A[currentLine][l] = A[lastPivotLine][l];
        A[lastPivotLine][l] = tmp;
    }
    // array_copy(m, A[currentLine], ptr);
    // array_copy(m, A[lastPivotLine], A[currentLine]);
    // array_copy(m, ptr, A[lastPivotLine]);

    #if DEBUG
    matrix_print_fpanr(n,m,A);
    #endif
    for(size_t i = 0 ; i < n ; ++i ) {
        tmp = A[i][currentColumn];
        if ( i != lastPivotLine ) {
            // Soustraire à la ligne i la ligne r multipliée par A[i,j] (de façon à annuler A[i,j])
            for ( size_t l = 0 ; l < m ; ++l ) {
                #if DEBUG
                printf("\ni:%zu,l:%zu,lastPivotLine:%zu,currentColumn:%zu\n\t%F = %F - (%F * %F)",i,l,lastPivotLine,currentColumn,A[i][l],A[i][l],A[lastPivotLine][l],tmp);
                #endif // DEBUG
                A[i][l] = A[i][l] - (A[lastPivotLine][l]*tmp);
                #if DEBUG
                printf(" = %F",A[i][l]);
                #endif // DEBUG
            }
        }
    }

    #if DEBUG
    printf("\nsuccess");
    fflush(stdout);
    #endif
}

// invert the matrix A and put the result in Ainv
void gaussJordanInversion(const size_t n, const size_t m, const double A[n][m], double Ainv[n][m], const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision) {
    const size_t height = m+m;
    // adding identity matrix to the end
    double (*B)[n][height];
    matrix_alloc(n,height,&B);
    for(int i = 0 ; i < n ; ++i ) {
        for(int j = 0 ; j < height ; ++j ) {
            if(j<m) {
                (*B)[i][j] = A[i][j];
            } else {
                if(i==j-m) {
                    (*B)[i][j] = CPREC(1.0); //FPANR_ONE;
                } else {
                    (*B)[i][j] = CPREC(0.0);
                }
            }
        }
    }
    #if DEBUG
    printf("\nA??\n");
    matrix_print_fpanr(n,m,A);
    printf("\nfirst B:\n");
    matrix_print_fpanr(n,height,*B);
    #endif // DEBUG
    int r = gaussJordanPivot(n, height, *B, isFpanr, strategy, indicateur, precision);
    if ( r == 0 ) {
        fprintf(stderr, "\n***********\nDidn't pivot at all....\n***********\n");
    }
    #if DEBUG
    matrix_print_fpanr(n,height,*B);
    fflush(stdout);
    printf("\nend pivot inversion");
    fflush(stdout);
    #endif
    for(size_t i = 0 ; i < n ; ++i ) {
        for (size_t j = 0 ; j < m ; ++j ) {
            #if DEBUG
            printf("\n[%zu,%zu] B=%F",i,j,(*B)[i][j+m]);
            fflush(stdout);
            #endif
            // FIXME Ainv seems to be impossible to write into
            Ainv[i][j] = (*B)[i][j+m];
        }
    }

    free(B);
}