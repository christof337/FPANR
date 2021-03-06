#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<string.h>
#include<time.h>

#include "utils.h"

#include "libfpanrio.h"

#define TRUE 1
#define FALSE 0

double myAbs(const double a) {
	double_st res, val;
	val._value = a;
	d_fabs(&res, val);
	return res._value;
}

double myLog(const double a) {
	double_st res, val;
	val._value = a;
	d_log(&res, val);
	return res._value;
}

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
void array_alloc (const size_t x, double(**aptr)[x])
{
	*aptr = malloc( sizeof(double[x]) ); // allocate a true 1D array
	assert(*aptr != NULL);
}

/**
 * Fills an array with 0
 * @param x size of the array
 * @param array the array to fill
 */
void array_fill (const size_t x, double array[x])
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
void arrayFillExp(const size_t x, double array[x]) {
	for(size_t i=0; i<x; ++i) {
		array[i] = exp(i/3.0);
	}
}

/**
 * Print an array to stdout
 * @param x size of the array
 * @param array the array to print
 */
void array_print (const size_t x, const double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		printf("%9f ", array[i]);
	}
	printf("\n");
}

void array_copy(const size_t n, const double source[n], double dest[n]) {
	for (size_t i = 0 ; i < n ; ++i) {
		dest[i] = source[i];
	}
}

// return the index of the first 1 encoutered
int getOne(const size_t n, const double array[n]) {
	int i = 0;
	while ( i < n ) {
		if (array[i] == 1.0) {
			return i;
		}
		i++;
	}

	return -1;
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
void matrix_alloc (const size_t x, const size_t y, double(**aptr)[x][y])
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
void matrix_fill (const size_t x, const size_t y, double matrix[x][y])
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
 * Fills a permutation matrix with 1 on the diagonal and 0 elsewhere
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill
 */
void permutation_matrix_fill (const size_t x, const size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			if (i==j) {
				matrix[i][j] = 1;
			} else {
				matrix[i][j] = 0;
			}
		}
	}
}

/**
 * Fills a matrix using hilbert's method
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill in respect to Hilbert
 */
void hilbert(const size_t x, const size_t y, double matrix[x][y]) {
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = 1.0/((i+1)+(j+1));
		}
	}
}

/**
 * Fills an array with an identity matrix.
 * matrix should be filled with zeros
 */
void matrixFillId(const size_t n, double matrix[n][n]) {
	for ( int j = 0 ; j < n ; ++j ) {
		matrix[j][j] = 1.0;
	}
}

void fill_fig1(double matrix[3][3]) {
	matrix[0][0] = 3000;
	matrix[0][1] = 1200;
	matrix[0][2] = 330;
	matrix[1][0] = 100;
	matrix[1][1] = 9;
	matrix[1][2] = 900;
	matrix[2][0] = 1500;
	matrix[2][1] = 0.1;
	matrix[2][2] = 0.55;
}


void fill_fig2(double matrix[3][3]) {
	matrix[0][0] = 25.0;
	matrix[0][1] = 3.3;
	matrix[0][2] = 2.0;
	matrix[1][0] = 6.0;
	matrix[1][1] = 1.6;
	matrix[1][2] = 3.86;
	matrix[2][0] = 0.82;
	matrix[2][1] = 4.0;
	matrix[2][2] = 9.6;
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
void matrix_mult(const size_t n, const size_t m, const size_t p, double (**result)[n][p], const double A[n][m], const double B[m][p]) {
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
void matrix_print (const size_t x, const size_t y, const double matrix[x][y])
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

void perturbateMatrix(const size_t n, const size_t m, double A[n][n], const int perturbationStage) {
	int val;
	double perturbation = 1.0 / 2.0 * pow(2, -perturbationStage);
	for ( size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			val = getRandomValue(DEFAULT_RANDOM_RANGE); // 0 or 1
			val = 2*val - 1 ; // -1 or 1
			A[i][j] += (val * perturbation);
		}
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
void array_fill_fpanr (const size_t x, double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		array[i] = dtfp(0.0);
	}
}

/**
 * Fills an array with 0 FPANR way at a given precision
 * @param x
 * @param array
 */
void array_fill_fpanr_with_prec (const size_t x, double array[x], const int precision)
{
	for(size_t i=0; i<x; ++i)
	{
		array[i] = dtfpwp(0.0, precision);
	}
}

/**
 * Fills an array with each a_{i} being equal to e^{i/3} fpanr way
 * Mostly used to fill an array with values.
 * @param x size of the array
 * @param array the array to fill exponentially
 */
void arrayFillExp_fpanr(const size_t x, double array[x]) {
	for(size_t i=0; i<x; ++i) {
		array[i] = dtfp(exp(i/3.0));
	}
}

/**
 * Fills a matrix with an identity matrix fpanrway. Matrix should be filled with zeros
 */
void matrixFillId_fpanr(const size_t n, double matrix[n][n]) {
	for ( int j = 0 ; j < n ; ++j ) {
		matrix[j][j] = dtfp(1.0);
	}
}

// return the index of the first 1 encoutered
int getOneFpanr(const size_t n, const double array[n]) {
	int i = 0;
	while ( i < n ) {
		if (array[i] == dtfp(1.0)) {
			return i;
		}
		i++;
	}
	return -1;
}

/**
 * Print an array to stdout in respect to FPANR output format, 
 * using fpanrDoubleToStr to retrieve the correct value AND the computed precision
 * @param x size of the array
 * @param array the array to print
 */
void array_print_fpanr (const size_t x, const double array[x])
{
	for(size_t i=0; i<x; ++i)
	{
		char * chaine = fpanrDoubleToStr(array[i]);
		assert(chaine != NULL);
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
void matrix_fill_fpanr (const size_t x, const size_t y, double matrix[x][y])
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
 * Fills a matrix with 0 fpanr way at a given precision
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param matrix
 */
void matrix_fill_fpanr_with_prec (const size_t x, const size_t y, double matrix[x][y], const int precision)
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			matrix[i][j] = dtfpwp(0.0,precision);
		}
	}
}

/**
 * Fills a permutation matrix with 1 on the diagonal and 0 elsewhere fpanr way
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param matrix
 */
void permutation_matrix_fill_fpanr (const size_t x, const size_t y, double matrix[x][y])
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			if ( i == j ) {
				matrix[i][j] = dtfp(1.0);
			} else {
				matrix[i][j] = dtfp(0.0);
			}
		}
	}
}


/**
 * Fills a permutation matrix with 1 on the diagonal and 0 elsewhere fpanr way
 * https://stackoverflow.com/questions/42094465/correctly-allocating-multi-dimensional-arrays
 * @param x
 * @param y
 * @param matrix
 */
void permutation_matrix_fill_fpanr_with_prec (const size_t x, const size_t y, double matrix[x][y], const int precision)
{
	for(size_t i=0; i<x; ++i)
	{
		for(size_t j=0; j<y; ++j)
		{
			if ( i == j ) {
				matrix[i][j] = dtfpwp(1.0,precision);
			} else {
				matrix[i][j] = dtfpwp(0.0,precision);
			}
		}
	}
}

/**
 * Fills a matrix using hilbert's method fpanrway
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill in respect to Hilbert
 */
void hilbert_fpanr(const size_t x, const size_t y, double matrix[x][y]) {
	for(int i=x; i>0; --i) {
		for(int j=y; j>0; --j) {
			matrix[i-1][j-1] = dtfp(1.0)/dtfp((x-i+1)+(y-j+1));
		}
	}
}

/**
 * Fills a matrix using hilbert's method fpanr way at given precision
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to fill in respect to Hilbert
 */
void hilbert_fpanr_with_prec(const size_t x, const size_t y, double matrix[x][y], const int precision) {
	for(int i=x; i>0; --i) {
		for(int j=y; j>0; --j) {
			matrix[i-1][j-1] = dtfpwp(1.0,precision)/dtfpwp((x-i+1)+(y-j+1),precision);
		}
	}
}

/*
for(size_t i=0; i<x; ++i)
{
	for(size_t j=0; j<y; ++j)
	{
		matrix[i][j] = dtfp(1.0)/dtfp((i+1)+(j+1));
	}
}
*/

void fill_fig1_fpanr(double matrix[3][3]) {
	fill_fig1_fpanr_with_prec(matrix, 51);
}


void fill_fig2_fpanr(double matrix[3][3]) {
	fill_fig2_fpanr_with_prec(matrix, 51);
}


void fill_fig1_fpanr_with_prec(double matrix[3][3], const int precision) {
	int ref = 51;
	matrix[0][0] = doubleToFpanrWithPrec(3000.0,precision-15);
	matrix[0][1] = doubleToFpanrWithPrec(1200.0,precision-3);
	matrix[0][2] = doubleToFpanrWithPrec(330.0,precision-6);
	matrix[1][0] = doubleToFpanrWithPrec(100.0,precision-3);
	matrix[1][1] = doubleToFpanrWithPrec(9.0,precision-3);
	matrix[1][2] = doubleToFpanrWithPrec(900.0,precision-3);
	matrix[2][0] = doubleToFpanrWithPrec(1500.0,precision-2);
	matrix[2][1] = doubleToFpanrWithPrec(0.1,precision-4);
	matrix[2][2] = doubleToFpanrWithPrec(0.55,precision-5);
}


void fill_fig2_fpanr_with_prec(double matrix[3][3], const int precision) {
	int ref = 51;
	matrix[0][0] = doubleToFpanrWithPrec(25.0,precision-15);
	matrix[0][1] = doubleToFpanrWithPrec(3.3,precision-3);
	matrix[0][2] = doubleToFpanrWithPrec(2.0,precision-5);
	matrix[1][0] = doubleToFpanrWithPrec(6.0,precision-4);
	matrix[1][1] = doubleToFpanrWithPrec(1.6,precision-4);
	matrix[1][2] = doubleToFpanrWithPrec(3.86,precision-5);
	matrix[2][0] = doubleToFpanrWithPrec(0.82,precision-4);
	matrix[2][1] = doubleToFpanrWithPrec(4.0,precision-4);
	matrix[2][2] = doubleToFpanrWithPrec(9.6,precision-3);
}


/**
 * Multiply the matrix A with B and put the result in result fpanrway.
 * @param n number of lines of A
 * @param m number of columns of A and number of lines of B
 * @param p number of columns of B
 * @param result a pointer to the adress of an empty matrix that will be filled with the result of the multiplication
 * @param A the first matrix in the product
 * @param B the second matrix in the product
 */
void matrix_mult_fpanr(const size_t n, const size_t m, const size_t p, double (**result)[n][p], const double A[n][m], const double B[m][p]) {
	matrix_alloc(n,m,result);
	for (int i=0; i<n; ++i) {
		for (int j=0; j<p; ++j) {
			(**result)[i][j]=dtfp(0.0);
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
void matrix_print_fpanr (const size_t x, const size_t y, const double matrix[x][y]) {
	for(size_t i=0; i<x; ++i) {
		for(size_t j=0; j<y; ++j) {
			// printf("\nbefore %zu,%zu",i,j);
			// fflush(stdout);
			// printf(": %F : ",matrix[i][j]);
			// fflush(stdout);
			char * chaine = fpanrDoubleToStr(matrix[i][j]);
			assert(chaine != NULL);
			printf ( "%s\t", chaine );
			free(chaine);
		}
		printf("\n");
	}
}

/*
 * Perturbate a matrix to the `perturbation`'th stage
 */
void perturbateMatrix_fpanr(const size_t n, const size_t m, double A[n][n], const int perturbationStage) {
	double val;
	int sign;
	double perturbation = dtfp(1.0) / dtfp(2.0) * dtfp(pow(2, -perturbationStage));

	for ( size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			sign = getRandomValue(DEFAULT_RANDOM_RANGE); // 0 or 1
			val = dtfp(2*sign - 1) ; // -1 or 1
			A[i][j] = A[i][j] + (val * perturbation);
		}
	}
}

// ---------------------------------------------------------------------------------------
// miscellaneous
//

/**
 * append a char to the end of a string
 */
void append(char* s, const char c) {
	int len = strlen(s);
	s[len] = c;
	s[len+1] = '\0';
}

/**
 * generates a random int between 0 and range
 * srandom need to have been call earlier
 */
int getRandomValue(const int range) {
	//time_t t;

   	/* Intializes random number generator */
	//srand((unsigned) time(&t));
	//srandom((unsigned) time(&t));

	return random() % range;
}

int isInZu(const size_t n, const size_t S[n][2], const int i, const int j) {
	for ( int k = 0 ; k < n ; ++k ) {
		if(S[k][0] == i && S[k][1] == j ) {
			return TRUE;
		} 
	}
	return FALSE;
}