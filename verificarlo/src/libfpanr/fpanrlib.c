/*
 * fpanrlib.c
 *
 *  Created on: 5 sept. 2018
 *      Author: Christophe Pont
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

#include "libfpanr.h"
#include "../vfcwrapper/vfcwrapper.h"

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

unsigned count_trailing_zeros(const unsigned long n) {
#if DEBUG
	printf("\t count_trailing_zeros");
#endif
	return __builtin_ctzll(n);
}

void f_setPrec(float_st * fpanrFVal, int prec) {
	union ieee754_float d;
	d.f = fpanrFVal->_value;

	prec = MIN(PREC_MAX_FLOAT, prec);

	d.ieee.mantissa &= (0x7FFFFF << (23 - prec));
	d.ieee.mantissa |= 1 << (PREC_MAX_FLOAT - prec); // set the leading 1

	fpanrFVal->_value = d.f;
}

void d_setPrec(double_st * fpanrDVal, int prec) {
#if DEBUG
	printf("\t setPrec");
#endif
	union ieee754_double d;
	d.d = fpanrDVal->_value;

	prec = MIN(PREC_MAX_DOUBLE, prec);

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
	fpanrDVal->_value = d.d;
}

void d_setPrecMax(double_st * fpanrDVal) {
#if DEBUG
	printf("\t setPrecMax");
#endif
	d_setPrec(fpanrDVal, PREC_MAX_DOUBLE);
}

void f_setPrecMax(float_st * fpanrFVal) {
	f_setPrec(fpanrFVal, PREC_MAX_FLOAT);
}

unsigned d_getPrec(const double_st fpanrDVal) {
#if DEBUG
	printf("\t getPrec");
#endif
	union ieee754_double d;
	unsigned c;

	d.d = fpanrDVal._value;

	if (d.ieee.mantissa1 != 0) {
		c = count_trailing_zeros(d.ieee.mantissa1);
	} else {
		if (d.ieee.mantissa0 != 0) {
			c = count_trailing_zeros(d.ieee.mantissa0);
			c += 32;
		} else {
			c = PREC_MAX_DOUBLE;
		}
	}
	return (PREC_MAX_DOUBLE - c); // 51 bits max as there are 52 bits of mantissa minus 1 bit for the flag
}

unsigned f_getPrec(const float_st fpanrFVal) {
	union ieee754_float d;
	unsigned c;

	d.f = fpanrFVal._value;

	if (d.ieee.mantissa != 0) {
		c = count_trailing_zeros(d.ieee.mantissa);
	} else {
		c = PREC_MAX_FLOAT;
	}

	return (PREC_MAX_FLOAT - c); // 22 bits max as there are 23 bits of mantissa minus 1 bit for the flag
}

double d_getVal(const double_st fpanrDVal, int *prec) {
#if DEBUG
	printf("\t getVal");
#endif
	union ieee754_double d;
	int c;

	d.d = fpanrDVal._value;

	if (d.ieee.mantissa1 != 0) {
		c = count_trailing_zeros(d.ieee.mantissa1);
		d.ieee.mantissa1 ^= 1 << c; // remove the leading 1
	} else {
		if (d.ieee.mantissa0 != 0) {
			c = count_trailing_zeros(d.ieee.mantissa0);
			d.ieee.mantissa0 ^= 1 << c; // remove the leading 1
			c += 32;
		} else {
			c = PREC_MAX_DOUBLE;
		}
	}
	*prec = PREC_MAX_DOUBLE - c;
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

	*prec = PREC_MAX_FLOAT - c;
	return (d.f);
}

void f_set(float_st * dest, const float_st source) {
	dest->_value = source._value;
}

void d_set(double_st * dest, const double_st source) {
	dest->_value = source._value;
}

void f_add(float_st * res, const float_st a, const float_st b) {
#if DEBUG
	printf("\t f_add");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = f_getVal(a, &p1) + f_getVal(b, &p2);

	frexp(res->_value, &er);
	f_setPrec(res, er - MAX((e1 - p1), (e2 - p2)));
}

void d_add(double_st * res, const double_st a, const double_st b) {
#if DEBUG
	printf("\t d_add");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = d_getVal(a, &p1) + d_getVal(b, &p2);

	frexp(res->_value, &er);
	d_setPrec(res, er - MAX((e1 - p1), (e2 - p2)));
}

void f_sub(float_st * res, const float_st a, const float_st b) {
#if DEBUG
	printf("\t f_sub");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = f_getVal(a, &p1) - f_getVal(b, &p2);

	frexp(res->_value, &er);
	f_setPrec(res, er - MAX((e1 - p1), (e2 - p2)));
}

void d_sub(double_st * res, const double_st a, const double_st b) {
#if DEBUG
	printf("\t d_sub");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = d_getVal(a, &p1) - d_getVal(b, &p2);

	frexp(res->_value, &er);
	d_setPrec(res, er - MAX((e1 - p1), (e2 - p2)));
}

void f_mul(float_st * res, const float_st a, const float_st b) {
#if DEBUG
	printf("\t f_mul");
#endif
	int p1, p2;

	res->_value = f_getVal(a, &p1) * f_getVal(b, &p2);

	f_setPrec(res, MIN(p1, p2));
}

void d_mul(double_st * res, const double_st a, const double_st b) {
#if DEBUG
	printf("\t d_mul");
#endif
	int p1, p2;

	res->_value = d_getVal(a, &p1) * d_getVal(b, &p2);

	d_setPrec(res, MIN(p1, p2));
}

void f_div(float_st * res, const float_st a, const float_st b) {
#if DEBUG
	printf("\t f_div");
#endif
	int p1, p2;

	res->_value = f_getVal(a, &p1) / f_getVal(b, &p2);

	f_setPrec(res, MIN(p1, p2));
}

void d_div(double_st * res, const double_st a, const double_st b) {
#if DEBUG
	printf("\t d_div");
#endif
	int p1, p2;

	res->_value = d_getVal(a, &p1) / d_getVal(b, &p2);

	d_setPrec(res, MIN(p1, p2));
}

void f_fabs(float_st * res, const float_st a) {
	int p;
	res->_value = fabs(f_getVal(a, &p));
	f_setPrec(res, p);
}

void d_fabs(double_st * res, const double_st a) {
	int p;
	res->_value = fabs(d_getVal(a, &p));
	d_setPrec(res, p);
}

void f_sqrt(float_st * res, const float_st a) {
	int p;
	res->_value = sqrt(f_getVal(a, &p));
	f_setPrec(res, p + 1);
}

void d_sqrt(double_st * res, const double_st a) {
	int p;
	res->_value = sqrt(d_getVal(a, &p));
	d_setPrec(res, p + 1);
}

void f_exp(float_st * res, const float_st a) {
	int p;
	res->_value = exp(f_getVal(a, &p));
	f_setPrec(res, p - log2(f_getVal(a, &p)));
}

void d_exp(double_st * res, const double_st a) {
	int p;
	res->_value = exp(d_getVal(a, &p));
	d_setPrec(res, p - log2(d_getVal(a, &p)));
}

void f_log(float_st * res, const float_st a) {

}

void d_log(double_st * res, const double_st a) {

}

void f_cos(float_st * res, const float_st a) {

}

void d_cos(double_st * res, const double_st a) {

}

void f_sin(float_st * res, const float_st a) {

}

void d_sin(double_st * res, const double_st a) {

}

/************************* FPHOOKS FUNCTIONS *************************
 * These functions correspond to those inserted into the source code
 * during source to source compilation and are replacement to floating
 * point operators
 **********************************************************************/

static float _floatadd(float _a, float _b) {
	//return a + b
#if DEBUG
	printf("\n_float_add");
#endif
	float_st res, a, b;
	a._value = _a;
	b._value = _b;
	f_add(&res, a, b);
	int prec = f_getPrec(res);
	return res._value;
	//return f_getVal(res, &prec);
//	return _mca_sbin(a, b,(mpfr_bin)MP_ADD);
}

static float _floatsub(float _a, float _b) {
#if DEBUG
	printf("\n_float_sub");
#endif
	//return a - b
	float_st res, a, b;
	a._value = _a;
	b._value = _b;
	f_sub(&res, a, b);
	int prec = f_getPrec(res);
	return res._value;
	//return f_getVal(res, &prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_SUB);
}

static float _floatmul(float _a, float _b) {
#if DEBUG
	printf("\n_float_mul");
#endif
	//return a * b
	float_st res, a, b;
	a._value = _a;
	b._value = _b;
	f_mul(&res, a, b);
	int prec = f_getPrec(res);
	return res._value;
	//return f_getVal(res, &prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_MUL);
}

static float _floatdiv(float _a, float _b) {
#if DEBUG
	printf("\n_float_div");
#endif
	//return a / b
	float_st res, a, b;
	a._value = _a;
	b._value = _b;
	f_div(&res, a, b);
	int prec = f_getPrec(res);
	return res._value;
	//return f_getVal(res, &prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_DIV);
}

static double _doubleadd(double _a, double _b) {
#if DEBUG
	printf("\n_double_add");
#endif
	//return a + b
	double_st res, a, b;
	a._value = _a;
	b._value = _b;
	d_add(&res, a, b);
	int prec = d_getPrec(res);
	return res._value;
	//return d_getVal(res, &prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_ADD);
}

static double _doublesub(double _a, double _b) {
#if DEBUG
	printf("\n_double_sub");
#endif
	//return a - b
	double_st res, a, b;
	a._value = _a;
	b._value = _b;
	d_sub(&res, a, b);
	int prec = d_getPrec(res);
	return res._value;
	//return d_getVal(res, &prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_SUB);
}

static double _doublemul(double _a, double _b) {
#if DEBUG
	printf("\n_double_mul");
#endif
	//return a * b
	double_st res, a, b;
	a._value = _a;
	b._value = _b;
	d_mul(&res, a, b);
	int prec = d_getPrec(res);
	return res._value;
	//return d_getVal(res, &prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_MUL);
}

static double _doublediv(double _a, double _b) {
#if DEBUG
	printf("\n_double_div");
#endif
	//return a / b
	double_st res, a, b;
	a._value = _a;
	b._value = _b;
	d_div(&res, a, b);
	int prec = d_getPrec(res);
	return res._value;
	//return d_getVal(res, &prec);
	//return _mca_dbin(a, b, (mpfr_bin)MP_DIV);
}

struct mca_interface_t fpanr_interface = {
	_floatadd,
	_floatsub,
	_floatmul,
	_floatdiv,
	_doubleadd,
	_doublesub,
	_doublemul,
	_doublediv,
	NULL,
	NULL,
	NULL
};
