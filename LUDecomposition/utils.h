
#ifndef UTILS_H
#define UTILS_H

#define dtfp(v) doubleToFpanr(v)
#define fptd(v) fpanrToDouble(v)
#define dtfpwp(v,p) doubleToFpanrWithPrec(v,p)

#define DEFAULT_RANDOM_RANGE 2

double myAbs(const double a);
double myLog(const double a);

// ---------------------------------------------------------------------------------------
// ARRAYS

void array_alloc (const size_t x, double(**aptr)[x]);
void array_fill (const size_t x, double array[x]);
void arrayFillExp(const size_t x, double array[x]);
int getOne(const size_t n, const double array[n]);
void array_print (const size_t x, const double array[x]);
void array_copy(const size_t n, const double source[n], double dest[n]);

// ---------------------------------------------------------------------------------------
// MATRICES

void matrix_alloc (const size_t x, const size_t y, double(**aptr)[x][y]);
void matrix_fill (const size_t x, const size_t y, double matrix[x][y]);
void permutation_matrix_fill (const size_t x, const size_t y, double matrix[x][y]);
void hilbert(const size_t x, const size_t y, double matrix[x][y]) ;
void matrixFillId(const size_t n, double matrix[n][n]);
void fill_fig1(double matrix[3][3]);
void fill_fig2(double matrix[3][3]);
void matrix_mult(const size_t n, const size_t m, const size_t p, double (**result)[n][p], const double A[n][m], const double B[m][p]);
void matrix_print (const size_t x, const size_t y, const double matrix[x][y]);
void perturbateMatrix(const size_t n, const size_t m, double A[n][n], const int perturbation);

// ---------------------------------------------------------------------------------------
// FPANR

void array_fill_fpanr (const size_t x, double array[x]);
void array_fill_fpanr_with_prec (const size_t x, double array[x], const int precision);
void arrayFillExp_fpanr(const size_t x, double array[x]) ;
int getOneFpanr(const size_t n, const double array[n]);
void array_print_fpanr (const size_t x, const double array[x]);
void matrixFillId_fpanr(const size_t n, double array[n][n]);
void matrix_fill_fpanr (const size_t x, const size_t y, double matrix[x][y]);
void matrix_fill_fpanr_with_prec (const size_t x, const size_t y, double matrix[x][y], const int precision);
void permutation_matrix_fill_fpanr (const size_t x, const size_t y, double matrix[x][y]);
void permutation_matrix_fill_fpanr_with_prec (const size_t x, const size_t y, double matrix[x][y], const int precision);
void hilbert_fpanr(const size_t x, const size_t y, double matrix[x][y]) ;
void fill_fig1_fpanr(double matrix[3][3]);
void fill_fig2_fpanr(double matrix[3][3]);
void matrix_mult_fpanr(const size_t n, const size_t m, const size_t p, double (**result)[n][p], const double A[n][m], const double B[m][p]);
void matrix_print_fpanr (const size_t x, const size_t y, const double matrix[x][y]);
void perturbateMatrix_fpanr(const size_t n, const size_t m, double A[n][n], const int perturbation);

// miscellaneous
void append(char* s, const char c);
int getRandomValue(const int range);
int isInZu(size_t n, size_t S[n][2], int i, int j);

#endif // UTILS_H