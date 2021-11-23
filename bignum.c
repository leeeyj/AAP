#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;
    bigint_gen_rand(&A, NON_NEGATVE, 1);
    bigint_gen_rand1(&B, NON_NEGATVE, 1);

    show_bigint_hex(A);
    show_bigint_hex(B);
    bigint* sum = NULL;
    ADD(A, B, &sum);
    show_bigint_hex(sum);

    return 0;
}
