# -*- coding: utf-8 -*-
import math

def add(a, b, s):
    bigint_a = int(a, 16) # a를 10진수 값으로 변환 
    bigint_b = int(b, 16) # b를 10진수 값으로 변환 
    bigint_sum = bigint_a + bigint_b # a와 b를 더하기 
    sum = hex(int(s, 16))
    if hex(bigint_sum) == sum: # 16진수 출력 값이 같은지 확인 
        return 1
    else:
        return 0
 
