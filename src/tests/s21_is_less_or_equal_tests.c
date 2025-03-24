#include <check.h>
#include "../s21_decimal.h"

START_TEST(is_less_or_equal) {
  int value1 = 111111;
  int value2 = 222222;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_not) {
  int value1 = 222222;
  int value2 = 111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_equal) {
  int value1 = 111111;
  int value2 = 111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_one_minus_true) {
  int value1 = -111111;
  int value2 = 222222;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_one_minus_false) {
  int value1 = 111111;
  int value2 = -222222;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_one_minus) {
  int value1 = -222222;
  int value2 = 111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_one_minus_rev) {
  int value1 = 222222;
  int value2 = -111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

START_TEST(is_less_or_equal_minus_equal) {
  int value1 = -111111;
  int value2 = -111111;
  s21_decimal dec_value1; s21_from_int_to_decimal(value1, &dec_value1);
  s21_decimal dec_value2; s21_from_int_to_decimal(value2, &dec_value2);
  ck_assert_int_eq(value1 <= value2, s21_is_less_or_equal(dec_value1, dec_value2));
}
END_TEST

int main() {
  Suite *s = suite_create("Suite");
  TCase *tc = tcase_create("Test case");
  SRunner *sr = srunner_create(s);
  int output;
  suite_add_tcase(s, tc);

  tcase_add_test(tc, is_less_or_equal);
  tcase_add_test(tc, is_less_or_equal_not);
  tcase_add_test(tc, is_less_or_equal_equal);
  tcase_add_test(tc, is_less_or_equal_one_minus_true);
  tcase_add_test(tc, is_less_or_equal_one_minus_false);  
  tcase_add_test(tc, is_less_or_equal_one_minus);
  tcase_add_test(tc, is_less_or_equal_one_minus_rev);
  tcase_add_test(tc, is_less_or_equal_minus_equal);

  srunner_run_all(sr, CK_VERBOSE);
  output = srunner_ntests_failed(sr);
  srunner_free(sr);

  return output;
}
