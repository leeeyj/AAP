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


    for (int j = 0; j < x->wordlen; j++){                       // Updating carry and C
        ADD_ABC(&(x->a[j]), &(y->a[j]), &carry, &C);
        sum->a[j] = C;
        C = 0;
    }
    
    if (carry == 1){                    // If last carry is 1, sum = [1][word][word]...[word]
        sum->a[sum->wordlen - 1] = 1;
        return sum;
    }

    bigint_refine(sum);                 // reallocation bigint sum
    return sum;
}