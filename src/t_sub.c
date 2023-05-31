#include "tests.h"

START_TEST(sub1) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = 9403;
  int b = 202;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 9201;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_int(res_od, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub2) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  int a = 9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 9200.902;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub3) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = -9403;
  float b = 202.098;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub4) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = 9403.0;
  float b = 202.09e8;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -20208990597;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub5) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = 9403.0e2;
  float b = 202.09e8;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -20208059700;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub6) {
  s21_decimal src1, src2, res_od;
  int ret = 0;
  float a = -9403.0e2;
  int b = -202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = a - b;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST

// START_TEST(sub7) {
//   s21_decimal src1, src2, res_od;
//   int ret = 0;
//   float a = -1.0 / 0.0;
//   int b = 202;
//   float res_our_dec = 0.0;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_int_to_decimal(b, &src2);
//   ret = s21_sub(src1, src2, &res_od);
//   s21_from_decimal_to_float(res_od, &res_our_dec);
//   ck_assert_float_eq(s21_check_inf(res_od), 1);
//   ck_assert_float_eq(s21_getsign(&res_od), 1);
//   // ck_assert_int_eq(res_od.bits[3], 0);
//   ck_assert_int_eq(res_od.bits[2], 0);
//   ck_assert_int_eq(res_od.bits[1], 0);
//   ck_assert_int_eq(res_od.bits[0], 0);
//   ck_assert_float_infinite(res_our_dec);
//   ck_assert_int_eq(ret, 2);

//   a = 1.0 / 0.0;
//   b = 202;
//   res_our_dec = 0.0;
//   s21_from_float_to_decimal(a, &src1);
//   s21_from_int_to_decimal(b, &src2);
//   ret = s21_sub(src1, src2, &res_od);
//   s21_from_decimal_to_float(res_od, &res_our_dec);
//   // ck_assert_float_eq(res_od.value_type, s21_infinity);
//   ck_assert_float_eq(s21_check_inf(res_od), 1);
//   // ck_assert_int_eq(res_od.bits[3], 0);
//   ck_assert_int_eq(res_od.bits[2], 0);
//   ck_assert_int_eq(res_od.bits[1], 0);
//   ck_assert_int_eq(res_od.bits[0], 0);
//   ck_assert_float_infinite(res_our_dec);
//   ck_assert_int_eq(ret, 1);

//   // float c = 2 * 0, d = 3 * 0;
//   // a = d / c;
//   // b = 202;
//   // res_our_dec = 0.0;
//   // s21_from_float_to_decimal(a, &src1);
//   // s21_from_int_to_decimal(b, &src2);
//   // ret = s21_sub(src1, src2, &res_od);
//   // s21_from_decimal_to_float(res_od, &res_our_dec);
//   // // ck_assert_float_eq(res_od.value_type, s21_nan);
//   // // ck_assert_int_eq(res_od.bits[3], 0);
//   // ck_assert_int_eq(res_od.bits[2], 0);
//   // ck_assert_int_eq(res_od.bits[1], 0);
//   // ck_assert_int_eq(res_od.bits[0], 0);
//   // ck_assert_float_nan(res_our_dec);
//   // // ck_assert_int_eq(ret, 0);
// }
// END_TEST
START_TEST(sub8) {
  s21_decimal src1, src2, res_od;
  int ret;
  float a = -94;
  float b = -202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = a - b;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);

  a = 2020;
  b = 94099992;
  res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  res_origin = a - b;
  ret = s21_sub(src1, src2, &res_od);
  s21_from_decimal_to_float(res_od, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub9) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub10) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0b00000000000000110000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000001000101000111010110;
  src2.bits[3] = 0b00000000000000010000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000000000000101110111100;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b10000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000000000000100001110011010;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub11) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0x80030000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFFFF;
  src1.bits[0] = 0xFF837E4F;
  src2.bits[3] = 0x80070000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFFF;
  src2.bits[0] = 0xFF837E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x80070000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x270FEFED;
  result_origin.bits[0] = 0x00F26FA1;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub12) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFFFF;
  src1.bits[0] = 0xFF837E4F;
  src2.bits[3] = 0x80070000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFFF;
  src2.bits[0] = 0xFF837E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x70000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x27100FEC;
  result_origin.bits[0] = 0xFFF96C3F;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub13) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0b10000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000000000100110000;
  src2.bits[3] = 0b10000000000001100000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00010001001000010001101001100000;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b00000000000001100000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00001111010100010011110001100000;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub14) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[3] = 0x80030000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFFFF;
  src1.bits[0] = 0xFF837E4F;
  src2.bits[3] = 0x70000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xFFF;
  src2.bits[0] = 0xFF837E4F;
  s21_decimal result_origin;
  result_origin.bits[3] = 0x80070000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x27100FEC;
  result_origin.bits[0] = 0xFFF96C3F;
  ret = s21_sub(src1, src2, &result_our);
  ck_assert_int_eq(result_origin.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub15) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  //   src1.value_type = src2.value_type = s21_usual;
  src1.bits[0] = 0b00000000000000000000011111100100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  src2.bits[0] = 0b00000101100110111101101000011001;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result;
  ret = s21_sub(src1, src2, &result_our);
  result.bits[0] = 0b00000101100110111101001000110101;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_int_eq(result.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST
START_TEST(sub16) {
  s21_decimal src1, src2, result_our;
  int ret = 0;
  src1.bits[0] = 0b00000000000000000000011111100100;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000000000000000000000;
  src2.bits[0] = 0b00000000000000000010010010111011;
  src2.bits[1] = 0b00000000000000000000000000000000;
  src2.bits[2] = 0b00000000000000000000000000000000;
  src2.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal result;
  ret = s21_sub(src1, src2, &result_our);
  result.bits[0] = 0b00000000000000000001110011010111;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;

  ck_assert_int_eq(result.bits[3], result_our.bits[3]);
  ck_assert_int_eq(result.bits[2], result_our.bits[2]);
  ck_assert_int_eq(result.bits[1], result_our.bits[1]);
  ck_assert_int_eq(result.bits[0], result_our.bits[0]);
  ck_assert_int_eq(ret, 0);
}
END_TEST

Suite *suite_sub(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("s21_sub");
  tc = tcase_create("case_sub");

  tcase_add_test(tc, sub1);
  tcase_add_test(tc, sub2);
  tcase_add_test(tc, sub3);
  tcase_add_test(tc, sub4);
  tcase_add_test(tc, sub5);
  tcase_add_test(tc, sub6);
  tcase_add_test(tc, sub8);
  tcase_add_test(tc, sub9);
  tcase_add_test(tc, sub10);
  tcase_add_test(tc, sub11);
  tcase_add_test(tc, sub12);
  tcase_add_test(tc, sub13);
  tcase_add_test(tc, sub14);
  tcase_add_test(tc, sub15);
  tcase_add_test(tc, sub16);

  suite_add_tcase(s, tc);
  return s;
}