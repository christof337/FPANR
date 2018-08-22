#include "ieee754.h"

typedef struct {
	double _value;
}double_st;

typedef struct {
	float _value;
}float_st;

unsigned count_trailing_zeros(unsigned long n) ;
void f_setPrec(float_st * _this, int prec) ;
void d_setPrec(double_st * _this, int prec) ;
void f_setPrecMax(float_st * _this) ;
void d_setPrecMax(double_st * _this) ;
unsigned f_getPrec(float_st _this) ;
unsigned d_getPrec(double_st _this) ;
float f_getVal(float_st _this, int *prec) ;
double d_getVal(const double_st _this, int *prec) ;
void f_set(float_st * dest, const float_st source);
void d_set(double_st * dest, const double_st source);

// binary
void f_add(float_st * res, const float_st a, const float_st b) ;
void d_add(double_st * res, const double_st a, const double_st b);
void f_sub(float_st * res, const float_st a, const float_st b);
void d_sub(double_st * res, const double_st a, const double_st b);
void f_mul(float_st * res, const float_st a, const float_st b);
void d_mul(double_st * res, const double_st a, const double_st b);
void f_div(float_st * res, const float_st a, const float_st b);
void d_div(double_st * res, const double_st a, const double_st b);

 // unary
//void f_abs(float_st * res, const float_st a);
//void d_abs(double_st * res, const double_st a);
void f_fabs(float_st * res, const float_st a);
void d_fabs(double_st * res, const double_st a);
void f_sqrt(float_st * res, const float_st a);
void d_sqrt(double_st * res, const double_st a);
void f_exp(float_st * res, const float_st a);
void d_exp(double_st * res, const double_st a);
void f_log(float_st * res, const float_st a);
void d_log(double_st * res, const double_st a);
void f_cos(float_st * res, const float_st a);
void d_cos(double_st * res, const double_st a);
void f_sin(float_st * res, const float_st a);
void d_sin(double_st * res, const double_st a);


/************************* FPHOOKS FUNCTIONS *************************
* These functions correspond to those inserted into the source code
* during source to source compilation and are replacement to floating
* point operators
**********************************************************************/

static float _floatadd(float _a, float _b) ;
static float _floatsub(float _a, float _b) ;
static float _floatmul(float _a, float _b) ;
static float _floatdiv(float _a, float _b) ;
static double _doubleadd(double _a, double _b) ;
static double _doublesub(double _a, double _b) ;
static double _doublemul(double _a, double _b) ;
static double _doublediv(double _a, double _b) ;

