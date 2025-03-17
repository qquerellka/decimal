#include "check_s21_decimal.h"

int main(void) {
    int number_failed = 0;
    SRunner *srunner = NULL;
  
    srunner = srunner_create(s21_get_scale_suite());
    //srunner_add_suite(srunner, s21_memcmp_suite());
    
    srunner_run_all(srunner, CK_NORMAL);
    number_failed = srunner_ntests_failed(srunner);
    srunner_free(srunner);
  
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
  }
  