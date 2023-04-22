#include "s21_decimal.h"

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

void float_to_binary(float f) {
  printf("\n");
  unsigned int fbits = *((unsigned int *)&f);
  for (unsigned int mask = 0x80000000; mask; mask >>= 1) //маску делим на 2
    printf("%d", !!(fbits & mask));
  printf("\n");
}

void double_to_binary(double f) {
  printf("\n");
  unsigned long long fbits = *((unsigned long long *)&f);
  unsigned long long mask = 1ull << 63;
  for (; mask; mask >>= 1) //маску делим на 2
    printf("%d", !!(fbits & mask));
  printf("\n");
}

float binary_to_float(unsigned int fbits) { // только положительные числа
  float res = 0;
  int i = 7, exp = -127;
  //встали маской на 1 бит цикл крутится 8 раз
  for (unsigned int mask = 0x40000000; mask >= 0x800000;
       mask >>= 1) { //маску делим на 2
    exp += !!(fbits & mask) * pow(2, i);
    i--;
  }
  //встали маской на 9 бит после exp
  //цикл крутится 23 раза
  res += pow(2, exp);
  for (unsigned int mask = 0x400000; mask; mask >>= 1) {
    exp--;
    res += !!(fbits & mask) * pow(2, exp);
  }
  return res;
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

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int rv = 0;
  if (dst && !(src == s21_INFINITY || src == -s21_INFINITY || src != src)) {
    for (int i = 0; i < 4; i++)
      dst->bits[i] = 0;
    int neg = 0, scale = 0;
    double rf = src;
    if (rf < 0) {
      neg = 1;
      rf = -rf;
    }
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
  return rv;
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

void printLD(long double x) {
  union {
    long double x;
    char c[sizeof(long double)];
  } u;
  u.x = x;

  for (int ofs = 9; ofs >= 0; ofs--) {
    for (int i = 7; i >= 0; i--) {
      printf(((1 << i) & u.c[ofs]) ? "1" : "0");
    }
    printf(" ");
  }
}

long double ld_to_ld(long double x) {
  long double res = 0;
  union {
    long double x;
    char c[sizeof(long double)];
  } u;
  u.x = x;

  int j = getBinExpLD(x);
  for (int ofs = 7; ofs >= 0; ofs--) {
    for (int i = 7; i >= 0; i--) {
      res += !!((1 << i) & u.c[ofs]) * pow(2, j);
      j--;
    }
  }
  return res;
}

int getSign(s21_decimal src) { return getBit(src, 127); }

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
    // printf("AFTER FOR: %.38f\n", *dst);
    //пока scale не 0 делим на 10
    int scale = getScale(src);
    while (scale) {
      ldst /= 10;
      scale--;
    }
    // printf("AFTER DIV: %.38f\n", *dst);

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
    for (int i = 0; i < 4; i++)
      dst->bits[i] = 0;
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

void dec_to_dop_code(s21_decimal *d) {
  d->bits[0] = ~d->bits[0] + 1;
  d->bits[1] = ~d->bits[1];
  d->bits[2] = ~d->bits[2];
}

void dec_to_norm_code(s21_decimal *d) {
  d->bits[0] -= 1;
  d->bits[0] = ~d->bits[0];
  d->bits[1] = ~d->bits[1];
  d->bits[2] = ~d->bits[2];
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int rv = 1;
  if (result) {
    if (getSign(value))
      clearBit(result, 127);
    else
      setBit(result, 127);
    rv = 0;
  }
  return rv;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int rv = 1;
  if (result) {
    s21_negate(value_2, &value_2);
    rv = s21_add(value_1, value_2, result);
  }
  return rv;
}

int _to_same_scale_dec(s21_decimal *value_1, s21_decimal *value_2, int* res_scale) {
  int rv = 0; // 0 ok 1 нельзя привести
  // приводим к большему, чтобы не потерять точность
  // scale нельзя вечно увеличивать, тк вместе с ним увеличивается и число
  //тогда нужно начать уменьшать scale
  int s1 = getScale(*value_1);
  int s2 = getScale(*value_2);
  if(s1>0 || s2>0) {
    if (s1 > s2) {
      int shift = s1 - s2;
      int err = _mult_10_dec(value_2, &shift);
      *res_scale = s1;
      if (err) { //уменьшаем scale
        //значит надо делить на 10 число с большим scale
        //поделить его нужно столько раз, сколько осталось сдвигов
        //scale = s1 - shift;
        printf("NADO UMENSHAT 1\n");
        //если и уменьшив не сможем сложить без переполнения
      }
    } else if (s2 > s1) {
      int shift = s2 - s1;
      int err = _mult_10_dec(value_1, &shift);
      *res_scale = s2;
      if (err) { //уменьшаем scale
        //значит надо делить на 10 число с большим scale
        printf("NADO UMENSHAT 2\n");
      }
    } else {
      *res_scale = s1;
    }
  }
  return rv;
}

int _is_less_dec_no_sign(s21_decimal value_1, s21_decimal value_2) {
  //нужно привести к 1 scale
  int res_scale, rv;
  //берем 1е ненулевые индексы
  if(getScale(value_1)!=getScale(value_2))
    _to_same_scale_dec(&value_1, &value_2, &res_scale);
  // printf("SAME SCALE\n");
  // dec_to_bin(value_1);
  // dec_to_bin(value_2);
  int fnzi1 = getFirstNotZeroIndex(value_1);
  int fnzi2 = getFirstNotZeroIndex(value_2);
  if(fnzi1 > fnzi2)
    rv = 0;
  else if(fnzi1 < fnzi2) {
    rv = 1;
  } else {
    int found = 0, i = fnzi1;
    while (i >= 0 && !found) {
      if (getBit(value_1, i) != getBit(value_2, i)){
        found = 1;
        if(getBit(value_1, i))//если тут у 1 стоит 1 значит он больше по модулю
          rv = 0;
        else
          rv = 1;
      }
      i--;
    }
    if(!found)//если не нашли различий - числа одинаковы
      rv = 2;
  }
  //если fnzi неравны - результат
  //fnzi равны - идем по числам до тех пор пока не натолкнемся на различие
  //rv 2 если числа равны
  return rv;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
    int rv;
    int sign1 = getSign(value_1);
    int sign2 = getSign(value_2);
    if(!sign1&&sign2)//+-
      rv = 0;
    else if(sign1 && !sign2)//-+
      rv = 1;
    else if(sign1 && sign2) {//-- 0 если в1 меньше по модулю
      int res = _is_less_dec_no_sign(value_1, value_2);
      if(res)//тут и в1 меньше по модулю + равенство res==2
        rv = 0;
      else if(!res) 
        rv = 1;
    } else if(!sign1 && !sign2) {//++ 1 (v1 меньше по модулю)
      int res = _is_less_dec_no_sign(value_1, value_2);
      if(res==1)
        rv = 1;
      else if(res==2 || res==0)
        rv = 0;
    }
    return rv;
}

// 0 - OK
// 1 - число слишком велико или равно бесконечности
// 2 - число слишком мало или равно отрицательной бесконечности
// 3 - деление на 0
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int rv = 0;
  if (result) {
    for (int i = 0; i < 4; i++)
      result->bits[i] = 0;
    //
    // нужно предусмотреть что оба числа положительны или отрицательны иначе
    // сюда запихнуть вычитание
    //
    int neg = 0, res_from_dop = 0;
    int sign1 = getSign(value_1);
    int sign2 = getSign(value_2);
    // нужно привести к 1 scale
    int res_scale = 0;
    _to_same_scale_dec(&value_1, &value_2, &res_scale);

    if (sign1 && sign2) {
      neg = 1;
    } else if ((sign1 && !sign2)) {
      //если число с минусом по модулю больше - результат придется конвертить из
      //доп кода
      //проверки по fnzi недостаточно - scale все портит
      clearBit(&value_1, 127);
      if (s21_is_less(value_2, value_1))
        res_from_dop = 1;
      setBit(&value_1, 127);

      //число у которого знак переводим в доп код и уже его складываем
      dec_to_dop_code(&value_1);
      printf("IN FUNCT DOP 1 \n");
      dec_to_bin(value_1);

    } else if ((!sign1 && sign2)) {
      clearBit(&value_2, 127);
      if (s21_is_less(value_1, value_2))
        res_from_dop = 1;
      setBit(&value_2, 127);
      
      dec_to_dop_code(&value_2);
      printf("IN FUNCT DOP 2 \n");
      dec_to_bin(value_2);
    }

    // dec_to_bin(value_1);
    // dec_to_bin(value_2);
    //внутри функ не нужно обнулять тк выше рез уже обнулялся
    //
    //учесть что при подачи в доп коде может быть переполнение  и rv станет 1
    //
    rv = add_dec_no_scale(value_1, value_2, result);
    //выше если переполнение вернется 1
    if (rv && (neg || res_from_dop))
      rv = 2; //тут говорим что оч маленькое число

    if (res_from_dop)
      dec_to_norm_code(result);
    if (res_scale)
      setScale(result, res_scale);
    if (neg || res_from_dop)
      setBit(result, 127);
    // printf("IN FUNC CHECK\n");
    // dec_to_bin(value_1);
    // dec_to_bin(value_2);
  }
  // printf("RESULT:\n");
  // dec_to_bin(*result);
  return rv;
}


// ADD
// int main() {
//   float float_a = -10758.218750;
//   float float_b = 6268.843750;

//   float float_res = float_a + float_b;

//   // s21_decimal expected = {0};
//   // s21_from_float_to_decimal(float_res, &expected);

//   s21_decimal dec_a = {0};
//   s21_from_float_to_decimal(float_a, &dec_a);
//   s21_decimal dec_b = {0};
//   s21_from_float_to_decimal(float_b, &dec_b);
//   dec_to_bin(dec_a);
//   dec_to_bin(dec_b);

//   s21_decimal result = {0};
//   int code = s21_add(dec_a, dec_b, &result);
//   printf("CODE %d\n", code);
//   dec_to_bin(result);

//   float got_float = 0;
//   s21_from_decimal_to_float(result, &got_float);
//   printf("RES      %.5f\n", got_float);
//   printf("RES ORIG %.5f\n", float_res);
//   //4489376
//   return 0;
// }


//ISLESS
//  int main () {

//   int num1 = -3;
//   int num2 = -3;
//   s21_decimal dec1, dec2;
//   s21_from_int_to_decimal(num1, &dec1);
//   s21_from_int_to_decimal(num2, &dec2);


//   dec_to_bin(dec1);
//   dec_to_bin(dec2);
//   int res = s21_is_less(dec1, dec2);
//   printf("RES %d\n", res);
//    return 0;
//  }