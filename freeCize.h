#include "./freeCize_core.h"

// Bigint Addition
void ADD_ABC(word* x, word* y, int* c, word* C);             // Addition of Same signed Two Word
void ADDC(bigint* x, bigint* y, bigint** z);                // Addition of Same Signed Two Integers
void ADD(bigint* x, bigint* y, bigint** z);                                                   // Addition of Two Integers

// Bigint Subtraction
void SUB_AbB(word* A, word* B, int* b, word* C);
void SUBC(bigint* A, bigint* B, bigint** z);
void SUB(bigint* x, bigint* y, bigint** z);

// Bigint Multiplication 
void MUL_AB(word* x, word* y, bigint** z);                  // Single word Multiplication
void MULC_Naive(bigint* x, bigint* y, bigint** z);          // Multiplication Naive Version 
void MULC_Karatsuba(bigint* x, bigint* y, bigint** z);      // Fast Multiplication Algorithm
