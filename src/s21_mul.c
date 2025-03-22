#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_ERROR_CONVERT;
  *result = (s21_decimal){0};

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);
  int result_sign = sign1 ^ sign2;

  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);
  int result_scale = scale1 + scale2;

  uint64_t temp_res[6] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      uint64_t mult = (uint64_t)value_1.bits[i] * (uint64_t)value_2.bits[j];
      uint64_t sum = temp_res[i + j] + mult;
      temp_res[i + j] = sum & 0xFFFFFFFF;
      temp_res[i + j + 1] += sum >> 32;
    }
  }

  while ((temp_res[3] || temp_res[4] || temp_res[5]) && result_scale > 0) {
    uint64_t remainder = 0;
    for (int i = 5; i >= 0; i--) {
      uint64_t value = (remainder << 32) | temp_res[i];
      temp_res[i] = value / 10;
      remainder = value % 10;
    }
    result_scale--;
  }

  if (temp_res[3] || temp_res[4] || temp_res[5]) {
    return result_sign ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;
  }

  if (result_scale > 28) {
    return result_sign ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;
  }

  result->bits[0] = (uint32_t)temp_res[0];
  result->bits[1] = (uint32_t)temp_res[1];
  result->bits[2] = (uint32_t)temp_res[2];

  s21_set_sign(result, result_sign);
  s21_set_scale(result, result_scale);

  return S21_OK;
}