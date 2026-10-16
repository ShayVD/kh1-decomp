/* newlib libc/machine-independent isinf/isnan (fdlibm style). sdk segment. */
typedef int __int32_t;
typedef unsigned int __uint32_t;

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

int isinf(double x) {
    __int32_t hx, lx;
    EXTRACT_WORDS(hx, lx, x);
    hx &= 0x7fffffff;
    hx |= (__uint32_t) (lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int) ((__uint32_t) (hx | (-hx)) >> 31);
}

int isnan(double x) {
    __int32_t hx, lx;
    EXTRACT_WORDS(hx, lx, x);
    hx &= 0x7fffffff;
    hx |= (__uint32_t) (lx | (-lx)) >> 31;
    hx = 0x7ff00000 - hx;
    return (int) (((__uint32_t) (hx)) >> 31);
}
