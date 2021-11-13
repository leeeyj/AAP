#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;

    // Test memory allocation bigint
    // bigint_create(&A, 10);
    //

    // Test setting bigint by array
    // word T[2] = { 0x0000cdef, 0x10234567 };
    // 0x 10234567 0000cdef
    // bigint_set_by_array(&A, 0, T, 2);
    // printf("%d", word);
    // show_bigint_hex(A);
    //

    // Test generate random bigint 
    bigint_gen_rand(&A, NON_NEGATVE, 2);
    bigint_gen_rand1(&B, NON_NEGATVE, 2);
    
    printf("A : ");
    show_bigint_hex(A);
    
    printf("B : ");
    show_bigint_hex(B);
    printf("\n");
    
    // Addition Testing
    bigint* sum = NULL;
    ADDC(A, B, &sum);
    printf("Sum : ");
    show_bigint_hex(sum);
    printf("\n");
    
    // Test compare two bigint
    // if (Compare(A, B) == 1)
    //     printf("A > B");
    // else if (Compare(A, B) == -1){
    //     printf("A < B");
    //     bigint* swap;
    //     swap = A;
    //     A = B;
    //     B = swap;
    // }        
    // else
        // printf("A = B");

    // Subtraction Testing 
    // bigint* sub = NULL;
    // SUBC(A, B, &sub);
    // printf("\n");
    // show_bigint_hex(sub);

    // Left Shift Testing 
    // printf("Left Shift 163 : ");
    // LeftShift(sum, 163);
    // show_bigint_hex(sum);

    // Right Shift Testing 
    // printf("Right Shift 100 : ");
    // RightShift(sum, 100);
    // show_bigint_hex(sum);

    // Reduction Testing 
    Reduction(sum, 33);
    printf("sum mod 2 ^ 65 : ");
    show_bigint_hex(sum);

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&sum);
    //
    return 0;
}






