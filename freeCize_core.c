#include "freeCize_core.h" 

// Creat and Delete Bigint //
void bigint_create(bigint** x, int wordlen)
{
    if (*x != NULL)
        bigint_delete(x);

    *x = (bigint*)malloc(sizeof(bigint));
    
    if (*x != NULL) {
        (*x)->sign = NON_NEGATVE;
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
    bigint_create(x, wordlen);
    (*x)->sign = sign;
    array_copy((*x)->a, t, wordlen);
}

void bigint_set_by_string(bigint** x, int sign, char* str, int base)    // Setting bigint by string
{
    // string how...?
}

// Show(print) Bigint //
void show_bigint_hex(bigint *x)
{   
    #if WordBitLen == 32
    // Case 1: word is unsigned int
    for (int i = (x->wordlen) - 1; i >= 0; i--){
        printf("%08x", x->a[i]);
    }
    printf("\n");
    
    #elif WordBitLen == 8
    // Case 2: word is unsigned char
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%02x", x->a[i])
    }
    printf("\n");

    #elif WordBitLen == 64
    // Case 3 : word is unsigned long long 
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%016x", x->a[i])
    }
    printf("\n");

    #endif
}

void show_bigint_dec(bigint* x)
{
    // How...?
}

void show_bigint_bin(bigint* x)
{
    // How...?
}

// Refine Bigint //
void bigint_refine(bigint* x)
{
    if (x == NULL)
        return;
    
    int new_wordlen = x->wordlen;
    while(new_wordlen > 1){
        if (x->a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }

    if (x->wordlen != new_wordlen){
        x->wordlen = new_wordlen;
        x->a = (word*)realloc(x->a, sizeof(word)*new_wordlen);
    }

    if((x->wordlen == 1) && (x->a[0] == 0x0))
        x->sign = NON_NEGATVE;
}

// Assign Bigint //
void bigint_assign(bigint** y, bigint* x)
{
    if(*y != NULL)
        bigint_delete(y);
    
    bigint_create(y, x->wordlen);
    (*y)->sign = x->sign;
    array_copy((*y)->a, x->a, x->wordlen);
}

// Generate Random Bigint //
void bigint_gen_rand(bigint** x, int sign, int wordlen)
{
    bigint_create(x, wordlen);
    (*x)->sign = sign;
    array_rand((*x)->a, wordlen);

    bigint_refine(*x);
}

void array_rand(word* dst, int wordlen)
{
    byte* p = (byte*)dst;
    int cnt = wordlen * sizeof(word);
    srand(time(NULL));                      // Seed = Current time
    // srand(0);
    while(cnt > 0)
    {
        *p = rand() & 0xff;                 // rand() is not safe, use "srand(time(NULL))",  
        p++;
        cnt--;
    }
}

/**/
// Only for Testing
void bigint_gen_rand1(bigint** x, int sign, int wordlen)
{
    bigint_create(x, wordlen);
    (*x)->sign = sign;
    array_rand1((*x)->a, wordlen);

    bigint_refine(*x);
}

void array_rand1(word* dst, int wordlen)
{
    byte* p = (byte*)dst;
    int cnt = wordlen * sizeof(word);
    srand(time(NULL)+1);                      // Seed = Current time
    // srand(0);
    while(cnt > 0)
    {
        *p = rand() & 0xff;                 // rand() is not safe, use "srand(time(NULL))",  
        p++;
        cnt--;
    }
}
/**/

// Set one, Set Zero //
void bigint_set_one(bigint** x)
{
    bigint_create(x, 1);
    (*x)->sign = NON_NEGATVE;
    (*x)->a[0] = 0x01;
}

void bigint_set_zero(bigint** x)
{
    bigint_create(x, 1);
    (*x)->sign = NON_NEGATVE;
    (*x)->a[0] = 0x00;    
}

// IsZero? IsOne? 이거 뭐하는 함수죠...? //
bool IsZero(bigint* x)
{
    if (x->sign == 1 || x->a[0] != 0)
        return false;
    
    for (int i = (x->wordlen) - 1; i >= 1; i--){
        if (x->a[i] != 0)
            return false;
    }

    return true;
}

bool IsOne(bigint* x)
{
    if (x->sign == 1 || x->a[0] != 1)
        return false;
    
    for (int i = (x->wordlen) - 1; i >= 1; i--){
        if (x->a[i] != 0)
            return false;
    }

    return true;
}

// Compare Two Bigint
int CompareABS(bigint* x, bigint* y)
{
    int n = x->wordlen;
    int m = y->wordlen;

    // Case: A > B
    if (n > m)
        return 1;

    // Case: A < B
    if (n < m)
        return -1;
    
    for(int i = n - 1; i >= 0; i--){
        
        if (x->a[i] > y->a[i])
            return 1;
        
        if (x->a[i] < y->a[i])
            return -1;

    }

    return 0;
}

int Compare(bigint* x, bigint* y)
{
    if (x->sign == NON_NEGATVE && y->sign == NEGATIVE)
        return 1;

    if (x->sign == NEGATIVE && y->sign == NON_NEGATVE)
        return -1;
    
    int ret = CompareABS(x, y);

    if (x->sign == NON_NEGATVE)
        return ret;
    
    return ret * (-1);
    
}


