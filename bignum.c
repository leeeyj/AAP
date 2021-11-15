#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"

int main()
{
    bigint* A = NULL;
    bigint* B = NULL;

    // Test generate random bigint 
    // bigint_gen_rand(&A, NON_NEGATVE, 20);
    // bigint_gen_rand1(&B, NON_NEGATVE, 20);
    
    word T0[20] = {0x193d8259, 0x7d647203, 0x06600909, 0x0691e1de, 0x3d32a245, 0xa3146a2d, 0x799d7ed1, 0x9102310e, 0xdbc31306, 0x32665df4, 0x67769a50, 0x8ebd9826, 0x86bf90b2, 0xcd79943f, 0x855a3840, 0xc08182ae, 0x123715a2, 0x58ad9b35, 0xc4f97296, 0x2b4c996b};
    word T2[20] = {0,};
    for (int i = 0; i < 20; i++){
        T2[i] = T0[19-i];
    }
    
    bigint_set_by_array(&A, NON_NEGATVE, T2, 20);

    word T1[20] = {0x0a1bf103, 0xc2dfb7cc, 0xa6685bd6, 0xb24d0a76, 0xa20af45f, 0xe6c82701, 0x8339eb27, 0x0b1005bd, 0x07334e3a, 0x2d18281b, 0x7aa590b5, 0x861ff0f9, 0x1177832b, 0xb29b6c74, 0xaeb01b1d, 0x7a5a87b7, 0x0cce7b71, 0xd841997b, 0x45421c9e, 0x02a15966};
    word T3[20] = {0,};
    for (int i = 0; i < 20; i++){
        T3[i] = T1[19-i];
    }
    bigint_set_by_array(&B, NON_NEGATVE, T3, 20);

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

    // Test deleting bigint
    bigint_delete(&A);
    bigint_delete(&B);
    // bigint_delete(&sum);
    // bigint_delete(&sub);
    bigint_delete(&mul);

    


    return 0;
}
