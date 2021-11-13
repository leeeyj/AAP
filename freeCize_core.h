#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WordBitLen 32
#define NON_NEGATVE 0
#define NEGATIVE 1
typedef char byte;

#if WordBitLen == 8
typedef unsigned char word;
#elif WordBitLen == 32
typedef unsigned int word;
#elif WordBitLen == 64;
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
void array_copy(word* A, word* T, int wordlen);                             // Copy word array
void bigint_set_by_array(bigint** x, int sign, word* t, int wordlen);       // bigint setting by word array
void bigint_set_by_string(bigint** x, int sign, char* str, int base);       // bigint setting by string

// print bigint
void show_bigint_hex(bigint* x);                // show bigint to hex
void show_bigint_dec(bigint* x);                // show bigint to decimal
void show_bigint_bin(bigint* x);                // show bigint to binary

// refine bigint, use realloc
void bigint_refine(bigint* x);                  // bigint memory reallocation 

// generate random bigint
void bigint_gen_rand(bigint** x, int sign, int wordlen);                // Generate Random bigint
void array_rand(word* dst, int wordlen);                                // Generate Random word array
// Only for Testing generate random bigint
void bigint_gen_rand1(bigint** x, int sign, int wordlen);
void array_rand1(word* dst, int wordlen);

// Assign Bigint 
void bigint_assign(bigint** y, bigint* x);          // Assign bigint ( y <- x )

// Set One, Set Zero
void bigint_set_one(bigint** x);                // ???
void bigint_set_zero(bigint** x);               // ???

// IsZero? IsOne?
bool IsZero(bigint* x);                 // ???
bool IsOne(bigint* x);                  // ???

// Compare Two Bigint
int CompareABS(bigint* x, bigint* y);           // Compare Absolute two integer 
int Compare(bigint* x, bigint* y);              // Compare two integer
                                                /* 
                                                    Compare(A, B) {
                                                        return 1 : A > B
                                                        return 0 : A = B
                                                        return -1 : A < B    
                                                    }
                                                */

// Left/Right shift Bigint 
void LeftShift(bigint* A, int r);
void RightShift(bigint* A, int r); 

// Reduction : A mod 2 ^ r
void Reduction(bigint* A, int r);