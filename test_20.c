#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include "./freeCize.h"
#include "./includePython.h"

unsigned char* array2string(bigint* x)
{
    unsigned char* s1 = (unsigned char*)malloc(sizeof(word) * 2 + 1);
    unsigned char* s2 = (unsigned char*)malloc(sizeof(word) * 2 * (x->wordlen) + 1);
    if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    if (s2 != NULL) memset(s2, 0, sizeof(word) * 2 * (x->wordlen) + 1);

#if WordBitLen == 32
    for (int i = (x->wordlen) - 1; i >= 0; i--) {
        if (s1 != 0) sprintf(s1, "%08x", x->a[i]);
        if (s2 != 0 && s1 != 0) strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
#elif WordBitLen == 8
    for (int i = (x->wordlen) - 1; i >= 0; i--) {
        if (s1 != 0) sprintf(s1, "%02x", x->a[i]);
        if (s2 != 0 && s1 != 0) strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
#elif WordBitLen == 64
    for (int i = (x->wordlen) - 1; i >= 0; i--) {
        if (s1 != 0) sprintf(s1, "%016llx", x->a[i]);
        if (s2 != 0 && s1 != 0) strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
#endif

}

void test()
{
    PyObject* pName, * pModule, * pFunc, * pValue, * pA, * A_sign, * pB, * B_sign, * pAdd, * Add_sign, * pSub, * Sub_sign, * pMul, * Mul_sign, * pSqu, * Squ_sign;
    Py_Initialize();
    if (Py_IsInitialized()) {                                               // Python 인터프리터 초기화 확인 
#if WordBitLen == 8
        pName = PyUnicode_FromString("test_8bit_version");                              // Python File name -> test1.py, 초기화 필요! 
#elif WordBitLen == 32
        pName = PyUnicode_FromString("test_32bit_version");
#elif WordBitLen == 64
        pName = PyUnicode_FromString("test_64bit_version");
#endif
        pModule = PyImport_Import(pName);                                   // Import Python File            초기화 필요!
        pFunc = PyObject_GetAttrString(pModule, "add");                     // test1.py에 있는 add 함수 (= 함수 이름)  초기화 필요!
        if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
            printf("Addition Testing\n");
            printf("Progress : ");
                bigint* A = NULL;
                bigint* B = NULL;
                bigint_gen_rand(&A, rand() & 0x01, 20);
                bigint_gen_rand(&B, rand() & 0x01, 20);

                bigint* Add = NULL;
                ADD(A, B, &Add);

                unsigned char* string_A = array2string(A);
                pA = PyUnicode_FromString(string_A);                        // 매개 변수 생성, c언어 문자열을 파이썬 문자열로 변환 
                A_sign = Py_BuildValue("i", A->sign);
                printf("A 값=");
                printf(string_A);
                printf("\n\n");

                unsigned char* string_B = array2string(B);
                pB = PyUnicode_FromString(string_B);
                B_sign = Py_BuildValue("i", B->sign);
                printf("B 값=");
                printf(string_B);
                printf("\n\n");

                unsigned char* string_Add = array2string(Add);
                pAdd = PyUnicode_FromString(string_Add);
                Add_sign = Py_BuildValue("i", Add->sign);
                printf("ADD 값=");
                printf(string_Add);
                printf("\n\n");

                // A, A_sign, B, B_sign, sum, sum_sign
                pValue = PyObject_CallFunctionObjArgs(pFunc, pA, A_sign, pB, B_sign, pAdd, Add_sign, NULL);     

                Py_DECREF(pValue);

                Py_DECREF(Add_sign);
                Py_DECREF(pAdd);
                free(string_Add);

                bigint_delete(&Add);
                
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                Py_DECREF(pName);



                    //========================================================================================================//

                    pModule = PyImport_Import(pName);
                    pFunc = PyObject_GetAttrString(pModule, "sub");                     // test1.py에 있는 sub 함수 (= 함수 이름)  초기화 필요!
                    if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
                        printf("Subtraction Testing\n");
                        printf("Progress : ");

                        bigint* Sub = NULL;

                        SUB(A, B, &Sub);

                        unsigned char* string_Sub = array2string(Sub);
                        pSub = PyUnicode_FromString(string_Sub);
                        Sub_sign = Py_BuildValue("i", Sub->sign);
                        printf("Sub 값=");
                        printf(string_Sub);
                        printf("\n\n");

                        // A, A_sign, B, B_sign, sum, sum_sign
                        pValue = PyObject_CallFunctionObjArgs(pFunc, pA, A_sign, pB, B_sign, pSub, Sub_sign, NULL);

                        Py_DECREF(pValue);

                        Py_DECREF(Sub_sign);
                        Py_DECREF(pSub);
                        free(string_Sub);

                        bigint_delete(&Sub);

                        Py_DECREF(pFunc);
                        Py_DECREF(pModule);
                        Py_DECREF(pName);


                        //========================================================================================================//


                        pModule = PyImport_Import(pName);
                        pFunc = PyObject_GetAttrString(pModule, "mul_k");                   // test1.py에 있는 mul_k 함수 (= 함수 이름)  초기화 필요!
                        if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
                            printf("Multiplication Testing\n");
                            printf("Progress : ");

                            bigint* mul = NULL;
                            MUL(A, B, &mul);

                            unsigned char* string_mul = array2string(mul);
                            pMul = PyUnicode_FromString(string_mul);
                            Mul_sign = Py_BuildValue("i", mul->sign);
                            printf("MUL 값=");
                            printf(string_mul);
                            printf("\n\n");

                            // A, A_sign, B, B_sign, sum, sum_sign
                            pValue = PyObject_CallFunctionObjArgs(pFunc, pA, A_sign, pB, B_sign, pMul, Mul_sign, NULL);

                            Py_DECREF(pValue);

                            Py_DECREF(Mul_sign);
                            Py_DECREF(pMul);
                            free(string_mul);

                            bigint_delete(&mul);

                            Py_DECREF(pFunc);
                            Py_DECREF(pModule);
                            Py_DECREF(pName);


                            //========================================================================================================//


                            pModule = PyImport_Import(pName);
                            pFunc = PyObject_GetAttrString(pModule, "sqr");                   // test1.py에 있는 sqr 함수 (= 함수 이름)  초기화 필요!
                            if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
                            printf("Squaring Testing\n");
                            printf("Progress : ");

                            bigint* Squ = NULL;
                            SQU(A, &Squ);

                            unsigned char* string_Squ = array2string(Squ);
                            pSqu = PyUnicode_FromString(string_Squ);
                            Squ_sign = Py_BuildValue("i", Squ->sign);
                            printf("Squ 값=");
                            printf(string_Squ);
                            printf("\n\n");

                            // A, A_sign, B, B_sign, sum, sum_sign
                            pValue = PyObject_CallFunctionObjArgs(pFunc, pA, A_sign, pSqu, Squ_sign, NULL);

                            Py_DECREF(pValue);

                            Py_DECREF(Squ_sign);
                            Py_DECREF(pSqu);
                            free(string_Squ);

                            bigint_delete(&Squ);

                            Py_DECREF(pFunc);
                            Py_DECREF(pModule);
                            Py_DECREF(pName);
                            return;
                
                            }

                        return;
                        }  

                    return;
                    }   

        return;
        }
    }
    Py_Finalize();
   
}

void ModularExponentiation_test()
{


}


int main()
{
    /*=========================================================================================================================================================*/
    // Setting Up Python for testing only
    srand((unsigned int)time(NULL));
    printf("<                                        %d-bit Version Testing                                >\n\n", WordBitLen);
    for (int i = 0; i < 20; i++) {
        test();
    }

    printf("<                                           Test Complete!!!                                   >\n");
    return 0;
}

/*
// 리스트로 전달하는 방법
pArg1 = PyList_New(A->wordlen);
Py_ssize_t size = PyList_GET_SIZE(pArg1);
for (Py_ssize_t j = 0; j < size; j++) {
    PyList_SetItem(pArg1, j, Py_BuildValue("I", A->a[j]));
}
*/