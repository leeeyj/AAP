#include "freeCize.h"

// ADDITION //
void ADD_ABC(word* x, word* y, int* c, word* C)
{
    (*C) = ((*x) + (*y)) & (2*( 1<<(WordBitLen-1) - 1) + 1);             // (A + B) mod 2 ^ WordBitLen
    if ((*C) < (*x)) *c = 1;

    (*C) = ((*C) + (*c));
    if ((*C) < (*c)) *c = 1;

    (*c) = 0;
}

bigint *ADDC(bigint* x, bigint* y)
{   
    y->a = (word*)realloc(y->a, sizeof(word)*(x->wordlen));
    for (int j = y->wordlen; j < x->wordlen; j++){
        y->a[j] = 0;
    }
    
    word C = 0;                                 // C is (x[j] + y[j]) mod 2 ^ WordBitLen
    bigint* sum = NULL;
    bigint_create(&sum, x->wordlen + 1);        // To save A + B, 최대 max(n, m) + 1 wordlen need
    int carry = 0;
    for (int j = 0; j < x->wordlen; j++){
        ADD_ABC(&(x->a[j]), &(y->a[j]), &carry, &C);
        sum->a[j] = C;
    }
    
    if (carry == 1){
        sum->a[sum->wordlen - 1] = 1;
        return sum;
    }
    bigint_refine(sum);
    return sum;
}