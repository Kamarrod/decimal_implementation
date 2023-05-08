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
#endif // S21_DECIMAL_H