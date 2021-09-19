#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*
ADD, SUB, MULTIPLE,  DIVISION, modulo,,,,암호에 쓰일 함수들...EC..???? 프린트함수  뭐 이런거 짜야해요~~~
bignum에 우리가 원하는 크기 입력해주면(ex 64byte, 64_size)
64_size라는 자료형이 생성되고
그걸 기반으로 사용할 연산들을 정의해주는 library구현입니다!!

*/
typedef unsigned int u_int32;

//freesize선언
typedef struct freesize{
    u_int32 len;
    u_int32* dats;
}bignum;

//생성자
u_int32 bignum_create(u_int32 len, bignum *xi)
{
    xi->len=len;
    // bignum 길이 
    // u_int32 = 4-byte 
    // 4byte 단위로 길이 

    xi->dats=(u_int32*)malloc(len*sizeof(u_int32));
    // 동적 메모리 할당
    // len 만큼

    if(xi->dats==NULL)
        return 0;
    
    return -1;
}

//u_int 형태의 data 넣기
void bignum_setuint(bignum *dest, u_int32 src)
{
    dest->dats[0]=src;
    memset(&dest->dats[1], 0, (dest->len-1)*sizeof(u_int32));
}

//bignum 형태의 데이터 넣기
void bigint_set(bignum *dest, const bignum *src)
{
    memcpy(dest->dats,src->dats,
        ((dest->len<src->len)?dest->len:src->len)*sizeof(u_int32));
}

//print 함수 필요

//사이즈 변환..필요할까..?
#if 0
u_int bignum_resize(u_int newsize, bignum* xi)
{
    xi->len = newsize;
    xi->dats = (u_int*)realloc(xi->dats, newsize * sizeof(u_int));
    if (xi->dats == NULL)return 0;
    return newsize;
}
#endif

//제거자
void bignum_release(bignum* xi)
{
    xi->len = 0;
    free(xi->dats);
}


//덧셈을 위한 준비01

inline u_int32 add_a(u_int32 len,u_int32* dest,u_int32* src)
{
    u_int32 carry=0;
    for(u_int32 i=0;i<len;++i)
    {
        dest[i]+=src[i];
        if(carry)
        {
            if(dest[i]>=src[i])
                carry=0;
            if(dest[i]==0xFFFFFFFF)
                carry=1;
            ++dest[i];
        }
        else
        {
            if(dest[i]<src[i])
                carry=1;
        }
    }
    return carry;
}

//덧셈을 위한 준비02

inline u_int32 add_u4(u_int32 len,u_int32* dest,u_int32 src)
{
    u_int32 carry=0;
    dest[0]+=src;
    if(dest[0]<src)carry=1;
    for(u_int32 i=1;i<len;++i)
    {
        if(carry)
        {
            if(dest[i]!=0xFFFFFFFF)carry=0;
            ++dest[i];
        }
        else
        {
            break;
        }
    }
    return carry;
}

//bignum 덧셈
void bignum_add(bignum *dest, const bignum *src)
{
    if(dest->len<src->len)
    {
        add_a(dest->len, dest->dats, src->dats);
    }
    else
    {
        if(add_a(src->len, dest->dats, src->dats))
        {
            add_u4(dest->len-src->len, &dest->dats[src->len], 1);
        }
    }
}

//u_int 덧셈

void bignum_adduint(bignum *dest, u_int32 src,u_int32 pos)
{
    if(dest->len<=pos)return;
    add_u4(dest->len-pos,&dest->dats[pos],src);
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