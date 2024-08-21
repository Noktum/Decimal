#include "../s21_decimal.h"
/*
 Функция, переводящая decimal в big_decimal. Просто переприсваиваются
 последние биты decimal в big_decimal.
*/
void s21_dec_to_bigdec(s21_decimal value, s21_big_decimal *bvalue) {
  bvalue->bits[7] = value.bits[3];
  for (int i = 0; i < 3; ++i) {
    bvalue->bits[i] = value.bits[i];
  }
}
/*
 Функция, переводящая big_decimal в decimal.
 Проверка экспоненты на значение > 28
 Если она > 28, делим на 10 без остатка, отсекая цифры
 (Пример: 123 * 10^-29 ----> 12 * 10^-28)
 Функция возвращает 0, если смогла перевести и все ок
                    1, если число слишком большое (> max)
                    2, если число слишком маленькое (< -max)

Алгоритм:
1) Проверка: число > макс. decimal? (только бинарно).
2) Если экспонента > 28, то отсекаем, деля на 10 и не оставляя остатка.
3) Если изначальное big_decimal < макс. decimal, то он
вмещается => переходим к присваиванию значений.
4) Если big_decimal > макс. decimal, проверка экспоненты: 0 - переполнение.
5) Если exp != 0, то получаем число, сколько раз надо поделить big_decimal на
10, чтобы оно стало < max_decimal. 6) Если оно > экспоненты, то big_decimal >
max_decimal - переполнение. 7) Если же нам удастся поделить: делим, записываем
остаток в remainder и делаем с ним банковское округление. 8) Результирующий
big_decimal рекурсивно запускаем эту же функцию, т.к. из-за округления может
быть переполнение
*/
int s21_bigdec_to_dec(s21_big_decimal bvalue, s21_decimal *value) {
  int comparison, code = 0, exp = s21_getExp_big(bvalue),
                  sign = s21_getSign_big(bvalue);
  s21_big_decimal remainder = s21_get_zero_big(), bvalue_copy = bvalue;
  for (int i = exp; i > 28; --i) {
    exp--;
    bvalue = s21_Big_div_binary(bvalue, s21_get_10_big(), &remainder);
    if (i == 29) {
      s21_setExp_big(&remainder, 29);
    }
    if (s21_is_zero_big(bvalue) == 0 && s21_is_zero_big(bvalue_copy) == 1) {
      code = 2;
    }
  }
  comparison = s21_Big_comparison_binary(bvalue, s21_get_max_decimal_big());
  s21_setExp_big(&bvalue, exp);
  if (comparison != 1) {
    bvalue = s21_bank_rounding(bvalue, remainder);
    if (value != NULL) {
      value->bits[3] = bvalue.bits[7];
      for (int i = 0; i < 3; ++i) {
        value->bits[i] = bvalue.bits[i];
      }
      s21_setSign(value, sign);
    }
  } else {
    if ((exp == 0) && (sign == 1)) {
      *value = s21_get_zero();
      code = 2;
    } else if ((exp == 0) && (sign == 0)) {
      *value = s21_get_zero();
      code = 1;
    } else {
      int exp_needed = s21_bigdec_to_dec_shift(bvalue);
      if (exp_needed > exp) {
        code = 1 + sign;
      } else {
        bvalue = s21_Big_div_binary(bvalue, s21_get_pow10_big(exp_needed),
                                    &remainder);
        s21_setExp_big(&remainder, exp);
        s21_setExp_big(&bvalue, exp - exp_needed);
        bvalue = s21_bank_rounding(bvalue, remainder);
        code = s21_bigdec_to_dec(bvalue, value);
      }
    }
  }
  return code;
}

// Функция, позволяющая определить, сколько раз нам нужно поделить
//  big_decimal на 10, чтобы он стал меньше, чем максимальный decimal
int s21_bigdec_to_dec_shift(s21_big_decimal value) {
  int exp_needed = 0;
  while (s21_Big_comparison_binary(value, s21_get_max_decimal_big()) == 1) {
    value = s21_Big_div_binary(value, s21_get_10_big(), NULL);
    exp_needed++;
  }
  return exp_needed;
}
