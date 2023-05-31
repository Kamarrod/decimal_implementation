CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS= -Wall -Werror -Wextra -lcheck -lpthread -lm

T_COMPARISONS=t_comparisons.c
T_CONVERTERS=t_from_dec_to_float.c t_from_dec_to_int.c t_from_float_to_dec.c t_from_int_to_dec.c
T_OTHERFUNCS=t_other_functions.c
T_ARIFM=t_add.c t_mul.c t_div.c t_sub.c

SRC = converters.c comparisons.c other_functions.c operations.c functions.c

TST_LIBS = $(shell pkg-config --libs check)

all: clean

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(SRC)
	ar -rcs s21_decimal.a ./*.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $(CFLAGS) $^ $(T_COMPARISONS) $(T_CONVERTERS) $(T_OTHERFUNCS) $(T_ARIFM) tests.c $(TST_LIBS) -o test
	rm -rf *.o
	./test

gcov_report:
# gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
	$(CC) $(T_COMPARISONS) $(T_CONVERTERS) $(T_OTHERFUNCS) $(T_ARIFM) $(SRC) tests.c -o gcov_check.out $(TST_LIBS) --coverage
	./gcov_check.out
	lcov -t "gcheck" -o gcheck.info -c -d . 
	genhtml -o report gcheck.info
	open ./report/index.html

clang:
# cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
# clang-format -n *.c
# clang-format -n *.h


clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf s21_math_test
	rm -rf test
	rm -rf report
	rm -rf *.gcda *.gcno *.gcov
	rm -rf .clang-format
	rm -rf *.out
	rm -rf gcheck.info

rebuild: clean all
