#include "main.h"

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

int s21_is_overflow(s21_decimal value) {
  s21_decimal max_value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  return (value.bits[2] > max_value.bits[2] ||
          (value.bits[2] == max_value.bits[2] &&
           value.bits[1] > max_value.bits[1]) ||
          (value.bits[2] == max_value.bits[2] &&
           value.bits[1] == max_value.bits[1] &&
           value.bits[0] > max_value.bits[0]));
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) return 1;
    if (a.bits[i] < b.bits[i]) return 0;
  }
  return 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return S21_ERROR_CONVERT;
  }
  dst->bits[0] = abs(src);
  dst->bits[2] = dst->bits[1] = 0;
  s21_set_scale(dst, 0);
  s21_set_sign(dst, src < 0);
  return S21_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (dst == NULL || isnan(src) || isinf(src) || src >= S21_MAX ||
      src <= S21_MIN) {
    return S21_ERROR_CONVERT;
  }
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }

  int scale = 0;
  while (scale < 28 && src - (long long)src != 0.0) {
    src *= 10;
    scale++;
  }
  unsigned long long mantissa = (unsigned long long)src;

  dst->bits[0] = (unsigned int)(mantissa & 0xFFFFFFFF);
  dst->bits[1] = (unsigned int)((mantissa >> 32) & 0xFFFFFFFF);
  dst->bits[2] = 0;

  s21_set_scale(dst, scale);

  return S21_OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return S21_ERROR_CONVERT;
  }
  int scale = s21_get_scale(&src);
  long long mantissa = (long long)src.bits[0] | ((long long)src.bits[1] << 32);

  for (int i = 0; i < scale; i++) {
    mantissa /= 10;
  }
  if (s21_get_sign(&src)) {
    mantissa = -mantissa;
  }
  if (mantissa > INT_MAX || mantissa < INT_MIN) {
    return S21_ERROR_CONVERT;
  }
  *dst = (int)mantissa;
  return S21_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return S21_ERROR_CONVERT;
  }
  int scale = s21_get_scale(&src);
  long long mantissa = (long long)src.bits[0] | ((long long)src.bits[1] << 32);

  float result = (float)mantissa / powf(10, scale);
  if (s21_get_sign(&src)) {
    result = -result;
  }
  *dst = result;
  return S21_OK;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_ERROR_CONVERT;
  *result = (s21_decimal){0};

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);
  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);
  int target_scale = (scale1 > scale2) ? scale1 : scale2;

  if (sign1 == sign2) {
    uint64_t temp_sum = 0;
    uint32_t carry = 0;

    for (int i = 0; i < 3; i++) {
      temp_sum = (uint64_t)value_1.bits[i] + (uint64_t)value_2.bits[i] + carry;
      result->bits[i] = (uint32_t)(temp_sum & 0xFFFFFFFF);
      carry = (uint32_t)(temp_sum >> 32);
    }

    if (carry) return sign1 ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;
    s21_set_sign(result, sign1);
  } else {
    s21_set_sign(&value_2, sign1);
    return s21_sub(value_1, value_2, result);
  }

  s21_set_scale(result, target_scale);
  return S21_OK;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result) return S21_ERROR_CONVERT;
  *result = (s21_decimal){0};

  int sign1 = s21_get_sign(&value_1);
  int sign2 = s21_get_sign(&value_2);
  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);
  int target_scale = (scale1 > scale2) ? scale1 : scale2;

  if (sign1 != sign2) {
    s21_set_sign(&value_2, sign1);
    return s21_add(value_1, value_2, result);
  }

  int greater =
      (value_1.bits[2] > value_2.bits[2]) ||
      (value_1.bits[2] == value_2.bits[2] &&
       value_1.bits[1] > value_2.bits[1]) ||
      (value_1.bits[2] == value_2.bits[2] &&
       value_1.bits[1] == value_2.bits[1] && value_1.bits[0] > value_2.bits[0]);

  s21_decimal max = greater ? value_1 : value_2;
  s21_decimal min = greater ? value_2 : value_1;

  uint64_t temp_sub = 0;
  int borrow = 0;
  for (int i = 0; i < 3; i++) {
    if (max.bits[i] >= min.bits[i] + borrow) {
      temp_sub = (uint64_t)max.bits[i] - min.bits[i] - borrow;
      borrow = 0;
    } else {
      temp_sub = (uint64_t)max.bits[i] + 0x100000000 - min.bits[i] - borrow;
      borrow = 1;
    }
    result->bits[i] = (uint32_t)temp_sub;
  }

  if (s21_is_overflow(*result)) return S21_NUMBER_MIN_INF;

  s21_set_sign(result, greater ? sign1 : !sign1);
  s21_set_scale(result, target_scale);
  return S21_OK;
}

int main() {
  s21_decimal a, b;
  s21_from_int_to_decimal(-214748364, &a);
  s21_from_int_to_decimal(20000000, &b);
  printf("%u\n", a.bits[0]);
  printf("%u\n", b.bits[0]);

  int l, g;
  s21_from_decimal_to_int(a, &l);
  s21_from_decimal_to_int(b, &g);
  printf("%d\n", l);
  printf("%d\n", g);

  s21_decimal a1, b1;
  s21_from_float_to_decimal(5.12345e2, &a1);
  s21_from_float_to_decimal(-1234.121e2, &b1);
  printf("%u\n", a1.bits[0]);
  printf("%u\n", b1.bits[0]);

  float ar, arr;
  s21_from_decimal_to_float(a1, &ar);
  s21_from_decimal_to_float(b1, &arr);
  printf("%lf\n", ar);
  printf("%lf\n", arr);
  printf("%d ", s21_get_scale(&a1));
  printf("%d \n", s21_get_scale(&b1));

  float src = 123456789012345.00f;
  s21_decimal dec;
  s21_from_float_to_decimal(src, &dec);

  printf("bits[0] = %u\n", dec.bits[0]);
  printf("bits[1] = %u\n", dec.bits[1]);
  printf("bits[2] = %u\n", dec.bits[2]);
  s21_from_decimal_to_float(dec, &src);
  printf("%lf\n", src);

  s21_decimal z = {{10, 10100, 1011, 0}};
  s21_decimal x = {{10, 110111, 1101, 0}};
  s21_decimal result_1;
  int code_1 = s21_add(z, x, &result_1);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_1.bits[0],
         result_1.bits[1], result_1.bits[2], result_1.bits[3], code_1);

  s21_decimal ag = {{100, 0, 0, 0}};
  s21_decimal bg = {{50, 0, 0, 1 << 31}};
  s21_decimal result_2;
  int code_2 = s21_add(ag, bg, &result_2);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_2.bits[0],
         result_2.bits[1], result_2.bits[2], result_2.bits[3], code_2);

  s21_decimal al = {{200, 0, 0, 1 << 31}};
  s21_decimal bl = {{300, 0, 0, 1 << 31}};
  s21_decimal result_3;
  int code_3 = s21_add(al, bl, &result_3);
  int sign_12 = s21_get_sign(&result_3);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_3.bits[0],
         result_3.bits[1], result_3.bits[2], sign_12, code_3);

  s21_decimal all = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal bll = {{1, 0, 0, 0}};
  s21_decimal result_4;
  int code_4 = s21_add(all, bll, &result_4);

  printf("Code: %d\n", code_4);

  s21_decimal aa = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 31}};
  s21_decimal bb = {{1, 0, 0, 1 << 31}};
  s21_decimal result_5;
  int code_5 = s21_add(aa, bb, &result_5);

  printf("Code: %d\n", code_5);

  s21_decimal ag1 = {{500, 0, 0, 0}};
  s21_decimal bg1 = {{200, 0, 0, 0}};
  s21_decimal result_6;
  int code_6 = s21_sub(ag1, bg1, &result_6);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_6.bits[0],
         result_6.bits[1], result_6.bits[2], result_6.bits[3], code_6);

  s21_decimal ag2 = {{500, 0, 0, 0}};
  s21_decimal bg2 = {{300, 0, 0, 1 << 31}};
  s21_decimal result_7;
  int code_7 = s21_sub(ag2, bg2, &result_7);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_7.bits[0],
         result_7.bits[1], result_7.bits[2], result_7.bits[3], code_7);

  s21_decimal ag3 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal bg3 = {{1, 0, 0, 0}};
  s21_decimal result_8;
  int code_8 = s21_sub(ag3, bg3, &result_8);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_8.bits[0],
         result_8.bits[1], result_8.bits[2], result_8.bits[3], code_8);

  s21_decimal ag4 = {{1, 0, 0, 1 << 31}};
  s21_decimal bg4 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result_9;
  int code_9 = s21_sub(ag4, bg4, &result_9);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_9.bits[0],
         result_9.bits[1], result_9.bits[2], result_9.bits[3], code_9);

  s21_decimal ag5 = {{1000, 0, 0, 0}};
  s21_decimal bg5 = {{50, 0, 0, 0}};
  s21_decimal result_10;
  int code_10 = s21_sub(ag5, bg5, &result_10);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_10.bits[0],
         result_10.bits[1], result_10.bits[2], result_10.bits[3], code_10);

  return 0;
}
