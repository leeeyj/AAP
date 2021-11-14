#include "freeCize.h"

// ADDITION //
int ADD_ABC(word* x, word* y, int* c, word* C)
{
    (*C) = ((*x) + (*y));               // (A + B) mod 2 ^ WordBitLen
    if ((*C) < (*x)) return *c = 1;

    (*C) = ((*C) + (*c));
    if ((*C) < (*c)) return *c = 1;

    return *c = 0;
}

bigint* ADDC(bigint* x, bigint* y)
{
    y->a = (word*)realloc(y->a, sizeof(word) * (x->wordlen));
    for (int j = y->wordlen; j < x->wordlen; j++) {
        y->a[j] = 0;
    }

    word C = 0;                                 // C is (x[j] + y[j]) mod 2 ^ WordBitLen
    bigint* sum = NULL;
    bigint_create(&sum, x->wordlen + 1);        // To save A + B, ÃÖ´ë max(n, m) + 1 wordlen need
    int carry = 0;


    for (int j = 0; j < x->wordlen; j++) {                       // Updating carry and C
        ADD_ABC(&(x->a[j]), &(y->a[j]), &carry, &C);
        sum->a[j] = C;
        C = 0;
    }

    if (carry == 1) {                    // If last carry is 1, sum = [1][word][word]...[word]
        sum->a[sum->wordlen - 1] = 1;
        return sum;
    }

    bigint_refine(sum);                 // reallocation bigint sum
    return sum;
}

//SUBTRACT//

void SUB_AbB(word* A, word* B, int* b, word* C)
{
    int b_2 = 0;
    (*C) = ((*A) - (*b));              
    if ((*A) < (*b)) 
        b_2 = 1;
    //0-1?....? what's problem..?-keon
    if ((*C) < (*B)) 
        b_2 = (b_2) ^ 0x1;
    (*C) = (*C) - (*B);
    *b = b_2;
    
    //return *C;
}

bigint* SUBC(bigint* A, bigint* B)
{
    B->a = (word*)realloc(B->a, sizeof(word) * (B->wordlen));
    for (int j = B->wordlen; j < A->wordlen; j++) {
        B->a[j] = 0;
    }

    int b = 0;                              
    word C = 0;                              
    bigint* sub = NULL;
    bigint_create(&sub, A->wordlen + 1);       
    // int count = 0; //what is this...? - keon

    for (int j = 0; j < A->wordlen; j++) {                       
        SUB_AbB(&(A->a[j]), &(B->a[j]), &b, &C);
        sub->a[j] = C;
        C = 0;
    }

    bigint_refine(sub);
    return sub;
}


bigint* ADD(bigint* x, bigint* y)
{
    if (x->wordlen == 0)
        return y;
    if (y->wordlen == 0)
        return x;

    if ((x->sign == NON_NEGATVE) & (y->sign == NEGATIVE))
    {

        // we need to make absolute func
        bigint** tmp = NULL;
        bigint_assign(tmp, y);
        (*tmp)->sign = NON_NEGATVE;
        return SUB(x, (*tmp));
    }
    if ((x->sign == NEGATIVE) & (y->sign == NON_NEGATVE))
    {

        // we need to make absolute func
        bigint** tmp = NULL;
        bigint_assign(tmp, x);
        (*tmp)->sign = NON_NEGATVE;
        return SUB(x, (*tmp));
    }
    if ((x->wordlen) >= (y->wordlen))
    {
        return ADDC(x, y);
    }
    else
        return ADDC(y, x);

    return -1;
}


bigint* SUB(bigint* x, bigint* y)
{
    if (x->wordlen == 0)
    {
        bigint** tmp = NULL;
        bigint_assign(tmp, y);
        (*tmp)->sign = (y->sign)^0x1;
        return *tmp;
    }
    if (y->wordlen == 0)
        return x;
    if (Compare(x,y) == 0) 
        return 0;

    if ((y->sign == NON_NEGATVE) & (Compare(x, y) != -1))
        return SUBC(x, y);
    if ((x->sign == NON_NEGATVE) & (Compare(x, y) == -1))
    {
        bigint** tmp = NULL;
        bigint_assign(tmp, SUBC(y, x));
        (*tmp)->sign = ((*tmp)->sign) ^ 0x1;
        return *tmp;
    }

    if ((Compare(x, y) != -1) & (x->sign == NEGATIVE))
    {
        bigint** tmp1 = NULL;
        bigint_assign(tmp1, x);
        (*tmp1)->sign = NON_NEGATVE;
        bigint** tmp2 = NULL;
        bigint_assign(tmp2, y);
        (*tmp2)->sign = NON_NEGATVE;
        return SUBC(tmp1, tmp2);
    }

    if ((Compare(x, y) == -1) & (y->sign == NEGATIVE))
    {
        bigint** tmp1 = NULL;
        bigint_assign(tmp1, x);
        (*tmp1)->sign = NON_NEGATVE;
        bigint** tmp2 = NULL;
        bigint_assign(tmp2, y);
        (*tmp2)->sign = NON_NEGATVE;

        bigint** tmp3 = NULL;
        bigint_assign(tmp3, SUBC(tmp1, tmp2));
        (*tmp3)->sign ^= 0x1;
        return *tmp3;
    }

    if ((x->sign == NON_NEGATVE) & (y->sign == NEGATIVE))
    {
        bigint** tmp1 = NULL;
        bigint_assign(tmp1, y);
        (*tmp1)->sign = NON_NEGATVE;
        return ADD(x, *tmp1);
    }
    else
    {
        bigint** tmp1 = NULL;
        bigint_assign(tmp1, x);
        (*tmp1)->sign = NON_NEGATVE;
        
        bigint** tmp2 = NULL;
        bigint_assign(tmp2, ADD(tmp1, y));
        (*tmp2)->sign ^= 0x1;
        return *tmp2;
    }
    return -1;
}