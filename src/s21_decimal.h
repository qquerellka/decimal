#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define S21_MAX 79228162514264337593543950335.0F
#define S21_MIN -79228162514264337593543950335.0F

typedef struct {
  unsigned bits[4];
} s21_decimal;

enum enum_error {
  S21_OK = 0,
  S21_FALSE = 0,
  S21_TRUE = 1,
  S21_ERROR_CONVERT = 1,
  S21_NUMBER_INF = 1,
  S21_NUMBER_MIN_INF = 2,
  S21_DEV_BY_ZERO = 3
};

// Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Операторы сравнения
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// Преобразователи
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Другие функции
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);


// Вспомогательные функции 
int s21_get_scale(const s21_decimal *decimal);
void s21_set_scale(s21_decimal *decimal, int scale);
int s21_get_sign(s21_decimal *decimal);
void s21_set_sign(s21_decimal *decimal, int sign);
int s21_is_overflow(s21_decimal value);
void s21_initDecimal(int num3, int num2, int num1, int num0, s21_decimal *num);
int s21_is_zero(s21_decimal *value);
int s21_mul_by_10(s21_decimal *value);
int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);

#endif