# CC = gcc
# CFLAGS = -c -Wall -Werror -Wextra
# LDFLAGS= -Wall -Werror -Wextra -lcheck -lpthread -lm

# TST_LIBS = $(shell pkg-config --libs check)

# all: clean main
# main:
# 	$(CC) $(CFLAGS) s21_decimal.c
# 	$(CC) s21_decimal.o -o s21_decimal
# 	./s21_decimal
# 	rm -rf *.o
# s21_decimal.a:
# 	$(CC) $(CFLAGS) s21_math.c
# 	ar -rc s21_math.a s21_math.o
# 	ranlib s21_math.a

# test: clean
# 	$(CC) -c s21_decimal.c tests.c t_add.c 
# 	$(CC) s21_decimal.o tests.o t_add.o $(TST_LIBS) -o test
# 	rm -rf *.o
# 	./test
# test_conv: clean
# 	$(CC) -c s21_decimal.c tests.c t_from_dec_to_float.c t_from_dec_to_int.c t_from_float_to_dec.c t_from_int_to_dec.c
# 	$(CC) s21_decimal.o tests.o t_from_dec_to_float.o t_from_dec_to_int.o t_from_float_to_dec.o t_from_int_to_dec.o $(TST_LIBS) -o test
# 	rm -rf *.o
# 	./test
# gcov_report_conv:
# 	gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
# 	./gcov_check.out
# 	lcov -t "gcheck" -o gcheck.info -c -d . 
# 	genhtml -o report gcheck.info
# 	open ./report/index.html
# gcov_report:
# 	gcc s21_math.c tests.c -o gcov_check.out $(TST_LIBS) --coverage
# 	./gcov_check.out
# 	lcov -t "gcheck" -o gcheck.info -c -d . 
# 	genhtml -o report gcheck.info
# 	open ./report/index.html

# clang:
# # cp ../materials/linters/.clang-format .
# 	clang-format -i *.c *.h
# # clang-format -n *.c
# # clang-format -n *.h


# clean:
# 	rm -rf *.o
# 	rm -rf *.a
# 	rm -rf s21_math_test
# 	rm -rf test
# 	rm -rf report
# 	rm -rf *.gcda *.gcno *.gcov
# 	rm -rf .clang-format
# 	rm -rf *.out
# 	rm -rf gcheck.info

# rebuild: clean all



CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
OBJ_DIR = obj
GCOV_DIR = gcov
PROJECT_NAME = s21_decimal
TEST_SRC = $(PROJECT_NAME)_test.c
LIB_SRC_DIR = functions
TEST_BIN = $(OBJ_DIR)/tests/$(PROJECT_NAME)_test
OS := $(shell uname -s)
LIB_SOURCES = $(shell find $(LIB_SRC_DIR) -name '*.c')
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(LIB_SOURCES))
HS = $(shell find . -name '*.h')
TEST_FLAGS = -lcheck

ifeq ($(OS), Darwin)
	OPEN_CMD = open
	ADD_FLAGS =
endif

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open
	ADD_FLAGS = -lrt -lpthread -lm -lsubunit
endif

$(OBJ_DIR)/%.o: %.c $(HS)
	$(CC) $(CFLAGS) $(ADD_FLAGS) -I . $< -c -o $@

create_obj_files: $(OBJS)

$(PROJECT_NAME).a: create_obj_files
	ar rcs $@ $(OBJ_DIR)/$(LIB_SRC_DIR)/*.o
	ranlib $@

test: $(TEST_SRC) $(PROJECT_NAME).a
	$(CC) $(CFLAGS) $^ -o $(TEST_BIN) $(TEST_FLAGS) $(ADD_FLAGS)
	@echo s21_string: Check leaks
ifeq ($(OS), Linux)
	valgrind --tool=memcheck --vgdb=no --trace-children=yes --log-file=RESULT_VALGRIND.log ./$(TEST_BIN)
# tail -n 9 RESULT_VALGRIND.log
else
	leaks -quiet --atExit -- ./$(TEST_BIN)
endif

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n $(LIB_SRC_DIR)/*.c
# clang-format -n $(LIB_SRC_DIR)/*.h
	clang-format -n *.c *.h

clang-replace:
	cp ../materials/linters/.clang-format .
	clang-format -i $(LIB_SRC_DIR)/*.c
# clang-format -i $(LIB_SRC_DIR)/*.h
	clang-format -i *.c *.h

install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov
	brew install gcovr

install_libs:
	brew install lcov
	brew install gcovr

add_report_flags:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage -fPIC)
	@echo s21_stringplus: Check build

gcov_report: clean add_report_flags test
	gcov *.c -o ${LIB_SRC_DIR}/*.c -o $(OBJ_DIR)/*
	mv *.gc* ./gcov/
	mv $(OBJ_DIR)/*/*.gc* ./gcov/
	lcov -t gcov/ -o report.info -c -d gcov/
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

clear:
	clear

clean:
	rm -rf *.info
	rm -rf report/
	rm -rf *.dSYM
	rm -rf *.a
	rm -rf RESULT_VALGRIND.log
	rm -rf $(GCOV_DIR)/*
	rm -rf $(OBJ_DIR)/$(LIB_SRC_DIR)/*.o
	rm -rf $(OBJ_DIR)/$(LIB_SRC_DIR)/*.gcno
	rm -rf $(OBJ_DIR)/tests/*.gcno
	rm -rf $(TEST_BIN)
	clear

.PHONY: test gcov_report clean all $(PROJECT_NAME).a add_report_flags clang clang-replace
