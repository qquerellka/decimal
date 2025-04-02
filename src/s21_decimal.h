#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_MAX 7.922816e+28f
//#define S21_MAX 79228162514264337593543950335.0F
#define S21_MIN -79228162514264337593543950335.0F

#define FLOAT_POSITIVE_NAN_MASK 0x7f800000
#define FLOAT_NEGATIVE_NAN_MASK 0xff800000

#define FLOAT_POSITIVE_ZERO_MASK 0x00000000
#define FLOAT_NEGATIVE_ZERO_MASK 0x80000000

#define FLOAT_SIGN_BIT 31
#define FLOAT_TOO_SMALL 1e-28

typedef union float_uint32_t {
  float float_value;
  uint32_t uint_value;
} s21_FloatUint32_t;

typedef struct float_descriptor {
  uint32_t mantisa;
  unsigned char is_minus_sign;
  char scale;
} s21_FloatDescriptor_t;

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
int s21_is_greater(s21_decimal, s21_decimal);
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
int s21_is_zero(s21_decimal *value);
int s21_mul_by_10(s21_decimal *value);
int s21_normalize(s21_decimal *value_1, s21_decimal *value_2);
int s21_div_by_ten(s21_decimal *value);
int s21_get_bit(s21_decimal value, unsigned bit);
void s21_set_bit(s21_decimal *value, unsigned bit, int set);
void s21_left_shift(s21_decimal *value);
int s21_is_float_overflow(double double_value);
int s21_is_float_too_small(double double_value);
int s21_is_float_nan(s21_FloatUint32_t float_box);
int s21_is_float_zero(s21_FloatUint32_t float_box);
void s21_initialize_decimal_as_zero(s21_decimal *decimal);
void s21_set_float_mantisa_in_decimal(s21_decimal *dst, uint32_t uint_value);
int s21_is_decimal_not_zero(s21_decimal *decimal);
double s21_convert_decimal_mantisa_to_double(s21_decimal dec);
s21_FloatUint32_t s21_pack_float_in_int_box(float float_value);
unsigned char s21_get_float_sign(uint32_t float_box);
s21_FloatDescriptor_t s21_get_float_data(s21_FloatUint32_t float_box);
double s21_get_multiplied_result(double decimal_mantissa_value);
double s21_get_frac_result(double decimal_mantissa_value);
double s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, double double_float_box);

#endif