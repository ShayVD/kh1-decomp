/* Minimal fdlibm/newlib internals for the libm in SLPS_251.98 (newlib's
 * libm, built with ee-gcc 2.96 -O2 -G0; docs/sdk.md). The EE build defines
 * _FLT_LARGEST_EXPONENT_IS_NORMAL and _FLT_NO_DENORMALS: no NaN/Inf tests
 * on floats, and tiny values count as zero.
 *
 * Not ported: the Vita build uses its own libm. */
#ifndef KH1_SDK_FDLIBM_H
#define KH1_SDK_FDLIBM_H

typedef int __int32_t;
typedef unsigned int __uint32_t;

typedef union {
    float value;
    __uint32_t word;
} ieee_float_shape_type;

#define GET_FLOAT_WORD(i, d)            \
    do {                                \
        ieee_float_shape_type gf_u;     \
        gf_u.value = (d);               \
        (i) = gf_u.word;                \
    } while (0)

#define SET_FLOAT_WORD(d, i)            \
    do {                                \
        ieee_float_shape_type sf_u;     \
        sf_u.word = (i);                \
        (d) = sf_u.value;               \
    } while (0)

typedef union {
    double value;
    struct {
        __uint32_t lsw;
        __uint32_t msw;
    } parts;
} ieee_double_shape_type;

#define EXTRACT_WORDS(ix0, ix1, d)      \
    do {                                \
        ieee_double_shape_type ew_u;    \
        ew_u.value = (d);               \
        (ix0) = ew_u.parts.msw;         \
        (ix1) = ew_u.parts.lsw;         \
    } while (0)

#define GET_HIGH_WORD(i, d)             \
    do {                                \
        ieee_double_shape_type gh_u;    \
        gh_u.value = (d);               \
        (i) = gh_u.parts.msw;           \
    } while (0)

#define SET_HIGH_WORD(d, v)             \
    do {                                \
        ieee_double_shape_type sh_u;    \
        sh_u.value = (d);               \
        sh_u.parts.msw = (v);           \
        (d) = sh_u.value;               \
    } while (0)

#define INSERT_WORDS(d, ix0, ix1)       \
    do {                                \
        ieee_double_shape_type iw_u;    \
        iw_u.parts.msw = (ix0);         \
        iw_u.parts.lsw = (ix1);         \
        (d) = iw_u.value;               \
    } while (0)

/* _FLT_LARGEST_EXPONENT_IS_NORMAL, _FLT_NO_DENORMALS */
#define FLT_UWORD_IS_FINITE(x) 1
#define FLT_UWORD_IS_ZERO(x) ((x) < 0x00800000L)
#define FLT_UWORD_IS_SUBNORMAL(x) 0

float __ieee754_sqrtf(float);
float __ieee754_acosf(float);
float __ieee754_asinf(float);
float __ieee754_atan2f(float, float);
float __ieee754_fmodf(float, float);
float __ieee754_powf(float, float);
__int32_t __ieee754_rem_pio2f(float, float *);
float __kernel_sinf(float, float, int);
float __kernel_cosf(float, float);
float __kernel_tanf(float, float, int);
double __ieee754_sqrt(double);
double __ieee754_asin(double);
double __ieee754_atan2(double, double);

#endif /* KH1_SDK_FDLIBM_H */
