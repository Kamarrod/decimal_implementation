#include "s21_decimal.h"

START_TEST(floor_1) {
  float num1 = 6268.843;
  float num2 = 6268;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(floor_2) {
  float num1 = -6268.843;
  float num2 = -6269;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal value;
  s21_decimal result;
  value.bits[3] = 0;
  value.bits[2] = 0;
  value.bits[1] = 0;
  value.bits[0] = 0;
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(value.bits[i], result.bits[i]);
}
END_TEST

START_TEST(floor_4) {
  float num1 = 0.1232424;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = 0;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 0;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
  {
    ck_assert_int_eq(out.bits[i], result.bits[i]);
  }
}
END_TEST


START_TEST(floor_5) {
  float num1 = -0.000000123;
  float num2 = -1;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_floor(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(floor_6) {
  s21_decimal value = {{0b1011100000110100001010010010010, 0b111000000110000000101, 0, 0b1100000000000000000}};
  s21_decimal out = {{0b11010110100011001100001100011011,0b1,0,0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_1)
{
  float num1 = 12321.12321;
  float num2 = 12321;
  s21_decimal value ={{0,0,0,0}};;
  s21_decimal result ={{0,0,0,0}};
  s21_decimal out ={{0,0,0,0}};;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(truncate_2)
{
  float num1 = -12321.12321;
  float num2 = -12321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(truncate_3)
{
  float num1 = 16.00000000012321;
  float num2 = 16;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  s21_from_float_to_decimal(num2, &out);
  s21_from_float_to_decimal(num1, &value);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(truncate_4)
{
  float num1 = 0.12321;
  s21_decimal out;
  s21_decimal value;
  s21_decimal result;
  out.bits[3] = 0;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 0;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  // printf("%d %d %d %d\n", out.bits[0], out.bits[1], out.bits[2], out.bits[3]);
  // printf("%d %d %d %d\n", result.bits[0], result.bits[1], result.bits[2], result.bits[3]);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST



START_TEST(truncate_5)
{
  float num1 = -0.12321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = -2147483648;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 0;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);  
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(truncate_6) {
  s21_decimal value = {{0b101110000011010000101001001001, 0 ,0, 0b1010000000000000000}};
  s21_decimal out =   {{0b1111000101110,0,0,0}};
  s21_decimal result = {{0, 0, 0, 0}};
  // printf("Value = %d %d %d %d\n", value.bits[0], value.bits[1], value.bits[2], value.bits[3]);
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value = {{0b101110000011010000101001001001, 0, 0, 0b10000000000001010000000000000000}};
  s21_decimal out = {{0b1111000101110, 0, 0 ,0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  // printf("%d %d %d %d\n", result.bits[0], result.bits[1], result.bits[2], result.bits[3]);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_8) {
    s21_decimal value = {{0b01101110000011010000101001001001, 0b1, 0, 0b10000000000001010000000000000000}};
    int res = s21_truncate(value, NULL);
    ck_assert_int_eq(res, 1);
}

START_TEST(truncate_9) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal value = {{0b01101110000011010000101001001001, 0b0000000000000000000000000000001, 0, 0b110000000000000000}};
  s21_decimal out = {{0b10111011011010110000011, 0, 0 ,0}};

  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_10) {
  // 6871
  s21_decimal value, out;
  // src1 = -545454512454545.35265454545645;

  value.bits[0] = 0b10000010111000100101101011101101;
  value.bits[1] = 0b11111001111010000010010110101101;
  value.bits[2] = 0b10110000001111101111000010010100;
  value.bits[3] = 0b10000000000011100000000000000000;
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  out.bits[0] = 0b10000110011101001011101110010001;
  out.bits[1] = 0b00000000000000011111000000010110;
  out.bits[2] = 0b00000000000000000000000000000000;
  out.bits[3] = 0b10000000000000000000000000000000;
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_11) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal value = {{0b10111110100110010001101010000011, 0b0000000000000000000000000000111, 0, 0b110000000000000000}};
  s21_decimal out = {{0b1111110111000101110001011, 0, 0 ,0}};

  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_12) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal value = {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0}};
  s21_decimal out = {{0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0b11111111111111111111111111111111, 0}};

  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(truncate_13) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal value = {{0b01100101111011101101100101011111, 0b01011100001001010100001101000110, 0b00000000000000000000000000000001, 0b00000000000100110000000000000000}};
  s21_decimal out = {{0b00000000000000000000000000000010, 0b00000000000000000000000000000000, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}

START_TEST(round_1)
{
  float num1 = -0.12321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = -2147483648;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 0;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST



START_TEST(round_2)
{
  float num1 = -1;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = -2147483648;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 1;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST



START_TEST(round_3)
{
  float num1 = -2.62321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = -2147483648;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 3;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(round_4)
{
  float num1 = 10.05321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = 0;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 10;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(round_5)
{
  float num1 = 2.62321;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = 0;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 3;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(round_6)
{
  float num1 = 0.00009;
  s21_decimal value;
  s21_decimal result;
  s21_decimal out;
  out.bits[3] = 0;
  out.bits[2] = 0;
  out.bits[1] = 0;
  out.bits[0] = 0;
  s21_from_float_to_decimal(num1, &value);
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST


START_TEST(round_7) {
  s21_decimal value = {{0b01011100000110100001010010010010, 0b111000000110000000101, 0, 0b1100000000000000000}};
  s21_decimal out = {{0b11010110100011001100001100011011,0b1,0,0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int res = s21_round(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}
END_TEST

START_TEST(round_8) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal value = {{0b01100101111011101101100101011111, 0b01011100001001010100001101000110, 0b00000000000000000000000000000001, 0b00000000000100110000000000000000}};
  s21_decimal out = {{0b00000000000000000000000000000011, 0, 0, 0}};
  int res = s21_truncate(value, &result);
  ck_assert_int_eq(res, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]);
}

START_TEST(negate_1) {
  s21_decimal value = {{0b01011100000110100001010010010010, 0b111000000110000000101, 0, 0b1100000000000000000}};
  s21_decimal out = {{0b01011100000110100001010010010010,0b111000000110000000101, 0, 0b10000000000001100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_2) {
  s21_decimal value = {{0b01011100000110100001010010010010, 0b111000000110000000101, 0, 0b10000000000001100000000000000000}};
  s21_decimal out = {{0b01011100000110100001010010010010,0b111000000110000000101, 0, 0b1100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_3) {
  s21_decimal value = {{0b01011100000110100001010010010010, 0b111000000110000000101, 0b1111100, 0b10000000000001100000000000000000}};
  s21_decimal out = {{0b01011100000110100001010010010010,0b111000000110000000101, 0b1111100, 0b1100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_4) {
  s21_decimal value = {{0, 0, 0, 0b10000000000000000000000000000000}};
  s21_decimal out = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_5) {
  s21_decimal value = {{0, 0, 0b1, 0b10000000000000000000000000000000}};
  s21_decimal out = {{0, 0, 0b1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_6) {
  s21_decimal value = {{0, 24, 0b1001, 0b10000000000111100000000000000000}};
  s21_decimal out = {{0, 24, 0b1001, 0b111100000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST

START_TEST(negate_7) {
  s21_decimal value = {{111, 1234, 56, 0}};
  s21_decimal out = {{111, 1234, 56, 0b10000000000000000000000000000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(value, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(out.bits[i], result.bits[i]); 
}
END_TEST


///
START_TEST(s21_round_1) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101;  // -16.5
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal dec1;
  dec1.bits[0] = 0b11111111111111111111111111111111;  // 18014398509481.983
  dec1.bits[1] = 0b00000000001111111111111111111111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000110000000000000000;
  s21_decimal result;

  result.bits[0] = 0b01001101110100101111000110101001;  // 18014398509481
  result.bits[1] = 0b00000000000000000001000001100010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000011110111001001110100;  // -10123.40
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000001111110100;  // -1012
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10000000000000000000001111110100;  // 112590205.4327284
  dec1.bits[1] = 0b00000000000001000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000001110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000110101101011111110101111101;  // 112590205
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10000000000000000000001111110100;  // 2147484660
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01100011000011111111111111111111;
  dec1.bits[1] = 0b01101011110001110101111000101101;
  dec1.bits[2] = 0b00000000000000000000000000000101;
  dec1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b01010100000010111110010000000000;
  result.bits[1] = 0b00000000000000000000000000000010;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal dec1;

  dec1.bits[0] = 0b11001101110001110111110001000000;
  dec1.bits[1] = 0b00111110001001010000001001100000;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b10000000000001000000000000000000;
  s21_decimal result;
  result.bits[0] = 0b10100000111111100100111000000100;
  result.bits[1] = 0b00011011110011101100110011101101;
  result.bits[2] = 0b00000000000000001101001111000010;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_round(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST



START_TEST(s21_floor_2) {
  s21_decimal dec1;
  dec1.bits[0] = 0b00000000000000000000000010100101;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000010000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000010000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111111111111110001010010;  // 2483027.026
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000000110000000000000000;  // 3
  s21_decimal result;
  result.bits[0] = 0b00000000001001011110001101010011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111111111111110001010011;
  dec1.bits[1] = 0b00000000000000000000000000000000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000000110000000000000000;
  s21_decimal result;
  result.bits[0] = 0b00000000001001011110001101010100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal dec1;

  dec1.bits[0] = 0b00001111111111111111111111111111;
  dec1.bits[1] = 0b00111110001001010000001001100001;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b10100111011000111111111111111111;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal dec1;

  dec1.bits[0] = 0b00001111111111111111111111111111;
  dec1.bits[1] = 0b00111110001001010000001001100001;
  dec1.bits[2] = 0b00100000010011111100111001011110;
  dec1.bits[3] = 0b10000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b10100111011001000000000000000000;
  result.bits[1] = 0b00001101111000001011011010110011;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10111101001001111000010001010010;
  dec1.bits[1] = 0b00000000000000000000000000011100;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000010010000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111100;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_9) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b10000000000100100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000001;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b10000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_10) {
  s21_decimal dec1;

  dec1.bits[0] = 0b01010101001110101110101110110001;
  dec1.bits[1] = 0b00001101101101001101101001011111;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000100100000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000000000000;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_11) {
  s21_decimal dec1;

  dec1.bits[0] = 0b10010111011100111001111111111111;
  dec1.bits[1] = 0b00111100000010000011000110001101;
  dec1.bits[2] = 0b00000000000000000000000000000001;
  dec1.bits[3] = 0b00000000000001110000000000000000;
  s21_decimal result;
  s21_floor(dec1, &result);
  s21_decimal result_origin;
  result_origin.bits[3] = 0;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0b00000000000000000000001000010010;
  result_origin.bits[0] = 0b00110110101101101000110000111111;
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floor_01) {
  s21_decimal dec1;
  dec1.bits[0] = 0b10010011111100000001110001010010;
  dec1.bits[1] = 0b00000000000000000000000100100000;
  dec1.bits[2] = 0b00000000000000000000000000000000;
  dec1.bits[3] = 0b00000000000010100000000000000000;
  float num = 0.0;
  s21_from_decimal_to_float(dec1, &num);
  s21_decimal result;
  result.bits[0] = 0b00000000000000000000000001111011;
  result.bits[1] = 0b00000000000000000000000000000000;
  result.bits[2] = 0b00000000000000000000000000000000;
  result.bits[3] = 0b00000000000000000000000000000000;
  s21_decimal res1;
  s21_floor(dec1, &res1);
  ck_assert_float_eq(res1.bits[0], result.bits[0]);
  ck_assert_float_eq(res1.bits[1], result.bits[1]);
  ck_assert_float_eq(res1.bits[2], result.bits[2]);
  ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floor_02) {
    s21_decimal dec1;
    dec1.bits[0] = 0b00000000000000000000000010100101;
    dec1.bits[1] = 0b00000000000000000000000000000000;
    dec1.bits[2] = 0b00000000000000000000000000000000;
    dec1.bits[3] = 0b00000000000000010000000000000000;
    float num = 0.0;
    s21_from_decimal_to_float(dec1, &num);
    // printf("%f", num);
    s21_decimal result;
    result.bits[0] = 0b00000000000000000000000000010000;
    result.bits[1] = 0b00000000000000000000000000000000;
    result.bits[2] = 0b00000000000000000000000000000000;
    result.bits[3] = 0b00000000000000000000000000000000;
    s21_decimal res1;
    s21_floor(dec1, &res1);
    ck_assert_float_eq(res1.bits[0], result.bits[0]);
    ck_assert_float_eq(res1.bits[1], result.bits[1]);
    ck_assert_float_eq(res1.bits[2], result.bits[2]);
    ck_assert_float_eq(res1.bits[3], result.bits[3]);
}
END_TEST

START_TEST(s21_floorTest1) {
  // 7130
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 2;

  src1.bits[0] = 0b00000000000000000000000000000010;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000000000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000010;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest2) {
  // 7151
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = 3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b00000000000000010000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000011;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b00000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(s21_floorTest3) {
  // 7172
  s21_decimal src1, origin, result = {{0, 0, 0, 0}};
  // src1 = -3.5;

  src1.bits[0] = 0b00000000000000000000000000100011;
  src1.bits[1] = 0b00000000000000000000000000000000;
  src1.bits[2] = 0b00000000000000000000000000000000;
  src1.bits[3] = 0b10000000000000010000000000000000;
  origin.bits[0] = 0b00000000000000000000000000000100;
  origin.bits[1] = 0b00000000000000000000000000000000;
  origin.bits[2] = 0b00000000000000000000000000000000;
  origin.bits[3] = 0b10000000000000000000000000000000;
  s21_floor(src1, &result);
  ck_assert_int_eq(origin.bits[3], result.bits[3]);
  ck_assert_int_eq(origin.bits[2], result.bits[2]);
  ck_assert_int_eq(origin.bits[1], result.bits[1]);
  ck_assert_int_eq(origin.bits[0], result.bits[0]);
}
END_TEST



START_TEST(negate_8) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {{0}};
  int sign_before = getSign(val);
  s21_negate(val, &res);
  int sign_after = getSign(res);

  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_9) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res;
  int sign_before = getSign(val);
  s21_negate(val, &res);
  int sign_after = getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_10) {
  s21_decimal val = {{0, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  int sign_before = getSign(val);
  s21_negate(val, &res);
  int sign_after = getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_11) {
  s21_decimal val = {{0}};
  s21_decimal res = {{0}};
  int sign_before = getSign(val);
  s21_negate(val, &res);
  int sign_after = getSign(res);
  ck_assert_int_ne(sign_before, sign_after);
}
END_TEST

START_TEST(negate_12) {
  s21_decimal value_1 = {{5, 0xFFFFFFFF, 0, 0b10000000000000000000000000000000}};
  s21_decimal check = {{5, 0xFFFFFFFF, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_13) {
  s21_decimal value_1 = {{1, 1, 1, 0}};
  s21_decimal check = {{1, 1, 1, 0x80000000}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(negate_14) {
  float a = 10.1234e5;
  float res_a = 0;
  s21_decimal src = {0};
  s21_from_float_to_decimal(a, &src);
  s21_decimal res = {0};
  s21_negate(src, &res);
  s21_from_decimal_to_float(res, &res_a);
  ck_assert_float_eq(-10.1234e5, res_a);
}
END_TEST

START_TEST(negate_15) {
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal minus_zero = {{0,0,0,  0b10000000000000000000000000000000}};
  s21_decimal res;
  int out = s21_negate(zero, &res);
  ck_assert_int_eq(out, 0);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(res.bits[i], minus_zero.bits[i]);
}
END_TEST

///




Suite* other_functions(void) {
  Suite* s = suite_create("tests");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_5);

  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);
  tcase_add_test(tc, truncate_9);
  tcase_add_test(tc, truncate_10);
  tcase_add_test(tc, truncate_11);
  tcase_add_test(tc, truncate_12);
  tcase_add_test(tc, truncate_13);
  
  

  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);  
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);
  tcase_add_test(tc, round_5);
  tcase_add_test(tc, round_6);
  tcase_add_test(tc, round_7); 

  tcase_add_test(tc, s21_round_1);
  tcase_add_test(tc, s21_round_2);
  tcase_add_test(tc, s21_round_3);
  tcase_add_test(tc, s21_round_4);
  tcase_add_test(tc, s21_round_5);
  tcase_add_test(tc, s21_round_6);
  tcase_add_test(tc, s21_round_7);
  tcase_add_test(tc, s21_round_8);
  tcase_add_test(tc, s21_round_9);
  tcase_add_test(tc, s21_round_10);

  tcase_add_test(tc, s21_floor_2);
  tcase_add_test(tc, s21_floor_3);
  tcase_add_test(tc, s21_floor_4);
  tcase_add_test(tc, s21_floor_5);
  tcase_add_test(tc, s21_floor_6);
  tcase_add_test(tc, s21_floor_7);
  tcase_add_test(tc, s21_floor_8);
  tcase_add_test(tc, s21_floor_9);
  tcase_add_test(tc, s21_floor_10);
  tcase_add_test(tc, s21_floor_11);
  tcase_add_test(tc, s21_floor_01);
  tcase_add_test(tc, s21_floor_02);
  tcase_add_test(tc, s21_floorTest1);
  tcase_add_test(tc, s21_floorTest2);
  tcase_add_test(tc, s21_floorTest3);

  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  tcase_add_test(tc, negate_7);
  tcase_add_test(tc, negate_8);
  tcase_add_test(tc, negate_9);
  tcase_add_test(tc, negate_10);
  tcase_add_test(tc, negate_11);
  tcase_add_test(tc, negate_12);
  tcase_add_test(tc, negate_13);
  tcase_add_test(tc, negate_14);
  tcase_add_test(tc, negate_15);

  
  suite_add_tcase(s, tc);

  return s;
}
