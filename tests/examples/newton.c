#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atof */
#include <math.h>       /* float_t */

#define FFABS(A) (((A)>(0)) ? (A) : (-A))

double f(double y)
{
	return (y-1)*(y-1)-1;
}

double df(double z)
{
//	printf("z=%e, %f",z,z);
//	getchar();
//	double x = z;
//	double y = 1.0;
//	printf("\nx=%e",x);
//	x = z - y;
//	printf("\nx=%e",x);
//	x = x * 2.0;
//	printf("\nx=%e",x);
	return 2.0*(z-1.0);
}

double newton(double x0,double eps)
{
	int i=0;
	// x=x0-f(x0)/df(x0);
//	printf("\nstep 1\n");
	double x = df(x0);
//	printf("f(x0)=%e,df(x0)=%e\n",f(x0),x);
	x = f(x0)/df(x0);
//	printf("step 2\nx=%e,x0=%e,x-x0=%e,eps=%e,FFABS((x-x0))=%e\n",x,x0,x-x0,eps,FFABS(x-x0));
	x = x0-x;
//	printf("step 3\nx=%e,x0=%e,x-x0=%e,eps=%e,FFABS((x-x0))=%e\n",x,x0,x-x0,eps,FFABS(x-x0));
	while (FFABS((x-x0))>eps)
	{
		//printf("%d, ",i++);
		x0=x;
		x=x0-f(x0)/df(x0);
		//printf("fin");
	};
//	printf("step 4\n");
	return x;
}

int main()
{
	double x0=125, eps=1e-18;

	printf("\n---------Newton's method - without FPANR---------\n");
	printf("\nFor f(x)=(x-1)*(x-1)-1\n");
	printf("x0=%f, eps=%e, step*=10\n",x0,eps);

	for (long i=1;1./i>eps /*&& i<1e13*/;i*=10) {
		printf("eps=%e,x=%1.16f\n",1./i,newton(x0,1./i));
	}
	return 0;
}
