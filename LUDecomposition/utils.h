
#ifndef UTILS_H
#define UTILS_H

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

#define dtfp(v) doubleToFpanr(v)
#define fptd(v) fpanrToDouble(v)

// ---------------------------------------------------------------------------------------
// ARRAYS

void array_alloc (size_t x, double(**aptr)[x]);
void array_fill (size_t x, double array[x]);
void arrayFillExp(size_t x, double array[x]);
void array_print (size_t x, double array[x]);

// ---------------------------------------------------------------------------------------
// MATRICES

void matrix_alloc (size_t x, size_t y, double(**aptr)[x][y]);
void matrix_fill (size_t x, size_t y, double matrix[x][y]);
void hilbert(size_t x, size_t y, double matrix[x][y]) ;
void matrix_mult(size_t n, size_t m, size_t p, double (**result)[n][p], double A[n][m], double B[m][p]);
void matrix_print (size_t x, size_t y, double matrix[x][y]);

// ---------------------------------------------------------------------------------------
// FPANR

void array_fill_fpanr (size_t x, double array[x]);
void arrayFillExp_fpanr(size_t x, double array[x]) ;
void array_print_fpanr (size_t x, double array[x]);
void matrix_fill_fpanr (size_t x, size_t y, double matrix[x][y]);
void hilbert_fpanr(size_t x, size_t y, double matrix[x][y]) ;
void matrix_print_fpanr (size_t x, size_t y, double matrix[x][y]);

#endif // UTILS_H