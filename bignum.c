#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;

    word T0[20] = {0xd820952c, 0xe7ffbf9a, 0x58d8a96e, 0xe3ebf714, 0x481d19b7, 0x5ef5f15e, 0x5fdbc340, 0x71925c69, 0x76f58491, 0x17f0a73a, 0x0dc0c10b, 0xb16d8a6b, 0xc587e15f, 0x831f7ca7, 0xe507cf16, 0x364c3c31, 0xd8f37b09, 0x56f14a5c, 0xab6f57e8, 0xd33e6d12};
    word T1[20] = {0, };
    word T2[20] = {0x60a2230f, 0x9795c961, 0xb8fd5cd0, 0x012bbda0, 0x2c9bbc71, 0x2863f748, 0x19dcf6df, 0x9190862b, 0x0e66542d, 0xb60cccfd, 0x50a33212, 0x84af01d6, 0x56408268, 0xdf5cafb2, 0x4cae48ae, 0x1a7335f3, 0x92a31d84, 0x825d46db, 0x3c97ae33, 0xd3066915};
    word T3[20] = {0, };

    for (int i = 0; i < 20; i++){
        T1[i] = T0[19-i];
        T3[i] = T2[19-i];
    }

    bigint_set_by_array(&A, NON_NEGATVE, T1, 20);
    bigint_set_by_array(&B, NON_NEGATVE, T3, 20);
;
    // Test generate random bigint 
    // bigint_gen_rand(&A, NON_NEGATVE, 20);
    // bigint_gen_rand1(&B, NON_NEGATVE, 20);
    
    printf("A : ");
    show_bigint_hex(A);
    
    printf("B : ");
    show_bigint_hex(B);
    printf("\n"); 

    // Multiplication Testing 
    bigint* mul = NULL;
    MULC_Karatsuba(A, B, &mul);
    printf("Mul : ");
    show_bigint_hex(mul);
            
    // Multiplication Testing 
    // bigint* mul = NULL;
    // MULC_Karatsuba(A, B, &mul);
    // printf("Mul : ");
    // show_bigint_hex(mul);

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&mul);

    // bigint_delete(&sum);
    // bigint_delete(&sub);
    // bigint_delete(&mul);
    // printf("%p", mul);
    


    return 0;
}
