#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size_of_word 4

#if size_of_word == 1
typedef unsigned char word;
#elif size_of_word == 4
typedef unsigned int word;
#elif size_of_word == 8;
typedef unsigned long long word;
#endif

// typedef unsigned int word;
// typedef unsigned char word;
// typedef unsigned long long word;

// BigInt struct
typedef struct{
    int sign;           // Negative or Positive
    int wordlen;        // word length
    word* a;            // address for big integer
}bigint;

// generate bigint
void bigint_create(bigint** x, int wordlen);        // bigint dynamic memory allocation
void bigint_delete(bigint** x);                     // bigint free memory 

// bigint setting 
void array_copy(word* A, word* T, int wordlen);
void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen);
void bigint_set_by_string(bigint** x, int sign, char* str, int base);

// print bigint
void show_bigint_hex(bigint* x);

// refine bigint, use realloc
void bigint_refine(bigint* x);

// generate random bigint
void bigint_gen_rand();
