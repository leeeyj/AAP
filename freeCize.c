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
        bigint* y_ = NULL;
        bigint_assign(&y_, y);
        y_->sign = NON_NEGATVE;
        SUB(x, y_, z);
        bigint_delete(&y_);
        return;
    }
 
    if ((!IsZero(y) && y->sign == NON_NEGATVE) && (!IsZero(x) && x->sign == NEGATIVE)){
        bigint* x_ = NULL;
        bigint_assign(&x_, x);
        x_->sign = NON_NEGATVE;
        SUB(y, x_, z);
        bigint_delete(&x_);
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
    if (IsZero(x)){
        bigint_assign(z, y);
        (*z)->sign = NEGATIVE; 
        return;
    }
    if (IsZero(y)){
        bigint_assign(z, x);
        (*z)->sign = NON_NEGATVE; 
        return;
    }
    if(Compare(x,y)==0){
        bigint_set_zero(z);
        return;
    }
    if((y->sign==NON_NEGATVE)&&(x->sign==NON_NEGATVE)&&(Compare(x,y) != -1) )
    {
        SUBC(x,y,z);
        (*z)->sign = NON_NEGATVE;
        return;
    }
    if((x->sign == NON_NEGATVE)&&(y->sign==NON_NEGATVE)&&(Compare(x,y)==-1))
    {
        SUBC(y,x,z);
        (*z)->sign = NEGATIVE;
        return;
    }
    if((x->sign==NEGATIVE)&&(y->sign==NEGATIVE)&&(Compare(x,y)!=-1))
    {
        bigint* x_ = NULL;
        bigint* y_ = NULL;
        bigint_assign(&x_, x);
        bigint_assign(&y_, y);    
        x_->sign = NON_NEGATVE;
        y_->sign = NON_NEGATVE;
        SUBC(y_,x_,z);
        bigint_delete(&x_);
        bigint_delete(&y_);
        return;
    }
    if((y->sign==NEGATIVE)&&(x->sign==NEGATIVE)&&(Compare(x,y)==-1))
    {
        bigint* x_ = NULL;
        bigint* y_ = NULL;
        bigint_assign(&x_, x);
        bigint_assign(&y_, y);    
        x_->sign = NON_NEGATVE;
        y_->sign = NON_NEGATVE;
        SUBC(x,y,z);
        (*z)->sign = NEGATIVE;
        bigint_delete(&x_);
        bigint_delete(&y_);
        return;
    }

    if((x->sign == NON_NEGATVE)&&(y->sign == NEGATIVE))
    {
        bigint* y_ = NULL;
        bigint_assign(&y_, y);
        y_->sign = NON_NEGATVE;
        ADD(x,y,z);
        bigint_delete(&y_);

        return;
    }
    if((x->sign == NEGATIVE)&&(y->sign == NON_NEGATVE))
    {   
        bigint* x_ = NULL;
        bigint_assign(&x_, y);
        x_->sign = NON_NEGATVE;
        ADD(x,y,z);
        (*z)->sign = NEGATIVE;        
        bigint_delete(&x_);
        return;
    }
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
            MUL_AB(&(x->a[i]), &(y->a[j]), &T);       // 여기 수정함 11/15 AM11:50
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
    if (x->wordlen <= 10 | y->wordlen <= 10){
        MULC_Naive(x, y, z);
        return;
    }
    else{
        int l = 0;
        if (x->wordlen >= y->wordlen) l = (x->wordlen + 1) >> 1;
        if (x->wordlen < y->wordlen) l = (y->wordlen + 1) >> 1;
        // printf("l : %d \n", l);
        bigint* A1 = NULL; bigint* A0 = NULL;
        bigint* B1 = NULL; bigint* B0 = NULL;
        bigint* T1 = NULL; bigint* T0 = NULL;
        bigint* S1 = NULL; bigint* S0 = NULL;
        bigint* S = NULL; bigint* R = NULL;

        bigint_assign(&A1, x);
        bigint_assign(&A0, x);
        bigint_assign(&B1, y);
        bigint_assign(&B0, y);
        
        RightShift(A1, l * WordBitLen);
        Reduction(A0, l * WordBitLen);
        RightShift(B1, l * WordBitLen);
        Reduction(B0, l * WordBitLen);
    
        // printf("A1 : (%d)", A1->sign); show_bigint_hex(A1);
        // printf("A0 : (%d)", A0->sign); show_bigint_hex(A0);
        // printf("B1 : (%d)", B1->sign); show_bigint_hex(B1);
        // printf("B0 : (%d)", B0->sign); show_bigint_hex(B0);
        // printf("\n");

        
        MULC_Karatsuba(A1, B1, &T1);
        MULC_Karatsuba(A0, B0, &T0);
        // printf("T1 : (%d)", T1->sign); show_bigint_hex(T1);
        // printf("T0 : (%d)", T0->sign); show_bigint_hex(T0);
        // printf("\n");
        
        LeftShift(T1, 2 * l * WordBitLen);
        ADD(T1, T0, &R);
        RightShift(T1, 2 * l * WordBitLen);
        // printf("T1 + T0 : (%d)", R->sign); show_bigint_hex(R);
        // printf("T1 : (%d)", T1->sign); show_bigint_hex(T1);

        SUB(A0, A1, &S1);
        SUB(B1, B0, &S0);
        // printf("S1 : (%d) ", S1->sign); show_bigint_hex(S1);
        // printf("S0 : (%d) ", S0->sign); show_bigint_hex(S0);

        int S_sign = S1->sign ^ S0->sign;
        S1->sign = NON_NEGATVE; S0->sign = NON_NEGATVE;
        MULC_Karatsuba(S1, S0, &S);
        if (S_sign == 0) S->sign = NON_NEGATVE;
        if (S_sign == 1) S->sign = NEGATIVE;
        // printf("S : (%d) ", S->sign); show_bigint_hex(S);

        ADD(S, T1, &S);  
        // printf("S + T1 : (%d) ", S->sign); show_bigint_hex(S);
        ADD(S, T0, &S);
        // printf("S + T1 + T0: (%d) ", S->sign); show_bigint_hex(S);

        // Error...;; 
        LeftShift(S, l * WordBitLen);
        // printf("S : (%d) ", S->sign); show_bigint_hex(S);

        ADD(R, S, &R);
        // printf("R : (%d) ", R->sign); show_bigint_hex(R);
        bigint_refine(R);
        bigint_assign(z, R);
        
        bigint_delete(&A1); bigint_delete(&A0);
        bigint_delete(&B1); bigint_delete(&B0);
        bigint_delete(&T1); bigint_delete(&T0);
        bigint_delete(&S1); bigint_delete(&S0);
        bigint_delete(&S); bigint_delete(&R);
    }
}

void MUL(bigint* x, bigint* y, bigint** z)
{
    if (IsZero(x) | IsZero(y))
    {
        bigint* mul = NULL;
        bigint_create(&mul, 1);
        mul->a[0] = 0;
        bigint_assign(z, mul);
        bigint_delete(&mul);
        return;
    }
    if (IsOne(x)){
        bigint_assign(z, y);
        (*z)->sign = (x->sign + y->sign) % 2;
        return;
    }
    if (IsOne(y)){
        bigint_assign(z, x);
        (*z)->sign = (x->sign + y->sign) % 2;
        return;
    }
    int x_sign = x->sign;
    int y_sign = y->sign;
    x->sign = NON_NEGATVE;
    y->sign = NON_NEGATVE;
    MULC_Karatsuba(x, y, z);
    x->sign = x_sign;
    y->sign = y_sign;
    (*z)->sign = (x->sign + y->sign) % 2;
    return;
}

// DIVISION //
void Long_Division(bigint* A, bigint* B, bigint** Q)
{
    bigint* q = NULL;
    bigint* r = NULL;
    
    // Q Initial Setting 
    bigint_create(&q, 1);
    q->a[0] = 0;

    // R Initial Setting
    bigint_assign(&r, A);
    RightShift(r, WordBitLen);
    word A0 = A->a[0];

    for (int i = WordBitLen - 1; i >= 0; i--){
        if (r->a[0] >= (word)(1<<(WordBitLen-1))){
            q->a[0] += (word)(1<<i);
            LeftShift(r, 1);
            r->a[0] += (A0 >> i) & 0x01;
            SUB(r, B, &r);
        }    
        else{
            LeftShift(r, 1);
            r->a[0] += (A0 >> i) & 0x01;
            if (Compare(r, B) == 1 | Compare(r, B) == 0){
                q->a[0] += (word)(1<<i);
                SUB(r, B, &r);
            }
        }
    }

    // show_bigint_hex(Q);
    // show_bigint_hex(R);

    bigint_assign(Q, q);
    bigint_delete(&q);
    bigint_delete(&r);
    A0 = 0;
}

void DIVCC(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    bigint* q = NULL;
    bigint* r = NULL;
    bigint* Bq = NULL;

    if (A->wordlen == B->wordlen){
        bigint_create(&q, 1);
        q->a[0] = (word)(A->a[B->wordlen - 1] / B->a[B->wordlen - 1]);
    }

    if (A->wordlen == B->wordlen + 1){
        if (A->a[B->wordlen] == B->a[B->wordlen - 1]){
            bigint_create(&q, 1);
            #if WordBitLen == 32
            q->a[0] = 0xffffffff;
            #elif WordBitLen == 8
            q->a[0] = 0xff;
            #elif WordBitLen == 64
            q->a[0] = 0xffffffffffffffff;
            #endif
        } else {
            bigint* new_A = NULL;
            bigint* new_B = NULL;

            bigint_create(&new_A, 2);
            bigint_create(&new_B, 1);
            new_A->a[0] = A->a[B->wordlen - 1];
            new_A->a[1] = A->a[B->wordlen];
            new_B->a[0] = B->a[B->wordlen - 1];

            Long_Division(new_A, new_B, &q);
            
            bigint_delete(&new_A);
            bigint_delete(&new_B);
        }
    }

    MUL(B, q, &Bq);
    SUB(A, Bq, &r);

    bigint* t = NULL;
    bigint_create(&t, 1);
    t->a[0] = 1;

    while (r->sign == NEGATIVE){
        SUB(q, t, &q);
        ADD(r, B, &r);
    }

    bigint_assign(Q, q);
    bigint_assign(R, r);

    bigint_delete(&t);
    bigint_delete(&q);
    bigint_delete(&r);
    bigint_delete(&Bq);
}

void DIVC(bigint* A, bigint* B, bigint** Q, bigint** R)
{   
    bigint* q = NULL;
    bigint* r = NULL;
    bigint* A_ = NULL;
    bigint* B_ = NULL;

    bigint_assign(&A_, A);
    bigint_assign(&B_, B);

    if (Compare(A_, B_) == -1){
        bigint_create(&q, 1);
        q->a[0] = 0;

        bigint_assign(Q, q);
        bigint_assign(R, A_);

        bigint_delete(&q);
        return;
    }

    int k = 0;
    while(B_->a[B_->wordlen - 1] <= (1 << (WordBitLen - 1))){
        LeftShift(A_, 1);
        LeftShift(B_, 1);
        k += 1;
    }

    DIVCC(A_, B_, &q, &r);

    bigint_assign(Q, q);
    RightShift(r, k);
    bigint_assign(R, r);

    bigint_delete(&q);
    bigint_delete(&r);
    bigint_delete(&A_);
    bigint_delete(&B_);
}

void DIV(bigint* A, bigint* B, bigint** Q, bigint** R)
{
    bigint* qi = NULL;
    bigint* r = NULL;
    bigint* q = NULL;

    if (Compare(A, B) == -1){
        bigint_create(&qi, 1);
        qi->a[0] = 0;

        bigint_assign(Q, qi);
        bigint_assign(R, A);

        bigint_delete(&qi);
        return;
    }

    bigint_create(&r, 1);
    r->a[0] = 0;

    bigint_create(&q, A->wordlen);

    for (int i = A->wordlen - 1; i >= 0; i--){
        LeftShift(r, WordBitLen);
        r->a[0] += A->a[i];
        DIVC(r, B, &qi, &r);
        q->a[i] = qi->a[0];
    }

    bigint_refine(q);
    bigint_refine(r);
    bigint_assign(Q, q);
    bigint_assign(R, r);

    bigint_delete(&q);
    bigint_delete(&r);
    bigint_delete(&qi);
}


void Single_percision_sqr(word A, word* C) 
{
    int worddiv2 = (WordBitLen >> 1);
    word A1 = A >> worddiv2;
    word A0 = A % (1 << worddiv2);
    word C0 = A0*A0;
    word C1 = A1 * A1;
    C[1] = (((A1 * A1) << WordBitLen) + (A0 * A0) + ((A0 * A1) << (worddiv2 + 1))) && (1 << WordBitLen);
    C[0] = (((A1 * A1) << WordBitLen) + (A0 * A0) + ((A0 * A1) << (worddiv2 + 1)))>>WordBitLen;
}

#if 0 //구현이 너무 어려움 370번 라인 저렇게 하는거 아닌거 아는데,, 어케하는지,,,
void Sqr_Textbook(bigint* x, bigint**y)
{
    bigint** C1 = NULL;bigint** C2 = NULL;
    bigint** T2 = NULL;
    word T1[2] = {0,0};
    
    bigint_create(T2,2*(sizeof(word)));
    bigint_create(C1,2*(x->wordlen));bigint_create(C2,2*(x->wordlen));
    int t = x->wordlen;
    for (int i = 0;i<t;i++)
    {
        Single_percision_sqr(x->a[i],&T1);
        (*C1)->a[2*i] = T1[0];
        (*C1)->a[2*i+1] = T1[1];
        for(int j=i+1;j<(t-1);j++)
        {
            MUL_AB(x->a[i],x->a[j],T2);
            LeftShift(T2,(i+j)*sizeof(word));
            ADD(C1,T2,C2);
        }
    }
    LeftShift(C2,1);
    ADD(C1,C2,y);

}
#endif
void SQUC(bigint* x, bigint** y)
{
    if (x->wordlen == 0)
        bigint_assign(y, x);
    if (x->wordlen == 1)
    {
        bigint_create(y, 1);
        (*y)->a[0] = 1;
    }
}
void Sqr_karatsba(bigint* x, bigint** y) 
{
    if (x->wordlen < 2)
    {
        SQUC(x, y);
        return;
    }
    int xsign = x->sign;
    x->sign = NON_NEGATVE;
    int l = (x->wordlen + 1) >> 1;
    bigint** A1 = NULL;
    bigint** A0 = NULL;
    
    bigint_assign(A0, x);
    bigint_assign(A1, x);
    RightShift(A1, l * (WordBitLen));
    Reduction(A0, l * (WordBitLen));

    bigint** T0=NULL; bigint** T1=NULL;
    Sqr_karatsba(A1, T1);
    Sqr_karatsba(A0, T0);

    bigint** R = NULL; bigint** S = NULL;
    LeftShift(T1, 2 * l * (WordBitLen));
    ADD(T1, T0, R);
    MULC_Karatsuba(A0, A1, S);
    LeftShift(S, l * (WordBitLen) + 1);
    ADD(R, S, y);
}
void Exponentiation(bigint* x, int N, bigint** z)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint_create(t0, 1);
    bigint_assign(t1, x);
    t0->a[0] = 1;
    
    int l = x->wordlen;
    for (int i = l - 1; i > 0; i--)
    {
        if (N & 0x1 == 1)
        {
            MULC_Karatsuba(t0, t1, t0);
            Sqr_karatsba(t1,t1);
        }
        else
        {
            MULC_Karatsuba(t0, t1, t1);
            Sqr_karatsba(t0, t0);
        }
        N >> 1;
    }
    bigint_assign(z, t0);

}

void Exponentiation2(bigint* x, int N, bigint** z)
{
    bigint* t0 = NULL;
    bigint* t1 = NULL;
    bigint_create(t0, 1);
    bigint_assign(t1, x);
    t0->a[0] = 0;

    int l = x->wordlen;
    for (int i = l - 1; i < 0; i--)
    {
        if (N & 0x1 == 1)
        {
            ADD(t0, t1, t0);
            LeftShift(t1, 1);
        }
        else
        {
            ADD(t0, t1, t1);
            LeftShift(t0, t0);
        }
        N >> 1;
    }
    bigint_assign(z, t0);

}

void Montgomery_reduction(bigint* x, bigint* N,bigint**z)
{
    bigint**R = NULL;
    while(1)
    {
        bigint_gen_rand(R,NON_NEGATVE,N->wordlen);
        if(gcd(R,N)==1)
        {
            if(Compare(N,R)==-1)
            {
                break;
            }
        }
    }
    //exgcd(R,N)  ==>>> N' 값 구하고 mod R===> 하위 R->wordlen
    
    
}