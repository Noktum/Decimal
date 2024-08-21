#include "../s21_decimal.h"

/*
Проверяет, big_decimal == 0 ?
Возвращаемое значение: 0 - равно нулю
                       1 - не равно нулю
*/
int s21_is_zero_big(s21_big_decimal value) {
  int result = 0;
  for (int i = 0; i < 7; ++i) {
    if (value.bits[i] != 0) {
      result = 1;
    }
  }
  return result;
}

/*
Проверяет, decimal == 0 ?
Возвращаемое значение: 0 - равно нулю
                       1 - не равно нулю
*/
int s21_is_zero(s21_decimal value) {  // CHANGE AS 'EQUAL'
  int result = 0;
  for (int i = 0; i < 3; ++i) {
    if (value.bits[i] != 0) {
      result = 1;
    }
  }
  return result;
}

/*
Сравнивает два big_decimal
Возвращаемое значение: 0 - равны
                       1 - value_1 > value_2
                       2 - value_2 > value_1
*/
int s21_Big_comparison(s21_big_decimal value_1, s21_big_decimal value_2) {
  s21_toTheSameExp(&value_1, &value_2);
  int res = s21_Big_comparison_binary(value_1, value_2);
  return res;
}

/*
Бинарное сравнение big_decimal без учета экспонент и знака.
Возвращаемое значение: 0 - равны
                       1 - value_1 > value_2
                       2 - value_2 > value_1
*/
int s21_Big_comparison_binary(  // CHANGE LIKE 'EQUAL'
    s21_big_decimal value_1,
    s21_big_decimal value_2) {  // 0 - eq, 1 - 1>2, 2 - 2>1
  int result = 0;
  for (int i = 6; i >= 0; --i) {
    if (value_1.bits[i] > value_2.bits[i]) {
      result = 1;
      break;
    } else if (value_2.bits[i] > value_1.bits[i]) {
      result = 2;
      break;
    }
  }
  return result;
}

/*
Четное число или нет

Возвращает 1 - число нечетное
           0 - число четное
*/
int s21_is_even(s21_big_decimal value) { return s21_getBit_big(value, 0); }

/*
Проверка, корректен ли decimal:
1 - да
0 - нет
*/
int s21_is_decimal_correct(s21_decimal value) {
  int code = 1;
  // биты 0-15 должны быть нулевыми
  for (int i = 0; i < 16; ++i) {
    if (s21_getBit(value, 96 + i) == 1) {
      code = 0;
      break;
    }
  }
  // экспонента не больше 28
  if (code) {
    int exp = 0, power_2 = 1;
    for (int i = 16; i < 24; ++i) {
      exp += s21_getBit(value, 96 + i) * power_2;
      power_2 *= 2;
    }
    if (exp > 28) code = 0;
  }
  if (code) {
    for (int i = 24; i < 31; ++i) {
      if (s21_getBit(value, 96 + i) == 1) {
        code = 0;
        break;
      }
    }
  }
  return code;
}
