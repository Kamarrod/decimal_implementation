#include "s21_decimal.h"

int s21_div(s21_decimal divident, s21_decimal divisor, s21_decimal *result) {
  int ret = 0;
  s21_set0bitstype(result);

  s21_decimal zero = {{0, 0, 0, 0}};
  int divsr_is_normal_plus =
      s21_is_greater(divisor, zero) == 1 && !s21_check_inf(divisor) ? 1 : 0;

  int divsr_is_normal_minus =
      s21_is_less(divisor, zero) == 1 && !s21_check_inf(divisor) ? 1 : 0;

  int flag = 1;  // для отлова ситуации с normal/+-inf

  if (s21_is_equal(divisor, zero) == 1 && s21_is_less(divident, zero) == 1) {
    s21_set_inf(result);
    s21_setsign(result, 1);
  } else if (s21_is_equal(divisor, zero) == 1 &&
             s21_is_greater(divident, zero) == 1) {
    s21_set_inf(result);
  } else if (s21_is_equal(divisor, zero) == 1 &&
             s21_is_equal(divident, zero) == 1) {
  } else if ((s21_check_inf(divident) && divsr_is_normal_plus) ||
             (s21_check_inf(divident) && s21_getsign(&divident) &&
              divsr_is_normal_minus)) {
    s21_set_inf(result);
  } else if ((s21_check_inf(divident) && divsr_is_normal_minus) ||
             (s21_check_inf(divident) && s21_getsign(&divident) &&
              divsr_is_normal_plus)) {
    s21_set_inf(result);
    s21_setsign(result, 1);
  } else if (s21_check_inf(divisor)) {
    *result = zero;
    flag = 0;
  }

  if (!s21_check_inf(*result) && flag) {
    int beginScale = s21_get_scale(&divident) - s21_get_scale(&divisor);
    int resultSign = s21_getsign(&divident) != s21_getsign(&divisor);

    s21_decimal remainder, tmp;

    // для предсказуемости зачищаем
    s21_set_scale(&divisor, 0);
    s21_set_scale(&divident, 0);
    s21_setsign(&divisor, 0);
    s21_setsign(&divident, 0);

    // первое целочисленное деление
    tmp = s21_div_bits(divident, divisor, &remainder);
    s21_copy_bits(tmp, result);

    // 1/10 от макс значения децимал - граница от переполнения
    s21_decimal border_value = {{-1, -1, -1, 0}};
    s21_decimal ten = {{10, 0, 0, 0}};

    s21_set_scale(&border_value, 1);
    int inside_scale = 0;

    // делим, пока не достигнем максимальной точности или пока не поделим
    // без остатка

    for (; inside_scale <= 27 && s21_is_equal(remainder, zero) == 0;) {
      if (s21_is_less(*result, border_value) == 0) {
        break;
      }
      s21_mul(remainder, ten, &remainder);
      tmp = s21_div_bits(remainder, divisor, &remainder);
      s21_mul(*result, ten, result);
      s21_add(*result, tmp, result);
      inside_scale++;
    }

    s21_decimal musor;
    // вводим итоговый скейл в требуемые границы
    int endScale = beginScale + inside_scale;
    for (; endScale > 28;) {
      *result = s21_div_bits(*result, ten, &musor);
      endScale--;
    }
    for (; endScale < 0;) {
      s21_mul(*result, ten, result);
      endScale++;
    }

    s21_set_scale(result, endScale);
    s21_setsign(result, resultSign);
  }


  if (s21_check_inf(*result)) {
    ret = 1;
    if (s21_getsign(&divident) != s21_getsign(&divisor)) ret = 2;
  }
  if (s21_is_equal(divisor, zero)) ret = 3;
  return ret;
}

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

  if (s21_check_inf(*res)) {
    ret = 1;
    if (s21_getsign(res)) ret = 2;
  }
  return ret;
}

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

