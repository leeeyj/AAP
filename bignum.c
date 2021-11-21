#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;

    // Test generate random bigint 
    bigint_gen_rand(&A, NON_NEGATVE, 10);
    bigint_gen_rand1(&B, NON_NEGATVE, 9);

    printf("A : ");
    show_bigint_hex(A);
    
    printf("B : ");
    show_bigint_hex(B);
    printf("\n"); 

    // Division Testing
    bigint* q = NULL;
    bigint* r = NULL;
    DIV(A, B, &q, &r);
    show_bigint_hex(q);
    show_bigint_hex(r);
            
    // Multiplication Testing 
    // bigint* mul = NULL;
    // MULC_Karatsuba(A, B, &mul);
    // printf("Mul : ");
    // show_bigint_hex(mul);

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&q);
    bigint_delete(&r);

    // bigint_delete(&sum);
    // bigint_delete(&sub);
    // bigint_delete(&mul);
    // printf("%p", mul);
    


    return 0;
}
