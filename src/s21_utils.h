#ifndef S21_UTILS_H_INCLUDED
#define S21_UTILS_H_INCLUDED

#include <stdint.h>

#define FLOAT_POSITIVE_NAN_MASK 0x7f800000
#define FLOAT_NEGATIVE_NAN_MASK 0xff800000

#define FLOAT_POSITIVE_ZERO_MASK 0x00000000
#define FLOAT_NEGATIVE_ZERO_MASK 0x80000000  // need check this crap

#define FLOAT_SIGN_BIT 31
#define FLOAT_GET_SIGN_MASK 0xff
//#define FLOAT_SCALE_EXIST_MASK 0x80000000  // why?
#define FLOAT_MANTISA_MASK 0xffffffff
#define FLOAT_MANTISA_BITS 22
#define FLOAT_MANTISA_SHIFT 9
#define FLOAT_SCALE_STEP 127
#define FLOAT_MAX_SCALE 255
#define FLOAT_MIN_SCALE 0

typedef union float_uint32_t {
  float float_value;
  uint32_t uint_value;
} s21_FloatUint32_t;

typedef struct float_descriptor {
  uint32_t mantisa;
  unsigned char is_minus_sign;
  unsigned char scale;
} s21_FloatDescriptor_t;

void s21_set_zero(unsigned int *value);
int s21_is_float_nan(s21_FloatUint32_t float_box);
int s21_is_float_zero(s21_FloatUint32_t float_box);

s21_FloatUint32_t s21_pack_float_in_int_box(float float_value);
unsigned char s21_get_float_sign(uint32_t float_box);
unsigned char s21_get_float_scale(uint32_t float_box);
uint32_t s21_get_float_mantisa(uint32_t float_box, unsigned char scale);
s21_FloatDescriptor_t s21_get_float_data(uint32_t float_box);
void s21_set_float_sign(s21_FloatDescriptor_t *float_descriptor, uint32_t *dst);
void s21_set_float_scale(s21_FloatDescriptor_t *float_descriptor,
                         uint32_t *dst);
void s21_set_float_mantissa(s21_FloatDescriptor_t *float_descriptor,
                            uint32_t *dst);
void s21_convert_float_descriptor_to_float(
    s21_FloatDescriptor_t *float_descriptor, s21_FloatUint32_t *dst);

#endif