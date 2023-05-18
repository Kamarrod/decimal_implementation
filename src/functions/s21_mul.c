#include "../s21_decimal.h"

int s21_mul(s21_decimal number_1, s21_decimal number_2, s21_decimal *res) {
  int ret = 0;
  *res = check_for_mul(number_1, number_2);

  // if (res->value_type == s21_usual) {
  if (s21_check_inf(*res) == 0) {
    int sign_result;

    if (s21_getsign(&number_1) != s21_getsign(&number_2)) {
      sign_result = 1;
    } else {
      sign_result = 0;
    }
    int last_bit_1 = s21_last_bit(number_1);
    s21_decimal tmp_res = {{0, 0, 0, 0}};

    // само умножение
    for (int i = 0; i <= last_bit_1; i++) {
      s21_set0bitstype(&tmp_res);
      int value_bit_1 = s21_get_bit(number_1, i);

      if (value_bit_1) {
        tmp_res = number_2;
        s21_shift_left(&tmp_res, i);
        *res = s21_add_bits(res, &tmp_res);
      }
    }

    // если на предыдущем этапе было выставлено INFINITY,
    // то если позволяет скейл, привести в нужный диапазон
    // и попробовать умножить снова

    // while (res->value_type != s21_usual &&
    while (s21_check_inf(*res) &&
           (s21_get_scale(&number_1) > 0 || s21_get_scale(&number_2) > 0)) {
      // более точное число поделим на 10, если позволяет скейл

      s21_decimal *chosen_numberPtr, *other_numberPtr;
      if (s21_last_bit(number_1) > s21_last_bit(number_2) &&
          s21_get_scale(&number_1) > 0) {
        chosen_numberPtr = &number_1;
        other_numberPtr = &number_2;
      } else if (s21_last_bit(number_2) > s21_last_bit(number_1) &&
                 s21_get_scale(&number_2) > 0) {
        chosen_numberPtr = &number_2;
        other_numberPtr = &number_1;
      } else {
        break;
      }

      int chos_number_scale = s21_get_scale(chosen_numberPtr);
      s21_decimal ten = {{10, 0, 0, 0}};
      s21_decimal remainder;
      s21_decimal tmpDiv = s21_div_bits(*chosen_numberPtr, ten, &remainder);

      // обезопасимся от обнуления
      s21_decimal zero = {{0, 0, 0, 0}};
      if (s21_are_zero(tmpDiv, zero) == 1) {
        s21_copy_bits(tmpDiv, chosen_numberPtr);
      } else {
        s21_copy_bits(remainder, chosen_numberPtr);
      }

      s21_set_scale(chosen_numberPtr, --chos_number_scale);
      s21_mul(*chosen_numberPtr, *other_numberPtr, res);
      return ret;
    }
    int scale = s21_get_scale(&number_1) + s21_get_scale(&number_2);
    s21_set_scale(res, scale);

    s21_setsign(res, sign_result);
  }

  //   if (res->value_type != s21_usual) s21_set0bits(res);
  // if (s21_check_inf(*res)) s21_set0bits(res);
  //   if (res->value_type == s21_neg_infinity) ret = 2;
  //   if (res->value_type == s21_infinity) ret = 1;

  if (s21_check_inf(*res)) {
    ret = 1;
    if (s21_getsign(res)) ret = 2;
  }
  return ret;
}
