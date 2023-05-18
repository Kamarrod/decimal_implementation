#include "../s21_decimal.h"

int s21_sub(s21_decimal number_1, s21_decimal number_2, s21_decimal *res) {
  int ret = 0;
  s21_set0bits(res);
  if (s21_check_inf(number_1) || s21_check_inf(number_1)) s21_set_inf(res);

  if (!s21_check_inf(*res)) {
    if (s21_get_scale(&number_1) != s21_get_scale(&number_2))
      s21_level_scale(&number_1, &number_2);

    int sign;
    if (s21_getsign(&number_1) !=
        s21_getsign(&number_2)) {  // signs don't equal
      sign = s21_getsign(&number_1);
      s21_setsign(&number_1, 0);
      s21_setsign(&number_2, 0);
      s21_add(number_1, number_2, res);
      s21_setsign(res, sign);
    } else {                                    // signs equal
      if (!s21_is_equal(number_1, number_2)) {  // digits don't equals
        int sign1 = s21_getsign(&number_1);
        int sign2 = s21_getsign(&number_2);
        s21_setsign(&number_1, 0);
        s21_setsign(&number_2, 0);
        s21_decimal *smallPtr, *bigPtr;

        if (s21_is_less(number_1, number_2)) {
          smallPtr = &number_1;
          bigPtr = &number_2;
          sign = !sign2;
        } else {
          smallPtr = &number_2;
          bigPtr = &number_1;
          sign = sign1;
        }

        to_addcode(smallPtr);
        s21_add(*smallPtr, *bigPtr, res);
        s21_setsign(res, sign);
      }
    }
  }
  if (s21_check_inf(*res)) {
    ret = 1;
    if (s21_getsign(&number_1) || s21_getsign(&number_2)) {
      ret = 2;
      s21_setsign(res, 1);
    }
  }
  return ret;
}
