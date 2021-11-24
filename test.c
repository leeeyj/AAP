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

    for (int i = (x->wordlen) - 1; i >= 0; i--) {
        if (s1 != 0) sprintf(s1, "%08x", x->a[i]);
        if (s2 != 0 && s1 != 0) strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
}

int main()
{   
    /*=========================================================================================================================================================*/
    // Setting Up Python for testing only
   
    PyObject *pName, *pModule, *pFunc, *pValue, *pA, *A_sign, *pB, *B_sign, *pMul, *Mul_sign;
    Py_Initialize();                                                        // Python 인터프리터 초기화 
    if (Py_IsInitialized()) {                                               // Python 인터프리터 초기화 확인 
        pName = PyUnicode_FromString("test1");                              // Python File name -> test1.py, 초기화 필요! 
        pModule = PyImport_Import(pName);                                   // Import Python File            초기화 필요!
        pFunc = PyObject_GetAttrString(pModule, "mul_k");                     // test1.py에 있는 add 함수 (= 함수 이름)  초기화 필요!
        if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
            int count = 0;
            printf("Testing : ");
            for (int i = 1; i < 100001; i++) {                               // 100000번 테스트
                bigint* A = NULL; 
                bigint* B = NULL;              
                
                srand(time(NULL));
                bigint_gen_rand(&A, 0, 20);
                srand(time(NULL) + 1);
                bigint_gen_rand1(&B, 0, 20);

                bigint* mul = NULL;
                MUL(A, B, &mul);
                // (A, B, &mul);

                unsigned char* string_A = array2string(A);
                pA = PyUnicode_FromString(string_A);                     // 매개 변수 생성, c언어 문자열을 파이썬 문자열로 변환 
                A_sign = Py_BuildValue("i", A->sign);

                unsigned char* string_B = array2string(B);
                pB = PyUnicode_FromString(string_B);
                B_sign = Py_BuildValue("i", B->sign);

                unsigned char* string_mul = array2string(mul);
                pMul = PyUnicode_FromString(string_mul);
                Mul_sign = Py_BuildValue("i", mul->sign);

                // A, A_sign, B, B_sign, sum, sum_sign
                
                pValue = PyObject_CallFunctionObjArgs(pFunc, pA, A_sign, pB, B_sign, pMul, Mul_sign, NULL);     // 파이썬 mul_k 함수 실행 ( 매개 변수 여러 개 전달 ) 초기화 필요!
                if (!PyLong_AsLong(pValue)) {
                    printf("\nError");
                    // printf("sub sign : %d", sub->sign);
                    printf("\n");
                    // printf("A : 0x");  show_bigint_hex(A);
                    // printf("B : 0x");  show_bigint_hex(B);
                    
                    Py_DECREF(pValue);
                    Py_DECREF(Mul_sign);
                    Py_DECREF(pMul);
                    free(string_mul);
                    Py_DECREF(B_sign);
                    Py_DECREF(pB);
                    free(string_B);
                    Py_DECREF(A_sign);
                    Py_DECREF(pA);
                    free(string_A);

                    bigint_delete(&mul);
                    bigint_delete(&B);
                    bigint_delete(&A);
                    Py_Finalize();
                    return 0;
                }

                if (i % 1000 == 0) {
                    printf("=");
                }

                Py_DECREF(pValue);
                Py_DECREF(Mul_sign);
                Py_DECREF(pMul);
                free(string_mul);
                Py_DECREF(B_sign);
                Py_DECREF(pB);
                free(string_B);
                Py_DECREF(A_sign);
                Py_DECREF(pA);
                free(string_A);

                bigint_delete(&mul);
                bigint_delete(&B);
                bigint_delete(&A);
                
            }
            printf(" : Test Success \n");
        }
        else {  
            PyErr_Print();  // Python 함수 호출 실패시, 에러 출력    
        }
        Py_DECREF(pFunc);
        Py_DECREF(pModule);
        Py_DECREF(pName);
    }
    Py_Finalize();          // Python 인터프리터 초기화 실패시, 종료 

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
