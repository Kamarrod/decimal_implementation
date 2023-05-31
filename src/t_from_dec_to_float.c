#include "tests.h"

#define eps 1e-32
START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  long int c = 2147680256;
  src.bits[0] = 18122;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = c;

  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 1812;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0b10000000000000000000000000000000;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3_1) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = 0;
  setBit(&src, 127);
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_4) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 2345099;
  src.bits[1] = 0;
  src.bits[2] = 0;
  src.bits[3] = -2147287040;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.099);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_5) {
  s21_decimal src;
  int result = 0;
  float number = 0.0;
  src.bits[0] = 0b10000011111111010100000000000000;
  src.bits[1] = 0b11111111111111111111110001001011;
  src.bits[2] = 0;
  src.bits[3] = 0;
  result = s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 1.844674E+19);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_7) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b111000010010111000010;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b110010000000000000000;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 1.844674E-19);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_8) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b1001110100000000000000000000;
  dec.bits[1] = 0b11000111011101110100011010111111;
  dec.bits[2] = 0b11110100001000111111;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 1.844674E+25);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_9) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b11100110101;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b111000000000000000000;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_double_eq_tol(number, 1.845e-25, eps);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_10) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b1101111110000000000000000000000;
  dec.bits[1] = 0b10010111100000011001000111011010;
  dec.bits[2] = 0b1101101111100110111110111111100;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 3.402823E+28);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_11) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b11;
  dec.bits[1] = 0;
  dec.bits[2] = 0;
  dec.bits[3] = 0b111000000000000000000;
  result = s21_from_decimal_to_float(dec, &number);
  // ck_assert_float_eq(number, 3e-28);
  ck_assert_double_eq_tol(number, 3e-28, eps);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_12) {
  s21_decimal dec;
  int result = 0;
  float number = 0.0;
  dec.bits[0] = 0b11000111001000111000000000000000;
  dec.bits[1] = 0b10010100011100101110110101110101;
  dec.bits[2] = 0b1000001111;
  dec.bits[3] = 0;
  result = s21_from_decimal_to_float(dec, &number);
  ck_assert_float_eq(number, 9.732131E+21);
  // ck_assert_double_eq_tol(number, 9.732131E+21, eps);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_float_13) {
  // 7054
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_float_14) {
  // 7073
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = -4.5;

  src1.bits[0] = 0b00000000000000000000000000101101;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -4.5);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_float_15) {
  // 7092
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = -5.49265;

  src1.bits[0] = 0b00000000000010000110000110010001;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000001010000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", -5.49265);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_float_16) {
  // 7111
  s21_decimal src1;

  float src2;
  float *srcp = &src2;
  // s21_decimal src1 = 2.5086531268974139743;

  src1.bits[0] = 0b01100101111011101101100101011111;
  src1.bits[1] = 0b01011100001001010100001101000110;
  src1.bits[2] = 0b00000000000000000000000000000001;
  src1.bits[3] = 0b00000000000100110000000000000000;
  s21_from_decimal_to_float(src1, srcp);
  char var3str[1000];
  char result[1000];
  snprintf(var3str, sizeof(var3str), "%.6f", 2.50865312689741);
  snprintf(result, sizeof(result), "%f", src2);
  ck_assert_str_eq(result, var3str);
}
END_TEST

START_TEST(s21_from_decimal_to_float_17) {
  s21_decimal src1;
  float dst;
  float check = 7922816200000000000000000000.0f;
  src1.bits[0] = -805306368;
  src1.bits[1] = -128223179;
  src1.bits[2] = 429496715;
  src1.bits[3] = 0;
  int code = s21_from_decimal_to_float(src1, &dst);
  ck_assert_double_eq_tol(dst, check, 5e+21);  //те разница в 8 цифре меньше 0,5
  ck_assert_int_eq(code, 0);
}
END_TEST

Suite *suite_from_decimal_to_float(void) {
  Suite *s = suite_create("s21_from_decimal_to_float");
  TCase *tc = tcase_create("case_from_decimal_to_float");

  tcase_add_test(tc, s21_from_decimal_to_float_1);
  tcase_add_test(tc, s21_from_decimal_to_float_2);
  tcase_add_test(tc, s21_from_decimal_to_float_3);
  tcase_add_test(tc, s21_from_decimal_to_float_3_1);

  tcase_add_test(tc, s21_from_decimal_to_float_4);
  tcase_add_test(tc, s21_from_decimal_to_float_5);

  tcase_add_test(tc, s21_from_decimal_to_float_7);
  tcase_add_test(tc, s21_from_decimal_to_float_8);
  tcase_add_test(tc, s21_from_decimal_to_float_9);

  tcase_add_test(tc, s21_from_decimal_to_float_10);
  tcase_add_test(tc, s21_from_decimal_to_float_11);
  tcase_add_test(tc, s21_from_decimal_to_float_12);
  tcase_add_test(tc, s21_from_decimal_to_float_13);
  tcase_add_test(tc, s21_from_decimal_to_float_14);
  tcase_add_test(tc, s21_from_decimal_to_float_15);
  tcase_add_test(tc, s21_from_decimal_to_float_16);
  tcase_add_test(tc, s21_from_decimal_to_float_17);

  suite_add_tcase(s, tc);
  return s;
}