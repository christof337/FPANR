// The Monte Carlo Arihmetic Library - A tool for automated rounding error
// analysis of floating point software.
//
// Copyright (C) 2014 The Computer Engineering Laboratory, The
// University of Sydney. Maintained by Michael Frechtling:
// michael.frechtling@sydney.edu.au
//
// Copyright (C) 2015
//     Universite de Versailles St-Quentin-en-Yvelines                          *
//     CMLA, Ecole Normale Superieure de Cachan                                 *
//
// Changelog:
//
// 2015-05-20 replace random number generator with TinyMT64. This
// provides a reentrant, independent generator of better quality than
// the one provided in libc.
//
// 2015-11-14 remove effectless comparison functions, llvm will not
// instrument it.
//
// This file is part of the Monte Carlo Arithmetic Library, (MCALIB). MCALIB is
// free software: you can redistribute it and/or modify it under the terms of
// the GNU General Public License as published by the Free Software Foundation,
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
//#include <mpfr.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <sys/time.h>
//#include <unistd.h>

#include "ieee754.h"

#include "FPANRlib.h"

#define MAX(A,B) (((A)>(B)) ? (A) : (B))
#define MIN(A,B) (((A)<(B)) ? (A) : (B))

#define DEBUG 0

// --------------------------------------


/*
// Helper functions
  unsigned count_trailing_zeros(unsigned long n) {
	//LOG("");
	return __builtin_ctzll(n);
    if (! n) return 0;
    unsigned int c = 32; // c will be the number of zero bits on the right
    n &= -(signed) n;
    if (n) c--;
    if (n & 0x0000FFFF) c -= 16;
    if (n & 0x00FF00FF) c -= 8;
    if (n & 0x0F0F0F0F) c -= 4;
    if (n & 0x33333333) c -= 2;
    if (n & 0x55555555) c -= 1;
    return c;
}
*/

  unsigned count_trailing_zeros(unsigned long n) {
	//LOG("");
#if DEBUG
	printf("\t count_trailing_zeros");
#endif
	return __builtin_ctzll(n);
}


/*

void float_st::SetPrec(int prec){
	//LOG("");
	union ieee754_float d;
	d.f = this->_Value;

	prec = MIN(22,prec);

	d.ieee.mantissa &= (0x7FFFFF<<(23-prec));
	d.ieee.mantissa |= 1<<(22-prec); // set the leading 1

	this->_Value = d.f;
}

*/
void f_setPrec(float_st * this, int prec) {
	//LOG("");
	union ieee754_float d;
	d.f = this->_value;

	prec = MIN(22,prec);

	d.ieee.mantissa &= (0x7FFFFF<<(23-prec));
	d.ieee.mantissa |= 1<<(22-prec); // set the leading 1

	this->_value = d.f;
}

/*
void double_st::SetPrec(int prec){
	//LOG("");
	union ieee754_double d;
	d.d = this->_Value;

	prec = MIN(51,prec);

	if (prec<20){
		d.ieee.mantissa0 &= (0xFFFFFu<<(20-prec));
		d.ieee.mantissa0 |= 1<<(19-prec); // set the leading 1
		d.ieee.mantissa1 = 0;
	}else{
		if (prec == 20){
			// cannot shift a number by 32 bit, so do it manually
			d.ieee.mantissa1 = 0x80000000;
		}else{
			d.ieee.mantissa1 &= (0xFFFFFFFF<<(32-(prec-20)));
			d.ieee.mantissa1 |= 1<<(31-(prec-20)); // set the leading 1
		}
	}
	this->_Value = d.d;
}

*/
void d_setPrec(double_st * this, int prec) {
#if DEBUG
	printf("\t setPrec");
#endif
	//LOG("");
	union ieee754_double d;
	d.d = this->_value;

	prec = MIN(51,prec);

	if (prec<20){
		d.ieee.mantissa0 &= (0xFFFFFu<<(20-prec));
		d.ieee.mantissa0 |= 1<<(19-prec); // set the leading 1
		d.ieee.mantissa1 = 0;
	}else{
		if (prec == 20){
			// cannot shift a number by 32 bit, so do it manually
			d.ieee.mantissa1 = 0x80000000;
		}else{
			d.ieee.mantissa1 &= (0xFFFFFFFF<<(32-(prec-20)));
			d.ieee.mantissa1 |= 1<<(31-(prec-20)); // set the leading 1
		}
	}
	this->_value = d.d;
}

/*
void   double_st::SetPrecMax(){
	//LOG("");
	SetPrec(51);
} */
void d_setPrecMax(double_st * this) {
#if DEBUG
	printf("\t setPrecMax");
#endif
	//LOG("");
	d_setPrec(this,51);
}



/*
void   float_st::SetPrecMax(){
	//LOG("");
	SetPrec(22);
}*/

void f_setPrecMax(float_st * this) {
	//LOG("");
	f_setPrec(this,22);
}

/*
unsigned   double_st::GetPrec() const{
	//LOG("");
	union ieee754_double d;
	unsigned c;

	d.d = this->_Value;

	if (d.ieee.mantissa1!=0){
		c = count_trailing_zeros(d.ieee.mantissa1);
	}else{
		if (d.ieee.mantissa0!=0){
			c = count_trailing_zeros(d.ieee.mantissa0);
			c += 32;
		}else{
			c = 51;
		}
	}
	return (51-c); // 51 bit max as there are 52 bit of mantissa minus 1 bit for the flag
}
*/

unsigned d_getPrec(double_st this) {
#if DEBUG
	printf("\t getPrec");
#endif
	union ieee754_double d;
	unsigned c;

	d.d = this._value;

	if(d.ieee.mantissa1!=0){
		c = count_trailing_zeros(d.ieee.mantissa1);
	}else {
		if(d.ieee.mantissa0!=0){
			c = count_trailing_zeros(d.ieee.mantissa0);
			c += 32;
		} else {
			c = 51;
		}
	}
	return (51-c); // 51 bits max as there are 52 bits of mantissa minus 1 bit for the flag
}


/*

unsigned   float_st::GetPrec() const{
	//LOG("");
	union ieee754_float d;
	unsigned c;

	d.f = this->_Value;

	if (d.ieee.mantissa!=0){
		c = count_trailing_zeros(d.ieee.mantissa);
	}else {
		c = 22;
	}

	return (22-c); // 22 bit max as there are 23 bit of mantissa minus 1 bit for the flag
}
*/

unsigned f_getPrec(float_st this) {
	union ieee754_float d;
	unsigned c;

	d.f = this._value;

	if (d.ieee.mantissa!=0){
		c = count_trailing_zeros(d.ieee.mantissa);
	} else {
		c = 22;
	}

	return (22 - c); // 22 bits max as there are 23 bits of mantissa minus 1 bit for the flag
}

/*

double   double_st::GetVal(int *prec) const{
	//LOG("");
	union ieee754_double d;
	int c;

	d.d = this->_Value;

	if (d.ieee.mantissa1!=0){
		c = count_trailing_zeros(d.ieee.mantissa1);
		d.ieee.mantissa1 ^= 1<<c; // remove the leading 1
	}else{
		if (d.ieee.mantissa0!=0){
			c = count_trailing_zeros(d.ieee.mantissa0);
			d.ieee.mantissa0 ^= 1<<c; // remove the leading 1
			c += 32;
		}else{
			c = 51;
		}
	}
	*prec = 51-c;
	return(d.d);
} */

double d_getVal(const double_st this, int *prec) {
#if DEBUG
	printf("\t getVal");
#endif
	union ieee754_double d;
	int c;

	d.d = this._value;

	if(d.ieee.mantissa1!=0) {
		c = count_trailing_zeros(d.ieee.mantissa1);
		d.ieee.mantissa1 ^= 1<<c; // remove the leading 1
	} else {
		if (d.ieee.mantissa0!=0) {
			c = count_trailing_zeros(d.ieee.mantissa0);
			d.ieee.mantissa0 ^= 1<<c; // remove the leading 1
			c += 32;
		} else {
			c = 51;
		}
	}
	*prec = 51-c;
	return(d.d);
}

/*

float   float_st::GetVal(int *prec) const{
	//LOG("");
	union ieee754_float d;
	int c;

	d.f = this->_Value;

	if (d.ieee.mantissa!=0){
		c = count_trailing_zeros(d.ieee.mantissa);
		d.ieee.mantissa ^= 1<<c; // remove the leading 1
	}

	*prec = 22-c;
	return(d.f);
}
*/

float f_getVal(float_st this, int *prec) {
	union ieee754_float d;
	int c;

	d.f = this._value;

	if(d.ieee.mantissa!=0) {
		c = count_trailing_zeros(d.ieee.mantissa);
		d.ieee.mantissa ^= 1<<c; // remove the leading 1
	}

	*prec = 22-c;
	return (d.f);
}


void f_set(float_st * dest, const float_st source) {
	dest->_value = source._value;
}

void d_set(double_st * dest, const double_st source) {
	dest->_value = source._value;
}


/*
  float_st& float_st::operator+=(const float_st& r){
	//LOG("");
	int e1, e2, er;
	int p1, p2;
	float res;

	frexp(_Value, &e1);
	frexp(r._Value, &e2);
	res = this->GetVal(&p1) + r.GetVal(&p2);

	frexp(res, &er);
	_Value = res;
	this->SetPrec(er - MAX((e1-p1) , (e2-p2)));

    return *this;
}*/

void f_add(float_st * res, const float_st a, const float_st b) {
	// LOG("")
#if DEBUG
	printf("\t f_add");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = f_getVal(a,&p1) + f_getVal(b,&p2);

	frexp(res->_value, &er);
	f_setPrec(res, er - MAX((e1-p1) , (e2-p2)));

	//return *this;
}

void d_add(double_st * res, const double_st a, const double_st b){
	//LOG("");
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
//	printf("\n**********%d",er - MAX((e1-p1) , (e2-p2)));

//    return *this;
}


void f_sub(float_st * res, const float_st a, const float_st b){
//	//LOG("");
#if DEBUG
	printf("\t f_sub");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = f_getVal(a, &p1) - f_getVal(b, &p2);

	frexp(res->_value, &er);
	f_setPrec(res,er - MAX((e1-p1) , (e2-p2)));

//    return *this;
}

void d_sub(double_st * res, const double_st a, const double_st b){
//	//LOG("");
#if DEBUG
	printf("\t d_sub");
#endif
	int e1, e2, er;
	int p1, p2;

	frexp(a._value, &e1);
	frexp(b._value, &e2);
	res->_value = d_getVal(a, &p1) - d_getVal(b, &p2);

	frexp(res->_value, &er);
	d_setPrec(res,er - MAX((e1-p1) , (e2-p2)));

//    return *this;
}

/*
  float_st& f_sub(const float_st& r){
	//LOG("");
	int e1, e2, er;
	int p1, p2;
	float res;

	frexp(_Value, &e1);
	frexp(r._Value, &e2);
	res = this->GetVal(&p1) - r.GetVal(&p2);

	frexp(res, &er);
	_Value = res;
	this->SetPrec(er - MAX((e1-p1) , (e2-p2)));

    return *this;
}

/*
  double_st& double_st::operator-=(const double_st& r){
	//LOG("");
	int e1, e2, er;
	int p1, p2;
	double res;

	frexp(_Value, &e1);
	frexp(r._Value, &e2);
	res = this->GetVal(&p1) - r.GetVal(&p2);

	frexp(res, &er);
	_Value = res;
	this->SetPrec(er - MAX((e1-p1) , (e2-p2)));

    return *this;
}

*/
void f_mul(float_st * res, const float_st a, const float_st b){
//	//LOG("");
#if DEBUG
	printf("\t f_mul");
#endif
	int p1, p2;

	res->_value = f_getVal(a, &p1) * f_getVal(b, &p2);

	f_setPrec(res,MIN(p1,p2));

//    return *this;
}

void d_mul(double_st * res, const double_st a, const double_st b){
//	//LOG("");
#if DEBUG
	printf("\t d_mul");
#endif
	int p1, p2;

	res->_value = d_getVal(a, &p1) * d_getVal(b, &p2);

	d_setPrec(res,MIN(p1,p2));

//    return *this;
}
/*

  float_st& float_st::operator*=(const float_st& r){
	//LOG("");
	int p1, p2;

	_Value  = this->GetVal(&p1) * r.GetVal(&p2);
	this->SetPrec(MIN(p1,p2));

    return *this;
}

  double_st& double_st::operator*=(const double_st& r){
	//LOG("");
	int p1, p2;

	_Value  = this->GetVal(&p1) * r.GetVal(&p2);
	this->SetPrec(MIN(p1,p2));

    return *this;
}

*/

void f_div(float_st * res, const float_st a, const float_st b){
//	//LOG("");
#if DEBUG
	printf("\t f_div");
#endif
	int p1, p2;

	res->_value = f_getVal(a, &p1) / f_getVal(b, &p2);

	f_setPrec(res,MIN(p1,p2));

//    return *this;
}

void d_div(double_st * res, const double_st a, const double_st b){
//	//LOG("");
#if DEBUG
	printf("\t d_div");
#endif
	int p1, p2;

	res->_value = d_getVal(a, &p1) / d_getVal(b, &p2);

	d_setPrec(res,MIN(p1,p2));

//    return *this;
}

/*
  float_st& float_st::operator/=(const float_st& r){
	//LOG("");
	int p1, p2;

	_Value  = this->GetVal(&p1) / r.GetVal(&p2);
	this->SetPrec(MIN(p1,p2));

    return *this;
}

  double_st& double_st::operator/=(const double_st& r){
	//LOG("");
	int p1, p2;

	_Value  = this->GetVal(&p1) / r.GetVal(&p2);
	this->SetPrec(MIN(p1,p2));

    return *this;
}
*/


// void f_abs(float_st * res, const float_st a) {
//	 int p;
//	 res->_value = abs(f_getVal(a,&p));
//	 f_setPrec(res, p);
// }
//
// void d_abs(double_st * res, const double_st a) {
//	 int p;
//	 res->_value = abs(d_getVal(a,&p));
//	 d_setPrec(res, p);
// }

 void f_fabs(float_st * res, const float_st a) {
	 int p;
	 res->_value = fabs(f_getVal(a,&p));
	 f_setPrec(res, p);
 }

 void d_fabs(double_st * res, const double_st a) {
	 int p;
	 res->_value = fabs(d_getVal(a,&p));
	 d_setPrec(res, p);
 }

 void f_sqrt(float_st * res, const float_st a) {
	 int p;
	 res->_value = sqrt(f_getVal(a,&p));
	 f_setPrec(res, p+1);
 }

 void d_sqrt(double_st * res, const double_st a) {
	 int p;
	 res->_value = sqrt(d_getVal(a,&p));
	 d_setPrec(res, p+1);
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
	float_st res,a,b;
	a._value=_a;
	b._value=_b;
	f_add(&res,a,b);
	int prec = f_getPrec(res);
	return f_getVal(res,&prec);
//	return _mca_sbin(a, b,(mpfr_bin)MP_ADD);
}

static float _floatsub(float _a, float _b) {
#if DEBUG
	printf("\n_float_sub");
#endif
	//return a - b
	float_st res,a,b;
	a._value=_a;
	b._value=_b;
	f_sub(&res,a,b);
	int prec = f_getPrec(res);
	return f_getVal(res,&prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_SUB);
}

static float _floatmul(float _a, float _b) {
#if DEBUG
	printf("\n_float_mul");
#endif
	//return a * b
	float_st res,a,b;
	a._value=_a;
	b._value=_b;
	f_mul(&res,a,b);
	int prec = f_getPrec(res);
	return f_getVal(res,&prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_MUL);
}

static float _floatdiv(float _a, float _b) {
#if DEBUG
	printf("\n_float_div");
#endif
	//return a / b
	float_st res,a,b;
	a._value=_a;
	b._value=_b;
	f_div(&res,a,b);
	int prec = f_getPrec(res);
	return f_getVal(res,&prec);
//	return _mca_sbin(a, b, (mpfr_bin)MP_DIV);
}


static double _doubleadd(double _a, double _b) {
#if DEBUG
	printf("\n_double_add");
#endif
	//return a + b
	double_st res,a,b;
	a._value=_a;
	b._value=_b;
	d_add(&res,a,b);
	int prec = d_getPrec(res);
	return d_getVal(res,&prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_ADD);
}

static double _doublesub(double _a, double _b) {
#if DEBUG
	printf("\n_double_sub");
#endif
	//return a - b
	double_st res,a,b;
	a._value=_a;
	b._value=_b;
	d_sub(&res,a,b);
	int prec = d_getPrec(res);
	return d_getVal(res,&prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_SUB);
}

static double _doublemul(double _a, double _b) {
#if DEBUG
	printf("\n_double_mul");
#endif
	//return a * b
	double_st res,a,b;
	a._value=_a;
	b._value=_b;
	d_mul(&res,a,b);
	int prec = d_getPrec(res);
	return d_getVal(res,&prec);
//	return _mca_dbin(a, b, (mpfr_bin)MP_MUL);
}

static double _doublediv(double _a, double _b) {
#if DEBUG
	printf("\n_double_div");
#endif
	//return a / b
	double_st res,a,b;
	a._value=_a;
	b._value=_b;
	d_div(&res,a,b);
	int prec = d_getPrec(res);
	return d_getVal(res,&prec);
	//return _mca_dbin(a, b, (mpfr_bin)MP_DIV);
}
