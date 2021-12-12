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
    
    bigint* A = NULL;
    bigint* B = NULL;
    
    bigint_gen_rand(&A, NON_NEGATVE, 2);
    bigint_gen_rand(&B, NON_NEGATVE, 2);


    show_bigint_hex(A);

    show_bigint_hex(B);

    bigint_delete(&B);
    bigint_delete(&A);


    // _CrtDumpMemoryLeaks();

    return 0;
}
