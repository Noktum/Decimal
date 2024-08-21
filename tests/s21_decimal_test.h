#ifndef SRC_S21_DECIMAL_TEST_H_
#define SRC_S21_DECIMAL_TEST_H_

#include <check.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

#include "../s21_decimal.h"

#define TRUE 1
#define FALSE 0

#define TEST_CONVERSION_OK 0
#define TEST_CONVERSION_ERROR 1

typedef struct {
  int fails;
} fail;

void run_tests(fail *fails);
void run_testcase(Suite *testcase, fail *fails);

Suite *suite_from_int_to_decimal(void);
Suite *suite_from_float_to_decimal(void);

Suite *suite_from_decimal_to_int(void);
Suite *suite_from_decimal_to_float(void);

#endif  //  SRC_S21_DECIMAL_TEST_H_
