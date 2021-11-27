#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Enterstellar_operation.h"
#include <crtdbg.h>

int main()
{

    /*
    **********************************************************************************************************************************************************************
    *                                                                                                                                                                    *
    *                       The Enterstellar library was created for arithmetic on large integers.                                                                       *
    *                                                                                                                                                                    *
    *                       It was produced by Professor Dongchan Kim's class at Kookmin University.                                                                     *
    *                                                                                                                                                                    *
    *                       creator: Keon-hee Choi , Yong-jin Lee , Hyeon-ho Lee,  Yoon-seo Ki, Dong-chan Kim(not profeesor).                                             *
    *                                                                                                                                                                    *
    *                       production date:  21. 09. 01. - 21. 12. 08.                                                                                                  *
    *                                                                                                                                                                    *
    *                                                                                                                                                                    *
    *                       Ownership of this code belongs to its creator(Keon-hee Choi , Yong-jin Lee , Hyun-ho Lee,  Yoon-seo Ki, Dong-chan Kim).                     *
    *                                                                                                                                                                    *
    *                       It is possible to reuse the code for free, but it is prohibited to make it a paid creation.                                                  *
    *                                                                                                                                                                    *
    *                       It can only be used through a contract with the creator.                                                                                     *
    *                                                                                                                                                                    *
    *                                                                                                                                                                    *
    **********************************************************************************************************************************************************************
    */
    srand((unsigned int)time(NULL));
   // printf("%d", sizeof(word));


    bigint* A = NULL;
    bigint* N = NULL;
    bigint* Z = NULL;
    bigint* M = NULL;

    bigint_gen_rand(&A, NON_NEGATVE, 1);
    bigint_gen_rand(&N, NON_NEGATVE, 1);
    bigint_gen_rand(&M, NON_NEGATVE, 1);


    Exponentiation(A, N, &Z, M);
    //show_bigint_bin(A);
    show_bigint_hex(A);
    show_bigint_hex(N);
    show_bigint_hex(M);
    show_bigint_hex(Z);
    // _CrtDumpMemoryLeaks();

    bigint* N_ = NULL;
    bigint_assign(&N_, A);
    int l = 0;
    while (!IsZero(N_)) {
        l += 1;
        RightShift(N_, 1);
    }
    bigint_delete(&N_);
#if 1

    word t = 0;
    for (int i = l - 1; i >= 0; i--)
    {
      
        printf("%u", ((A->a[i / WordBitLen]) >> (i % WordBitLen))&0x1);
    }
#endif

    return 0;
}
