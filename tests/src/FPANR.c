#include "src/FPANRlib.h"

#include <stdio.h>

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
    double _a=0.1,_b=0.5;

    a._value = _a;
	d_setPrecMax(a);
    b._value = _b;
	d_setPrecMax(b);

	d_add(&res,a,b);
	int rPrec = d_getPrec(res);
	int aPrec = d_getPrec(a);
	int bPrec = d_getPrec(b);

	printf("\n\n%f=%f+%f(%f)\n\n",d_getVal(res,&rPrec),d_getVal(a,&aPrec),d_getVal(b,&bPrec),d_getVal(a,&aPrec)+d_getVal(b,&bPrec));


    return 0;
}
