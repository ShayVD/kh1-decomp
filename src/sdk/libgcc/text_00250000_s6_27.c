#include "common.h"
/* __muldf3, __divdf3 (fp-bit.c double, must NOT share a file with a __pack_d definition: callee-above effect) and __pack_f (single precision, own types below). */
#include "fp-bit.h"

FLO_type __pack_d(fp_number_type *);
void __unpack_d(FLO_union_type *, fp_number_type *);

extern const fp_number_type D_00492830;
#define __thenan_df D_00492830

static inline fp_number_type *nan(void) {
    return (fp_number_type *) (&__thenan_df);
}

static inline fp_number_type *_fpmul_parts(fp_number_type *a, fp_number_type *b, fp_number_type *tmp) {
    fractype low = 0;
    fractype high = 0;

    if (isnan(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isnan(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }
    if (isinf(a)) {
        if (iszero(b))
            return nan();
        a->sign = a->sign != b->sign;
        return a;
    }
    if (isinf(b)) {
        if (iszero(a))
            return nan();
        b->sign = a->sign != b->sign;
        return b;
    }
    if (iszero(a)) {
        a->sign = a->sign != b->sign;
        return a;
    }
    if (iszero(b)) {
        b->sign = a->sign != b->sign;
        return b;
    }

    /* No DImode multiply on the R5900: four 32x32 partial products. */
    {
        UDItype nl = a->fraction.ll & 0xffffffff;
        UDItype nh = a->fraction.ll >> 32;
        UDItype ml = b->fraction.ll & 0xffffffff;
        UDItype mh = b->fraction.ll >> 32;
        UDItype pp_ll = ml * nl;
        UDItype pp_hl = mh * nl;
        UDItype pp_lh = ml * nh;
        UDItype pp_hh = mh * nh;
        UDItype res2 = 0;
        UDItype res0 = 0;
        UDItype ps_hh__ = pp_hl + pp_lh;
        if (ps_hh__ < pp_hl)
            res2 += 0x100000000LL;
        pp_hl = ps_hh__ << BITS_PER_SI;
        res0 = pp_ll + pp_hl;
        if (res0 < pp_ll)
            res2++;
        res2 += ((ps_hh__ >> BITS_PER_SI) & 0xffffffff) + pp_hh;
        high = res2;
        low = res0;
    }

    tmp->normal_exp = a->normal_exp + b->normal_exp;
    tmp->sign = a->sign != b->sign;
    tmp->normal_exp += 4;
    while (high >= IMPLICIT_2) {
        tmp->normal_exp++;
        if (high & 1) {
            low >>= 1;
            low |= FRACHIGH;
        }
        high >>= 1;
    }
    while (high < IMPLICIT_1) {
        tmp->normal_exp--;

        high <<= 1;
        if (low & FRACHIGH)
            high |= 1;
        low <<= 1;
    }
    /* The SDK's fp-bit does no rounding here either. */
    tmp->fraction.ll = high;
    tmp->class = CLASS_NUMBER;
    return tmp;
}

FLO_type __muldf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type tmp;
    fp_number_type *res;
    FLO_union_type au, bu;

    au.value = arg_a;
    bu.value = arg_b;

    __unpack_d(&au, &a);
    __unpack_d(&bu, &b);

    res = _fpmul_parts(&a, &b, &tmp);

    return __pack_d(res);
}

static inline fp_number_type *_fpdiv_parts(fp_number_type *a, fp_number_type *b) {
    fractype bit;
    fractype numerator;
    fractype denominator;
    fractype quotient;

    if (isnan(a)) {
        return a;
    }
    if (isnan(b)) {
        return b;
    }

    a->sign = a->sign ^ b->sign;

    if (isinf(a) || iszero(a)) {
        if (a->class == b->class)
            return nan();
        return a;
    }

    if (isinf(b)) {
        a->fraction.ll = 0;
        a->normal_exp = 0;
        return a;
    }
    if (iszero(b)) {
        a->class = CLASS_INFINITY;
        return a;
    }

    {
        a->normal_exp = a->normal_exp - b->normal_exp;
        numerator = a->fraction.ll;
        denominator = b->fraction.ll;

        if (numerator < denominator) {
            /* Fraction will be less than 1.0 */
            numerator *= 2;
            a->normal_exp--;
        }
        bit = IMPLICIT_1;
        quotient = 0;
        while (bit) {
            if (numerator >= denominator) {
                quotient |= bit;
                numerator -= denominator;
            }
            bit >>= 1;
            numerator *= 2;
        }

        /* No rounding in the SDK's fp-bit. */
        a->fraction.ll = quotient;
        return (a);
    }
}

FLO_type __divdf3(FLO_type arg_a, FLO_type arg_b) {
    fp_number_type a;
    fp_number_type b;
    fp_number_type *res;
    FLO_union_type au, bu;

    au.value = arg_a;
    bu.value = arg_b;

    __unpack_d(&au, &a);
    __unpack_d(&bu, &b);

    res = _fpdiv_parts(&a, &b);

    return __pack_d(res);
}

/* __pack_f: fp-bit.c built with FLOAT (single precision); the shared fp-bit.h
 * is included for double above, so the float types are spelled out here. */
typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union {
        USItype ll;
        UHItype l[2];
    } fraction;
} sf_fp_number_type;

typedef union {
    SFtype value;
    USItype value_raw;
    struct {
        USItype fraction : 23 __attribute__((packed));
        unsigned int exp : 8 __attribute__((packed));
        unsigned int sign : 1 __attribute__((packed));
    } bits;
} sf_FLO_union_type;

static inline int sf_iszero(sf_fp_number_type *x) {
    return x->class == CLASS_ZERO;
}

SFtype __pack_f(sf_fp_number_type *src) {
    sf_FLO_union_type dst;
    USItype fraction = src->fraction.ll;
    int sign = src->sign;
    int exp = 0;

    if (sf_iszero(src)) {
        fraction = 0;
    } else if (fraction == 0) {
        exp = 0;
    } else {
        if (src->normal_exp < (-127 + 1)) {
            fraction = 0;
        } else if (!(src->normal_exp <= 127 + 1)) {
            exp = 0xff;
            fraction = 0;
        } else {
            if (src->normal_exp == 127 + 1 && (SItype) fraction < 0) {
                exp = 0xff;
                fraction = 0;
            } else {
                exp = src->normal_exp + 127;
                fraction >>= 7L;
            }
        }
    }

    dst.bits.fraction = fraction;
    dst.bits.exp = exp;
    dst.bits.sign = sign;
    return dst.value;
}

