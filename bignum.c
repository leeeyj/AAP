#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;
    bigint* N = NULL;
    bigint* M = NULL;

    // Test generate random bigint 
    bigint_gen_rand(&A, NON_NEGATVE, 1);
    bigint_gen_rand1(&N, NON_NEGATVE, 2);
    // bigint_create(&B, 10);

    word T[1] = {0x12345678};
    bigint_set_by_array(&M, NON_NEGATVE, T, 1);

    printf("A : ");
    show_bigint_hex(A);
    
    Exponentiation(A, N, &B, M);
    show_bigint_hex(B);
    // show_bigint_hex(B);
    // printf("B : ");
    // show_bigint_hex(B);
    // printf("\n"); 

    // Test Squaring 
    // Sqr_karatsuba(A, &B);
    // printf("A^2 = ");
    // show_bigint_hex(B);

    // Division Testing
    // bigint* q = NULL;
    // bigint* r = NULL;
    // DIV(A, B, &q, &r);
    // show_bigint_hex(q);
    // show_bigint_hex(r);
             
    // Multiplication Testing 
    //bigint* mul = NULL;
    //MUL(A, B, &mul);
    //printf("Mul : ");
    //show_bigint_hex(mul);

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&M);
    bigint_delete(&N);


    // bigint_delete(&q);
    // bigint_delete(&r);

    // bigint_delete(&sum);
    // bigint_delete(&sub);
    //bigint_delete(&mul);
    // printf("%p", mul);


    return 0;
}
