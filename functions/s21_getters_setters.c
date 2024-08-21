#include "../s21_decimal.h"

/* Функция, достающая бит по его индексу в decimal, биты в порядке от 0 до 127.

Как получается бит: допустим, хотим пятый бит отсюда:
11001|0|11010.
Создаем число 1 и 'двигаем' его влево на 5:
      1|00000
Дальше делаем логическую операцию & с этими двумя числами. Если искомый бит
нулевой, то в результате операции получим 1 & 0 = 0. Если же он равен единице,
то 1 & 1 = 1.
*/
int s21_getBit(s21_decimal value, int index) {
  int result = 0;
  if (index < 128) {
    unsigned int bit = 1 << (index - index / 32 * 32), temp;
    temp = value.bits[index / 32] & bit;
    if (temp > 0) {
      result = 1;
    }
  }
  return result;
}

int s21_get_bit_num(unsigned int num, int i) {
  int result = (num >> i) & 1;
  return result;
}

/* Функция, достающая бит по его индексу в big_decimal, биты в порядке от 0 до
255.
*/
int s21_getBit_big(s21_big_decimal value, int index) {
  int result = 0;
  if (index < 256) {
    unsigned int bit = 1 << (index - index / 32 * 32), temp;
    temp = value.bits[index / 32] & bit;
    if (temp > 0) {
      result = 1;
    }
  }
  return result;
}

/* Функция, достающая экспоненту из decimal.

Экспонента находится в последнем элементе с 16 по 23 бит. Начинаем доставать ее
от младшего бита и умножаем на соответствующую степень двойки. Пример: exp =
10110

порядок бита:   4  3  2  1  0
  экспонента:   1  0  1  1  0
1) exp == 0
   exp += 0 * 2^0
2) exp == 0
   exp += 1 * 2^1
3) exp == 2
   exp += 1 * 2^2
4) exp == 6
   exp += 0 * 2^3
5) exp == 6
   exp += 1 * 2^4

Итог: exp == 22
*/
int s21_getExp(s21_decimal value) {
  int exp = 0, power_2 = 1;
  for (int i = 16; i < 24; ++i) {
    exp += power_2 * s21_getBit(value, i + 96);
    // На каждой итерации увеличивается степень двойки, на которую надо умножать
    power_2 *= 2;
  }
  return exp;
}

// Функция, достающая экспоненту из big_decimal.
int s21_getExp_big(s21_big_decimal value) {
  int exp = 0, power_2 = 1;
  for (int i = 16; i < 24; ++i) {
    exp += power_2 * s21_getBit_big(value, i + 224);
    power_2 *= 2;
  }
  return exp;
}

// Функция, достающая знак из decimal. Если 1, то отрицатльное, 0 -
// положительное.
int s21_getSign(s21_decimal value) {
  int bit = s21_getBit(value, 127);
  return bit;
}

// Функция, достающая знак из big_decimal. Если 1, то отрицатльное, 0 -
// положительное.
int s21_getSign_big(s21_big_decimal value) {
  int bit = s21_getBit_big(value, 255);
  return bit;
}

/*
Возвращает порядок старшего бита числа
Если число нулевое, вернет -1

Пример: число 1 1 0 1
Порядок старшего бита == 3 (нумерация с нуля)
*/
int s21_get_Max_order(s21_big_decimal value) {  // CHANGE
  int res, temp = 0;
  for (int i = 223; i >= 0 && temp == 0; --i) {
    temp = s21_getBit_big(value, i);
    res = i;
  }
  return res;
}

// Функция, которая устанавливает нужный бит на соответствующий индекс
// (Нумерация индексов с нуля).
void s21_setBit(s21_decimal *value, int index, int bit_toset) {
  int bit_tochange = s21_getBit(*value, index);
  // Проверка: если бит уже такой, какой нужен, то менять ничего не будем.
  if (bit_tochange != bit_toset) {
    // Двигаем единицу
    unsigned int bit = (1 << (index - index / 32 * 32));
    // Если надо будет менять 1 на 0, то применяем исключающее или
    // Если 0 на 1, то обычный оператор или
    if (bit_tochange == 1) {
      value->bits[index / 32] = value->bits[index / 32] ^ bit;
    } else {
      value->bits[index / 32] = value->bits[index / 32] | bit;
    }
  }
}

// Функция, которая устанавливает нужный бит на соответствующий индекс
// (Нумерация индексов с нуля).
void s21_setBit_big(s21_big_decimal *value, int index, int bit_toset) {
  int bit_tochange = s21_getBit_big(*value, index);
  if (bit_tochange != bit_toset) {
    unsigned int bit = (1 << (index - index / 32 * 32));
    if (bit_tochange == 1) {
      value->bits[index / 32] = value->bits[index / 32] ^ bit;
    } else {
      value->bits[index / 32] = value->bits[index / 32] | bit;
    }
  }
}

/*
 Функция, устанавливающая знак decimal (127 бит, 0 - положительное, 1 -
 отрицательное)
*/
void s21_setSign(s21_decimal *value, int sign) { s21_setBit(value, 127, sign); }

/*
 Функция, устанавливающая знак big_decimal (255 бит, 0 - положительное, 1 -
 отрицательное)
*/
void s21_setSign_big(s21_big_decimal *value, int sign) {
  s21_setBit_big(value, 255, sign);
}

void s21_set_scale(s21_decimal *result, int exp) {
  int i = 112;
  int k = 0;
  while (i < 119) {
    s21_setBit(result, i, s21_get_bit_num(exp, k));
    i++;
    k++;
  }
}

// Функция, устанавливающая экспоненту в big_decimal.
void s21_setExp_big(s21_big_decimal *value, int exp) {
  for (int i = 0; i < 7; ++i) {
    // Получение младшего бита экспоненты
    int bit = exp & 1;
    s21_setBit_big(value, i + 240, bit);
    // Смещение экспоненты на 1 разряд вправо (отсечение младшего)
    exp = exp >> 1;
  }
}

/*
 Приведение двух big_decimal к одной экспоненте.
 Возвращает экспоненту, к которой приведены оба числа.

 Алгоритм:
 1) Вычисляем экспоненты обоих чисел.
 2) Число с меньшей экспонентой умножаем на 10 (abs(exp_1 - exp_2)) раз.
 3) Его экспоненте присваиваем новое значение.
*/
int s21_toTheSameExp(s21_big_decimal *value_1, s21_big_decimal *value_2) {
  int exp_1 = 0, exp_2 = 0, power_2 = 1;
  for (int i = 240; i < 248; ++i) {
    exp_1 += s21_getBit_big(*value_1, i) * power_2;
    exp_2 += s21_getBit_big(*value_2, i) * power_2;
    power_2 *= 2;
  }
  int res_exp = exp_1;
  if (exp_1 > exp_2) {
    int diff = exp_1 - exp_2;
    for (int i = 0; i < diff; ++i) {
      s21_mul_by_ten(value_2);
    }
  } else if (exp_2 > exp_1) {
    res_exp = exp_2;
    int diff = exp_2 - exp_1;
    for (int i = 0; i < diff; ++i) {
      s21_mul_by_ten(value_1);
    }
  }
  return res_exp;
}

/*
 Функция, дающая 0 в виде числа decimal. Необходима, т.к. иначе в объявленном,
 но не определенном decimal будет содержаться мусор
*/
s21_decimal s21_get_zero() {
  s21_decimal result;
  for (int i = 0; i < 4; ++i) {
    result.bits[i] = 0;
  }
  return result;
}

/*
 Функция, дающая 0 в виде числа big_decimal. Необходима, т.к. иначе в
 объявленном, но не определенном big_decimal будет содержаться мусор
*/
s21_big_decimal s21_get_zero_big() {
  s21_big_decimal result;
  for (int i = 0; i < 8; ++i) {
    result.bits[i] = 0;
  }
  return result;
}
/*
 Функция, позволяющая получить 0.5 в виде big_decimal. Нужно для банковского
 округления.
*/
s21_big_decimal s21_get_zero_pfive() {
  s21_big_decimal result = s21_get_zero_big();
  result.bits[0] = 5;
  // Ставим такое двоичное число, чтобы биты с 16 по 23 == 00000001 - это
  // экспонента == 1, т. к. 0.5 = 5/10^1
  result.bits[7] = 65536;
  return result;
}

// Функция, позволяющая получить 1 в виде big_decimal.
s21_big_decimal s21_get_one() {
  s21_big_decimal result = s21_get_zero_big();
  result.bits[0] = 1;
  return result;
}
// Функция, позволяющая получить 10 в виде big_decimal.
s21_big_decimal s21_get_10_big() {
  s21_big_decimal result = s21_get_zero_big();
  result.bits[0] = 10;
  return result;
}
/*
 Функция, позволяющая получить нужную степень двойки в виде big_decimal.
 power - степень двойки
*/
s21_big_decimal s21_get_pow2_big(int power) {
  s21_big_decimal result = s21_get_zero_big();
  s21_setBit_big(&result, power, 1);
  return result;
}

// Функция, позволяющая получить нужную степень десяти в виде big_decimal
s21_big_decimal s21_get_pow10_big(int power) {
  s21_big_decimal result = s21_get_zero_big();
  if (power <= 9) {
    result.bits[0] = (unsigned int)(pow(10, power));
  } else {
    result.bits[0] = (unsigned int)(pow(10, 9));
    for (int i = 0, end = power - 9; i < end; ++i) {
      s21_mul_by_ten(&result);
    }
  }
  return result;
}
/*
 Функция, позволяющая получить максимальный decimal в виде big_decimal. Все
 биты в bits[0], bits[1], bits[2] равны единице. Нужно для сравнения
*/
s21_big_decimal s21_get_max_decimal_big() {
  s21_big_decimal result = s21_get_zero_big();
  for (int i = 0; i < 3; ++i) {
    result.bits[i] = UINT_MAX;
  }
  return result;
}