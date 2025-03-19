#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
    int flag = S21_TRUE;
    if (s21_is_zero(&value_1) && s21_is_zero(&value_2)){
        flag =  S21_TRUE;
    }else if (s21_get_sign(&value_1) != s21_get_sign(&value_2)){
        flag = S21_FALSE;
    }else if(!s21_normalize(&value_1, &value_2)) {
        flag =  S21_FALSE;
    }else{
        s21_normalize(&value_1, &value_2);
        for (int i = 0; i < 3; i++) {
            if (value_1.bits[i] != value_2.bits[i]){
                flag =  S21_FALSE;
            }
        }
    }
    return flag;
}
