#include "../s21_decimal.h"
/*
Функция банковского округления по остатку от деления big_decimal.
Возвращает округленный big_decimal

Алгоритм:
1) Приводим остаток и 0.5 к одной экспоненте
2) Если остаток == 0.5, то добавляем единицу к результату, если число нечетное,
иначе оставляем, как есть.
3) Если остаток > 0.5, то увеличиваем результат на 1
4) Если остаток < 0.5, то оставляем результат, как есть
*/
s21_big_decimal s21_bank_rounding(s21_big_decimal value,
                                  s21_big_decimal remainder) {
  s21_big_decimal zero_pfive = s21_get_zero_pfive(), result = value;
  s21_setExp_big(&zero_pfive, s21_getExp_big(value) + 1);
  int equal = s21_Big_comparison(zero_pfive, remainder);
  if (equal == 0) {
    if (s21_is_even(value) == 1) {
      result = s21_Big_add_binary(result, s21_get_one());
      s21_setExp_big(&result, s21_getExp_big(value));
    }
  } else if (equal == 2) {
    result = s21_Big_add_binary(value, s21_get_one());
    s21_setExp_big(&result, s21_getExp_big(value));
  } else {
  }
  result.bits[7] = value.bits[7];
  return result;
}