#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define word unsigned int
// #define word unsigned char 
// #define word unsigned long long
// typedef unsigned int word;
typedef struct{
    int sign;           // Negative or Positive
    int wordlen;        // word length
    word* a;            // address for big integer
}bigint;

// generate bigint
void bigint_create(bigint** x, int wordlen);        // bigint dynamic memory allocation
void bigint_delete(bigint** x);                     // bigint free memory 

// bigint setting 
void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen);
void bigint_set_by_string(bigint** x, int sign, char* str, int base);

// print bigint
void show_bigint_hex(bigint *x);

// refine bigint, use realloc
void bigint_refine();

// generate random bigint
void bigint_gen_rand();
