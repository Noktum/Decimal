#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int flag_error = 0;
  if ((dst == NULL) || !s21_is_decimal_correct(src)) {
    flag_error = 1;
  } else {
    *dst = 0;
    int minus = 1;
    long double result = 0, two = 1;
    int exp = s21_getExp(src);
    if (s21_getSign(src) == 1) minus = -1;
    for (int k = 0; k < 96; k++) {
      if (s21_getBit(src, k)) {
        result += two;
      }
      two *= 2;
    }
    for (int k = 0; k < exp; k++) {
      result /= 10;
    }
    *dst = minus * result;
  }
  return flag_error;
}