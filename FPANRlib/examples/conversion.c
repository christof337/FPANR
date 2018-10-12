#include <config.h>
#include <stdio.h>
#include <math.h>

// FIXME : trouver comment linker dynamiquement le chemin
#include "../src/libfpanrio.h"
#include "../src/fp2bin.h"

#define A_PREC 26
#define B_PREC 37

#define A_VAL 1.12
#define B_VAL 2.643

void printVal(double a, double fpA, double currentA, int aPrec, int prec, char string[100]) {
	char binString[FP2BIN_STRING_MAX];
	fp2bin(a,binString);
	printf("\n\n%s\t\t   =\t%f = %s\n",string,a,binString);
	fp2bin(fpA,binString);
	if(prec == -1) {
		printf("fpanr_add(a,b)\t   =\t%f = %s\n",fpA,binString);
	} else {
		printf("fpanr(%s,%d)\t   =\t%f = %s\n",string,prec,fpA,binString);
	}
	printf("\tprecision(%s)=%d\n",string,aPrec);
	fp2bin(currentA,binString);
	if(prec == -1) {
		printf("double(fpanr_add(a,b))=\t%f = %s\n",currentA,binString);
	} else {
		printf("double(fpanr(%s,%d))=\t%f = %s\n",string,prec,currentA,binString);
	}
}

int
main (void)
{
	/* double numbers */
	double a,b,res;
	/* fpanr numbers */
	double fpA,fpB,fpRes;
	/* precisions of fpanr numbers */
	int rPrec, bPrec, aPrec;
	/* exponents */
	int rExp, aExp, bExp;
	/* values after reconversion */
	double currentA, currentB, currentRes;
	/* string to print binary numbers */
	char binString[FP2BIN_STRING_MAX];

	a = A_VAL;
	b = B_VAL;

	/* conversion with max precision by default */
	fpA = doubleToFpanrWithPrec(a, A_PREC);
	fpB = doubleToFpanrWithPrec(b, B_PREC);

	res = a + b;

	// -------------------------
	/* FIXME : ne pas passer par les types "double_st",
	 * mais appeler verificarlo sur le programme pour réaliser l'addition */
	double_st tmp, _a, _b;
	_a._value=fpA;
	_b._value=fpB;
	tmp._value=fpRes;
	d_add(&tmp,_a,_b);

	fpRes = tmp._value;
	// ----------------------------
	//	fpRes = doubleToFpanr(res);

	aPrec = getPrecFromFpanrDouble(fpA);
	bPrec = getPrecFromFpanrDouble(fpB);
	rPrec = getPrecFromFpanrDouble(fpRes);
	currentA = fpanrToDouble(fpA);
	currentB = fpanrToDouble(fpB);
	currentRes = fpanrToDouble(fpRes);
	frexp(currentA, &aExp);
	frexp(currentB, &bExp);
	frexp(currentRes, &rExp);

	printf("Paramètres initiaux :\n"
			"\ta=%f, b=%f, r=a+b=%f, \n"
			"\taExp=%d, aPrec=%d,  bExp=%d, bPrec=%d, rPrec=%d, rExp=%d\n",
		a, b, a+b,  aExp, aPrec, bExp, bPrec, rPrec, rExp);
	fflush(stdout);

//	printf("\n\n%f=%f+%f(%f)\n",currentRes,currentA,currentB,currentA+currentB);
//	printf("is res=a+b? %d (%s)\n\n",currentRes==currentA+currentB,currentRes==currentA+currentB?"yes":"no");


	printVal(a, fpA, currentA, aPrec, A_PREC, "a");

//	fp2bin(a,binString);
//	printf("\n\na\t\t   =\t%f = %s\n",a,binString);
//	fp2bin(fpA,binString);
//	printf("fpanr(a,26)\t   =\t%f = %s\n",fpA,binString);
//	printf("\taPrec=%d\n",aPrec);
//	fp2bin(currentA,binString);
//	printf("double(fpanr(a,26))=\t%f = %s\n",currentA,binString);


	printVal(b, fpB, currentB, bPrec, B_PREC, "b");

//	fp2bin(b,binString);
//	printf("\n\n_b=\t\t%f\t=%s\n",b,binString);
//	fp2bin(currentB,binString);
//	printf("currentB=\t%f\t=%s\n",currentB,binString);
//	fp2bin(fpB,binString);
//	printf("b._value=\t%f\t=%s\n",fpB,binString);
//	printf("bPrec=%d\n",aPrec);

	printVal(res, fpRes, currentRes, rPrec, -1, "a+b");
//	fp2bin(res,binString);
//	printf("\n\n_a+_b=\t\t%f\t=%s\n",a+b,binString);
//	fp2bin(currentRes,binString);
//	printf("currentRes\t%f\t=%s\n",currentRes,binString);
//	fp2bin(fpRes,binString);
//	printf("res._value=\t%f\t=%s\n",fpRes,binString);
//	printf("rPrec=%d\n",rPrec);

//	for(int i = 0 ; i < 10 ; ++i) {
//		printf("\ni=%d",i);
//		res += a;
//		fpRes = doubleToFpanrWithPrec(res,rPrec);
//		currentRes = fpanrToDouble(fpRes);
//		rPrec = getPrecFromFpanrDouble(fpRes);
//		fp2bin(res,binString);
//		printf("\n\nres+a=\t\t%f\t=%s\n",res,binString);
//		fp2bin(currentRes,binString);
//		printf("currentRes\t%f\t=%s\n",currentRes,binString);
//		fp2bin(fpRes,binString);
//		printf("res._value=\t%f\t=%s\n",fpRes,binString);
//		printf("rPrec=%d\n",rPrec);
//	}

	//	float f = 1.0/3.0;
//	printf("\nbefore conversion : %e, after conversion : %e, after conversion of the conversion : %e\n",f,floatToFpanr(f),fpanrToFloat(floatToFpanr(f)));

	return 0;
}
