#include "freeCize_core.h" 

//bigint 계산 함수 생성
void bigint_create(bigint** x, int wordlen)
{
    //에러 방지
    if (*x != NULL)
        bigint_delete(x);

    //bigint의 크기만큼 메모리 공간 확보
    *x = (bigint*)malloc(sizeof(bigint));   
    
    //bigint 변수별로 초기값 설정
    //sign = 음이 아닌 정수, wordlen = 변수의 길이, a = 데이터 값들을 0으로 초기화
    if (*x != NULL) {
        (*x)->sign = NON_NEGATVE;
        (*x)->wordlen = wordlen;
        (*x)->a = (word*)calloc(wordlen, sizeof(word));
        // printf("Success..");
    } else{
        // printf("Fail..");
    }
}

//bigint 계산 삭제 함수
void bigint_delete(bigint** x)  
{
    //에러 방지
    if (*x == NULL)
        return;
    
    //bigint_create 함수에서 a에게 필요한 크기를 동적으로 할당하였기 때문에
    //free 함수를 통해 메모리 해제(삭제하는 역할)
    //x의 주소에 NULL 값 대입
    free((*x)->a);
    free(*x);
    *x = NULL;
}

// bigint 세팅
// 배열 복사
void array_copy(word* dest, word* src, int wordlen)                     
{
    // 메모리 값 복사(복사 받을 메모리, 복사할 메모리, 복사할 데이터의 길이)
    memcpy(dest, src, sizeof(word) * wordlen);  
}

// bigint를 배열로 세팅
void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen) 
{
    bigint_create(x, wordlen);
    (*x)->sign = sign;  // sign 메모리에 sign 값 저장
    array_copy((*x)->a, t, wordlen);    // array_copy 함수 실행
}

// bigint를 string으로 세팅 -> 파이썬에서 사용하기 위해서 string으로 세팅하는건가?
void bigint_set_by_string(bigint** x, int sign, char* str, int base) 
{
    int size = strlen(str); // size = str의 문자열 길이
    int byte_size = WordBitLen>>3; //WordBitLen을 오른쪽으로 3만큼 shift
    size = size/byte_size;
    
    // size를 byte_size로 나눴을 때 나머지가 0이 아니라면
    // size의 값을 1만큼 증가
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
        printf("%08x", x->a[i]);    //8자리 16진수로 출력, 구조체 멤버에 접근하여 값 할당
    }
    printf("\n");
    
    #elif WordBitLen == 8
    // Case 2: word is unsigned char
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%02x", x->a[i]);    //2자리 16진수로 출력, 구조체 멤버에 접근하여 값 할당
    }
    printf("\n");

    #elif WordBitLen == 64
    // Case 3 : word is unsigned long long 
    for  (int i = (x->wordlen) -1 ; i >=0; i--){
        printf("%016x", x->a[i])    //하위 4바이트만 출력, 나머지는 00, 구조체 멤버에 접근하여 값 할당
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
    int len = x->wordlen;   //len에 wordlen 값 대입
    printf("0b");
    for(int i=(len-1);i>0;i--)
    {
        word t = x->a[i];
        for(int j=0;j<WordBitLen;j++)
        {
            // t를 j만큼 shift 했을 때의 비트 값이 1일 때는 1
            // 값이 0일 때는 0 출력
            if((t>>j)&(0x1) ==1)
                printf("1");
            else
                printf("0"); 
        }
    }
    printf("\n");
}

// bigint 정의
void bigint_refine(bigint* x) 
{
    //에러 방지
    if (x == NULL)
        return;

    // new_wordlen에 x의 word 길이를 대입
    // new_wordlen이 1보다 클 경우, a 배열의 크기
    int new_wordlen = x->wordlen;
    while(new_wordlen > 1){
        if (x->a[new_wordlen - 1] != 0)
            break;
        new_wordlen--;
    }

    //x의 word 길이와 new_wordlen 값이 다를경우, 이미 할당한 공간의 크기를 (2*new_wordlen)byte로 바꿈
    if (x->wordlen != new_wordlen){
        x->wordlen = new_wordlen;
        x->a = (word*)realloc(x->a, sizeof(word)*new_wordlen);  
    }

    //x의 word 길이의 값이 1이고 a[0]의 값이 NULL일 경우, sign은 음이 아닌 정수로 설정
    if((x->wordlen == 1) && (x->a[0] == 0x0))
        x->sign = NON_NEGATVE;
}

// bigint 배정
void bigint_assign(bigint** y, bigint* x)
{
    // y의 값이 NULL이 아닐 경우, 계산 삭제 함수 실행(bigint y를 비움)
    if(*y != NULL)
        bigint_delete(y);
    
    // y를 x의 word 길이만큼 새로 만들고
    // y에 x의 부호 할당 (음수, 양수 판단)
    // array_copy(y의 word 배열의 시작주소, x의 word 배열의 시작 주소 위치, 얼만큼 복사?)
    bigint_create(y, x->wordlen);
    (*y)->sign = x->sign;
    array_copy((*y)->a, x->a, x->wordlen);
}

// bigint의 랜덤값 생성
void bigint_gen_rand(bigint** x, int sign, int wordlen)
{
    //bigint 계산 함수를 실행한 후
    //x에 부호 할당
    //x에 a값을 대입하여 array_rand 함수 실행
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

    //cnt가 0보다 클 경우
    //난수와 0xff와 AND 연산한 값인 p의 주소를
    //1씩 늘려서 저장하고
    //cnt의 값은 1씩 줄여서 저장
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

// IsZero? IsOne? 이거 뭐하는 함수죠? //
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

// 두 개의 bigint를 비교
int CompareABS(bigint* x, bigint* y)
{
    //n은 x의 word 길이 값
    //m은 y의 word 길이 값
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
    //x가 음이 아닌 정수이고, y가 음수일 경우, 1 리턴
    if (x->sign == NON_NEGATVE && y->sign == NEGATIVE)
        return 1;

    //x가 음수이고, y가 음이 아닌 정수일 경우, -1 리턴
    if (x->sign == NEGATIVE && y->sign == NON_NEGATVE)
        return -1;
    
    //두 개의 bigint x와 y의 값을 비교하고 리턴 값을 ret으로 정의
    int ret = CompareABS(x, y);

    //x가 음이 아닌 정수일 때, ret 값 리턴 
    if (x->sign == NON_NEGATVE)
        return ret;
    
    return ret * (-1);
    
}