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
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>

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

#ifdef DBL_DECIMAL_DIG
  #define OP_DBL_Digs (DBL_DECIMAL_DIG)
#else  
  #ifdef DECIMAL_DIG
    #define OP_DBL_Digs (DECIMAL_DIG)
  #else  
    #define OP_DBL_Digs (DBL_DIG + 3)
  #endif
#endif

#ifdef FLT_DECIMAL_DIG
  #define OP_FLT_Digs (FLT_DECIMAL_DIG)
#else  
  #ifdef DECIMAL_DIG
    #define OP_FLT_Digs (DECIMAL_DIG)
  #else  
    #define OP_FLT_Digs (FLT_DIG + 3)
  #endif
#endif

// --------------------------------------

// ---------------
//     float
// ---------------

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

char * fpanrFloatToStr(const float fpanrVal) {
	int Digs = OP_FLT_Digs;
	int p = getPrecFromFpanrFloat(fpanrVal);
	float val = fpanrToFloat(fpanrVal);
	size_t needed = snprintf(NULL, 0, "%*.e (%d)", Digs, val, p);
	char  *buffer = malloc((needed+1)*sizeof(char));
	sprintf(buffer, "%.*e (%d)", Digs, val, p);
	return buffer;
}

int countLines(FILE * fp) {
	char ch;
	int cpt = 0;
	while((ch = fgetc(fp)) != EOF) {
		fflush(stdout);
		if(ch=='\n') {
			cpt++;
		}
	}
	return cpt;
}

int countColumns(FILE * fp) {
	char ch;
	int cpt = 0;
	while((ch = fgetc(fp)) != '\n') {
		if(ch == DELIM) {
			cpt++;
		}
	}
	return cpt;
}

int fpanrFVecToFile(const size_t n, const float array[n], const char * fileName) {
	FILE *fp;

	fp = fopen(fileName, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%f\n",fpanrToFloat(array[i]));
	}

	fclose(fp);

	// writing precisions
	char * str = malloc((strlen(fileName)+strlen(".prec")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".prec");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%d\n",getPrecFromFpanrFloat(array[i]));
	}

	free(str);
	fclose(fp);

 	// works
    /*int Digs = OP_FLT_Digs;
    double OneSeventh = 1.0/10.0;
    printf("%.*e (%e)\n", Digs, OneSeventh, OneSeventh*20.0);
    char str[60];
    sprintf(str,"%.*e",Digs,OneSeventh);
    double test;
    sscanf(str,"%le",&test);
    printf("%.*e (%e)",Digs,test,test*20.0);*/

	// writing both
	int Digs = OP_FLT_Digs;
	str = malloc((strlen(fileName)+strlen(".fpanr")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".fpanr");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%.*e (%d)%c",Digs,fpanrToFloat(array[i]),getPrecFromFpanrFloat(array[i]),DELIM);
	}

	free(str);
	fclose(fp);
}

int fpanrFMatToFile(const size_t n, const size_t m, const float matrix[n][m], const char * fileName) {
	FILE *fp;

	fp = fopen(fileName, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%f%c",fpanrToFloat(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);

	// writing precisions
	char * str = malloc((strlen(fileName)+strlen(".prec")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".prec");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%d%c",getPrecFromFpanrFloat(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}

	free(str);
	fclose(fp);
	// writing both
	int Digs = OP_FLT_Digs;
	str = malloc((strlen(fileName)+strlen(".fpanr")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".fpanr");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%d%c",getPrecFromFpanrFloat(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}

	free(str);
	fclose(fp);
}


int fpanrFileToFVec(const size_t n, float array[n], const char * fileName) {
	FILE *fp;
	int cpt;
	float val;
	int prec;
	int nbParsed;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error while opening file %s", fileName);
		return -1;
	}
	for ( int i = 0 ; i < n ; ++i ) {
		nbParsed = fscanf(fp,"%e (%d)",&val,&prec);
		if (nbParsed > 1) 
			array[i] = floatToFpanrWithPrec(val, prec);
	}

	fclose(fp);

	return 0;
}

int fpanrFileToFMat(const size_t n, const size_t m, float matrix[n][m], const char * fileName) {
	FILE *fp;
	int cpt, prec, nbParsed;
	float val;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error while opening file %s", fileName);
		return -1;
	}

	int maxLength = m*(20+OP_FLT_Digs);
	char * str = malloc(sizeof(char) * maxLength);
	char * token, s[2];
	s[0]=DELIM;
	s[1]='\0';

	for ( size_t i = 0 ; i < n ; ++i ) {
		str = malloc(sizeof(char) * maxLength);
		assert(str != NULL);
		token = fgets(str, maxLength, fp);
		if (token == str) {
			token = strtok(str, s);

			cpt = 0;
	   		/* walk through other tokens */
			while( token != NULL ) {
				nbParsed = sscanf(token,"%e (%d)",&val, &prec);

				if(nbParsed>1) {
					matrix[i][cpt] = floatToFpanrWithPrec(val, prec);
				}

				token = strtok(NULL, s);
				cpt++;
			}
		}

		free(str);
	}

	return 0;
}


// --------------
//    double
// --------------

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

char * fpanrDoubleToStr(const double fpanrVal) {
	// writing both	
	int Digs = OP_DBL_Digs;
	int p = getPrecFromFpanrDouble(fpanrVal);
	double val = fpanrToDouble(fpanrVal);
	size_t needed = snprintf(NULL, 0, "%.*e (%d)", Digs, val, p);
	char  *buffer = malloc((needed+1)*sizeof(char));
	sprintf(buffer, "%.*e (%d)", Digs, val, p);
	return buffer;
}

int fpanrDVecToFile(const size_t n, const double array[n], const char * fileName) {
	FILE *fp;

	fp = fopen(fileName, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%f\n",fpanrToDouble(array[i]));
	}

	fclose(fp);

	// writing precisions
	char * str = malloc((strlen(fileName)+strlen(".prec")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".prec");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%d\n",getPrecFromFpanrDouble(array[i]));
	}

	free(str);
	fclose(fp);

	// writing both	
	int Digs = OP_DBL_Digs;
	str = malloc((strlen(fileName)+strlen(".fpanr")+1) * sizeof(char));
	assert(str != NULL);
	strcpy(str,fileName);
	strcat(str, ".fpanr");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		fprintf(fp, "%.*e (%d)\n",Digs,fpanrToDouble(array[i]),getPrecFromFpanrDouble(array[i]));
	}

	free(str);
	fclose(fp);
}

int fpanrDMatToFile(const size_t n, const size_t m, const double matrix[n][m], const char * fileName) {
	FILE *fp;

	fp = fopen(fileName, "w");
	assert(fp != NULL /* error while opening file */);
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%f%c",fpanrToDouble(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}

	fclose(fp);

	// writing precisions
	char str[strlen(fileName)+strlen(".prec")];
	assert(str != NULL /* couldn't allocate memory for str */);
	strcpy(str,fileName);
	strcat(str, ".prec");
	fp = fopen(str, "w");
	assert(fp != NULL /* error while opening file */);
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%d%c",getPrecFromFpanrDouble(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}
	//free(str);
	fclose(fp);

	// writing both	
	int Digs = OP_DBL_Digs;
	//str = malloc((strlen(fileName)+strlen(".fpanr")+1) * sizeof(char));
	assert(str != NULL /* couldn't allocate memory for str */);
	strcpy(str,fileName);
	strcat(str, ".fpanr");
	fp = fopen(str, "w");
	for(size_t i = 0 ; i < n ; ++i ) {
		for ( size_t j = 0 ; j < m ; ++j ) {
			fprintf(fp, "%.*e (%d)%c",Digs,fpanrToDouble(matrix[i][j]),getPrecFromFpanrDouble(matrix[i][j]),DELIM);
		}
		fprintf(fp,"\n");
	}

	//free(str);
	fclose(fp);
}

int fpanrFileToDVec(const size_t n, double array[n], const char * fileName) {
	FILE *fp;
	int cpt;
	double val;
	int prec;
	int nbParsed;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error while opening file %s", fileName);
		return -1;
	}

	for ( int i = 0 ; i < n ; ++i ) {
		nbParsed = fscanf(fp,"%le (%d)",&val,&prec);
		if ( nbParsed > 1 ) 
			array[i] = doubleToFpanrWithPrec(val, prec);
	}

	fclose(fp);

	return 0;
}

int fpanrFileToDMat(const size_t n, const size_t m, double matrix[n][m], const char * fileName) {
	FILE *fp;
	int cpt, prec, nbParsed;
	double val;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fprintf(stderr, "Error while opening file %s", fileName);
		return -1;
	}

	int maxLength = m*(20+OP_DBL_Digs);
	char * str;
	char * token, s[2];
	s[0]=DELIM;
	s[1]='\0';

	for ( size_t i = 0 ; i < n ; ++i ) {
		str = malloc(sizeof(char) * maxLength);
		assert(str != NULL);
		token = fgets(str, maxLength, fp);
		if (token == str) { // on success, fgets return the same str parameter 
			// read success
			token = strtok(str, s);

			cpt = 0;
	   		/* walk through other tokens */
			while( token != NULL ) {
				nbParsed = sscanf(token,"%le (%d)",&val, &prec);

				if(nbParsed>1) {
					matrix[i][cpt] = doubleToFpanrWithPrec(val, prec);
				}

				token = strtok(NULL, s);
				cpt++;
			}
		}

		free(str);
	}

	fclose(fp);

	return 0;
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
#if DEBUG
	printf("\t setPrec %d - MAX((%d-%d),(%d-%d))",er,e1,p1,e2,p2);
#endif
	d_setPrec(res, er - MAX((e1 - p1), (e2 - p2)));
}

double _doublesub(double _a, double _b) {
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

int cmpFpanrDouble(const double a, const double b) {
	double valA, valB;
	valA = fpanrToDouble(a);
	valB = fpanrToDouble(b);

	if ( fpanrToDouble(_doublesub(a,b)) == 0.0) {
		return 0;
	} else if ( fpanrToDouble(_doublesub(a,b)) > 0.0 ) {
		return 1;
	} else {
		return -1;
	}
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

double log2(double val) {
	return log(val)/log(2);
}

void f_log(float_st * res, const float_st a) {
	int p;
	float val = f_getVal(a,&p);
	res->_value = log(val);
	f_setPrec(res,p+log2(log(val)));
}

void d_log(double_st * res, const double_st a) {
	int p;
	fflush(stdout);
	double val = d_getVal(a,&p);
	fflush(stdout);

	res->_value = log(val);
	fflush(stdout);

	d_setPrec(res,p+log2(log(val)));
	fflush(stdout);

}

void f_cos(float_st * res, const float_st a) {
	int p;
	float val = f_getVal(a,&p);
	res->_value = cos(val);
	f_setPrec(res, p+((log2(cos(val)/(val*sin(val))))));
}

void d_cos(double_st * res, const double_st a) {
	int p;
	double val = d_getVal(a,&p);
	res->_value = cos(val);
	d_setPrec(res, p+log2(cos(val)/(val*sin(val))));
}

void f_sin(float_st * res, const float_st a) {
	int p;
	float val = f_getVal(a,&p);
	res->_value = sin(val);
	f_setPrec(res, p+log2(sin(val)/(val*cos(val))));
}

void d_sin(double_st * res, const double_st a) {
	int p;
	double val = d_getVal(a,&p);
	res->_value = sin(val);
	d_setPrec(res, p+log2(sin(val)/(val*cos(val))));
}


/************************* FPHOOKS FUNCTIONS *************************
 * These functions correspond to those inserted into the source code
 * during source to source compilation and are replacement to floating
 * point operators
 **********************************************************************/


