#ifndef S21_DECIMAL
#define S21_DECIMAL
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_DECIMAL \
  79228162514264337593543950335.0F  // 79,228,162,514,264,337,593,543,950,335
#define MIN_DECIMAL \
  (-79228162514264337593543950335.0F)  //-79,228,162,514,264,337,593,543,950,335
#define SC \
  0x00ff0000  // 00000000 11111111 000000000 00000000 // scale - степень

#define MINUS 0x80000000

#define POSITIVE 0
#define NEGATIVE 1

/*
[0] 00000000.00000000.00000000.00000000  \
[1] 00000000.00000000.00000000.00000000  |- mantiss
[2] 00000000.00000000.00000000.00000000 /
[3] [0]xxxxxxx.[00000000].xxxxxxxx.xxxxxxxx
.....^.................^
....sign...........scale
    0 - +
    1 - -
*/

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;

typedef union {
  int ui;
  float fl;
} fbits;

// Arithmetic Operators
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Another functions
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_comparison(s21_decimal num1, s21_decimal num2);
int s21_positive_comparison(s21_decimal num1, s21_decimal num2);

// Oolongsh
int s21_getBit(s21_decimal value, int index);
int s21_getBit_big(s21_big_decimal value, int index);
int s21_getExp(s21_decimal value);
int s21_getExp_big(s21_big_decimal value);
int s21_getSign(s21_decimal value);
int s21_getSign_big(s21_big_decimal value);
void s21_setBit(s21_decimal *value, int index, int bit_toset);
void s21_setBit_big(s21_big_decimal *value, int index, int bit_toset);
void s21_setSign(s21_decimal *value, int sign);
void s21_setSign_big(s21_big_decimal *value, int sign);
void s21_setExp_big(s21_big_decimal *value, int exp);

s21_decimal s21_get_zero();
s21_big_decimal s21_get_zero_big();
s21_big_decimal s21_get_zero_pfive();
s21_big_decimal s21_get_one();
s21_big_decimal s21_get_10_big();
s21_big_decimal s21_get_pow2_big(int power);
s21_big_decimal s21_get_pow10_big(int power);
s21_big_decimal s21_get_max_decimal_big();

s21_big_decimal s21_bank_rounding(s21_big_decimal value,
                                  s21_big_decimal remainder);

void s21_dec_to_bigdec(s21_decimal value, s21_big_decimal *bvalue);
int s21_bigdec_to_dec(s21_big_decimal bvalue, s21_decimal *value);

s21_big_decimal s21_shift_big(s21_big_decimal value, int times, int direction);

int s21_toTheSameExp(s21_big_decimal *value_1, s21_big_decimal *value_2);
void s21_mul_by_ten(s21_big_decimal *value);
int s21_is_even(s21_big_decimal value);
int s21_bigdec_to_dec_shift(s21_big_decimal value);
s21_decimal s21_dec_abs(s21_decimal value);
int s21_Big_comparison_binary(s21_big_decimal value_1, s21_big_decimal value_2);
s21_big_decimal s21_Big_add_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
s21_big_decimal s21_Big_sub_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
s21_big_decimal s21_Big_div_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2,
                                   s21_big_decimal *remainder);
int s21_is_even(s21_big_decimal value);
int s21_Big_comparison(s21_big_decimal value_1, s21_big_decimal value_2);
int s21_is_zero(s21_decimal value);
int s21_is_zero_big(s21_big_decimal value);
int s21_get_Max_order(s21_big_decimal value);
s21_big_decimal s21_Big_mul_binary(s21_big_decimal value_1,
                                   s21_big_decimal value_2);
int s21_is_decimal_correct(s21_decimal value);

// Helping functions
int s21_get_sign(s21_decimal decimal);
void s21_set_sign(s21_decimal *decimal, int sign_to_set);

int s21_get_scale(s21_decimal decimal);
void s21_set_scale(s21_decimal *decimal, int scale);

void s21_set_bit(s21_decimal *num, int index, int bit);

int s21_get_bit_num(unsigned int num, int i);

int s21_get_bit(s21_decimal num, int i);

int s21_is_decimal_correct(s21_decimal value);
void adjust_mantissa(double *mantissa_double, int *scale);
void adjust_scale(double *mantissa_double, int *scale_small, int *scale_digit);

#endif