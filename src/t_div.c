#include "s21_decimal.h"

START_TEST(div1) {
  s21_decimal src1, src2, res_od;
  float a = 9403.0e2;
  int b = 202, ret;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 4654.950495049504950495049505;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div2) {
  s21_decimal src1, src2, res_od;
  int ret;
  int a = -32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = -16384;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div3) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -9403.0e2;
  float b = -2020.29;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 465.4282306005573457275935633;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div4) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -9403.0e2;
  float b = 2020.29;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -465.4282306005573457275935633;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div5) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -9403.0e20;
  float b = 2.28e17;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div6) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -0.9;
  float b = 30.323;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div7) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -0.9e3;
  float b = 30.32;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div8) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -0.9e3;
  int b = 30;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = a / b;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div9) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -0.9;
  float b = 0.000076;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a / b;
  ret = s21_div(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

// START_TEST(div10) {
//   s21_decimal src1, src2, res_od;
//   int ret;
//   s21_set_inf(&src1);
//   s21_set_inf(&src2);

//   ret = s21_div(src1, src2, &res_od);
//   float res;
//   s21_from_decimal_to_float(res_od, &res);
//   ck_assert_int_eq(ret, 0);
// }
// END_TEST

// START_TEST(div11) {
//   s21_decimal src1, src2, res_od;
//   int ret;
//   s21_from_int_to_decimal(10, &src1);
//   s21_from_int_to_decimal(0, &src2);
//   ret = s21_div(src1, src2, &res_od);
//   ck_assert_int_eq(s21_check_inf(res_od), 1);
//   float res;
//   s21_from_decimal_to_float(res_od, &res);
//   ck_assert_float_infinite(res);
//   ck_assert_int_eq(ret, 3);
// }
// END_TEST

// START_TEST(div13) {
//   s21_decimal src1, src2, res_od;
//   int ret;
//   float a = 1.0 / 0.0;
//   float b = 1.0 / 0.0;
//   float res_our_dec = 0.0;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_float_to_decimal(b, &src2);
//   ret = s21_div(src1, src2, &res_od);
//   s21_from_decimal_to_float(res_od, &res_our_dec);
//   ck_assert_int_eq(res_od.bits[2], 0);
//   ck_assert_int_eq(res_od.bits[1], 0);
//   ck_assert_int_eq(res_od.bits[0], 0);
//   float res;
//   s21_from_decimal_to_float(res_od, &res);
//   ck_assert_int_eq(ret, 0);

//   a = 1.0 / 0.0;
//   b = 2;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_float_to_decimal(b, &src2);
//   ret = s21_div(src1, src2, &res_od);
//   s21_from_decimal_to_float(res_od, &res_our_dec);
//   ck_assert_float_infinite(res_our_dec);
//   ck_assert_int_eq(ret, 1);

//   a = -1.0 / 0.0;
//   b = 2;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_float_to_decimal(b, &src2);
//   ret = s21_div(src1, src2, &res_od);
//   s21_from_decimal_to_float(res_od, &res_our_dec);
//   ck_assert_float_infinite(res_our_dec);
//   ck_assert_int_eq(ret, 2);
// }
// END_TEST

START_TEST(div15) {
  s21_decimal src1, src2, res_od;
  int ret;
  src1.bits[0] = 0b01110001001110010011101000100111;
  src1.bits[1] = 0b00000000000000000000000011100010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001010000000000000000;
  src2.bits[0] = 0b00000000000000010111101111011011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000100000000000000000;
  s21_decimal result_origin;
  result_origin.bits[0] = 0b00100000111100011100110110110001;
  result_origin.bits[1] = 0b01011000000100101111110011101001;
  result_origin.bits[2] = 0b00100000010100001110111000110111;
  result_origin.bits[3] = 0b00000000000110000000000000000000;
  ret = s21_div(src1, src2, &res_od);
  float a, b;
  s21_from_decimal_to_float(result_origin, &a);
  s21_from_decimal_to_float(res_od, &b);
  ck_assert_float_eq(a, b);
  ck_assert_int_eq(ret, 0);
}
END_TEST

START_TEST(div16) {
  s21_decimal src1, src2, res_od;
  int ret;
  src1.bits[0] = 0b00010001100000110100010101000111;
  src1.bits[1] = 0b00000000000000101011011100110010;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000001010000000000000000;
  src2.bits[0] = 0b01111001000001000011011001001011;
  src2.bits[1] = 0b00000000000000000101010011111111;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000001010000000000000000;
  s21_decimal result_origin;
  result_origin.bits[0] = 0b01000111110000001001001101101011;
  result_origin.bits[1] = 0b10111000000101111000101110100000;
  result_origin.bits[2] = 0b00011010011011010111110000110100;
  result_origin.bits[3] = 0b00000000000110110000000000000000;
  ret = s21_div(src1, src2, &res_od);

  float a, b;
  s21_from_decimal_to_float(result_origin, &a);
  s21_from_decimal_to_float(res_od, &b);
  ck_assert_float_eq(a, b);
  ck_assert_int_eq(ret, 0);
}
END_TEST

// START_TEST(div17) {
//   s21_decimal src1, src2, res_od;
//   int ret;
//   int a = -17272;
//   float b = -1.0 / 0.0;
//   s21_from_int_to_decimal(a, &src1);
//   s21_from_float_to_decimal(b, &src2);
//   ret = s21_div(src1, src2, &res_od);
//   s21_decimal zero = {{0, 0, 0, 0}};
//   ck_assert_int_eq(!!(s21_is_equal(res_od, zero) == 1), 1);
//   ck_assert_int_eq(res_od.bits[3], 0);
//   ck_assert_int_eq(res_od.bits[2], 0);
//   ck_assert_int_eq(res_od.bits[1], 0);
//   ck_assert_int_eq(res_od.bits[0], 0);
//   float c;
//   s21_from_decimal_to_float(res_od, &c);
//   ck_assert_float_eq(a / b, c);
//   ck_assert_int_eq(ret, 0);
// }
// END_TEST

// START_TEST(div19) {
//   s21_decimal src1, src2, res_od;
//   int ret;
//   float a = -115.2;
//   float b = 0.0;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_float_to_decimal(b, &src2);
//   ret = s21_div(src1, src2, &res_od);

//   ck_assert_int_eq(s21_check_inf(res_od), 1);
//   ck_assert_int_eq(s21_getsign(&res_od), 1);

//   ck_assert_int_eq(res_od.bits[2], 0);
//   ck_assert_int_eq(res_od.bits[1], 0);
//   ck_assert_int_eq(res_od.bits[0], 0);
//   float res;
//   s21_from_decimal_to_float(res_od, &res);
//   ck_assert_float_infinite(res);
//   ck_assert_int_eq(ret, 3);
// }
// END_TEST

Suite *suite_div(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_div");
  tc = tcase_create("case_div");

  tcase_add_test(tc, div1);
  tcase_add_test(tc, div2);
  tcase_add_test(tc, div3);
  tcase_add_test(tc, div4);
  tcase_add_test(tc, div5);
  tcase_add_test(tc, div6);
  tcase_add_test(tc, div7);
  tcase_add_test(tc, div8);
  tcase_add_test(tc, div9);
  // tcase_add_test(tc, div10);
  // tcase_add_test(tc, div11);
  // tcase_add_test(tc, div13);
  tcase_add_test(tc, div15);
  tcase_add_test(tc, div16);
  // tcase_add_test(tc, div17);
  // tcase_add_test(tc, div19);

  suite_add_tcase(s, tc);
  return s;
}