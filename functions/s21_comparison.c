#include "../s21_decimal.h"

// Returns "-1" if num1 < num2, "1" if num1 > num2, "0" if they are equal
int s21_comparison(s21_decimal num1, s21_decimal num2) {
  int flag = 0;
  if (s21_is_zero(num1) == 0) {
    s21_setSign(&num1, 0);
  }
  if (s21_is_zero(num2) == 0) {
    s21_setSign(&num2, 0);
  }
  int sign_1 = s21_getSign(num1), sign_2 = s21_getSign(num2);
  if (s21_is_zero(num1) == 0 && s21_is_zero(num2) == 0) {
  } else if (sign_1 == 1 && sign_2 == 0) {
    flag = -1;
  } else if (sign_1 == 0 && sign_2 == 1) {
    flag = 1;
  } else if (sign_1 == 0 && sign_2 == 0) {
    flag = s21_positive_comparison(num1, num2);
  } else if (sign_1 == 1 && sign_2 == 1) {
    flag = -s21_positive_comparison(num1, num2);
  }
  return flag;
}

// Comparison of positive values
// Returns "-1" if num1 < num2, "1" if num1 > num2, "0" if they are equal
int s21_positive_comparison(s21_decimal num1, s21_decimal num2) {
  int flag = 0;
  int scale1 = s21_getExp(num1), scale2 = s21_getExp(num2);
  s21_big_decimal big1 = s21_get_zero_big(), big2 = s21_get_zero_big();
  s21_dec_to_bigdec(num1, &big1);
  s21_dec_to_bigdec(num2, &big2);

  if (scale1 != scale2) {
    s21_toTheSameExp(&big1, &big2);
  }

  int i = 6;
  while (big1.bits[i] == 0 && big2.bits[i] == 0) {
    i--;
  }
  while (i >= 0 && flag == 0) {
    if (big1.bits[i] > big2.bits[i]) {
      flag = 1;
    } else if (big1.bits[i] < big2.bits[i]) {
      flag = -1;
    }
    i--;
  }
  return flag;
}

// Returns TRUE if num1 < num2
int s21_is_less(s21_decimal num1, s21_decimal num2) {
  int result = TRUE;
  if (s21_comparison(num1, num2) != -1) {
    result = FALSE;
  }
  return result;
}

// Returns TRUE if num1 > num2
int s21_is_greater(s21_decimal num1, s21_decimal num2) {
  int result = TRUE;
  if (s21_comparison(num1, num2) != 1) {
    result = FALSE;
  }
  return result;
}

// Returns TRUE if num1 == num2
int s21_is_equal(s21_decimal num1, s21_decimal num2) {
  int result = TRUE;
  if (s21_comparison(num1, num2) != 0) {
    result = FALSE;
  }
  return result;
}

// Returns TRUE if num1 != num2
int s21_is_not_equal(s21_decimal num1, s21_decimal num2) {
  int result = TRUE;
  if (s21_comparison(num1, num2) == 0) {
    result = FALSE;
  }
  return result;
}

// Returns TRUE if num1 <= num2
int s21_is_less_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = FALSE;
  if (s21_is_less(num1, num2) || s21_is_equal(num1, num2)) {
    result = TRUE;
  }
  return result;
}

// Returns TRUE if num1 >= num2
int s21_is_greater_or_equal(s21_decimal num1, s21_decimal num2) {
  int result = FALSE;
  if (s21_is_greater(num1, num2) || s21_is_equal(num1, num2)) {
    result = TRUE;
  }
  return result;
}