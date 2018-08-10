#include "src/FPANRlib.h"

#include "src/fp2bin.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
//	double_st a,b,c;
//	a._value = 0.1;
//	d_setPrec(a,3);
//	b._value = 0.2;
//	d_setPrec(b,43);
//	d_add(&c,a,b);
//	int prec = d_getPrec(c);
//	printf("\nc=%f (prec=%d)\n",d_getVal(c,&prec),prec);

    double_st a,b,res;
    double _a=1.1,_b=2.643;

    b._value = _b;
	d_setPrecMax(&b);
    a._value = _a;
	d_setPrecMax(&a);

	d_add(&res,a,b);

	int rPrec = d_getPrec(res);
	int bPrec = d_getPrec(b);
	int aPrec = d_getPrec(a);
	int rExp, aExp, bExp;
	double currentA, currentB, currentRes;
	currentA = d_getVal(a,&aPrec);
	currentB = d_getVal(b,&bPrec);
	currentRes = d_getVal(res,&rPrec);
	frexp(currentA, &aExp);
	frexp(currentB, &bExp);
	frexp(currentRes, &rExp);

	printf("\nrPrec=%d, rExp=%d, aExp=%d, aPrec=%d, bExp=%d, bPrec=%d 10=%d\n",
			rPrec, rExp, aExp, aPrec, bExp, bPrec,10);
	fflush(stdout);
//	ck_assert_int_eq(rPrec,rExp-MAX((aExp-aPrec),(bExp-bPrec)));

	printf("\n\n%f=%f+%f(%f)\n",currentRes,currentA,currentB,currentA+currentB);
	printf("is res=a+b? %d (%s)\n\n",currentRes==currentA+currentB,currentRes==currentA+currentB?"yes":"no");

	char binString[FP2BIN_STRING_MAX];
	fp2bin(_a,binString);
	printf("\n\n_a=\t\t%f\t=%s\n",_a,binString);
	fp2bin(currentA,binString);
	printf("currentA=\t%f\t=%s\n",currentA,binString);
	fp2bin(a._value,binString);
	printf("a._value=\t%f\t=%s\n",a._value,binString);

	fp2bin(_b,binString);
	printf("\n\n_b=\t\t%f\t=%s\n",_b,binString);
	fp2bin(currentB,binString);
	printf("currentB=\t%f\t=%s\n",currentB,binString);
	fp2bin(b._value,binString);
	printf("b._value=\t%f\t=%s\n",b._value,binString);

	fp2bin(_a+_b,binString);
	printf("\n\n_a+_b=\t\t%f\t=%s\n",_a+_b,binString);
	fp2bin(currentRes,binString);
	printf("currentRes\t%f\t=%s\n",currentRes,binString);
	fp2bin(res._value,binString);
	printf("res._value=\t%f\t=%s\n",res._value,binString);
    return 0;
}

