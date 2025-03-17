# Настройки компиляции
LIBRARY = s21_decimal.a
CC = gcc
ARR = ar
RL = ranlib
CFLAGS = -g -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -lcheck -lm -lsubunit
LIB = -L. -l:s21_decimal.a
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
BRANCHES = --rc lcov_branch_coverage=1
GCOV_REPORT_DIR = gcov_report
TESTS_DIR = ../tests
TEST_PROGRAM = $(TESTS_DIR)/check_s21_decimal

# Источники и объекты
SOURCE = $(wildcard *.c)
OBJECTS = $(SOURCE:.c=.o)
TESTS = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJECTS = $(TESTS:.c=.o)

# Основные цели
.PHONY: all clean format_project scan_project_on_format rebuild gcov_report valgrind_test test

all: $(LIBRARY) test gcov_report

$(LIBRARY): $(OBJECTS)
	$(ARR) r $(LIBRARY) $(OBJECTS)
	$(RL) $(LIBRARY)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Тестирование
test: $(LIBRARY) $(TESTS_OBJECTS)
	$(CC) $(CFLAGS) $(TESTS_OBJECTS) -o $(TEST_PROGRAM) $(LIB) $(TEST_FLAGS)
	$(TEST_PROGRAM)

gcov_report :
	$(CC) $(CFLAGS) $(TESTS) $(SOURCE) -o $(TEST_PROGRAM) $(TEST_FLAGS) $(GCOV_FLAGS)
	$(TEST_PROGRAM)
	mkdir -p $(GCOV_REPORT_DIR)
	lcov -t "Report" -c -d $(TESTS_DIR) -o $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)
	genhtml -o $(GCOV_REPORT_DIR)/html $(GCOV_REPORT_DIR)/coverage.info $(BRANCHES)


# Проверка на утечки памяти
valgrind_test:
	valgrind --leak-check=full $(TEST_PROGRAM)

# Очистка
clean: clean_tests_report_files
	rm -rf $(OBJECTS) $(LIBRARY) $(TESTS_OBJECTS) $(TEST_PROGRAM) $(GCOV_REPORT_DIR)

clean_tests_report_files:
	rm -f $(TESTS_DIR)/*.gdna $(TESTS_DIR)/*.gcno $(TESTS_DIR)/*.gcda

# Форматирование кода
format_project:
	clang-format -i *.c *.h $(TESTS_DIR)/*.c $(TESTS_DIR)/*.h

# Проверка форматирования
scan_project_on_format:
	clang-format -n *.c *.h $(TESTS_DIR)/*.c $(TESTS_DIR)/*.h

cppcheck_test:
	cppcheck $(SOURCE)

# Пересборка
rebuild: clean all
