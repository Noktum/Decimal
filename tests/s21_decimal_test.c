#include "s21_decimal_test.h"

int s21_is_zero_val(s21_decimal val);
void s21_mul_by_ten_hand(s21_decimal *value);
int s21_toTheSameExp_hand(s21_decimal *value_1, s21_decimal *value_2);
s21_decimal s21_Big_add_binary_hand(s21_decimal value_1, s21_decimal value_2);
void s21_print_fail(s21_decimal x);
int s21_is_equal_hand_div(s21_decimal *x, s21_decimal *y);
int s21_is_equal_hand(s21_decimal x, s21_decimal y);
s21_decimal s21_shift(s21_decimal value, int times, int direction);

void run_tests(fail *fails) {
  Suite *list_cases[] = {

      suite_from_int_to_decimal(), suite_from_float_to_decimal(),
      suite_from_decimal_to_int(), suite_from_decimal_to_float(),

      NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase, fails);
  }
}

void run_testcase(Suite *testcase, fail *fails) {
  int failed = 0;
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed += srunner_ntests_failed(sr);
  fails->fails += failed;
  srunner_free(sr);
  // sleep(1);
  if (!failed) {
    printf("========= \033[32mPASSED\033[0m =========\n");
  } else {
    printf("========= \033[31mFAILED: %d\033[0m =========\n", failed);
  }
}

int main(void) {
  fail fails;
  fails.fails = 0;
  run_tests(&fails);
  printf("\n\n");
  if (!fails.fails) {
    printf("============ \033[32mALL PASSED\033[0m ============\n");
  } else {
    printf("============ \033[31mALL FAILED: %d\033[0m ============\n",
           fails.fails);
  }
  return 0;
}

void test_from_decimal_to_float(s21_decimal decimal, float check) {
  float result = 0;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

///

START_TEST(test_from_decimal_to_float_fail_manual1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_float(decimal, NULL);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}

START_TEST(test_from_decimal_to_float_fail_manual2) {
  // степень 154 (показатель степени должен быть от 0 до 28)
  // биты 0-15 не нули
  // биты 24-30 не нули
  s21_decimal decimal = {{0, 0, 0, 1000000000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual3) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual4) {
  // степень 29 (показатель степени должен быть от 0 до 28)
  s21_decimal decimal = {{0, 0, 0, 0x1D0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual5) {
  // степень 28 (что корректно), но биты 0-15 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C0001}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual6) {
  // степень 28 (что корректно), но биты 0-15 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x1C8000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual7) {
  // степень 28 (что корректно), но биты 24-30 не нули (младший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x11C0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual8) {
  // степень 28 (что корректно), но биты 24-30 не нули (старший бит)
  s21_decimal decimal = {{-1, 0, 0, 0x401C0000}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_decimal_to_float_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  float result;
  int code = s21_from_decimal_to_float(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

///

START_TEST(test_from_decimal_to_float_ok1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  float check = 79228162514264337593543950335.0;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  float check = -79228162514264337593543950335.0;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};
  float check = 7922816251426433759354395033.5;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};
  float check = -7922816251426433759354395033.5;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok5) {
  // 20995463066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x0}};
  float check = 20995463066280049462289146839.0;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok6) {
  // -20995463066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80000000}};
  float check = -20995463066280049462289146839.0;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok7) {
  // 792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x20000}};
  float check = 792281625142643375935439503.35;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok8) {
  // -792281625142643375935439503.35
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80020000}};
  float check = -792281625142643375935439503.35;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok9) {
  // 2099546306628004946228914683.9
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x10000}};
  float check = 2099546306628004946228914683.9;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok10) {
  // -2099546306628004946228914683.9
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80010000}};
  float check = -2099546306628004946228914683.9;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok11) {
  // 79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x30000}};
  float check = 79228162514264337593543950.335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok12) {
  // -79228162514264337593543950.335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80030000}};
  float check = -79228162514264337593543950.335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok13) {
  // 209954630662800494622891468.39
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x20000}};
  float check = 209954630662800494622891468.39;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok14) {
  // -209954630662800494622891468.39
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80020000}};
  float check = -209954630662800494622891468.39;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok15) {
  // 7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x40000}};
  float check = 7922816251426433759354395.0335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok16) {
  // -7922816251426433759354395.0335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80040000}};
  float check = -7922816251426433759354395.0335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok17) {
  // 20995463066280049462289146.839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x30000}};
  float check = 20995463066280049462289146.839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok18) {
  // -20995463066280049462289146.839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80030000}};
  float check = -20995463066280049462289146.839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok19) {
  // 792281625142643375935439.50335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x50000}};
  float check = 792281625142643375935439.50335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok20) {
  // -792281625142643375935439.50335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80050000}};
  float check = -792281625142643375935439.50335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok21) {
  // 2099546306628004946228914.6839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x40000}};
  float check = 2099546306628004946228914.6839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok22) {
  // -2099546306628004946228914.6839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80040000}};
  float check = -2099546306628004946228914.6839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok23) {
  // 79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x60000}};
  float check = 79228162514264337593543.950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok24) {
  // -79228162514264337593543.950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80060000}};
  float check = -79228162514264337593543.950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok25) {
  // 209954630662800494622891.46839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x50000}};
  float check = 209954630662800494622891.46839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok26) {
  // -209954630662800494622891.46839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80050000}};
  float check = -209954630662800494622891.46839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok27) {
  // 7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x70000}};
  float check = 7922816251426433759354.3950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok28) {
  // -7922816251426433759354.3950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80070000}};
  float check = -7922816251426433759354.3950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok29) {
  // 20995463066280049462289.146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x60000}};
  float check = 20995463066280049462289.146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok30) {
  // -20995463066280049462289.146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80060000}};
  float check = -20995463066280049462289.146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok31) {
  // 792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000}};
  float check = 792281625142643375935.43950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok32) {
  // -792281625142643375935.43950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80080000}};
  float check = -792281625142643375935.43950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok33) {
  // 2099546306628004946228.9146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x70000}};
  float check = 2099546306628004946228.9146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok34) {
  // -2099546306628004946228.9146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80070000}};
  float check = -2099546306628004946228.9146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok35) {
  // 79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x90000}};
  float check = 79228162514264337593.543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok36) {
  // -79228162514264337593.543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80090000}};
  float check = -79228162514264337593.543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok37) {
  // 209954630662800494622.89146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80000}};
  float check = 209954630662800494622.89146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok38) {
  // -209954630662800494622.89146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80080000}};
  float check = -209954630662800494622.89146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok39) {
  // 7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xA0000}};
  float check = 7922816251426433759.3543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok40) {
  // -7922816251426433759.3543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800A0000}};
  float check = -7922816251426433759.3543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok41) {
  // 20995463066280049462.289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x90000}};
  float check = 20995463066280049462.289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok42) {
  // -20995463066280049462.289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80090000}};
  float check = -20995463066280049462.289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok43) {
  // 792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xB0000}};
  float check = 792281625142643375.93543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok44) {
  // -792281625142643375.93543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800B0000}};
  float check = -792281625142643375.93543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok45) {
  // 2099546306628004946.2289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xA0000}};
  float check = 2099546306628004946.2289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok46) {
  // -2099546306628004946.2289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800A0000}};
  float check = -2099546306628004946.2289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok47) {
  // 79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0000}};
  float check = 79228162514264337.593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok48) {
  // -79228162514264337.593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800C0000}};
  float check = -79228162514264337.593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok49) {
  // 209954630662800494.62289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xB0000}};
  float check = 209954630662800494.62289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok50) {
  // -209954630662800494.62289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800B0000}};
  float check = -209954630662800494.62289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok51) {
  // 7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xD0000}};
  float check = 7922816251426433.7593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok52) {
  // -7922816251426433.7593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800D0000}};
  float check = -7922816251426433.7593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok53) {
  // 20995463066280049.462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xC0000}};
  float check = 20995463066280049.462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok54) {
  // -20995463066280049.462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800C0000}};
  float check = -20995463066280049.462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok55) {
  // 792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xE0000}};
  float check = 792281625142643.37593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok56) {
  // -792281625142643.37593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800E0000}};
  float check = -792281625142643.37593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok57) {
  // 2099546306628004.9462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xD0000}};
  float check = 2099546306628004.9462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok58) {
  // -2099546306628004.9462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800D0000}};
  float check = -2099546306628004.9462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok59) {
  // 79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xF0000}};
  float check = 79228162514264.337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok60) {
  // -79228162514264.337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x800F0000}};
  float check = -79228162514264.337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok61) {
  // 209954630662800.49462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xE0000}};
  float check = 209954630662800.49462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok62) {
  // -209954630662800.49462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800E0000}};
  float check = -209954630662800.49462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok63) {
  // 7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x100000}};
  float check = 7922816251426.4337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok64) {
  // -7922816251426.4337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80100000}};
  float check = -7922816251426.4337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok65) {
  // 20995463066280.049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0xF0000}};
  float check = 20995463066280.049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok66) {
  // -20995463066280.049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x800F0000}};
  float check = -20995463066280.049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok67) {
  // 792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x110000}};
  float check = 792281625142.64337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok68) {
  // -792281625142.64337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80110000}};
  float check = -792281625142.64337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok69) {
  // 2099546306628.0049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x100000}};
  float check = 2099546306628.0049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok70) {
  // -2099546306628.0049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80100000}};
  float check = -2099546306628.0049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok71) {
  // 79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x120000}};
  float check = 79228162514.264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok72) {
  // -79228162514.264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80120000}};
  float check = -79228162514.264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok73) {
  // 209954630662.80049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x110000}};
  float check = 209954630662.80049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok74) {
  // -209954630662.80049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80110000}};
  float check = -209954630662.80049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok75) {
  // 7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x130000}};
  float check = 7922816251.4264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok76) {
  // -7922816251.4264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80130000}};
  float check = -7922816251.4264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok77) {
  // 20995463066.280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x120000}};
  float check = 20995463066.280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok78) {
  // -20995463066.280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80120000}};
  float check = -20995463066.280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok79) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  float check = 792281625.14264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok80) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  float check = -792281625.14264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok81) {
  // 2099546306.6280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x130000}};
  float check = 2099546306.6280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok82) {
  // -2099546306.6280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80130000}};
  float check = -2099546306.6280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok83) {
  // 79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
  float check = 79228162.514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok84) {
  // -79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
  float check = -79228162.514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok85) {
  // 209954630.66280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x140000}};
  float check = 209954630.66280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok86) {
  // -209954630.66280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80140000}};
  float check = -209954630.66280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok87) {
  // 7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x160000}};
  float check = 7922816.2514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok88) {
  // -7922816.2514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80160000}};
  float check = -7922816.2514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok89) {
  // 20995463.066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x150000}};
  float check = 20995463.066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok90) {
  // -20995463.066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80150000}};
  float check = -20995463.066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok91) {
  // 792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x170000}};
  float check = 792281.62514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok92) {
  // -792281.62514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80170000}};
  float check = -792281.62514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok93) {
  // 2099546.3066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x160000}};
  float check = 2099546.3066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok94) {
  // -2099546.3066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80160000}};
  float check = -2099546.3066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok95) {
  // 79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x180000}};
  float check = 79228.162514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok96) {
  // -79228.162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80180000}};
  float check = -79228.162514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok97) {
  // 209954.63066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x170000}};
  float check = 209954.63066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok98) {
  // -209954.63066280049462289146839
  s21_decimal decimal = {{0x3D70A3D7, 0x70A3D70A, 0x43D70A3D, 0x80170000}};
  float check = -209954.63066280049462289146839;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok99) {
  // 7922.8162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x190000}};
  float check = 7922.8162514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

START_TEST(test_from_decimal_to_float_ok100) {
  // -7922.8162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80190000}};
  float check = -7922.8162514264337593543950335;

  test_from_decimal_to_float(decimal, check);
}

Suite *suite_from_decimal_to_float(void) {
  Suite *s =
      suite_create("\033[45m-=S21_suite_from_decimal_to_float_mini=-\033[0m");
  TCase *tc_core = tcase_create("case_from_decimal_to_float_mini");

  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual1);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual2);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual3);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual4);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual5);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual6);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual7);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual8);
  tcase_add_test(tc_core, test_from_decimal_to_float_fail_manual9);

  tcase_add_test(tc_core, test_from_decimal_to_float_ok1);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok2);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok3);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok4);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok5);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok6);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok7);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok8);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok9);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok10);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok11);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok12);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok13);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok14);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok15);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok16);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok17);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok18);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok19);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok20);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok21);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok22);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok23);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok24);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok25);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok26);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok27);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok28);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok29);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok30);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok31);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok32);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok33);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok34);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok35);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok36);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok37);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok38);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok39);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok40);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok41);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok42);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok43);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok44);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok45);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok46);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok47);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok48);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok49);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok50);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok51);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok52);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok53);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok54);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok55);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok56);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok57);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok58);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok59);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok60);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok61);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok62);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok63);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok64);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok65);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok66);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok67);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok68);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok69);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok70);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok71);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok72);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok73);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok74);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok75);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok76);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok77);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok78);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok79);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok80);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok81);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok82);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok83);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok84);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok85);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok86);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok87);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok88);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok89);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok90);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok91);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok92);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok93);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok94);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok95);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok96);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok97);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok98);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok99);
  tcase_add_test(tc_core, test_from_decimal_to_float_ok100);

  suite_add_tcase(s, tc_core);
  return s;
}

void tests_from_decimal_to_int(s21_decimal decimal, int check) {
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(result, check);
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
}

void tests_from_decimal_to_int_fail(s21_decimal decimal) {
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}

START_TEST(tests_from_decimal_to_int_fail_manual9) {
  // Просто все единицы
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

/////

START_TEST(tests_from_decimal_to_int_ok1) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int check = 792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok2) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  int check = -792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok3) {
  // 79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x150000}};
  int check = 79228162;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok4) {
  // -79228162.514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80150000}};
  int check = -79228162;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok5) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int check = 7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok6) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int check = -7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok7) {
  // 528187750.09509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x140000}};
  int check = 528187750;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok8) {
  // -528187750.09509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80140000}};
  int check = -528187750;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok9) {
  // 5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x1C0000}};
  int check = 5;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok10) {
  // -5.2818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x801C0000}};
  int check = -5;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok11) {
  // 286331153.0
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x10000}};
  int check = 286331153;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok12) {
  // -286331153.0
  s21_decimal decimal = {{0xAAAAAAAA, 0x0, 0x0, 0x80010000}};
  int check = -286331153;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok13) {
  // 429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x10000}};
  int check = 429496729;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok14) {
  // -429496729.7
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80010000}};
  int check = -429496729;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok15) {
  // 1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x0}};
  int check = 1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok16) {
  // -1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80000000}};
  int check = -1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok17) {
  // 0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x10000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok18) {
  // -0.1
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x80010000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok19) {
  // 0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x1C0000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok20) {
  // -0.0000000000000000000000000001
  s21_decimal decimal = {{0x1, 0x0, 0x0, 0x801C0000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok21) {
  // -2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok22) {
  // 214748364.8
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x10000}};
  int check = 214748364;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok23) {
  // -214748364.8
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80010000}};
  int check = -214748364;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok24) {
  // 8460288
  s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x0}};
  int check = 8460288;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok25) {
  // -8460288
  s21_decimal decimal = {{0x811800, 0x0, 0x0, 0x80000000}};
  int check = -8460288;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok26) {
  // 792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int check = 792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok27) {
  // -792281625.14264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80140000}};
  int check = -792281625;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok28) {
  // 7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x1C0000}};
  int check = 7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok29) {
  // -7.9228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int check = -7;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok30) {
  // 1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x10000}};
  int check = 1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok31) {
  // -1.0
  s21_decimal decimal = {{0xA, 0x0, 0x0, 0x80010000}};
  int check = -1;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok32) {
  // 99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x20000}};
  int check = 99;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok33) {
  // -99.99
  s21_decimal decimal = {{0x270F, 0x0, 0x0, 0x80020000}};
  int check = -99;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok34) {
  // -0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80000000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok35) {
  // 0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x0}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok36) {
  // -0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x80010000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok37) {
  // 0.0
  s21_decimal decimal = {{0x0, 0x0, 0x0, 0x10000}};
  int check = 0;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok38) {
  // 2147483647
  s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};
  int check = 2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok39) {
  // -2147483647
  s21_decimal decimal = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};
  int check = -2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok40) {
  // 2147483647.00
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x20000}};
  int check = 2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok41) {
  // -2147483647.00
  s21_decimal decimal = {{0xFFFFFF9C, 0x31, 0x0, 0x80020000}};
  int check = -2147483647;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok42) {
  // -2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80000000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok43) {
  // -2147483648.00
  s21_decimal decimal = {{0x0, 0x32, 0x0, 0x80020000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok44) {
  // -2147483648.99
  s21_decimal decimal = {{0x63, 0x32, 0x0, 0x80020000}};
  int check = -2147483648;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok45) {
  // 21474836.48
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x20000}};
  int check = 21474836;

  tests_from_decimal_to_int(decimal, check);
}

START_TEST(tests_from_decimal_to_int_ok46) {
  // -21474836.48
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x80020000}};
  int check = -21474836;

  tests_from_decimal_to_int(decimal, check);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * Tests for incorrect data (auto)
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * */

START_TEST(tests_from_decimal_to_int_fail1) {
  // 79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail2) {
  // -79228162514264337593543950335
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail3) {
  // 7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail4) {
  // -7922816251426433759354395033.5
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail5) {
  // 52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail6) {
  // -52818775009509558392832655360
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail7) {
  // 5281877500950955839283265536.0
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail8) {
  // -5281877500950955839283265536.0
  s21_decimal decimal = {{0x0, 0xAAAAAAAA, 0xAAAAAAAA, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail9) {
  // 26409387504754779196416327680
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail10) {
  // -26409387504754779196416327680
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail11) {
  // 2640938750475477919641632768.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail12) {
  // -2640938750475477919641632768.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x55555555, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail13) {
  // 26409387498605864508043122005
  s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail17) {
  // -26409387498605864508043122005
  s21_decimal decimal = {{0x55555555, 0x0, 0x55555555, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail18) {
  // 6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail19) {
  // -6148914689804861440
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail20) {
  // 614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail21) {
  // -614891468980486144.0
  s21_decimal decimal = {{0x0, 0x55555555, 0x0, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail22) {
  // 4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail23) {
  // -4294967297
  s21_decimal decimal = {{0x1, 0x1, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail24) {
  // 39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail25) {
  // -39614081266355540835774234624
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x80000000, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail26) {
  // 39614081257132168798919458816
  s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail27) {
  // -39614081257132168798919458816
  s21_decimal decimal = {{0x80000000, 0x0, 0x80000000, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail28) {
  // 9223372039002259456
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail29) {
  // -9223372039002259456
  s21_decimal decimal = {{0x80000000, 0x80000000, 0x0, 0x80000000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail30) {
  // 2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail31) {
  // 7922816251426433758924898304.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail32) {
  // -7922816251426433758924898304.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0xFFFFFFFF, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail33) {
  // 1844674406941458432.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x10000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail34) {
  // -1844674406941458432.0
  s21_decimal decimal = {{0x0, 0xFFFFFFFF, 0x0, 0x80010000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail35) {
  // 2147483648
  s21_decimal decimal = {{0x80000000, 0x0, 0x0, 0x0}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail36) {
  // 2147483648.00
  s21_decimal decimal = {{0x0, 0x32, 0x0, 0x20000}};

  tests_from_decimal_to_int_fail(decimal);
}

START_TEST(tests_from_decimal_to_int_fail37) {
  // 2147483648.99
  s21_decimal decimal = {{0x63, 0x32, 0x0, 0x20000}};

  tests_from_decimal_to_int_fail(decimal);
}

Suite *suite_from_decimal_to_int(void) {
  Suite *s = suite_create("\033[45m-=S21_from_decimal_to_int=-\033[0m");
  TCase *tc = tcase_create("case_from_int_to_decimal");
  tcase_add_test(tc, tests_from_decimal_to_int_fail_manual9);
  ///

  tcase_add_test(tc, tests_from_decimal_to_int_ok1);
  tcase_add_test(tc, tests_from_decimal_to_int_ok2);
  tcase_add_test(tc, tests_from_decimal_to_int_ok3);
  tcase_add_test(tc, tests_from_decimal_to_int_ok4);
  tcase_add_test(tc, tests_from_decimal_to_int_ok5);
  tcase_add_test(tc, tests_from_decimal_to_int_ok6);
  tcase_add_test(tc, tests_from_decimal_to_int_ok7);
  tcase_add_test(tc, tests_from_decimal_to_int_ok8);
  tcase_add_test(tc, tests_from_decimal_to_int_ok9);
  tcase_add_test(tc, tests_from_decimal_to_int_ok10);
  tcase_add_test(tc, tests_from_decimal_to_int_ok11);
  tcase_add_test(tc, tests_from_decimal_to_int_ok12);
  tcase_add_test(tc, tests_from_decimal_to_int_ok13);
  tcase_add_test(tc, tests_from_decimal_to_int_ok14);
  tcase_add_test(tc, tests_from_decimal_to_int_ok15);
  tcase_add_test(tc, tests_from_decimal_to_int_ok16);
  tcase_add_test(tc, tests_from_decimal_to_int_ok17);
  tcase_add_test(tc, tests_from_decimal_to_int_ok18);
  tcase_add_test(tc, tests_from_decimal_to_int_ok19);
  tcase_add_test(tc, tests_from_decimal_to_int_ok20);
  tcase_add_test(tc, tests_from_decimal_to_int_ok21);
  tcase_add_test(tc, tests_from_decimal_to_int_ok22);
  tcase_add_test(tc, tests_from_decimal_to_int_ok23);
  tcase_add_test(tc, tests_from_decimal_to_int_ok24);
  tcase_add_test(tc, tests_from_decimal_to_int_ok25);
  tcase_add_test(tc, tests_from_decimal_to_int_ok26);
  tcase_add_test(tc, tests_from_decimal_to_int_ok27);
  tcase_add_test(tc, tests_from_decimal_to_int_ok28);
  tcase_add_test(tc, tests_from_decimal_to_int_ok29);
  tcase_add_test(tc, tests_from_decimal_to_int_ok30);
  tcase_add_test(tc, tests_from_decimal_to_int_ok31);
  tcase_add_test(tc, tests_from_decimal_to_int_ok32);
  tcase_add_test(tc, tests_from_decimal_to_int_ok33);
  tcase_add_test(tc, tests_from_decimal_to_int_ok34);
  tcase_add_test(tc, tests_from_decimal_to_int_ok35);
  tcase_add_test(tc, tests_from_decimal_to_int_ok36);
  tcase_add_test(tc, tests_from_decimal_to_int_ok37);
  tcase_add_test(tc, tests_from_decimal_to_int_ok38);
  tcase_add_test(tc, tests_from_decimal_to_int_ok39);
  tcase_add_test(tc, tests_from_decimal_to_int_ok40);
  tcase_add_test(tc, tests_from_decimal_to_int_ok41);
  tcase_add_test(tc, tests_from_decimal_to_int_ok42);
  tcase_add_test(tc, tests_from_decimal_to_int_ok43);
  tcase_add_test(tc, tests_from_decimal_to_int_ok44);
  tcase_add_test(tc, tests_from_decimal_to_int_ok45);
  tcase_add_test(tc, tests_from_decimal_to_int_ok46);
  ///
  tcase_add_test(tc, tests_from_decimal_to_int_fail1);
  tcase_add_test(tc, tests_from_decimal_to_int_fail2);
  tcase_add_test(tc, tests_from_decimal_to_int_fail3);
  tcase_add_test(tc, tests_from_decimal_to_int_fail4);
  tcase_add_test(tc, tests_from_decimal_to_int_fail5);
  tcase_add_test(tc, tests_from_decimal_to_int_fail6);
  tcase_add_test(tc, tests_from_decimal_to_int_fail7);
  tcase_add_test(tc, tests_from_decimal_to_int_fail8);
  tcase_add_test(tc, tests_from_decimal_to_int_fail9);
  tcase_add_test(tc, tests_from_decimal_to_int_fail10);
  tcase_add_test(tc, tests_from_decimal_to_int_fail11);
  tcase_add_test(tc, tests_from_decimal_to_int_fail12);
  tcase_add_test(tc, tests_from_decimal_to_int_fail13);
  tcase_add_test(tc, tests_from_decimal_to_int_fail17);
  tcase_add_test(tc, tests_from_decimal_to_int_fail18);
  tcase_add_test(tc, tests_from_decimal_to_int_fail19);
  tcase_add_test(tc, tests_from_decimal_to_int_fail20);
  tcase_add_test(tc, tests_from_decimal_to_int_fail21);
  tcase_add_test(tc, tests_from_decimal_to_int_fail22);
  tcase_add_test(tc, tests_from_decimal_to_int_fail23);
  tcase_add_test(tc, tests_from_decimal_to_int_fail24);
  tcase_add_test(tc, tests_from_decimal_to_int_fail25);
  tcase_add_test(tc, tests_from_decimal_to_int_fail26);
  tcase_add_test(tc, tests_from_decimal_to_int_fail27);
  tcase_add_test(tc, tests_from_decimal_to_int_fail28);
  tcase_add_test(tc, tests_from_decimal_to_int_fail29);
  tcase_add_test(tc, tests_from_decimal_to_int_fail30);
  tcase_add_test(tc, tests_from_decimal_to_int_fail31);
  tcase_add_test(tc, tests_from_decimal_to_int_fail32);
  tcase_add_test(tc, tests_from_decimal_to_int_fail33);
  tcase_add_test(tc, tests_from_decimal_to_int_fail34);
  tcase_add_test(tc, tests_from_decimal_to_int_fail35);
  tcase_add_test(tc, tests_from_decimal_to_int_fail36);
  tcase_add_test(tc, tests_from_decimal_to_int_fail37);

  suite_add_tcase(s, tc);
  return s;
}

static const float fails_big[] = {
    340282346638528859811704183484516925440.f,
    340282326356119256160033759537265639424.f,
    340282306073709652508363335590014353408.f,
    170141173319264429905852091742258462720.f,
    226854897759019239874469455656344616960.f,
    283568632339978851668922031544056414208.f,
    85070586659632214952926045871129231360.f,
    85070591730234615865843651857942052864.f,
    5316911666227013434557877866945576960.f,
    2658455991569831745807614120560689152.f,
    20769186196199271228741710417756160.f,
    10384593717069655257060992658440192.f,
    158456325028528675187087900672.0f,
    158456315583795709447797473280.0f,
    158456306139062743708507045888.0f,
    316912631167591418895594946560.f,
    158456325028528675187087900672.f,
    79228190848463234811415232512.f,
    79228181403730269072124805120.f,
    79228171958997303332834377728.f,

};

void test_from_float_to_decimal(float number, s21_decimal decimal_check) {
  s21_decimal result = {0};
  int code = s21_from_float_to_decimal(number, &result);
  int sign_check = s21_getSign(decimal_check);
  int sign_result = s21_getSign(result);
  int re = s21_is_equal_hand_div(&result, &decimal_check);

  ck_assert_int_eq(code, TEST_CONVERSION_OK);
  if (re == 0) {
    printf("CHECK: ");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(decimal_check, i));
    }
    printf("\nRESUL: ");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(result, i));
    }
    printf("\n\n");
  }
  ck_assert_int_eq(re, 1);
  ck_assert_int_eq(sign_check, sign_result);
}

///

START_TEST(test_from_float_to_decimal_unnormal1) {
  float f = 0.0;
  s21_decimal result = s21_get_zero();
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  int re = s21_is_equal_hand_div(&result, &check);

  int code = s21_from_float_to_decimal(f, &result);
  if (re == 0) {
    printf("CHECK: ");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(check, i));
    }
    printf("\nRESUL: ");
    for (int i = 127; i >= 0; --i) {
      printf("%d", s21_getBit(result, i));
    }
    printf("\n\n");
  }
  ck_assert_int_eq(code, TEST_CONVERSION_OK);
  ck_assert_int_eq(re, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal3) {
  float f = INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal4) {
  float f = -INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal5) {
  float f = NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_unnormal6) {
  float f = -NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

///

START_TEST(test_from_float_to_decimal_incorrect1) {
  float f = 1.0f;
  int code = s21_from_float_to_decimal(f, NULL);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_incorrect2) {
  float f = 1e-29;
  s21_decimal result;
  int code = s21_from_float_to_decimal(f, &result);

  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_big) {
  float f = fails_big[_i];
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_fail_big_negate) {
  float f = -fails_big[_i];
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(test_from_float_to_decimal_ok1) {
  // 2.28401628E-19
  float f = 2.28401628E-19;
  // 0.0000000000000000002284016
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2) {
  // -2.28401628E-19
  float f = -2.28401628E-19;
  // -0.0000000000000000002284016
  s21_decimal decimal_check = {{0x22D9F0, 0x0, 0x0, 0x80190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok3) {
  // 5.92141241E+23
  float f = 5.92141241E+23;
  // 592141200000000000000000
  s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok4) {
  // -5.92141241E+23
  float f = -5.92141241E+23;
  // -592141200000000000000000
  s21_decimal decimal_check = {{0xBF280000, 0x9ED0576, 0x7D64, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok5) {
  // 2.1349025E-18
  float f = 2.1349025E-18;
  // 0.000000000000000002134902
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok6) {
  // -2.1349025E-18
  float f = -2.1349025E-18;
  // -0.000000000000000002134902
  s21_decimal decimal_check = {{0x209376, 0x0, 0x0, 0x80180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok7) {
  // 2.38582807E-08
  float f = 2.38582807E-08;
  // 0.00000002385828
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0xE0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok8) {
  // -2.38582807E-08
  float f = -2.38582807E-08;
  // -0.00000002385828
  s21_decimal decimal_check = {{0x2467A4, 0x0, 0x0, 0x800E0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok9) {
  // 7.91617864E+11
  float f = 7.91617864E+11;
  // 791617900000
  s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok10) {
  // -7.91617864E+11
  float f = -7.91617864E+11;
  // -791617900000
  s21_decimal decimal_check = {{0x501A8DE0, 0xB8, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok11) {
  // 1.99102057E+21
  float f = 1.99102057E+21;
  // 1991021000000000000000
  s21_decimal decimal_check = {{0x5F048000, 0xEEF78A9E, 0x6B, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok12) {
  // -1.99102057E+21
  float f = -1.99102057E+21;
  // -1991021000000000000000
  s21_decimal decimal_check = {{0x5F048000, 0xEEF78A9E, 0x6B, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok13) {
  // 9.29209423E+24
  float f = 9.29209423E+24;
  // 9292094000000000000000000
  s21_decimal decimal_check = {{0xE380000, 0x6CD28004, 0x7AFAD, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok14) {
  // -9.29209423E+24
  float f = -9.29209423E+24;
  // -9292094000000000000000000
  s21_decimal decimal_check = {{0xE380000, 0x6CD28004, 0x7AFAD, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok15) {
  // 0.000115481133
  float f = 0.000115481133;
  // 0.0001154811
  s21_decimal decimal_check = {{0x119EFB, 0x0, 0x0, 0xA0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok16) {
  // -0.000115481133
  float f = -0.000115481133;
  // -0.0001154811
  s21_decimal decimal_check = {{0x119EFB, 0x0, 0x0, 0x800A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok17) {
  // 8.66900895E-23
  float f = 8.66900895E-23;
  // 0.0000000000000000000000866901
  s21_decimal decimal_check = {{0xD3A55, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok18) {
  // -8.66900895E-23
  float f = -8.66900895E-23;
  // -0.0000000000000000000000866901
  s21_decimal decimal_check = {{0xD3A55, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok19) {
  // 3.91406387E+11
  float f = 3.91406387E+11;
  // 391406400000
  s21_decimal decimal_check = {{0x21A3B200, 0x5B, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok20) {
  // -3.91406387E+11
  float f = -3.91406387E+11;
  // -391406400000
  s21_decimal decimal_check = {{0x21A3B200, 0x5B, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok21) {
  // 1.54636995E-16
  float f = 1.54636995E-16;
  // 0.000000000000000154637
  s21_decimal decimal_check = {{0x25C0D, 0x0, 0x0, 0x150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok22) {
  // -1.54636995E-16
  float f = -1.54636995E-16;
  // -0.000000000000000154637
  s21_decimal decimal_check = {{0x25C0D, 0x0, 0x0, 0x80150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok23) {
  // 1.05583253E-13
  float f = 1.05583253E-13;
  // 0.0000000000001055833
  s21_decimal decimal_check = {{0x101C59, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok24) {
  // -1.05583253E-13
  float f = -1.05583253E-13;
  // -0.0000000000001055833
  s21_decimal decimal_check = {{0x101C59, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok25) {
  // 4882.71582
  float f = 4882.71582;
  // 4882.716
  s21_decimal decimal_check = {{0x4A811C, 0x0, 0x0, 0x30000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok26) {
  // -4882.71582
  float f = -4882.71582;
  // -4882.716
  s21_decimal decimal_check = {{0x4A811C, 0x0, 0x0, 0x80030000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok27) {
  // 1.9929916E-26
  float f = 1.9929916E-26;
  // 0.0000000000000000000000000199
  s21_decimal decimal_check = {{0xC7, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok28) {
  // -1.9929916E-26
  float f = -1.9929916E-26;
  // -0.0000000000000000000000000199
  s21_decimal decimal_check = {{0xC7, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok29) {
  // 3574.10864
  float f = 3574.10864;
  // 3574.109
  s21_decimal decimal_check = {{0x36895D, 0x0, 0x0, 0x30000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok30) {
  // -3574.10864
  float f = -3574.10864;
  // -3574.109
  s21_decimal decimal_check = {{0x36895D, 0x0, 0x0, 0x80030000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok31) {
  // 3.62930687E-13
  float f = 3.62930687E-13;
  // 0.0000000000003629307
  s21_decimal decimal_check = {{0x3760FB, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok32) {
  // -3.62930687E-13
  float f = -3.62930687E-13;
  // -0.0000000000003629307
  s21_decimal decimal_check = {{0x3760FB, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok33) {
  // 2.1409382E-19
  float f = 2.1409382E-19;
  // 0.0000000000000000002140938
  s21_decimal decimal_check = {{0x20AB0A, 0x0, 0x0, 0x190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok34) {
  // -2.1409382E-19
  float f = -2.1409382E-19;
  // -0.0000000000000000002140938
  s21_decimal decimal_check = {{0x20AB0A, 0x0, 0x0, 0x80190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok35) {
  // 241.244507
  float f = 241.244507;
  // 241.2445
  s21_decimal decimal_check = {{0x24CF9D, 0x0, 0x0, 0x40000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok36) {
  // -241.244507
  float f = -241.244507;
  // -241.2445
  s21_decimal decimal_check = {{0x24CF9D, 0x0, 0x0, 0x80040000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok37) {
  // 802580.063
  float f = 802580.063;
  // 802580.1
  s21_decimal decimal_check = {{0x7A76C9, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok38) {
  // -802580.063
  float f = -802580.063;
  // -802580.1
  s21_decimal decimal_check = {{0x7A76C9, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok39) {
  // 8.38680669E+16
  float f = 8.38680669E+16;
  // 83868070000000000
  s21_decimal decimal_check = {{0xB858FC00, 0x129F590, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok40) {
  // -8.38680669E+16
  float f = -8.38680669E+16;
  // -83868070000000000
  s21_decimal decimal_check = {{0xB858FC00, 0x129F590, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok41) {
  // 3.93541897E-17
  float f = 3.93541897E-17;
  // 0.00000000000000003935419
  s21_decimal decimal_check = {{0x3C0CBB, 0x0, 0x0, 0x170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok42) {
  // -3.93541897E-17
  float f = -3.93541897E-17;
  // -0.00000000000000003935419
  s21_decimal decimal_check = {{0x3C0CBB, 0x0, 0x0, 0x80170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok43) {
  // 1.45764168E-20
  float f = 1.45764168E-20;
  // 0.00000000000000000001457642
  s21_decimal decimal_check = {{0x163DEA, 0x0, 0x0, 0x1A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok44) {
  // -1.45764168E-20
  float f = -1.45764168E-20;
  // -0.00000000000000000001457642
  s21_decimal decimal_check = {{0x163DEA, 0x0, 0x0, 0x801A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok45) {
  // 1.34647118E+20
  float f = 1.34647118E+20;
  // 134647100000000000000
  s21_decimal decimal_check = {{0x207FC000, 0x4C9A980F, 0x7, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok46) {
  // -1.34647118E+20
  float f = -1.34647118E+20;
  // -134647100000000000000
  s21_decimal decimal_check = {{0x207FC000, 0x4C9A980F, 0x7, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok47) {
  // 2.20958198E-20
  float f = 2.20958198E-20;
  // 0.00000000000000000002209582
  s21_decimal decimal_check = {{0x21B72E, 0x0, 0x0, 0x1A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok48) {
  // -2.20958198E-20
  float f = -2.20958198E-20;
  // -0.00000000000000000002209582
  s21_decimal decimal_check = {{0x21B72E, 0x0, 0x0, 0x801A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok49) {
  // 5.36623235E-09
  float f = 5.36623235E-09;
  // 0.000000005366232
  s21_decimal decimal_check = {{0x51E1D8, 0x0, 0x0, 0xF0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok50) {
  // -5.36623235E-09
  float f = -5.36623235E-09;
  // -0.000000005366232
  s21_decimal decimal_check = {{0x51E1D8, 0x0, 0x0, 0x800F0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok51) {
  // 4.71008997E+17
  float f = 4.71008997E+17;
  // 471009000000000000
  s21_decimal decimal_check = {{0xA3031000, 0x6895C30, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok52) {
  // -4.71008997E+17
  float f = -4.71008997E+17;
  // -471009000000000000
  s21_decimal decimal_check = {{0xA3031000, 0x6895C30, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok53) {
  // 2.36363464E-11
  float f = 2.36363464E-11;
  // 0.00000000002363635
  s21_decimal decimal_check = {{0x2410F3, 0x0, 0x0, 0x110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok54) {
  // -2.36363464E-11
  float f = -2.36363464E-11;
  // -0.00000000002363635
  s21_decimal decimal_check = {{0x2410F3, 0x0, 0x0, 0x80110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok55) {
  // 0.0255207196
  float f = 0.0255207196;
  // 0.02552072
  s21_decimal decimal_check = {{0x26F108, 0x0, 0x0, 0x80000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok56) {
  // -0.0255207196
  float f = -0.0255207196;
  // -0.02552072
  s21_decimal decimal_check = {{0x26F108, 0x0, 0x0, 0x80080000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok57) {
  // 3.9575282E-24
  float f = 3.9575282E-24;
  // 0.0000000000000000000000039575
  s21_decimal decimal_check = {{0x9A97, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok58) {
  // -3.9575282E-24
  float f = -3.9575282E-24;
  // -0.0000000000000000000000039575
  s21_decimal decimal_check = {{0x9A97, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok59) {
  // 0.00399137754
  float f = 0.00399137754;
  // 0.003991378
  s21_decimal decimal_check = {{0x3CE752, 0x0, 0x0, 0x90000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok60) {
  // -0.00399137754
  float f = -0.00399137754;
  // -0.003991378
  s21_decimal decimal_check = {{0x3CE752, 0x0, 0x0, 0x80090000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok61) {
  // 1.95127377E-05
  float f = 1.95127377E-05;
  // 0.00001951274
  s21_decimal decimal_check = {{0x1DC62A, 0x0, 0x0, 0xB0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok62) {
  // -1.95127377E-05
  float f = -1.95127377E-05;
  // -0.00001951274
  s21_decimal decimal_check = {{0x1DC62A, 0x0, 0x0, 0x800B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok63) {
  // 1.26745242E-20
  float f = 1.26745242E-20;
  // 0.00000000000000000001267452
  s21_decimal decimal_check = {{0x1356FC, 0x0, 0x0, 0x1A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok64) {
  // -1.26745242E-20
  float f = -1.26745242E-20;
  // -0.00000000000000000001267452
  s21_decimal decimal_check = {{0x1356FC, 0x0, 0x0, 0x801A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok65) {
  // 0.0764362067
  float f = 0.0764362067;
  // 0.07643621
  s21_decimal decimal_check = {{0x74A1E5, 0x0, 0x0, 0x80000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok66) {
  // -0.0764362067
  float f = -0.0764362067;
  // -0.07643621
  s21_decimal decimal_check = {{0x74A1E5, 0x0, 0x0, 0x80080000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok67) {
  // 1.19421885E-18
  float f = 1.19421885E-18;
  // 0.000000000000000001194219
  s21_decimal decimal_check = {{0x1238EB, 0x0, 0x0, 0x180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok68) {
  // -1.19421885E-18
  float f = -1.19421885E-18;
  // -0.000000000000000001194219
  s21_decimal decimal_check = {{0x1238EB, 0x0, 0x0, 0x80180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok69) {
  // 7.93902012E-16
  float f = 7.93902012E-16;
  // 0.000000000000000793902
  s21_decimal decimal_check = {{0xC1D2E, 0x0, 0x0, 0x150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok70) {
  // -7.93902012E-16
  float f = -7.93902012E-16;
  // -0.000000000000000793902
  s21_decimal decimal_check = {{0xC1D2E, 0x0, 0x0, 0x80150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok71) {
  // 5.86327048E-15
  float f = 5.86327048E-15;
  // 0.00000000000000586327
  s21_decimal decimal_check = {{0x8F257, 0x0, 0x0, 0x140000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok72) {
  // -5.86327048E-15
  float f = -5.86327048E-15;
  // -0.00000000000000586327
  s21_decimal decimal_check = {{0x8F257, 0x0, 0x0, 0x80140000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok73) {
  // 8.52215659E-11
  float f = 8.52215659E-11;
  // 0.00000000008522157
  s21_decimal decimal_check = {{0x8209AD, 0x0, 0x0, 0x110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok74) {
  // -8.52215659E-11
  float f = -8.52215659E-11;
  // -0.00000000008522157
  s21_decimal decimal_check = {{0x8209AD, 0x0, 0x0, 0x80110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok75) {
  // 9.61645806E-28
  float f = 9.61645806E-28;
  // 0.000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok76) {
  // -9.61645806E-28
  float f = -9.61645806E-28;
  // -0.000000000000000000000000001
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok77) {
  // 46282560
  float f = 46282560;
  // 46282560
  s21_decimal decimal_check = {{0x2C23740, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok78) {
  // -46282560
  float f = -46282560;
  // -46282560
  s21_decimal decimal_check = {{0x2C23740, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok79) {
  // 1.15109615E-12
  float f = 1.15109615E-12;
  // 0.000000000001151096
  s21_decimal decimal_check = {{0x119078, 0x0, 0x0, 0x120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok80) {
  // -1.15109615E-12
  float f = -1.15109615E-12;
  // -0.000000000001151096
  s21_decimal decimal_check = {{0x119078, 0x0, 0x0, 0x80120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok81) {
  // 2.83794689E-11
  float f = 2.83794689E-11;
  // 0.00000000002837947
  s21_decimal decimal_check = {{0x2B4DBB, 0x0, 0x0, 0x110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok82) {
  // -2.83794689E-11
  float f = -2.83794689E-11;
  // -0.00000000002837947
  s21_decimal decimal_check = {{0x2B4DBB, 0x0, 0x0, 0x80110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok83) {
  // 8.43187742E-10
  float f = 8.43187742E-10;
  // 0.0000000008431877
  s21_decimal decimal_check = {{0x80A905, 0x0, 0x0, 0x100000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok84) {
  // -8.43187742E-10
  float f = -8.43187742E-10;
  // -0.0000000008431877
  s21_decimal decimal_check = {{0x80A905, 0x0, 0x0, 0x80100000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok85) {
  // 9.83161032E+17
  float f = 9.83161032E+17;
  // 983161000000000000
  s21_decimal decimal_check = {{0x72049000, 0xDA4E3B8, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok86) {
  // -9.83161032E+17
  float f = -9.83161032E+17;
  // -983161000000000000
  s21_decimal decimal_check = {{0x72049000, 0xDA4E3B8, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok87) {
  // 5010.18115
  float f = 5010.18115;
  // 5010.181
  s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x30000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok88) {
  // -5010.18115
  float f = -5010.18115;
  // -5010.181
  s21_decimal decimal_check = {{0x4C7305, 0x0, 0x0, 0x80030000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok89) {
  // 5.82704236E-25
  float f = 5.82704236E-25;
  // 0.0000000000000000000000005827
  s21_decimal decimal_check = {{0x16C3, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok90) {
  // -5.82704236E-25
  float f = -5.82704236E-25;
  // -0.0000000000000000000000005827
  s21_decimal decimal_check = {{0x16C3, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok91) {
  // 5.07265574E+16
  float f = 5.07265574E+16;
  // 50726560000000000
  s21_decimal decimal_check = {{0x9D7A4000, 0xB43789, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok92) {
  // -5.07265574E+16
  float f = -5.07265574E+16;
  // -50726560000000000
  s21_decimal decimal_check = {{0x9D7A4000, 0xB43789, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok93) {
  // 1.35639493E+19
  float f = 1.35639493E+19;
  // 13563950000000000000
  s21_decimal decimal_check = {{0xFD28E000, 0xBC3CD4A8, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok94) {
  // -1.35639493E+19
  float f = -1.35639493E+19;
  // -13563950000000000000
  s21_decimal decimal_check = {{0xFD28E000, 0xBC3CD4A8, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok95) {
  // 1.2867606E+27
  float f = 1.2867606E+27;
  // 1286761000000000000000000000
  s21_decimal decimal_check = {{0x8FA00000, 0x955F02E9, 0x428623D, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok96) {
  // -1.2867606E+27
  float f = -1.2867606E+27;
  // -1286761000000000000000000000
  s21_decimal decimal_check = {{0x8FA00000, 0x955F02E9, 0x428623D, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok97) {
  // 9.07980924E+20
  float f = 9.07980924E+20;
  // 907980900000000000000
  s21_decimal decimal_check = {{0x6B7A4000, 0x38C429DC, 0x31, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok98) {
  // -9.07980924E+20
  float f = -9.07980924E+20;
  // -907980900000000000000
  s21_decimal decimal_check = {{0x6B7A4000, 0x38C429DC, 0x31, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok99) {
  // 15372566
  float f = 15372566;
  // 15372570
  s21_decimal decimal_check = {{0xEA911A, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok100) {
  // -15372566
  float f = -15372566;
  // -15372570
  s21_decimal decimal_check = {{0xEA911A, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok101) {
  // 9.85001198E-23
  float f = 9.85001198E-23;
  // 0.0000000000000000000000985001
  s21_decimal decimal_check = {{0xF07A9, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok102) {
  // -9.85001198E-23
  float f = -9.85001198E-23;
  // -0.0000000000000000000000985001
  s21_decimal decimal_check = {{0xF07A9, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok103) {
  // 4.58205132E-12
  float f = 4.58205132E-12;
  // 0.000000000004582051
  s21_decimal decimal_check = {{0x45EAA3, 0x0, 0x0, 0x120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok104) {
  // -4.58205132E-12
  float f = -4.58205132E-12;
  // -0.000000000004582051
  s21_decimal decimal_check = {{0x45EAA3, 0x0, 0x0, 0x80120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok105) {
  // 6.88863376E-12
  float f = 6.88863376E-12;
  // 0.000000000006888634
  s21_decimal decimal_check = {{0x691CBA, 0x0, 0x0, 0x120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok106) {
  // -6.88863376E-12
  float f = -6.88863376E-12;
  // -0.000000000006888634
  s21_decimal decimal_check = {{0x691CBA, 0x0, 0x0, 0x80120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok107) {
  // 1.94770514E+10
  float f = 1.94770514E+10;
  // 19477050000
  s21_decimal decimal_check = {{0x88EC3290, 0x4, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok108) {
  // -1.94770514E+10
  float f = -1.94770514E+10;
  // -19477050000
  s21_decimal decimal_check = {{0x88EC3290, 0x4, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok109) {
  // 0.000745483907
  float f = 0.000745483907;
  // 0.0007454839
  s21_decimal decimal_check = {{0x71C077, 0x0, 0x0, 0xA0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok110) {
  // -0.000745483907
  float f = -0.000745483907;
  // -0.0007454839
  s21_decimal decimal_check = {{0x71C077, 0x0, 0x0, 0x800A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok111) {
  // 7.85835969E+18
  float f = 7.85835969E+18;
  // 7858360000000000000
  s21_decimal decimal_check = {{0xDD238000, 0x6D0E80C8, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok112) {
  // -7.85835969E+18
  float f = -7.85835969E+18;
  // -7858360000000000000
  s21_decimal decimal_check = {{0xDD238000, 0x6D0E80C8, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok113) {
  // 4.39337262E+21
  float f = 4.39337262E+21;
  // 4393373000000000000000
  s21_decimal decimal_check = {{0x883C8000, 0x2A4C5A69, 0xEE, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok114) {
  // -4.39337262E+21
  float f = -4.39337262E+21;
  // -4393373000000000000000
  s21_decimal decimal_check = {{0x883C8000, 0x2A4C5A69, 0xEE, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok115) {
  // 4.8940947E+19
  float f = 4.8940947E+19;
  // 48940950000000000000
  s21_decimal decimal_check = {{0x88276000, 0xA7312EB9, 0x2, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok116) {
  // -4.8940947E+19
  float f = -4.8940947E+19;
  // -48940950000000000000
  s21_decimal decimal_check = {{0x88276000, 0xA7312EB9, 0x2, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok117) {
  // 2.1753997E+18
  float f = 2.1753997E+18;
  // 2175400000000000000
  s21_decimal decimal_check = {{0x34628000, 0x1E3092C6, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok118) {
  // -2.1753997E+18
  float f = -2.1753997E+18;
  // -2175400000000000000
  s21_decimal decimal_check = {{0x34628000, 0x1E3092C6, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok119) {
  // 8.42251829E+11
  float f = 8.42251829E+11;
  // 842251800000
  s21_decimal decimal_check = {{0x1A1E8DC0, 0xC4, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok120) {
  // -8.42251829E+11
  float f = -8.42251829E+11;
  // -842251800000
  s21_decimal decimal_check = {{0x1A1E8DC0, 0xC4, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok121) {
  // 4.26393967E-07
  float f = 4.26393967E-07;
  // 0.000000426394
  s21_decimal decimal_check = {{0x6819A, 0x0, 0x0, 0xC0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok122) {
  // -4.26393967E-07
  float f = -4.26393967E-07;
  // -0.000000426394
  s21_decimal decimal_check = {{0x6819A, 0x0, 0x0, 0x800C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok123) {
  // 1.84532337E-12
  float f = 1.84532337E-12;
  // 0.000000000001845323
  s21_decimal decimal_check = {{0x1C284B, 0x0, 0x0, 0x120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok124) {
  // -1.84532337E-12
  float f = -1.84532337E-12;
  // -0.000000000001845323
  s21_decimal decimal_check = {{0x1C284B, 0x0, 0x0, 0x80120000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok125) {
  // 7.70974401E-20
  float f = 7.70974401E-20;
  // 0.00000000000000000007709744
  s21_decimal decimal_check = {{0x75A430, 0x0, 0x0, 0x1A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok126) {
  // -7.70974401E-20
  float f = -7.70974401E-20;
  // -0.00000000000000000007709744
  s21_decimal decimal_check = {{0x75A430, 0x0, 0x0, 0x801A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok127) {
  // 0.0104842195
  float f = 0.0104842195;
  // 0.01048422
  s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok128) {
  // -0.0104842195
  float f = -0.0104842195;
  // -0.01048422
  s21_decimal decimal_check = {{0xFFF66, 0x0, 0x0, 0x80080000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok129) {
  // 1.98140566E-22
  float f = 1.98140566E-22;
  // 0.0000000000000000000001981406
  s21_decimal decimal_check = {{0x1E3BDE, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok130) {
  // -1.98140566E-22
  float f = -1.98140566E-22;
  // -0.0000000000000000000001981406
  s21_decimal decimal_check = {{0x1E3BDE, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok131) {
  // 1.17932588E+22
  float f = 1.17932588E+22;
  // 11793260000000000000000
  s21_decimal decimal_check = {{0x6F3E0000, 0x505C1EA1, 0x27F, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok132) {
  // -1.17932588E+22
  float f = -1.17932588E+22;
  // -11793260000000000000000
  s21_decimal decimal_check = {{0x6F3E0000, 0x505C1EA1, 0x27F, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok133) {
  // 356700.438
  float f = 356700.438;
  // 356700.4
  s21_decimal decimal_check = {{0x366D9C, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok134) {
  // -356700.438
  float f = -356700.438;
  // -356700.4
  s21_decimal decimal_check = {{0x366D9C, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok135) {
  // 4.27844415E-17
  float f = 4.27844415E-17;
  // 0.00000000000000004278444
  s21_decimal decimal_check = {{0x4148AC, 0x0, 0x0, 0x170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok136) {
  // -4.27844415E-17
  float f = -4.27844415E-17;
  // -0.00000000000000004278444
  s21_decimal decimal_check = {{0x4148AC, 0x0, 0x0, 0x80170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok137) {
  // 12419649
  float f = 12419649;
  // 12419650
  s21_decimal decimal_check = {{0xBD8242, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok138) {
  // -12419649
  float f = -12419649;
  // -12419650
  s21_decimal decimal_check = {{0xBD8242, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok139) {
  // 3.08497797E-21
  float f = 3.08497797E-21;
  // 0.000000000000000000003084978
  s21_decimal decimal_check = {{0x2F12B2, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok140) {
  // -3.08497797E-21
  float f = -3.08497797E-21;
  // -0.000000000000000000003084978
  s21_decimal decimal_check = {{0x2F12B2, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok141) {
  // 4.18459603E+15
  float f = 4.18459603E+15;
  // 4184596000000000
  s21_decimal decimal_check = {{0x2E1BC800, 0xEDDDE, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok142) {
  // -4.18459603E+15
  float f = -4.18459603E+15;
  // -4184596000000000
  s21_decimal decimal_check = {{0x2E1BC800, 0xEDDDE, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok143) {
  // 1.16865436E+26
  float f = 1.16865436E+26;
  // 116865400000000000000000000
  s21_decimal decimal_check = {{0xBAE00000, 0x7467DF7, 0x60AB36, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok144) {
  // -1.16865436E+26
  float f = -1.16865436E+26;
  // -116865400000000000000000000
  s21_decimal decimal_check = {{0xBAE00000, 0x7467DF7, 0x60AB36, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok145) {
  // 2.70840103E+12
  float f = 2.70840103E+12;
  // 2708401000000
  s21_decimal decimal_check = {{0x99478E40, 0x276, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok146) {
  // -2.70840103E+12
  float f = -2.70840103E+12;
  // -2708401000000
  s21_decimal decimal_check = {{0x99478E40, 0x276, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok147) {
  // 6.74712444E-21
  float f = 6.74712444E-21;
  // 0.000000000000000000006747124
  s21_decimal decimal_check = {{0x66F3F4, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok148) {
  // -6.74712444E-21
  float f = -6.74712444E-21;
  // -0.000000000000000000006747124
  s21_decimal decimal_check = {{0x66F3F4, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok149) {
  // 5.64592297E-11
  float f = 5.64592297E-11;
  // 0.00000000005645923
  s21_decimal decimal_check = {{0x562663, 0x0, 0x0, 0x110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok150) {
  // -5.64592297E-11
  float f = -5.64592297E-11;
  // -0.00000000005645923
  s21_decimal decimal_check = {{0x562663, 0x0, 0x0, 0x80110000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok151) {
  // 4.58151199E+10
  float f = 4.58151199E+10;
  // 45815120000
  s21_decimal decimal_check = {{0xAACB4080, 0xA, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok152) {
  // -4.58151199E+10
  float f = -4.58151199E+10;
  // -45815120000
  s21_decimal decimal_check = {{0xAACB4080, 0xA, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok153) {
  // 1.48573706E-20
  float f = 1.48573706E-20;
  // 0.00000000000000000001485737
  s21_decimal decimal_check = {{0x16ABA9, 0x0, 0x0, 0x1A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok154) {
  // -1.48573706E-20
  float f = -1.48573706E-20;
  // -0.00000000000000000001485737
  s21_decimal decimal_check = {{0x16ABA9, 0x0, 0x0, 0x801A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok155) {
  // 1.40592974E-22
  float f = 1.40592974E-22;
  // 0.000000000000000000000140593
  s21_decimal decimal_check = {{0x22531, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok156) {
  // -1.40592974E-22
  float f = -1.40592974E-22;
  // -0.000000000000000000000140593
  s21_decimal decimal_check = {{0x22531, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok157) {
  // 1.83958331E+22
  float f = 1.83958331E+22;
  // 18395830000000000000000
  s21_decimal decimal_check = {{0x2A1F0000, 0x3D6CDFB7, 0x3E5, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok158) {
  // -1.83958331E+22
  float f = -1.83958331E+22;
  // -18395830000000000000000
  s21_decimal decimal_check = {{0x2A1F0000, 0x3D6CDFB7, 0x3E5, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok159) {
  // 1.04831784E-07
  float f = 1.04831784E-07;
  // 0.0000001048318
  s21_decimal decimal_check = {{0xFFEFE, 0x0, 0x0, 0xD0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok160) {
  // -1.04831784E-07
  float f = -1.04831784E-07;
  // -0.0000001048318
  s21_decimal decimal_check = {{0xFFEFE, 0x0, 0x0, 0x800D0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok161) {
  // 3.40432057E+16
  float f = 3.40432057E+16;
  // 34043210000000000
  s21_decimal decimal_check = {{0x7F106400, 0x78F21E, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok162) {
  // -3.40432057E+16
  float f = -3.40432057E+16;
  // -34043210000000000
  s21_decimal decimal_check = {{0x7F106400, 0x78F21E, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok163) {
  // 4.44212428E-21
  float f = 4.44212428E-21;
  // 0.000000000000000000004442124
  s21_decimal decimal_check = {{0x43C80C, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok164) {
  // -4.44212428E-21
  float f = -4.44212428E-21;
  // -0.000000000000000000004442124
  s21_decimal decimal_check = {{0x43C80C, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok165) {
  // 2.77922045E-05
  float f = 2.77922045E-05;
  // 0.0000277922
  s21_decimal decimal_check = {{0x43DA2, 0x0, 0x0, 0xA0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok166) {
  // -2.77922045E-05
  float f = -2.77922045E-05;
  // -0.0000277922
  s21_decimal decimal_check = {{0x43DA2, 0x0, 0x0, 0x800A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok167) {
  // 2.47787305E-13
  float f = 2.47787305E-13;
  // 0.0000000000002477873
  s21_decimal decimal_check = {{0x25CF31, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok168) {
  // -2.47787305E-13
  float f = -2.47787305E-13;
  // -0.0000000000002477873
  s21_decimal decimal_check = {{0x25CF31, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok169) {
  // 8.1853854E-19
  float f = 8.1853854E-19;
  // 0.0000000000000000008185385
  s21_decimal decimal_check = {{0x7CE629, 0x0, 0x0, 0x190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok170) {
  // -8.1853854E-19
  float f = -8.1853854E-19;
  // -0.0000000000000000008185385
  s21_decimal decimal_check = {{0x7CE629, 0x0, 0x0, 0x80190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok171) {
  // 2.11021068E+24
  float f = 2.11021068E+24;
  // 2110211000000000000000000
  s21_decimal decimal_check = {{0xE22C0000, 0xC47CDAF3, 0x1BEDA, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok172) {
  // -2.11021068E+24
  float f = -2.11021068E+24;
  // -2110211000000000000000000
  s21_decimal decimal_check = {{0xE22C0000, 0xC47CDAF3, 0x1BEDA, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok173) {
  // 1.82873229E+09
  float f = 1.82873229E+09;
  // 1828732000
  s21_decimal decimal_check = {{0x6D003C60, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok174) {
  // -1.82873229E+09
  float f = -1.82873229E+09;
  // -1828732000
  s21_decimal decimal_check = {{0x6D003C60, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok175) {
  // 3807398.25
  float f = 3807398.25;
  // 3807398
  s21_decimal decimal_check = {{0x3A18A6, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok176) {
  // -3807398.25
  float f = -3807398.25;
  // -3807398
  s21_decimal decimal_check = {{0x3A18A6, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok177) {
  // 807.082397
  float f = 807.082397;
  // 807.0824
  s21_decimal decimal_check = {{0x7B26A8, 0x0, 0x0, 0x40000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok178) {
  // -807.082397
  float f = -807.082397;
  // -807.0824
  s21_decimal decimal_check = {{0x7B26A8, 0x0, 0x0, 0x80040000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok179) {
  // 1.00471938E-16
  float f = 1.00471938E-16;
  // 0.0000000000000001004719
  s21_decimal decimal_check = {{0xF54AF, 0x0, 0x0, 0x160000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok180) {
  // -1.00471938E-16
  float f = -1.00471938E-16;
  // -0.0000000000000001004719
  s21_decimal decimal_check = {{0xF54AF, 0x0, 0x0, 0x80160000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok181) {
  // 1.31486965E-18
  float f = 1.31486965E-18;
  // 0.00000000000000000131487
  s21_decimal decimal_check = {{0x2019F, 0x0, 0x0, 0x170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok182) {
  // -1.31486965E-18
  float f = -1.31486965E-18;
  // -0.00000000000000000131487
  s21_decimal decimal_check = {{0x2019F, 0x0, 0x0, 0x80170000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok183) {
  // 8.47554286E-13
  float f = 8.47554286E-13;
  // 0.0000000000008475543
  s21_decimal decimal_check = {{0x815397, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok184) {
  // -8.47554286E-13
  float f = -8.47554286E-13;
  // -0.0000000000008475543
  s21_decimal decimal_check = {{0x815397, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok185) {
  // 2.07975469E-28
  float f = 2.07975469E-28;
  // 0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok186) {
  // -2.07975469E-28
  float f = -2.07975469E-28;
  // -0.0000000000000000000000000002
  s21_decimal decimal_check = {{0x2, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok187) {
  // 2.76817269E+13
  float f = 2.76817269E+13;
  // 27681730000000
  s21_decimal decimal_check = {{0x27AEF480, 0x192D, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok188) {
  // -2.76817269E+13
  float f = -2.76817269E+13;
  // -27681730000000
  s21_decimal decimal_check = {{0x27AEF480, 0x192D, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok189) {
  // 2.64643858E+12
  float f = 2.64643858E+12;
  // 2646439000000
  s21_decimal decimal_check = {{0x2C0E77C0, 0x268, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok190) {
  // -2.64643858E+12
  float f = -2.64643858E+12;
  // -2646439000000
  s21_decimal decimal_check = {{0x2C0E77C0, 0x268, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok191) {
  // 7.66456801E+18
  float f = 7.66456801E+18;
  // 7664568000000000000
  s21_decimal decimal_check = {{0xC4D38000, 0x6A5E03FC, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok192) {
  // -7.66456801E+18
  float f = -7.66456801E+18;
  // -7664568000000000000
  s21_decimal decimal_check = {{0xC4D38000, 0x6A5E03FC, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok193) {
  // 2.76005793E+27
  float f = 2.76005793E+27;
  // 2760058000000000000000000000
  s21_decimal decimal_check = {{0x38400000, 0xFD42C0C4, 0x8EB1103, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok194) {
  // -2.76005793E+27
  float f = -2.76005793E+27;
  // -2760058000000000000000000000
  s21_decimal decimal_check = {{0x38400000, 0xFD42C0C4, 0x8EB1103, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok195) {
  // 4.72614865E-19
  float f = 4.72614865E-19;
  // 0.0000000000000000004726149
  s21_decimal decimal_check = {{0x481D85, 0x0, 0x0, 0x190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok196) {
  // -4.72614865E-19
  float f = -4.72614865E-19;
  // -0.0000000000000000004726149
  s21_decimal decimal_check = {{0x481D85, 0x0, 0x0, 0x80190000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok197) {
  // 1.22559799E-13
  float f = 1.22559799E-13;
  // 0.0000000000001225598
  s21_decimal decimal_check = {{0x12B37E, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok198) {
  // -1.22559799E-13
  float f = -1.22559799E-13;
  // -0.0000000000001225598
  s21_decimal decimal_check = {{0x12B37E, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok199) {
  // 4.67068756E+27
  float f = 4.67068756E+27;
  // 4670688000000000000000000000
  s21_decimal decimal_check = {{0x4C000000, 0xD4815AA5, 0xF1780A7, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok200) {
  // -4.67068756E+27
  float f = -4.67068756E+27;
  // -4670688000000000000000000000
  s21_decimal decimal_check = {{0x4C000000, 0xD4815AA5, 0xF1780A7, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok201) {
  // 1.43260896E-27
  float f = 1.43260896E-27;
  // 0.0000000000000000000000000014
  s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok202) {
  // -1.43260896E-27
  float f = -1.43260896E-27;
  // -0.0000000000000000000000000014
  s21_decimal decimal_check = {{0xE, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok203) {
  // 0.00161657971
  float f = 0.00161657971;
  // 0.00161658
  s21_decimal decimal_check = {{0x2777A, 0x0, 0x0, 0x80000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok204) {
  // -0.00161657971
  float f = -0.00161657971;
  // -0.00161658
  s21_decimal decimal_check = {{0x2777A, 0x0, 0x0, 0x80080000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok205) {
  // 1.11468367E-18
  float f = 1.11468367E-18;
  // 0.000000000000000001114684
  s21_decimal decimal_check = {{0x11023C, 0x0, 0x0, 0x180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok206) {
  // -1.11468367E-18
  float f = -1.11468367E-18;
  // -0.000000000000000001114684
  s21_decimal decimal_check = {{0x11023C, 0x0, 0x0, 0x80180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok207) {
  // 1478.01416
  float f = 1478.01416;
  // 1478.014
  s21_decimal decimal_check = {{0x168D7E, 0x0, 0x0, 0x30000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok208) {
  // -1478.01416
  float f = -1478.01416;
  // -1478.014
  s21_decimal decimal_check = {{0x168D7E, 0x0, 0x0, 0x80030000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok209) {
  // 3.6517143E+09
  float f = 3.6517143E+09;
  // 3651714000
  s21_decimal decimal_check = {{0xD9A8BBD0, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok210) {
  // -3.6517143E+09
  float f = -3.6517143E+09;
  // -3651714000
  s21_decimal decimal_check = {{0xD9A8BBD0, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok211) {
  // 2.08207478E+25
  float f = 2.08207478E+25;
  // 20820750000000000000000000
  s21_decimal decimal_check = {{0x13780000, 0x1E7FE2B2, 0x1138F7, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok212) {
  // -2.08207478E+25
  float f = -2.08207478E+25;
  // -20820750000000000000000000
  s21_decimal decimal_check = {{0x13780000, 0x1E7FE2B2, 0x1138F7, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok213) {
  // 1.67284952E-06
  float f = 1.67284952E-06;
  // 0.00000167285
  s21_decimal decimal_check = {{0x28D75, 0x0, 0x0, 0xB0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok214) {
  // -1.67284952E-06
  float f = -1.67284952E-06;
  // -0.00000167285
  s21_decimal decimal_check = {{0x28D75, 0x0, 0x0, 0x800B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok215) {
  // 1.00791645E+27
  float f = 1.00791645E+27;
  // 1007916000000000000000000000
  s21_decimal decimal_check = {{0xE3800000, 0xD819E2BC, 0x341BA83, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok216) {
  // -1.00791645E+27
  float f = -1.00791645E+27;
  // -1007916000000000000000000000
  s21_decimal decimal_check = {{0xE3800000, 0xD819E2BC, 0x341BA83, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok217) {
  // 6.66145091E-18
  float f = 6.66145091E-18;
  // 0.000000000000000006661451
  s21_decimal decimal_check = {{0x65A54B, 0x0, 0x0, 0x180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok218) {
  // -6.66145091E-18
  float f = -6.66145091E-18;
  // -0.000000000000000006661451
  s21_decimal decimal_check = {{0x65A54B, 0x0, 0x0, 0x80180000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok219) {
  // 15725.3545
  float f = 15725.3545;
  // 15725.35
  s21_decimal decimal_check = {{0x17FEB7, 0x0, 0x0, 0x20000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok220) {
  // -15725.3545
  float f = -15725.3545;
  // -15725.35
  s21_decimal decimal_check = {{0x17FEB7, 0x0, 0x0, 0x80020000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok221) {
  // 1.33397293
  float f = 1.33397293;
  // 1.333973
  s21_decimal decimal_check = {{0x145AD5, 0x0, 0x0, 0x60000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok222) {
  // -1.33397293
  float f = -1.33397293;
  // -1.333973
  s21_decimal decimal_check = {{0x145AD5, 0x0, 0x0, 0x80060000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok223) {
  // 165025.641
  float f = 165025.641;
  // 165025.6
  s21_decimal decimal_check = {{0x192E50, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok224) {
  // -165025.641
  float f = -165025.641;
  // -165025.6
  s21_decimal decimal_check = {{0x192E50, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok225) {
  // 1.2441821E+15
  float f = 1.2441821E+15;
  // 1244182000000000
  s21_decimal decimal_check = {{0xB2255C00, 0x46B93, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok226) {
  // -1.2441821E+15
  float f = -1.2441821E+15;
  // -1244182000000000
  s21_decimal decimal_check = {{0xB2255C00, 0x46B93, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok227) {
  // 2.10811349E-13
  float f = 2.10811349E-13;
  // 0.0000000000002108113
  s21_decimal decimal_check = {{0x202AD1, 0x0, 0x0, 0x130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok228) {
  // -2.10811349E-13
  float f = -2.10811349E-13;
  // -0.0000000000002108113
  s21_decimal decimal_check = {{0x202AD1, 0x0, 0x0, 0x80130000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok229) {
  // 2.40751309E+13
  float f = 2.40751309E+13;
  // 24075130000000
  s21_decimal decimal_check = {{0x6D925280, 0x15E5, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok230) {
  // -2.40751309E+13
  float f = -2.40751309E+13;
  // -24075130000000
  s21_decimal decimal_check = {{0x6D925280, 0x15E5, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok231) {
  // 2.48895624E-25
  float f = 2.48895624E-25;
  // 0.0000000000000000000000002489
  s21_decimal decimal_check = {{0x9B9, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok232) {
  // -2.48895624E-25
  float f = -2.48895624E-25;
  // -0.0000000000000000000000002489
  s21_decimal decimal_check = {{0x9B9, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok233) {
  // 1.31895402E+11
  float f = 1.31895402E+11;
  // 131895400000
  s21_decimal decimal_check = {{0xB5941640, 0x1E, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok234) {
  // -1.31895402E+11
  float f = -1.31895402E+11;
  // -131895400000
  s21_decimal decimal_check = {{0xB5941640, 0x1E, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok235) {
  // 1.4550111E+11
  float f = 1.4550111E+11;
  // 145501100000
  s21_decimal decimal_check = {{0xE08A97E0, 0x21, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok236) {
  // -1.4550111E+11
  float f = -1.4550111E+11;
  // -145501100000
  s21_decimal decimal_check = {{0xE08A97E0, 0x21, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok237) {
  // 6.25111367E-23
  float f = 6.25111367E-23;
  // 0.0000000000000000000000625111
  s21_decimal decimal_check = {{0x989D7, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok238) {
  // -6.25111367E-23
  float f = -6.25111367E-23;
  // -0.0000000000000000000000625111
  s21_decimal decimal_check = {{0x989D7, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok239) {
  // 4.58558402E+27
  float f = 4.58558402E+27;
  // 4585584000000000000000000000
  s21_decimal decimal_check = {{0x66000000, 0xBEE8B75C, 0xED11B2E, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok240) {
  // -4.58558402E+27
  float f = -4.58558402E+27;
  // -4585584000000000000000000000
  s21_decimal decimal_check = {{0x66000000, 0xBEE8B75C, 0xED11B2E, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok241) {
  // 3.28743145E-26
  float f = 3.28743145E-26;
  // 0.0000000000000000000000000329
  s21_decimal decimal_check = {{0x149, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok242) {
  // -3.28743145E-26
  float f = -3.28743145E-26;
  // -0.0000000000000000000000000329
  s21_decimal decimal_check = {{0x149, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok243) {
  // 9.16167978E+16
  float f = 9.16167978E+16;
  // 91616800000000000
  s21_decimal decimal_check = {{0x83754000, 0x1457CFE, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok244) {
  // -9.16167978E+16
  float f = -9.16167978E+16;
  // -91616800000000000
  s21_decimal decimal_check = {{0x83754000, 0x1457CFE, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok245) {
  // 0.026427852
  float f = 0.026427852;
  // 0.02642785
  s21_decimal decimal_check = {{0x285361, 0x0, 0x0, 0x80000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok246) {
  // -0.026427852
  float f = -0.026427852;
  // -0.02642785
  s21_decimal decimal_check = {{0x285361, 0x0, 0x0, 0x80080000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok247) {
  // 1.24064249E-15
  float f = 1.24064249E-15;
  // 0.000000000000001240642
  s21_decimal decimal_check = {{0x12EE42, 0x0, 0x0, 0x150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok248) {
  // -1.24064249E-15
  float f = -1.24064249E-15;
  // -0.000000000000001240642
  s21_decimal decimal_check = {{0x12EE42, 0x0, 0x0, 0x80150000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok249) {
  // 1.16119836E+15
  float f = 1.16119836E+15;
  // 1161198000000000
  s21_decimal decimal_check = {{0x7A4DCC00, 0x4201A, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok647) {
  // 1.71251152E-25
  float f = 1.71251152E-25;
  // 0.0000000000000000000000001713
  s21_decimal decimal_check = {{0x6B1, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok648) {
  // -1.71251152E-25
  float f = -1.71251152E-25;
  // -0.0000000000000000000000001713
  s21_decimal decimal_check = {{0x6B1, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2001) {
  // 7.92281578E+28
  float f = 7.92281578E+28;
  // 79228160000000000000000000000
  s21_decimal decimal_check = {{0x20000000, 0xB392B21A, 0xFFFFFF77, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2002) {
  // -7.92281578E+28
  float f = -7.92281578E+28;
  // -79228160000000000000000000000
  s21_decimal decimal_check = {
      {0x20000000, 0xB392B21A, 0xFFFFFF77, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2435) {
  // 0.5
  float f = 0.5;
  // 0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2436) {
  // -0.5
  float f = -0.5;
  // -0.5
  s21_decimal decimal_check = {{0x5, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2691) {
  // 999998.438
  float f = 999998.438;
  // 999998.4
  s21_decimal decimal_check = {{0x989670, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2692) {
  // -999998.438
  float f = -999998.438;
  // -999998.4
  s21_decimal decimal_check = {{0x989670, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2693) {
  // 2.57396453E-21
  float f = 2.57396453E-21;
  // 0.000000000000000000002573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2694) {
  // -2.57396453E-21
  float f = -2.57396453E-21;
  // -0.000000000000000000002573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2695) {
  // 2.57396453E-21
  float f = 2.57396453E-21;
  // 0.000000000000000000002573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x1B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2696) {
  // -2.57396453E-21
  float f = -2.57396453E-21;
  // -0.000000000000000000002573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x801B0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2697) {
  // 2.5739646
  float f = 2.5739646;
  // 2.573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x60000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2698) {
  // -2.5739646
  float f = -2.5739646;
  // -2.573965
  s21_decimal decimal_check = {{0x27468D, 0x0, 0x0, 0x80060000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2699) {
  // 0.001953125
  float f = 0.001953125;
  // 0.001953125
  s21_decimal decimal_check = {{0x1DCD65, 0x0, 0x0, 0x90000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2700) {
  // -0.001953125
  float f = -0.001953125;
  // -0.001953125
  s21_decimal decimal_check = {{0x1DCD65, 0x0, 0x0, 0x80090000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2701) {
  // 15555555
  float f = 15555555;
  // 15555560
  s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2702) {
  // -15555555
  float f = -15555555;
  // -15555560
  s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2703) {
  // 15555565
  float f = 15555565;
  // 15555560
  s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2704) {
  // -15555565
  float f = -15555565;
  // -15555560
  s21_decimal decimal_check = {{0xED5BE8, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2705) {
  // 3901384.5
  float f = 3901384.5;
  // 3901384
  s21_decimal decimal_check = {{0x3B87C8, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2706) {
  // -3901384.5
  float f = -3901384.5;
  // -3901384
  s21_decimal decimal_check = {{0x3B87C8, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2707) {
  // 3901385.5
  float f = 3901385.5;
  // 3901386
  s21_decimal decimal_check = {{0x3B87CA, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2708) {
  // -3901385.5
  float f = -3901385.5;
  // -3901386
  s21_decimal decimal_check = {{0x3B87CA, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2709) {
  // 0.792281568
  float f = 0.792281568;
  // 0.7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x70000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2710) {
  // -0.792281568
  float f = -0.792281568;
  // -0.7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80070000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2711) {
  // 0.792281628
  float f = 0.792281628;
  // 0.7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x70000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2712) {
  // -0.792281628
  float f = -0.792281628;
  // -0.7922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80070000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2713) {
  // 0.792281687
  float f = 0.792281687;
  // 0.7922817
  s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x70000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2714) {
  // -0.792281687
  float f = -0.792281687;
  // -0.7922817
  s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80070000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2715) {
  // 7.9228158
  float f = 7.9228158;
  // 7.922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x60000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2716) {
  // -7.9228158
  float f = -7.9228158;
  // -7.922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80060000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2717) {
  // 7.92281628
  float f = 7.92281628;
  // 7.922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x60000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2718) {
  // -7.92281628
  float f = -7.92281628;
  // -7.922816
  s21_decimal decimal_check = {{0x78E480, 0x0, 0x0, 0x80060000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2719) {
  // 7.92281675
  float f = 7.92281675;
  // 7.922817
  s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x60000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2720) {
  // -7.92281675
  float f = -7.92281675;
  // -7.922817
  s21_decimal decimal_check = {{0x78E481, 0x0, 0x0, 0x80060000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2721) {
  // 0.00048828125
  float f = 0.00048828125;
  // 0.0004882812
  s21_decimal decimal_check = {{0x4A817C, 0x0, 0x0, 0xA0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2722) {
  // -0.00048828125
  float f = -0.00048828125;
  // -0.0004882812
  s21_decimal decimal_check = {{0x4A817C, 0x0, 0x0, 0x800A0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2723) {
  // 5.55555671E-23
  float f = 5.55555671E-23;
  // 0.0000000000000000000000555556
  s21_decimal decimal_check = {{0x87A24, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2724) {
  // -5.55555671E-23
  float f = -5.55555671E-23;
  // -0.0000000000000000000000555556
  s21_decimal decimal_check = {{0x87A24, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2725) {
  // 5.55555684E-22
  float f = 5.55555684E-22;
  // 0.0000000000000000000005555557
  s21_decimal decimal_check = {{0x54C565, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2726) {
  // -5.55555684E-22
  float f = -5.55555684E-22;
  // -0.0000000000000000000005555557
  s21_decimal decimal_check = {{0x54C565, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2727) {
  // 5.55555687E-24
  float f = 5.55555687E-24;
  // 0.0000000000000000000000055556
  s21_decimal decimal_check = {{0xD904, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2728) {
  // -5.55555687E-24
  float f = -5.55555687E-24;
  // -0.0000000000000000000000055556
  s21_decimal decimal_check = {{0xD904, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2729) {
  // 5.55555687E-25
  float f = 5.55555687E-25;
  // 0.0000000000000000000000005556
  s21_decimal decimal_check = {{0x15B4, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2730) {
  // -5.55555687E-25
  float f = -5.55555687E-25;
  // -0.0000000000000000000000005556
  s21_decimal decimal_check = {{0x15B4, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2731) {
  // 5.55555662E-26
  float f = 5.55555662E-26;
  // 0.0000000000000000000000000556
  s21_decimal decimal_check = {{0x22C, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2732) {
  // -5.55555662E-26
  float f = -5.55555662E-26;
  // -0.0000000000000000000000000556
  s21_decimal decimal_check = {{0x22C, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2733) {
  // 5.55555678E-27
  float f = 5.55555678E-27;
  // 0.0000000000000000000000000056
  s21_decimal decimal_check = {{0x38, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2734) {
  // -5.55555678E-27
  float f = -5.55555678E-27;
  // -0.0000000000000000000000000056
  s21_decimal decimal_check = {{0x38, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2735) {
  // 5.55555678E-28
  float f = 5.55555678E-28;
  // 0.0000000000000000000000000006
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x1C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2736) {
  // -5.55555678E-28
  float f = -5.55555678E-28;
  // -0.0000000000000000000000000006
  s21_decimal decimal_check = {{0x6, 0x0, 0x0, 0x801C0000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2737) {
  // 0.0299999993
  float f = 0.0299999993;
  // 0.03
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x20000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2738) {
  // -0.0299999993
  float f = -0.0299999993;
  // -0.03
  s21_decimal decimal_check = {{0x3, 0x0, 0x0, 0x80020000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2739) {
  // 0.100000001
  float f = 0.100000001;
  // 0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2740) {
  // -0.100000001
  float f = -0.100000001;
  // -0.1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2741) {
  // 0.899999976
  float f = 0.899999976;
  // 0.9
  s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x10000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2742) {
  // -0.899999976
  float f = -0.899999976;
  // -0.9
  s21_decimal decimal_check = {{0x9, 0x0, 0x0, 0x80010000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2743) {
  // 0.99999994
  float f = 0.99999994;
  // 0.9999999
  s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x70000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2744) {
  // -0.99999994
  float f = -0.99999994;
  // -0.9999999
  s21_decimal decimal_check = {{0x98967F, 0x0, 0x0, 0x80070000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2745) {
  // 1
  float f = 1;
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2746) {
  // -1
  float f = -1;
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2747) {
  // 1.00000012
  float f = 1.00000012;
  // 1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  test_from_float_to_decimal(f, decimal_check);
}

START_TEST(test_from_float_to_decimal_ok2748) {
  // -1.00000012
  float f = -1.00000012;
  // -1
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  test_from_float_to_decimal(f, decimal_check);
}

Suite *suite_from_float_to_decimal(void) {
  Suite *s =
      suite_create("\033[45m-=S21_suite_from_float_to_decimal_mini=-\033[0m");
  TCase *tc = tcase_create("case_from_float_to_decimal");

  tcase_add_loop_test(tc, test_from_float_to_decimal_fail_big, 0,
                      sizeof(fails_big) / sizeof(*fails_big));
  tcase_add_loop_test(tc, test_from_float_to_decimal_fail_big_negate, 0,
                      sizeof(fails_big) / sizeof(*fails_big));

  tcase_add_test(tc, test_from_float_to_decimal_incorrect1);
  tcase_add_test(tc, test_from_float_to_decimal_incorrect2);
  tcase_add_test(tc, test_from_float_to_decimal_unnormal1);
  tcase_add_test(tc, test_from_float_to_decimal_unnormal3);
  tcase_add_test(tc, test_from_float_to_decimal_unnormal4);
  tcase_add_test(tc, test_from_float_to_decimal_unnormal5);
  tcase_add_test(tc, test_from_float_to_decimal_unnormal6);

  //

  tcase_add_test(tc, test_from_float_to_decimal_ok1);
  tcase_add_test(tc, test_from_float_to_decimal_ok2);
  tcase_add_test(tc, test_from_float_to_decimal_ok3);
  tcase_add_test(tc, test_from_float_to_decimal_ok4);
  tcase_add_test(tc, test_from_float_to_decimal_ok5);
  tcase_add_test(tc, test_from_float_to_decimal_ok6);
  tcase_add_test(tc, test_from_float_to_decimal_ok7);
  tcase_add_test(tc, test_from_float_to_decimal_ok8);
  tcase_add_test(tc, test_from_float_to_decimal_ok9);
  tcase_add_test(tc, test_from_float_to_decimal_ok10);
  tcase_add_test(tc, test_from_float_to_decimal_ok11);
  tcase_add_test(tc, test_from_float_to_decimal_ok12);
  tcase_add_test(tc, test_from_float_to_decimal_ok13);
  tcase_add_test(tc, test_from_float_to_decimal_ok14);
  tcase_add_test(tc, test_from_float_to_decimal_ok15);
  tcase_add_test(tc, test_from_float_to_decimal_ok16);
  tcase_add_test(tc, test_from_float_to_decimal_ok17);
  tcase_add_test(tc, test_from_float_to_decimal_ok18);
  tcase_add_test(tc, test_from_float_to_decimal_ok19);
  tcase_add_test(tc, test_from_float_to_decimal_ok20);
  tcase_add_test(tc, test_from_float_to_decimal_ok21);
  tcase_add_test(tc, test_from_float_to_decimal_ok22);
  tcase_add_test(tc, test_from_float_to_decimal_ok23);
  tcase_add_test(tc, test_from_float_to_decimal_ok24);
  tcase_add_test(tc, test_from_float_to_decimal_ok25);
  tcase_add_test(tc, test_from_float_to_decimal_ok26);
  tcase_add_test(tc, test_from_float_to_decimal_ok27);
  tcase_add_test(tc, test_from_float_to_decimal_ok28);
  tcase_add_test(tc, test_from_float_to_decimal_ok29);
  tcase_add_test(tc, test_from_float_to_decimal_ok30);
  tcase_add_test(tc, test_from_float_to_decimal_ok31);
  tcase_add_test(tc, test_from_float_to_decimal_ok32);
  tcase_add_test(tc, test_from_float_to_decimal_ok33);
  tcase_add_test(tc, test_from_float_to_decimal_ok34);
  tcase_add_test(tc, test_from_float_to_decimal_ok35);
  tcase_add_test(tc, test_from_float_to_decimal_ok36);
  tcase_add_test(tc, test_from_float_to_decimal_ok37);
  tcase_add_test(tc, test_from_float_to_decimal_ok38);
  tcase_add_test(tc, test_from_float_to_decimal_ok39);
  tcase_add_test(tc, test_from_float_to_decimal_ok40);
  tcase_add_test(tc, test_from_float_to_decimal_ok41);
  tcase_add_test(tc, test_from_float_to_decimal_ok42);
  tcase_add_test(tc, test_from_float_to_decimal_ok43);
  tcase_add_test(tc, test_from_float_to_decimal_ok44);
  tcase_add_test(tc, test_from_float_to_decimal_ok45);
  tcase_add_test(tc, test_from_float_to_decimal_ok46);
  tcase_add_test(tc, test_from_float_to_decimal_ok47);
  tcase_add_test(tc, test_from_float_to_decimal_ok48);
  tcase_add_test(tc, test_from_float_to_decimal_ok49);
  tcase_add_test(tc, test_from_float_to_decimal_ok50);
  tcase_add_test(tc, test_from_float_to_decimal_ok51);
  tcase_add_test(tc, test_from_float_to_decimal_ok52);
  tcase_add_test(tc, test_from_float_to_decimal_ok53);
  tcase_add_test(tc, test_from_float_to_decimal_ok54);
  tcase_add_test(tc, test_from_float_to_decimal_ok55);
  tcase_add_test(tc, test_from_float_to_decimal_ok56);
  tcase_add_test(tc, test_from_float_to_decimal_ok57);
  tcase_add_test(tc, test_from_float_to_decimal_ok58);
  tcase_add_test(tc, test_from_float_to_decimal_ok59);
  tcase_add_test(tc, test_from_float_to_decimal_ok60);
  tcase_add_test(tc, test_from_float_to_decimal_ok61);
  tcase_add_test(tc, test_from_float_to_decimal_ok62);
  tcase_add_test(tc, test_from_float_to_decimal_ok63);
  tcase_add_test(tc, test_from_float_to_decimal_ok64);
  tcase_add_test(tc, test_from_float_to_decimal_ok65);
  tcase_add_test(tc, test_from_float_to_decimal_ok66);
  tcase_add_test(tc, test_from_float_to_decimal_ok67);
  tcase_add_test(tc, test_from_float_to_decimal_ok68);
  tcase_add_test(tc, test_from_float_to_decimal_ok69);
  tcase_add_test(tc, test_from_float_to_decimal_ok70);
  tcase_add_test(tc, test_from_float_to_decimal_ok71);
  tcase_add_test(tc, test_from_float_to_decimal_ok72);
  tcase_add_test(tc, test_from_float_to_decimal_ok73);
  tcase_add_test(tc, test_from_float_to_decimal_ok74);
  tcase_add_test(tc, test_from_float_to_decimal_ok75);
  tcase_add_test(tc, test_from_float_to_decimal_ok76);
  tcase_add_test(tc, test_from_float_to_decimal_ok77);
  tcase_add_test(tc, test_from_float_to_decimal_ok78);
  tcase_add_test(tc, test_from_float_to_decimal_ok79);
  tcase_add_test(tc, test_from_float_to_decimal_ok80);
  tcase_add_test(tc, test_from_float_to_decimal_ok81);
  tcase_add_test(tc, test_from_float_to_decimal_ok82);
  tcase_add_test(tc, test_from_float_to_decimal_ok83);
  tcase_add_test(tc, test_from_float_to_decimal_ok84);
  tcase_add_test(tc, test_from_float_to_decimal_ok85);
  tcase_add_test(tc, test_from_float_to_decimal_ok86);
  tcase_add_test(tc, test_from_float_to_decimal_ok87);
  tcase_add_test(tc, test_from_float_to_decimal_ok88);
  tcase_add_test(tc, test_from_float_to_decimal_ok89);
  tcase_add_test(tc, test_from_float_to_decimal_ok90);
  tcase_add_test(tc, test_from_float_to_decimal_ok91);
  tcase_add_test(tc, test_from_float_to_decimal_ok92);
  tcase_add_test(tc, test_from_float_to_decimal_ok93);
  tcase_add_test(tc, test_from_float_to_decimal_ok94);
  tcase_add_test(tc, test_from_float_to_decimal_ok95);
  tcase_add_test(tc, test_from_float_to_decimal_ok96);
  tcase_add_test(tc, test_from_float_to_decimal_ok97);
  tcase_add_test(tc, test_from_float_to_decimal_ok98);
  tcase_add_test(tc, test_from_float_to_decimal_ok99);
  tcase_add_test(tc, test_from_float_to_decimal_ok100);
  tcase_add_test(tc, test_from_float_to_decimal_ok101);
  tcase_add_test(tc, test_from_float_to_decimal_ok102);
  tcase_add_test(tc, test_from_float_to_decimal_ok103);
  tcase_add_test(tc, test_from_float_to_decimal_ok104);
  tcase_add_test(tc, test_from_float_to_decimal_ok105);
  tcase_add_test(tc, test_from_float_to_decimal_ok106);
  tcase_add_test(tc, test_from_float_to_decimal_ok107);
  tcase_add_test(tc, test_from_float_to_decimal_ok108);
  tcase_add_test(tc, test_from_float_to_decimal_ok109);
  tcase_add_test(tc, test_from_float_to_decimal_ok110);
  tcase_add_test(tc, test_from_float_to_decimal_ok111);
  tcase_add_test(tc, test_from_float_to_decimal_ok112);
  tcase_add_test(tc, test_from_float_to_decimal_ok113);
  tcase_add_test(tc, test_from_float_to_decimal_ok114);
  tcase_add_test(tc, test_from_float_to_decimal_ok115);
  tcase_add_test(tc, test_from_float_to_decimal_ok116);
  tcase_add_test(tc, test_from_float_to_decimal_ok117);
  tcase_add_test(tc, test_from_float_to_decimal_ok118);
  tcase_add_test(tc, test_from_float_to_decimal_ok119);
  tcase_add_test(tc, test_from_float_to_decimal_ok120);
  tcase_add_test(tc, test_from_float_to_decimal_ok121);
  tcase_add_test(tc, test_from_float_to_decimal_ok122);
  tcase_add_test(tc, test_from_float_to_decimal_ok123);
  tcase_add_test(tc, test_from_float_to_decimal_ok124);
  tcase_add_test(tc, test_from_float_to_decimal_ok125);
  tcase_add_test(tc, test_from_float_to_decimal_ok126);
  tcase_add_test(tc, test_from_float_to_decimal_ok127);
  tcase_add_test(tc, test_from_float_to_decimal_ok128);
  tcase_add_test(tc, test_from_float_to_decimal_ok129);
  tcase_add_test(tc, test_from_float_to_decimal_ok130);
  tcase_add_test(tc, test_from_float_to_decimal_ok131);
  tcase_add_test(tc, test_from_float_to_decimal_ok132);
  tcase_add_test(tc, test_from_float_to_decimal_ok133);
  tcase_add_test(tc, test_from_float_to_decimal_ok134);
  tcase_add_test(tc, test_from_float_to_decimal_ok135);
  tcase_add_test(tc, test_from_float_to_decimal_ok136);
  tcase_add_test(tc, test_from_float_to_decimal_ok137);
  tcase_add_test(tc, test_from_float_to_decimal_ok138);
  tcase_add_test(tc, test_from_float_to_decimal_ok139);
  tcase_add_test(tc, test_from_float_to_decimal_ok140);
  tcase_add_test(tc, test_from_float_to_decimal_ok141);
  tcase_add_test(tc, test_from_float_to_decimal_ok142);
  tcase_add_test(tc, test_from_float_to_decimal_ok143);
  tcase_add_test(tc, test_from_float_to_decimal_ok144);
  tcase_add_test(tc, test_from_float_to_decimal_ok145);
  tcase_add_test(tc, test_from_float_to_decimal_ok146);
  tcase_add_test(tc, test_from_float_to_decimal_ok147);
  tcase_add_test(tc, test_from_float_to_decimal_ok148);
  tcase_add_test(tc, test_from_float_to_decimal_ok149);
  tcase_add_test(tc, test_from_float_to_decimal_ok150);
  tcase_add_test(tc, test_from_float_to_decimal_ok151);
  tcase_add_test(tc, test_from_float_to_decimal_ok152);
  tcase_add_test(tc, test_from_float_to_decimal_ok153);
  tcase_add_test(tc, test_from_float_to_decimal_ok154);
  tcase_add_test(tc, test_from_float_to_decimal_ok155);
  tcase_add_test(tc, test_from_float_to_decimal_ok156);
  tcase_add_test(tc, test_from_float_to_decimal_ok157);
  tcase_add_test(tc, test_from_float_to_decimal_ok158);
  tcase_add_test(tc, test_from_float_to_decimal_ok159);
  tcase_add_test(tc, test_from_float_to_decimal_ok160);
  tcase_add_test(tc, test_from_float_to_decimal_ok161);
  tcase_add_test(tc, test_from_float_to_decimal_ok162);
  tcase_add_test(tc, test_from_float_to_decimal_ok163);
  tcase_add_test(tc, test_from_float_to_decimal_ok164);
  tcase_add_test(tc, test_from_float_to_decimal_ok165);
  tcase_add_test(tc, test_from_float_to_decimal_ok166);
  tcase_add_test(tc, test_from_float_to_decimal_ok167);
  tcase_add_test(tc, test_from_float_to_decimal_ok168);
  tcase_add_test(tc, test_from_float_to_decimal_ok169);
  tcase_add_test(tc, test_from_float_to_decimal_ok170);
  tcase_add_test(tc, test_from_float_to_decimal_ok171);
  tcase_add_test(tc, test_from_float_to_decimal_ok172);
  tcase_add_test(tc, test_from_float_to_decimal_ok173);
  tcase_add_test(tc, test_from_float_to_decimal_ok174);
  tcase_add_test(tc, test_from_float_to_decimal_ok175);
  tcase_add_test(tc, test_from_float_to_decimal_ok176);
  tcase_add_test(tc, test_from_float_to_decimal_ok177);
  tcase_add_test(tc, test_from_float_to_decimal_ok178);
  tcase_add_test(tc, test_from_float_to_decimal_ok179);
  tcase_add_test(tc, test_from_float_to_decimal_ok180);
  tcase_add_test(tc, test_from_float_to_decimal_ok181);
  tcase_add_test(tc, test_from_float_to_decimal_ok182);
  tcase_add_test(tc, test_from_float_to_decimal_ok183);
  tcase_add_test(tc, test_from_float_to_decimal_ok184);
  tcase_add_test(tc, test_from_float_to_decimal_ok185);
  tcase_add_test(tc, test_from_float_to_decimal_ok186);
  tcase_add_test(tc, test_from_float_to_decimal_ok187);
  tcase_add_test(tc, test_from_float_to_decimal_ok188);
  tcase_add_test(tc, test_from_float_to_decimal_ok189);
  tcase_add_test(tc, test_from_float_to_decimal_ok190);
  tcase_add_test(tc, test_from_float_to_decimal_ok191);
  tcase_add_test(tc, test_from_float_to_decimal_ok192);
  tcase_add_test(tc, test_from_float_to_decimal_ok193);
  tcase_add_test(tc, test_from_float_to_decimal_ok194);
  tcase_add_test(tc, test_from_float_to_decimal_ok195);
  tcase_add_test(tc, test_from_float_to_decimal_ok196);
  tcase_add_test(tc, test_from_float_to_decimal_ok197);
  tcase_add_test(tc, test_from_float_to_decimal_ok198);
  tcase_add_test(tc, test_from_float_to_decimal_ok199);
  tcase_add_test(tc, test_from_float_to_decimal_ok200);
  tcase_add_test(tc, test_from_float_to_decimal_ok201);
  tcase_add_test(tc, test_from_float_to_decimal_ok202);
  tcase_add_test(tc, test_from_float_to_decimal_ok203);
  tcase_add_test(tc, test_from_float_to_decimal_ok204);
  tcase_add_test(tc, test_from_float_to_decimal_ok205);
  tcase_add_test(tc, test_from_float_to_decimal_ok206);
  tcase_add_test(tc, test_from_float_to_decimal_ok207);
  tcase_add_test(tc, test_from_float_to_decimal_ok208);
  tcase_add_test(tc, test_from_float_to_decimal_ok209);
  tcase_add_test(tc, test_from_float_to_decimal_ok210);
  tcase_add_test(tc, test_from_float_to_decimal_ok211);
  tcase_add_test(tc, test_from_float_to_decimal_ok212);
  tcase_add_test(tc, test_from_float_to_decimal_ok213);
  tcase_add_test(tc, test_from_float_to_decimal_ok214);
  tcase_add_test(tc, test_from_float_to_decimal_ok215);
  tcase_add_test(tc, test_from_float_to_decimal_ok216);
  tcase_add_test(tc, test_from_float_to_decimal_ok217);
  tcase_add_test(tc, test_from_float_to_decimal_ok218);
  tcase_add_test(tc, test_from_float_to_decimal_ok219);
  tcase_add_test(tc, test_from_float_to_decimal_ok220);
  tcase_add_test(tc, test_from_float_to_decimal_ok221);
  tcase_add_test(tc, test_from_float_to_decimal_ok222);
  tcase_add_test(tc, test_from_float_to_decimal_ok223);
  tcase_add_test(tc, test_from_float_to_decimal_ok224);
  tcase_add_test(tc, test_from_float_to_decimal_ok225);
  tcase_add_test(tc, test_from_float_to_decimal_ok226);
  tcase_add_test(tc, test_from_float_to_decimal_ok227);
  tcase_add_test(tc, test_from_float_to_decimal_ok228);
  tcase_add_test(tc, test_from_float_to_decimal_ok229);
  tcase_add_test(tc, test_from_float_to_decimal_ok230);
  tcase_add_test(tc, test_from_float_to_decimal_ok231);
  tcase_add_test(tc, test_from_float_to_decimal_ok232);
  tcase_add_test(tc, test_from_float_to_decimal_ok233);
  tcase_add_test(tc, test_from_float_to_decimal_ok234);
  tcase_add_test(tc, test_from_float_to_decimal_ok235);
  tcase_add_test(tc, test_from_float_to_decimal_ok236);
  tcase_add_test(tc, test_from_float_to_decimal_ok237);
  tcase_add_test(tc, test_from_float_to_decimal_ok238);
  tcase_add_test(tc, test_from_float_to_decimal_ok239);
  tcase_add_test(tc, test_from_float_to_decimal_ok240);
  tcase_add_test(tc, test_from_float_to_decimal_ok241);
  tcase_add_test(tc, test_from_float_to_decimal_ok242);
  tcase_add_test(tc, test_from_float_to_decimal_ok243);
  tcase_add_test(tc, test_from_float_to_decimal_ok244);
  tcase_add_test(tc, test_from_float_to_decimal_ok245);
  tcase_add_test(tc, test_from_float_to_decimal_ok246);
  tcase_add_test(tc, test_from_float_to_decimal_ok247);
  tcase_add_test(tc, test_from_float_to_decimal_ok248);
  tcase_add_test(tc, test_from_float_to_decimal_ok249);

  tcase_add_test(tc, test_from_float_to_decimal_ok647);
  tcase_add_test(tc, test_from_float_to_decimal_ok648);
  ///
  tcase_add_test(tc, test_from_float_to_decimal_ok2001);
  tcase_add_test(tc, test_from_float_to_decimal_ok2002);
  tcase_add_test(tc, test_from_float_to_decimal_ok2435);
  tcase_add_test(tc, test_from_float_to_decimal_ok2436);
  // //
  tcase_add_test(tc, test_from_float_to_decimal_ok2691);
  tcase_add_test(tc, test_from_float_to_decimal_ok2692);
  tcase_add_test(tc, test_from_float_to_decimal_ok2693);
  tcase_add_test(tc, test_from_float_to_decimal_ok2694);
  tcase_add_test(tc, test_from_float_to_decimal_ok2695);
  tcase_add_test(tc, test_from_float_to_decimal_ok2696);
  tcase_add_test(tc, test_from_float_to_decimal_ok2697);
  tcase_add_test(tc, test_from_float_to_decimal_ok2698);
  tcase_add_test(tc, test_from_float_to_decimal_ok2699);
  tcase_add_test(tc, test_from_float_to_decimal_ok2700);
  tcase_add_test(tc, test_from_float_to_decimal_ok2701);
  tcase_add_test(tc, test_from_float_to_decimal_ok2702);
  tcase_add_test(tc, test_from_float_to_decimal_ok2703);
  tcase_add_test(tc, test_from_float_to_decimal_ok2704);
  tcase_add_test(tc, test_from_float_to_decimal_ok2705);
  tcase_add_test(tc, test_from_float_to_decimal_ok2706);
  tcase_add_test(tc, test_from_float_to_decimal_ok2707);
  tcase_add_test(tc, test_from_float_to_decimal_ok2708);
  tcase_add_test(tc, test_from_float_to_decimal_ok2709);
  tcase_add_test(tc, test_from_float_to_decimal_ok2710);
  tcase_add_test(tc, test_from_float_to_decimal_ok2711);
  tcase_add_test(tc, test_from_float_to_decimal_ok2712);
  tcase_add_test(tc, test_from_float_to_decimal_ok2713);
  tcase_add_test(tc, test_from_float_to_decimal_ok2714);
  tcase_add_test(tc, test_from_float_to_decimal_ok2715);
  tcase_add_test(tc, test_from_float_to_decimal_ok2716);
  tcase_add_test(tc, test_from_float_to_decimal_ok2717);
  tcase_add_test(tc, test_from_float_to_decimal_ok2718);
  tcase_add_test(tc, test_from_float_to_decimal_ok2719);
  tcase_add_test(tc, test_from_float_to_decimal_ok2720);
  tcase_add_test(tc, test_from_float_to_decimal_ok2721);
  tcase_add_test(tc, test_from_float_to_decimal_ok2722);
  tcase_add_test(tc, test_from_float_to_decimal_ok2723);
  tcase_add_test(tc, test_from_float_to_decimal_ok2724);
  tcase_add_test(tc, test_from_float_to_decimal_ok2725);
  tcase_add_test(tc, test_from_float_to_decimal_ok2726);
  tcase_add_test(tc, test_from_float_to_decimal_ok2727);
  tcase_add_test(tc, test_from_float_to_decimal_ok2728);
  tcase_add_test(tc, test_from_float_to_decimal_ok2729);
  tcase_add_test(tc, test_from_float_to_decimal_ok2730);
  tcase_add_test(tc, test_from_float_to_decimal_ok2731);
  tcase_add_test(tc, test_from_float_to_decimal_ok2732);
  tcase_add_test(tc, test_from_float_to_decimal_ok2733);
  tcase_add_test(tc, test_from_float_to_decimal_ok2734);
  tcase_add_test(tc, test_from_float_to_decimal_ok2735);
  tcase_add_test(tc, test_from_float_to_decimal_ok2736);
  tcase_add_test(tc, test_from_float_to_decimal_ok2737);
  tcase_add_test(tc, test_from_float_to_decimal_ok2738);
  tcase_add_test(tc, test_from_float_to_decimal_ok2739);
  tcase_add_test(tc, test_from_float_to_decimal_ok2740);
  tcase_add_test(tc, test_from_float_to_decimal_ok2741);
  tcase_add_test(tc, test_from_float_to_decimal_ok2742);
  tcase_add_test(tc, test_from_float_to_decimal_ok2743);
  tcase_add_test(tc, test_from_float_to_decimal_ok2744);
  tcase_add_test(tc, test_from_float_to_decimal_ok2745);
  tcase_add_test(tc, test_from_float_to_decimal_ok2746);
  tcase_add_test(tc, test_from_float_to_decimal_ok2747);
  tcase_add_test(tc, test_from_float_to_decimal_ok2748);

  suite_add_tcase(s, tc);
  return s;
}

void tests_from_int_to_decimal(int number, s21_decimal decimal_check) {
  s21_decimal result;
  int code = s21_from_int_to_decimal(number, &result);
  int sign_check = s21_getSign(decimal_check);
  int sign_result = s21_getSign(result);

  ck_assert_int_eq(code, TEST_CONVERSION_OK);
  ck_assert_int_eq(sign_check, sign_result);
}

START_TEST(tests_from_int_to_decimal_fail) {
  int number = -2147483648;
  int result = s21_from_int_to_decimal(number, NULL);

  ck_assert_int_eq(result, TEST_CONVERSION_ERROR);
}
END_TEST

START_TEST(tests_from_int_to_decimal_ok1) {
  int number = -2147483648;
  // Converted the Int32 value -2147483648 to the Decimal value -2147483648.
  s21_decimal decimal_check = {{0x80000000, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok2) {
  int number = -2147483647;
  // Converted the Int32 value -2147483647 to the Decimal value -2147483647.
  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok3) {
  int number = -214748364;
  // Converted the Int32 value -214748364 to the Decimal value -214748364.
  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok4) {
  int number = -214748;
  // Converted the Int32 value -214748 to the Decimal value -214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok5) {
  int number = -1000;
  // Converted the Int32 value -1000 to the Decimal value -1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok6) {
  int number = -1;
  // Converted the Int32 value -1 to the Decimal value -1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x80000000}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok7) {
  int number = 0;
  // Converted the Int32 value 0 to the Decimal value 0.
  s21_decimal decimal_check = {{0x0, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok8) {
  int number = 1;
  // Converted the Int32 value 1 to the Decimal value 1.
  s21_decimal decimal_check = {{0x1, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok9) {
  int number = 1000;
  // Converted the Int32 value 1000 to the Decimal value 1000.
  s21_decimal decimal_check = {{0x3E8, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok10) {
  int number = 214748;
  // Converted the Int32 value 214748 to the Decimal value 214748.
  s21_decimal decimal_check = {{0x346DC, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok11) {
  int number = 214748364;
  // Converted the Int32 value 214748364 to the Decimal value 214748364.
  s21_decimal decimal_check = {{0xCCCCCCC, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok12) {
  int number = 2147483646;
  // Converted the Int32 value 2147483646 to the Decimal value 2147483646.
  s21_decimal decimal_check = {{0x7FFFFFFE, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

START_TEST(tests_from_int_to_decimal_ok13) {
  int number = 2147483647;
  // Converted the Int32 value 2147483647 to the Decimal value 2147483647.
  s21_decimal decimal_check = {{0x7FFFFFFF, 0x0, 0x0, 0x0}};

  tests_from_int_to_decimal(number, decimal_check);
}

Suite *suite_from_int_to_decimal(void) {
  Suite *s = suite_create("\033[45m-=S21_suite_from_int_to_decimal=-\033[0m");
  TCase *tc = tcase_create("case_from_int_to_decimal");

  tcase_add_test(tc, tests_from_int_to_decimal_fail);

  tcase_add_test(tc, tests_from_int_to_decimal_ok1);
  tcase_add_test(tc, tests_from_int_to_decimal_ok2);
  tcase_add_test(tc, tests_from_int_to_decimal_ok3);
  tcase_add_test(tc, tests_from_int_to_decimal_ok4);
  tcase_add_test(tc, tests_from_int_to_decimal_ok5);
  tcase_add_test(tc, tests_from_int_to_decimal_ok6);
  tcase_add_test(tc, tests_from_int_to_decimal_ok7);
  tcase_add_test(tc, tests_from_int_to_decimal_ok8);
  tcase_add_test(tc, tests_from_int_to_decimal_ok9);
  tcase_add_test(tc, tests_from_int_to_decimal_ok10);
  tcase_add_test(tc, tests_from_int_to_decimal_ok11);
  tcase_add_test(tc, tests_from_int_to_decimal_ok12);
  tcase_add_test(tc, tests_from_int_to_decimal_ok13);

  suite_add_tcase(s, tc);
  return s;
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
