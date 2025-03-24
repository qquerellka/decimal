#include "s21_decimal.h"

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {

//     if (!result) return S21_ERROR_CONVERT;

//     *result = (s21_decimal){0};

//     if (s21_is_zero(&value_2)) {
//         return S21_DEV_BY_ZERO;
//     }

//     int sign_1 = s21_get_sign(&value_1);
//     int sign_2 = s21_get_sign(&value_2);
//     int result_sign = sign_1 ^ sign_2;

//     int scale_1 = s21_get_scale(&value_1);
//     int scale_2 = s21_get_scale(&value_2);
//     int result_scale = scale_1 - scale_2;

//     if (result_scale < 0) result_scale = 0;
//     if (result_scale > 28) return S21_NUMBER_INF;

//     if (s21_normalize(&value_1, &value_2) != 0) {
//         return S21_NUMBER_INF;
//     }

//     uint32_t num1[3] = {value_1.bits[0], value_1.bits[1], value_1.bits[2]};
//     uint32_t num2[3] = {value_2.bits[0], value_2.bits[1], value_2.bits[2]};
//     uint32_t quotient[3] = {0, 0, 0};
//     uint32_t remainder[3] = {0, 0, 0};

//     for (int i = 95; i >= 0; i--) {

//         remainder[0] = (remainder[0] << 1) | ((num1[2] >> i) & 1);
//         remainder[1] = (remainder[1] << 1) | ((remainder[0] >> 31) & 1);
//         remainder[2] = (remainder[2] << 1) | ((remainder[1] >> 31) & 1);
//         remainder[0] &= 0xFFFFFFFF;
//         remainder[1] &= 0xFFFFFFFF;
//         remainder[2] &= 0xFFFFFFFF;

//         if (remainder[2] > num2[2] ||
//             (remainder[2] == num2[2] && remainder[1] > num2[1]) ||
//             (remainder[2] == num2[2] && remainder[1] == num2[1] &&
//             remainder[0] >= num2[0])) { quotient[0] |= (1 << i);

//             if (remainder[0] < num2[0]) {
//                 remainder[1]--;
//                 remainder[0] += 0x100000000;
//             }
//             remainder[0] -= num2[0];
//             if (remainder[1] < num2[1]) {
//                 remainder[2]--;
//                 remainder[1] += 0x100000000;
//             }
//             remainder[1] -= num2[1];
//             remainder[2] -= num2[2];
//         }
//     }

//     if (remainder[3] || remainder[4] || remainder[5]) {
//         return result_sign ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;
//     }

//     if (result_scale > 0) {
//         uint32_t last_digit = (remainder[0] >> (32 - result_scale)) & 1;
//         if (last_digit == 1) {

//             if ((quotient[0] & 1) == 1) {
//                 quotient[0]++;
//             }
//         }
//     }

//     result->bits[0] = quotient[0];
//     result->bits[1] = quotient[1];
//     result->bits[2] = quotient[2];

//     s21_set_sign(result, result_sign);
//     s21_set_scale(result, result_scale);

//     return S21_OK;
// }

// int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
//   if (!result) return S21_ERROR_CONVERT;
//   if (s21_is_zero(&value_2)) return S21_DEV_BY_ZERO;

//   *result = (s21_decimal){0};

//   int sign_1 = s21_get_sign(&value_1);
//   int sign_2 = s21_get_sign(&value_2);
//   int result_sign = sign_1 ^ sign_2;

//   int scale_1 = s21_get_scale(&value_1);
//   int scale_2 = s21_get_scale(&value_2);
//   int result_scale = scale_1 - scale_2;

//   if (s21_normalize(&value_1, &value_2) != 0) return S21_NUMBER_INF;

//   uint32_t num1[3] = {value_1.bits[0], value_1.bits[1], value_1.bits[2]};
//   uint32_t num2[3] = {value_2.bits[0], value_2.bits[1], value_2.bits[2]};
//   uint32_t quotient[3] = {0, 0, 0};
//   uint32_t remainder[3] = {0, 0, 0};

//   for (int i = 95; i >= 0; i--) {
//     s21_shift_left_96(remainder, 1);
//     remainder[0] |= (num1[2] >> i) & 1;

//     if (s21_is_greater_or_equal_96(remainder, num2)) {
//       s21_sub_96(remainder, num2);
//       s21_set_bit_96(quotient, i);
//     }
//   }

//   if (!s21_is_zero_96(remainder)) {
//     result_scale++;

//     if (result_scale > 28)
//       return result_sign ? S21_NUMBER_MIN_INF : S21_NUMBER_INF;

//     if (s21_is_greater_or_equal_96(remainder, num2)) {
//       s21_add_96(quotient, 1);
//     }
//   }

//   result->bits[0] = quotient[0];
//   result->bits[1] = quotient[1];
//   result->bits[2] = quotient[2];

//   s21_set_sign(result, result_sign);
//   s21_set_scale(result, result_scale);

//   return S21_OK;
// }
