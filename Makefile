FLAGS = -Wall -Wextra -Werror
CHF = -lcheck -lsubunit -lm
SRC = $(wildcard functions/*.c)
SRC_OBJ = $(SRC:.c=.o)

.PHONY: test clean all

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
CHF += -lsubunit -lm
endif

all: clean s21_decimal.a

s21_decimal.a: clean $(SRC_OBJ)
	ar -rcs $@ $(SRC_OBJ)
	ar -rcs libs21_decimal.a $(SRC_OBJ)
	cp libs21_decimal.a s21_decimal.a

gcov_report: clean
	gcc $(FLAGS) --coverage tests/comp_test.c functions/*.c -o test $(CHF)
	gcc $(FLAGS) --coverage tests/test_arith.c functions/*.c -o test1 $(CHF)
	gcc $(FLAGS) --coverage tests/test_floor.c functions/*.c -o test2 $(CHF)
	gcc $(FLAGS) --coverage tests/test_round.c functions/*.c -o test3 $(CHF)
	gcc $(FLAGS) --coverage tests/s21_decimal_test.c functions/*.c -o test4 $(CHF)
	./test
	./test1
	./test2
	./test3
	./test4
	lcov -d . -c -o coverage.info
	genhtml -o coverage coverage.info
	open coverage/index.html
	rm *.gcda *.gcno *.info

test: clean
	gcc $(FLAGS) tests/comp_test.c functions/*.c -o test $(CHF)
	gcc $(FLAGS) tests/test_arith.c functions/*.c -o test1 $(CHF)
	gcc $(FLAGS) tests/test_floor.c functions/*.c -o test2 $(CHF)
	gcc $(FLAGS) tests/test_round.c functions/*.c -o test3 $(CHF)
	gcc $(FLAGS) tests/s21_decimal_test.c functions/*.c -o test4 $(CHF)
	./test
	./test1
	./test2
	./test3
	./test4

clean:
	rm -rf *.out *.a functions/*.o *.o *.gcda *.gcno test test1 test2 test3 test4 *.info coverage