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

#if 0 
//first made
void bigint_set_by_string(bigint** x, int sign, char* str, int base)    // Setting bigint by string //base mean is a of x^a 
{
    bigint_create(x, strlen(str));
    (*x)->sign = sign;
    memset((*x)->a,strtoul(str, NULL, base),strlen(str)*sizeof(word));
}
#endif
void bigint_set_by_string(bigint** x, int sign, char* str, int base)    // Setting bigint by string //base mean is a of x^a 
{
    int size = strlen(str);
    int byte_size = WordBitLen>>3;
    size = size/byte_size;
    if(size%byte_size != 0 )
    {
        size++;
    }
    bigint_create(x, size);
    (*x)->sign = sign;
    for(int i=0;i<size*byte_size;i+=byte_size)
    {
        // memset((*x)->a,strtoul(str, NULL, base),strlen(str)*sizeof(word));
        //please your opinion. -keonhee
    }
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
    // we need to make bigint to decimal func
    // idk.... sorry
}

void show_bigint_bin(bigint* x)
{
    int len = x->wordlen;
    printf("0b");
    for(int i=(len-1);i>0;i--)
    {
        word t = x->a[i];
        for(int j=0;j<WordBitLen;j++)
        {
            if((t>>j)&(0x1) ==1)
                printf("1");
            else
                printf("0"); 
        }
    }
    printf("\n");
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
    if((*y) != NULL)              // bigint y가 비어있지 않다면..?
        bigint_delete(y);       // bigint y를 비우고 
    
    bigint_create(y, x->wordlen);       // y를 x의 word길이 만큼 새로 만들기  
    (*y)->sign = x->sign;               // y에 x의 부호 할당 (음수, 양수 판단)
    array_copy((*y)->a, x->a, x->wordlen);      // array_copy(y의 word 배열의 시작 주소, x의 word배열의 시작 주소 위치, 얼만큼 복사?)
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
    /*
    if (x->sign == 1 || x->a[0] != 0)
        return false;
    */
    if (x->a[0] != 0)
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

void LeftShift(bigint* A, int r)
{   
    // Case1 (r = WordBitLen * k)
    if (r % WordBitLen == 0){
        A->a = (word*)realloc(A->a, sizeof(word) * (r / WordBitLen + A->wordlen));

        memmove(&(A->a[r / WordBitLen]), &(A->a[0]), sizeof(word) * A->wordlen);
        A->wordlen += r / WordBitLen;
        for (int i = 0; i < r / WordBitLen; i++){
            A->a[i] = 0;
        }
        bigint_refine(A);
        return;
    } 

    // Case 2 (r = WordBitLen * k + r')
    if (r % WordBitLen != 0){
        A->a = (word*)realloc(A->a, sizeof(word) * (r / WordBitLen + A->wordlen + 1));

        word t1 = A->a[0] >> (WordBitLen - (r % WordBitLen)); 
        A->a[0] = A->a[0] << (r % WordBitLen);

        for (int i = 1; i < A->wordlen; i++){
            word t2 = A->a[i] >> (WordBitLen - (r % WordBitLen)); 
            A->a[i] = (A->a[i] << (r % WordBitLen)) | t1;
            t1 = t2;
            t2 = 0;
        }
        A->a[A->wordlen] = t1;
        t1 = 0; 
        
        memmove(&(A->a[r / WordBitLen]), &(A->a[0]), sizeof(word) * (A->wordlen + 1));

        A->wordlen += (r / WordBitLen + 1);
        for (int i = 0; i < (r / WordBitLen); i++){
            A->a[i] = 0;
        }
        bigint_refine(A);
        return;
    }
    
}

void RightShift(bigint* A, int r)
{   
    int o = WordBitLen * A->wordlen; 
    // Case1 (r >= WordBitLen * A->wordlen)
    if (r >= o){
        memset(A->a, 0, sizeof(word) * A->wordlen);
        bigint_refine(A);
        // Bigint Refine X
        return;
    }

    // Case2 (r = WordBitLen * k)
    if (r % WordBitLen == 0 && r < o){
        memmove(&(A->a[0]), &(A->a[r / WordBitLen]), sizeof(word) * (A->wordlen - r / WordBitLen));
        for (int i = A->wordlen - (r / WordBitLen); i < A->wordlen; i++){
            A->a[i] = 0;
        }
        bigint_refine(A);
        return;
    }

    // Case3 (r = WordBitLen * k + r')
    if (r % WordBitLen != 0 && r < o){
        word t1 = A->a[A->wordlen - 1] << (WordBitLen - (r % WordBitLen));
        A->a[A->wordlen - 1] = A->a[A->wordlen - 1] >> (r % WordBitLen);
        
        for (int i = A->wordlen - 2; i >= r / WordBitLen; i--){
            word t2 = A->a[i] << (WordBitLen - (r % WordBitLen));
            A->a[i] = t1 | (A->a[i] >> (r % WordBitLen));
            t1 = t2;
            t2 = 0;
        }
        t1 = 0;

        memmove(&(A->a[0]), &(A->a[r / WordBitLen]), sizeof(word) * (A->wordlen - r / WordBitLen));
        for (int i = A->wordlen - r / WordBitLen; i < A->wordlen; i++){
            A->a[i] = 0;
        }
        bigint_refine(A);
        return;
    }
}

void Reduction(bigint* A, int r)
{
    // case 1 : r >= WordBitLen * wordlen
    // no needed

    int k = r / WordBitLen;
    int len = A->wordlen;
    int r0 = r % WordBitLen;
    word q = 0;

    // case 2: r = WordBitLen * k, k < wordlen
    if ((k < len) && (r0 == 0)){
        for (int i = k; i < len; i++) {
            A->a[i] = 0;
        }
        bigint_refine(A);
        return;
    }
    
    // case 3: r = WordBitLen * k + r, same
    if ((k < len) && (0 < r0) && (r0 < WordBitLen)){
        for (int i = k+1; i < len; i++) {
            A->a[i] = 0;
        }
        q = (1 << r0) - 1;
        printf("%x", q);
        A->a[k] = A->a[k] & q;
        bigint_refine(A);
        return;
    }
    
    return;
}