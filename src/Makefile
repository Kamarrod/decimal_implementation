CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

T_COMPARISONS=t_comparisons.c
T_CONVERTERS=t_from_dec_to_float.c t_from_dec_to_int.c t_from_float_to_dec.c t_from_int_to_dec.c
T_OTHERFUNCS=t_other_functions.c
T_ARIFM=t_add.c t_mul.c t_div.c t_sub.c

SRC = converters.c comparisons.c other_functions.c functions.c

TST_LIBS = $(shell pkg-config --libs check)

ifeq ($(OS), Darwin)
	OPEN_CMD = open
	ADD_FLAGS =
endif

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	ADD_FLAGS = -lrt -lpthread -lm -lsubunit
endif


all: clean test

s21_decimal.a:
	$(CC) $(CFLAGS) -c $(SRC)
	ar -rcs s21_decimal.a ./*.o
	ranlib s21_decimal.a

test: s21_decimal.a
	$(CC) $^ $(T_COMPARISONS) $(T_CONVERTERS) $(T_OTHERFUNCS) $(T_ARIFM) $(SRC) tests.c $(CFLAGS) $(ADD_FLAGS) -lcheck -o test
	rm -rf *.o
	./test

valgrind: clean test
	valgrind --tool=memcheck --vgdb=no --trace-children=yes ./test

gcov_report:
	$(CC) $(T_COMPARISONS) $(T_CONVERTERS) $(T_OTHERFUNCS) $(T_ARIFM) $(SRC) tests.c -o gcov_check.out $(TST_LIBS) -lcheck --coverage
	./gcov_check.out
	lcov -t "gcheck" -o gcheck.info -c -d . 
	genhtml -o report gcheck.info
	open ./report/index.html

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h


clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.log
	rm -rf test
	rm -rf report
	rm -rf *.gcda *.gcno *.gcov
	rm -rf .clang-format
	rm -rf *.out
	rm -rf gcheck.info

rebuild: clean all
