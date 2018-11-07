/*
 ============================================================================
 Name        : fpanrlib.c
 Author      : Christophe Pont
 Version     : 0.2
 Copyright   : GPL3
 Description : Library of FPANR implementation
 ============================================================================
 */

// This file is part of the Floating-Point Adaptive Noise Reduction Library, (FPANR).
// FPANR is free software: you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program.  If not, see <http://www.gnu.org/licenses/>.
#include <math.h>
#include <stdio.h>

#include "ieee754.h"

#include "libfpanrio.h"

#define MAX(A,B) (((A)>(B)) ? (A) : (B))
#define MIN(A,B) (((A)<(B)) ? (A) : (B))

/**
 * Manual handling of max precisions.
 * TODO : use a system call to learn the actual mantissa maximum length.
 */
#define PREC_MAX_FLOAT 22
#define PREC_MAX_DOUBLE 51

/**
 * Switch DEBUG to 1 if you want to have a verbose output.
 */
#define DEBUG 0

// --------------------------------------

/**
 * Convert the given fpanr value into a readable and exportable IEEE754 float.
 */
float fpanrToFloat(const float fpanrVal) {
#if DEBUG
	printf("\t fpanrToFloat");
#endif
	int prec;
	float_st fpanrVal_st;
	fpanrVal_st._value = fpanrVal;
	return f_getVal(fpanrVal_st, &prec);
}

float floatToFpanr(const float floatVal) {
#if DEBUG
	printf("\t floatToFpanr");
#endif
	return floatToFpanrWithPrec(floatVal, PREC_MAX_FLOAT);
}

float floatToFpanrWithPrec(const float floatVal, const int prec) {
#if DEBUG
	printf("\t floatToFpanrWithPrec");
#endif
	float_st fpanrVal;
	fpanrVal._value = floatVal;
	f_setPrec(&fpanrVal, prec);
	return fpanrVal._value;
}

unsigned getPrecFromFpanrFloat(const float floatVal) {
#if DEBUG
	printf("\t getFpanrFloatPrec");
#endif
	float_st fpanrVal;
	fpanrVal._value = floatVal;
	return f_getPrec(fpanrVal);
}

double fpanrToDouble(const double fpanrVal) {
#if DEBUG
	printf("\t fpanrToDouble - début");
#endif
	int prec;
	double_st fpanrVal_st;
	fpanrVal_st._value = fpanrVal;
#if DEBUG
	printf("\t fpanrToDouble - fin");
#endif
	return d_getVal(fpanrVal_st, &prec);
}

double doubleToFpanr(const double doubleVal) {
#if DEBUG
	printf("\t doubleToFpanr");
#endif
	return doubleToFpanrWithPrec(doubleVal, PREC_MAX_DOUBLE);
}

double doubleToFpanrWithPrec(const double doubleVal, const int prec) {
#if DEBUG
	printf("\t doubleToFpanrWithPrec - début");
#endif
	double_st fpanrVal;
	fpanrVal._value = doubleVal;
	d_setPrec(&fpanrVal, prec);
#if DEBUG
	printf("\t doubleToFpanrWithPrec - fin");
#endif
	return fpanrVal._value;
}

unsigned getPrecFromFpanrDouble(const double doubleVal) {
#if DEBUG
	printf("\t getFpanrDoublePrec");
#endif
	double_st fpanrVal;
	fpanrVal._value = doubleVal;
	return d_getPrec(fpanrVal);
}

// --------------------------------------

unsigned count_trailing_zeros(const unsigned long n) {
#if DEBUG
	printf("\t count_trailing_zeros");
#endif
	return __builtin_ctzll(n);
}

void f_setPrec(float_st * this, int prec) {
	union ieee754_float d;
	d.f = this->_value;

	prec = MIN(22, prec);

	d.ieee.mantissa &= (0x7FFFFF << (23 - prec));
	d.ieee.mantissa |= 1 << (22 - prec); // set the leading 1

	this->_value = d.f;
}

void d_setPrec(double_st * this, int prec) {
#if DEBUG
	printf("\t setPrec");
#endif
	union ieee754_double d;
	d.d = this->_value;

	prec = MIN(51, prec);

	if (prec < 20) {
		d.ieee.mantissa0 &= (0xFFFFFu << (20 - prec));
		d.ieee.mantissa0 |= 1 << (19 - prec); // set the leading 1
		d.ieee.mantissa1 = 0;
	} else {
		if (prec == 20) {
			// cannot shift a number by 32 bit, so do it manually
			d.ieee.mantissa1 = 0x80000000;
		} else {
			d.ieee.mantissa1 &= (0xFFFFFFFF << (32 - (prec - 20)));
			d.ieee.mantissa1 |= 1 << (31 - (prec - 20)); // set the leading 1
		}
	}
	this->_value = d.d;
}

void d_setPrecMax(double_st * this) {
#if DEBUG
	printf("\t setPrecMax");
#endif
	d_setPrec(this, PREC_MAX_DOUBLE);
}

void f_setPrecMax(float_st * this) {
	f_setPrec(this, PREC_MAX_FLOAT);
}

unsigned d_getPrec(const double_st this) {
#if DEBUG
	printf("\t getPrec");
#endif
	union ieee754_double d;
	unsigned c;

	d.d = this._value;

	if (d.ieee.mantissa1 != 0) {
		c = count_trailing_zeros(d.ieee.mantissa1);
	} else {
		if (d.ieee.mantissa0 != 0) {
			c = count_trailing_zeros(d.ieee.mantissa0);
			c += 32;
		} else {
			c = 51;
		}
	}
	return (51 - c); // 51 bits max as there are 52 bits of mantissa minus 1 bit for the flag
}

unsigned f_getPrec(const float_st this) {
	union ieee754_float d;
	unsigned c;

	d.f = this._value;

	if (d.ieee.mantissa != 0) {
		c = count_trailing_zeros(d.ieee.mantissa);
	} else {
		c = 22;
	}

	return (22 - c); // 22 bits max as there are 23 bits of mantissa minus 1 bit for the flag
}

double d_getVal(const double_st this, int *prec) {
#if DEBUG
	printf("\t getVal");
#endif
	union ieee754_double d;
	int c;

	d.d = this._value;

	if (d.ieee.mantissa1 != 0) {
		c = count_trailing_zeros(d.ieee.mantissa1);
		d.ieee.mantissa1 ^= 1 << c; // remove the leading 1
	} else {
		if (d.ieee.mantissa0 != 0) {
			c = count_trailing_zeros(d.ieee.mantissa0);
			d.ieee.mantissa0 ^= 1 << c; // remove the leading 1
			c += 32;
		} else {
			c = 51;
		}
	}
	*prec = 51 - c;
	return (d.d);
}

float f_getVal(const float_st this, int *prec) {
	union ieee754_float d;
	int c;

	d.f = this._value;

	if (d.ieee.mantissa != 0) {
		c = count_trailing_zeros(d.ieee.mantissa);
		d.ieee.mantissa ^= 1 << c; // remove the leading 1
	}

	*prec = 22 - c;
	return (d.f);
}

void f_set(float_st * dest, const float_st source) {
	dest->_value = source._value;
}

void d_set(double_st * dest, const double_st source) {
	dest->_value = source._value;
}

void d_add(double_st * res, const double_st a, const double_st b){
#if DEBUG
	printf("\t d_add");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = d_getVal(a, &p1) + d_getVal(b, &p2);

	frexp(res->_value, &er);
	d_setPrec(res,er - MAX((e1-p1) , (e2-p2)));
}

/************************* FPHOOKS FUNCTIONS *************************
 * These functions correspond to those inserted into the source code
 * during source to source compilation and are replacement to floating
 * point operators
 **********************************************************************/

