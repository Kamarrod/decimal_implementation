#include "../s21_decimal.h"

int s21_add(s21_decimal value1, s21_decimal value2, s21_decimal *res) {
  int ret = 0;
  *res = s21_check_boundary(value1, value2);

  if (!s21_check_inf(*res) || s21_get_bit(*res, 126)) {
    if (!s21_getsign(&value1) && !s21_getsign(&value2)) {  // positive
      if (s21_get_scale(&value1) != s21_get_scale(&value2))
        s21_level_scale(&value1, &value2);

      s21_decimal tmp = s21_add_bits(&value1, &value2);

      if (s21_check_inf(tmp) && s21_get_scale(&value1) == 0) {
        s21_set_inf(res);
      } else if (s21_check_inf(tmp) &&
                 s21_get_scale(&value1) > 0) {  // lower scale
        while (s21_check_inf(*res) &&
               (s21_get_scale(&value1) > 0 &&
                s21_get_scale(&value2) > 0)) {  // divide by 10
          s21_decimal ten = {{10, 0, 0, 0}}, rem1, rem2, zero = {{0, 0, 0, 0}};
          s21_decimal tmp1 = s21_div_bits(value1, ten, &rem1);
          s21_decimal tmp2 = s21_div_bits(value2, ten, &rem2);

          s21_are_zero(tmp1, zero) == 1
              ? s21_copy_bits(tmp1, &value1)  // check for 0
              : s21_copy_bits(rem1, &value1);
          s21_are_zero(tmp2, zero) == 1 ? s21_copy_bits(tmp2, &value2)
                                        : s21_copy_bits(rem2, &value2);

          s21_set_scale(&value1, s21_get_scale(&value1) - 1);
          s21_set_scale(&value2, s21_get_scale(&value2) - 1);
          ret = s21_add(value1, value2, res);
          return ret;
        }

      } else {
        *res = tmp;
        int tmp_add = s21_get_bit(*res, 126);
        res->bits[3] = value1.bits[3];
        s21_set_bit(res, 126, tmp_add);
      }
    } else if (s21_getsign(&value1) &&
               !s21_getsign(&value2)) {  // 1 - negative, 2 - positive
      s21_setsign(&value1, 0);
      s21_sub(value2, value1, res);
    } else if (!s21_getsign(&value1) &&
               s21_getsign(&value2)) {  // 2 - negative, 1 - positive
      s21_setsign(&value2, 0);
      s21_sub(value1, value2, res);
    } else {  // both negative
      s21_setsign(&value1, 0);
      s21_setsign(&value2, 0);
      s21_add(value1, value2, res);
      s21_setsign(res, 1);
      if (s21_check_inf(*res)) {
        s21_set_inf(res);
        s21_setsign(res, 1);
      }
    }
  }

  if (s21_check_inf(*res)) {
    ret = 1;
    if (s21_getsign(&value1) || s21_getsign(&value2)) {
      ret = 2;
      s21_setsign(res, 1);
    }
  }
  return ret;
}