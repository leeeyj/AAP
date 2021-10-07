#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NON_NEGATIVE 0;
#define NEGATIVE 1;
/*
ADD, SUB, MULTIPLE,  DIVISION, modulo,,,,암호에 쓰일 함수들...EC..???? 프린트함수  뭐 이런거 짜야해요~~~
bignum에 우리가 원하는 크기 입력해주면(ex 64byte, 64_size)
64_size라는 자료형이 생성되고
그걸 기반으로 사용할 연산들을 정의해주는 library구현입니다!!
*/

/*
    자료형의 크기를 선택할 수 있습니다.
*/
typedef unsigned char word;
/*
typedef unsigned int u_int32;
typedef unsigned long long u_int32;
*/
//freesize선언
typedef struct {
    int sign;           //NEGATIVE or NON - NEGATIVE
    int wordlen;            // wordlen >= 0
    word* a;          // address for big integer
}bignum;


/*

Zerorize 함수안에 arr init 구현하는건가요..???
*/    
//제거자
void bignum_delete(bignum* x)
{
    if (* x == NULL )
        retrun ;
#ifdef ZERORIZE                                 //얘 뭐임? ㅋㅋㅋㅋㅋㅋ
    array_init((*x)->a,(*x)->wordlen);          
#endif

    free ((* x ) ->a );
    free (* x ) ;
    *x = NULL ;
}

void bignum_new ( bignum ** x , int wordlen )
{
    if (* x != NULL )
    bignum_delete(x);

    *x = ( bigint *) malloc ( sizeof ( bigint )) ;
    (*x) -> sign = NON_NEGATIVE ; // 0
    (*x) -> wordlen = wordlen ;
    (*x) ->a = ( word *) calloc ( wordlen , sizeof ( word ));
}

void bignum_refine ( bignum * x)
{
    if (x == NULL )
    return ;

    int new_wordlen = x -> wordlen ;
    while ( new_wordlen > 1) // at least one word needed
    {
        if (x -> a[ new_wordlen - 1] != 0)
            break ;
        new_wordlen - -;
    }
    if (x -> wordlen != new_wordlen )
    {
        x -> wordlen = new_wordlen ;
        x ->a = ( word *) realloc (x - >a , sizeof ( word )* new_wordlen );
    }

    if ((x - > wordlen == 1) && (x -> a [0] == 0 x0 ))
        x -> sign = NON_NEGATIVE ;
}

void bignum_assign ( bignum ** y , bignum * x)
{
    if (* y != NULL )
    bignum_delete (y);
    bignum_new (y , x -> wordlen ); 
    (* y) -> sign = x -> sign ;
    array_copy ((* y ) ->a , x ->a , x -> wordlen );
}

/*

여기가 set함수 들어갈 자리
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen); // bigint x <- sign and array a
void bi_set_by_string(bigint** x, int sign, char* str, int base); // bigint x <- base string
void bi_show_hex(bigint* x); // show x in hexa. representation.
void bi_show_dec(bigint* x); // show x in deci. representation.
void bi_show_bin(bigint* x); // show x in binary representation



//u_int 형태의 data 넣기
void bignum_setword(bignum *dest, word src)
{
    dest->dats[0]=src;
    memset(&dest->dats[1], 0, (dest->len-1)*sizeof(word));
}

//bignum 형태의 데이터 넣기
void bignum_set(bignum *dest, const bignum *src)
{
    memcpy(dest->dats,src->dats,
        ((dest->len<src->len)?dest->len:src->len)*sizeof(word));
}

*/  


void bignum_gen_rand ( bignum **x , int sign , int wordlen )
{
    bignum_new (x , wordlen );
    (* x) -> sign = sign ;
    array_rand ((* x ) ->a , wordlen );
    bignum_refine (* x);
}

void array_rand ( word * dst , int wordlen )
{
    byte * p = ( byte *) dst ;
    int cnt = wordlen * sizeof ( word );
    while ( cnt > 0)
    {
        *p = rand () & 0 xff ;
        p ++;
        cnt - -;
    }
}

/*
Get Sign and Flip Sign of BitInt
Get Word Length/Bit Length/j-th Bit of BigInt
 Is Zero?, Is One?
*/
void bignum_set_one ( bignum ** x)
 {
    bi_new (x , 1) ;
    (* x) -> sign = NON_NEGATIVE ;
    (* x) ->a [0] = 0 x1 ;
}

 void bignum_set_zero ( bignum ** x )
{
    bi_new (x , 1) ;
    (* x) -> sign = NON_NEGATIVE ;
    (* x) ->a [0] = 0 x0 ;
}




int main()
{
    bignum a,b;
    bignum_create(2, &a);
    bignum_create(2, &b);
    bignum_setuint(&a, 1234567890);
    bignum_setuint(&b, 3692581470);
    bignum_add(&a, &b);
    
}