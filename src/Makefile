# FL = -Werror -Wextra -Wall -std=c11
# LFL = -lcheck -lsubunit -lpthread -lm
# GCOV = -fprofile-arcs -ftest-coverage

# SRC_FILES = $(wildcard *.c) 
# HEADER_FILES = $(wildcard *.h)
# OBJ_FILES = $(SRC_FILES:.c=.o)

# all: s21_decimal.a

# s21_decimal.a: $(OBJ_FILES) 
# 	ar rc $@ $^
# 	ranlib s21_decimal.a

# %.o: %.c
# 	gcc $(FL) -c -o $@ $<

# gcov_report: 
# 	make test
# 	lcov --capture --directory . --output-file coverage.info
# 	genhtml coverage.info -o coverage_html

# test: clean
# 	make s21_decimal.a
# 	gcc $(SRC_FILES) test/test.c s21_decimal.a -o testfile $(FL) $(LFL) $(GCOV)
# 	./testfile

# clean:
# 	rm -rf *.o *.gcno *.gcda *.c.gcov *.a *.info math main a.out testfile coverage_html

# main: 
# 	gcc $(SRC_FILES)
# 	./a.out

# clang: 
# 	clang-format -i $(SRC_FILES) $(HEADER_FILES)
# 	clang-format -i test/test.c

# cpp:
# 	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC_FILES)




CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
MAC_FLAGS=-lcheck -lm
LINUX_FLAGS=-lcheck -lm -lrt -lpthread -lsubunit
GCOV_FLAGS=-fprofile-arcs -ftest-coverage

FILES=$(wildcard s21_*.c)
OBJ=$(patsubst %o, %o, $(patsubst %.c,%.o,$(FILES)))
TEST_FILES = $(wildcard tests/test.c)
USERNAME=$(shell whoami)

MYLIB = s21_decimal.a

OS := $(shell uname -s)

ifeq ($(OS),Darwin)
	OPEN=open
endif
ifeq ($(OS),Linux)
	OPEN=xdg-open
endif

all: s21_decimal.a

.PHONY: all test memory_test s21_decimal.a gcov_report clean rebuild

s21_decimal.a: $(FILES)
	$(CC) -c $(FLAGS) $(FILES)
	ar rc $@ $(OBJ)
	ranlib $@
	rm -rf *.o

test: s21_decimal.a
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(TEST_FILES) $< -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(TEST_FILES) $< -o test $(LINUX_FLAGS)
endif
	./test


gcov_report: clean
ifeq ($(OS),Darwin)
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(MAC_FLAGS)
else
	$(CC) $(FLAGS) $(GCOV_FLAGS) $(FILES) $(TEST_FILES) -o test $(LINUX_FLAGS)
endif
	./test
	rm test
	lcov -t "s21_test" -o postreport.info -c -d .
	genhtml -o report postreport.info
	$(OPEN) report/index.html


style_check:
	clang-format -i -style=google tests/*.c tests/*.h *.c *.h
	clang-format -n -style=google tests/*.c tests/*.h *.c *.h


clean_obj:
	rm -rf obj/*.o *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_test clean_obj
	rm -rf unit_test

rebuild: clean all


