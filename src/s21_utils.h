#ifndef S21_UTILS_H_INCLUDED
#define S21_UTILS_H_INCLUDED

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "s21_decimal.h"

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
float s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, double double_float_box);

#endif