/*
 * libfpanr.h
 *
 *  Created on: 5 sept. 2018
 *      Author: Christophe Pont
 */

#ifndef SRC_LIBFPANR_LIBFPANR_H_
#define SRC_LIBFPANR_LIBFPANR_H_

#include "ieee754.h"

struct mca_interface_t;
extern struct mca_interface_t fpanr_interface;

typedef struct {
	double _value;
}double_st;

typedef struct {
	float _value;
}float_st;

unsigned count_trailing_zeros(const unsigned long n) ;
void f_setPrec(float_st * fpanrFVal, int prec) ;
void d_setPrec(double_st * fpanrDVal, int prec) ;
void f_setPrecMax(float_st * fpanrFVal) ;
void d_setPrecMax(double_st * fpanrDVal) ;
unsigned f_getPrec(float_st fpanrFVal) ;
unsigned d_getPrec(double_st fpanrDVal) ;
float f_getVal(const float_st fpanrFVal, int *prec) ;
double d_getVal(const double_st fpanrDVal, int *prec) ;
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

#endif /* SRC_LIBFPANR_LIBFPANR_H_ */
