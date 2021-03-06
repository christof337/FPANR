#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <stdio.h>

#define MIN(A,B) A<B?A:B
#define MAX(A,B) A>B?A:B
#define CPREC(a) indicateur==IE_LOW_PREC?dtfpwp(a,precision):(isFpanr?dtfp(a):a)

enum INDICATEUR_ENUM { IE_PERTURBED=0, IE_LOW_PREC};

int hungarian(const size_t n, const size_t m, double matrix[n][m], size_t independantSet[MIN(n,m)][2], short int isFpanr, const enum INDICATEUR_ENUM indicateur, const int precision);
short int rowContainsTrue(const size_t n, const size_t m, const size_t row, const short int matrix[n][m]);
short int columnContainsTrue(const size_t n, const size_t m, const size_t column, const short int matrix[n][m]);
void setRow(const size_t n, const size_t m, const size_t row, short int matrix[n][m], const short int val);
void setColumn(const size_t n, const size_t m, const size_t column, short int matrix[n][m], const short int val) ;
short int isCoveredRow(const size_t n, const size_t row, const short int matrix[n]);
short int isCoveredColumn(const size_t m, const size_t column, const short int matrix[m]);
void cusPrintA(const size_t n, const short int a[n]);
void cusPrintM(const size_t n, const size_t m, const short int mat[n][m]);
 
void cusPrintMZu(const size_t n, const size_t m, const size_t mat[n][m]);
#endif // HUNGARIAN_H
