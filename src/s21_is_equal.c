// #include "s21_decimal.h"

// int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
//   int flag = S21_TRUE;
//   if (s21_is_zero(&value_1) && s21_is_zero(&value_2)) {
//     flag = S21_TRUE;
//   } else if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) {
//     flag = S21_FALSE;
//   } else if (!s21_normalize(&value_1, &value_2)) {
//     flag = S21_FALSE;
//   } 
//   else {
//     s21_normalize(&value_1, &value_2);
//     for (int i = 2; i>=0; i--) {
//       if (value_1.bits[i] != value_2.bits[i]) {
//         flag += 2;
//       }
//     }
//   }
//   if (flag >=2) {
//     return S21_FALSE;
//   }
//   return flag;
// }


#include "s21_decimal.h"

int s21_is_equal(s21_decimal value1, s21_decimal value2) {
  int sign1 = s21_get_sign(&value1);
  int sign2 = s21_get_sign(&value2);

  if (sign1 != sign2) {
    return S21_FALSE;
  }

  s21_normalize(&value1, &value2);

  for (int i = 2; i >= 0; i--) {
    if (value1.bits[i] != value2.bits[i]) {
      return S21_FALSE;
    }
  }

  return S21_TRUE;
}

