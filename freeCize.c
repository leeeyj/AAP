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

// Setting Big int //
void array_copy(word* dest, word* src, int wordlen)                     // Copy array
{
    memcpy(dest, src, sizeof(word) * wordlen);
}

void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen)    // Setting bigint by array
{
    // 생성부터 하고 가야할까?
    bigint_create(x, wordlen);
    (*x)->sign = sign;
    array_copy((*x)->a, t, wordlen);
}

void bigint_set_by_string(bigint** x, int sign, char* str, int base)    // Setting bigint by string
{
    // string how...?
}

// Show(print) Bigint
void show_bigint_hex(bigint *x)
{   
    #if size_of_word == 4
    // Case 1: word is unsigned int
    for (int i = (x->wordlen) - 1; i >= 0; i--){
        printf("%08x", x->a[i]);
    }
    
    #elif size_of_word == 1
    // Case 2: word is unsigned char
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%02x", x->a[i])
    }

    #elif size_of_word == 8
    // Case 3 : word is unsigned long long 
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%016x", x->a[i])
    }
    #endif
}