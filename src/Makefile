# Настройки компиляции
PROGRAM = main_check
CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11
#CFLAGS = -g -Wall -Wextra -Werror -std=c11
LIB = -L. -l:s21_decimal.a

# Источники и объекты
SOURCE = $(wildcard *.c)
OBJECTS = $(SOURCE:.c=.o)

# Основные цели
.PHONY: all clean format_project scan_project_on_format rebuild 

all: cp_lib format_project main Float_Parsers $(PROGRAM)

$(PROGRAM): 
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROGRAM) $(LIB) -lm

main: 
	$(CC) $(CFLAGS) -c main.c -o main.o

Float_Parsers: 
	$(CC) $(CFLAGS) -c Float_Parsers.c -o Float_Parsers.o

cp_lib :
	cp ../../C5_s21_decimal-1/src/s21_decimal.a ../../C5_s21_decimal-1/src/s21_decimal.h .

rebuild : clean all run

# Очистка
clean: 
	rm -rf $(OBJECTS) $(PROGRAM) s21_decimal.a s21_decimal.h


# Форматирование кода
format_project:
	clang-format -i *.c *.h 

# Проверка форматирования
scan_project_on_format:
	clang-format -n *.c *.h

run : clean all
	./$(PROGRAM)

