#include "../s21_decimal.h"

// Returns decimal * (-1)
int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 0;  // OK

  if (!result || s21_getExp(value) > 29) {
    flag = 1;
  }

  if (s21_getSign(value) == 0 && flag == 0) {
    *result = value;
    s21_setSign(result, 1);
  } else if (s21_getSign(value) == 1 && flag == 0) {
    *result = value;
    s21_setSign(result, 0);
  }
  return flag;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;

  if (!result || s21_getExp(value) > 29) {
    flag = 1;
  } else {
    s21_big_decimal big = s21_get_zero_big(), rem = s21_get_zero_big();
    s21_dec_to_bigdec(value, &big);
    int scale = s21_getExp_big(big);
    big = s21_Big_div_binary(big, s21_get_pow10_big(scale), &rem);
    s21_setExp_big(&big, 0);
    s21_bigdec_to_dec(big, result);
  }

  return flag;
}