/* __muldf3 (0x00263010) and __divdf3 (0x00263298), sdk segment: gcc
 * fp-bit.c _fpmul_parts/_fpdiv_parts inlined into their wrappers, as the SDK
 * built them (no rounding; four __muldi3 partial products for the multiply).
 * Like __pack_f, each differs only in branch-likely choice: the original
 * fills one (__muldf3) or two (__divdf3) delay slots from the branch target
 * as bnezl where ee-gcc 2.96 emits a plain bnez with the same slot insn.
 * No flag (-g, -fexceptions, -fno-thread-jumps, other ee-gcc builds) moves
 * it. Paste back into src/sdk/libgcc/dp-bit.c before __cmpdf2 once found. */
#include "../src/sdk/libgcc/fp-bit.h"

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
