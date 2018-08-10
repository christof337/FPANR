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

START_TEST(test_fpanr_d_add)
{
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

	ck_assert(a._value==_a);
	ck_assert(b._value==_b);
	ck_assert(res._value==_a+_b);
//	ck_assert(d_getVal(res,&rPrec)==(d_getVal(a,&aPrec)+d_getVal(b,&bPrec)));
//	printf("\n\n%f=%f+%f(%f)\n\n",d_getVal(res,&rPrec),d_getVal(a,&aPrec),d_getVal(b,&bPrec),d_getVal(a,&aPrec)+d_getVal(b,&bPrec));
}
END_TEST

Suite * fpanr_suite(void)
{
    Suite *s;
    TCase *tc_core;
    TCase *tc_limits;

    s = suite_create("FPANR");

    /* Core test case */
    tc_core = tcase_create("Core_add");

    tcase_add_test(tc_core, test_fpanr_d_add);
    suite_add_tcase(s, tc_core);

    /* Limits test case */
//    tc_limits = tcase_create("Limits");
//
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
