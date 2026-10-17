/* gcc 2.9x config/fp-bit.c types, as the SDK's libgcc was built from it:
 * fp-bit.c compiled twice, with FLOAT defined (single precision, the
 * __*_f / __*sf* routines) and without (double, __*_d / __*df*). sdk segment;
 * see docs/sdk.md. */
#ifndef KH1_SDK_FP_BIT_H
#define KH1_SDK_FP_BIT_H

typedef float SFtype __attribute__((mode(SF)));
typedef float DFtype __attribute__((mode(DF)));
typedef int SItype __attribute__((mode(SI)));
typedef int DItype __attribute__((mode(DI)));
typedef unsigned int UHItype __attribute__((mode(HI)));
typedef unsigned int USItype __attribute__((mode(SI)));
typedef unsigned int UDItype __attribute__((mode(DI)));
typedef int CMPtype __attribute__((mode(SI)));

#define MAX_SI_INT ((SItype) ((unsigned) (~0) >> 1))
#define MAX_USI_INT ((USItype) ~0)
#define BITS_PER_SI (4 * 8)

#ifdef FLOAT
#define NGARDS 7L
#define GARDROUND 0x3f
#define GARDMASK 0x7f
#define GARDMSB 0x40
#define EXPBITS 8
#define EXPBIAS 127
#define FRACBITS 23
#define EXPMAX (0xff)
#define QUIET_NAN 0x100000L
#define FRAC_NBITS 32
#define FRACHIGH 0x80000000L
#define FRACHIGH2 0xc0000000L
typedef USItype fractype;
typedef UHItype halffractype;
typedef SFtype FLO_type;
typedef SItype intfrac;
#else
#define NGARDS 8L
#define GARDROUND 0x7f
#define GARDMASK 0xff
#define GARDMSB 0x80
#define EXPBITS 11
#define EXPBIAS 1023
#define FRACBITS 52
#define EXPMAX (0x7ff)
#define QUIET_NAN 0x8000000000000LL
#define FRAC_NBITS 64
#define FRACHIGH 0x8000000000000000LL
#define FRACHIGH2 0xc000000000000000LL
typedef UDItype fractype;
typedef USItype halffractype;
typedef DFtype FLO_type;
typedef DItype intfrac;
#endif

#define F_D_BITOFF (52 + 8 - (23 + 7))

#define NORMAL_EXPMIN (-(EXPBIAS) + 1)
#define IMPLICIT_1 ((fractype) 1 << (FRACBITS + NGARDS))
#define IMPLICIT_2 ((fractype) 1 << (FRACBITS + 1 + NGARDS))

typedef enum {
    CLASS_SNAN,
    CLASS_QNAN,
    CLASS_ZERO,
    CLASS_NUMBER,
    CLASS_INFINITY
} fp_class_type;

typedef struct {
    fp_class_type class;
    unsigned int sign;
    int normal_exp;
    union {
        fractype ll;
        halffractype l[2];
    } fraction;
} fp_number_type;

/* The SDK's fp-bit is the older bitfield version (FLOAT_BIT_ORDER_MISMATCH
 * layout for little endian), built without denormals and without rounding:
 * see __pack_d/__unpack_d in dp-bit.c. */
typedef union {
    FLO_type value;
    fractype value_raw;
#ifndef FLOAT
    halffractype words[2];
#endif
    struct {
        fractype fraction : FRACBITS __attribute__((packed));
        unsigned int exp : EXPBITS __attribute__((packed));
        unsigned int sign : 1 __attribute__((packed));
    } bits;
} FLO_union_type;

/* fp-bit.c's INLINE static predicates (functions, not macros: the
 * `if (iszero (&a))` tests compile to xori/beqz on the returned flag). */
static inline int isnan(fp_number_type *x) {
    return x->class == CLASS_SNAN || x->class == CLASS_QNAN;
}

static inline int isinf(fp_number_type *x) {
    return x->class == CLASS_INFINITY;
}

static inline int iszero(fp_number_type *x) {
    return x->class == CLASS_ZERO;
}

SFtype __make_fp(fp_class_type, unsigned int, int, USItype);
DFtype __make_dp(fp_class_type, unsigned int, int, UDItype);

#endif /* KH1_SDK_FP_BIT_H */
