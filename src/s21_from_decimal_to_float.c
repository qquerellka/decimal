#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int result_to_float = 0;
  int is_decimal_not_zero = 0;
  int is_scale_correct=0;
  int is_decimal_error=0;
  s21_FloatDescriptor_t float_descriptor = {0};
  double float_buffer = 0;

  s21_FloatUint32_t float_box = {0};

  if (dst) {
    *dst = 0;

    is_decimal_not_zero = s21_is_decimal_not_zero(&src);

    if (is_decimal_not_zero) {
      float_descriptor.scale = s21_get_scale(&src);
      is_scale_correct=((float_descriptor.scale > -29) && (float_descriptor.scale < 29));
      if(is_scale_correct){
        float_descriptor.is_minus_sign = (unsigned char)s21_get_sign(&src);
        //конвертируем собсно мантису децимала
        float_buffer = s21_convert_decimal_mantisa_to_double(src);
        //упаковываем дабл в перечисление,чтобы не мучиться с приведением типов
        float_box.float_value=(float)float_buffer;
        //проверяем на допустимость значения самой мантисы
        is_decimal_error += s21_is_float_nan(float_box);
        //заполняем знаки и приводим к нужной степени
        float_buffer=s21_convert_float_descriptor_to_float(&float_descriptor,
          float_buffer);
        //проверяем на переполнение итога
        is_decimal_error += s21_is_float_overflow(float_buffer);
        //проверяем на маленькость
        is_decimal_error += s21_is_float_too_small(float_buffer);
        //если хоть один критерий не срабатывает, возвращаем нуль и код ошибки
        if(is_decimal_error){
          result_to_float=1;
        }else{
          *dst = float_buffer;
        }
      }else{
        result_to_float = 1;                           
      }
    }

  } else {
    result_to_float = 1;
  }

  return result_to_float;
}