#ifndef CALC_DATA_H
#define CALC_DATA_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NON_NEGATIVE 0
#define NEGATIVE 1

int Dtype = 0; 



/*
    자료형의 크기를 선택할 수 있습니다.

    이걸 Dtype 값을 0 1 -1 이런식으로 하고 싶은데 아이디어가 필요해요 위에처럼 global 변수로 선언하는게 맞을까요..?
*/
if(Dtype = 0)
    typedef unsigned char word;
else if(Dtype = 1)
    typedef unsigned int word;
else
    typedef unsigned long long word;




typedef struct {
    int sign;           //NEGATIVE or NON - NEGATIVE
    int wordlen;            // wordlen >= 0
    word* a;          // address for big integer
}bignum;


void array_init(word*a, int wordlen);

void bignum_delete(bignum* x);
void bignum_new ( bignum ** x , int wordlen );
void bignum_refine ( bignum * x);
void bignum_assign ( bignum ** y , bignum *x);
void bignum_set_by_array(bignum** x, int sign, word* a, int wordlen);
void bignum_set_by_string(bignum** x, int sign, char* str, int base);
void bignum_show_hex(bignum* x);

void bignum_gen_rand ( bignum **x , int sign , int wordlen );
void array_rand(word* dst , int wordlen );
void bignum_set_one ( bignum ** x);
void bignum_set_zero ( bignum ** x );




#endif