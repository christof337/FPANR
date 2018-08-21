#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atof */
#include <math.h>       /* float_t */

#include "../src/FPANRlib.h"

#define FFABS(A) (((A)>(0)) ? (A) : (-A))

void f(double_st * res, double_st x)
{
	double_st one;
	one._value = 1.0;
	d_setPrecMax(&one);
	d_sub(res, x, one);
	d_mul(res, *res, *res);
	d_sub(res, *res, one);
//	return (y-1)*(y-1)-1;
}

void df(double_st * res, double_st x)
{
//	printf("z=%e, %f",z,z);
//	getchar();
//	double x = z;
	double_st one, two;
	one._value = 1.0;
	two._value = 2.0;
	d_setPrecMax(&one);
	d_setPrecMax(&two);
//	printf("\nx=%e",x);
	d_sub(res, x, one);
//	printf("\nx=%e",x);
	d_mul(res, x, two);
//	x = x * 2.0;
//	printf("\nx=%e",x);
	// (x-1)*2
//	return 2.0*(z-1.0);
}

double_st newton(double_st x0,double_st eps)
{
	int i=0,p;
//	printf("\nstep 1\n");
	double_st x, y, z;
	f(&y,x0);
	df(&z,x0);
//	printf("f(x0)=%e,df(x0)=%e\n",f(x0),x);
	d_div(&x,y,z);
//	x = f(x0)/df(x0);
//	printf("step 2\nx=%e,x0=%e,x-x0=%e,eps=%e,FFABS((x-x0))=%e\n",x,x0,x-x0,eps,FFABS(x-x0));
	d_sub(&x, x0, x);
//	x = x0-x;
//	printf("step 3\nx=%e,x0=%e,x-x0=%e,eps=%e,FFABS((x-x0))=%e\n",x,x0,x-x0,eps,FFABS(x-x0));
	double_st diff;
	do {
		// x0=x;
		d_set(&x0,x);
		// x=x0-f(x0)/df(x0);
		f(&y,x0);
		df(&z,x0);
		d_div(&x,y,z);
		d_sub(&x,x0,x);

		d_sub(&diff,x,x0);
		d_fabs(&diff,diff);
	} while(d_getVal(diff,&p)>d_getVal(eps,&p));
//	while (FFABS((x-x0))>eps)
//	{
//		//printf("%d, ",i++);
//		x0=x;
//		x=x0-f(x0)/df(x0);
//		//printf("fin");
//	};
//	printf("step 4\n");
	return x;
}

int main()
{
	double_st x0, eps, itEps;
	int p;
	x0._value=125;
	d_setPrecMax(&x0);
	eps._value=1e-18;
	d_setPrecMax(&eps);

	printf("\n---------Newton's method - with FPANR---------\n");
	printf("\nFor f(x)=(x-1)*(x-1)-1\n");
	printf("x0=%f, eps=%e, step*=10\n",d_getVal(x0,&p),d_getVal(eps,&p));

	for (long i=1 ; itEps._value=1./i,d_setPrecMax(&itEps),d_getVal(itEps,&p)>d_getVal(eps,&p) /* && i<1e13 */ ; i*=10) {
		printf("eps=%e,x=%1.16f\n",d_getVal(itEps,&p),d_getVal(newton(x0,itEps),&p));
	}
	return 0;
}
