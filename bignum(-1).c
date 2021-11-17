#include "파이썬 헤더파일" //헤더파일을 직접 만들어서 추가하는 부분
#include <Python.h> //위 작업을 하면 아래가 필요가 없나? or <Python.h>를 넣으면 위의 작업이 필요가 없나 or 둘다 필요한가?
#include <stdio.h>

int main()
{
    //pyObject는 c언어에서 쓰는 int,double,char..etc를 한번에 선언을 하는 과정인듯 하다
 PyObject *module; //밑에 있는 moudle을 표현하는 과정
 PyObject *func; //함수포인터변수를 선언
 PyObject *ret; //함수포인터변수로 함수를 호출하기 위해 선언? 그러려면 ret앞에 *이 빠져야하지 않나?

 int i_ret; //이게 파이썬으로 돌린 큰수 연산의 결과값으로 출력된다
 
 Py_Initialize(); //파이썬의 전역을 초기화 하는 부분

 module = PyImport_ImportModule("example"); //파이썬 형식으로 작성된 example.py을 "로드"하는 부분
//  func = PyObject_GetAttrString(module,"add");  /PyObject_GetAttrString로 파이썬에서 add 함수를 "로드"
 
 ret = PyObject_CallObject(func,Py_BuildValue("(ii)", 1,2));//PyObject_CallObject로 파이썬에 만들어놓은 add 함수 "호출"
 PyArg_Parse(ret,"i",&i_ret); //PyArg_Parse로 파이썬에서 계산된 결과값을 호출 받는다
 printf("결과 : %d\n", i_ret); //출력
 Py_DECREF(ret); //이부분은 뭔지 잘 모르겠다

 Py_Finalize(); //전역초기화를 종료하는 곳

 return 0;
}
