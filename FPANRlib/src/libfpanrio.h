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

// --------------------------------------

float fpanrToFloat(const float fpanrVal);
float floatToFpanr(const float floatVal);
float floatToFpanrWithPrec(const float floatVal, const int prec);

double fpanrToDouble(const double fpanrVal);
double doubleToFpanr(const double doubleVal);
double doubleToFpanrWithPrec(const double doubleVal, const int prec);

unsigned count_trailing_zeros(const unsigned long n) ;
void f_setPrec(float_st * _this, int prec) ;
void d_setPrec(double_st * _this, int prec) ;
void f_setPrecMax(float_st * _this) ;
void d_setPrecMax(double_st * _this) ;
unsigned f_getPrec(const float_st _this) ;
unsigned d_getPrec(const double_st _this) ;
float f_getVal(float_st _this, int *prec) ;
double d_getVal(const double_st _this, int *prec) ;
void f_set(float_st * dest, const float_st source);
void d_set(double_st * dest, const double_st source);


#endif /* SRC_LIBFPANR_LIBFPANR_H_ */
