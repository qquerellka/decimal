#ifndef S21_FLOAT_PARSERS_H_INCLUDED
#define S21_FLOAT_PARSERS_H_INCLUDED

#include "s21_decimal.h"

int from_f_to_d(float src, s21_decimal *dst);

int from_d_to_f(s21_decimal src, float *dst);
#endif