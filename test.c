#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./freeCize.h"
#include "./includePython.h"

unsigned char* array2string(bigint* x)
{
    unsigned char* s1 = (unsigned char*)malloc(sizeof(word) * 2 + 1);
    unsigned char* s2 = (unsigned char*)malloc(sizeof(word) * 2 * (x->wordlen) + 1);
    if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    if (s2 != NULL) memset(s2, 0, sizeof(word) * 2 * (x->wordlen) + 1);

    for (int i = (x->wordlen) - 1; i >= 0; i--) {
        sprintf(s1, "%08x", x->a[i]);
        strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
}

int main()
{   
    /*=========================================================================================================================================================*/
    // Setting Up Python for testing only
   
    PyObject *pName, *pModule, *pFunc, *pValue, *pArg1, *pArg2;
    Py_Initialize();                                                        // Python 인터프리터 초기화 
    if (Py_IsInitialized()) {                                               // Python 인터프리터 초기화 확인 
        pName = PyUnicode_FromString("test1");                              // Python File name -> test1.py, 초기화 필요! 
        pModule = PyImport_Import(pName);                                   // Import Python File            초기화 필요!
        pFunc = PyObject_GetAttrString(pModule, "sqr");                   // test1.py에 있는 add 함수 (= 함수 이름)  초기화 필요!
        if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
            int count = 0;
            printf("Testing : ");
            for (int i = 1; i < 100001; i++) {                               // 100000번 테스트
                bigint* A = NULL; 
                bigint_gen_rand(&A, NON_NEGATVE, 20);
                bigint* B = NULL;              
                Sqr_karatsuba(A, &B);
                // bigint* mul = NULL;
                // MUL_AB(A, B, &mul);
 
                unsigned char* string_A = array2string(A);
                pArg1 = PyUnicode_FromString(string_A);                     // 매개 변수 생성, c언어 문자열을 파이썬 문자열로 변환 

                unsigned char* string_B = array2string(B);
                pArg2 = PyUnicode_FromString(string_B);

                // unsigned char* string_Q = array2string(Q);
                // pArg3 = PyUnicode_FromString(string_Q);
                
                // unsigned char* string_R = array2string(R);
                // pArg4 = PyUnicode_FromString(string_R);
                // Py_DECREF -> 메모리 누수 방지 
                // printf("\nA : %s", string_A);
                // printf("\nB : %s", string_B);
                // printf("\nmul : %s", string_mul);

                pValue = PyObject_CallFunctionObjArgs(pFunc, pArg1, pArg2, NULL);     // 파이썬 mul_k 함수 실행 ( 매개 변수 여러 개 전달 ) 초기화 필요!
                // printf("%d", PyLong_AsLong(pValue));                                      // 인자가 더 이상 없다면 마지막에 NULL 
                // printf("%d", PyLong_AsLong(pValue));
                if (!PyLong_AsLong(pValue)) {
                    printf("\nError");
                    printf("\n");
                    printf("A : ");  show_bigint_hex(A);
                    printf("B : 0x");  show_bigint_hex(B);
                    // printf("Q : ");  show_bigint_hex(Q);
                    // printf("R : ");  show_bigint_hex(R);

                    Py_DECREF(string_A);
                    Py_DECREF(string_B);
                    // Py_DECREF(string_Q);
                    // Py_DECREF(string_R);


                    Py_DECREF(pArg1);
                    Py_DECREF(pArg2);
                    // Py_DECREF(pArg3);
                    // Py_DECREF(pArg4);
                    Py_DECREF(pValue);

                    bigint_delete(&A);
                    bigint_delete(&B);
                    // bigint_delete(&Q);
                    // bigint_delete(&R);

                    free(string_A);
                    free(string_B);
                    // free(string_Q);
                    // free(string_R);

                    Py_Finalize();
                    return 0;
                }
                if (i % 1000 == 0) {
                    printf("=");
                }

                Py_DECREF(pArg1);
                Py_DECREF(pArg2);
                // Py_DECREF(pArg3);
                // Py_DECREF(pArg4);
                Py_DECREF(pValue);

                bigint_delete(&A);
                bigint_delete(&B);
                // bigint_delete(&Q);
                // bigint_delete(&R);

                free(string_A);
                free(string_B);
                // free(string_Q);
                // free(string_R);

            }
            printf(" : Test Success \n");
        }
        else {  
            PyErr_Print();  // Python 함수 호출 실패시, 에러 출력    
        }
        Py_DECREF(pName);
        Py_DECREF(pModule);
        Py_DECREF(pFunc);
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
