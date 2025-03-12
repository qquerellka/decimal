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

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) {
    return S21_FALSE;
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
    return S21_FALSE;
  }
  dst->bits[0] = dst->bits[1] = dst->bits[2] = dst->bits[3] = 0;

  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }
  // char buffer[100];
  // snprintf(buffer, sizeof(buffer), "%f", src);

  // char *point_pos = strchr(buffer, '.');
  // int scale = 0;
  // if (point_pos != NULL) {
  //   scale = strlen(point_pos + 1);
  //   memmove(point_pos, point_pos + 1, strlen(point_pos)+1);
  // }

  int scale = 0;
  while (scale < 28 && src - (long long)src != 0.0) {
    src *= 10;
    scale++;
  }

  // unsigned long long mantissa = strtoull(buffer, NULL, 10);
  unsigned long long mantissa = (unsigned long long)src;

  dst->bits[0] = (unsigned int)(mantissa & 0xFFFFFFFF);
  dst->bits[1] = (unsigned int)((mantissa >> 32) & 0xFFFFFFFF);
  dst->bits[2] = 0;

  s21_set_scale(dst, scale);

  return S21_OK;
}

// Конвертация decimal в int
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) {
    return S21_FALSE;
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
    return S21_FALSE;
  }
  *dst = (int)mantissa;
  return S21_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (dst == NULL) {
    return S21_FALSE;
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
  s21_from_float_to_decimal(5.123456E+2, &a1);
  s21_from_float_to_decimal(-1234.12123, &b1);
  printf("%u\n", a1.bits[0]);
  printf("%u\n", b1.bits[0]);

  float ar, arr;
  s21_from_decimal_to_float(a1, &ar);
  s21_from_decimal_to_float(b1, &arr);
  printf("%lf\n", ar);
  printf("%lf\n", arr);
  printf("%d ", s21_get_scale(&a1));
  printf("%d \n", s21_get_scale(&b1));

  float src = 123456789012345.00;
  s21_decimal dec;
  s21_from_float_to_decimal(src, &dec);

  printf("bits[0] = %u\n", dec.bits[0]);
  printf("bits[1] = %u\n", dec.bits[1]);
  printf("bits[2] = %u\n", dec.bits[2]);
  s21_from_decimal_to_float(dec, &src);
  printf("%lf\n", src);

  return 0;
}
