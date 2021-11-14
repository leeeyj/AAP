#include "freeCize.h"

// ADDITION //

void ADD_ABC(word* x, word* y, int* c, word* C)
{   
    int carry = (*c);
    (*c) = 0;
    (*C) = ((*x) + (*y));               // (A + B) mod 2 ^ WordBitLen
    if ((*C) < (*x)) (*c) = 1;    

    (*C) = ((*C) + carry);
    if ((*C) < carry) (*c) = 1;

    carry = 0;
}


void ADDC(bigint* x, bigint* y, bigint** z)
{   
    y->a = (word*)realloc(y->a, sizeof(word)*(x->wordlen));
    for (int j = y->wordlen; j < x->wordlen; j++){
        y->a[j] = 0;
    }
    word C = 0;                                 // C is (x[j] + y[j]) mod 2 ^ WordBitLen
    bigint* sum = NULL;                         // a + b 저장할 sum 생성 
    bigint_create(&sum, x->wordlen + 1);        // To save A + B, 최대 max(n, m) + 1 wordlen need
    int carry = 0;

    for (int j = 0; j < x->wordlen; j++){                       // Updating carry and C
        ADD_ABC(&(x->a[j]), &(y->a[j]), &carry, &C);
        sum->a[j] = C;
        // show_bigint_hex(sum);
        C = 0;
    }
    
    if (carry == 1){                    // If last carry is 1, sum = [1][word][word]...[word]
        sum->a[sum->wordlen - 1] = 1;
    }

    bigint_refine(sum);                 // reallocation bigint sum
    bigint_refine(y);
    bigint_assign(z, sum);    
    bigint_delete(&sum);
}

void ADD(bigint* x, bigint* y, bigint** z)
{   
    if (IsZero(x)){
        bigint_assign(z, y);
        return;
    }

    if (IsZero(y)){
        bigint_assign(z, x);
        return;
    } 

    if ((!IsZero(x) && x->sign == NON_NEGATVE) && (!IsZero(y) && y->sign == NEGATIVE)){
        y->sign = NON_NEGATVE;
        SUB(x, y, z);
        y->sign = NEGATIVE;
        return;
    }

    if ((!IsZero(y) && y->sign == NON_NEGATVE) && (!IsZero(x) && x->sign == NEGATIVE)){
        x->sign = NON_NEGATVE;
        SUB(y, x, z);
        x->sign = NEGATIVE;
        return;
    }

    if (x->wordlen >= y->wordlen){
        ADDC(x, y, z);
        return;
    }

    if (x->wordlen < y->wordlen){
        ADDC(y, x, z);
        return;
    } 
}

//SUBTRACT//
void SUB_AbB(word* A, word* B, int* b, word* C)
{
    int b_2 = 0;
    (*C) = ((*A) - (*b));              
    if ((*A) < (*b)) 
        b_2 = 1;

    if ((*C) < (*B)) 
        b_2 = (b_2) ^ 0x1;
    (*C) = (*C) - (*B);
    *b = b_2;
}

void SUBC(bigint* A, bigint* B, bigint** z)
{
    B->a = (word*)realloc(B->a, sizeof(word) * (A->wordlen));
    for (int j = B->wordlen; j < A->wordlen; j++) {
        B->a[j] = 0;
    }

    int b = 0;                              
    word C = 0;                              
    bigint* sub = NULL;
    bigint_create(&sub, A->wordlen);       

    for (int j = 0; j < A->wordlen; j++) {                       
        SUB_AbB(&(A->a[j]), &(B->a[j]), &b, &C);
        sub->a[j] = C;
        C = 0;
    }

    bigint_refine(sub);
    bigint_refine(B);
    bigint_assign(z, sub);
    bigint_delete(&sub);
}

void SUB(bigint* x, bigint* y, bigint** z)
{
    // 만들어주세요 :)
}

// Multiplication 
void MUL_AB(word* x, word* y, bigint** z)
{   
    bigint* mul = NULL;
    bigint_create(&mul, 2);

    word A1 = (*x) >> (WordBitLen / 2); 
    word A0 = (*x) & (word)((1 << (WordBitLen / 2)) - 1);
    
    word B1 = (*y) >> (WordBitLen / 2); 
    word B0 = (*y) & (word)((1 << (WordBitLen / 2)) - 1);
    
    word T1 = A1 * B0;
    word T0 = A0 * B1;
    word T = 0;

    T0 = T1 + T0;
    T1 = (T0 < T1);

    word C1 = A1 * B1;
    word C0 = A0 * B0;
    T = C0;

    C0 = C0 + (T0 << (WordBitLen / 2));
    C1 = C1 + (T1 << (WordBitLen / 2)) + (T0 >> (WordBitLen / 2)) + (C0 < T);

    mul->a[1] = C1;
    mul->a[0] = C0;

    bigint_assign(z, mul);
    bigint_delete(&mul);
    A1 = 0; A0 = 0; B1 = 0; B1 = 0; 
    T1 = 0; T0 = 0; T = 0;
    C1 = 0; C0 = 0; 
}

void MULC_Naive(bigint* x, bigint* y, bigint** z)
{
    bigint* mul = NULL;
    bigint_create(&mul, (x->wordlen + y->wordlen));
    mul->a[0] = 0;

    for (int i = 0; i < x->wordlen; i++){
        for (int j = 0; j < y->wordlen; j++){
            bigint* T = NULL;
            MUL_AB(&(x->a[i]), &(y->a[j]), &T);
            LeftShift(T, WordBitLen * (i + j));
            if (T->wordlen <= mul->wordlen) ADDC(mul, T, &mul);
            else ADDC(T, mul, &mul);
            bigint_delete(&T);
        }
    }

    bigint_assign(z, mul);
    bigint_delete(&mul); 
}

void MULC_Karatsuba(bigint* x, bigint* y, bigint** z)
{   
    // wordlen이 충분히 길지 않으면 Naive Version으로 연산하는 것이 더 빠르다
    if (x->wordlen < 10 | y->wordlen < 10) MULC_Naive(x, y, z);
    else{



    }
}
