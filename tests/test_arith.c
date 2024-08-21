#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_decimal.h"

int s21_is_zero_val(s21_decimal val);
void s21_mul_by_ten_hand(s21_decimal *value);
int s21_toTheSameExp_hand(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal s21_Big_add_binary_hand(s21_decimal value_1, s21_decimal value_2);
void s21_print_fail(s21_decimal x);
int s21_is_equal_hand_div(s21_decimal *x, s21_decimal *y);
int s21_is_equal_hand(s21_decimal x, s21_decimal y);
void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check);
void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2, int code_check);
void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check);
void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check);
s21_decimal s21_shift(s21_decimal value, int times, int direction);

START_TEST(test_div1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -20000000000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 1.0000000002328306436538696289
  s21_decimal decimal_check = {{0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000002328306436538696289
  s21_decimal decimal_check = {
      {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -10000000000000000000000000000
  s21_decimal decimal_check = {
      {0x10000000, 0x3E250261, 0x204FCE5E, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 1320469375237738959892399172.1
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -1320469375237738959892399172.1
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 1999999999534338.7126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xD0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -1999999999534338.7126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800D0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div56) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div58) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div60) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div61) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div62) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div63) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 55340232234013556739000000000
  s21_decimal decimal_check = {{0xB2D05E00, 0xB2D05E00, 0xB2D05E00, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div64) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -55340232234013556739000000000
  s21_decimal decimal_check = {
      {0xB2D05E00, 0xB2D05E00, 0xB2D05E00, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div65) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 9364712231340627836019760.833
  s21_decimal decimal_check = {{0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div66) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -9364712231340627836019760.833
  s21_decimal decimal_check = {
      {0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div67) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div68) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div69) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 79149013500763574019524425909
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div70) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -79149013500763574019524425909
  s21_decimal decimal_check = {
      {0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div71) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div72) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div73) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div74) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div75) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div76) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div77) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div78) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div79) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // -55.440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x801B0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div80) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // 55.440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x1B0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div81) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 21669104637638919604.083853925
  s21_decimal decimal_check = {{0x63478A65, 0x327B2965, 0x46044364, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div82) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -21669104637638919604.083853925
  s21_decimal decimal_check = {
      {0x63478A65, 0x327B2965, 0x46044364, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div83) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 126429998059967356684.63712959
  s21_decimal decimal_check = {{0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div84) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -126429998059967356684.63712959
  s21_decimal decimal_check = {
      {0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80080000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div85) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div86) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div87) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div88) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div89) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div90) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div91) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div92) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div93) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div94) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div95) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div96) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // 2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div97) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -20000000000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div98) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 20000000000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div99) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // -18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div100) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 18446744069414584321
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div101) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // -1.0000000002328306436538696289
  s21_decimal decimal_check = {
      {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div102) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000002328306436538696289
  s21_decimal decimal_check = {{0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div103) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // -18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div104) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div105) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // -36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div106) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // 36893488147419103232
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div107) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // -9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div108) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // 9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div109) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div110) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div111) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // -39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div112) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // 39614081257132168796771975168
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div113) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div114) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div115) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div116) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div117) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div118) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950327
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div119) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div120) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div121) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div122) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div123) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div124) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div125) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div126) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div127) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -10000000000000000000000000000
  s21_decimal decimal_check = {
      {0x10000000, 0x3E250261, 0x204FCE5E, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div128) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 10000000000000000000000000000
  s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div129) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // -1320469375237738959892399172.1
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div130) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // 1320469375237738959892399172.1
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div131) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div132) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div133) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div134) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div135) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div136) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div137) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // -1999999999534338.7126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800D0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div138) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // 1999999999534338.7126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xD0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div139) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // -1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div140) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div141) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // -368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div142) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // 368934881474191032320000
  s21_decimal decimal_check = {{0x0, 0x0, 0x4E20, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div143) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // -1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div144) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // 1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div145) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div146) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div147) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // -55340232234013556739000000000
  s21_decimal decimal_check = {
      {0xB2D05E00, 0xB2D05E00, 0xB2D05E00, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div148) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // 55340232234013556739000000000
  s21_decimal decimal_check = {{0xB2D05E00, 0xB2D05E00, 0xB2D05E00, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div149) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -9364712231340627836019760.833
  s21_decimal decimal_check = {
      {0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div150) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // 9364712231340627836019760.833
  s21_decimal decimal_check = {{0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div151) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // -9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div152) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // 9903520314283042199192993792
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div153) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // -79149013500763574019524425909
  s21_decimal decimal_check = {
      {0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div154) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // 79149013500763574019524425909
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div155) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950335
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div156) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div157) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div158) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div159) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div160) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div161) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div162) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div163) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 55.440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x1B0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div164) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -55.440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x801B0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div165) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -21669104637638919604.083853925
  s21_decimal decimal_check = {
      {0x63478A65, 0x327B2965, 0x46044364, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div166) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 21669104637638919604.083853925
  s21_decimal decimal_check = {{0x63478A65, 0x327B2965, 0x46044364, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div167) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -126429998059967356684.63712959
  s21_decimal decimal_check = {
      {0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80080000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div168) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 126429998059967356684.63712959
  s21_decimal decimal_check = {{0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div169) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div170) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div171) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div172) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div173) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div174) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div175) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div176) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div177) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 0.1999999999999999999891579783
  s21_decimal decimal_check = {{0xC989A387, 0x3FA10079, 0x6765C79, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div178) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -0.1999999999999999999891579783
  s21_decimal decimal_check = {{0xC989A387, 0x3FA10079, 0x6765C79, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div179) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 0.2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div180) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -0.2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div181) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 2000000000000000000000000000
  s21_decimal decimal_check = {{0xD0000000, 0x3FA10079, 0x6765C79, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div182) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -2000000000000000000000000000
  s21_decimal decimal_check = {{0xD0000000, 0x3FA10079, 0x6765C79, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div183) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 1844674406941458432.1
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div184) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -1844674406941458432.1
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div185) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 0.1000000000232830643653869629
  s21_decimal decimal_check = {{0x87D0803D, 0xA30BAE79, 0x33B2E3C, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div186) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -0.1000000000232830643653869629
  s21_decimal decimal_check = {{0x87D0803D, 0xA30BAE79, 0x33B2E3C, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div187) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 1844674407370955161.6
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div188) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -1844674407370955161.6
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div189) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 3689348814741910323.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div190) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -3689348814741910323.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div191) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 922337203792851763.2125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x40000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div192) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -922337203792851763.2125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80040000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div193) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 1584563250285286751870879006.7
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div194) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -1584563250285286751870879006.7
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div195) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 3961408125713216879677197516.8
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div196) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -3961408125713216879677197516.8
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div197) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 3961408125713216879677197714.8
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div198) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -3961408125713216879677197714.8
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div199) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 3961408125713216879677197516.9
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div200) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -3961408125713216879677197516.9
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div201) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395032.7
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div202) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7922816251426433759354395032.7
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div203) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div204) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div205) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div206) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div207) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div208) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div209) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div210) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div211) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 1000000000000000000000000000
  s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div212) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -1000000000000000000000000000
  s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div213) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 132046937523773895989239917.21
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x20000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div214) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -132046937523773895989239917.21
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80020000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div215) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div216) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div217) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div218) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div219) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div220) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div221) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 199999999953433.87126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xE0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div222) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -199999999953433.87126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800E0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div223) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 184467440737095516160000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x989680, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div224) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -184467440737095516160000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x989680, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div225) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 36893488147419103232000
  s21_decimal decimal_check = {{0x0, 0x0, 0x7D0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div226) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -36893488147419103232000
  s21_decimal decimal_check = {{0x0, 0x0, 0x7D0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div227) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 184467440780045189130000000
  s21_decimal decimal_check = {{0x989680, 0x989680, 0x989680, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div228) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -184467440780045189130000000
  s21_decimal decimal_check = {{0x989680, 0x989680, 0x989680, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div229) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // 7923608612287662525606955729
  s21_decimal decimal_check = {{0xB80E8AD1, 0x917FD565, 0x199A4163, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div230) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // -7923608612287662525606955729
  s21_decimal decimal_check = {
      {0xB80E8AD1, 0x917FD565, 0x199A4163, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div231) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 5534023223401355673900000000
  s21_decimal decimal_check = {{0x11E1A300, 0x11E1A300, 0x11E1A300, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div232) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -5534023223401355673900000000
  s21_decimal decimal_check = {
      {0x11E1A300, 0x11E1A300, 0x11E1A300, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div233) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // 936471223134062783601976.0833
  s21_decimal decimal_check = {{0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x40000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div234) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // -936471223134062783601976.0833
  s21_decimal decimal_check = {
      {0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x80040000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div235) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // 990352031428304219919299379.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div236) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // -990352031428304219919299379.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div237) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // 7914901350076357401952442590.9
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div238) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // -7914901350076357401952442590.9
  s21_decimal decimal_check = {
      {0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div239) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div240) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div241) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // 792281625142643375935439503.35
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div242) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // -792281625142643375935439503.35
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div243) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div244) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div245) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div246) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div247) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // -5.5440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div248) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // 5.5440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div249) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // 2166910463763891960.4083853925
  s21_decimal decimal_check = {{0x63478A65, 0x327B2965, 0x46044364, 0xA0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div250) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // -2166910463763891960.4083853925
  s21_decimal decimal_check = {
      {0x63478A65, 0x327B2965, 0x46044364, 0x800A0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div251) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // 12642999805996735668.463712959
  s21_decimal decimal_check = {{0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div252) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // -12642999805996735668.463712959
  s21_decimal decimal_check = {
      {0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div253) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div254) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div255) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div256) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div257) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div258) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div259) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div260) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div261) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // -0.1999999999999999999891579783
  s21_decimal decimal_check = {{0xC989A387, 0x3FA10079, 0x6765C79, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div262) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // 0.1999999999999999999891579783
  s21_decimal decimal_check = {{0xC989A387, 0x3FA10079, 0x6765C79, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div263) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // -0.2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div264) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // 0.2
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div265) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // -2000000000000000000000000000
  s21_decimal decimal_check = {{0xD0000000, 0x3FA10079, 0x6765C79, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div266) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // 2000000000000000000000000000
  s21_decimal decimal_check = {{0xD0000000, 0x3FA10079, 0x6765C79, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div267) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // -1844674406941458432.1
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div268) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // 1844674406941458432.1
  s21_decimal decimal_check = {{0x1, 0xFFFFFFFF, 0x0, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div269) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // -0.1000000000232830643653869629
  s21_decimal decimal_check = {{0x87D0803D, 0xA30BAE79, 0x33B2E3C, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div270) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // 0.1000000000232830643653869629
  s21_decimal decimal_check = {{0x87D0803D, 0xA30BAE79, 0x33B2E3C, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div271) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // -1844674407370955161.6
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div272) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // 1844674407370955161.6
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div273) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // -3689348814741910323.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div274) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // 3689348814741910323.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x2, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div275) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // -922337203792851763.2125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80040000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div276) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // 922337203792851763.2125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x40000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div277) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // -1584563250285286751870879006.7
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div278) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // 1584563250285286751870879006.7
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div279) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // -3961408125713216879677197516.8
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div280) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // 3961408125713216879677197516.8
  s21_decimal decimal_check = {{0x0, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div281) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -3961408125713216879677197714.8
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div282) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 3961408125713216879677197714.8
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div283) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -3961408125713216879677197516.9
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div284) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 3961408125713216879677197516.9
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div285) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7922816251426433759354395032.7
  s21_decimal decimal_check = {
      {0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div286) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395032.7
  s21_decimal decimal_check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div287) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div288) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div289) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div290) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div291) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div292) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div293) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7922816251426433759354395034
  s21_decimal decimal_check = {
      {0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div294) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395034
  s21_decimal decimal_check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div295) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -1000000000000000000000000000
  s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div296) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 1000000000000000000000000000
  s21_decimal decimal_check = {{0xE8000000, 0x9FD0803C, 0x33B2E3C, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div297) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // -132046937523773895989239917.21
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80020000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div298) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // 132046937523773895989239917.21
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x20000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div299) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div300) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div301) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div302) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div303) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div304) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div305) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // -199999999953433.87126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800E0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div306) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // 199999999953433.87126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xE0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div307) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // -184467440737095516160000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x989680, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div308) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // 184467440737095516160000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x989680, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div309) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // -36893488147419103232000
  s21_decimal decimal_check = {{0x0, 0x0, 0x7D0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div310) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // 36893488147419103232000
  s21_decimal decimal_check = {{0x0, 0x0, 0x7D0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div311) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // -184467440780045189130000000
  s21_decimal decimal_check = {{0x989680, 0x989680, 0x989680, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div312) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // 184467440780045189130000000
  s21_decimal decimal_check = {{0x989680, 0x989680, 0x989680, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div313) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // -7923608612287662525606955729
  s21_decimal decimal_check = {
      {0xB80E8AD1, 0x917FD565, 0x199A4163, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div314) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // 7923608612287662525606955729
  s21_decimal decimal_check = {{0xB80E8AD1, 0x917FD565, 0x199A4163, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div315) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // -5534023223401355673900000000
  s21_decimal decimal_check = {
      {0x11E1A300, 0x11E1A300, 0x11E1A300, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div316) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // 5534023223401355673900000000
  s21_decimal decimal_check = {{0x11E1A300, 0x11E1A300, 0x11E1A300, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div317) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x30000}};
  // -936471223134062783601976.0833
  s21_decimal decimal_check = {
      {0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x80040000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div318) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -8460.288
  s21_decimal decimal2 = {{0x811800, 0x0, 0x0, 0x80030000}};
  // 936471223134062783601976.0833
  s21_decimal decimal_check = {{0x9ACD5EC1, 0x4BCA35AA, 0x1E424EF3, 0x40000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div319) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x30000}};
  // -990352031428304219919299379.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div320) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -8.000
  s21_decimal decimal2 = {{0x1F40, 0x0, 0x0, 0x80030000}};
  // 990352031428304219919299379.2
  s21_decimal decimal_check = {{0x0, 0x0, 0x20000000, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div321) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x30000}};
  // -7914901350076357401952442590.9
  s21_decimal decimal_check = {
      {0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div322) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.001
  s21_decimal decimal2 = {{0x3E9, 0x0, 0x0, 0x80030000}};
  // 7914901350076357401952442590.9
  s21_decimal decimal_check = {{0xFBE878B5, 0x6170458F, 0xFFBE878B, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div323) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div324) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1.0
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div325) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x0}};
  // -792281625142643375935439503.35
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div326) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x80000000}};
  // 792281625142643375935439503.35
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div327) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div328) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div329) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div330) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // division by zero
  int code_check = 3;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div331) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x80010000}};
  // 5.5440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div332) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 1429062841781896312709593009.2
  s21_decimal decimal2 = {{0xDF162CEC, 0xD6D0972E, 0x2E2CEE46, 0x10000}};
  // -5.5440642775005513864255183391
  s21_decimal decimal_check = {{0x2D411A1F, 0x85E406F, 0xB3236CC3, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div333) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x130000}};
  // -2166910463763891960.4083853925
  s21_decimal decimal_check = {
      {0x63478A65, 0x327B2965, 0x46044364, 0x800A0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div334) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -3656273013.5441854660747245473
  s21_decimal decimal2 = {{0x3C2CB7A1, 0x3E0B91AF, 0x7623FB44, 0x80130000}};
  // 2166910463763891960.4083853925
  s21_decimal decimal_check = {{0x63478A65, 0x327B2965, 0x46044364, 0xA0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div335) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x140000}};
  // -12642999805996735668.463712959
  s21_decimal decimal_check = {
      {0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div336) {
  // -7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -626656361.06935169033698303587
  s21_decimal decimal2 = {{0xD8705E63, 0x5DC32547, 0xCA7BCC9C, 0x80140000}};
  // 12642999805996735668.463712959
  s21_decimal decimal_check = {{0xFF91BABF, 0xD1DCAEAC, 0x28DA0B58, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div337) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div338) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div339) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div340) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -10
  s21_decimal decimal_check = {{0xA, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div341) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div342) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div343) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div344) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -3
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div345) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999998915797827
  s21_decimal decimal_check = {{0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div346) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168798919458816
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999998915797827
  s21_decimal decimal_check = {
      {0xDF606343, 0x7C4A04C1, 0x409F9CBC, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div347) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal_check = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div348) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x80000000}};
  // -1.9999999999999999999999999999
  s21_decimal decimal_check = {
      {0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div349) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x1C0000}};
  // 19999999999999999999999999999
  s21_decimal decimal_check = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div350) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.9614081257132168796771975168
  s21_decimal decimal2 = {{0x0, 0x0, 0x80000000, 0x801C0000}};
  // -19999999999999999999999999999
  s21_decimal decimal_check = {
      {0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div351) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x0}};
  // 18446744069414584320.999999999
  s21_decimal decimal_check = {{0x3B9AC9FF, 0xC4653600, 0x3B9AC9FF, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div352) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967297
  s21_decimal decimal2 = {{0x1, 0x1, 0x0, 0x80000000}};
  // -18446744069414584320.999999999
  s21_decimal decimal_check = {
      {0x3B9AC9FF, 0xC4653600, 0x3B9AC9FF, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div353) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x0}};
  // 1.0000000002328306436538696289
  s21_decimal decimal_check = {{0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x1C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div354) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162495817593524129366015
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000002328306436538696289
  s21_decimal decimal_check = {
      {0x4E250261, 0x5E74D0BF, 0x204FCE5E, 0x801C0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div355) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x0}};
  // 18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div356) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -4294967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000000}};
  // -18446744073709551616
  s21_decimal decimal_check = {{0x0, 0x0, 0x1, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div357) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x0}};
  // 36893488147419103231.999999999
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x773593FF, 0x90000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div358) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2147483648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80000000}};
  // -36893488147419103231.999999999
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0x773593FF, 0x80090000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div359) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x0}};
  // 9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x30000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div360) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8589934591
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x1, 0x0, 0x80000000}};
  // -9223372037928517632.125
  s21_decimal decimal_check = {{0x7D, 0xFA, 0x1F4, 0x80030000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div361) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x0}};
  // 15845632502852867518708790067
  s21_decimal decimal_check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div362) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80000000}};
  // -15845632502852867518708790067
  s21_decimal decimal_check = {
      {0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div363) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x0}};
  // 39614081257132168796771975167
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div364) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -2
  s21_decimal decimal2 = {{0x2, 0x0, 0x0, 0x80000000}};
  // -39614081257132168796771975167
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0x7FFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div365) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div366) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771977148
  s21_decimal decimal_check = {{0x7BC, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div367) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div368) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999999
  s21_decimal decimal2 = {{0x1FFFFFFF, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -39614081257132168796771975169
  s21_decimal decimal_check = {{0x1, 0x0, 0x80000000, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div369) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950326
  s21_decimal decimal_check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div370) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950326
  s21_decimal decimal_check = {
      {0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div371) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div372) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000008
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div373) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div374) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div375) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div376) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div377) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div378) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div379) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 10000000000000000000000000000
  s21_decimal decimal_check = {{0x10000000, 0x3E250261, 0x204FCE5E, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div380) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -10000000000000000000000000000
  s21_decimal decimal_check = {
      {0x10000000, 0x3E250261, 0x204FCE5E, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div381) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x1B0000}};
  // 1320469375237738959892399172.1
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x10000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div382) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -60.000000000000000000000000005
  s21_decimal decimal2 = {{0x60000005, 0x74DE0E46, 0xC1DED635, 0x801B0000}};
  // -1320469375237738959892399172.1
  s21_decimal decimal_check = {
      {0xAAAAAAA9, 0xAAAAAAAA, 0x2AAAAAAA, 0x80010000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div383) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div384) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div385) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div386) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div387) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x30000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div388) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.019
  s21_decimal decimal2 = {{0x13, 0x0, 0x0, 0x80030000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div389) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0xF0000}};
  // 1999999999534338.7126922607422
  s21_decimal decimal_check = {{0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0xD0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div390) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -39614081266355.540835774234624
  s21_decimal decimal2 = {{0x80000000, 0x80000000, 0x80000000, 0x800F0000}};
  // -1999999999534338.7126922607422
  s21_decimal decimal_check = {
      {0xA3B5FB3E, 0x3BAA6805, 0x409F9CBC, 0x800D0000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div391) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80000}};
  // 1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div392) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967296
  s21_decimal decimal2 = {{0x0, 0x1, 0x0, 0x80080000}};
  // -1844674407370955161600000000
  s21_decimal decimal_check = {{0x0, 0x0, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div393) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x40000}};
  // 368934881474191032319999.99999
  s21_decimal decimal_check = {{0xFFFFFFFF, 0xFFFFFFFF, 0x773593FF, 0x50000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div394) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -214748.3648
  s21_decimal decimal2 = {{0x80000000, 0x0, 0x0, 0x80040000}};
  // -368934881474191032319999.99999
  s21_decimal decimal_check = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0x773593FF, 0x80050000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div395) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80000}};
  // 1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div396) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -42.94967295
  s21_decimal decimal2 = {{0xFFFFFFFF, 0x0, 0x0, 0x80080000}};
  // -1844674407800451891300000000
  s21_decimal decimal_check = {{0x5F5E100, 0x5F5E100, 0x5F5E100, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div397) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x40000}};
  // overflow
  int code_check = 1;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div398) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.9999
  s21_decimal decimal2 = {{0x270F, 0x0, 0x0, 0x80040000}};
  // overflow
  int code_check = 2;

  test_div_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_div399) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x90000}};
  // 55340232234013556738999999999
  s21_decimal decimal_check = {{0xB2D05DFF, 0xB2D05E00, 0xB2D05E00, 0x0}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_div400) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80090000}};
  // -55340232234013556738999999999
  s21_decimal decimal_check = {
      {0xB2D05DFF, 0xB2D05E00, 0xB2D05E00, 0x80000000}};

  test_div(decimal1, decimal2, decimal_check);
}

START_TEST(test_add1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 52818775009509558395695966890
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 52818775015658473085500828330
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xAAAAAAAA, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 79228162508115422902307433130
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 79228162508115422903739088895
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 79228162514264337592112294570
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 79228162514264337593543950331
  s21_decimal check = {{0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // 79228106389283212384222373411
  s21_decimal check = {{0x3AC4E623, 0x756BD584, 0xFFFFF41D, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add56) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // 79228162514264337543839948913
  s21_decimal check = {{0x6D692071, 0xFFFFFFF4, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add58) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // 79228162514264337592894706333
  s21_decimal check = {{0xD94D529D, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add60) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add61) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add62) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add63) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add64) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add65) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add66) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add67) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add68) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add69) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add70) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add71) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add72) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add73) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add74) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add75) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add76) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add77) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add78) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add79) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add80) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add81) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add82) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add83) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add84) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add85) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -52818775009509558395695966890
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add86) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add87) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -52818775015658473085500828330
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xAAAAAAAA, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add88) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add89) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -79228162508115422902307433130
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add90) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add91) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -79228162508115422903739088895
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add92) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add93) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -79228162514264337592112294570
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add94) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add95) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add96) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add97) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add98) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add99) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add100) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add101) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add102) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add103) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add104) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add105) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -79228162514264337593543950331
  s21_decimal check = {{0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add106) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add107) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add108) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add109) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add110) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add111) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add112) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add113) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add114) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add115) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add116) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // -79228106389283212384222373411
  s21_decimal check = {{0x3AC4E623, 0x756BD584, 0xFFFFF41D, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add117) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add118) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // -79228162514264337543839948913
  s21_decimal check = {{0x6D692071, 0xFFFFFFF4, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add119) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add120) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // -79228162514264337592894706333
  s21_decimal check = {{0xD94D529D, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add121) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add122) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add123) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add124) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add125) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add126) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add127) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add128) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add129) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add130) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add131) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add132) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 71305346262837903834189555299
  s21_decimal check = {{0x66666663, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add133) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add134) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add135) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add136) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add137) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add138) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add139) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add140) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add141) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add142) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 79228162514264337593543950332
  s21_decimal check = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add143) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add144) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add145) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add146) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 52818775009509558395695966889
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add147) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add148) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 52818775015658473085500828329
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xAAAAAAAA, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add149) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add150) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 79228162508115422902307433129
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add151) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add152) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 79228162508115422903739088894
  s21_decimal check = {{0xFFFFFFFE, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add153) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add154) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 79228162514264337592112294569
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add155) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add156) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // 79228162514264337593517540946
  s21_decimal check = {{0xFE6D0652, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add157) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add158) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add159) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add160) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add161) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add162) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add163) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add164) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add165) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add166) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 79228162514264337593543950330
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add167) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add168) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add169) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add170) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add171) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add172) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add173) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add174) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add175) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // 79228106389283212384222373410
  s21_decimal check = {{0x3AC4E622, 0x756BD584, 0xFFFFF41D, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add176) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add177) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // 79228162514264337543839948912
  s21_decimal check = {{0x6D692070, 0xFFFFFFF4, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add178) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add179) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // 79228162514264337592894706332
  s21_decimal check = {{0xD94D529C, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add180) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add181) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add182) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add183) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add184) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add185) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add186) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add187) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add188) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add189) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add190) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add191) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -71305346262837903834189555299
  s21_decimal check = {{0x66666663, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add192) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add193) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add194) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add195) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add196) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add197) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add198) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add199) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add200) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add201) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -79228162514264337593543950332
  s21_decimal check = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add202) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add203) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add204) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add205) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -52818775009509558395695966889
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add206) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add207) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -52818775015658473085500828329
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xAAAAAAAA, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add208) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add209) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -79228162508115422902307433129
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add210) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add211) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -79228162508115422903739088894
  s21_decimal check = {{0xFFFFFFFE, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add212) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add213) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -79228162514264337592112294569
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add214) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add215) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // -79228162514264337593517540946
  s21_decimal check = {{0xFE6D0652, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add216) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add217) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add218) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add219) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add220) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add221) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add222) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add223) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add224) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add225) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -79228162514264337593543950330
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add226) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add227) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add228) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add229) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add230) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add231) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add232) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add233) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add234) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add235) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add236) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // -79228106389283212384222373410
  s21_decimal check = {{0x3AC4E622, 0x756BD584, 0xFFFFF41D, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add237) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add238) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // -79228162514264337543839948912
  s21_decimal check = {{0x6D692070, 0xFFFFFFF4, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add239) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add240) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // -79228162514264337592894706332
  s21_decimal check = {{0xD94D529C, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add241) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add242) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add243) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add244) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add245) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add246) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add247) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add248) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add249) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add250) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add251) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add252) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add253) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add254) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395032
  s21_decimal check = {{0x99999998, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add255) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add256) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add257) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add258) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add259) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add260) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add261) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add262) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7922816251426433759354395031.0
  s21_decimal check = {{0xFFFFFFE6, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add263) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add264) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395032.0
  s21_decimal check = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add265) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add266) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add267) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add268) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add269) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add270) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7922816245277519068117877828
  s21_decimal check = {{0x44444444, 0x44444444, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add271) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7922816257575348449159256473
  s21_decimal check = {{0x99999999, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add272) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 7922816245277519069549533593
  s21_decimal check = {{0x99999999, 0x44444444, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add273) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add274) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 7922816251426433757922739268
  s21_decimal check = {{0x44444444, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add275) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add276) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // 7922816251426433759327985645.3
  s21_decimal check = {{0xF0423F45, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add277) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add278) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add279) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add280) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759327985646
  s21_decimal check = {{0x98069FEE, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add281) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add282) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7922816251426433759354395025.1
  s21_decimal check = {{0xFFFFFFAB, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add283) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add284) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395025
  s21_decimal check = {{0x99999991, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add285) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 7922816251426433759354395037
  s21_decimal check = {{0x9999999D, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add286) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 7922816251426433759354395029.4
  s21_decimal check = {{0xFFFFFFD6, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add287) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add288) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add289) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add290) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add291) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add292) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add293) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add294) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add295) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // 7922760126445308550032818109.0
  s21_decimal check = {{0x4BB0FD62, 0x9636572A, 0xFFFF8926, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add296) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // 7922872376407558968675971957
  s21_decimal check = {{0x5ED4B375, 0x242DC415, 0x1999A57C, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add297) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // 7922816251426433709650393610.6
  s21_decimal check = {{0x461B446A, 0xFFFFFF8C, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add298) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // 7922816251426433809058396455
  s21_decimal check = {{0x2C307927, 0x999999A5, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add299) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // 7922816251426433758705151030.8
  s21_decimal check = {{0x7D053A24, 0xFFFFFFFE, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add300) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // 7922816251426433760003639035
  s21_decimal check = {{0xC04C46FB, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add301) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add302) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add303) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add304) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 2;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add305) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add306) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add307) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add308) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add309) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add310) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add311) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add312) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add313) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395032
  s21_decimal check = {{0x99999998, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add314) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add315) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add316) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add317) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add318) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add319) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add320) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add321) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -7922816251426433759354395031.0
  s21_decimal check = {{0xFFFFFFE6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add322) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add323) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7922816251426433759354395032.0
  s21_decimal check = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add324) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add325) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add326) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add327) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add328) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add329) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -7922816245277519068117877828
  s21_decimal check = {{0x44444444, 0x44444444, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add330) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add331) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -7922816245277519069549533593
  s21_decimal check = {{0x99999999, 0x44444444, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add332) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -7922816257575348449159256473
  s21_decimal check = {{0x99999999, 0xEEEEEEEE, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add333) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -7922816251426433757922739268
  s21_decimal check = {{0x44444444, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add334) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add335) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // -7922816251426433759327985645.3
  s21_decimal check = {{0xF0423F45, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add336) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // -7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add337) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add338) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add339) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -7922816251426433759327985646
  s21_decimal check = {{0x98069FEE, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add340) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add341) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7922816251426433759354395025.1
  s21_decimal check = {{0xFFFFFFAB, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add342) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add343) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395025
  s21_decimal check = {{0x99999991, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add344) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add345) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -7922816251426433759354395029.4
  s21_decimal check = {{0xFFFFFFD6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add346) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -7922816251426433759354395037
  s21_decimal check = {{0x9999999D, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add347) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add348) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add349) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add350) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add351) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add352) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add353) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add354) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add355) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x80060000}};
  // -7922872376407558968675971957
  s21_decimal check = {{0x5ED4B375, 0x242DC415, 0x1999A57C, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add356) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 56124981125209321576924.010631
  s21_decimal decimal2 = {{0xF555887, 0x553F1641, 0xB5597F0B, 0x60000}};
  // -7922760126445308550032818109.0
  s21_decimal check = {{0x4BB0FD62, 0x9636572A, 0xFFFF8926, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add357) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x80120000}};
  // -7922816251426433809058396455
  s21_decimal check = {{0x2C307927, 0x999999A5, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add358) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 49704001422.391670881925172831
  s21_decimal decimal2 = {{0x7F7B8E5F, 0x2B4271A6, 0xA09A2FB4, 0x120000}};
  // -7922816251426433709650393610.6
  s21_decimal check = {{0x461B446A, 0xFFFFFF8C, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add359) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x80140000}};
  // -7922816251426433760003639035
  s21_decimal check = {{0xC04C46FB, 0x99999999, 0x19999999, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add360) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 649244002.20841517182548587502
  s21_decimal decimal2 = {{0x122233EE, 0x5675EBE6, 0xD1C83484, 0x140000}};
  // -7922816251426433758705151030.8
  s21_decimal check = {{0x7D053A24, 0xFFFFFFFE, 0xFFFFFFFF, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add361) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add362) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add363) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 1;

  test_add_fail(decimal1, decimal2, check);
}

START_TEST(test_add364) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add365) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add366) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add367) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add368) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add369) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add370) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add371) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add372) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x80010000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add373) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add374) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add375) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add376) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add377) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add378) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add379) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add380) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add381) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add382) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7922816251426433759354395031.5
  s21_decimal check = {{0xFFFFFFEB, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add383) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add384) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add385) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add386) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add387) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add388) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x80000000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add389) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add390) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7922816245277519068117877828.5
  s21_decimal check = {{0xAAAAAAAD, 0xAAAAAAAA, 0xFFFFFFFC, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add391) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7922816257575348449159256474
  s21_decimal check = {{0x9999999A, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add392) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 7922816245277519069549533593.5
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAD, 0xFFFFFFFC, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add393) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add394) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 7922816251426433757922739268.5
  s21_decimal check = {{0xAAAAAAAD, 0xFFFFFFFC, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add395) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add396) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387.704754779197847983445
  s21_decimal decimal2 = {{0x1B755555, 0x2CE411B0, 0x55555560, 0x80150000}};
  // 7922816251426433759327985645.8
  s21_decimal check = {{0xF0423F4A, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add397) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add398) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 7922816251426433759327985646.0
  s21_decimal check = {{0xF0423F4C, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add399) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_add400) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759327985646.5
  s21_decimal check = {{0xF0423F51, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_add(decimal1, decimal2, check);
}

START_TEST(test_sub1) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub2) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub3) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub4) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub5) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub6) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub7) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub8) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub9) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub10) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub11) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub12) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub13) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub14) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub15) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub16) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub17) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub18) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub19) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub20) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub21) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub22) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub23) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub24) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub25) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 52818775009509558395695966890
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub26) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub27) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 52818775015658473085500828330
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub28) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub29) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 79228162508115422902307433130
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub30) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub31) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 79228162508115422903739088895
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub32) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub33) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 79228162514264337592112294570
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub34) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub35) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub36) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub37) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub38) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub39) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub40) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub41) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub42) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub43) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub44) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub45) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 79228162514264337593543950331
  s21_decimal check = {{0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub46) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub47) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub48) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub49) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub50) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub51) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub52) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub53) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub54) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub55) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // 79228162514264337593543949689
  s21_decimal check = {{0xFFFFFD79, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub56) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub57) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub58) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // 79228162514240090656400479551
  s21_decimal check = {{0x4AC153F, 0xFFA9DB8A, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub59) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // 18994429982494779296567793531
  s21_decimal check = {{0xB3DC177B, 0x9B738FD3, 0x3D5FD300, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub60) {
  // 79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub61) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub62) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub63) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub64) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub65) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub66) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub67) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub68) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub69) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub70) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub71) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub72) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub73) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub74) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub75) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub76) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub77) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub78) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub79) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub80) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub81) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub82) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub83) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub84) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub85) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub86) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -52818775009509558395695966890
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub87) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub88) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -52818775015658473085500828330
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xAAAAAAAA, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub89) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub90) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -79228162508115422902307433130
  s21_decimal check = {{0xAAAAAAAA, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub91) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub92) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -79228162508115422903739088895
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub93) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub94) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -79228162514264337592112294570
  s21_decimal check = {{0xAAAAAAAA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub95) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub96) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub97) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub98) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub99) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub100) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593517540948
  s21_decimal check = {{0xFE6D0654, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub101) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub102) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub103) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub104) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950327
  s21_decimal check = {{0xFFFFFFF7, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub105) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub106) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -79228162514264337593543950331
  s21_decimal check = {{0xFFFFFFFB, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub107) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub108) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub109) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub110) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub111) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub112) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub113) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub114) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub115) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub116) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // -79228162514264337593543949689
  s21_decimal check = {{0xFFFFFD79, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub117) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // -79228162514240090656400479551
  s21_decimal check = {{0x4AC153F, 0xFFA9DB8A, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub118) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub119) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub120) {
  // -79228162514264337593543950335
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // -18994429982494779296567793531
  s21_decimal check = {{0xB3DC177B, 0x9B738FD3, 0x3D5FD300, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub121) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub122) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub123) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub124) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub125) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub126) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub127) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub128) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub129) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub130) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub131) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // 71305346262837903834189555299
  s21_decimal check = {{0x66666663, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub132) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub133) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub134) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub135) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub136) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub137) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub138) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub139) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub140) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub141) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 79228162514264337593543950332
  s21_decimal check = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub142) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub143) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub144) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub145) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 52818775009509558395695966889
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub146) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub147) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 52818775015658473085500828329
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xAAAAAAAA, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub148) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub149) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 79228162508115422902307433129
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub150) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub151) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 79228162508115422903739088894
  s21_decimal check = {{0xFFFFFFFE, 0xAAAAAAAA, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub152) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub153) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 79228162514264337592112294569
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub154) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub155) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 79228162514264337593517540946
  s21_decimal check = {{0xFE6D0652, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub156) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub157) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub158) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub159) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub160) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub161) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub162) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub163) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub164) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub165) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 79228162514264337593543950330
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub166) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub167) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub168) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub169) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub170) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub171) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub172) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub173) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub174) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub175) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // 79228162514264337593543949688
  s21_decimal check = {{0xFFFFFD78, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub176) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub177) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub178) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // 79228162514240090656400479550
  s21_decimal check = {{0x4AC153E, 0xFFA9DB8A, 0xFFFFFFFF, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub179) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // 18994429982494779296567793530
  s21_decimal check = {{0xB3DC177A, 0x9B738FD3, 0x3D5FD300, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub180) {
  // 79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub181) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub182) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub183) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub184) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub185) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub186) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub187) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub188) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub189) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub190) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub191) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub192) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // -71305346262837903834189555299
  s21_decimal check = {{0x66666663, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub193) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub194) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub195) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub196) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub197) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub198) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub199) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub200) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub201) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub202) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -79228162514264337593543950332
  s21_decimal check = {{0xFFFFFFFC, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub203) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -79228162514264337593543950335
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub204) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -79228162514264337593543950333
  s21_decimal check = {{0xFFFFFFFD, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub205) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub206) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -52818775009509558395695966889
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub207) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub208) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -52818775015658473085500828329
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xAAAAAAAA, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub209) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub210) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -79228162508115422902307433129
  s21_decimal check = {{0xAAAAAAA9, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub211) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub212) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -79228162508115422903739088894
  s21_decimal check = {{0xFFFFFFFE, 0xAAAAAAAA, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub213) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub214) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -79228162514264337592112294569
  s21_decimal check = {{0xAAAAAAA9, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub215) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub216) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -79228162514264337593517540946
  s21_decimal check = {{0xFE6D0652, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub217) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub218) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub219) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub220) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593517540947
  s21_decimal check = {{0xFE6D0653, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub221) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub222) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub223) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub224) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950326
  s21_decimal check = {{0xFFFFFFF6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub225) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub226) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -79228162514264337593543950330
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub227) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub228) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub229) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub230) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub231) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub232) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub233) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub234) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -79228162514264337593543950334
  s21_decimal check = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub235) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub236) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // -79228162514264337593543949688
  s21_decimal check = {{0xFFFFFD78, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub237) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // -79228162514240090656400479550
  s21_decimal check = {{0x4AC153E, 0xFFA9DB8A, 0xFFFFFFFF, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub238) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub239) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub240) {
  // -79228162514264337593543950334
  s21_decimal decimal1 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // -18994429982494779296567793530
  s21_decimal check = {{0xB3DC177A, 0x9B738FD3, 0x3D5FD300, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub241) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub242) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub243) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub244) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub245) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub246) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub247) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub248) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub249) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub250) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub251) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub252) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub253) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395032
  s21_decimal check = {{0x99999998, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub254) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub255) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub256) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub257) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub258) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub259) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub260) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub261) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 7922816251426433759354395031.0
  s21_decimal check = {{0xFFFFFFE6, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub262) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub263) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395032.0
  s21_decimal check = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub264) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub265) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub266) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub267) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub268) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub269) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7922816245277519068117877828
  s21_decimal check = {{0x44444444, 0x44444444, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub270) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub271) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7922816245277519069549533593
  s21_decimal check = {{0x99999999, 0x44444444, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub272) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 7922816257575348449159256473
  s21_decimal check = {{0x99999999, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub273) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 7922816251426433757922739268
  s21_decimal check = {{0x44444444, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub274) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub275) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub276) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub277) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub278) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub279) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759327985646
  s21_decimal check = {{0x98069FEE, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub280) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub281) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 7922816251426433759354395025.1
  s21_decimal check = {{0xFFFFFFAB, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub282) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub283) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395025
  s21_decimal check = {{0x99999991, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub284) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub285) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // 7922816251426433759354395029.4
  s21_decimal check = {{0xFFFFFFD6, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub286) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // 7922816251426433759354395037
  s21_decimal check = {{0x9999999D, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub287) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub288) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub289) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub290) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub291) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub292) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub293) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub294) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub295) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // 7922816251426433759354394386.7
  s21_decimal check = {{0xFFFFE6BB, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub296) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // 7922816251426433759354395679
  s21_decimal check = {{0x99999C1F, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub297) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // 7922816251450680696497865817
  s21_decimal check = {{0x94ED8459, 0x99EFBE0F, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub298) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // 7922816251402186822210924249.2
  s21_decimal check = {{0x2EB8D47C, 0xFCA29364, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub299) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // -52310916280343124537621761771
  s21_decimal check = {{0xB28A4EEB, 0xCAF2D692, 0xA9069365, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub300) {
  // 7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // 68156548783195992056330551837
  s21_decimal check = {{0xE5BD821D, 0xFE2609C5, 0xDC39C698, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub301) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub302) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub303) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int check = 2;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub304) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // 71305346262837903834189555301
  s21_decimal check = {{0x66666665, 0x66666666, 0xE6666666, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub305) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // -15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub306) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub307) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub308) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub309) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub310) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 1
  s21_decimal check = {{0x1, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub311) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub312) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 2
  s21_decimal check = {{0x2, 0x0, 0x0, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub313) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub314) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395032
  s21_decimal check = {{0x99999998, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub315) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub316) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub317) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub318) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub319) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -7922816251426433759354395033.5
  s21_decimal check = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub320) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub321) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub322) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -7922816251426433759354395031.0
  s21_decimal check = {{0xFFFFFFE6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub323) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub324) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -7922816251426433759354395032.0
  s21_decimal check = {{0xFFFFFFF0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub325) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub326) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub327) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub328) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub329) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub330) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -7922816245277519068117877828
  s21_decimal check = {{0x44444444, 0x44444444, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub331) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -7922816257575348449159256473
  s21_decimal check = {{0x99999999, 0xEEEEEEEE, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub332) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // -7922816245277519069549533593
  s21_decimal check = {{0x99999999, 0x44444444, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub333) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub334) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -7922816251426433757922739268
  s21_decimal check = {{0x44444444, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub335) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // -7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub336) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub337) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub338) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -7922816251426433759327985645.5
  s21_decimal check = {{0xF0423F47, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub339) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub340) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759327985646
  s21_decimal check = {{0x98069FEE, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub341) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub342) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -7922816251426433759354395025.1
  s21_decimal check = {{0xFFFFFFAB, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub343) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395041
  s21_decimal check = {{0x999999A1, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub344) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395025
  s21_decimal check = {{0x99999991, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub345) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x100000}};
  // -7922816251426433759354395037
  s21_decimal check = {{0x9999999D, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub346) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -3.6336660283201536
  s21_decimal decimal2 = {{0x811800, 0x811800, 0x0, 0x80100000}};
  // -7922816251426433759354395029.4
  s21_decimal check = {{0xFFFFFFD6, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub347) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // -7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub348) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // -7922816251426433759354395033
  s21_decimal check = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub349) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub350) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub351) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub352) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub353) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub354) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub355) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x1A0000}};
  // -7922816251426433759354395679
  s21_decimal check = {{0x99999C1F, 0x99999999, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub356) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -646.33673839575124685661598885
  s21_decimal decimal2 = {{0xB2C6F4A5, 0xA11CA39F, 0xD0D7B8CF, 0x801A0000}};
  // -7922816251426433759354394386.7
  s21_decimal check = {{0xFFFFE6BB, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub357) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0x800B0000}};
  // -7922816251402186822210924249.2
  s21_decimal check = {{0x2EB8D47C, 0xFCA29364, 0xFFFFFFFF, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub358) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 24246937143470783.81744120110
  s21_decimal decimal2 = {{0x11B612E, 0xA2A675B4, 0x7D5A8DD, 0xB0000}};
  // -7922816251450680696497865817
  s21_decimal check = {{0x94ED8459, 0x99EFBE0F, 0x19999999, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub359) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x0}};
  // -68156548783195992056330551837
  s21_decimal check = {{0xE5BD821D, 0xFE2609C5, 0xDC39C698, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub360) {
  // -7922816251426433759354395033
  s21_decimal decimal1 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // -60233732531769558296976156804
  s21_decimal decimal2 = {{0x4C23E884, 0x648C702C, 0xC2A02CFF, 0x80000000}};
  // 52310916280343124537621761771
  s21_decimal check = {{0xB28A4EEB, 0xCAF2D692, 0xA9069365, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub361) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -71305346262837903834189555302
  s21_decimal check = {{0x66666666, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub362) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub363) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // -71305346262837903834189555300
  s21_decimal check = {{0x66666664, 0x66666666, 0xE6666666, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub364) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -79228162514264337593543950334
  s21_decimal decimal2 = {{0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int check = 1;

  test_sub_fail(decimal1, decimal2, check);
}

START_TEST(test_sub365) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x0}};
  // 0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub366) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033
  s21_decimal decimal2 = {{0x99999999, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790066
  s21_decimal check = {{0x33333332, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub367) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.0
  s21_decimal check = {{0x0, 0x0, 0x0, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub368) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395033.5
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  // 15845632502852867518708790067
  s21_decimal check = {{0x33333333, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub369) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};
  // -0.5
  s21_decimal check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub370) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub371) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};
  // -1.5
  s21_decimal check = {{0xF, 0x0, 0x0, 0x80010000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub372) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -7922816251426433759354395035
  s21_decimal decimal2 = {{0x9999999B, 0x99999999, 0x19999999, 0x80000000}};
  // 15845632502852867518708790068
  s21_decimal check = {{0x33333334, 0x33333333, 0x33333333, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub373) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub374) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub375) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub376) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub377) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub378) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub379) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 7922816251426433759354395033.0
  s21_decimal check = {{0xFFFFFFFA, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub380) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 7922816251426433759354395034
  s21_decimal check = {{0x9999999A, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub381) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 7922816251426433759354395031.5
  s21_decimal check = {{0xFFFFFFEB, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub382) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub383) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 7922816251426433759354395032.5
  s21_decimal check = {{0xFFFFFFF5, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub384) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 7922816251426433759354395035
  s21_decimal check = {{0x9999999B, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub385) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -18486571253328345438493588412
  s21_decimal check = {{0xBBBBBBBC, 0xBBBBBBBB, 0x3BBBBBBB, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub386) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 34332203756181212957202378478
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x6EEEEEEE, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub387) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -18486571247179430748688726972
  s21_decimal check = {{0xBBBBBBBC, 0x66666666, 0x3BBBBBBB, 0x80000000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub388) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 34332203750032298267397517038
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x6EEEEEEE, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub389) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7922816245277519068117877828.5
  s21_decimal check = {{0xAAAAAAAD, 0xAAAAAAAA, 0xFFFFFFFC, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub390) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7922816257575348450590912238
  s21_decimal check = {{0xEEEEEEEE, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub391) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7922816245277519069549533593.5
  s21_decimal check = {{0xFFFFFFFF, 0xAAAAAAAD, 0xFFFFFFFC, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub392) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // 7922816257575348449159256474
  s21_decimal check = {{0x9999999A, 0xEEEEEEEE, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub393) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 7922816251426433757922739268.5
  s21_decimal check = {{0xAAAAAAAD, 0xFFFFFFFC, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub394) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 7922816251426433760786050798
  s21_decimal check = {{0xEEEEEEEE, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub395) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 7922816251426433759327985646.0
  s21_decimal check = {{0xF0423F4C, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub396) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub397) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 7922816251426433759327985646.0
  s21_decimal check = {{0xF0423F4C, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub398) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 7922816251426433759380804421
  s21_decimal check = {{0x9B2C9345, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub399) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 7922816251426433759327985646.5
  s21_decimal check = {{0xF0423F51, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_sub400) {
  // 7922816251426433759354395033.5
  s21_decimal decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 7922816251426433759380804420
  s21_decimal check = {{0x9B2C9344, 0x99999999, 0x19999999, 0x0}};

  test_sub(decimal1, decimal2, check);
}

START_TEST(test_mul1) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul2) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul3) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul4) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul5) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul6) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul7) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul8) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul9) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul10) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul11) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul12) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul13) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul14) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul15) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul16) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul17) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul18) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -52818775009509558395695964249
  s21_decimal decimal_check = {
      {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul19) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul20) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul21) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul22) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul23) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991720
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul24) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul25) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693752377389598923991725
  s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul26) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693752377389598923991725
  s21_decimal decimal_check = {
      {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul27) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983448
  s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul28) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387504754779197847983448
  s21_decimal decimal_check = {
      {0x55555558, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul29) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul30) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul31) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387504754779197847983442
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul32) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387504754779197847983442
  s21_decimal decimal_check = {
      {0x55555552, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul33) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul34) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul35) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul36) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul37) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul38) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul39) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul40) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul41) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 66023468761886.947994619958612
  s21_decimal decimal_check = {{0x55555554, 0x55555555, 0xD5555555, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul42) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -66023468761886.947994619958612
  s21_decimal decimal_check = {
      {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul43) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 13204693752377.389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul44) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -13204693752377.389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul45) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul46) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul47) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul48) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul49) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 2.6409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul50) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -2.6409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul51) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 26.409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul52) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -26.409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul53) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul54) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul55) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul56) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul57) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul58) {
  // 26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul59) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul60) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul61) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul62) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul63) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul64) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul65) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul66) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul67) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul68) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul69) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul70) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul71) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul72) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul73) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul74) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul75) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -52818775009509558395695964249
  s21_decimal decimal_check = {
      {0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul76) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 52818775009509558395695964249
  s21_decimal decimal_check = {{0xAAAAA059, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul77) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul78) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul79) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -13204693752377389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul80) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 13204693752377389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul81) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693752377389598923991720
  s21_decimal decimal_check = {
      {0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul82) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693752377389598923991720
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul83) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693752377389598923991725
  s21_decimal decimal_check = {
      {0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul84) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693752377389598923991725
  s21_decimal decimal_check = {{0xAAAAAAAD, 0xAAAAAAAA, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul85) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387504754779197847983448
  s21_decimal decimal_check = {
      {0x55555558, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul86) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387504754779197847983448
  s21_decimal decimal_check = {{0x55555558, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul87) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul88) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul89) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387504754779197847983442
  s21_decimal decimal_check = {
      {0x55555552, 0x55555555, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul90) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387504754779197847983442
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul91) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul92) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul93) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul94) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul95) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -20923672451288935879452631411
  s21_decimal decimal_check = {
      {0xADCFA173, 0x67336914, 0x439BA7FC, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul96) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 20923672451288935879452631411
  s21_decimal decimal_check = {{0xADCFA173, 0x67336914, 0x439BA7FC, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul97) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul98) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul99) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -66023468761886.947994619958612
  s21_decimal decimal_check = {
      {0x55555554, 0x55555555, 0xD5555555, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul100) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 66023468761886.947994619958612
  s21_decimal decimal_check = {{0x55555554, 0x55555555, 0xD5555555, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul101) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // -13204693752377.389598923991722
  s21_decimal decimal_check = {
      {0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul102) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 13204693752377.389598923991722
  s21_decimal decimal_check = {{0xAAAAAAAA, 0xAAAAAAAA, 0x2AAAAAAA, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul103) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul104) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul105) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul106) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul107) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -2.6409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul108) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 2.6409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul109) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -26.409387504754779197847983445
  s21_decimal decimal_check = {
      {0x55555555, 0x55555555, 0x55555555, 0x801B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul110) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 26.409387504754779197847983445
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x55555555, 0x1B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul111) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul112) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul113) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul114) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul115) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul116) {
  // -26409387504754779197847983445
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul117) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul118) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul119) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul120) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul121) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul122) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul123) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul124) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul125) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul126) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul127) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul128) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul129) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul130) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul131) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul132) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul133) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 52818774997211729016086241369
  s21_decimal decimal_check = {{0xAAAAA059, 0x0, 0xAAAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul134) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -52818774997211729016086241369
  s21_decimal decimal_check = {{0xAAAAA059, 0x0, 0xAAAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul135) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul136) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul137) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 13204693749302932254021561002
  s21_decimal decimal_check = {{0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul138) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -13204693749302932254021561002
  s21_decimal decimal_check = {
      {0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul139) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693749302932254021561000
  s21_decimal decimal_check = {{0x2AAAAAA8, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul140) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693749302932254021561000
  s21_decimal decimal_check = {
      {0x2AAAAAA8, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul141) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 13204693749302932254021561005
  s21_decimal decimal_check = {{0x2AAAAAAD, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul142) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -13204693749302932254021561005
  s21_decimal decimal_check = {
      {0x2AAAAAAD, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul143) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387498605864508043122008
  s21_decimal decimal_check = {{0x55555558, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul144) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387498605864508043122008
  s21_decimal decimal_check = {{0x55555558, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul145) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul146) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul147) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 26409387498605864508043122002
  s21_decimal decimal_check = {{0x55555552, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul148) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -26409387498605864508043122002
  s21_decimal decimal_check = {{0x55555552, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul149) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul150) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul151) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul152) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul153) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 20923672446417263756150562907
  s21_decimal decimal_check = {{0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul154) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -20923672446417263756150562907
  s21_decimal decimal_check = {
      {0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul155) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul156) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul157) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 66023468746514.661270107805012
  s21_decimal decimal_check = {{0xD5555554, 0x80000000, 0xD5555554, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul158) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -66023468746514.661270107805012
  s21_decimal decimal_check = {
      {0xD5555554, 0x80000000, 0xD5555554, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul159) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 13204693749302.932254021561002
  s21_decimal decimal_check = {{0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul160) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -13204693749302.932254021561002
  s21_decimal decimal_check = {
      {0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul161) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul162) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul163) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul164) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul165) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 2.6409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul166) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -2.6409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul167) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 26.409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x1B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul168) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -26.409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x801B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul169) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul170) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul171) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul172) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul173) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul174) {
  // 26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul175) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul176) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul177) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul178) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul179) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul180) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul181) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul182) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul183) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul184) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul185) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul186) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul187) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul188) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul189) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul190) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul191) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -52818774997211729016086241369
  s21_decimal decimal_check = {{0xAAAAA059, 0x0, 0xAAAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul192) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 52818774997211729016086241369
  s21_decimal decimal_check = {{0xAAAAA059, 0x0, 0xAAAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul193) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul194) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul195) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -13204693749302932254021561002
  s21_decimal decimal_check = {
      {0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul196) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 13204693749302932254021561002
  s21_decimal decimal_check = {{0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul197) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693749302932254021561000
  s21_decimal decimal_check = {
      {0x2AAAAAA8, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul198) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693749302932254021561000
  s21_decimal decimal_check = {{0x2AAAAAA8, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul199) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -13204693749302932254021561005
  s21_decimal decimal_check = {
      {0x2AAAAAAD, 0x80000000, 0x2AAAAAAA, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul200) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 13204693749302932254021561005
  s21_decimal decimal_check = {{0x2AAAAAAD, 0x80000000, 0x2AAAAAAA, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul201) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387498605864508043122008
  s21_decimal decimal_check = {{0x55555558, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul202) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387498605864508043122008
  s21_decimal decimal_check = {{0x55555558, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul203) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul204) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul205) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -26409387498605864508043122002
  s21_decimal decimal_check = {{0x55555552, 0x0, 0x55555555, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul206) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 26409387498605864508043122002
  s21_decimal decimal_check = {{0x55555552, 0x0, 0x55555555, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul207) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul208) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul209) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul210) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul211) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -20923672446417263756150562907
  s21_decimal decimal_check = {
      {0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul212) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 20923672446417263756150562907
  s21_decimal decimal_check = {{0x8A37E05B, 0x2397C118, 0x439BA7FC, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul213) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul214) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul215) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -66023468746514.661270107805012
  s21_decimal decimal_check = {
      {0xD5555554, 0x80000000, 0xD5555554, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul216) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 66023468746514.661270107805012
  s21_decimal decimal_check = {{0xD5555554, 0x80000000, 0xD5555554, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul217) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // -13204693749302.932254021561002
  s21_decimal decimal_check = {
      {0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0x800F0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul218) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 13204693749302.932254021561002
  s21_decimal decimal_check = {{0x2AAAAAAA, 0x80000000, 0x2AAAAAAA, 0xF0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul219) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul220) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul221) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul222) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul223) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -2.6409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul224) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 2.6409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul225) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -26.409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x801B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul226) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 26.409387498605864508043122005
  s21_decimal decimal_check = {{0x55555555, 0x0, 0x55555555, 0x1B0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul227) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul228) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul229) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul230) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul231) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul232) {
  // -26409387498605864508043122005
  s21_decimal decimal1 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul233) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul234) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul235) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul236) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul237) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul238) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul239) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul240) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul241) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 8803129166201954835059936825
  s21_decimal decimal_check = {{0x38E38E39, 0x55555555, 0x1C71C71C, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul242) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -8803129166201954835059936825
  s21_decimal decimal_check = {
      {0x38E38E39, 0x55555555, 0x1C71C71C, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul243) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 162389070814544768680495185.58
  s21_decimal decimal_check = {{0x9C3D3FDE, 0xD33DA3EB, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul244) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -162389070814544768680495185.58
  s21_decimal decimal_check = {
      {0x9C3D3FDE, 0xD33DA3EB, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul245) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 162389070776735616809194041.03
  s21_decimal decimal_check = {{0xFD781E47, 0x9EC52196, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul246) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -162389070776735616809194041.03
  s21_decimal decimal_check = {
      {0xFD781E47, 0x9EC52196, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul247) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 162389067710850691399003335
  s21_decimal decimal_check = {{0xFF79ACC7, 0xFFFFFFFF, 0x865338, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul248) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -162389067710850691399003335
  s21_decimal decimal_check = {{0xFF79ACC7, 0xFFFFFFFF, 0x865338, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul249) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 12297829382473034409.999999385
  s21_decimal decimal_check = {{0x82EE2199, 0xAAAAAAAA, 0x27BC86AA, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul250) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -12297829382473034409.999999385
  s21_decimal decimal_check = {
      {0x82EE2199, 0xAAAAAAAA, 0x27BC86AA, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul251) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul252) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul253) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 3074457345618258602.5
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x10000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul254) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -3074457345618258602.5
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x80010000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul255) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 3074457345618258602.4999999994
  s21_decimal decimal_check = {{0x475359FA, 0xAAAAAAAA, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul256) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -3074457345618258602.4999999994
  s21_decimal decimal_check = {
      {0x475359FA, 0xAAAAAAAA, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul257) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 3074457345618258602.5000000006
  s21_decimal decimal_check = {{0x47535A06, 0xAAAAAAAA, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul258) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -3074457345618258602.5000000006
  s21_decimal decimal_check = {
      {0x47535A06, 0xAAAAAAAA, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul259) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914691236517205.0000000006
  s21_decimal decimal_check = {{0x8EA6B406, 0x55555554, 0xC6AEA155, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul260) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -6148914691236517205.0000000006
  s21_decimal decimal_check = {
      {0x8EA6B406, 0x55555554, 0xC6AEA155, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul261) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 49191317529892137640
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul262) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -49191317529892137640
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul263) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914691236517204.9999999994
  s21_decimal decimal_check = {{0x8EA6B3FA, 0x55555554, 0xC6AEA155, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul264) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -6148914691236517204.9999999994
  s21_decimal decimal_check = {
      {0x8EA6B3FA, 0x55555554, 0xC6AEA155, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul265) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul266) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul267) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 48716721244363430604.148555673
  s21_decimal decimal_check = {{0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul268) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -48716721244363430604.148555673
  s21_decimal decimal_check = {
      {0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul269) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 4871672124436343060.4148555676
  s21_decimal decimal_check = {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul270) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -4871672124436343060.4148555676
  s21_decimal decimal_check = {
      {0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul271) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul272) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul273) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 15372.2867280912930125
  s21_decimal decimal_check = {{0x5555554D, 0x55555555, 0x8, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul274) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -15372.2867280912930125
  s21_decimal decimal_check = {{0x5555554D, 0x55555555, 0x8, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul275) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 3074.4573456182586025
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul276) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -3074.4573456182586025
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul277) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul278) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul279) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul280) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul281) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000006148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul282) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000006148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul283) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.0000000061489146912365172050
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x3, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul284) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -0.0000000061489146912365172050
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x3, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul285) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul286) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul287) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul288) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul289) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // -43385638798924061271577.476380
  s21_decimal decimal_check = {{0x588A3D1C, 0x5F33F93, 0x8C2FC260, 0x80060000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul290) {
  // 6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // 43385638798924061271577.476380
  s21_decimal decimal_check = {{0x588A3D1C, 0x5F33F93, 0x8C2FC260, 0x60000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul291) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul292) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul293) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul294) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul295) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul296) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul297) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul298) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul299) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // -8803129166201954835059936825
  s21_decimal decimal_check = {
      {0x38E38E39, 0x55555555, 0x1C71C71C, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul300) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // 8803129166201954835059936825
  s21_decimal decimal_check = {{0x38E38E39, 0x55555555, 0x1C71C71C, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul301) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // -162389070814544768680495185.58
  s21_decimal decimal_check = {
      {0x9C3D3FDE, 0xD33DA3EB, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul302) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // 162389070814544768680495185.58
  s21_decimal decimal_check = {{0x9C3D3FDE, 0xD33DA3EB, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul303) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // -162389070776735616809194041.03
  s21_decimal decimal_check = {
      {0xFD781E47, 0x9EC52196, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul304) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // 162389070776735616809194041.03
  s21_decimal decimal_check = {{0xFD781E47, 0x9EC52196, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul305) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // -162389067710850691399003335
  s21_decimal decimal_check = {{0xFF79ACC7, 0xFFFFFFFF, 0x865338, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul306) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // 162389067710850691399003335
  s21_decimal decimal_check = {{0xFF79ACC7, 0xFFFFFFFF, 0x865338, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul307) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // -12297829382473034409.999999385
  s21_decimal decimal_check = {
      {0x82EE2199, 0xAAAAAAAA, 0x27BC86AA, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul308) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // 12297829382473034409.999999385
  s21_decimal decimal_check = {{0x82EE2199, 0xAAAAAAAA, 0x27BC86AA, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul309) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // -6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul310) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // 6148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul311) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // -3074457345618258602.5
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x80010000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul312) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // 3074457345618258602.5
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x10000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul313) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3074457345618258602.4999999994
  s21_decimal decimal_check = {
      {0x475359FA, 0xAAAAAAAA, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul314) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 3074457345618258602.4999999994
  s21_decimal decimal_check = {{0x475359FA, 0xAAAAAAAA, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul315) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // -3074457345618258602.5000000006
  s21_decimal decimal_check = {
      {0x47535A06, 0xAAAAAAAA, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul316) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // 3074457345618258602.5000000006
  s21_decimal decimal_check = {{0x47535A06, 0xAAAAAAAA, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul317) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -6148914691236517205.0000000006
  s21_decimal decimal_check = {
      {0x8EA6B406, 0x55555554, 0xC6AEA155, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul318) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 6148914691236517205.0000000006
  s21_decimal decimal_check = {{0x8EA6B406, 0x55555554, 0xC6AEA155, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul319) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // -49191317529892137640
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul320) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // 49191317529892137640
  s21_decimal decimal_check = {{0xAAAAAAA8, 0xAAAAAAAA, 0x2, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul321) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // -6148914691236517204.9999999994
  s21_decimal decimal_check = {
      {0x8EA6B3FA, 0x55555554, 0xC6AEA155, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul322) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // 6148914691236517204.9999999994
  s21_decimal decimal_check = {{0x8EA6B3FA, 0x55555554, 0xC6AEA155, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul323) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul324) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul325) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // -48716721244363430604.148555673
  s21_decimal decimal_check = {
      {0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul326) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // 48716721244363430604.148555673
  s21_decimal decimal_check = {{0xD4B7BF99, 0x79B8EBC2, 0x9D6986FE, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul327) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // -4871672124436343060.4148555676
  s21_decimal decimal_check = {
      {0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul328) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // 4871672124436343060.4148555676
  s21_decimal decimal_check = {{0xD4B7BF9C, 0x79B8EBC2, 0x9D6986FE, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul329) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul330) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul331) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // -15372.2867280912930125
  s21_decimal decimal_check = {{0x5555554D, 0x55555555, 0x8, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul332) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // 15372.2867280912930125
  s21_decimal decimal_check = {{0x5555554D, 0x55555555, 0x8, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul333) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // -3074.4573456182586025
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul334) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // 3074.4573456182586025
  s21_decimal decimal_check = {{0xAAAAAAA9, 0xAAAAAAAA, 0x1, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul335) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul336) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul337) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul338) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul339) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // -0.0000000006148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul340) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // 0.0000000006148914691236517205
  s21_decimal decimal_check = {{0x55555555, 0x55555555, 0x0, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul341) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // -0.0000000061489146912365172050
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x3, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul342) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // 0.0000000061489146912365172050
  s21_decimal decimal_check = {{0x55555552, 0x55555555, 0x3, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul343) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0xE0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul344) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -400435217312910.10886274103770
  s21_decimal decimal2 = {{0x4F4FB9DA, 0xC076B0FB, 0x8163398E, 0x800E0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul345) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x80090000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul346) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 57476540395758265626.742442133
  s21_decimal decimal2 = {{0xD42B4895, 0x339BF28D, 0xB9B77ADA, 0x90000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul347) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // -7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x80180000}};
  // 43385638798924061271577.476380
  s21_decimal decimal_check = {{0x588A3D1C, 0x5F33F93, 0x8C2FC260, 0x60000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul348) {
  // -6148914691236517205
  s21_decimal decimal1 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // 7055.820576069728775806815669
  s21_decimal decimal2 = {{0x69168DB5, 0xDCB4F4B1, 0x16CC701F, 0x180000}};
  // -43385638798924061271577.476380
  s21_decimal decimal_check = {{0x588A3D1C, 0x5F33F93, 0x8C2FC260, 0x80060000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul349) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul350) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -26409387504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul351) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul352) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -26409387498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul353) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul354) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -6148914691236517205
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul355) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul356) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -6148914689804861440
  s21_decimal decimal2 = {{0x0, 0x55555555, 0x0, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul357) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x0}};
  // 8803129164152316605602201600
  s21_decimal decimal_check = {{0x0, 0x38E38E39, 0x1C71C71C, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul358) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1431655765
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x0, 0x80000000}};
  // -8803129164152316605602201600
  s21_decimal decimal_check = {{0x0, 0x38E38E39, 0x1C71C71C, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul359) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x150000}};
  // 162389070776735616809194041.03
  s21_decimal decimal_check = {{0xFD781E47, 0x9EC52196, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul360) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -26409387.504754779197847983445
  s21_decimal decimal2 = {{0x55555555, 0x55555555, 0x55555555, 0x80150000}};
  // -162389070776735616809194041.03
  s21_decimal decimal_check = {
      {0xFD781E47, 0x9EC52196, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul361) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x150000}};
  // 162389070738926464946696025.64
  s21_decimal decimal_check = {{0x932B7F04, 0x6A4C9F42, 0x34788254, 0x20000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul362) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -26409387.498605864508043122005
  s21_decimal decimal2 = {{0x55555555, 0x0, 0x55555555, 0x80150000}};
  // -162389070738926464946696025.64
  s21_decimal decimal_check = {
      {0x932B7F04, 0x6A4C9F42, 0x34788254, 0x80020000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul363) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x0}};
  // 162389067673041540250337280
  s21_decimal decimal_check = {{0x0, 0xFF79ACC7, 0x865338, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul364) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -26409387
  s21_decimal decimal2 = {{0x192F9AB, 0x0, 0x0, 0x80000000}};
  // -162389067673041540250337280
  s21_decimal decimal_check = {{0x0, 0xFF79ACC7, 0x865338, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul365) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x1C0000}};
  // 12297829379609722879.999999385
  s21_decimal decimal_check = {{0xFFFFFD99, 0x82EE23FF, 0x27BC86AA, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul366) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1.9999999999999999999999999000
  s21_decimal decimal2 = {{0x1FFFFC18, 0x7C4A04C2, 0x409F9CBC, 0x801C0000}};
  // -12297829379609722879.999999385
  s21_decimal decimal_check = {
      {0xFFFFFD99, 0x82EE23FF, 0x27BC86AA, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul367) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x0}};
  // 6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul368) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x80000000}};
  // -6148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul369) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x10000}};
  // 3074457344902430720.0
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA9, 0x1, 0x10000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul370) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.5
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80010000}};
  // -3074457344902430720.0
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA9, 0x1, 0x80010000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul371) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 3074457344902430719.9999999994
  s21_decimal decimal_check = {{0xFFFFFFFA, 0x475359FF, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul372) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.4999999999999999999999999999
  s21_decimal decimal2 = {{0x87FFFFFF, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -3074457344902430719.9999999994
  s21_decimal decimal_check = {
      {0xFFFFFFFA, 0x475359FF, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul373) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x1C0000}};
  // 3074457344902430720.0000000006
  s21_decimal decimal_check = {{0x6, 0x47535A00, 0x635750AA, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul374) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.5000000000000000000000000001
  s21_decimal decimal2 = {{0x88000001, 0x1F128130, 0x1027E72F, 0x801C0000}};
  // -3074457344902430720.0000000006
  s21_decimal decimal_check = {{0x6, 0x47535A00, 0x635750AA, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul375) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914689804861440.0000000006
  s21_decimal decimal_check = {{0x6, 0x8EA6B400, 0xC6AEA154, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul376) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -1.0000000000000000000000000001
  s21_decimal decimal2 = {{0x10000001, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -6148914689804861440.0000000006
  s21_decimal decimal_check = {{0x6, 0x8EA6B400, 0xC6AEA154, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul377) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x0}};
  // 49191317518438891520
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA8, 0x2, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul378) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -8
  s21_decimal decimal2 = {{0x8, 0x0, 0x0, 0x80000000}};
  // -49191317518438891520
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA8, 0x2, 0x80000000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul379) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 6148914689804861439.9999999994
  s21_decimal decimal_check = {{0xFFFFFFFA, 0x8EA6B3FF, 0xC6AEA154, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul380) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.9999999999999999999999999999
  s21_decimal decimal2 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x801C0000}};
  // -6148914689804861439.9999999994
  s21_decimal decimal_check = {
      {0xFFFFFFFA, 0x8EA6B3FF, 0xC6AEA154, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul381) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul382) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -79228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul383) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  // 48716721233020685042.758212308
  s21_decimal decimal_check = {{0xF8685AD4, 0xDC4F64C4, 0x9D6986FD, 0x90000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul384) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -7.9228162514264337593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  // -48716721233020685042.758212308
  s21_decimal decimal_check = {
      {0xF8685AD4, 0xDC4F64C4, 0x9D6986FD, 0x80090000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul385) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x1C0000}};
  // 4871672123302068504.2758212311
  s21_decimal decimal_check = {{0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0xA0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul386) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.7922816251426433759354395034
  s21_decimal decimal2 = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  // -4871672123302068504.2758212311
  s21_decimal decimal_check = {
      {0xF8685AD7, 0xDC4F64C4, 0x9D6986FD, 0x800A0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul387) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  // overflow
  int code_check = 1;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul388) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -792281625142643.37593543950335
  s21_decimal decimal2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  // overflow
  int code_check = 2;

  test_mul_fail1(decimal1, decimal2, code_check);
}

START_TEST(test_mul389) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 15372.2867245121536000
  s21_decimal decimal_check = {{0x0, 0x5555554D, 0x8, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul390) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x80100000}};
  // -15372.2867245121536000
  s21_decimal decimal_check = {{0x0, 0x5555554D, 0x8, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul391) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x100000}};
  // 3074.4573449024307200
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA9, 0x1, 0x100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul392) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000005
  s21_decimal decimal2 = {{0x5, 0x0, 0x0, 0x80100000}};
  // -3074.4573449024307200
  s21_decimal decimal_check = {{0x0, 0xAAAAAAA9, 0x1, 0x80100000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul393) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x80000000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul394) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x0}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul395) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x801C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul396) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000000
  s21_decimal decimal2 = {{0x0, 0x0, 0x0, 0x1C0000}};
  // 0
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul397) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x1C0000}};
  // 0.0000000006148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul398) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000001
  s21_decimal decimal2 = {{0x1, 0x0, 0x0, 0x801C0000}};
  // -0.0000000006148914689804861440
  s21_decimal decimal_check = {{0x0, 0x55555555, 0x0, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul399) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // 0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x1C0000}};
  // 0.0000000061489146898048614400
  s21_decimal decimal_check = {{0x0, 0x55555552, 0x3, 0x1C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

START_TEST(test_mul400) {
  // 6148914689804861440
  s21_decimal decimal1 = {{0x0, 0x55555555, 0x0, 0x0}};
  // -0.0000000000000000000000000010
  s21_decimal decimal2 = {{0xA, 0x0, 0x0, 0x801C0000}};
  // -0.0000000061489146898048614400
  s21_decimal decimal_check = {{0x0, 0x55555552, 0x3, 0x801C0000}};

  test_mul(decimal1, decimal2, decimal_check);
}

Suite *sub_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("sub");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sub1);
  tcase_add_test(tc_core, test_sub2);
  tcase_add_test(tc_core, test_sub3);
  tcase_add_test(tc_core, test_sub4);
  tcase_add_test(tc_core, test_sub5);
  tcase_add_test(tc_core, test_sub6);
  tcase_add_test(tc_core, test_sub7);
  tcase_add_test(tc_core, test_sub8);
  tcase_add_test(tc_core, test_sub9);
  tcase_add_test(tc_core, test_sub10);
  tcase_add_test(tc_core, test_sub11);
  tcase_add_test(tc_core, test_sub12);
  tcase_add_test(tc_core, test_sub13);
  tcase_add_test(tc_core, test_sub14);
  tcase_add_test(tc_core, test_sub15);
  tcase_add_test(tc_core, test_sub16);
  tcase_add_test(tc_core, test_sub17);
  tcase_add_test(tc_core, test_sub18);
  tcase_add_test(tc_core, test_sub19);
  tcase_add_test(tc_core, test_sub20);
  tcase_add_test(tc_core, test_sub21);
  tcase_add_test(tc_core, test_sub22);
  tcase_add_test(tc_core, test_sub23);
  tcase_add_test(tc_core, test_sub24);
  tcase_add_test(tc_core, test_sub25);
  tcase_add_test(tc_core, test_sub26);
  tcase_add_test(tc_core, test_sub27);
  tcase_add_test(tc_core, test_sub28);
  tcase_add_test(tc_core, test_sub29);
  tcase_add_test(tc_core, test_sub30);
  tcase_add_test(tc_core, test_sub31);
  tcase_add_test(tc_core, test_sub32);
  tcase_add_test(tc_core, test_sub33);
  tcase_add_test(tc_core, test_sub34);
  tcase_add_test(tc_core, test_sub35);
  tcase_add_test(tc_core, test_sub36);
  tcase_add_test(tc_core, test_sub37);
  tcase_add_test(tc_core, test_sub38);
  tcase_add_test(tc_core, test_sub39);
  tcase_add_test(tc_core, test_sub40);
  tcase_add_test(tc_core, test_sub41);
  tcase_add_test(tc_core, test_sub42);
  tcase_add_test(tc_core, test_sub43);
  tcase_add_test(tc_core, test_sub44);
  tcase_add_test(tc_core, test_sub45);
  tcase_add_test(tc_core, test_sub46);
  tcase_add_test(tc_core, test_sub47);
  tcase_add_test(tc_core, test_sub48);
  tcase_add_test(tc_core, test_sub49);
  tcase_add_test(tc_core, test_sub50);
  tcase_add_test(tc_core, test_sub51);
  tcase_add_test(tc_core, test_sub52);
  tcase_add_test(tc_core, test_sub53);
  tcase_add_test(tc_core, test_sub54);
  tcase_add_test(tc_core, test_sub55);
  tcase_add_test(tc_core, test_sub56);
  tcase_add_test(tc_core, test_sub57);
  tcase_add_test(tc_core, test_sub58);
  tcase_add_test(tc_core, test_sub59);
  tcase_add_test(tc_core, test_sub60);
  tcase_add_test(tc_core, test_sub61);
  tcase_add_test(tc_core, test_sub62);
  tcase_add_test(tc_core, test_sub63);
  tcase_add_test(tc_core, test_sub64);
  tcase_add_test(tc_core, test_sub65);
  tcase_add_test(tc_core, test_sub66);
  tcase_add_test(tc_core, test_sub67);
  tcase_add_test(tc_core, test_sub68);
  tcase_add_test(tc_core, test_sub69);
  tcase_add_test(tc_core, test_sub70);
  tcase_add_test(tc_core, test_sub71);
  tcase_add_test(tc_core, test_sub72);
  tcase_add_test(tc_core, test_sub73);
  tcase_add_test(tc_core, test_sub74);
  tcase_add_test(tc_core, test_sub75);
  tcase_add_test(tc_core, test_sub76);
  tcase_add_test(tc_core, test_sub77);
  tcase_add_test(tc_core, test_sub78);
  tcase_add_test(tc_core, test_sub79);
  tcase_add_test(tc_core, test_sub80);
  tcase_add_test(tc_core, test_sub81);
  tcase_add_test(tc_core, test_sub82);
  tcase_add_test(tc_core, test_sub83);
  tcase_add_test(tc_core, test_sub84);
  tcase_add_test(tc_core, test_sub85);
  tcase_add_test(tc_core, test_sub86);
  tcase_add_test(tc_core, test_sub87);
  tcase_add_test(tc_core, test_sub88);
  tcase_add_test(tc_core, test_sub89);
  tcase_add_test(tc_core, test_sub90);
  tcase_add_test(tc_core, test_sub91);
  tcase_add_test(tc_core, test_sub92);
  tcase_add_test(tc_core, test_sub93);
  tcase_add_test(tc_core, test_sub94);
  tcase_add_test(tc_core, test_sub95);
  tcase_add_test(tc_core, test_sub96);
  tcase_add_test(tc_core, test_sub97);
  tcase_add_test(tc_core, test_sub98);
  tcase_add_test(tc_core, test_sub99);
  tcase_add_test(tc_core, test_sub100);
  tcase_add_test(tc_core, test_sub101);
  tcase_add_test(tc_core, test_sub102);
  tcase_add_test(tc_core, test_sub103);
  tcase_add_test(tc_core, test_sub104);
  tcase_add_test(tc_core, test_sub105);
  tcase_add_test(tc_core, test_sub106);
  tcase_add_test(tc_core, test_sub107);
  tcase_add_test(tc_core, test_sub108);
  tcase_add_test(tc_core, test_sub109);
  tcase_add_test(tc_core, test_sub110);
  tcase_add_test(tc_core, test_sub111);
  tcase_add_test(tc_core, test_sub112);
  tcase_add_test(tc_core, test_sub113);
  tcase_add_test(tc_core, test_sub114);
  tcase_add_test(tc_core, test_sub115);
  tcase_add_test(tc_core, test_sub116);
  tcase_add_test(tc_core, test_sub117);
  tcase_add_test(tc_core, test_sub118);
  tcase_add_test(tc_core, test_sub119);
  tcase_add_test(tc_core, test_sub120);
  tcase_add_test(tc_core, test_sub121);
  tcase_add_test(tc_core, test_sub122);
  tcase_add_test(tc_core, test_sub123);
  tcase_add_test(tc_core, test_sub124);
  tcase_add_test(tc_core, test_sub125);
  tcase_add_test(tc_core, test_sub126);
  tcase_add_test(tc_core, test_sub127);
  tcase_add_test(tc_core, test_sub128);
  tcase_add_test(tc_core, test_sub129);
  tcase_add_test(tc_core, test_sub130);
  tcase_add_test(tc_core, test_sub131);
  tcase_add_test(tc_core, test_sub132);
  tcase_add_test(tc_core, test_sub133);
  tcase_add_test(tc_core, test_sub134);
  tcase_add_test(tc_core, test_sub135);
  tcase_add_test(tc_core, test_sub136);
  tcase_add_test(tc_core, test_sub137);
  tcase_add_test(tc_core, test_sub138);
  tcase_add_test(tc_core, test_sub139);
  tcase_add_test(tc_core, test_sub140);
  tcase_add_test(tc_core, test_sub141);
  tcase_add_test(tc_core, test_sub142);
  tcase_add_test(tc_core, test_sub143);
  tcase_add_test(tc_core, test_sub144);
  tcase_add_test(tc_core, test_sub145);
  tcase_add_test(tc_core, test_sub146);
  tcase_add_test(tc_core, test_sub147);
  tcase_add_test(tc_core, test_sub148);
  tcase_add_test(tc_core, test_sub149);
  tcase_add_test(tc_core, test_sub150);
  tcase_add_test(tc_core, test_sub151);
  tcase_add_test(tc_core, test_sub152);
  tcase_add_test(tc_core, test_sub153);
  tcase_add_test(tc_core, test_sub154);
  tcase_add_test(tc_core, test_sub155);
  tcase_add_test(tc_core, test_sub156);
  tcase_add_test(tc_core, test_sub157);
  tcase_add_test(tc_core, test_sub158);
  tcase_add_test(tc_core, test_sub159);
  tcase_add_test(tc_core, test_sub160);
  tcase_add_test(tc_core, test_sub161);
  tcase_add_test(tc_core, test_sub162);
  tcase_add_test(tc_core, test_sub163);
  tcase_add_test(tc_core, test_sub164);
  tcase_add_test(tc_core, test_sub165);
  tcase_add_test(tc_core, test_sub166);
  tcase_add_test(tc_core, test_sub167);
  tcase_add_test(tc_core, test_sub168);
  tcase_add_test(tc_core, test_sub169);
  tcase_add_test(tc_core, test_sub170);
  tcase_add_test(tc_core, test_sub171);
  tcase_add_test(tc_core, test_sub172);
  tcase_add_test(tc_core, test_sub173);
  tcase_add_test(tc_core, test_sub174);
  tcase_add_test(tc_core, test_sub175);
  tcase_add_test(tc_core, test_sub176);
  tcase_add_test(tc_core, test_sub177);
  tcase_add_test(tc_core, test_sub178);
  tcase_add_test(tc_core, test_sub179);
  tcase_add_test(tc_core, test_sub180);
  tcase_add_test(tc_core, test_sub181);
  tcase_add_test(tc_core, test_sub182);
  tcase_add_test(tc_core, test_sub183);
  tcase_add_test(tc_core, test_sub184);
  tcase_add_test(tc_core, test_sub185);
  tcase_add_test(tc_core, test_sub186);
  tcase_add_test(tc_core, test_sub187);
  tcase_add_test(tc_core, test_sub188);
  tcase_add_test(tc_core, test_sub189);
  tcase_add_test(tc_core, test_sub190);
  tcase_add_test(tc_core, test_sub191);
  tcase_add_test(tc_core, test_sub192);
  tcase_add_test(tc_core, test_sub193);
  tcase_add_test(tc_core, test_sub194);
  tcase_add_test(tc_core, test_sub195);
  tcase_add_test(tc_core, test_sub196);
  tcase_add_test(tc_core, test_sub197);
  tcase_add_test(tc_core, test_sub198);
  tcase_add_test(tc_core, test_sub199);
  tcase_add_test(tc_core, test_sub200);
  tcase_add_test(tc_core, test_sub201);
  tcase_add_test(tc_core, test_sub202);
  tcase_add_test(tc_core, test_sub203);
  tcase_add_test(tc_core, test_sub204);
  tcase_add_test(tc_core, test_sub205);
  tcase_add_test(tc_core, test_sub206);
  tcase_add_test(tc_core, test_sub207);
  tcase_add_test(tc_core, test_sub208);
  tcase_add_test(tc_core, test_sub209);
  tcase_add_test(tc_core, test_sub210);
  tcase_add_test(tc_core, test_sub211);
  tcase_add_test(tc_core, test_sub212);
  tcase_add_test(tc_core, test_sub213);
  tcase_add_test(tc_core, test_sub214);
  tcase_add_test(tc_core, test_sub215);
  tcase_add_test(tc_core, test_sub216);
  tcase_add_test(tc_core, test_sub217);
  tcase_add_test(tc_core, test_sub218);
  tcase_add_test(tc_core, test_sub219);
  tcase_add_test(tc_core, test_sub220);
  tcase_add_test(tc_core, test_sub221);
  tcase_add_test(tc_core, test_sub222);
  tcase_add_test(tc_core, test_sub223);
  tcase_add_test(tc_core, test_sub224);
  tcase_add_test(tc_core, test_sub225);
  tcase_add_test(tc_core, test_sub226);
  tcase_add_test(tc_core, test_sub227);
  tcase_add_test(tc_core, test_sub228);
  tcase_add_test(tc_core, test_sub229);
  tcase_add_test(tc_core, test_sub230);
  tcase_add_test(tc_core, test_sub231);
  tcase_add_test(tc_core, test_sub232);
  tcase_add_test(tc_core, test_sub233);
  tcase_add_test(tc_core, test_sub234);
  tcase_add_test(tc_core, test_sub235);
  tcase_add_test(tc_core, test_sub236);
  tcase_add_test(tc_core, test_sub237);
  tcase_add_test(tc_core, test_sub238);
  tcase_add_test(tc_core, test_sub239);
  tcase_add_test(tc_core, test_sub240);
  tcase_add_test(tc_core, test_sub241);
  tcase_add_test(tc_core, test_sub242);
  tcase_add_test(tc_core, test_sub243);
  tcase_add_test(tc_core, test_sub244);
  tcase_add_test(tc_core, test_sub245);
  tcase_add_test(tc_core, test_sub246);
  tcase_add_test(tc_core, test_sub247);
  tcase_add_test(tc_core, test_sub248);
  tcase_add_test(tc_core, test_sub249);
  tcase_add_test(tc_core, test_sub250);
  tcase_add_test(tc_core, test_sub251);
  tcase_add_test(tc_core, test_sub252);
  tcase_add_test(tc_core, test_sub253);
  tcase_add_test(tc_core, test_sub254);
  tcase_add_test(tc_core, test_sub255);
  tcase_add_test(tc_core, test_sub256);
  tcase_add_test(tc_core, test_sub257);
  tcase_add_test(tc_core, test_sub258);
  tcase_add_test(tc_core, test_sub259);
  tcase_add_test(tc_core, test_sub260);
  tcase_add_test(tc_core, test_sub261);
  tcase_add_test(tc_core, test_sub262);
  tcase_add_test(tc_core, test_sub263);
  tcase_add_test(tc_core, test_sub264);
  tcase_add_test(tc_core, test_sub265);
  tcase_add_test(tc_core, test_sub266);
  tcase_add_test(tc_core, test_sub267);
  tcase_add_test(tc_core, test_sub268);
  tcase_add_test(tc_core, test_sub269);
  tcase_add_test(tc_core, test_sub270);
  tcase_add_test(tc_core, test_sub271);
  tcase_add_test(tc_core, test_sub272);
  tcase_add_test(tc_core, test_sub273);
  tcase_add_test(tc_core, test_sub274);
  tcase_add_test(tc_core, test_sub275);
  tcase_add_test(tc_core, test_sub276);
  tcase_add_test(tc_core, test_sub277);
  tcase_add_test(tc_core, test_sub278);
  tcase_add_test(tc_core, test_sub279);
  tcase_add_test(tc_core, test_sub280);
  tcase_add_test(tc_core, test_sub281);
  tcase_add_test(tc_core, test_sub282);
  tcase_add_test(tc_core, test_sub283);
  tcase_add_test(tc_core, test_sub284);
  tcase_add_test(tc_core, test_sub285);
  tcase_add_test(tc_core, test_sub286);
  tcase_add_test(tc_core, test_sub287);
  tcase_add_test(tc_core, test_sub288);
  tcase_add_test(tc_core, test_sub289);
  tcase_add_test(tc_core, test_sub290);
  tcase_add_test(tc_core, test_sub291);
  tcase_add_test(tc_core, test_sub292);
  tcase_add_test(tc_core, test_sub293);
  tcase_add_test(tc_core, test_sub294);
  tcase_add_test(tc_core, test_sub295);
  tcase_add_test(tc_core, test_sub296);
  tcase_add_test(tc_core, test_sub297);
  tcase_add_test(tc_core, test_sub298);
  tcase_add_test(tc_core, test_sub299);
  tcase_add_test(tc_core, test_sub300);
  tcase_add_test(tc_core, test_sub301);
  tcase_add_test(tc_core, test_sub302);
  tcase_add_test(tc_core, test_sub303);
  tcase_add_test(tc_core, test_sub304);
  tcase_add_test(tc_core, test_sub305);
  tcase_add_test(tc_core, test_sub306);
  tcase_add_test(tc_core, test_sub307);
  tcase_add_test(tc_core, test_sub308);
  tcase_add_test(tc_core, test_sub309);
  tcase_add_test(tc_core, test_sub310);
  tcase_add_test(tc_core, test_sub311);
  tcase_add_test(tc_core, test_sub312);
  tcase_add_test(tc_core, test_sub313);
  tcase_add_test(tc_core, test_sub314);
  tcase_add_test(tc_core, test_sub315);
  tcase_add_test(tc_core, test_sub316);
  tcase_add_test(tc_core, test_sub317);
  tcase_add_test(tc_core, test_sub318);
  tcase_add_test(tc_core, test_sub319);
  tcase_add_test(tc_core, test_sub320);
  tcase_add_test(tc_core, test_sub321);
  tcase_add_test(tc_core, test_sub322);
  tcase_add_test(tc_core, test_sub323);
  tcase_add_test(tc_core, test_sub324);
  tcase_add_test(tc_core, test_sub325);
  tcase_add_test(tc_core, test_sub326);
  tcase_add_test(tc_core, test_sub327);
  tcase_add_test(tc_core, test_sub328);
  tcase_add_test(tc_core, test_sub329);
  tcase_add_test(tc_core, test_sub330);
  tcase_add_test(tc_core, test_sub331);
  tcase_add_test(tc_core, test_sub332);
  tcase_add_test(tc_core, test_sub333);
  tcase_add_test(tc_core, test_sub334);
  tcase_add_test(tc_core, test_sub335);
  tcase_add_test(tc_core, test_sub336);
  tcase_add_test(tc_core, test_sub337);
  tcase_add_test(tc_core, test_sub338);
  tcase_add_test(tc_core, test_sub339);
  tcase_add_test(tc_core, test_sub340);
  tcase_add_test(tc_core, test_sub341);
  tcase_add_test(tc_core, test_sub342);
  tcase_add_test(tc_core, test_sub343);
  tcase_add_test(tc_core, test_sub344);
  tcase_add_test(tc_core, test_sub345);
  tcase_add_test(tc_core, test_sub346);
  tcase_add_test(tc_core, test_sub347);
  tcase_add_test(tc_core, test_sub348);
  tcase_add_test(tc_core, test_sub349);
  tcase_add_test(tc_core, test_sub350);
  tcase_add_test(tc_core, test_sub351);
  tcase_add_test(tc_core, test_sub352);
  tcase_add_test(tc_core, test_sub353);
  tcase_add_test(tc_core, test_sub354);
  tcase_add_test(tc_core, test_sub355);
  tcase_add_test(tc_core, test_sub356);
  tcase_add_test(tc_core, test_sub357);
  tcase_add_test(tc_core, test_sub358);
  tcase_add_test(tc_core, test_sub359);
  tcase_add_test(tc_core, test_sub360);
  tcase_add_test(tc_core, test_sub361);
  tcase_add_test(tc_core, test_sub362);
  tcase_add_test(tc_core, test_sub363);
  tcase_add_test(tc_core, test_sub364);
  tcase_add_test(tc_core, test_sub365);
  tcase_add_test(tc_core, test_sub366);
  tcase_add_test(tc_core, test_sub367);
  tcase_add_test(tc_core, test_sub368);
  tcase_add_test(tc_core, test_sub369);
  tcase_add_test(tc_core, test_sub370);
  tcase_add_test(tc_core, test_sub371);
  tcase_add_test(tc_core, test_sub372);
  tcase_add_test(tc_core, test_sub373);
  tcase_add_test(tc_core, test_sub374);
  tcase_add_test(tc_core, test_sub375);
  tcase_add_test(tc_core, test_sub376);
  tcase_add_test(tc_core, test_sub377);
  tcase_add_test(tc_core, test_sub378);
  tcase_add_test(tc_core, test_sub379);
  tcase_add_test(tc_core, test_sub380);
  tcase_add_test(tc_core, test_sub381);
  tcase_add_test(tc_core, test_sub382);
  tcase_add_test(tc_core, test_sub383);
  tcase_add_test(tc_core, test_sub384);
  tcase_add_test(tc_core, test_sub385);
  tcase_add_test(tc_core, test_sub386);
  tcase_add_test(tc_core, test_sub387);
  tcase_add_test(tc_core, test_sub388);
  tcase_add_test(tc_core, test_sub389);
  tcase_add_test(tc_core, test_sub390);
  tcase_add_test(tc_core, test_sub391);
  tcase_add_test(tc_core, test_sub392);
  tcase_add_test(tc_core, test_sub393);
  tcase_add_test(tc_core, test_sub394);
  tcase_add_test(tc_core, test_sub395);
  tcase_add_test(tc_core, test_sub396);
  tcase_add_test(tc_core, test_sub397);
  tcase_add_test(tc_core, test_sub398);
  tcase_add_test(tc_core, test_sub399);
  tcase_add_test(tc_core, test_sub400);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *mul_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("mul");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mul1);
  tcase_add_test(tc_core, test_mul2);
  tcase_add_test(tc_core, test_mul3);
  tcase_add_test(tc_core, test_mul4);
  tcase_add_test(tc_core, test_mul5);
  tcase_add_test(tc_core, test_mul6);
  tcase_add_test(tc_core, test_mul7);
  tcase_add_test(tc_core, test_mul8);
  tcase_add_test(tc_core, test_mul9);
  tcase_add_test(tc_core, test_mul10);
  tcase_add_test(tc_core, test_mul11);
  tcase_add_test(tc_core, test_mul12);
  tcase_add_test(tc_core, test_mul13);
  tcase_add_test(tc_core, test_mul14);
  tcase_add_test(tc_core, test_mul15);
  tcase_add_test(tc_core, test_mul16);
  tcase_add_test(tc_core, test_mul17);
  tcase_add_test(tc_core, test_mul18);
  tcase_add_test(tc_core, test_mul19);
  tcase_add_test(tc_core, test_mul20);
  tcase_add_test(tc_core, test_mul21);
  tcase_add_test(tc_core, test_mul22);
  tcase_add_test(tc_core, test_mul23);
  tcase_add_test(tc_core, test_mul24);
  tcase_add_test(tc_core, test_mul25);
  tcase_add_test(tc_core, test_mul26);
  tcase_add_test(tc_core, test_mul27);
  tcase_add_test(tc_core, test_mul28);
  tcase_add_test(tc_core, test_mul29);
  tcase_add_test(tc_core, test_mul30);
  tcase_add_test(tc_core, test_mul31);
  tcase_add_test(tc_core, test_mul32);
  tcase_add_test(tc_core, test_mul33);
  tcase_add_test(tc_core, test_mul34);
  tcase_add_test(tc_core, test_mul35);
  tcase_add_test(tc_core, test_mul36);
  tcase_add_test(tc_core, test_mul37);
  tcase_add_test(tc_core, test_mul38);
  tcase_add_test(tc_core, test_mul39);
  tcase_add_test(tc_core, test_mul40);
  tcase_add_test(tc_core, test_mul41);
  tcase_add_test(tc_core, test_mul42);
  tcase_add_test(tc_core, test_mul43);
  tcase_add_test(tc_core, test_mul44);
  tcase_add_test(tc_core, test_mul45);
  tcase_add_test(tc_core, test_mul46);
  tcase_add_test(tc_core, test_mul47);
  tcase_add_test(tc_core, test_mul48);
  tcase_add_test(tc_core, test_mul49);
  tcase_add_test(tc_core, test_mul50);
  tcase_add_test(tc_core, test_mul51);
  tcase_add_test(tc_core, test_mul52);
  tcase_add_test(tc_core, test_mul53);
  tcase_add_test(tc_core, test_mul54);
  tcase_add_test(tc_core, test_mul55);
  tcase_add_test(tc_core, test_mul56);
  tcase_add_test(tc_core, test_mul57);
  tcase_add_test(tc_core, test_mul58);
  tcase_add_test(tc_core, test_mul59);
  tcase_add_test(tc_core, test_mul60);
  tcase_add_test(tc_core, test_mul61);
  tcase_add_test(tc_core, test_mul62);
  tcase_add_test(tc_core, test_mul63);
  tcase_add_test(tc_core, test_mul64);
  tcase_add_test(tc_core, test_mul65);
  tcase_add_test(tc_core, test_mul66);
  tcase_add_test(tc_core, test_mul67);
  tcase_add_test(tc_core, test_mul68);
  tcase_add_test(tc_core, test_mul69);
  tcase_add_test(tc_core, test_mul70);
  tcase_add_test(tc_core, test_mul71);
  tcase_add_test(tc_core, test_mul72);
  tcase_add_test(tc_core, test_mul73);
  tcase_add_test(tc_core, test_mul74);
  tcase_add_test(tc_core, test_mul75);
  tcase_add_test(tc_core, test_mul76);
  tcase_add_test(tc_core, test_mul77);
  tcase_add_test(tc_core, test_mul78);
  tcase_add_test(tc_core, test_mul79);
  tcase_add_test(tc_core, test_mul80);
  tcase_add_test(tc_core, test_mul81);
  tcase_add_test(tc_core, test_mul82);
  tcase_add_test(tc_core, test_mul83);
  tcase_add_test(tc_core, test_mul84);
  tcase_add_test(tc_core, test_mul85);
  tcase_add_test(tc_core, test_mul86);
  tcase_add_test(tc_core, test_mul87);
  tcase_add_test(tc_core, test_mul88);
  tcase_add_test(tc_core, test_mul89);
  tcase_add_test(tc_core, test_mul90);
  tcase_add_test(tc_core, test_mul91);
  tcase_add_test(tc_core, test_mul92);
  tcase_add_test(tc_core, test_mul93);
  tcase_add_test(tc_core, test_mul94);
  tcase_add_test(tc_core, test_mul95);
  tcase_add_test(tc_core, test_mul96);
  tcase_add_test(tc_core, test_mul97);
  tcase_add_test(tc_core, test_mul98);
  tcase_add_test(tc_core, test_mul99);
  tcase_add_test(tc_core, test_mul100);
  tcase_add_test(tc_core, test_mul101);
  tcase_add_test(tc_core, test_mul102);
  tcase_add_test(tc_core, test_mul103);
  tcase_add_test(tc_core, test_mul104);
  tcase_add_test(tc_core, test_mul105);
  tcase_add_test(tc_core, test_mul106);
  tcase_add_test(tc_core, test_mul107);
  tcase_add_test(tc_core, test_mul108);
  tcase_add_test(tc_core, test_mul109);
  tcase_add_test(tc_core, test_mul110);
  tcase_add_test(tc_core, test_mul111);
  tcase_add_test(tc_core, test_mul112);
  tcase_add_test(tc_core, test_mul113);
  tcase_add_test(tc_core, test_mul114);
  tcase_add_test(tc_core, test_mul115);
  tcase_add_test(tc_core, test_mul116);
  tcase_add_test(tc_core, test_mul117);
  tcase_add_test(tc_core, test_mul118);
  tcase_add_test(tc_core, test_mul119);
  tcase_add_test(tc_core, test_mul120);
  tcase_add_test(tc_core, test_mul121);
  tcase_add_test(tc_core, test_mul122);
  tcase_add_test(tc_core, test_mul123);
  tcase_add_test(tc_core, test_mul124);
  tcase_add_test(tc_core, test_mul125);
  tcase_add_test(tc_core, test_mul126);
  tcase_add_test(tc_core, test_mul127);
  tcase_add_test(tc_core, test_mul128);
  tcase_add_test(tc_core, test_mul129);
  tcase_add_test(tc_core, test_mul130);
  tcase_add_test(tc_core, test_mul131);
  tcase_add_test(tc_core, test_mul132);
  tcase_add_test(tc_core, test_mul133);
  tcase_add_test(tc_core, test_mul134);
  tcase_add_test(tc_core, test_mul135);
  tcase_add_test(tc_core, test_mul136);
  tcase_add_test(tc_core, test_mul137);
  tcase_add_test(tc_core, test_mul138);
  tcase_add_test(tc_core, test_mul139);
  tcase_add_test(tc_core, test_mul140);
  tcase_add_test(tc_core, test_mul141);
  tcase_add_test(tc_core, test_mul142);
  tcase_add_test(tc_core, test_mul143);
  tcase_add_test(tc_core, test_mul144);
  tcase_add_test(tc_core, test_mul145);
  tcase_add_test(tc_core, test_mul146);
  tcase_add_test(tc_core, test_mul147);
  tcase_add_test(tc_core, test_mul148);
  tcase_add_test(tc_core, test_mul149);
  tcase_add_test(tc_core, test_mul150);
  tcase_add_test(tc_core, test_mul151);
  tcase_add_test(tc_core, test_mul152);
  tcase_add_test(tc_core, test_mul153);
  tcase_add_test(tc_core, test_mul154);
  tcase_add_test(tc_core, test_mul155);
  tcase_add_test(tc_core, test_mul156);
  tcase_add_test(tc_core, test_mul157);
  tcase_add_test(tc_core, test_mul158);
  tcase_add_test(tc_core, test_mul159);
  tcase_add_test(tc_core, test_mul160);
  tcase_add_test(tc_core, test_mul161);
  tcase_add_test(tc_core, test_mul162);
  tcase_add_test(tc_core, test_mul163);
  tcase_add_test(tc_core, test_mul164);
  tcase_add_test(tc_core, test_mul165);
  tcase_add_test(tc_core, test_mul166);
  tcase_add_test(tc_core, test_mul167);
  tcase_add_test(tc_core, test_mul168);
  tcase_add_test(tc_core, test_mul169);
  tcase_add_test(tc_core, test_mul170);
  tcase_add_test(tc_core, test_mul171);
  tcase_add_test(tc_core, test_mul172);
  tcase_add_test(tc_core, test_mul173);
  tcase_add_test(tc_core, test_mul174);
  tcase_add_test(tc_core, test_mul175);
  tcase_add_test(tc_core, test_mul176);
  tcase_add_test(tc_core, test_mul177);
  tcase_add_test(tc_core, test_mul178);
  tcase_add_test(tc_core, test_mul179);
  tcase_add_test(tc_core, test_mul180);
  tcase_add_test(tc_core, test_mul181);
  tcase_add_test(tc_core, test_mul182);
  tcase_add_test(tc_core, test_mul183);
  tcase_add_test(tc_core, test_mul184);
  tcase_add_test(tc_core, test_mul185);
  tcase_add_test(tc_core, test_mul186);
  tcase_add_test(tc_core, test_mul187);
  tcase_add_test(tc_core, test_mul188);
  tcase_add_test(tc_core, test_mul189);
  tcase_add_test(tc_core, test_mul190);
  tcase_add_test(tc_core, test_mul191);
  tcase_add_test(tc_core, test_mul192);
  tcase_add_test(tc_core, test_mul193);
  tcase_add_test(tc_core, test_mul194);
  tcase_add_test(tc_core, test_mul195);
  tcase_add_test(tc_core, test_mul196);
  tcase_add_test(tc_core, test_mul197);
  tcase_add_test(tc_core, test_mul198);
  tcase_add_test(tc_core, test_mul199);
  tcase_add_test(tc_core, test_mul200);
  tcase_add_test(tc_core, test_mul201);
  tcase_add_test(tc_core, test_mul202);
  tcase_add_test(tc_core, test_mul203);
  tcase_add_test(tc_core, test_mul204);
  tcase_add_test(tc_core, test_mul205);
  tcase_add_test(tc_core, test_mul206);
  tcase_add_test(tc_core, test_mul207);
  tcase_add_test(tc_core, test_mul208);
  tcase_add_test(tc_core, test_mul209);
  tcase_add_test(tc_core, test_mul210);
  tcase_add_test(tc_core, test_mul211);
  tcase_add_test(tc_core, test_mul212);
  tcase_add_test(tc_core, test_mul213);
  tcase_add_test(tc_core, test_mul214);
  tcase_add_test(tc_core, test_mul215);
  tcase_add_test(tc_core, test_mul216);
  tcase_add_test(tc_core, test_mul217);
  tcase_add_test(tc_core, test_mul218);
  tcase_add_test(tc_core, test_mul219);
  tcase_add_test(tc_core, test_mul220);
  tcase_add_test(tc_core, test_mul221);
  tcase_add_test(tc_core, test_mul222);
  tcase_add_test(tc_core, test_mul223);
  tcase_add_test(tc_core, test_mul224);
  tcase_add_test(tc_core, test_mul225);
  tcase_add_test(tc_core, test_mul226);
  tcase_add_test(tc_core, test_mul227);
  tcase_add_test(tc_core, test_mul228);
  tcase_add_test(tc_core, test_mul229);
  tcase_add_test(tc_core, test_mul230);
  tcase_add_test(tc_core, test_mul231);
  tcase_add_test(tc_core, test_mul232);
  tcase_add_test(tc_core, test_mul233);
  tcase_add_test(tc_core, test_mul234);
  tcase_add_test(tc_core, test_mul235);
  tcase_add_test(tc_core, test_mul236);
  tcase_add_test(tc_core, test_mul237);
  tcase_add_test(tc_core, test_mul238);
  tcase_add_test(tc_core, test_mul239);
  tcase_add_test(tc_core, test_mul240);
  tcase_add_test(tc_core, test_mul241);
  tcase_add_test(tc_core, test_mul242);
  tcase_add_test(tc_core, test_mul243);
  tcase_add_test(tc_core, test_mul244);
  tcase_add_test(tc_core, test_mul245);
  tcase_add_test(tc_core, test_mul246);
  tcase_add_test(tc_core, test_mul247);
  tcase_add_test(tc_core, test_mul248);
  tcase_add_test(tc_core, test_mul249);
  tcase_add_test(tc_core, test_mul250);
  tcase_add_test(tc_core, test_mul251);
  tcase_add_test(tc_core, test_mul252);
  tcase_add_test(tc_core, test_mul253);
  tcase_add_test(tc_core, test_mul254);
  tcase_add_test(tc_core, test_mul255);
  tcase_add_test(tc_core, test_mul256);
  tcase_add_test(tc_core, test_mul257);
  tcase_add_test(tc_core, test_mul258);
  tcase_add_test(tc_core, test_mul259);
  tcase_add_test(tc_core, test_mul260);
  tcase_add_test(tc_core, test_mul261);
  tcase_add_test(tc_core, test_mul262);
  tcase_add_test(tc_core, test_mul263);
  tcase_add_test(tc_core, test_mul264);
  tcase_add_test(tc_core, test_mul265);
  tcase_add_test(tc_core, test_mul266);
  tcase_add_test(tc_core, test_mul267);
  tcase_add_test(tc_core, test_mul268);
  tcase_add_test(tc_core, test_mul269);
  tcase_add_test(tc_core, test_mul270);
  tcase_add_test(tc_core, test_mul271);
  tcase_add_test(tc_core, test_mul272);
  tcase_add_test(tc_core, test_mul273);
  tcase_add_test(tc_core, test_mul274);
  tcase_add_test(tc_core, test_mul275);
  tcase_add_test(tc_core, test_mul276);
  tcase_add_test(tc_core, test_mul277);
  tcase_add_test(tc_core, test_mul278);
  tcase_add_test(tc_core, test_mul279);
  tcase_add_test(tc_core, test_mul280);
  tcase_add_test(tc_core, test_mul281);
  tcase_add_test(tc_core, test_mul282);
  tcase_add_test(tc_core, test_mul283);
  tcase_add_test(tc_core, test_mul284);
  tcase_add_test(tc_core, test_mul285);
  tcase_add_test(tc_core, test_mul286);
  tcase_add_test(tc_core, test_mul287);
  tcase_add_test(tc_core, test_mul288);
  tcase_add_test(tc_core, test_mul289);
  tcase_add_test(tc_core, test_mul290);
  tcase_add_test(tc_core, test_mul291);
  tcase_add_test(tc_core, test_mul292);
  tcase_add_test(tc_core, test_mul293);
  tcase_add_test(tc_core, test_mul294);
  tcase_add_test(tc_core, test_mul295);
  tcase_add_test(tc_core, test_mul296);
  tcase_add_test(tc_core, test_mul297);
  tcase_add_test(tc_core, test_mul298);
  tcase_add_test(tc_core, test_mul299);
  tcase_add_test(tc_core, test_mul300);
  tcase_add_test(tc_core, test_mul301);
  tcase_add_test(tc_core, test_mul302);
  tcase_add_test(tc_core, test_mul303);
  tcase_add_test(tc_core, test_mul304);
  tcase_add_test(tc_core, test_mul305);
  tcase_add_test(tc_core, test_mul306);
  tcase_add_test(tc_core, test_mul307);
  tcase_add_test(tc_core, test_mul308);
  tcase_add_test(tc_core, test_mul309);
  tcase_add_test(tc_core, test_mul310);
  tcase_add_test(tc_core, test_mul311);
  tcase_add_test(tc_core, test_mul312);
  tcase_add_test(tc_core, test_mul313);
  tcase_add_test(tc_core, test_mul314);
  tcase_add_test(tc_core, test_mul315);
  tcase_add_test(tc_core, test_mul316);
  tcase_add_test(tc_core, test_mul317);
  tcase_add_test(tc_core, test_mul318);
  tcase_add_test(tc_core, test_mul319);
  tcase_add_test(tc_core, test_mul320);
  tcase_add_test(tc_core, test_mul321);
  tcase_add_test(tc_core, test_mul322);
  tcase_add_test(tc_core, test_mul323);
  tcase_add_test(tc_core, test_mul324);
  tcase_add_test(tc_core, test_mul325);
  tcase_add_test(tc_core, test_mul326);
  tcase_add_test(tc_core, test_mul327);
  tcase_add_test(tc_core, test_mul328);
  tcase_add_test(tc_core, test_mul329);
  tcase_add_test(tc_core, test_mul330);
  tcase_add_test(tc_core, test_mul331);
  tcase_add_test(tc_core, test_mul332);
  tcase_add_test(tc_core, test_mul333);
  tcase_add_test(tc_core, test_mul334);
  tcase_add_test(tc_core, test_mul335);
  tcase_add_test(tc_core, test_mul336);
  tcase_add_test(tc_core, test_mul337);
  tcase_add_test(tc_core, test_mul338);
  tcase_add_test(tc_core, test_mul339);
  tcase_add_test(tc_core, test_mul340);
  tcase_add_test(tc_core, test_mul341);
  tcase_add_test(tc_core, test_mul342);
  tcase_add_test(tc_core, test_mul343);
  tcase_add_test(tc_core, test_mul344);
  tcase_add_test(tc_core, test_mul345);
  tcase_add_test(tc_core, test_mul346);
  tcase_add_test(tc_core, test_mul347);
  tcase_add_test(tc_core, test_mul348);
  tcase_add_test(tc_core, test_mul349);
  tcase_add_test(tc_core, test_mul350);
  tcase_add_test(tc_core, test_mul351);
  tcase_add_test(tc_core, test_mul352);
  tcase_add_test(tc_core, test_mul353);
  tcase_add_test(tc_core, test_mul354);
  tcase_add_test(tc_core, test_mul355);
  tcase_add_test(tc_core, test_mul356);
  tcase_add_test(tc_core, test_mul357);
  tcase_add_test(tc_core, test_mul358);
  tcase_add_test(tc_core, test_mul359);
  tcase_add_test(tc_core, test_mul360);
  tcase_add_test(tc_core, test_mul361);
  tcase_add_test(tc_core, test_mul362);
  tcase_add_test(tc_core, test_mul363);
  tcase_add_test(tc_core, test_mul364);
  tcase_add_test(tc_core, test_mul365);
  tcase_add_test(tc_core, test_mul366);
  tcase_add_test(tc_core, test_mul367);
  tcase_add_test(tc_core, test_mul368);
  tcase_add_test(tc_core, test_mul369);
  tcase_add_test(tc_core, test_mul370);
  tcase_add_test(tc_core, test_mul371);
  tcase_add_test(tc_core, test_mul372);
  tcase_add_test(tc_core, test_mul373);
  tcase_add_test(tc_core, test_mul374);
  tcase_add_test(tc_core, test_mul375);
  tcase_add_test(tc_core, test_mul376);
  tcase_add_test(tc_core, test_mul377);
  tcase_add_test(tc_core, test_mul378);
  tcase_add_test(tc_core, test_mul379);
  tcase_add_test(tc_core, test_mul380);
  tcase_add_test(tc_core, test_mul381);
  tcase_add_test(tc_core, test_mul382);
  tcase_add_test(tc_core, test_mul383);
  tcase_add_test(tc_core, test_mul384);
  tcase_add_test(tc_core, test_mul385);
  tcase_add_test(tc_core, test_mul386);
  tcase_add_test(tc_core, test_mul387);
  tcase_add_test(tc_core, test_mul388);
  tcase_add_test(tc_core, test_mul389);
  tcase_add_test(tc_core, test_mul390);
  tcase_add_test(tc_core, test_mul391);
  tcase_add_test(tc_core, test_mul392);
  tcase_add_test(tc_core, test_mul393);
  tcase_add_test(tc_core, test_mul394);
  tcase_add_test(tc_core, test_mul395);
  tcase_add_test(tc_core, test_mul396);
  tcase_add_test(tc_core, test_mul397);
  tcase_add_test(tc_core, test_mul398);
  tcase_add_test(tc_core, test_mul399);
  tcase_add_test(tc_core, test_mul400);

  suite_add_tcase(s, tc_core);
  return s;
}

Suite *div_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("div");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_div1);
  tcase_add_test(tc_core, test_div2);
  tcase_add_test(tc_core, test_div3);
  tcase_add_test(tc_core, test_div4);
  tcase_add_test(tc_core, test_div5);
  tcase_add_test(tc_core, test_div6);
  tcase_add_test(tc_core, test_div7);
  tcase_add_test(tc_core, test_div8);
  tcase_add_test(tc_core, test_div9);
  tcase_add_test(tc_core, test_div10);
  tcase_add_test(tc_core, test_div11);
  tcase_add_test(tc_core, test_div12);
  tcase_add_test(tc_core, test_div13);
  tcase_add_test(tc_core, test_div14);
  tcase_add_test(tc_core, test_div15);
  tcase_add_test(tc_core, test_div16);
  tcase_add_test(tc_core, test_div17);
  tcase_add_test(tc_core, test_div18);
  tcase_add_test(tc_core, test_div19);
  tcase_add_test(tc_core, test_div20);
  tcase_add_test(tc_core, test_div21);
  tcase_add_test(tc_core, test_div22);
  tcase_add_test(tc_core, test_div23);
  tcase_add_test(tc_core, test_div24);
  tcase_add_test(tc_core, test_div25);
  tcase_add_test(tc_core, test_div26);
  tcase_add_test(tc_core, test_div27);
  tcase_add_test(tc_core, test_div28);
  tcase_add_test(tc_core, test_div29);
  tcase_add_test(tc_core, test_div30);
  tcase_add_test(tc_core, test_div31);
  tcase_add_test(tc_core, test_div32);
  tcase_add_test(tc_core, test_div33);
  tcase_add_test(tc_core, test_div34);
  tcase_add_test(tc_core, test_div35);
  tcase_add_test(tc_core, test_div36);
  tcase_add_test(tc_core, test_div37);
  tcase_add_test(tc_core, test_div38);
  tcase_add_test(tc_core, test_div39);
  tcase_add_test(tc_core, test_div40);
  tcase_add_test(tc_core, test_div41);
  tcase_add_test(tc_core, test_div42);
  tcase_add_test(tc_core, test_div43);
  tcase_add_test(tc_core, test_div44);
  tcase_add_test(tc_core, test_div45);
  tcase_add_test(tc_core, test_div46);
  tcase_add_test(tc_core, test_div47);
  tcase_add_test(tc_core, test_div48);
  tcase_add_test(tc_core, test_div49);
  tcase_add_test(tc_core, test_div50);
  tcase_add_test(tc_core, test_div51);
  tcase_add_test(tc_core, test_div52);
  tcase_add_test(tc_core, test_div53);
  tcase_add_test(tc_core, test_div54);
  tcase_add_test(tc_core, test_div55);
  tcase_add_test(tc_core, test_div56);
  tcase_add_test(tc_core, test_div57);
  tcase_add_test(tc_core, test_div58);
  tcase_add_test(tc_core, test_div59);
  tcase_add_test(tc_core, test_div60);
  tcase_add_test(tc_core, test_div61);
  tcase_add_test(tc_core, test_div62);
  tcase_add_test(tc_core, test_div63);
  tcase_add_test(tc_core, test_div64);
  tcase_add_test(tc_core, test_div65);
  tcase_add_test(tc_core, test_div66);
  tcase_add_test(tc_core, test_div67);
  tcase_add_test(tc_core, test_div68);
  tcase_add_test(tc_core, test_div69);
  tcase_add_test(tc_core, test_div70);
  tcase_add_test(tc_core, test_div71);
  tcase_add_test(tc_core, test_div72);
  tcase_add_test(tc_core, test_div73);
  tcase_add_test(tc_core, test_div74);
  tcase_add_test(tc_core, test_div75);
  tcase_add_test(tc_core, test_div76);
  tcase_add_test(tc_core, test_div77);
  tcase_add_test(tc_core, test_div78);
  tcase_add_test(tc_core, test_div79);
  tcase_add_test(tc_core, test_div80);
  tcase_add_test(tc_core, test_div81);
  tcase_add_test(tc_core, test_div82);
  tcase_add_test(tc_core, test_div83);
  tcase_add_test(tc_core, test_div84);
  tcase_add_test(tc_core, test_div85);
  tcase_add_test(tc_core, test_div86);
  tcase_add_test(tc_core, test_div87);
  tcase_add_test(tc_core, test_div88);
  tcase_add_test(tc_core, test_div89);
  tcase_add_test(tc_core, test_div90);
  tcase_add_test(tc_core, test_div91);
  tcase_add_test(tc_core, test_div92);
  tcase_add_test(tc_core, test_div93);
  tcase_add_test(tc_core, test_div94);
  tcase_add_test(tc_core, test_div95);
  tcase_add_test(tc_core, test_div96);
  tcase_add_test(tc_core, test_div97);
  tcase_add_test(tc_core, test_div98);
  tcase_add_test(tc_core, test_div99);
  tcase_add_test(tc_core, test_div100);
  tcase_add_test(tc_core, test_div101);
  tcase_add_test(tc_core, test_div102);
  tcase_add_test(tc_core, test_div103);
  tcase_add_test(tc_core, test_div104);
  tcase_add_test(tc_core, test_div105);
  tcase_add_test(tc_core, test_div106);
  tcase_add_test(tc_core, test_div107);
  tcase_add_test(tc_core, test_div108);
  tcase_add_test(tc_core, test_div109);
  tcase_add_test(tc_core, test_div110);
  tcase_add_test(tc_core, test_div111);
  tcase_add_test(tc_core, test_div112);
  tcase_add_test(tc_core, test_div113);
  tcase_add_test(tc_core, test_div114);
  tcase_add_test(tc_core, test_div115);
  tcase_add_test(tc_core, test_div116);
  tcase_add_test(tc_core, test_div117);
  tcase_add_test(tc_core, test_div118);
  tcase_add_test(tc_core, test_div119);
  tcase_add_test(tc_core, test_div120);
  tcase_add_test(tc_core, test_div121);
  tcase_add_test(tc_core, test_div122);
  tcase_add_test(tc_core, test_div123);
  tcase_add_test(tc_core, test_div124);
  tcase_add_test(tc_core, test_div125);
  tcase_add_test(tc_core, test_div126);
  tcase_add_test(tc_core, test_div127);
  tcase_add_test(tc_core, test_div128);
  tcase_add_test(tc_core, test_div129);
  tcase_add_test(tc_core, test_div130);
  tcase_add_test(tc_core, test_div131);
  tcase_add_test(tc_core, test_div132);
  tcase_add_test(tc_core, test_div133);
  tcase_add_test(tc_core, test_div134);
  tcase_add_test(tc_core, test_div135);
  tcase_add_test(tc_core, test_div136);
  tcase_add_test(tc_core, test_div137);
  tcase_add_test(tc_core, test_div138);
  tcase_add_test(tc_core, test_div139);
  tcase_add_test(tc_core, test_div140);
  tcase_add_test(tc_core, test_div141);
  tcase_add_test(tc_core, test_div142);
  tcase_add_test(tc_core, test_div143);
  tcase_add_test(tc_core, test_div144);
  tcase_add_test(tc_core, test_div145);
  tcase_add_test(tc_core, test_div146);
  tcase_add_test(tc_core, test_div147);
  tcase_add_test(tc_core, test_div148);
  tcase_add_test(tc_core, test_div149);
  tcase_add_test(tc_core, test_div150);
  tcase_add_test(tc_core, test_div151);
  tcase_add_test(tc_core, test_div152);
  tcase_add_test(tc_core, test_div153);
  tcase_add_test(tc_core, test_div154);
  tcase_add_test(tc_core, test_div155);
  tcase_add_test(tc_core, test_div156);
  tcase_add_test(tc_core, test_div157);
  tcase_add_test(tc_core, test_div158);
  tcase_add_test(tc_core, test_div159);
  tcase_add_test(tc_core, test_div160);
  tcase_add_test(tc_core, test_div161);
  tcase_add_test(tc_core, test_div162);
  tcase_add_test(tc_core, test_div163);
  tcase_add_test(tc_core, test_div164);
  tcase_add_test(tc_core, test_div165);
  tcase_add_test(tc_core, test_div166);
  tcase_add_test(tc_core, test_div167);
  tcase_add_test(tc_core, test_div168);
  tcase_add_test(tc_core, test_div169);
  tcase_add_test(tc_core, test_div170);
  tcase_add_test(tc_core, test_div171);
  tcase_add_test(tc_core, test_div172);
  tcase_add_test(tc_core, test_div173);
  tcase_add_test(tc_core, test_div174);
  tcase_add_test(tc_core, test_div175);
  tcase_add_test(tc_core, test_div176);
  tcase_add_test(tc_core, test_div177);
  tcase_add_test(tc_core, test_div178);
  tcase_add_test(tc_core, test_div179);
  tcase_add_test(tc_core, test_div180);
  tcase_add_test(tc_core, test_div181);
  tcase_add_test(tc_core, test_div182);
  tcase_add_test(tc_core, test_div183);
  tcase_add_test(tc_core, test_div184);
  tcase_add_test(tc_core, test_div185);
  tcase_add_test(tc_core, test_div186);
  tcase_add_test(tc_core, test_div187);
  tcase_add_test(tc_core, test_div188);
  tcase_add_test(tc_core, test_div189);
  tcase_add_test(tc_core, test_div190);
  tcase_add_test(tc_core, test_div191);
  tcase_add_test(tc_core, test_div192);
  tcase_add_test(tc_core, test_div193);
  tcase_add_test(tc_core, test_div194);
  tcase_add_test(tc_core, test_div195);
  tcase_add_test(tc_core, test_div196);
  tcase_add_test(tc_core, test_div197);
  tcase_add_test(tc_core, test_div198);
  tcase_add_test(tc_core, test_div199);
  tcase_add_test(tc_core, test_div200);
  tcase_add_test(tc_core, test_div201);
  tcase_add_test(tc_core, test_div202);
  tcase_add_test(tc_core, test_div203);
  tcase_add_test(tc_core, test_div204);
  tcase_add_test(tc_core, test_div205);
  tcase_add_test(tc_core, test_div206);
  tcase_add_test(tc_core, test_div207);
  tcase_add_test(tc_core, test_div208);
  tcase_add_test(tc_core, test_div209);
  tcase_add_test(tc_core, test_div210);
  tcase_add_test(tc_core, test_div211);
  tcase_add_test(tc_core, test_div212);
  tcase_add_test(tc_core, test_div213);
  tcase_add_test(tc_core, test_div214);
  tcase_add_test(tc_core, test_div215);
  tcase_add_test(tc_core, test_div216);
  tcase_add_test(tc_core, test_div217);
  tcase_add_test(tc_core, test_div218);
  tcase_add_test(tc_core, test_div219);
  tcase_add_test(tc_core, test_div220);
  tcase_add_test(tc_core, test_div221);
  tcase_add_test(tc_core, test_div222);
  tcase_add_test(tc_core, test_div223);
  tcase_add_test(tc_core, test_div224);
  tcase_add_test(tc_core, test_div225);
  tcase_add_test(tc_core, test_div226);
  tcase_add_test(tc_core, test_div227);
  tcase_add_test(tc_core, test_div228);
  tcase_add_test(tc_core, test_div229);
  tcase_add_test(tc_core, test_div230);
  tcase_add_test(tc_core, test_div231);
  tcase_add_test(tc_core, test_div232);
  tcase_add_test(tc_core, test_div233);
  tcase_add_test(tc_core, test_div234);
  tcase_add_test(tc_core, test_div235);
  tcase_add_test(tc_core, test_div236);
  tcase_add_test(tc_core, test_div237);
  tcase_add_test(tc_core, test_div238);
  tcase_add_test(tc_core, test_div239);
  tcase_add_test(tc_core, test_div240);
  tcase_add_test(tc_core, test_div241);
  tcase_add_test(tc_core, test_div242);
  tcase_add_test(tc_core, test_div243);
  tcase_add_test(tc_core, test_div244);
  tcase_add_test(tc_core, test_div245);
  tcase_add_test(tc_core, test_div246);
  tcase_add_test(tc_core, test_div247);
  tcase_add_test(tc_core, test_div248);
  tcase_add_test(tc_core, test_div249);
  tcase_add_test(tc_core, test_div250);
  tcase_add_test(tc_core, test_div251);
  tcase_add_test(tc_core, test_div252);
  tcase_add_test(tc_core, test_div253);
  tcase_add_test(tc_core, test_div254);
  tcase_add_test(tc_core, test_div255);
  tcase_add_test(tc_core, test_div256);
  tcase_add_test(tc_core, test_div257);
  tcase_add_test(tc_core, test_div258);
  tcase_add_test(tc_core, test_div259);
  tcase_add_test(tc_core, test_div260);
  tcase_add_test(tc_core, test_div261);
  tcase_add_test(tc_core, test_div262);
  tcase_add_test(tc_core, test_div263);
  tcase_add_test(tc_core, test_div264);
  tcase_add_test(tc_core, test_div265);
  tcase_add_test(tc_core, test_div266);
  tcase_add_test(tc_core, test_div267);
  tcase_add_test(tc_core, test_div268);
  tcase_add_test(tc_core, test_div269);
  tcase_add_test(tc_core, test_div270);
  tcase_add_test(tc_core, test_div271);
  tcase_add_test(tc_core, test_div272);
  tcase_add_test(tc_core, test_div273);
  tcase_add_test(tc_core, test_div274);
  tcase_add_test(tc_core, test_div275);
  tcase_add_test(tc_core, test_div276);
  tcase_add_test(tc_core, test_div277);
  tcase_add_test(tc_core, test_div278);
  tcase_add_test(tc_core, test_div279);
  tcase_add_test(tc_core, test_div280);
  tcase_add_test(tc_core, test_div281);
  tcase_add_test(tc_core, test_div282);
  tcase_add_test(tc_core, test_div283);
  tcase_add_test(tc_core, test_div284);
  tcase_add_test(tc_core, test_div285);
  tcase_add_test(tc_core, test_div286);
  tcase_add_test(tc_core, test_div287);
  tcase_add_test(tc_core, test_div288);
  tcase_add_test(tc_core, test_div289);
  tcase_add_test(tc_core, test_div290);
  tcase_add_test(tc_core, test_div291);
  tcase_add_test(tc_core, test_div292);
  tcase_add_test(tc_core, test_div293);
  tcase_add_test(tc_core, test_div294);
  tcase_add_test(tc_core, test_div295);
  tcase_add_test(tc_core, test_div296);
  tcase_add_test(tc_core, test_div297);
  tcase_add_test(tc_core, test_div298);
  tcase_add_test(tc_core, test_div299);
  tcase_add_test(tc_core, test_div300);
  tcase_add_test(tc_core, test_div301);
  tcase_add_test(tc_core, test_div302);
  tcase_add_test(tc_core, test_div303);
  tcase_add_test(tc_core, test_div304);
  tcase_add_test(tc_core, test_div305);
  tcase_add_test(tc_core, test_div306);
  tcase_add_test(tc_core, test_div307);
  tcase_add_test(tc_core, test_div308);
  tcase_add_test(tc_core, test_div309);
  tcase_add_test(tc_core, test_div310);
  tcase_add_test(tc_core, test_div311);
  tcase_add_test(tc_core, test_div312);
  tcase_add_test(tc_core, test_div313);
  tcase_add_test(tc_core, test_div314);
  tcase_add_test(tc_core, test_div315);
  tcase_add_test(tc_core, test_div316);
  tcase_add_test(tc_core, test_div317);
  tcase_add_test(tc_core, test_div318);
  tcase_add_test(tc_core, test_div319);
  tcase_add_test(tc_core, test_div320);
  tcase_add_test(tc_core, test_div321);
  tcase_add_test(tc_core, test_div322);
  tcase_add_test(tc_core, test_div323);
  tcase_add_test(tc_core, test_div324);
  tcase_add_test(tc_core, test_div325);
  tcase_add_test(tc_core, test_div326);
  tcase_add_test(tc_core, test_div327);
  tcase_add_test(tc_core, test_div328);
  tcase_add_test(tc_core, test_div329);
  tcase_add_test(tc_core, test_div330);
  tcase_add_test(tc_core, test_div331);
  tcase_add_test(tc_core, test_div332);
  tcase_add_test(tc_core, test_div333);
  tcase_add_test(tc_core, test_div334);
  tcase_add_test(tc_core, test_div335);
  tcase_add_test(tc_core, test_div336);
  tcase_add_test(tc_core, test_div337);
  tcase_add_test(tc_core, test_div338);
  tcase_add_test(tc_core, test_div339);
  tcase_add_test(tc_core, test_div340);
  tcase_add_test(tc_core, test_div341);
  tcase_add_test(tc_core, test_div342);
  tcase_add_test(tc_core, test_div343);
  tcase_add_test(tc_core, test_div344);
  tcase_add_test(tc_core, test_div345);
  tcase_add_test(tc_core, test_div346);
  tcase_add_test(tc_core, test_div347);
  tcase_add_test(tc_core, test_div348);
  tcase_add_test(tc_core, test_div349);
  tcase_add_test(tc_core, test_div350);
  tcase_add_test(tc_core, test_div351);
  tcase_add_test(tc_core, test_div352);
  tcase_add_test(tc_core, test_div353);
  tcase_add_test(tc_core, test_div354);
  tcase_add_test(tc_core, test_div355);
  tcase_add_test(tc_core, test_div356);
  tcase_add_test(tc_core, test_div357);
  tcase_add_test(tc_core, test_div358);
  tcase_add_test(tc_core, test_div359);
  tcase_add_test(tc_core, test_div360);
  tcase_add_test(tc_core, test_div361);
  tcase_add_test(tc_core, test_div362);
  tcase_add_test(tc_core, test_div363);
  tcase_add_test(tc_core, test_div364);
  tcase_add_test(tc_core, test_div365);
  tcase_add_test(tc_core, test_div366);
  tcase_add_test(tc_core, test_div367);
  tcase_add_test(tc_core, test_div368);
  tcase_add_test(tc_core, test_div369);
  tcase_add_test(tc_core, test_div370);
  tcase_add_test(tc_core, test_div371);
  tcase_add_test(tc_core, test_div372);
  tcase_add_test(tc_core, test_div373);
  tcase_add_test(tc_core, test_div374);
  tcase_add_test(tc_core, test_div375);
  tcase_add_test(tc_core, test_div376);
  tcase_add_test(tc_core, test_div377);
  tcase_add_test(tc_core, test_div378);
  tcase_add_test(tc_core, test_div379);
  tcase_add_test(tc_core, test_div380);
  tcase_add_test(tc_core, test_div381);
  tcase_add_test(tc_core, test_div382);
  tcase_add_test(tc_core, test_div383);
  tcase_add_test(tc_core, test_div384);
  tcase_add_test(tc_core, test_div385);
  tcase_add_test(tc_core, test_div386);
  tcase_add_test(tc_core, test_div387);
  tcase_add_test(tc_core, test_div388);
  tcase_add_test(tc_core, test_div389);
  tcase_add_test(tc_core, test_div390);
  tcase_add_test(tc_core, test_div391);
  tcase_add_test(tc_core, test_div392);
  tcase_add_test(tc_core, test_div393);
  tcase_add_test(tc_core, test_div394);
  tcase_add_test(tc_core, test_div395);
  tcase_add_test(tc_core, test_div396);
  tcase_add_test(tc_core, test_div397);
  tcase_add_test(tc_core, test_div398);
  tcase_add_test(tc_core, test_div399);
  tcase_add_test(tc_core, test_div400);
  suite_add_tcase(s, tc_core);
  return s;
}

Suite *add_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("add");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_add1);
  tcase_add_test(tc_core, test_add2);
  tcase_add_test(tc_core, test_add3);
  tcase_add_test(tc_core, test_add4);
  tcase_add_test(tc_core, test_add5);
  tcase_add_test(tc_core, test_add6);
  tcase_add_test(tc_core, test_add7);
  tcase_add_test(tc_core, test_add8);
  tcase_add_test(tc_core, test_add9);
  tcase_add_test(tc_core, test_add10);
  tcase_add_test(tc_core, test_add11);
  tcase_add_test(tc_core, test_add12);
  tcase_add_test(tc_core, test_add13);
  tcase_add_test(tc_core, test_add14);
  tcase_add_test(tc_core, test_add15);
  tcase_add_test(tc_core, test_add16);
  tcase_add_test(tc_core, test_add17);
  tcase_add_test(tc_core, test_add18);
  tcase_add_test(tc_core, test_add19);
  tcase_add_test(tc_core, test_add20);
  tcase_add_test(tc_core, test_add21);
  tcase_add_test(tc_core, test_add22);
  tcase_add_test(tc_core, test_add23);
  tcase_add_test(tc_core, test_add24);
  tcase_add_test(tc_core, test_add25);
  tcase_add_test(tc_core, test_add26);
  tcase_add_test(tc_core, test_add27);
  tcase_add_test(tc_core, test_add28);
  tcase_add_test(tc_core, test_add29);
  tcase_add_test(tc_core, test_add30);
  tcase_add_test(tc_core, test_add31);
  tcase_add_test(tc_core, test_add32);
  tcase_add_test(tc_core, test_add33);
  tcase_add_test(tc_core, test_add34);
  tcase_add_test(tc_core, test_add35);
  tcase_add_test(tc_core, test_add36);
  tcase_add_test(tc_core, test_add37);
  tcase_add_test(tc_core, test_add38);
  tcase_add_test(tc_core, test_add39);
  tcase_add_test(tc_core, test_add40);
  tcase_add_test(tc_core, test_add41);
  tcase_add_test(tc_core, test_add42);
  tcase_add_test(tc_core, test_add43);
  tcase_add_test(tc_core, test_add44);
  tcase_add_test(tc_core, test_add45);
  tcase_add_test(tc_core, test_add46);
  tcase_add_test(tc_core, test_add47);
  tcase_add_test(tc_core, test_add48);
  tcase_add_test(tc_core, test_add49);
  tcase_add_test(tc_core, test_add50);
  tcase_add_test(tc_core, test_add51);
  tcase_add_test(tc_core, test_add52);
  tcase_add_test(tc_core, test_add53);
  tcase_add_test(tc_core, test_add54);
  tcase_add_test(tc_core, test_add55);
  tcase_add_test(tc_core, test_add56);
  tcase_add_test(tc_core, test_add57);
  tcase_add_test(tc_core, test_add58);
  tcase_add_test(tc_core, test_add59);
  tcase_add_test(tc_core, test_add60);
  tcase_add_test(tc_core, test_add61);
  tcase_add_test(tc_core, test_add62);
  tcase_add_test(tc_core, test_add63);
  tcase_add_test(tc_core, test_add64);
  tcase_add_test(tc_core, test_add65);
  tcase_add_test(tc_core, test_add66);
  tcase_add_test(tc_core, test_add67);
  tcase_add_test(tc_core, test_add68);
  tcase_add_test(tc_core, test_add69);
  tcase_add_test(tc_core, test_add70);
  tcase_add_test(tc_core, test_add71);
  tcase_add_test(tc_core, test_add72);
  tcase_add_test(tc_core, test_add73);
  tcase_add_test(tc_core, test_add74);
  tcase_add_test(tc_core, test_add75);
  tcase_add_test(tc_core, test_add76);
  tcase_add_test(tc_core, test_add77);
  tcase_add_test(tc_core, test_add78);
  tcase_add_test(tc_core, test_add79);
  tcase_add_test(tc_core, test_add80);
  tcase_add_test(tc_core, test_add81);
  tcase_add_test(tc_core, test_add82);
  tcase_add_test(tc_core, test_add83);
  tcase_add_test(tc_core, test_add84);
  tcase_add_test(tc_core, test_add85);
  tcase_add_test(tc_core, test_add86);
  tcase_add_test(tc_core, test_add87);
  tcase_add_test(tc_core, test_add88);
  tcase_add_test(tc_core, test_add89);
  tcase_add_test(tc_core, test_add90);
  tcase_add_test(tc_core, test_add91);
  tcase_add_test(tc_core, test_add92);
  tcase_add_test(tc_core, test_add93);
  tcase_add_test(tc_core, test_add94);
  tcase_add_test(tc_core, test_add95);
  tcase_add_test(tc_core, test_add96);
  tcase_add_test(tc_core, test_add97);
  tcase_add_test(tc_core, test_add98);
  tcase_add_test(tc_core, test_add99);
  tcase_add_test(tc_core, test_add100);
  tcase_add_test(tc_core, test_add101);
  tcase_add_test(tc_core, test_add102);
  tcase_add_test(tc_core, test_add103);
  tcase_add_test(tc_core, test_add104);
  tcase_add_test(tc_core, test_add105);
  tcase_add_test(tc_core, test_add106);
  tcase_add_test(tc_core, test_add107);
  tcase_add_test(tc_core, test_add108);
  tcase_add_test(tc_core, test_add109);
  tcase_add_test(tc_core, test_add110);
  tcase_add_test(tc_core, test_add111);
  tcase_add_test(tc_core, test_add112);
  tcase_add_test(tc_core, test_add113);
  tcase_add_test(tc_core, test_add114);
  tcase_add_test(tc_core, test_add115);
  tcase_add_test(tc_core, test_add116);
  tcase_add_test(tc_core, test_add117);
  tcase_add_test(tc_core, test_add118);
  tcase_add_test(tc_core, test_add119);
  tcase_add_test(tc_core, test_add120);
  tcase_add_test(tc_core, test_add121);
  tcase_add_test(tc_core, test_add122);
  tcase_add_test(tc_core, test_add123);
  tcase_add_test(tc_core, test_add124);
  tcase_add_test(tc_core, test_add125);
  tcase_add_test(tc_core, test_add126);
  tcase_add_test(tc_core, test_add127);
  tcase_add_test(tc_core, test_add128);
  tcase_add_test(tc_core, test_add129);
  tcase_add_test(tc_core, test_add130);
  tcase_add_test(tc_core, test_add131);
  tcase_add_test(tc_core, test_add132);
  tcase_add_test(tc_core, test_add133);
  tcase_add_test(tc_core, test_add134);
  tcase_add_test(tc_core, test_add135);
  tcase_add_test(tc_core, test_add136);
  tcase_add_test(tc_core, test_add137);
  tcase_add_test(tc_core, test_add138);
  tcase_add_test(tc_core, test_add139);
  tcase_add_test(tc_core, test_add140);
  tcase_add_test(tc_core, test_add141);
  tcase_add_test(tc_core, test_add142);
  tcase_add_test(tc_core, test_add143);
  tcase_add_test(tc_core, test_add144);
  tcase_add_test(tc_core, test_add145);
  tcase_add_test(tc_core, test_add146);
  tcase_add_test(tc_core, test_add147);
  tcase_add_test(tc_core, test_add148);
  tcase_add_test(tc_core, test_add149);
  tcase_add_test(tc_core, test_add150);
  tcase_add_test(tc_core, test_add151);
  tcase_add_test(tc_core, test_add152);
  tcase_add_test(tc_core, test_add153);
  tcase_add_test(tc_core, test_add154);
  tcase_add_test(tc_core, test_add155);
  tcase_add_test(tc_core, test_add156);
  tcase_add_test(tc_core, test_add157);
  tcase_add_test(tc_core, test_add158);
  tcase_add_test(tc_core, test_add159);
  tcase_add_test(tc_core, test_add160);
  tcase_add_test(tc_core, test_add161);
  tcase_add_test(tc_core, test_add162);
  tcase_add_test(tc_core, test_add163);
  tcase_add_test(tc_core, test_add164);
  tcase_add_test(tc_core, test_add165);
  tcase_add_test(tc_core, test_add166);
  tcase_add_test(tc_core, test_add167);
  tcase_add_test(tc_core, test_add168);
  tcase_add_test(tc_core, test_add169);
  tcase_add_test(tc_core, test_add170);
  tcase_add_test(tc_core, test_add171);
  tcase_add_test(tc_core, test_add172);
  tcase_add_test(tc_core, test_add173);
  tcase_add_test(tc_core, test_add174);
  tcase_add_test(tc_core, test_add175);
  tcase_add_test(tc_core, test_add176);
  tcase_add_test(tc_core, test_add177);
  tcase_add_test(tc_core, test_add178);
  tcase_add_test(tc_core, test_add179);
  tcase_add_test(tc_core, test_add180);
  tcase_add_test(tc_core, test_add181);
  tcase_add_test(tc_core, test_add182);
  tcase_add_test(tc_core, test_add183);
  tcase_add_test(tc_core, test_add184);
  tcase_add_test(tc_core, test_add185);
  tcase_add_test(tc_core, test_add186);
  tcase_add_test(tc_core, test_add187);
  tcase_add_test(tc_core, test_add188);
  tcase_add_test(tc_core, test_add189);
  tcase_add_test(tc_core, test_add190);
  tcase_add_test(tc_core, test_add191);
  tcase_add_test(tc_core, test_add192);
  tcase_add_test(tc_core, test_add193);
  tcase_add_test(tc_core, test_add194);
  tcase_add_test(tc_core, test_add195);
  tcase_add_test(tc_core, test_add196);
  tcase_add_test(tc_core, test_add197);
  tcase_add_test(tc_core, test_add198);
  tcase_add_test(tc_core, test_add199);
  tcase_add_test(tc_core, test_add200);
  tcase_add_test(tc_core, test_add201);
  tcase_add_test(tc_core, test_add202);
  tcase_add_test(tc_core, test_add203);
  tcase_add_test(tc_core, test_add204);
  tcase_add_test(tc_core, test_add205);
  tcase_add_test(tc_core, test_add206);
  tcase_add_test(tc_core, test_add207);
  tcase_add_test(tc_core, test_add208);
  tcase_add_test(tc_core, test_add209);
  tcase_add_test(tc_core, test_add210);
  tcase_add_test(tc_core, test_add211);
  tcase_add_test(tc_core, test_add212);
  tcase_add_test(tc_core, test_add213);
  tcase_add_test(tc_core, test_add214);
  tcase_add_test(tc_core, test_add215);
  tcase_add_test(tc_core, test_add216);
  tcase_add_test(tc_core, test_add217);
  tcase_add_test(tc_core, test_add218);
  tcase_add_test(tc_core, test_add219);
  tcase_add_test(tc_core, test_add220);
  tcase_add_test(tc_core, test_add221);
  tcase_add_test(tc_core, test_add222);
  tcase_add_test(tc_core, test_add223);
  tcase_add_test(tc_core, test_add224);
  tcase_add_test(tc_core, test_add225);
  tcase_add_test(tc_core, test_add226);
  tcase_add_test(tc_core, test_add227);
  tcase_add_test(tc_core, test_add228);
  tcase_add_test(tc_core, test_add229);
  tcase_add_test(tc_core, test_add230);
  tcase_add_test(tc_core, test_add231);
  tcase_add_test(tc_core, test_add232);
  tcase_add_test(tc_core, test_add233);
  tcase_add_test(tc_core, test_add234);
  tcase_add_test(tc_core, test_add235);
  tcase_add_test(tc_core, test_add236);
  tcase_add_test(tc_core, test_add237);
  tcase_add_test(tc_core, test_add238);
  tcase_add_test(tc_core, test_add239);
  tcase_add_test(tc_core, test_add240);
  tcase_add_test(tc_core, test_add241);
  tcase_add_test(tc_core, test_add242);
  tcase_add_test(tc_core, test_add243);
  tcase_add_test(tc_core, test_add244);
  tcase_add_test(tc_core, test_add245);
  tcase_add_test(tc_core, test_add246);
  tcase_add_test(tc_core, test_add247);
  tcase_add_test(tc_core, test_add248);
  tcase_add_test(tc_core, test_add249);
  tcase_add_test(tc_core, test_add250);
  tcase_add_test(tc_core, test_add251);
  tcase_add_test(tc_core, test_add252);
  tcase_add_test(tc_core, test_add253);
  tcase_add_test(tc_core, test_add254);
  tcase_add_test(tc_core, test_add255);
  tcase_add_test(tc_core, test_add256);
  tcase_add_test(tc_core, test_add257);
  tcase_add_test(tc_core, test_add258);
  tcase_add_test(tc_core, test_add259);
  tcase_add_test(tc_core, test_add260);
  tcase_add_test(tc_core, test_add261);
  tcase_add_test(tc_core, test_add262);
  tcase_add_test(tc_core, test_add263);
  tcase_add_test(tc_core, test_add264);
  tcase_add_test(tc_core, test_add265);
  tcase_add_test(tc_core, test_add266);
  tcase_add_test(tc_core, test_add267);
  tcase_add_test(tc_core, test_add268);
  tcase_add_test(tc_core, test_add269);
  tcase_add_test(tc_core, test_add270);
  tcase_add_test(tc_core, test_add271);
  tcase_add_test(tc_core, test_add272);
  tcase_add_test(tc_core, test_add273);
  tcase_add_test(tc_core, test_add274);
  tcase_add_test(tc_core, test_add275);
  tcase_add_test(tc_core, test_add276);
  tcase_add_test(tc_core, test_add277);
  tcase_add_test(tc_core, test_add278);
  tcase_add_test(tc_core, test_add279);
  tcase_add_test(tc_core, test_add280);
  tcase_add_test(tc_core, test_add281);
  tcase_add_test(tc_core, test_add282);
  tcase_add_test(tc_core, test_add283);
  tcase_add_test(tc_core, test_add284);
  tcase_add_test(tc_core, test_add285);
  tcase_add_test(tc_core, test_add286);
  tcase_add_test(tc_core, test_add287);
  tcase_add_test(tc_core, test_add288);
  tcase_add_test(tc_core, test_add289);
  tcase_add_test(tc_core, test_add290);
  tcase_add_test(tc_core, test_add291);
  tcase_add_test(tc_core, test_add292);
  tcase_add_test(tc_core, test_add293);
  tcase_add_test(tc_core, test_add294);
  tcase_add_test(tc_core, test_add295);
  tcase_add_test(tc_core, test_add296);
  tcase_add_test(tc_core, test_add297);
  tcase_add_test(tc_core, test_add298);
  tcase_add_test(tc_core, test_add299);
  tcase_add_test(tc_core, test_add300);
  tcase_add_test(tc_core, test_add301);
  tcase_add_test(tc_core, test_add302);
  tcase_add_test(tc_core, test_add303);
  tcase_add_test(tc_core, test_add304);
  tcase_add_test(tc_core, test_add305);
  tcase_add_test(tc_core, test_add306);
  tcase_add_test(tc_core, test_add307);
  tcase_add_test(tc_core, test_add308);
  tcase_add_test(tc_core, test_add309);
  tcase_add_test(tc_core, test_add310);
  tcase_add_test(tc_core, test_add311);
  tcase_add_test(tc_core, test_add312);
  tcase_add_test(tc_core, test_add313);
  tcase_add_test(tc_core, test_add314);
  tcase_add_test(tc_core, test_add315);
  tcase_add_test(tc_core, test_add316);
  tcase_add_test(tc_core, test_add317);
  tcase_add_test(tc_core, test_add318);
  tcase_add_test(tc_core, test_add319);
  tcase_add_test(tc_core, test_add320);
  tcase_add_test(tc_core, test_add321);
  tcase_add_test(tc_core, test_add322);
  tcase_add_test(tc_core, test_add323);
  tcase_add_test(tc_core, test_add324);
  tcase_add_test(tc_core, test_add325);
  tcase_add_test(tc_core, test_add326);
  tcase_add_test(tc_core, test_add327);
  tcase_add_test(tc_core, test_add328);
  tcase_add_test(tc_core, test_add329);
  tcase_add_test(tc_core, test_add330);
  tcase_add_test(tc_core, test_add331);
  tcase_add_test(tc_core, test_add332);
  tcase_add_test(tc_core, test_add333);
  tcase_add_test(tc_core, test_add334);
  tcase_add_test(tc_core, test_add335);
  tcase_add_test(tc_core, test_add336);
  tcase_add_test(tc_core, test_add337);
  tcase_add_test(tc_core, test_add338);
  tcase_add_test(tc_core, test_add339);
  tcase_add_test(tc_core, test_add340);
  tcase_add_test(tc_core, test_add341);
  tcase_add_test(tc_core, test_add342);
  tcase_add_test(tc_core, test_add343);
  tcase_add_test(tc_core, test_add344);
  tcase_add_test(tc_core, test_add345);
  tcase_add_test(tc_core, test_add346);
  tcase_add_test(tc_core, test_add347);
  tcase_add_test(tc_core, test_add348);
  tcase_add_test(tc_core, test_add349);
  tcase_add_test(tc_core, test_add350);
  tcase_add_test(tc_core, test_add351);
  tcase_add_test(tc_core, test_add352);
  tcase_add_test(tc_core, test_add353);
  tcase_add_test(tc_core, test_add354);
  tcase_add_test(tc_core, test_add355);
  tcase_add_test(tc_core, test_add356);
  tcase_add_test(tc_core, test_add357);
  tcase_add_test(tc_core, test_add358);
  tcase_add_test(tc_core, test_add359);
  tcase_add_test(tc_core, test_add360);
  tcase_add_test(tc_core, test_add361);
  tcase_add_test(tc_core, test_add362);
  tcase_add_test(tc_core, test_add363);
  tcase_add_test(tc_core, test_add364);
  tcase_add_test(tc_core, test_add365);
  tcase_add_test(tc_core, test_add366);
  tcase_add_test(tc_core, test_add367);
  tcase_add_test(tc_core, test_add368);
  tcase_add_test(tc_core, test_add369);
  tcase_add_test(tc_core, test_add370);
  tcase_add_test(tc_core, test_add371);
  tcase_add_test(tc_core, test_add372);
  tcase_add_test(tc_core, test_add373);
  tcase_add_test(tc_core, test_add374);
  tcase_add_test(tc_core, test_add375);
  tcase_add_test(tc_core, test_add376);
  tcase_add_test(tc_core, test_add377);
  tcase_add_test(tc_core, test_add378);
  tcase_add_test(tc_core, test_add379);
  tcase_add_test(tc_core, test_add380);
  tcase_add_test(tc_core, test_add381);
  tcase_add_test(tc_core, test_add382);
  tcase_add_test(tc_core, test_add383);
  tcase_add_test(tc_core, test_add384);
  tcase_add_test(tc_core, test_add385);
  tcase_add_test(tc_core, test_add386);
  tcase_add_test(tc_core, test_add387);
  tcase_add_test(tc_core, test_add388);
  tcase_add_test(tc_core, test_add389);
  tcase_add_test(tc_core, test_add390);
  tcase_add_test(tc_core, test_add391);
  tcase_add_test(tc_core, test_add392);
  tcase_add_test(tc_core, test_add393);
  tcase_add_test(tc_core, test_add394);
  tcase_add_test(tc_core, test_add395);
  tcase_add_test(tc_core, test_add396);
  tcase_add_test(tc_core, test_add397);
  tcase_add_test(tc_core, test_add398);
  tcase_add_test(tc_core, test_add399);
  tcase_add_test(tc_core, test_add400);

  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  int number_failed;
  SRunner *sr;
  sr = srunner_create(NULL);
  srunner_add_suite(sr, div_suite());
  srunner_add_suite(sr, mul_suite());
  srunner_add_suite(sr, add_suite());
  srunner_add_suite(sr, sub_suite());
  srunner_set_fork_status(sr, CK_NOFORK);
  // Используем данный блок для вывода подробно про каждый тест с разбиением по
  // блокам srunner_set_log(sr, "-"); srunner_run_all(sr, CK_SILENT);  //
  // CK_SILENT || CK_MINIMAL || CK_NORMAL || CK_VERBOSE Либо данный блок вместо
  // предыдущего для вывода только ошибок и общего результата
  srunner_run_all(sr, CK_ENV);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void test_add(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result), res_eq = 1;
  if (!s21_is_zero_val(result) && !s21_is_zero_val(check)) {
    for (int i = 0; i < 4; ++i) {
      if (result.bits[i] != check.bits[i]) {
        res_eq = 0;
      }
    }
  }
  if (res_eq == 0) {
    printf("check:\n");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(check, i));
    }
    printf("\nresult:\n");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(result, i));
    }
    printf("\n\n");
  }
  ck_assert_int_eq(res_eq, 1);
  ck_assert_int_eq(code, 0);
}

void test_add_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}

void test_mul(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  if (s21_is_equal_hand(result, check) == 0) {
    printf("---------------------------------------\n");
    printf("result:\n");
    s21_print_fail(result);
    printf("\ncheck:\n");
    s21_print_fail(check);
    printf("---------------------------------------");
    printf("\n\n");
  }
  ck_assert_int_eq(s21_is_equal_hand(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_mul_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
}

void test_mul_fail2(s21_decimal decimal1, s21_decimal decimal2,
                    s21_decimal decimal_check, int code_check) {
  s21_decimal result;
  int code = s21_mul(decimal1, decimal2, &result);
  ck_assert_int_eq(code, code_check);
  ck_assert_int_eq(s21_is_equal_hand(result, decimal_check), 1);
}

void test_div(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result), res_eq = 1;
  if (s21_is_equal_hand_div(&result, &check) == 0) {
    printf("---------------------------------------\n");
    printf("result:\n");
    s21_print_fail(result);
    printf("\ncheck:\n");
    s21_print_fail(check);
    printf("---------------------------------------");
    printf("\n\n");
    res_eq = 0;
  }
  ck_assert_int_eq(res_eq, 1);
  ck_assert_int_eq(code, 0);
}

void test_sub_fail(s21_decimal decimal1, s21_decimal decimal2, int check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  ck_assert_int_eq(code, check);
}

void test_sub(s21_decimal decimal1, s21_decimal decimal2, s21_decimal check) {
  s21_decimal result;
  int code = s21_sub(decimal1, decimal2, &result);
  if (s21_is_equal_hand(result, check) == 0) {
    printf("---------------------------------------\n");
    printf("result:\n");
    s21_print_fail(result);
    printf("\ncheck:\n");
    s21_print_fail(check);
    printf("---------------------------------------");
    printf("\n\n");
  }
  ck_assert_int_eq(s21_is_equal_hand(result, check), 1);
  ck_assert_int_eq(code, 0);
}

void test_div_fail1(s21_decimal decimal1, s21_decimal decimal2,
                    int code_check) {
  s21_decimal result;
  int code = s21_div(decimal1, decimal2, &result);

  ck_assert_int_eq(code, code_check);
}

int s21_is_equal_hand(s21_decimal x, s21_decimal y) {
  int result = 1, flag_null = 1;
  for (int i = 0; i < 3; ++i) {
    if (!(x.bits[i] == 0 && y.bits[i] == 0)) {
      flag_null = 0;
      break;
    }
  }
  if (!flag_null) {
    for (int i = 0; i < 4; ++i) {
      if (x.bits[i] != y.bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}

int s21_is_equal_hand_div(s21_decimal *x, s21_decimal *y) {
  int result = 1, flag_null = 1;
  for (int i = 0; i < 3; ++i) {
    if (!(x->bits[i] == 0 && y->bits[i] == 0)) {
      flag_null = 0;
      break;
    }
  }
  if (!flag_null) {
    s21_toTheSameExp_hand(x, y);
    for (int i = 0; i < 4; ++i) {
      if (x->bits[i] != y->bits[i]) {
        result = 0;
      }
    }
  }
  return result;
}

void s21_print_fail(s21_decimal x) {
  for (int i = 127; i >= 0; --i) {
    printf("%d", s21_getBit(x, i));
  }
  printf("\n");
}

s21_decimal s21_Big_add_binary_hand(
    s21_decimal value_1,
    s21_decimal value_2) {  // val_1 & val_2 positive
  s21_decimal result = s21_get_zero();
  int temp = 0;
  for (int i = 0; i < 96; ++i) {
    int bit1 = s21_getBit(value_1, i);
    int bit2 = s21_getBit(value_2, i);
    int sum = bit1 + bit2 + temp;
    if (sum > 1) {
      temp = 1;
      s21_setBit(&result, i, sum - 2);
    } else {
      temp = 0;
      s21_setBit(&result, i, sum);
    }
  }
  result.bits[3] = value_1.bits[3];
  return result;
}

int s21_toTheSameExp_hand(s21_decimal *value_1, s21_decimal *value_2) {
  int exp_1 = 0, exp_2 = 0, power_2 = 1, diff;
  for (int i = 16; i < 24; ++i) {
    exp_1 += s21_getBit(*value_1, i + 96) * power_2;
    exp_2 += s21_getBit(*value_2, i + 96) * power_2;
    power_2 *= 2;
  }
  int res_exp = exp_1;
  if (exp_1 > exp_2) {
    diff = exp_1 - exp_2;
    for (int i = 0; i < diff; ++i) {
      s21_mul_by_ten_hand(value_2);
    }
  } else if (exp_2 > exp_1) {
    res_exp = exp_2;
    diff = exp_2 - exp_1;
    for (int i = 0; i < diff; ++i) {
      s21_mul_by_ten_hand(value_1);
    }
  }
  return res_exp;
}

void s21_mul_by_ten_hand(s21_decimal *value) {
  s21_decimal temp_val = *value;
  *value = s21_shift(*value, 3, 1);
  temp_val = s21_shift(temp_val, 1, 1);
  *value = s21_Big_add_binary_hand(*value, temp_val);
  for (int i = 16; i < 24; ++i) {
    int temp = s21_getBit(*value, i + 96);
    if (temp == 1) {
      s21_setBit(value, i + 96, 0);
    } else {
      s21_setBit(value, i + 96, 1);
      break;
    }
  }
}

int s21_is_zero_val(s21_decimal val) {
  int res = 1;
  for (int i = 0; i < 3; ++i) {
    if (val.bits[i] != 0) {
      res = 0;
    }
  }
  return res;
}

s21_decimal s21_shift(s21_decimal value, int times, int direction) {
  s21_decimal temp = value;
  if (times != 0) {
    if (direction == 1) {
      if (times < 32) {
        value.bits[0] = value.bits[0] << times;
      } else {
        value.bits[0] = 0;
      }
      for (int i = 1; i < 3; ++i) {
        if (times < 32) {
          value.bits[i] = value.bits[i] << times;
        } else {
          value.bits[i] = 0;
        }
        for (int j = 0; j < times; ++j) {
          int set_index = j + i * 32;
          int get_index = i * 32 - times + j;
          if ((set_index < 96) && (get_index >= 0)) {
            s21_setBit(&value, j + i * 32,
                       s21_getBit(temp, i * 32 - times + j));
          }
        }
      }
    } else if (direction == 2) {
      value.bits[2] = value.bits[2] >> times;
      for (int i = 1; i >= 0; --i) {
        value.bits[i] = value.bits[i] >> times;
        for (int j = 0; j < times; ++j) {
          s21_setBit(&value, (i + 1) * 32 - j - 1,
                     s21_getBit(temp, (i + 1) * 32 + times - j - 1));
        }
      }
    }
  }
  return value;
}