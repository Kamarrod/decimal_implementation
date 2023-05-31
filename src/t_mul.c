#include "s21_decimal.h"

START_TEST(mul1) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul1_1) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = 1.23456789;
  int b = 2.34567891;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = a * b;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq_tol(res_our_dec, res_origin, 1e-6);
  ck_assert_ldouble_eq_tol(res_our_dec, res_origin, 1e-6);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul2) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = 9403.0e2;
  float b = 9403.0e2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 884164090000;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul3) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = 9403;
  int b = 202;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 1899406;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul4) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = -32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -65536;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul41) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = -3;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -6;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul5) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = -32768;
  int b = 32768;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -1073741824;
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul6) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  float a = 1.0 / 0.0;
  int b = 0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(mul7) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  int ret = 0;
  float a = 1.0 / 0.0;
  float b = 132;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  // ck_assert_float_infinite(res_our_dec);
  ck_assert_float_eq(s21_check_inf(res_od), 0);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul8) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  int ret = 0;
  float a = 1.0 / 0.0;
  float b = 1.0 / 0.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  ret = s21_mul(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  // ck_assert_float_infinite(res_our_dec);
  ck_assert_float_eq(s21_check_inf(res_od), 0);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(mul9) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  float a = 1.0 / 0.0;
  float b = 0.0 * 2 / 3 * 0.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mul(src1, src2, &res_od);  // ret =
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(mul15) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  float a = 1.0 / 0.0;
  int b = 0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  s21_mul(src1, src2, &res_od);  // ret =
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(mul16) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  float a = -1.0 / 0.0;
  float b = 0.0 * 2 / 3 * 0.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mul(src1, src2, &res_od);  // ret =
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(mul17) {
  s21_decimal src1 = {0}, src2 = {0}, res_od = {0};
  float a = -1.0 / 0.0;
  float b = 0.0 * 2 / 3 * 0.0;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mul(src1, src2, &res_od);  // ret =
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_int_eq(res_od.bits[2], 0);
  ck_assert_int_eq(res_od.bits[1], 0);
  ck_assert_int_eq(res_od.bits[0], 0);
}
END_TEST

START_TEST(s21_mul_test) {
  s21_decimal result1 = {{0, 0, 0, 0}};
  s21_decimal result2 = {{0, 0, 0, 0}};
  s21_decimal case_full1 = {{123, 321, -2147483648, 0}};
  s21_decimal case_full2 = {{123, 321, -2147483648, 0}};
  s21_decimal case_max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int res_mul = -1;
  s21_decimal case_d = {{0, 0, 0, 0}};
  res_mul = s21_mul(case_d, case_max, &result1);
  ck_assert_int_eq(res_mul, 0);
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  res_mul = s21_mul(max, max, &result1);
  ck_assert_int_eq(res_mul, 0);
  int res_ful1 = 0;
  int res_ful2 = 0;
  res_ful1 = s21_mul(case_full1, case_full2, &result1);
  ck_assert_int_eq(res_ful1, 0);
  res_ful2 = s21_mul(case_full1, case_full2, &result2);
  setBit(&result2, 127);
  ck_assert_int_eq(res_ful2, 0);
}
END_TEST

Suite *suite_mul(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_mul");
  tc = tcase_create("case_mul");

  tcase_add_test(tc, mul1);
  tcase_add_test(tc, mul1_1);
  tcase_add_test(tc, mul2);
  tcase_add_test(tc, mul3);
  tcase_add_test(tc, mul4);
  tcase_add_test(tc, mul41);
  tcase_add_test(tc, mul5);
  tcase_add_test(tc, mul6);
  tcase_add_test(tc, mul7);
  tcase_add_test(tc, mul8);
  tcase_add_test(tc, mul9);
  tcase_add_test(tc, mul15);
  tcase_add_test(tc, mul16);
  tcase_add_test(tc, mul17);
  tcase_add_test(tc, s21_mul_test);

  suite_add_tcase(s, tc);
  return s;
}