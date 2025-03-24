#include <check.h>

#include "../s21_decimal.h"
START_TEST(is_equal) {
  int value1 = 111111;
  int value2 = 111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1==value2, s21_is_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_equal_float) {
  double value1 = 111111.111;
  double value2 = 111111.111;
  s21_decimal dec_value1; s21_from_float_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_float_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1==value2, s21_is_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_equal_not) {
  int value1 = 111111;
  int value2 = 222222;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1==value2, s21_is_equal(dec_value1, dec_value2));
}
END_TEST

// START_TEST(is_equal_float_not) {
//   double value1 = 111111.111;
//   double value2 = 111111.1111;
//   s21_decimal dec_value1; s21_from_float_to_decimal(value1, &dec_value1);
//   s21_decimal dec_value2; s21_from_float_to_decimal(value2, &dec_value2);
//   ck_assert_int_eq(value1==value2, s21_is_equal(dec_value1, dec_value2));
// }
// END_TEST

START_TEST(is_equal_minus) {
  int value1 = 111111;
  int value2 = -111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1==value2, s21_is_equal(dec_value1, dec_value2));
}
END_TEST

int main() {
  Suite *s = suite_create("Suite");
  TCase *tc = tcase_create("Test case");
  SRunner *sr = srunner_create(s);
  int output;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, is_equal);
  tcase_add_test(tc, is_equal_float);
  tcase_add_test(tc, is_equal_not);
  // tcase_add_test(tc, is_equal_float_not);
  tcase_add_test(tc, is_equal_minus);

  srunner_run_all(sr, CK_VERBOSE);
  output = srunner_ntests_failed(sr);
  srunner_free(sr);

  return output;
}

