#include "./freeCize_core.h"

// Bigint Addition
int ADD_ABC(word* x, word* y, int* c, word* C);             // Addition of Same signed Two Word
bigint* ADDC(bigint* x, bigint* y);                         // Addition of Same Signed Two Integers
bigint* ADD(bigint* x, bigint* y);                                                   // Addition of Two Integers

// Bigint Subtraction
void SUB_AbB(word* A, word* B, int* b, word* C);
bigint* SUBC(bigint* A, bigint* B);
bigint* SUB(bigint* x, bigint* y);