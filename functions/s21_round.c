#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int code = 0;
  if (!result) {
    code = 1;
  } else if (!s21_is_decimal_correct(value)) {
    *result = s21_get_zero();
    code = 1;
  } else {
    s21_big_decimal bvalue = s21_get_zero_big(), rem = s21_get_zero_big(),
                    zero_pfve = s21_get_zero_pfive();
    s21_dec_to_bigdec(value, &bvalue);
    int exp = s21_getExp_big(bvalue);
    bvalue = s21_Big_div_binary(bvalue, s21_get_pow10_big(exp), &rem);
    s21_setExp_big(&bvalue, 0);
    s21_setExp_big(&rem, exp);
    s21_toTheSameExp(&zero_pfve, &rem);
    if (s21_Big_comparison_binary(zero_pfve, rem) != 1) {
      bvalue = s21_Big_add_binary(bvalue, s21_get_one());
    }
    s21_bigdec_to_dec(bvalue, result);
  }
  return code;
}
