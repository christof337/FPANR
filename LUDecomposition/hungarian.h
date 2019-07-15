#ifndef HUNGARIAN_H
#define HUNGARIAN_H

#include <stdio.h>

#define MIN(A,B) A<B?A:B

int hungarian(const size_t n, const size_t m, double matrix[n][m], size_t independantSet[MIN(n,m)][2]);
short int rowContainsTrue(const size_t n, const size_t m, const size_t row, const short int matrix[n][m]);
short int columnContainsTrue(const size_t n, const size_t m, const size_t column, const short int matrix[n][m]);
void setRow(const size_t n, const size_t m, const size_t row, short int matrix[n][m], const short int val);
void setColumn(const size_t n, const size_t m, const size_t column, short int matrix[n][m], const short int val) ;
short int isCoveredRow(const size_t n, const size_t row, const short int matrix[n]);
short int isCoveredColumn(const size_t m, const size_t column, const short int matrix[m]);
 
#endif // HUNGARIAN_H
