#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag_error = 0;

  // Проверка на NULL указатель dst
  if (dst == NULL) {
    flag_error = 1;  // Вернуть ошибку, если указатель NULL
  } else {
    s21_decimal src_trunc;
    s21_truncate(src, &src_trunc);
    int sign = s21_getSign(src_trunc);

    if ((src_trunc.bits[2] == 0) && (src_trunc.bits[1] == 0) &&
        (src_trunc.bits[0] < 2147483648 ||
         (sign && src_trunc.bits[0] == 2147483648))) {
      *dst = src_trunc.bits[0];
      if (sign) {
        (*dst) *= -1;
      }
    } else {
      // Значение src выходит за пределы допустимого диапазона для int
      flag_error = 1;
    }
  }
  return flag_error;
}