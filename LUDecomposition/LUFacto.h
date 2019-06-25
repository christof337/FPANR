#ifndef LUFACTO_H
#define LUFACTO_H

int computeMatrix(size_t n, short int isFpanr);
void LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], short int isFpanr, double P[n][n]);
int LUPivot(int n, double A[n][n], /*double tol,*/ double P[n][n], int currentRow, short int isFpanr);
void LUPSolve(size_t n, double L[n][n], double U[n][n], double Y[n], double P[n][n], double B[n], double X[n], short int isFpanr);
void LUPInvert(int n, double U[n][n], double L[n][n], double P[n][n], double IA[n][n], short int isFpanr);
double LUPDeterminant(size_t n, double A[n][n], int nbPivots);

#endif // LUFACTO_H