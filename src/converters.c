#include "s21_decimal.h"
// #include "string.h"
int getBit(s21_decimal d, int i) {
  // i % 32 от переполнения, тк сдвиг больше чем на 32 сделать не можем
  unsigned int mask = 1u << (i % 32);
  // получили маску с 1 на i позиции и 0 на остальных
  // i/32 всегда целое - должно быть от 0 до 3
  //попадаем в LOW/MID/HIGH и зануляем все кроме i позиции
  //если 0, то вернем 0
  //если 1, то вернем число > 0 или инт мин
  return !!(d.bits[i / 32] & mask);
}

void setBit(s21_decimal *d, int i) {
  // i % 32 от переполнения, тк сдвиг больше чем на 32 сделать не можем
  unsigned int mask = 1u << (i % 32);
  // получили маску с 1 на i позиции и 0 на остальных

  // printf("SETBIt DO %X\n", d->bits[i/32]);
  d->bits[i / 32] |= mask;
  // printf("SETBIT POSLE %X\n", d->bits[i/32]);
}

void setScale(s21_decimal *d, int scale) {
  //есть десятичное число scale 0 до 28 11100
  //его нужно записать в bits[3] с 16 по 23
  unsigned int fbits = *((unsigned int *)&scale);
  int shift = 31 + 32 + 32;
  int i = 17 + shift;
  unsigned int mask = 1u;
  for (; i <= 24 + shift; i++) {
    if (!!(fbits & mask)) {
      setBit(d, i);
    }
    mask <<= 1;
  }
}

int getScale(s21_decimal d) {
  int scale = 0;
  int j = 7;
  for (int i = 119; i >= 112; i--) {
    if (getBit(d, i))
      scale += pow(2, j);
    j--;
  }
  return scale;
}


int getBinExpD(double f) {
  int i = 11, res = -1023;
  unsigned long long fbits = *((unsigned long long *)&f);
  unsigned long long mask = 1ull << 62;
  // printf("*");
  for (; i > 0; mask >>= 1) {
    i--;
    res += !!(fbits & mask) * pow(2, i);
    // printf("%d", !!(fbits&mask));
  }
  // printf("\n");
  return res;
}

void _double_to_dec(double dinp, s21_decimal *dst) {
  int binexp = getBinExpD(dinp);
  int i = binexp - 1;
  setBit(dst, binexp);
  unsigned long long mask = 1ull << 51;
  unsigned long long fbits = *((unsigned long long *)&dinp);
  for (; mask; mask >>= 1) {
    if (!!(fbits & mask)) {
      setBit(dst, i);
    }
    i--;
  }
}

int get_scale_n_right_form(int *scale, double dinp, double *rf,
                           s21_decimal *dst) {
  double inp = dinp;
  int p = 0; //кол-во цифр перед точкой
  while (inp / 10. > 1e-1) {
    inp /= 10.;
    p++;
  }
  double shift = p - 7; //перед точкой сколько осталось до 7
  if (shift > 0) { //часть до точки длиннее 7,обрезаем
    for (int i = 0; i < shift; i++)
      dinp /= 10;
    dinp = round(dinp);        //округляем обрезанное
    _double_to_dec(dinp, dst); //переписать обрезанное в дец
    int tshift = shift;
    _mult_10_dec(dst, &tshift); //*10 децимал - нет потери точности
  } else {        //значит часть до точки короче 7
    int i, j = 0; // j (подсчет общего сдвига),
    int limit_mult10 = 7; //зацепляем 28 символов после точки
    for (; !(int)dinp && j < 28; dinp *= 10, j++) {
      *(scale) += 1;
    }
    if (*scale > 0) { // число по длине меньше 1, сдвигали до головы
      int can_shift = 28;
      can_shift -= j;
      i = 1;
      if (can_shift < 7 && can_shift >= 0) {
        limit_mult10 = can_shift + 1;
      } else if (can_shift < 0) {
        limit_mult10 = 0;
      }
    } else { //если перед точкой уже есть до 6 цифр
      i = p;
    } // дальше в цикле будем крутиться меньше
    //умножение на 10 до правильного вида
    while (i < limit_mult10) {
      dinp *= 10;
      i++;
      *(scale) += 1;
    }
    dinp = round(dinp); //могут на конце появиться 0
    while ((int)dinp % 10 == 0 && (int)dinp) {
      dinp /= 10;
      *scale -= 1;
    }
    if (*scale < 0) {   //если число c 0 на конце сразу
      *scale = -*scale; //цикл выше их уничтожит
      while (*scale) {
        dinp *= 10;
        *scale = *scale - 1;
      }
    }
  }
  *rf = dinp;
  return shift;
}


int getSign(s21_decimal src) { return getBit(src, 127); }


int getFirstNotZeroIndex(s21_decimal src) {
  int i = 95;
  int found = 0;
  while (i >= 0 && !found) {
    if (getBit(src, i))
      found = 1;
    i--;
  }
  return i;
}



//применяется для сложения без учета scale
int add_dec_no_scale(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  int ret_val = 0; // 0 ok 1 overflow
  int temp = 0;    // для того чтобы перненосить 1
  for (int i = 0; i < 4; i++)
    result->bits[i] = 0;
  for (int i = 0; i <= 95; i++) {
    int top = getBit(value_1, i);
    int bot = getBit(value_2, i);
    if (top && bot) {
      if (temp)
        setBit(result, i);
      else
        temp = 1;
    } else if (top || bot) {
      if (!temp)
        setBit(result, i);
    } else if (temp) {
    // } else if (!top && !bot && temp) {
      setBit(result, i);
      temp = 0;
    }
  }
  if (temp)
    ret_val = 1;
  return ret_val;
}

//функция не меняет scale
int shift_left_dec(s21_decimal d, s21_decimal *r, int IndexShift) {
  int rv = 0; // 0 ok 1 of
  if (r) {
    for (int i = 0; i < 4; i++)
      r->bits[i] = 0;
    int fnz = getFirstNotZeroIndex(d);
    if (fnz + IndexShift <= 95) {
      for (int i = 0; i <= fnz + 1; i++) {
        if (getBit(d, i))
          setBit(r, i + IndexShift);
      }
    } else {
      rv = 1;
    }
  }
  return rv;
}

void _cpy_dec(s21_decimal d, s21_decimal *r) {
  if(r) {
    for(int i = 0; i < 4; i++)
      r->bits[i]= d.bits[i];
  }
}

int _mult_10_dec(s21_decimal *d, int* shift10) {
  int rv = 0;
  //нужно сделать так, чтобы результат до ошибки оставался
  //запоминать сделанный shift
  s21_decimal tmp;
  while (*shift10 && !rv) {
    _cpy_dec(*d, &tmp);
    s21_decimal slv3; //на 3
    int err = shift_left_dec(tmp, &slv3, 3);
    if (!err) {
      s21_decimal slv1; //сдвинутое на 1
      shift_left_dec(tmp, &slv1, 1);
      add_dec_no_scale(slv1, slv3, d);
      *shift10=*shift10-1;
    } else {
      rv = 1;
    }
  }
  return rv; // 0 ok/// 1 значит мы не можем сдвинуть нужное кол-во раз
}


int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int rv = 0;
  if (dst && !(src == s21_INFINITY || src == -s21_INFINITY || src != src)) {
    // for (int i = 0; i < 4; i++)
    //   dst->bits[i] = 0;
    memset(dst, 0, sizeof(s21_decimal));
    int scale = 0;
    if(src!=0) {
        int neg = 0;
        double rf = src;
        if (rf < 0) {
          neg = 1;
          rf = -rf;
        }
        if(rf>= 1E-28 && rf < 79228162514264337593543950335.0f) {
          int binexp = getBinExpD(rf);
          if (binexp <= 95) {
            int shift = get_scale_n_right_form(&scale, rf, &rf, dst);
            setScale(dst, scale);
            if (shift <= 0)
              _double_to_dec(rf, dst);
            if (neg)
              setBit(dst, 127);
          } else {
            rv = 1;
          }
        } else {
          rv = 1;
        }
    }

  } else {
    rv = 1;
  }
  return rv;
}


int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int ret_val = 1;
  if (dst) {
    if (getFirstNotZeroIndex(src) > 31) {
      ret_val = 1;
    } else {
      double dsrc = 0;
      for (int i = 0; i < 96; i++) {
        if (getBit(src, i)) {
          dsrc += pow(2, i);
        }
      }
      int scale = getScale(src);
      while (scale && dsrc) {
        dsrc /= 10;
        scale--;
      }
      *dst = trunc(dsrc);

      if (getSign(src)) {
        *dst = -*dst;
      }
      ret_val = 0;
    }
  }
  return ret_val;
}


int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int ret_val = 1;
  if (dst) {
    *dst = 0;
    long double ldst = 0;
    for (int i = 0; i < 96; i++) {
      if (getBit(src, i)) {
        ldst += pow(2, i); //во флот прибавляем 2 в степени i
      }
    }
    //пока scale не 0 делим на 10
    int scale = getScale(src);
    while (scale) {
      ldst /= 10;
      scale--;
    }
    if (getSign(src))
      ldst = -ldst;
    *dst = ldst;
    ret_val = 0;
  }
  return ret_val;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int ret_val = 1;
  if (dst) {
    // for (int i = 0; i < 4; i++)
    //   dst->bits[i] = 0;
    memset(dst, 0, sizeof(s21_decimal)); 
    int neg = 0;
    if (src < 0) {
      neg = 1;
      src = -src;
    }
    dst->bits[0] = src;
    if (neg)
      setBit(dst, 127);
    ret_val = 0;

  }
  return ret_val;
}

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
  // res->value_type = number_1.value_type ? number_1.value_type :
  // number_2.value_type;
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
  //   if (res->value_type == s21_infinity) ret = 1;
  //   if (res->value_type == s21_neg_infinity) ret = 2;
  if (s21_check_inf(*res)) {
    ret = 1;
    // if (s21_getsign(res)) ret = 2;
    if (s21_getsign(&number_1) || s21_getsign(&number_2)) {
      ret = 2;
      s21_setsign(res, 1);
    }
  }
  return ret;
}
