#include "s21_float_parsers.h"

#include <stdio.h>

#include "s21_utils.h"

static void s21_initialize_decimal_as_zero(s21_decimal *decimal) {
  for (int i = 0; i < 4; i++) {
    decimal->bits[i] = 0;
  }
}

static void print_binary(int val) {
  for (int i = 31; i >= 0; i--) {
    if ((i + 1) % 4 == 0) {
      printf(" ");
    }
    printf(" %d", (val >> i) & 1);
  }
  printf("\n");
}

void print_dec(s21_decimal dec) {
  for (int i = 2; i >= 0; i--) {
    printf("bits [%d]", i);
    print_binary(dec.bits[i]);
    printf("\n");
  }

  char *bufffffchar = dec.bits;

  for (int i = 0; i < 96; i++) {
  }
}
// static int s21_is_decimal_overflow_float(s21_decimal *decimal) {
//   int result = 0;

//   // if (decimal->bits[0] > FLOAT_MANTISA_MAXIMUM_MASK) {
//   //   result++;
//   // } else {
//   for (int i = 1; i < 3; i++) {
//     if (decimal->bits[i]) {
//       result++;
//     }
//   }
//   //}

//   return result;
// }

static void s21_set_float_mantisa_in_decimal(s21_decimal *dst,
                                             uint32_t uint_value) {
  dst->bits[0] = uint_value;
}

static int s21_is_decimal_not_zero(s21_decimal *decimal) {
  int result = 0;

  for (int i = 0; i < 3; i++) {
    if (decimal->bits[i]) {
      result++;
    }
  }

  return result;
}

int from_f_to_d(float src, s21_decimal *dst) {
  int result_to_decimal = 0;
  int is_nan = 0;
  int is_zero = 0;
  int is_float_overflow_decimal = 0;
  int is_float_is_too_small = 0;
  s21_FloatUint32_t float_box = {0};
  s21_FloatDescriptor_t float_descriptor = {0};

  s21_initialize_decimal_as_zero(dst);

  float_box = s21_pack_float_in_int_box(src);

  is_nan = s21_is_float_nan(float_box);

  if (is_nan) {
    result_to_decimal = 1;
  } else {
    is_zero = s21_is_float_zero(float_box);
    is_float_overflow_decimal = s21_is_float_overflow((double)src);
    is_float_is_too_small = s21_is_float_too_small((double)src);

    if (!is_zero && !is_float_overflow_decimal && !is_float_is_too_small) {
      float_descriptor = s21_get_float_data(float_box);

      s21_set_sign(dst, (int)float_descriptor.is_minus_sign);

      s21_set_scale(dst, (int)float_descriptor.scale);

      s21_set_float_mantisa_in_decimal(dst, float_descriptor.mantisa);
    } else if (is_float_overflow_decimal) {
      result_to_decimal = 1;
    } else if (is_float_is_too_small) {
      result_to_decimal = 1;
    }
  }

  return result_to_decimal;
}

int from_d_to_f(s21_decimal src, float *dst) {
  int result_to_float = 0;
  int is_decimal_not_zero = 0;
  // int is_decimal_overflow_float_mantisa = 0;  //
  s21_FloatDescriptor_t float_descriptor = {0};
  s21_FloatUint32_t float_box = {0};
  //*dst = 0;

  if (dst) {
    is_decimal_not_zero = s21_is_decimal_not_zero(&src);
    // // is_decimal_overflow_float_mantisa =
    // s21_is_decimal_overflow_float(&src);

    // //
    // printf("is_decimal_not_zero %d\n",
    //        is_decimal_not_zero);  //, is_decimal_overflow_float_mantisa);
    // //
    if (is_decimal_not_zero) {
      //   //
      //   double buffer = 0;
      //   char char_buffer[97] = {0};

      //   for(int=0;i<3;i++){
      //     for(int j=0;j<4;j++)
      //     char_buffer[i+j]=src.bits[i];
      //   }

      //   printf("buffer is %lf\nchar buffer is %s\n", buffer, char_buffer);
      //   //
      // if (!is_decimal_overflow_float_mantisa) {
      float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);

      float_descriptor.scale = (unsigned char)s21_get_scale(&src);

      float_descriptor.mantisa = src.bits[0];

      s21_convert_float_descriptor_to_float(&float_descriptor, &float_box);

      *dst = float_box.float_value;
    }
    // } else {
    //   result_to_float = 1;
    // }

  } else {
    result_to_float = 1;
  }

  return result_to_float;
}