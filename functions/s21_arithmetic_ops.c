#include "../s21_decimal.h"
/*
 Cложение двух decimal, код результата:
 0 - OK
 1 - число слишком велико или равно бесконечности
 2 - число слишком мало или равно отрицательной бесконечности

 Алгоритм:
 1) Если какое-то из чисел отрицательное - s21_sub.
 2) Перевод значений в big_decimal.
 3) Приведя оба числа к одной экспоненте, складываем бинарно и присваиваем
 значение мантиссы результату.
 4) Устанавливаем значение экспоненты в результат.
 5) Переводим big_decimal decimal, проверка на overflow.
 6) Если оба значения отрицательные, результат - отрицательный.
*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2), code = 0;
  if ((sign_1 == 0) && (sign_2 == 1)) {
    code = s21_sub(value_1, s21_dec_abs(value_2), result);
  } else if ((sign_1 == 1) && (sign_2 == 0)) {
    code = s21_sub(value_2, s21_dec_abs(value_1), result);
  } else {
    s21_big_decimal bvalue_1 = s21_get_zero_big(),
                    bvalue_2 = s21_get_zero_big();
    s21_dec_to_bigdec(value_1, &bvalue_1);
    s21_dec_to_bigdec(value_2, &bvalue_2);
    int res_exp = s21_toTheSameExp(&bvalue_1, &bvalue_2);
    s21_big_decimal bresult = s21_Big_add_binary(
        bvalue_1,
        bvalue_2);  // set_exp отдельной функцией или внутри суммы ставить?
    s21_setExp_big(&bresult, res_exp);
    if (sign_1 == 1) {
      s21_setSign_big(&bresult, 1);
    }
    code = s21_bigdec_to_dec(bresult, result);
  }
  return code;
}

/*
 Вычитание двух decimal, код результата::
 0 - OK
 1 - число слишком велико или равно бесконечности
 2 - число слишком мало или равно отрицательной бесконечности

 Алгоритм:
 1) Если какое-то одно из чисел - отрицательное, вызываем функцию s21_sum.
 2) Переводим оба значения в big_decimal и работаем с ними.
 3) Приведя оба числа к одной экспоненте, вычитаем бинарно и присваиваем
 значение мантиссы результату.
 4) Устанавливаем значение экспоненты в результат.
 5) Переводим в decimal, проверка на overflow

*/
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2), code = 0;
  if ((sign_1 == 0) && (sign_2 == 1)) {
    code = s21_add(value_1, s21_dec_abs(value_2), result);
  } else if ((sign_1 == 1) && (sign_2 == 0)) {
    s21_setSign(&value_2, 1);
    code = s21_add(value_1, value_2, result);
  } else if ((sign_1 == 1) && (sign_2 == 1)) {
    code = s21_sub(s21_dec_abs(value_2), s21_dec_abs(value_1), result);
  } else {
    s21_big_decimal bvalue_1 = s21_get_zero_big(),
                    bvalue_2 = s21_get_zero_big();
    s21_dec_to_bigdec(value_1, &bvalue_1);
    s21_dec_to_bigdec(value_2, &bvalue_2);
    int res_exp = s21_toTheSameExp(&bvalue_1, &bvalue_2);
    s21_big_decimal bresult = s21_Big_sub_binary(
        bvalue_1,
        bvalue_2);  // set_exp отдельной функцией или внутри суммы ставить?
    s21_setExp_big(&bresult, res_exp);
    code = s21_bigdec_to_dec(bresult, result);
  }
  return code;
}

/*
 Умножение двух decimal, код результата:
 0 - OK
 1 - число слишком велико или равно бесконечности
 2 - число слишком мало или равно отрицательной бесконечности

 Алгоритм:
 1) Если какое-то одно из чисел - отрицательное, делаем результат отрицательным.
 2) Переводим в big_decimal.
 3) Умножаем бинарно и присваиваем значение мантиссы результату.
 4) exp_1 + exp_2 => в значение экспоненты результата
 5) Переводим в decimal, проверка на overflow

*/
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2), code = 0;
  s21_big_decimal bvalue_1 = s21_get_zero_big(), bvalue_2 = s21_get_zero_big();
  s21_dec_to_bigdec(value_1, &bvalue_1);
  s21_dec_to_bigdec(value_2, &bvalue_2);
  int res_exp = s21_getExp_big(bvalue_1) + s21_getExp_big(bvalue_2);
  s21_big_decimal bresult = s21_Big_mul_binary(bvalue_1, bvalue_2);
  if (((sign_1 == 0) && (sign_2 == 1)) || ((sign_1 == 1) && (sign_2 == 0))) {
    s21_setSign_big(&bresult, 1);
  }
  s21_setExp_big(&bresult, res_exp);
  code = s21_bigdec_to_dec(bresult, result);
  return code;
}
/*
 Деление двух decimal, код результата:
 0 - OK
 1 - число слишком велико или равно бесконечности
 2 - число слишком мало или равно отрицательной бесконечности
 3 - деление на 0

 Алгоритм:
 1) Проверяем делитель на 0
 2) Переводим в big_decimal.
 3) Делим бинарно и присваиваем значение мантиссы результату.
 4) exp_1 - exp_2 => в значение экспоненты результата
 Если оно меньше нуля => умножаем результат и остаток на 10^(-exp), после чего
 exp = 0.
 5) Если остаток != 0, умножаем остаток и результат на 10 (при этом exp += 1),
 делим остаток на 10 и прибавляем к результату. Если новый остаток != 0,
 повторяем, пока либо остаток не станет == 0, либо пока результат < max_decimal.
 6) Переводим в decimal, проверка на overflow
*/

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = 0;
  if (s21_is_zero(value_2) == 0) {
    code = 3;
  } else {
    int sign_1 = s21_getSign(value_1), sign_2 = s21_getSign(value_2);
    s21_big_decimal bvalue_1 = s21_get_zero_big(),
                    bvalue_2 = s21_get_zero_big(),
                    remainder = s21_get_zero_big(),
                    remainder_2 = s21_get_zero_big();
    s21_dec_to_bigdec(value_1, &bvalue_1);
    s21_dec_to_bigdec(value_2, &bvalue_2);
    s21_big_decimal bresult =
        s21_Big_div_binary(bvalue_1, bvalue_2, &remainder);
    int res_exp = s21_getExp_big(bvalue_1) - s21_getExp_big(bvalue_2);
    int flag_exp = res_exp;
    if (res_exp < 0) {
      res_exp = 0;
    }
    while (
        (s21_is_zero_big(remainder) == 1) &&
        (s21_Big_comparison_binary(bresult, s21_get_max_decimal_big()) == 2)) {
      s21_mul_by_ten(&remainder);
      s21_big_decimal result_rem =
          s21_Big_div_binary(remainder, bvalue_2, &remainder_2);
      ++res_exp;
      s21_mul_by_ten(&bresult);
      bresult = s21_Big_add_binary(bresult, result_rem);
      remainder = remainder_2;
    }
    if (flag_exp < 0) {
      for (int i = 0, end = abs(flag_exp); i < end; ++i) {
        s21_mul_by_ten(&bresult);
      }
    }
    if (((sign_1 == 0) && (sign_2 == 1)) || ((sign_1 == 1) && (sign_2 == 0))) {
      s21_setSign_big(&bresult, 1);
    } else {
      s21_setSign_big(&bresult, 0);
    }
    s21_setExp_big(&bresult, res_exp);
    code = s21_bigdec_to_dec(bresult, result);
  }
  return code;
}

/*
Бинарное деление big_decimal с записью остатка в remainder.
Деление чисто мантисс без учета экспонент и знака.

Алгоритм:
1) Находим n такое, что value_2 * 2^(n + 1) >= value_1
2) result += 2^n
3) value_1 -= value_2 * 2^n
4) Повтор п. 1-3
*/
s21_big_decimal s21_Big_div_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2,
                                   s21_big_decimal *remainder) {  // CHANGED
  s21_big_decimal result = s21_get_zero_big(), temp_2, temp;
  int m_order_2 = s21_get_Max_order(value_2);
  unsigned int bit_val = value_1.bits[7];
  while (s21_Big_comparison_binary(value_1, value_2) != 2) {
    int m_order_1, dif_order, flag_comp;
    flag_comp = 0;
    m_order_1 = s21_get_Max_order(value_1);
    dif_order = m_order_1 - m_order_2;
    temp_2 = value_2;
    temp_2 = s21_shift_big(temp_2, dif_order, 1);
    if (s21_Big_comparison_binary(value_1, temp_2) == 1) {
      dif_order += 1;
      flag_comp = 1;
    }
    if (dif_order == 0) {
      temp = s21_get_pow2_big(0);
    } else {
      if (!flag_comp) temp_2 = s21_shift_big(temp_2, 1, 2);
      temp = s21_get_pow2_big(dif_order - 1);
    }
    result = s21_Big_add_binary(result, temp);
    value_1 = s21_Big_sub_binary(value_1, temp_2);
  }
  if (remainder != NULL) {
    *remainder = value_1;
  }
  result.bits[7] = bit_val;
  return result;
}

/*
Бинарное вычитание big_decimal.
Вычитание чисто мантисс без учета экспонент, но с учетом знака.

Алгоритм:

Побитовое вычитание, начиная с младших битов. Если bit_1 - bit_2 < 0,
то в следующем вычитании  будет bit_1 - bit_2 - 1.
*/
s21_big_decimal s21_Big_sub_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2) {  // CHANGE
  s21_big_decimal result = s21_get_zero_big();
  int temp = 0, exp = s21_getExp_big(value_1);
  if (s21_Big_comparison_binary(value_1, value_2) == 2) {
    s21_big_decimal temporary = value_1;
    value_1 = value_2;
    value_2 = temporary;
    s21_setBit_big(&result, 255, 1);
  }
  for (int i = 0; i < 224; ++i) {
    int sub = s21_getBit_big(value_1, i) - s21_getBit_big(value_2, i) - temp;
    s21_setBit_big(&result, i, abs(sub % 2));
    if (sub < 0) {
      temp = 1;
    } else {
      temp = 0;
    }
  }
  s21_setExp_big(&result, exp);
  return result;
}

/*
Бинарное сложение big_decimal.
Вычитание чисто мантисс без учета экспонент и знака.

Алгоритм:

Побитовое сложение, начиная с младших битов. Если bit_1 + bit_2 >= 2,
то в следующем сложении  будет bit_1 + bit_2 + 1.
*/
s21_big_decimal s21_Big_add_binary(
    s21_big_decimal value_1,
    s21_big_decimal value_2) {  // val_1 & val_2 positive
  s21_big_decimal result = s21_get_zero_big();
  int temp = 0;
  for (int i = 0; i < 224; ++i) {
    int bit1 = s21_getBit_big(value_1, i), bit2 = s21_getBit_big(value_2, i);
    int sum = bit1 + bit2 + temp;
    if (sum > 1) {
      temp = 1;
      s21_setBit_big(&result, i, sum - 2);
    } else {
      temp = 0;
      s21_setBit_big(&result, i, sum);
    }
  }
  result.bits[7] = value_1.bits[7];
  return result;
}

/*
Бинарное умножение big_decimal без учета экспоненты и знака

Алгоритм:
1) i == 0
2) Берем i-ый бит value_1
3) result += value_2 * bit * 2^(i)
4) i++
5) Повторяем 2-4 до последнего ненулевого бита value_1.
*/
s21_big_decimal s21_Big_mul_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2) {
  s21_big_decimal result = s21_get_zero_big(), temp = value_2;
  int max_bit_order_1 = s21_get_Max_order(value_1);
  for (int i = 0, end = max_bit_order_1 + 1; i < end; ++i) {
    int bit = s21_getBit_big(value_1, i);
    if (bit == 1) {
      result = s21_Big_add_binary(result, s21_shift_big(temp, i, 1));
    }
  }
  return result;
}

/*
 Умножение big_decimal на 10

 Алгоритм:
 1) temp = value
 2) value << 3 (*8)
 3) value += 2 * temp
 Т.е. 10 * value = 8 * value + 2 * value
*/
void s21_mul_by_ten(s21_big_decimal *value) {
  s21_big_decimal temp_val = *value;
  *value = s21_shift_big(*value, 3, 1);
  temp_val = s21_shift_big(temp_val, 1, 1);
  *value = s21_Big_add_binary(*value, temp_val);
  for (int i = 240; i < 248; ++i) {
    int temp = s21_getBit_big(*value, i);
    if (temp == 1) {
      s21_setBit_big(value, i, 0);
    } else {
      s21_setBit_big(value, i, 1);
      break;
    }
  }
}

/*
Возвращает модуль числа
*/
s21_decimal s21_dec_abs(s21_decimal value) {
  s21_setBit(&value, 127, 0);
  return value;
}