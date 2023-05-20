CC = gcc
CFLAGS = -c -Wall -Werror -Wextra
LDFLAGS= -Wall -Werror -Wextra -lcheck -lpthread -lm

TST_LIBS = $(shell pkg-config --libs check)

all: clean main
main:
	$(CC) $(CFLAGS) s21_decimal.c
	$(CC) s21_decimal.o -o s21_decimal
	./s21_decimal
	rm -rf *.o
s21_decimal.a:
	$(CC) $(CFLAGS) s21_math.c
	ar -rc s21_math.a s21_math.o
	ranlib s21_math.a

test: clean
	$(CC) -c s21_decimal.c tests.c t_add.c 
	$(CC) s21_decimal.o tests.o t_add.o $(TST_LIBS) -o test
	rm -rf *.o
	# ./test
test_conv: clean
	$(CC) -c s21_decimal.c tests.c t_from_dec_to_float.c t_from_dec_to_int.c t_from_float_to_dec.c t_from_int_to_dec.c
	$(CC) s21_decimal.o tests.o t_from_dec_to_float.o t_from_dec_to_int.o t_from_float_to_dec.o t_from_int_to_dec.o $(TST_LIBS) -o test
	rm -rf *.o
	./test
gcov_report_conv:
	gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
	./gcov_check.out
	lcov -t "gcheck" -o gcheck.info -c -d . 
	genhtml -o report gcheck.info
	open ./report/index.html
gcov_report:
	gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
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
