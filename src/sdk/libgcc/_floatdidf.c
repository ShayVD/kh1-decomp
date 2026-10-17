/* libgcc2.c, L_floatdidf. sdk segment. */
#include "libgcc2.h"

typedef float DFtype __attribute__((mode(DF)));

#define WORD_SIZE (sizeof(SItype) * 8)
#define HIGH_HALFWORD_COEFF (((UDItype) 1) << (WORD_SIZE / 2))
#define HIGH_WORD_COEFF (((UDItype) 1) << WORD_SIZE)

DFtype __floatdidf(DItype u) {
    DFtype d;

    d = (SItype) (u >> WORD_SIZE);
    d *= HIGH_HALFWORD_COEFF;
    d *= HIGH_HALFWORD_COEFF;
    d += (USItype) (u & (HIGH_WORD_COEFF - 1));

    return d;
}
