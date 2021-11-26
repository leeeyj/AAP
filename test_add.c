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
        if (s1 != 0) sprintf(s1, "%08x", x->a[i]);
        if (s2 != 0 && s1 != 0) strcat(s2, s1);
        if (s1 != NULL) memset(s1, 0, sizeof(word) * 2 + 1);
    }
    free(s1);
    return s2;
}

int main()
{
    /*==================================================================================================================================*/
    // Setting Up Python for testing only

    PyObject* pName, * pModule, * pFunc, * pValue, *pA, *pB, *pSUM;
    Py_Initialize();                                                        
    if (Py_IsInitialized()) {                                              
        pName = PyUnicode_FromString("test1");                             
        pModule = PyImport_Import(pName);                                   
        pFunc = PyObject_GetAttrString(pModule, "add");                     
        if (PyCallable_Check(pFunc)) {                                      
            int count = 0;
            printf("Testing : ");
            for (int i = 1; i < 20; i++) {                             
                bigint* A = NULL;
                bigint_gen_rand(&A, NON_NEGATVE, 20);

                bigint* B = NULL;
                bigint_gen_rand(&B, NON_NEGATVE, 20);

                bigint* SUM = NULL;
                ADD(A, B, &SUM);

                unsigned char* string_A = array2string(A);
                pA = PyUnicode_FromString(string_A); 
                printf("A = %p \n", pA);

                unsigned char* string_B = array2string(B);
                pB = PyUnicode_FromString(string_B);
                printf("B = %p \n", pB);

                unsigned char* string_SUM = array2string(SUM);
                pSUM = PyUnicode_FromString(string_SUM);
                printf("SUM = %p \n \n", pSUM);

                pValue = PyObject_CallFunctionObjArgs(pFunc, pA, pB, pSUM, NULL);     
                if (!PyLong_AsLong(pValue)) {
                    printf("\nError");
                    printf("\n");
                    printf("A : ");  show_bigint_hex(A);
                    printf("B : ");  show_bigint_hex(B);
                    printf("SUM : ");  show_bigint_hex(SUM);

                    Py_DECREF(string_A);
                    Py_DECREF(string_B);
                    Py_DECREF(string_SUM);

                    Py_DECREF(pA);
                    Py_DECREF(pB);
                    Py_DECREF(pSUM);
                    Py_DECREF(pValue);

                    bigint_delete(&A);
                    bigint_delete(&B);
                    bigint_delete(&SUM);

                    free(string_A);
                    free(string_B);
                    free(string_SUM);

                    Py_Finalize();
                    return 0;
                }
                if (i % 1000 == 0) {
                    printf("=");
                }

                Py_DECREF(pA);
                Py_DECREF(pB);
                Py_DECREF(pSUM);
                Py_DECREF(pValue);

                bigint_delete(&A);
                bigint_delete(&B);
                bigint_delete(&SUM);

                free(string_A);
                free(string_B);
                free(string_SUM);

            }
            printf(" : Test Success \n");
        }
        else {
            PyErr_Print(); 
        }
        Py_DECREF(pName);
        Py_DECREF(pModule);
        Py_DECREF(pFunc);
    }
    Py_Finalize();         

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