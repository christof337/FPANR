/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/**
 * Functions in this file are named according to their function.
 * <ul>
 * 	<li> Test function names respect the following format "test_fpanr_<type>_<testedFunction>", <type> being "D" for double or "F" for float
 * 	<li> General function ends with "<X><type>", X being "B" for Binary, indicating a binary operator, "U" for Unary, and Type is "D" for double or "F" for float
 */

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/FPANRlib.h"

#define MAX(A,B) (((A)>(B)) ? (A) : (B))
#define MIN(A,B) (((A)<(B)) ? (A) : (B))

enum varEnum {
	varEnumA,
	varEnumB,
	varEnumLast
};

// feel free to add values
double defaultAValues[] = {1.1};
double defaultBValues[] = {2.643};

double * defaultValues[] = {defaultAValues, defaultBValues};

int defaultAPrec[] = {43};
int defaultBPrec[] = {36};

int * defaultPrec[] = {defaultAPrec,defaultBPrec};

double_st a,b,res, expected1, expected2;
double _a,_b;
double currentA, currentB, currentRes;
int aPrec, bPrec, rPrec;
int rExp, aExp, bExp;

void basicTestInitUD(double_st * a, double * _a, double * currentA,
		int * aPrec,int * aExp, enum varEnum vE) {

	   // initializations
	    *_a=defaultValues[vE][0];

	    a->_value = *_a;

//		d_setPrecMax(a);

		d_setPrec(a,defaultPrec[vE][0]);

		// retrieve needed values for a and b
		*aPrec = d_getPrec(*a);
		*currentA = d_getVal(*a,aPrec);
		frexp(*currentA, aExp);
}

void basicTestInitBD(double_st * a, double_st * b, double * _a, double * _b, double * currentA,
		double * currentB, int * aPrec,	int * bPrec, int * aExp, int * bExp) {
	basicTestInitUD(a,_a,currentA,aPrec,aExp,varEnumA);
	basicTestInitUD(b,_b,currentB,bPrec,bExp,varEnumB);
}

void setupBD(void)
{
	basicTestInitBD(&a,&b, &_a, &_b, &currentA, &currentB, &aPrec, &bPrec, &aExp, &bExp);
}

void setupUD(void) {
	basicTestInitUD(&a, &_a, &currentA, &aPrec, &aExp, varEnumA);
}

void teardown(void) {

}

void basicPostTest(int * rPrec, double_st * res, double * currentRes, int * rExp, double_st * expected1, double_st * expected2) {
	// getting needed values
	*rPrec = d_getPrec(*res);
	*currentRes = d_getVal(*res,rPrec);
	frexp(*currentRes, rExp);
	d_setPrec(expected1,*rPrec);
	d_setPrec(expected2,*rPrec);
}

START_TEST(test_fpanr_d_getVal)
{
	b._value = a._value;

	// repeatable
	currentA = d_getVal(a, &aPrec);
	a._value = currentA;
	d_setPrec(&a,aPrec);

	ck_assert(b._value == a._value);
	ck_assert(d_getVal(b,&bPrec)==d_getVal(a,&aPrec));
}
END_TEST

START_TEST(test_fpanr_d_sqrt)
{
	// setting expected values
	expected1._value = sqrt(currentA);
	expected2._value = sqrt(_a);

	// --------------------
	// tested function call
	// --------------------
	d_sqrt(&res,a);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	// alpha x + 1
	ck_assert_int_eq(rPrec,aPrec+1);
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

START_TEST(test_fpanr_d_exp)
{
	// setting expected values
	expected1._value = exp(currentA);
	expected2._value = exp(_a);

	// --------------------
	// tested function call
	// --------------------
	d_exp(&res,a);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	// alpha x + 1
	ck_assert_int_eq(rPrec,aPrec-log2(currentA));
	ck_assert_int_eq(rPrec,aPrec-log2(_a));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
//	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

//TODO : finir les opérations unaires
START_TEST(test_fpanr_d_log)
{

}
END_TEST

START_TEST(test_fpanr_d_sin)
{

}
END_TEST

START_TEST(test_fpanr_d_cos)
{

}
END_TEST

START_TEST(test_fpanr_d_add)
{
	// setting expected values
	expected1._value = currentA+currentB;
	expected2._value = _a+_b;

	// --------------------
	// tested function call
	// --------------------
	d_add(&res,a,b);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	ck_assert_int_eq(rPrec,rExp-MAX((aExp-aPrec),(bExp-bPrec)));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
//	ck_assert(d_getVal(res,&rPrec)==d_getVal(a,&rPrec)+d_getVal(b,&rPrec));
}
END_TEST

START_TEST(test_fpanr_d_sub)
{
	// setting expected values
	expected1._value = currentA-currentB;
	expected2._value = _a-_b;

	// --------------------
	// tested function call
	// --------------------
	d_sub(&res,a,b);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	ck_assert_int_eq(rPrec,rExp-MAX((aExp-aPrec),(bExp-bPrec)));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

START_TEST(test_fpanr_d_mul)
{
	// setting expected values
	expected1._value = currentA*currentB;
	expected2._value = _a*_b;

	// --------------------
	// tested function call
	// --------------------
	d_mul(&res,a,b);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	ck_assert_int_eq(rPrec,MIN(aPrec,bPrec));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
//	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

START_TEST(test_fpanr_d_div)
{
	// setting expected values
	expected1._value = currentA/currentB;
	expected2._value = _a/_b;

	// --------------------
	// tested function call
	// --------------------
	d_div(&res,a,b);

	basicPostTest(&rPrec, &res, &currentRes, &rExp, &expected1, &expected2);

	// precision test
	ck_assert_int_eq(rPrec,MIN(aPrec,bPrec));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
//	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

Suite * fpanr_suite(void)
{
    Suite *s;
    TCase *tc_core_unary, *tc_core_binary, *tc_core;
    TCase *tc_limits;

    s = suite_create("FPANR");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setupBD, teardown);
    tcase_add_test(tc_core, test_fpanr_d_getVal);
    suite_add_tcase(s, tc_core);

    /* Unary operations test case */
    tc_core_unary = tcase_create("Core_double_unary_op");
    tcase_add_checked_fixture(tc_core_unary, setupUD, teardown);
    tcase_add_test(tc_core_unary, test_fpanr_d_sqrt);
    tcase_add_test(tc_core_unary, test_fpanr_d_exp);
    tcase_add_test(tc_core_unary, test_fpanr_d_log);
    tcase_add_test(tc_core_unary, test_fpanr_d_sin);
    tcase_add_test(tc_core_unary, test_fpanr_d_cos);
    suite_add_tcase(s, tc_core_unary);

    /* Binary operations test case */
    tc_core_binary = tcase_create("Core_double_binary_op");
    tcase_add_checked_fixture(tc_core_binary, setupBD, teardown);
    tcase_add_test(tc_core_binary, test_fpanr_d_add);
    tcase_add_test(tc_core_binary, test_fpanr_d_sub);
    tcase_add_test(tc_core_binary, test_fpanr_d_mul);
    tcase_add_test(tc_core_binary, test_fpanr_d_div);
    suite_add_tcase(s, tc_core_binary);

    /* Limits test case */
//    tc_limits = tcase_create("Limits");
//tc_core
//    tcase_add_test(tc_limits, test_money_create_neg);
//    tcase_add_test(tc_limits, test_money_create_zero);
//    suite_add_tcase(s, tc_limits);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = fpanr_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
