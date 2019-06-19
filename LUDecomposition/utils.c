#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>

#include "utils.h"
#include "libfpanrio.h"

// ---------------------------------------------------------------------------------------
// 
// ARRAYS
//
//

/**
 * Allocate a 1D array
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x size of the array
 * @param aptr pointer to the adress of the array
 */
void array_alloc (size_t x, double(**aptr)[x])
{
	*aptr = malloc( sizeof(double[x]) ); // allocate a true 1D array
	assert(*aptr != NULL);
}

/**
 * Fills an array with 0
 * @param x size of the array
 * @param array the array to fill
 */
void array_fill (size_t x, double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		array[i] = 0;
	}
}

/**
 * Fills an array with each a_{i} being equal to e^{i/3}
 * Mostly used to fill an array with values.
 * @param x size of the array
 * @param array the array to fill exponentially
 */
void arrayFillExp(size_t x, double array[x]) {
	for(size_t i=0; i<x; ++i) {
		array[i] = exp(i/3.0);
	}
}

/**
 * Print an array to stdout
 * @param x size of the array
 * @param array the array to print
 */
void array_print (size_t x, double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		printf("%9f ", array[i]);
	}
	printf("\n");
}

// ---------------------------------------------------------------------------------------
// 
// MATRICES
//
//

/**
 * Allocate a 2D matrix
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x number of lines
 * @param y number of columns
 * @param aptr pointer to the adress of the matrix
 */
void matrix_alloc (size_t x, size_t y, double(**aptr)[x][y])
{
	*aptr = malloc( sizeof(double[x][y]) ); // allocate a true 2D array
	assert(*aptr != NULL);
}

/**
 * Fills a matrix with 0
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill
 */
void matrix_fill (size_t x, size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

/**
 * Fills a matrix using hilbert's method
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill in respect to Hilbert
 */
void hilbert(size_t x, size_t y, double matrix[x][y]) {
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = 1.0/((i+1)+(j+1));
		}
	}
}

/**
 * Multiply the matrix A with B and put the result in result.
 * @param n number of lines of A
 * @param m number of columns of A and number of lines of B
 * @param p number of columns of B
 * @param result a pointer to the adress of an empty matrix that will be filled with the result of the multiplication
 * @param A the first matrix in the product
 * @param B the second matrix in the product
 */
void matrix_mult(size_t n, size_t m, size_t p, double (**result)[n][p], double A[n][m], double B[m][p]) {
	matrix_alloc(n,m,result);
	for (int i=0; i<n; ++i) {
		for (int j=0; j<p; ++j) {
			(**result)[i][j]=0;
			for (int k=0; k<m; ++k) {
				(**result)[i][j] += A[i][k]*B[k][j];
			}
		}
	}
}

/**
 * Print a matrix to stdout
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to print
 */
void matrix_print (size_t x, size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			printf("%9f ", matrix[i][j]);
		}
		printf("\n");
	}
}

// ---------------------------------------------------------------------------------------
// 
// FPANR
//
//

/**
 * Fills an array with 0 FPANR way
 * @param x
 * @param array
 */
void array_fill_fpanr (size_t x, double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		array[i] = dtfp(0.0);
	}
}

/**
 * Fills an array with each a_{i} being equal to e^{i/3} fpanr way
 * Mostly used to fill an array with values.
 * @param x size of the array
 * @param array the array to fill exponentially
 */
void arrayFillExp_fpanr(size_t x, double array[x]) {
	for(size_t i=0; i<x; ++i) {
		array[i] = dtfp(exp(i/3.0));
	}
}

/**
 * Print an array to stdout in respect to FPANR output format, 
 * using fpanrDoubleToStr to retrieve the correct value AND the computed precision
 * @param x size of the array
 * @param array the array to print
 */
void array_print_fpanr (size_t x, double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		char * chaine = fpanrDoubleToStr(array[i]);
		printf ( "%s\t", chaine );
		free(chaine);
	}
	printf("\n");
}


/**
 * Fills a matrix with 0 fpanr way
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param matrix
 */
void matrix_fill_fpanr (size_t x, size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = dtfp(0.0);
		}
	}
}

/**
 * Fills a matrix using hilbert's method
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill in respect to Hilbert
 */
void hilbert_fpanr(size_t x, size_t y, double matrix[x][y]) {
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = dtfp(1.0)/dtfp((i+1)+(j+1));
		}
	}
}

/**
 * Print a matrix to stdout
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to print
 */
void matrix_print_fpanr (size_t x, size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
  			char * chaine = fpanrDoubleToStr(matrix[i][j]);
  			printf ( "%s\t", chaine );
  			free(chaine);
		}
		printf("\n");
	}
}