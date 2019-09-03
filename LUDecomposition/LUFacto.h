#ifndef LUFACTO_H
#define LUFACTO_H

#include "hungarian.h"

#define FPANR_ZERO isFpanr?dtfp(0.0):0.0
#define FPANR_ONE isFpanr?dtfp(1.0):1.0
#define DEFAULT_LOW_PRECISION 15
#define PREC_MAX_DOUBLE 51

enum PIVOT_STRATEGY { PS_MAX_MAG_NOT_IN_S=0, PS_MAX_MAG_IN_S, PS_MAX_PRECISION };
enum OUTPUT_MATRIX { OM_L='L', OM_U='U', OM_Y='Y', OM_X='X', OM_A_INV, OM_PREC, OM_DIST};
enum INPUT_MATRIX { MAT_1=0, MAT_2, MAT_HILBERT};


enum INVERSION_ALGORITHM { IA_LU=0, IA_HUNG };

extern enum OUTPUT_MATRIX OM;
extern enum PIVOT_STRATEGY strategy;


int computeMatrix(const size_t n, const short int isFpanr, const short int index, const enum PIVOT_STRATEGY strategy, const enum INVERSION_ALGORITHM algorithm, const enum INPUT_MATRIX matrix, const enum INDICATEUR_ENUM indicateur, const int precision );
int LU_decomposition(const size_t n, double U[n][n], double A[n][n], double L[n][n], const short int isFpanr, double P[n][n], const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision);
int LUPivot(const int n, double A[n][n], /*double tol,*/ double P[n][n], const int currentColumn, const int lastPivotLine, const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision);
void LUPSolve(const size_t n, double L[n][n], double U[n][n], double Y[n], double P[n][n], double B[n], double X[n], const short int isFpanr);
void LUPInvert(const int n, double U[n][n], double L[n][n], double P[n][n], double IA[n][n], const short int isFpanr, const enum INDICATEUR_ENUM indicateur, const int precision);
double LUPDeterminant(const size_t n, double A[n][n], const int nbPivots);
char * buildFileName(const enum OUTPUT_MATRIX OM, const size_t n, const short int index, const enum PIVOT_STRATEGY strategy, const enum INVERSION_ALGORITHM algorithm);
int gaussJordanPivot(const size_t n, const size_t m, double A[n][m], const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision);
void gaussJordanInversion(const size_t n, const size_t m, const double A[n][m], double Ainv[n][m], const short int isFpanr, const enum PIVOT_STRATEGY strategy, const enum INDICATEUR_ENUM indicateur, const int precision);

void manualPivoting(const size_t n, const size_t m, double A[n][m], const double pivotValue, const size_t currentLine, const size_t currentColumn, const size_t lastPivotLine);

#endif // LUFACTO_H
