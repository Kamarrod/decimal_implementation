#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#include <limits.h>
#include <math.h>
#include <stdio.h>

#include "check.h"
// typedef enum {
//     NORM,
//     INF,
//     N_INF,
//     NAN,
//     DOP_CODE
// } value_type_t;

#define s21_INFINITY 1.0 / 0.0
#define s21_NAN -0.0 / 0.0

typedef struct {
  unsigned int bits[4];
  // value_type_t value_type;
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal divident, s21_decimal divisor, s21_decimal *result);
int s21_mul(s21_decimal number_1, s21_decimal number_2, s21_decimal *res);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);

int getBit(s21_decimal d, int i);
void setBit(s21_decimal *d, int i);
void setScale(s21_decimal *d, int i);
int _mult_10_dec(s21_decimal *d, int* shift10);
int getSign(s21_decimal src);
int getScale(s21_decimal d);
s21_decimal s21_add_bits(s21_decimal *value1, s21_decimal *value2);
s21_decimal s21_check_boundary(s21_decimal value1, s21_decimal value2);
s21_decimal s21_div_bits(s21_decimal a, s21_decimal b, s21_decimal *rem);
int s21_check_inf(s21_decimal value);
int s21_get_bit(const s21_decimal value, int bit);
int s21_getsign(const s21_decimal *value);
int s21_get_scale(const s21_decimal *value);
void s21_level_scale(s21_decimal *value1, s21_decimal *value2);
void s21_set_inf(s21_decimal *value);
int s21_are_zero(s21_decimal a, s21_decimal b);
void s21_copy_bits(s21_decimal source, s21_decimal *dest);
void s21_set_scale(s21_decimal *value, int scale);
void s21_set_bit(s21_decimal *value, int bit, int new_bit);
void s21_setsign(s21_decimal *value, int sign);
int s21_are_inf_new(s21_decimal *value1, s21_decimal *value2);
void s21_set0bitstype(s21_decimal *value);
void s21_set0bits(s21_decimal *ptr);
int s21_last_bit(s21_decimal value);
void s21_shift_left(s21_decimal *value, int offset);
s21_decimal check_for_mul(s21_decimal value1, s21_decimal value2);
void to_addcode(s21_decimal *value);

int s21_is_less(s21_decimal first, s21_decimal second);
int s21_is_less_or_equal(s21_decimal first, s21_decimal second);
int s21_is_greater(s21_decimal first, s21_decimal second);
int s21_is_greater_or_equal(s21_decimal first, s21_decimal second);
int s21_is_equal(s21_decimal first, s21_decimal second);
int s21_is_not_equal(s21_decimal first, s21_decimal second);

Suite *test_from_float_to_decimal(void);
Suite *suite_from_decimal_to_float(void);
Suite *suite_from_int_to_decimal(void);
Suite *suite_from_decimal_to_int(void);
Suite *suite_add(void);
Suite *suite_sub(void);
Suite *suite_is_less(void);
Suite *suite_mul(void);
Suite *suite_div(void);
#endif // S21_DECIMAL_H