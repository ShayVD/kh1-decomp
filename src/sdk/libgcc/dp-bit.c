/* gcc 2.9x config/fp-bit.c, double precision (libgcc's dp-bit.c). sdk segment. */
#include "fp-bit.h"

FLO_type __pack_d(fp_number_type *);
void __unpack_d(FLO_union_type *, fp_number_type *);

/* fp-bit.c's `extern const fp_number_type __thenan_df` ({CLASS_SNAN, ...}). */
extern const fp_number_type D_00492830;
#define __thenan_df D_00492830

static inline fp_number_type *nan(void) {
    return (fp_number_type *) (&__thenan_df);
}

#define LSHIFT(a) { a = (a & 1) | (a >> 1); }

FLO_type __pack_d(fp_number_type *src) {
    FLO_union_type dst;
    fractype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (isnan(src)) {
        exp = EXPMAX;
        fraction |= QUIET_NAN;
    } else if (isinf(src)) {
        exp = EXPMAX;
        fraction = 0;
    } else if (iszero(src)) {
        exp = 0;
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        /* No denormals and no rounding: too small is zero, too big is
         * infinity, everything else is truncated. */
        if (src->normal_exp < NORMAL_EXPMIN) {
            exp = 0;
            fraction = 0;
        } else if (src->normal_exp > EXPBIAS) {
            exp = EXPMAX;
            fraction = 0;
        } else {
            exp = src->normal_exp + EXPBIAS;
            fraction >>= NGARDS;
        }
    }

    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

void __unpack_d(FLO_union_type *src, fp_number_type *dst) {
    fractype fraction = src->bits.fraction;
    int exp = src->bits.exp;
    int sign = src->bits.sign;

    dst->sign = sign;
    if (exp == 0) {
        /* No denormals: a zero exponent is zero. */
        dst->class = CLASS_ZERO;
    } else if (exp == EXPMAX) {
        dst->normal_exp = EXPBIAS;
        if (fraction == 0) {
            dst->class = CLASS_INFINITY;
            dst->fraction.ll = IMPLICIT_1;
        } else {
            if (fraction & QUIET_NAN) {
                dst->class = CLASS_QNAN;
            } else {
                dst->class = CLASS_SNAN;
            }
            dst->fraction.ll = fraction;
        }
    } else {
        dst->normal_exp = exp - EXPBIAS;
        dst->class = CLASS_NUMBER;
        dst->fraction.ll = (fraction << NGARDS) | IMPLICIT_1;
    }
}

fp_number_type *_fpadd_parts(fp_number_type *a, fp_number_type *b, fp_number_type *tmp) {
    intfrac tfraction;
    int a_normal_exp;
    int b_normal_exp;
    fractype a_fraction;
    fractype b_fraction;

    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }
    if (isinf(a)) {
        if (isinf(b) && a->sign != b->sign) {
            return nan();
        }
        return a;
    }
    if (isinf(b)) {
        return b;
    }
    if (iszero(b)) {
        if (iszero(a)) {
            *tmp = *a;
            tmp->sign = a->sign & b->sign;
            return tmp;
        }
        return a;
    }
    if (iszero(a)) {
        return b;
    }

    {
        int diff;

        a_normal_exp = a->normal_exp;
        b_normal_exp = b->normal_exp;
        a_fraction = a->fraction.ll;
        b_fraction = b->fraction.ll;

        diff = a_normal_exp - b_normal_exp;

        if (diff < 0) {
            diff = -diff;
        }
        if (diff < FRAC_NBITS) {
            while (a_normal_exp > b_normal_exp) {
                b_normal_exp++;
                LSHIFT(b_fraction);
            }
            while (b_normal_exp > a_normal_exp) {
                a_normal_exp++;
                LSHIFT(a_fraction);
            }
        } else {
            if (a_normal_exp > b_normal_exp) {
                b_normal_exp = a_normal_exp;
                b_fraction = 0;
            } else {
                a_normal_exp = b_normal_exp;
                a_fraction = 0;
            }
        }
    }

    if (a->sign != b->sign) {
        if (a->sign) {
            tfraction = -a_fraction + b_fraction;
        } else {
            tfraction = a_fraction - b_fraction;
        }
        if (tfraction >= 0) {
            tmp->sign = 0;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = tfraction;
        } else {
            tmp->sign = 1;
            tmp->normal_exp = a_normal_exp;
            tmp->fraction.ll = -tfraction;
        }

        while (tmp->fraction.ll < IMPLICIT_1 && tmp->fraction.ll) {
            tmp->fraction.ll <<= 1;
            tmp->normal_exp--;
        }
    } else {
        tmp->sign = a->sign;
        tmp->normal_exp = a_normal_exp;
        tmp->fraction.ll = a_fraction + b_fraction;
    }
    tmp->class = CLASS_NUMBER;

    if (tmp->fraction.ll >= IMPLICIT_2) {
        LSHIFT(tmp->fraction.ll);
        tmp->normal_exp++;
    }
    return tmp;
}

int __fpcmp_parts_d(fp_number_type *a, fp_number_type *b) {
    if (isnan(a) || isnan(b)) {
        return 1;
    }
    if (isinf(a) && isinf(b)) {
        return b->sign - a->sign;
    }
    if (isinf(a)) {
        return a->sign ? -1 : 1;
    }
    if (isinf(b)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(a) && iszero(b)) {
        return 0;
    }
    if (iszero(a)) {
        return b->sign ? 1 : -1;
    }
    if (iszero(b)) {
        return a->sign ? -1 : 1;
    }
    if (a->sign != b->sign) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp > b->normal_exp) {
        return a->sign ? -1 : 1;
    }
    if (a->normal_exp < b->normal_exp) {
        return a->sign ? 1 : -1;
    }
    if (a->fraction.ll > b->fraction.ll) {
        return a->sign ? -1 : 1;
    }
    if (a->fraction.ll < b->fraction.ll) {
        return a->sign ? 1 : -1;
    }
    return 0;
}

FLO_type __adddf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    FLO_union_type au, bu;

    au.value = arg_a;
    bu.value = arg_b;

    __unpack_d(&au, &a);
    __unpack_d(&bu, &b);

    res = _fpadd_parts(&a, &b, &tmp);

    return __pack_d(res);
}

FLO_type __subdf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    FLO_union_type au, bu;

    au.value = arg_a;
    bu.value = arg_b;

    __unpack_d(&au, &a);
    __unpack_d(&bu, &b);

    b.sign ^= 1;

    res = _fpadd_parts(&a, &b, &tmp);

    return __pack_d(res);
}

CMPtype __cmpdf2(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    FLO_union_type au, bu;

    au.value = arg_a;
    bu.value = arg_b;

    __unpack_d(&au, &a);
    __unpack_d(&bu, &b);

    return __fpcmp_parts_d(&a, &b);
}

FLO_type __floatsidf(SItype arg_a) {
    fp_number_type in;

    in.class = CLASS_NUMBER;
    in.sign = arg_a < 0;
    if (!arg_a) {
        in.class = CLASS_ZERO;
    } else {
        in.normal_exp = FRACBITS + NGARDS;
        if (in.sign) {
            if (arg_a == (-MAX_SI_INT - 1)) {
                return (FLO_type) (-MAX_SI_INT - 1);
            }
            in.fraction.ll = (-arg_a);
        } else {
            in.fraction.ll = arg_a;
        }

        while (in.fraction.ll < ((fractype) 1 << (FRACBITS + NGARDS))) {
            in.fraction.ll <<= 1;
            in.normal_exp -= 1;
        }
    }
    return __pack_d(&in);
}

SItype __fixdfsi(FLO_type arg_a) {
    fp_number_type a;
    SItype tmp;
    FLO_union_type au;

    au.value = arg_a;
    __unpack_d(&au, &a);

    if (iszero(&a)) {
        return 0;
    }
    if (isnan(&a)) {
        return 0;
    }
    if (isinf(&a)) {
        return a.sign ? (-MAX_SI_INT) - 1 : MAX_SI_INT;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > BITS_PER_SI - 2) {
        return a.sign ? (-MAX_SI_INT) - 1 : MAX_SI_INT;
    }
    tmp = a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
    return a.sign ? (-tmp) : (tmp);
}

DFtype __make_dp(fp_class_type class, unsigned int sign, int exp, UDItype frac) {
    fp_number_type in;

    in.class = class;
    in.sign = sign;
    in.normal_exp = exp;
    in.fraction.ll = frac;
    return __pack_d(&in);
}

SFtype __truncdfsf2(DFtype arg_a) {
    fp_number_type in;
    USItype sffrac;
    FLO_union_type au;

    au.value = arg_a;
    __unpack_d(&au, &in);

    sffrac = in.fraction.ll >> F_D_BITOFF;

    if ((in.fraction.ll & (((USItype) 1 << F_D_BITOFF) - 1)) != 0) {
        sffrac |= 1;
    }

    return __make_fp(in.class, in.sign, in.normal_exp, sffrac);
}

USItype __fixunsdfsi(FLO_type arg_a) {
    fp_number_type a;
    FLO_union_type au;

    au.value = arg_a;
    __unpack_d(&au, &a);

    if (iszero(&a)) {
        return 0;
    }
    if (isnan(&a)) {
        return 0;
    }
    if (a.sign) {
        return 0;
    }
    if (isinf(&a)) {
        return MAX_USI_INT;
    }
    if (a.normal_exp < 0) {
        return 0;
    }
    if (a.normal_exp > BITS_PER_SI - 1) {
        return MAX_USI_INT;
    } else if (a.normal_exp > (FRACBITS + NGARDS)) {
        return a.fraction.ll << (a.normal_exp - (FRACBITS + NGARDS));
    } else {
        return a.fraction.ll >> ((FRACBITS + NGARDS) - a.normal_exp);
    }
}
