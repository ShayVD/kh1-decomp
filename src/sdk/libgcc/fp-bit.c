/* gcc 2.9x config/fp-bit.c, single precision (libgcc's fp-bit.c). sdk segment. */
#define FLOAT
#include "fp-bit.h"

FLO_type __pack_f(fp_number_type *);
void __unpack_f(FLO_union_type *, fp_number_type *);

void __unpack_f(FLO_union_type *src, fp_number_type *dst) {
    fractype fraction = src->bits.fraction;
    int exp = src->bits.exp;
    int sign = src->bits.sign;

    dst->sign = sign;
    if (exp == 0) {
        dst->class = CLASS_ZERO;
    } else {
        dst->normal_exp = exp - EXPBIAS;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}

SFtype __make_fp(fp_class_type class, unsigned int sign, int exp, USItype frac) {
    fp_number_type in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return __pack_f(&in);
}

DFtype __extendsfdf2(SFtype arg_a) {
    fp_number_type in;
    FLO_union_type au;

    au.value = arg_a;
    __unpack_f(&au, &in);

    return __make_dp(in.class, in.sign, in.normal_exp, ((UDItype) in.fraction.ll) << F_D_BITOFF);
}
