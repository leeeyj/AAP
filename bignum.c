#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    // bigint_create(&A, 10);
    // word T[2] = { 0x0000cdef, 0x10234567 };
    // 0x 10234567 0000cdef
    // bigint_set_by_array(&A, 0, T, 2);
    // printf("%d", word);
    // show_bigint_hex(A);
    bigint_gen_rand(&A, NON_NEGATVE, 2);
    show_bigint_hex(A);
    bigint_delete(&A);
    return 0;
}






