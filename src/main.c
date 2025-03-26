#include <stdint.h>
#include <stdio.h>

#include "Float_Parsers.h"
#include "s21_decimal.h"

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
  //
  float cf = -5.75f;

  from_f_to_d(cf, &a);
  printf("cf before = %f\n", cf);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  //
  cf = -120.75678f;

  from_f_to_d(cf, &a);
  printf("cf before = %f\n", cf);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  //
  cf = 0.37507f;

  from_f_to_d(cf, &a);
  printf("cf before = %f\n", cf);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);

  //
  cf = 0.37507e-5f;

  from_f_to_d(cf, &a);
  printf("cf before = %f\n", cf);
  print(a);

  cf = 0;

  from_d_to_f(a, &cf);

  printf("cf after = %f\n\n", cf);
  return 0;
}
