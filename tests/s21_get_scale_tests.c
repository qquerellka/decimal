#include "check_s21_decimal.h"

START_TEST(test_s21_get_scale_1) {
    // char *str = "";
    // char *tk = "";
    // size_t s21_strcspn_result = 0;
    // size_t strcspn_result = 0;
  
    // s21_strcspn_result = s21_strcspn(str, tk);
    // strcspn_result = strcspn(str, tk);
  
    // ck_assert(s21_strcspn_result == strcspn_result);
  }
  END_TEST
  
  // const string or null ptr => sega
  Suite *s21_get_scale_suite(void) {
    Suite *suite;
    TCase *tc_s21_get_scale;
  
    suite = suite_create("s21_get_scale");
  
    tc_s21_get_scale = tcase_create("S21_get_scale");
  
    tcase_add_test(tc_s21_get_scale, test_s21_get_scale_1);
    suite_add_tcase(suite, tc_s21_get_scale);
  
  
    return suite;
  }
  