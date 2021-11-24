#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freeCize.h"


/*
**********************************************************************************************************************************************************************
*                                                                                                                                                                    * 
*                       The Interstellar library was created for arithmetic on large integers.                                                                       *
*                                                                                                                                                                    *
*                       It was produced by Professor Dongchan Kim's class at Kookmin University.                                                                     *
*                                                                                                                                                                    *
*                       creator: Keon-hee Choi , Yong-jin Lee , Hyeon-ho Lee,  Yoon-seo Ki, Dong-chan Kim(not profeesor)                                             *
*                                                                                                                                                                    *
*                       production date:  21. 09. 01. - 21. 12. 08.                                                                                                  *
*                                                                                                                                                                    *
*                                                                                                                                                                    *
*                       Ownership of this code belongs to its creator(Keon-hee Choi , Yong-jin Lee , Hyeon-ho Lee,  Yoon-seo Ki, Dong-chan Kim).                     *
*                                                                                                                                                                    *
*                       It is possible to reuse the code for free, but it is prohibited to make it a paid creation.                                                  *
*                                                                                                                                                                    *
*                       It can only be used through a contract with the creator.                                                                                     *
*                                                                                                                                                                    *
*                                                                                                                                                                    *
**********************************************************************************************************************************************************************
*/
int main()
{
    bigint* A = NULL;
    bigint* B = NULL;
    bigint_gen_rand(&A, NON_NEGATVE, 1);
    bigint_gen_rand1(&B, NON_NEGATVE, 1);

    show_bigint_hex(A);
    show_bigint_hex(B);
    bigint* sum = NULL;
    clock_t st, et; //각각 start time, end time을 의미(이름 상관 없음)

    st = clock();
   
    ADD(A, B, &sum);
    et = clock();

    printf("%d ms\n", et - st);
    show_bigint_hex(sum);

    return 0;
}
