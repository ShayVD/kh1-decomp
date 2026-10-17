#include "common.h"

typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V53;

static inline f32 w53_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void w53_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w53_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

void func_0011a978(s32, s32, V53 *);
void func_0011a9c8(s32, s32, V53 *);

s32 func_0011bfc8(s32 a0, s32 a1, void *p0, void *dir, void *out) {
    V53 n, p;
    f32 den, t;
    func_0011a978(a0, a1, &n);
    den = w53_dot(&n, dir);
    if (den >= 0.0f) return 0;
    func_0011a9c8(a0, a1, &p);
    t = (w53_dot(&n, &p) - w53_dot(&n, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w53_scale(out, dir, t);
    w53_add(out, out, p0);
    return 1;
}
