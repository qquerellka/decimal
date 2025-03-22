#include "s21_decimal.h"

// Получение масштаба (биты 16-23 в bits[3])
int s21_get_scale(const s21_decimal *decimal) {
  return (decimal->bits[3] >> 16) & 0xFF;
}

// Установка масштаба (биты 16-23 в bits[3])
void s21_set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= ~(0xFF << 16);
  decimal->bits[3] |= (scale & 0xFF) << 16;
}

// Получение знака (бит 31 в bits[3])
int s21_get_sign(s21_decimal *decimal) {
  return ((unsigned int)decimal->bits[3] >> 31) & 1;
}

// Установка знака (бит 31 в bits[3])
void s21_set_sign(s21_decimal *decimal, int sign) {
  if (sign) {
    decimal->bits[3] |= (1U << 31);
  } else {
    decimal->bits[3] &= ~(1U << 31);
  }
}

void s21_initDecimal(int num3, int num2, int num1, int num0, s21_decimal *num) {
  num->bits[3] = num3;
  num->bits[2] = num2;
  num->bits[1] = num1;
  num->bits[0] = num0;
}

int s21_is_zero(s21_decimal *value) {
  return (value->bits[0] == 0 && value->bits[1] == 0 && value->bits[2] == 0);
}

int s21_mul_by_10(s21_decimal *value) {
  uint64_t temp = 0;
  uint64_t carry = 0;

  for (int i = 0; i < 3; i++) {
    temp = (uint64_t)value->bits[i] * 10 + carry;
    value->bits[i] = (uint32_t)(temp & 0xFFFFFFFF);
    carry = temp >> 32;
  }

  if (carry) {
    return 0;
  }

  int scale = (value->bits[3] >> 16) & 0xFF;
  if (scale < 28) {
    value->bits[3] &= ~(0xFF << 16);      // Очистка scale
    value->bits[3] |= (scale + 1) << 16;  // Запись нового scale
  } else {
    return 0;
  }

  return 1;
}

int s21_normalize(s21_decimal *value_1, s21_decimal *value_2) {
  int scale1 = s21_get_scale(value_1);
  int scale2 = s21_get_scale(value_2);

  while (scale1 < scale2) {
    if (!s21_mul_by_10(value_1)) return 0;
    scale1++;
  }
  while (scale2 < scale1) {
    if (!s21_mul_by_10(value_2)) return 0;
    scale2++;
  }
  return 1;
}
