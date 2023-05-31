#include "s21_decimal.h"

int test_bit(unsigned int value, int BitNumber) {
  return value & (1 << BitNumber);
}

int convert(s21_decimal value) {
  int result = 0;
  int power = 1;
  for (int i = 16; i < 21; i++, power = power * 2)
    if (test_bit(value.bits[3], i)) {
      result = result + power;
    }
  return result;
}

void s21_truncate_buf(s21_decimal *buf, int exp) {
  for (int i = 0; i < exp; i++) {
    unsigned long long u_num;
    u_num = buf->bits[2];
    int j = 2;
    for (; j >= 0; j--) {
      if (j == 0) {
        buf->bits[j] = u_num / 10;
      } else {
        int tmp_int = 0;
        tmp_int = u_num % 10;  // запомнили первый разряд который мы отнимаем
        buf->bits[j] = u_num / 10;  // получили в последнем инте валуе получили
                                    // последний инт резалта
        u_num = tmp_int * (4294967296) + buf->bits[j - 1];
      }
    }
  }
  buf->bits[3] = 0;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int rv = 1;
  if (result) {
    int exp = convert(value);
    int sign = getSign(value);
    if (exp != 0) {
      s21_decimal buf = {0};
      buf = value;
      s21_truncate_buf(&buf, exp);
      *result = buf;
    } else {
      *result = value;
    }
    if (sign) {
      setBit(result, 127);
    }
    rv = 0;
  }
  return rv;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int rv = 1;
  if (result && !s21_check_inf(value)) {
    int sign = getSign(value);
    if (getScale(value) == 0) {
      *result = value;
    } else {
      s21_truncate(value, result);
      s21_decimal one = {{1, 0, 0, 0}};
      s21_decimal half_one = {{5, 0, 0, 0b10000000000000000}};
      s21_decimal copy = {
          {value.bits[0], value.bits[1], value.bits[2], value.bits[3]}};
      if (sign) {
        s21_decimal sub = {{0, 0, 0, 0}};
        s21_sub(*result, copy, &sub);
        if (s21_is_greater_or_equal(sub, half_one) == 1) {
          s21_decimal resultCopy = {{result->bits[0], result->bits[1],
                                     result->bits[2], result->bits[3]}};
          s21_sub(resultCopy, one, result);
        }
      } else {
        s21_decimal sub = {{0, 0, 0, 0}};
        s21_sub(copy, *result, &sub);
        if (s21_is_greater_or_equal(sub, half_one) == 1) {
          s21_decimal resultCopy = {{result->bits[0], result->bits[1],
                                     result->bits[2], result->bits[3]}};
          s21_add(resultCopy, one, result);
        }
      }
    }
    rv = 0;
  }
  if (result && (s21_check_inf(value))) {
    *result = value;
    rv = 0;
  }
  return rv;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int rv = 1;
  if (result) {
    if (s21_check_inf(value)) {
      *result = value;
    } else {
      int scale = getScale(value);
      s21_truncate(value, result);
      if (getSign(value)) {
        if (scale != 0) {
          s21_decimal one = {{1, 0, 0, 0}};
          s21_sub(*result, one, result);
        }
      }
    }
    rv = 0;
  }
  return rv;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int rv = 1;
  if (result) {
    result->bits[0] = value.bits[0];
    result->bits[1] = value.bits[1];
    result->bits[2] = value.bits[2];
    result->bits[3] = value.bits[3];
    if (!getSign(value)) {
      setBit(result, 127);
    } else {
      int i = 127;
      unsigned int mask = 1u << (i % 32);
      mask = ~mask;
      result->bits[i / 32] &= mask;
    }
    rv = 0;
  }
  return rv;
}