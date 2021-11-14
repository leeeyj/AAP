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
    *b = 0;
    (*C) = ((*A) - (*b));              
    if ((*A) < (*b)) 
        *b = 1;
    //0-1?....? what's problem..?-keon
    if ((*C) < (*B)) 
        *b = (*b) ^ 0x1;
    (*C) = (*C) - (*B);
    word Temp = -1;
    *C = (Temp+1) * (*b)*(-1) + *C;
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
