#include "s21_decimal.h"

int s21_get_scale(const s21_decimal *decimal) {
  return (decimal->bits[3] >> 16) & 0xFF;
}

void s21_set_scale(s21_decimal *decimal, int scale) {
  decimal->bits[3] &= ~(0xFF << 16);
  decimal->bits[3] |= (scale & 0xFF) << 16;
}

int s21_get_sign(s21_decimal *decimal) {
  return ((unsigned int)decimal->bits[3] >> 31) & 1;
}

void s21_set_sign(s21_decimal *decimal, int sign) {
  if (sign) {
    decimal->bits[3] |= (1U << 31);
  } else {
    decimal->bits[3] &= ~(1U << 31);
  }
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
    value->bits[3] &= ~(0xFF << 16);
    value->bits[3] |= (scale + 1) << 16;
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

int s21_div_by_ten(s21_decimal *value) {
  uint64_t temp = 0;
  uint64_t remainder = 0;
  for (int i = 2; i >= 0; i--) {
    temp = (uint64_t)(value->bits[i]) + (remainder << 32);
    value->bits[i] = (uint32_t)(temp / 10);
    remainder = temp % 10;
  }
  return (uint32_t)remainder;
}

// ==============================================

// int s21_get_bit(unsigned value, unsigned bit) {
//   uint32_t temp = 1;
//   uint32_t code = 0;
//   temp = temp << bit;
//   if (value & temp) {
//     code = 1;
//   }
//   return code;
// }

// void s21_multiply_by_10_96(uint32_t *quotient, uint32_t *remainder) {
//   // Умножаем все 96 бит на 10
//   uint64_t tmp1 = (uint64_t)quotient[0] * 10;
//   uint64_t tmp2 = (uint64_t)quotient[1] * 10;
//   uint64_t tmp3 = (uint64_t)quotient[2] * 10;

//   quotient[0] = (uint32_t)(tmp1 & 0xFFFFFFFF);
//   quotient[1] = (uint32_t)(tmp2 & 0xFFFFFFFF);
//   quotient[2] = (uint32_t)(tmp3 & 0xFFFFFFFF);

//   tmp1 = (uint64_t)remainder[0] * 10;
//   tmp2 = (uint64_t)remainder[1] * 10;
//   tmp3 = (uint64_t)remainder[2] * 10;

//   remainder[0] = (uint32_t)(tmp1 & 0xFFFFFFFF);
//   remainder[1] = (uint32_t)(tmp2 & 0xFFFFFFFF);
//   remainder[2] = (uint32_t)(tmp3 & 0xFFFFFFFF);
// }

// void s21_shift_left_96(uint32_t num[3], int shift) {
//   while (shift--) {
//     num[2] = (num[2] << 1) | (num[1] >> 31);
//     num[1] = (num[1] << 1) | (num[0] >> 31);
//     num[0] = (num[0] << 1);
//   }
// }

// int s21_is_greater_or_equal_96(uint32_t num1[3], uint32_t num2[3]) {
//   for (int i = 2; i >= 0; i--) {
//     if (num1[i] > num2[i]) return 1;
//     if (num1[i] < num2[i]) return 0;
//   }
//   return 1;
// }

// void s21_sub_96(uint32_t num1[3], uint32_t num2[3]) {
//   uint64_t borrow = 0;
//   for (int i = 0; i < 3; i++) {
//     uint64_t tmp = (uint64_t)num1[i] - num2[i] - borrow;
//     num1[i] = (uint32_t)tmp;
//     borrow = (tmp >> 32) & 1;
//   }
// }

// void s21_set_bit_96(uint32_t num[3], int bit) {
//   num[bit / 32] |= (1U << (bit % 32));
// }

// int s21_is_zero_96(uint32_t num[3]) {
//   return (num[0] == 0 && num[1] == 0 && num[2] == 0);
// }

// void s21_add_96(uint32_t num[3], uint32_t value) {
//   uint64_t tmp = (uint64_t)num[0] + value;
//   num[0] = (uint32_t)tmp;
//   tmp = (uint64_t)num[1] + (tmp >> 32);
//   num[1] = (uint32_t)tmp;
//   tmp = (uint64_t)num[2] + (tmp >> 32);
//   num[2] = (uint32_t)tmp;
// }
