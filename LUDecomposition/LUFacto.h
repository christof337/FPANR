#ifndef LUFACTO_H
#define LUFACTO_H

enum PIVOT_STRATEGY { PS_MAX=0, PS_MAX_PRECISION };
enum OUTPUT_MATRIX { OM_L='L', OM_U='U', OM_Y='Y', OM_X='X', OM_A_INV};

extern enum OUTPUT_MATRIX OM;
extern enum PIVOT_STRATEGY strategy;

int computeMatrix(size_t n, short int isFpanr, short int index, enum PIVOT_STRATEGY strategy);
int LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], short int isFpanr, double P[n][n], enum PIVOT_STRATEGY strategy);
int LUPivot(int n, double A[n][n], /*double tol,*/ double P[n][n], int currentRow, short int isFpanr, enum PIVOT_STRATEGY strategy);
void LUPSolve(size_t n, double L[n][n], double U[n][n], double Y[n], double P[n][n], double B[n], double X[n], short int isFpanr);
void LUPInvert(int n, double U[n][n], double L[n][n], double P[n][n], double IA[n][n], short int isFpanr);
double LUPDeterminant(size_t n, double A[n][n], int nbPivots);
char * buildFileName(enum OUTPUT_MATRIX OM, size_t n, short int index, enum PIVOT_STRATEGY strategy);

#endif // LUFACTO_H
