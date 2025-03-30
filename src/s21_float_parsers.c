#include "s21_decimal.h"

#include "s21_utils.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result_to_decimal = 0;
  int is_nan = 0;
  int is_zero = 0;
  int is_float_overflow_decimal = 0;
  int is_float_is_too_small = 0;
  s21_FloatUint32_t float_box = {0};
  s21_FloatDescriptor_t float_descriptor = {0};

  if(dst){
    s21_initialize_decimal_as_zero(dst);
    float_box = s21_pack_float_in_int_box(src);
    is_nan = s21_is_float_nan(float_box);

    if (is_nan) {
      result_to_decimal = 1;
    } else {
      is_zero = s21_is_float_zero(float_box);
      is_float_overflow_decimal = s21_is_float_overflow((double)src);
      is_float_is_too_small = s21_is_float_too_small((double)src);
      if(!is_zero){
        if (!is_float_overflow_decimal && !is_float_is_too_small) {
          float_descriptor = s21_get_float_data(float_box);

          s21_set_sign(dst, (int)float_descriptor.is_minus_sign);

          s21_set_scale(dst, (int)float_descriptor.scale);

          s21_set_float_mantisa_in_decimal(dst, float_descriptor.mantisa);
        } else if (is_float_overflow_decimal) {
          result_to_decimal = 1;
        }else if (is_float_is_too_small) {
          result_to_decimal = 1;
        }
      }
    }
  }else{
    result_to_decimal = 1;
  }

  return result_to_decimal;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_to_float = 0;
  int is_decimal_not_zero = 0;
  s21_FloatDescriptor_t float_descriptor = {0};
  double float_buffer = 0;
  

  if(dst) {
    *dst = 0;
    is_decimal_not_zero = s21_is_decimal_not_zero(&src);

    if (is_decimal_not_zero) {
      float_buffer = s21_convert_decimal_mantisa_to_double(src);

      float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);

      float_descriptor.scale = (unsigned char)s21_get_scale(&src);

      *dst = s21_convert_float_descriptor_to_float(&float_descriptor,
                                                   float_buffer);
    }

  } else {
    result_to_float = 1;
  }

  return result_to_float;
}