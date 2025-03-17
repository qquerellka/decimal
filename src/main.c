#include "s21_decimal.h"

int main() {
  s21_decimal a, b;
  s21_from_int_to_decimal(-214748364, &a);
  s21_from_int_to_decimal(20000000, &b);
  printf("%u\n", a.bits[0]);
  printf("%u\n", b.bits[0]);

  int l, g;
  s21_from_decimal_to_int(a, &l);
  s21_from_decimal_to_int(b, &g);
  printf("%d\n", l);
  printf("%d\n", g);

  s21_decimal a1, b1;
  s21_from_float_to_decimal(5.12345e2, &a1);
  s21_from_float_to_decimal(-1234.121e2, &b1);
  printf("%u\n", a1.bits[0]);
  printf("%u\n", b1.bits[0]);

  float ar, arr;
  s21_from_decimal_to_float(a1, &ar);
  s21_from_decimal_to_float(b1, &arr);
  printf("%lf\n", ar);
  printf("%lf\n", arr);
  printf("%d ", s21_get_scale(&a1));
  printf("%d \n", s21_get_scale(&b1));

  float src = 123456789012345.00f;
  s21_decimal dec;
  s21_from_float_to_decimal(src, &dec);

  printf("bits[0] = %u\n", dec.bits[0]);
  printf("bits[1] = %u\n", dec.bits[1]);
  printf("bits[2] = %u\n", dec.bits[2]);
  s21_from_decimal_to_float(dec, &src);
  printf("%lf\n", src);

  s21_decimal z = {{10, 10100, 1011, 0}};
  s21_decimal x = {{10, 110111, 1101, 0}};
  s21_decimal result_1;
  int code_1 = s21_add(z, x, &result_1);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_1.bits[0],
         result_1.bits[1], result_1.bits[2], result_1.bits[3], code_1);

  s21_decimal ag = {{100, 0, 0, 0}};      
  s21_decimal bg = {{50, 0, 0, 1 << 31}};  
  s21_decimal result_2;
  int code_2 = s21_add(ag, bg, &result_2);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_2.bits[0],
         result_2.bits[1], result_2.bits[2], result_2.bits[3], code_2);

  s21_decimal al = {{200, 0, 0, 1 << 31}};  
  s21_decimal bl = {{300, 0, 0, 1 << 31}};
  s21_decimal result_3;
  int code_3 = s21_add(al, bl, &result_3);
  int sign_12 = s21_get_sign(&result_3);

  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_3.bits[0],
         result_3.bits[1], result_3.bits[2], sign_12, code_3);

  s21_decimal all = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal bll = {{1, 0, 0, 0}};
  s21_decimal result_4;
  int code_4 = s21_add(all, bll, &result_4);

  printf("Code: %d\n", code_4);

  s21_decimal aa = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 1 << 31}};
  s21_decimal bb = {{1, 0, 0, 1 << 31}};
  s21_decimal result_5;
  int code_5 = s21_add(aa, bb, &result_5);

  printf("Code: %d\n", code_5);

  s21_decimal ag1 = {{500, 0, 0, 0}};  
  s21_decimal bg1 = {{200, 0, 0, 0}}; 
  s21_decimal result_6;
  int code_6 = s21_sub(ag1, bg1, &result_6);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_6.bits[0],
         result_6.bits[1], result_6.bits[2], result_6.bits[3], code_6);

  s21_decimal ag2 = {{500, 0, 0, 0}};        
  s21_decimal bg2 = {{300, 0, 0, 1 << 31}}; 
  s21_decimal result_7;
  int code_7 = s21_sub(ag2, bg2, &result_7);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_7.bits[0],
         result_7.bits[1], result_7.bits[2], result_7.bits[3], code_7);

  s21_decimal ag3 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}; 
  s21_decimal bg3 = {{1, 0, 0, 0}};
  s21_decimal result_8;
  int code_8 = s21_sub(ag3, bg3, &result_8);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_8.bits[0],
         result_8.bits[1], result_8.bits[2], result_8.bits[3], code_8);

  s21_decimal ag4 = {{1, 0, 0, 1 << 31}};  
  s21_decimal bg4 = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}; 
  s21_decimal result_9;
  int code_9 = s21_sub(ag4, bg4, &result_9);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_9.bits[0],
         result_9.bits[1], result_9.bits[2], result_9.bits[3], code_9);

  s21_decimal ag5 = {{1000, 0, 0, 0}};  
  s21_decimal bg5 = {{50, 0, 0, 0}}; 
  s21_decimal result_10;
  int code_10 = s21_sub(ag5, bg5, &result_10);
  printf("Result: {%d, %d, %d, %d}, Code: %d\n", result_10.bits[0],
         result_10.bits[1], result_10.bits[2], result_10.bits[3], code_10);

  return 0;
}
