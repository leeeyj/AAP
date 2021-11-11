#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./freeCize.h"
#include "./includePython.h"

int main()
{     
    bigint* A = NULL;
    bigint* B = NULL;

    bigint_gen_rand(&A, NON_NEGATVE, 2);
    bigint_gen_rand1(&B, NON_NEGATVE, 2);

    show_bigint_hex(A);
    show_bigint_hex(B);
    printf("\n");
    
    bigint* sum;
    sum = ADDC(A, B);
    show_bigint_hex(sum);

    bigint_delete(&A);
    bigint_delete(&B);
    bigint_delete(&sum);

    
    // Setting Up Python for testing only
    // int ret;
    PyObject *pName, *pModule, *pFunc, *pValue, *pArg;
    Py_Initialize();
    if (Py_IsInitialized()) {
        pName = PyUnicode_FromString("test1");                              // Python File name -> test1.py 
        pModule = PyImport_Import(pName);                                   // Import Python File
        pFunc = PyObject_GetAttrString(pModule, "test_func");               // test1.py에 있는 test_func (함수 이름)
        pArg = Py_BuildValue("II", 1, 2);                                 // 매개변수 설정
        if (PyCallable_Check(pFunc)) {                                      // 함수가 잘 불러져 왔는지 확인
            pValue = PyObject_CallObject(pFunc, pArg);                      // 파이썬 test_func 함수 실행 
        }
        else {                                                               
            PyErr_Print();                                                  // 에러 출력
        }
        
        // pValue = PyObject_CallObject(pFunc, NULL);
    }
    Py_Finalize();                                                          // 초기화
    
    return 0;
}
