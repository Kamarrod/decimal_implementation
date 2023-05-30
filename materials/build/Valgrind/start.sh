#!/bin/bash

make test
# gcc -g test_s21_string.c s21_string.a -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
gcc -g s21_decimal.c t_other_functions.c s21_other_functions.c functions.c s21_mul.c s21_div.c  s21_add.c s21_sub.c comparisons.c -o test -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test
# valgrind --leak-check=full -s --show-leak-kinds=all ./test
