
/*
bignum에 우리가 원하는 크기 정해주면(ex unsigned char, unsigned int, unsigned longlong)
64_size라는 자료형이 생성되고
그걸 기반으로 사용할 연산들을 정의해주는 library구현입니다!!
*/


#include "bignum.h"


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


//freesize선언
typedef struct {
    int sign;           //NEGATIVE or NON - NEGATIVE
    int wordlen;            // wordlen >= 0
    word* a;          // address for big integer
}bignum;


/*
Zerorize 함수안에 arr init 구현하는건가요..???
대충 느낌으로만 이렇게 구현함 ㅋㅋㅋ
0 초기화 하는거 같아서,,,

void array_init(word*a, int wordlen)
{
    for(int i=0;i<worlen;i++)
    {
        a[i] =  0x0;
    }

}
*/    


//제거자
void bignum_delete(bignum* x)
{
    if (*x == NULL )
        retrun ;
#ifdef ZERORIZE                                 //얘 뭐임? ㅋㅋㅋㅋㅋㅋ
    array_init((*x)->a,(*x)->wordlen);          
#endif

    free ((*x ) ->a );
    free (*x ) ;
    *x = NULL ;
}

void bignum_new ( bignum ** x , int wordlen )
{
    if (*x != NULL )
    bignum_delete(x);

    *x = ( bignum *) malloc ( sizeof ( bignum )) ;
    (*x) -> sign = NON_NEGATIVE ; // 0
    (*x) -> wordlen = wordlen ;
    (*x) ->a = (word*) calloc ( wordlen , sizeof ( word ));
}

void bignum_refine ( bignum * x)
{
    if (x == NULL )
    return ;

    int new_wordlen = x -> wordlen;
    while ( new_wordlen > 1) // at least one word needed
    {
        if (x -> a[ new_wordlen - 1] != 0)
            break ;
        new_wordlen--;
    }
    if (x -> wordlen != new_wordlen )
    {
        x -> wordlen = new_wordlen ;
        x ->a = ( word*) realloc (x - >a , sizeof( word )* new_wordlen );
    }

    if ((x - > wordlen == 1) && (x -> a [0] == 0x0 ))
        x -> sign = NON_NEGATIVE ;
}

void bignum_assign ( bignum ** y , bignum *x)
{
    if (*y != NULL )
    bignum_delete (y);
    bignum_new (y , x -> wordlen ); 
    (*y) -> sign = x -> sign ;
    array_copy ((*y ) ->a , x ->a , x -> wordlen );
}

/*

여기가 set함수 들어갈 자리
void bi_set_by_array(bigint** x, int sign, word* a, int wordlen); // bigint x <- sign and array a
void bi_set_by_string(bigint** x, int sign, char* str, int base); // bigint x <- base string
void bi_show_hex(bigint* x); // show x in hexa. representation.
void bi_show_dec(bigint* x); // show x in deci. representation.
void bi_show_bin(bigint* x); // show x in binary representation



*/  
void bignum_set_by_array(bignum** x, int sign, word* a, int wordlen) // bigint x <- sign and array a
{
    if (*x != NULL )
    bignum_delete (x);
    bignum_new (x , wordlen );
    (*x) -> sign = sign;
    array_copy ((*x ) ->a , a , wordlen );

}

//맞게 구현한건가...?/???
void bignum_set_by_string(bignum** x, int sign, char* str, int base)// bigint x <- base string        //////////////////base가 무슨 의미일까,,, 스트링 길이???
{
if (*x != NULL )
    bignum_delete (x);
    bignum_new (x , base );
    (*x) -> sign = sign;
    memcpy((*x ) ->a , str , base );
}

void bignum_show_hex(bignum* x)
{
    int len = (*x)->wordlen;
    for(int i=0;i<len;i++)
    {
        printf("%x",(*x)->a[i]);
    }
    
}

void bignum_show_dec(bignum* x)
{
    // show얘네는 char int longlong나눠서 생각해야 하는거 아닌가요...?????
    
}

void bignum_show_dec(bignum* x)
{
   
    
}


void bignum_gen_rand ( bignum **x , int sign , int wordlen )
{
    bignum_new (x , wordlen );
    (*x) -> sign = sign ;
    array_rand ((*x) ->a , wordlen );
    bignum_refine (*x);
}

void array_rand ( word* dst , int wordlen )
{
    byte*p = ( byte*) dst ;
    int cnt = wordlen * sizeof ( word );
    while ( cnt > 0)
    {
        *p = rand () & 0 xff ;
        p ++;
        cnt--;
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
    (*x) -> sign = NON_NEGATIVE ;
    (*x) ->a[0] = 0 x1 ;
}

void bignum_set_zero ( bignum ** x )
{
    bi_new (x , 1) ;
    (*x) -> sign = NON_NEGATIVE ;
    (*x) ->a[0] = 0 x0 ;
}




int main()
{
    bignum a,b;
}