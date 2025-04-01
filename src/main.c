#include <math.h>
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
  int result_fd = 0;
  int result_df = 0;
  //
  float testing_f = -5.75f;
  float control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-7) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("\n\n");

  testing_f = -120.75678f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-5) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-5 = \t\t%f\n\n", 1e-5);

  testing_f = 0.9f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-7) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-7 = \t\t%f\n\n", 1e-7);

  //------------------------------------------------------------------------------------------------------------//
    // cf = 0;
    // a = new_dec();
    // result = from_f_to_d(cf, &a);
    // printf("cf before = %E, result = %d\n", cf, result);
    // print(a);
    // cf = 0;
    // from_d_to_f(a, &cf);
    // printf("cf after = %E\n\n", cf);

    // cf = NAN;
    // result = from_f_to_d(cf, &a);
    // printf("cf before = %E, result = %d\n", cf, result);
    // print(a);
    // cf = 0;
    // from_d_to_f(a, &cf);
    // printf("cf after = %E\n\n", cf);

    // s21_FloatUint32_t val = {0};
    // // val.uint_value = 0x7f800000;
    // // //  cf = INF;

    // // printf("Fusk %f %u\n", val.float_value, val.uint_value);
    // // printf("Fusk %f \n", val.float_value);

    // // cf = val.float_value;

    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);

    // // cf = 0;

    // // from_d_to_f(a, &cf);

    // // printf("cf after = %f\n\n", cf);

    // // val.uint_value = 0xff800000;
    // // //  cf = - INF;

    // // printf("Fusk %f %u\n", val.float_value, val.uint_value);
    // // printf("Fusk %f \n", val.float_value);

    // // cf = val.float_value;

    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);

    // // cf = 0;

    // // from_d_to_f(a, &cf);

    // // printf("cf after = %f\n\n", cf);

    // // val.uint_value = 0xff803500;
    // // //  cf = - INF;

    // // printf("Fusk %f %u\n", val.float_value, val.uint_value);
    // // printf("Fusk %f \n", val.float_value);

    // // cf = val.float_value;

    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);

    // // cf = 0;

    // // from_d_to_f(a, &cf);

    // // printf("cf after = %f\n\n", cf);

    // // cf = 7.53e-15;
    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);
    // // cf = 0;
    // // from_d_to_f(a, &cf);
    // // printf("cf after = %29.15f\n\n", cf);

    // // val.uint_value = 0x80000000;
    // // cf = val.float_value;
    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);
    // // cf = 0;
    // // from_d_to_f(a, &cf);
    // // printf("cf after = %29.29f\n\n", cf);

    // // val.uint_value = 0x0000000000;
    // // cf = val.float_value;
    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);
    // // cf = 0;
    // // from_d_to_f(a, &cf);
    // // printf("cf after = %29.29f\n\n", cf);

    // // cf = 0;
    // // result = from_f_to_d(cf, &a);
    // // printf("cf before = %f, result = %d\n", cf, result);
    // // print(a);
    // // cf = 0;
    // // from_d_to_f(a, &cf);
    // // printf("cf after = %29.29f\n\n", cf);
  //------------------------------------------------------------------------------------------------------------//

  testing_f = 0.15625f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-6) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-6 = \t\t%f\n\n", 1e-6);

  testing_f = 792281625.0f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e2) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e2 = \t\t%f\n\n", 1e2);

  testing_f = 0.0792281625f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-7) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-7 = \t\t%f\n\n", 1e-7);

  //fail...
  testing_f = 79.22800735f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-6) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-6 = \t\t%f\n\n", 1e-6);

  //fail if 1e-5
  testing_f = 456.789345f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-4) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-4 = \t\t%f\n\n", 1e-4);

  testing_f = 5.75f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-4) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-4 = \t\t%f\n\n", 1e-4);

  //работает корректно
   testing_f = 79.22816E+28f;
   control_f = testing_f;
   result_fd = from_f_to_d(testing_f, &a);
   print(a);
   testing_f = 0;
   result_df = from_d_to_f(a, &testing_f);
   printf(
       "result = %d, testing_f before\t%f\nresult = %d, testing_f"
       "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-4) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-4 = \t\t%f\n\n", 1e-4);

  testing_f = 7.922816E+28f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e21) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e21 = \t\t\t\t%f\n\n", 1e21);

  testing_f = 1e-28f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e21) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e21 = \t\t\t\t%f\n\n", 1e21);

  testing_f = 1e-29f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e21) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e21 = \t\t\t\t%f\n\n", 1e21);

  //fail if 1e-1
  testing_f = 2147483.647f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-1) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-1 is \t\t\t\t%f\n\n", 1e-1);

  //fail if 1e-1
  testing_f = -2147483.647f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f"
      "after\t%f\n", result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e-1) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e-1 is \t\t\t\t%f\n\n", 1e-1);

  testing_f = 18446744073709617151.0f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  a.bits[3] = 0;
  a.bits[2] = 1;
  a.bits[1] = 0;
  a.bits[0] = 0;
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f after\t%f\n",
      result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e13) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e13 is \t\t\t\t%f\n\n", 1e13);

  testing_f = 18446744073709551616.0f;
  control_f = testing_f;
  result_fd = from_f_to_d(testing_f, &a);
  print(a);
  a.bits[3] = 0;
  a.bits[2] = 1;
  a.bits[1] = 0;
  a.bits[0] = 0xffff;
  print(a);
  testing_f = 0;
  result_df = from_d_to_f(a, &testing_f);
  printf(
      "result = %d, testing_f before\t%f\nresult = %d, testing_f after\t%f\n",
      result_fd, control_f, result_df, testing_f);

  if (fabs(testing_f - control_f) < 1e13) {
    printf("OK\n");
  } else {
    printf("FAIL\n");
  }
  printf("1e13 is \t\t\t\t%f\n\n", 1e13);

  // cf = 0;
  // a.bits[3] = 0;
  // a.bits[2] = 1;
  // a.bits[1] = 0;
  // a.bits[0] = 0xffff;
  // print(a);
  // from_d_to_f(a, &cf);
  // printf("cf after = %E result =%d\n\n", cf, result);

  // cf = 0;
  // a.bits[3] = 0;
  // a.bits[2] = 0;
  // a.bits[1] = 0;
  // a.bits[0] = 0x01000000;
  // print(a);
  // from_d_to_f(a, &cf);
  // printf("cf after = %E result =%d\n\n", cf, result);

  // cf = 0;
  // a.bits[3] = 0;
  // a.bits[2] = 0;
  // a.bits[1] = 0;
  // a.bits[0] = 0x01000000;
  // print(a);
  // from_d_to_f(a, &cf);
  // printf("cf after = %E result =%d\n\n", cf, result);

  // s21_decimal dec = {0};
  // dec.bits[0] = 1234;
  // dec.bits[1] = 9876;
  // dec.bits[2] = 86688;
  // print(dec);
  // from_d_to_f(dec, &cf);
  // printf("cf after = %E result =%d\n\n", cf, result);
  // // print_dec(dec);
  return 0;
}
