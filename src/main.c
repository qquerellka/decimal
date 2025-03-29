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
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);
  //
  cf = -120.75678f;
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  //
  cf = 0.9;
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  //
  cf = 0;
  a = new_dec();
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  cf = NAN;
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  s21_FloatUint32_t val = {0};
  // val.uint_value = 0x7f800000;
  // //  cf = INF;

  // printf("Fusk %f %u\n", val.float_value, val.uint_value);
  // printf("Fusk %f \n", val.float_value);

  // cf = val.float_value;

  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);

  // cf = 0;

  // from_d_to_f(a, &cf);

  // printf("cf after = %f\n\n", cf);

  // val.uint_value = 0xff800000;
  // //  cf = - INF;

  // printf("Fusk %f %u\n", val.float_value, val.uint_value);
  // printf("Fusk %f \n", val.float_value);

  // cf = val.float_value;

  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);

  // cf = 0;

  // from_d_to_f(a, &cf);

  // printf("cf after = %f\n\n", cf);

  // val.uint_value = 0xff803500;
  // //  cf = - INF;

  // printf("Fusk %f %u\n", val.float_value, val.uint_value);
  // printf("Fusk %f \n", val.float_value);

  // cf = val.float_value;

  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);

  // cf = 0;

  // from_d_to_f(a, &cf);

  // printf("cf after = %f\n\n", cf);

  // cf = 7.53e-15;
  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);
  // cf = 0;
  // from_d_to_f(a, &cf);
  // printf("cf after = %29.15f\n\n", cf);

  // val.uint_value = 0x80000000;
  // cf = val.float_value;
  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);
  // cf = 0;
  // from_d_to_f(a, &cf);
  // printf("cf after = %29.29f\n\n", cf);

  // val.uint_value = 0x0000000000;
  // cf = val.float_value;
  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);
  // cf = 0;
  // from_d_to_f(a, &cf);
  // printf("cf after = %29.29f\n\n", cf);

  // cf = 0;
  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f, result = %d\n", cf, result);
  // print(a);
  // cf = 0;
  // from_d_to_f(a, &cf);
  // printf("cf after = %29.29f\n\n", cf);

  //
  cf = 0.15625;
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = 792281625;
  cf = val.float_value;
  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = 0.0792281625;
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  // val.float_value = 79.22800;
  // cf = val.float_value;

  // result = from_f_to_d(cf, &a);
  // printf("cf before = %f uint = %u, result = %d\n", cf, val.uint_value,
  // result); print(a);
  // // cf = 0;
  // //  from_d_to_f(a, &cf);
  // //  printf("cf after = %15.29f\n\n", cf);

  // printf("float in decimal form is:\n");
  // s21_from_float_to_decimal(456.789345f, &a);
  // printf("3: %u\n2: %u\n1: %u\n0: %u\n\nreal scale = %d\n", a.bits[3],
  //        a.bits[2], a.bits[1], a.bits[0], s21_get_scale(&a));
  // float part = a.bits[0];

  // for (int i = 0; i < 4; i++) {
  //   part /= 10;
  // }

  // printf("float = %.9f\n", part);

  val.float_value = 5.75;
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = pow(2, 96);
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = -pow(2, 96);
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = 1e-29;
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  val.float_value = -1e-29;
  cf = val.float_value;

  result = from_f_to_d(cf, &a);
  printf("cf before = %E, result = %d\n", cf, result);
  print(a);
  cf = 0;
  from_d_to_f(a, &cf);
  printf("cf after = %E\n\n", cf);

  return 0;
}
