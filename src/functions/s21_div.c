#include "../s21_decimal.h"

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
