#include "../s21_decimal.h"
/*
  Смещение битов big_decimal на times раз в направлении direction:
 1 - влево (* 2), 2 - вправо (отсекаем младшие биты)

*/
s21_big_decimal s21_shift_big(s21_big_decimal value, int times, int direction) {
  s21_big_decimal temp = value;
  if (times != 0) {
    if (direction == 1) {
      int set_index, get_index;
      if (times < 32) {
        value.bits[0] = value.bits[0] << times;
      } else {
        value.bits[0] = 0;
      }
      for (int i = 1; i < 7; ++i) {
        if (times < 32) {
          value.bits[i] = value.bits[i] << times;
        } else {
          value.bits[i] = 0;
        }
        for (int j = 0; j < times; ++j) {
          set_index = j + i * 32;
          get_index = i * 32 - times + j;
          if ((set_index < 224) && (get_index >= 0)) {
            s21_setBit_big(&value, j + i * 32,
                           s21_getBit_big(temp, i * 32 - times + j));
          }
        }
      }
    } else if (direction == 2) {
      value.bits[6] = value.bits[6] >> times;
      for (int i = 5; i >= 0; --i) {
        value.bits[i] = value.bits[i] >> times;
        for (int j = 0; j < times; ++j) {
          s21_setBit_big(&value, (i + 1) * 32 - j - 1,
                         s21_getBit_big(temp, (i + 1) * 32 + times - j - 1));
        }
      }
    }
  }
  return value;
}  // 1 - left (<<), 2 - right (>>)