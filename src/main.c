#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "s21_decimal.h"
#include "s21_float_parsers.h"
#include "s21_utils.h"

s21_decimal new_dec() {
  s21_decimal result = {0};
  return result;
}

void print(s21_decimal decimal) {
  printf("Decimal is \n");

  for (int i = 3; i >= 0; i--) {
    printf("\t%d : %u\n", i, decimal.bits[i]);
  }
}

int main(void) {
  s21_decimal a = new_dec();
  int result = 0;
  //
  float cf = -5.75f;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %f\n\n", cf);
  //
  cf = -120.75678f;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  //
  cf = 0.9;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  //
  cf = 0;
  a = new_dec();
  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  cf = NAN;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  s21_FloatUint32_t val = {0};
  val.uint_value = 0x7f800000;
  //  cf = INF;

  printf("Fusk %f %u\n", val.float_value, val.uint_value);
  printf("Fusk %f \n", val.float_value);

  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  val.uint_value = 0xff800000;
  //  cf = - INF;

  printf("Fusk %f %u\n", val.float_value, val.uint_value);
  printf("Fusk %f \n", val.float_value);

  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  val.uint_value = 0xff803500;
  //  cf = - INF;

  printf("Fusk %f %u\n", val.float_value, val.uint_value);
  printf("Fusk %f \n", val.float_value);

  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %f, result = %d\n", cf, result);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  return 0;
}
