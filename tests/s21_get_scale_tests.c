#include "check_s21_decimal.h"

START_TEST(test_s21_get_scale_1) {
  s21_decimal test_decimal={0};
  int exp=36;
  int value=0;
  int result = 0;
  value=((unsigned char)exp)<<16;
  test_decimal.bits[3]|=value;

  result = s21_get_scale(&test_decimal);

  ck_assert_int_eq(result, exp);
}
END_TEST


Suite *s21_get_scale_suite(void) {
  Suite *suite;
  TCase *tc_s21_get_scale;

  suite = suite_create("s21_get_scale");

  tc_s21_get_scale = tcase_create("S21_get_scale");

  tcase_add_test(tc_s21_get_scale, test_s21_get_scale_1);
  suite_add_tcase(suite, tc_s21_get_scale);

  return suite;
}
