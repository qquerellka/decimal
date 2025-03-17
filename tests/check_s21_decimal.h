#ifndef CHECK_S21_DECIMAL_H_INCLUDED
#define CHECK_S21_DECIMAL_H_INCLUDED
#include <stdio.h>

#include "../src/s21_decimal.h"
// необходима тому же check.h, чтобы взять тот же пустой указатель NULL
#include <stdlib.h>
#include <string.h>
// собственно подключение библиотеки для тестирования
#include <check.h>

Suite *s21_get_scale_suite(void);

#endif