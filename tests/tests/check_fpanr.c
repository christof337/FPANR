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

#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/FPANRlib.h"

#define MAX(A,B) (((A)>(B)) ? (A) : (B))
#define MIN(A,B) (((A)<(B)) ? (A) : (B))

START_TEST(test_fpanr_d_add)
{
    double_st a,b,res, expected1, expected2;
    double _a,_b;
	double currentA, currentB, currentRes;
    int aPrec, bPrec, rPrec;
	int rExp, aExp, bExp;

    // initializations
    _a=1.1;
    _b=2.643;

    a._value = _a;
    b._value = _b;

	d_setPrecMax(&a);
	d_setPrecMax(&b);

//	d_setPrec(&a,34);
//	d_setPrec(&b,43);

	// retrieve needed values for a and b
	aPrec = d_getPrec(a);
	bPrec = d_getPrec(b);
	currentA = d_getVal(a,&aPrec);
	currentB = d_getVal(b,&bPrec);
	frexp(currentA, &aExp);
	frexp(currentB, &bExp);

	// setting expected values
	expected1._value = currentA+currentB;
	expected2._value = _a+_b;

	// --------------------
	// tested function call
	// --------------------
	d_add(&res,a,b);

	// getting needed values
	rPrec = d_getPrec(res);
	currentRes = d_getVal(res,&rPrec);
	frexp(currentRes, &rExp);
	d_setPrec(&expected1,rPrec);
	d_setPrec(&expected2,rPrec);

	// precision test
	ck_assert_int_eq(rPrec,rExp-MAX((aExp-aPrec),(bExp-bPrec)));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

START_TEST(test_fpanr_d_sub)
{
	double_st a,b,res, expected1, expected2;
	double _a,_b;
	double currentA, currentB, currentRes;
	int aPrec, bPrec, rPrec;
	int rExp, aExp, bExp;

	// initializations
	_a=1.1;
	_b=2.643;

	a._value = _a;
	b._value = _b;

	d_setPrecMax(&a);
	d_setPrecMax(&b);

	// retrieve needed values for a and b
	aPrec = d_getPrec(a);
	bPrec = d_getPrec(b);
	currentA = d_getVal(a,&aPrec);
	currentB = d_getVal(b,&bPrec);
	frexp(currentA, &aExp);
	frexp(currentB, &bExp);

	// setting expected values
	expected1._value = currentA-currentB;
	expected2._value = _a-_b;

	// --------------------
	// tested function call
	// --------------------
	d_sub(&res,a,b);

	// getting needed values
	rPrec = d_getPrec(res);
	currentRes = d_getVal(res,&rPrec);
	frexp(currentRes, &rExp);
	d_setPrec(&expected1,rPrec);
	d_setPrec(&expected2,rPrec);

	// precision test
	ck_assert_int_eq(rPrec,rExp-MAX((aExp-aPrec),(bExp-bPrec)));
	// numerical value test
	ck_assert(d_getVal(expected1,&rPrec)==currentRes);
	ck_assert(d_getVal(expected2,&rPrec)==currentRes);
}
END_TEST

Suite * fpanr_suite(void)
{
    Suite *s;
    TCase *tc_core_add,*tc_core_sub;
    TCase *tc_limits;

    s = suite_create("FPANR");

    /* Core test case */
    tc_core_add = tcase_create("Core_add");
    tcase_add_test(tc_core_add, test_fpanr_d_add);
    tc_core_sub = tcase_create("Core_sub");
    tcase_add_test(tc_core_sub, test_fpanr_d_sub);
    suite_add_tcase(s, tc_core_add);
    suite_add_tcase(s, tc_core_sub);

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
