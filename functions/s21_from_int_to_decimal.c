#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag_error = 0;
  if ((dst == NULL) || abs(src) > MAX_DECIMAL) {
    flag_error = 1;
  } else {
    *dst = (s21_decimal){{0}};
    dst->bits[0] = (src >= 0) ? src : -src;
    s21_setSign(dst, src < 0);
  }
  return flag_error;  // Успешное завершение, ошибок не было
}