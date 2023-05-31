#ifndef S21_TESTS_H
#define S21_TESTS_H

#include "check.h"
#include "s21_decimal.h"

Suite *test_from_float_to_decimal(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_int_to_decimal(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_comparisons(void);
Suite *suite_add(void);
Suite *suite_div(void);
Suite *suite_mul(void);
Suite *suite_sub(void);
Suite *other_functions(void);

#endif  // S21_TESTS_H