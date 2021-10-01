#include "freeCize.h" 

void bigint_create(bigint** x, int wordlen)
{
    if (*x != NULL)
        bigint_delete(x);

    *x = (bigint*)malloc(sizeof(bigint));
    
    if (*x != NULL) {
        (*x)->sign = 0;
        (*x)->wordlen = wordlen;
        (*x)->a = (word*)calloc(wordlen, sizeof(word));  // 메모리를 0으로 초기화 
        // printf("Success..");
    } else{
        // printf("Fail..");
    }
}

void bigint_delete(bigint** x)
{
    if (*x == NULL)
        return;
    
    free((*x)->a);
    free(*x);
    *x = NULL;
}

void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen)
{
    // 생성부터 하고 가야할까?
    bigint_create(x, wordlen);
    (*x)->sign = sign;
    (*x)->a = t;
    // 뭐하는 함수 였더라...?
    // 기억이 안 나네;;
}

void bigint_set_by_string(bigint** x, int sign, char* str, int base)
{
    // 뭐하는 함수 였더라...?
    // 기억이 안 나네;;
}

void show_bigint_hex(bigint *x)
{

    // Case 1: word is unsigned int
    for (int i = (x->wordlen) - 1; i >= 0; i--){
        printf("%08x", x->a[i]);
    }
    
    // Case 2: word is unsigned char
    // code...

    // Case 3 : word is unsigned long long 
    // code...

}