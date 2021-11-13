#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;

    // Test generate random bigint 
    bigint_gen_rand1(&A, NON_NEGATVE, 3);
    bigint_gen_rand1(&B, NON_NEGATVE, 2);
    
    printf("A : ");
    show_bigint_hex(A);
    
    printf("B : ");
    show_bigint_hex(B);
    printf("\n");

    // Addition Testing
    bigint* sum = NULL;
    ADD(A, B, &sum);
    printf("Sum : ");
    show_bigint_hex(sum);
    // printf("\n");

    // Multiplication Testing 
    bigint* mul = NULL;
    MULC_Naive(A, B, &mul);
    printf("Mul : ");
    show_bigint_hex(mul);

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&sum);
    bigint_delete(&mul);


    return 0;
}






