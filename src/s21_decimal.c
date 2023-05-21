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

void dec_to_bin(s21_decimal d) {
  printf(" SCALE: ");
  int sci = 32;
  for (unsigned int mask = 1u << 31; mask; mask >>= 1) {
    if (sci % 4 == 0)
      printf(" ");
    printf("%d", !!(d.bits[3] & mask));
    sci--;
  }
  printf(" HIGH: ");
  for (unsigned int mask = 1u << 31; mask; mask >>= 1)
    printf("%d", !!(d.bits[2] & mask));
  printf(" MID: ");
  for (unsigned int mask = 1u << 31; mask; mask >>= 1)
    printf("%d", !!(d.bits[1] & mask));
  printf(" LOW: ");
  for (unsigned int mask = 1u << 31; mask; mask >>= 1)
    printf("%d", !!(d.bits[0] & mask));
  printf("\n");

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


int getBinExpF(float f) {
  //число представляет в битах f
  unsigned int fbits =
      *((unsigned int *)&f); //получаем f так как он хранится в памяти
  //нужно проверить биты с 1 по 8
  int i = 7, res = -127;
  for (unsigned int mask = 0x40000000; mask >= 0x800000;
       mask >>= 1) { //маску делим на 2
    res += !!(fbits & mask) * pow(2, i);
    i--;
  }
  return res;
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
    int can_shift = 28, limit_mult10 = 7; //зацепляем 28 символов после точки
    for (; !(int)dinp && j < 28; dinp *= 10, j++) {
      *(scale) += 1;
    }
    if (*scale > 0) { // число по длине меньше 1, сдвигали до головы
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



int getBinExpLD(long double x) {
  int res = -16383;
  union {
    long double x;
    char c[sizeof(long double)];
  } u;
  u.x = x;
  printf(" ");
  int j = 14;
  for (int i = 6; i >= 0; i--) {
    printf("%d", !!((1 << i) & u.c[9]));
    res += !!((1 << i) & u.c[9]) * pow(2, j);
    j--;
  }
  printf(" ");
  for (int i = 7; i >= 0; i--) {
    printf("%d", !!((1 << i) & u.c[8]));
    res += !!((1 << i) & u.c[8]) * pow(2, j);
    j--;
  }
  return res;
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
    } else if (!top && !bot && temp) {
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

void clearBit(s21_decimal *d, int i) {
  unsigned int mask = 1u << (i % 32);
  mask = ~mask;
  d->bits[i / 32] &= mask;
}


int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int rv = 0;
  if (dst && !(src == s21_INFINITY || src == -s21_INFINITY || src != src)) {
    // for (int i = 0; i < 4; i++)
    //   dst->bits[i] = 0;
    memset(dst, 0, sizeof(s21_decimal));
    int neg = 0, scale = 0;
    if(src!=0) {
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

// int main() {
//   s21_decimal src1;
//   float dst;
//   src1.bits[0] = -805306368;
//   src1.bits[1] = -128223179;
//   src1.bits[2] = 429496715;
//   src1.bits[3] = 0;
//   int code = s21_from_decimal_to_float(src1, &dst);
//   char var3str[1000];
//   char result[1000];
//   snprintf(var3str, 8, "%f", 7922816200000000000000000000.0f);
//   snprintf(result, 8, "%f", dst);
//   printf("RES %f\n", roundf(dst));
//   printf("CODE %d \n", code);
//   printf("STR ORIG %s\n STR RES %s\n", var3str, dst);
//   return 0;
// }