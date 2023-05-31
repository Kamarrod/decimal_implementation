#include "s21_decimal.h"

s21_decimal s21_add_bits(s21_decimal *value1, s21_decimal *value2) {
  s21_decimal res = {{0, 0, 0, 0}};

  if (s21_are_inf_new(value1, value2)) {
    s21_set_inf(&res);
  } else {
    int buffer = 0;
    for (int i = 0; i < 96; i++) {
      int bit_value1 = s21_get_bit(*value1, i);
      int bit_value2 = s21_get_bit(*value2, i);

      if (!bit_value1 && !bit_value2) {
        if (buffer) {
          s21_set_bit(&res, i, 1);
          buffer = 0;
        } else {
          s21_set_bit(&res, i, 0);
        }
      } else if (bit_value1 != bit_value2) {
        if (buffer) {
          s21_set_bit(&res, i, 0);
          buffer = 1;
        } else {
          s21_set_bit(&res, i, 1);
        }
      } else {
        if (buffer) {
          s21_set_bit(&res, i, 1);
          buffer = 1;
        } else {
          s21_set_bit(&res, i, 0);
          buffer = 1;
        }
      }

      if (i == 95 && buffer == 1 && s21_get_bit(*value1, 126) != 1 &&
          s21_get_bit(*value2, 126) != 1)
        s21_set_inf(&res);
    }
  }

  return res;
}

s21_decimal s21_check_boundary(s21_decimal value1, s21_decimal value2) {
  s21_decimal res = {{0, 0, 0, 0}};
  if (s21_check_inf(value1) || s21_check_inf(value2)) s21_set_inf(&res);
  return res;
}

s21_decimal s21_div_bits(s21_decimal a, s21_decimal b, s21_decimal *rem) {
  s21_set0bitstype(rem);
  s21_decimal res = {{0, 0, 0, 0}};
  for (int i = s21_last_bit(a); i >= 0; i--) {
    if (s21_get_bit(a, i)) s21_set_bit(rem, 0, 1);
    if (s21_is_greater_or_equal(*rem, b)) {
      s21_sub(*rem, b, rem);
      if (i != 0) s21_shift_left(rem, 1);
      if (s21_get_bit(a, i - 1)) s21_set_bit(rem, 0, 1);
      s21_shift_left(&res, 1);
      s21_set_bit(&res, 0, 1);
    } else {
      s21_shift_left(&res, 1);
      if (i != 0) s21_shift_left(rem, 1);
      if ((i - 1) >= 0 && s21_get_bit(a, i - 1)) s21_set_bit(rem, 0, 1);
    }
  }
  return res;
}

int s21_check_inf(s21_decimal value) {
  int ret = 0;
  if ((s21_get_scale(&value) == 28) && (value.bits[0] == 0) &&
      (value.bits[1] == 0) && (value.bits[2] == 0))
    ret = 1;
  return ret;  // 0 - non inf, 1 - inf
}

int s21_get_bit(const s21_decimal value, int bit) {
  return (value.bits[bit / 32] & (1u << (bit % 32))) ? 1 : 0;
}

int s21_getsign(const s21_decimal *value) {
  return !!(value->bits[3] &
            0x80000000);  // use !! to get 1 in any event except 0
}

int s21_get_scale(const s21_decimal *value) {
  return (char)(value->bits[3] >> 16);
}

void s21_level_scale(s21_decimal *value1, s21_decimal *value2) {
  s21_decimal *bigger = value2, *smaller = value1, tmp = {{0, 0, 0, 0}};

  if (s21_get_scale(value1) > s21_get_scale(value2)) {
    bigger = value1;
    smaller = value2;
  }

  while (s21_get_scale(value1) != s21_get_scale(value2)) {
    if (!s21_check_inf(tmp)) {
      s21_decimal tmp1, tmp2;
      tmp1 = *smaller, tmp2 = *smaller;

      s21_shift_left(&tmp1, 1);
      s21_shift_left(&tmp2, 3);
      tmp = s21_add_bits(&tmp1, &tmp2);  // equals to multiplying by 10

      if (!s21_check_inf(tmp)) {
        s21_copy_bits(tmp, smaller);
        s21_set_scale(smaller, s21_get_scale(smaller) + 1);
      }
    } else {
      s21_decimal remainder, ten = {{10, 0, 0, 0}}, zero = {{0, 0, 0, 0}},
                             tmp2 = s21_div_bits(*bigger, ten, &remainder);

      if (s21_are_zero(tmp2, zero) == 1) {
        s21_copy_bits(tmp2, bigger);
      } else {
        s21_copy_bits(remainder, bigger);  // bigger = 0
      }
      s21_set_scale(bigger, s21_get_scale(bigger) - 1);
    }
  }
}

void s21_set_inf(s21_decimal *value) {
  s21_set_scale(value, 28);
  value->bits[0] = 0;
  value->bits[1] = 0;
  value->bits[2] = 0;
}

int s21_are_zero(s21_decimal a, s21_decimal b) {
  return (!a.bits[0] && !b.bits[0] && !a.bits[1] && !b.bits[1] && !a.bits[2] &&
          !b.bits[2])
             ? 0
             : 1;
}

void s21_copy_bits(s21_decimal source, s21_decimal *dest) {
  dest->bits[0] = source.bits[0];
  dest->bits[1] = source.bits[1];
  dest->bits[2] = source.bits[2];
}

void s21_set_scale(s21_decimal *value, int scale) {
  if (scale >= 0 && scale <= 28) {
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= scale << 16;
  }
}

void s21_set_bit(s21_decimal *value, int bit, int new_bit) {
  unsigned int mask = 1u << (bit % 32);
  if (new_bit) {
    value->bits[bit / 32] |= mask;
  } else {
    value->bits[bit / 32] &= ~mask;
  }
}

void s21_setsign(s21_decimal *value, int sign) {
  if (sign == 1) {
    value->bits[3] |= 0x80000000;
  } else {
    value->bits[3] &= ~0x80000000;
  }
}

int s21_are_inf_new(s21_decimal *value1, s21_decimal *value2) {
  int res = 0;
  if (!s21_check_inf(*value2) && s21_check_inf(*value1)) {
    res = 1;
  }
  if (!s21_check_inf(*value1) && s21_check_inf(*value2)) {
    res = -1;
  }
  if (s21_check_inf(*value2) && s21_check_inf(*value1)) {
    res = 2;
  }
  return res;  // 0 - не бесконечны, 1 - первое бесконечно, 2 - оба
               // бесконечны, -1 - второе бесконечно
}

void s21_set0bitstype(s21_decimal *value) { s21_set0bits(value); }

void s21_set0bits(s21_decimal *ptr) { memset(ptr->bits, 0, sizeof(ptr->bits)); }

int s21_last_bit(s21_decimal value) {
  int lb = 95;
  for (; lb >= 0 && s21_get_bit(value, lb) == 0; lb--) {
  }
  return lb;  // 0-95 - номер значащего бита, -1 - если все биты пустые
}

void s21_shift_left(s21_decimal *value, int offset) {
  if (s21_last_bit(*value) + offset > 95) {
    s21_set_inf(value);
  } else {
    for (int i = 0; i < offset; i++) {
      int bit_31st = s21_get_bit(*value, 31);
      int bit_63d = s21_get_bit(*value, 63);
      value->bits[0] <<= 1;
      value->bits[1] <<= 1;
      value->bits[2] <<= 1;
      if (bit_31st) s21_set_bit(value, 32, 1);
      if (bit_63d) s21_set_bit(value, 64, 1);
    }
  }
}

s21_decimal check_for_mul(s21_decimal value1, s21_decimal value2) {
  s21_decimal res = {{0, 0, 0, 0}};

  if (s21_check_inf(value1) || s21_check_inf(value2)) {
    s21_set_inf(&res);
    s21_setsign(&res, s21_getsign(&value1) ^ s21_getsign(&value2));
  }

  return res;
}

void to_addcode(s21_decimal *value) {
  s21_decimal res;
  s21_decimal add = {{1, 0, 0, 0}};

  value->bits[0] = ~value->bits[0];
  value->bits[1] = ~value->bits[1];
  value->bits[2] = ~value->bits[2];

  res = s21_add_bits(value, &add);

  value->bits[0] = res.bits[0];
  value->bits[1] = res.bits[1];
  value->bits[2] = res.bits[2];

  s21_set_bit(value, 126, 1);  // ref
}
