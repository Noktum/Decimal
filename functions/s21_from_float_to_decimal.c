#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int error = 0, scale = 0, scale_small = 0, scale_digit = 0;
  if (dst == NULL || (fabs(src) > MAX_DECIMAL) || (fabs(src) == INFINITY) ||
      isnan(fabs(src))) {
    error = 1;
  } else if (fabs(src) > 0 && fabs(src) < 1e-28) {
    error = 1;
    s21_get_zero();
  } else if (src == 0.0) {
    s21_get_zero();
  } else {
    fbits mantissa = {0};
    mantissa.fl = src;
    int exp = ((mantissa.ui & ~(1u << 31)) >> 23) - 127;
    unsigned int sign = (mantissa.ui >> 31) & 0x00000001;
    if (sign == 1) {
      mantissa.fl *= -1;
      s21_setSign(dst, 1);
    }
    if (exp >= -94 && exp < 96) {
      double mantissa_double = (double)mantissa.fl;
      if (fabs(src) < 1000000) {
        adjust_scale(&mantissa_double, &scale_small, &scale_digit);
      } else if (fabs(mantissa_double) > 9999999) {
        adjust_mantissa(&mantissa_double, &scale);
      }
      double mantissa_double_temp = mantissa_double;
      long int whole_part = mantissa_double;
      whole_part *= 100000000;
      mantissa_double_temp *= 100000000;
      long int fraction_part = mantissa_double_temp;
      fraction_part -= whole_part;
      if (fraction_part == 50000000) {
        long int digit = whole_part / 100000000;
        digit -= (whole_part / 1000000000) * 10;
        if ((digit % 2) == 1) mantissa_double += 1.0;
      }
      if (fraction_part != 50000000) mantissa_double = roundl(mantissa_double);
      dst->bits[0] = (unsigned int)mantissa_double;
      s21_decimal ten = {{0xA, 0x0, 0x0, 0x0}};
      for (int i = scale; i > 0; i--) s21_mul(*dst, ten, dst);
      s21_set_scale(dst, scale_small);
    }
  }
  return error;
}

void adjust_mantissa(double *mantissa_double, int *scale) {
  while (fabs(*mantissa_double) > 9999999) {
    *mantissa_double /= 10;
    (*scale)++;
  }
}

void adjust_scale(double *mantissa_double, int *scale_small, int *scale_digit) {
  while (fabs(*mantissa_double) < 1) {
    *mantissa_double *= 10;
    (*scale_small)++;
  }
  while (fabs(*mantissa_double) > 0 && fabs(*mantissa_double) < 1000000 &&
         (*scale_digit) < 7) {
    *mantissa_double *= 10;
    (*scale_small)++;
    (*scale_digit)++;
  }
  while (fmod(*mantissa_double, 10) == 0) {
    *mantissa_double /= 10;
    (*scale_small)--;
  }
  while ((*scale_small) > 28) {
    *mantissa_double /= 10;
    (*scale_small)--;
  }
}