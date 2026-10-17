/* func_00119a20 and func_00119ef8 only match with their callee func_001198c8
 * defined above them. */
#include "common.h"
typedef f32 V4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));

extern s32 D_002BD150[];
extern s32 D_002BD160[];
extern u128 D_002C12F0;
s32 func_00104ae0(s32, V4 *);
s32 func_0011aa18(s32, s32, V4 *);

static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void vcross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline f32 vdot(f32 *a, f32 *b) {
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

static inline void vcopy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}

s32 func_001198c8(s32 a0, s32 a1, f32 *p) {
    V4 c, n;
    V4 pts[4];
    s32 i, cnt;
    s32 *idx;
    if (a0 == -1) cnt = func_00104ae0(a1, pts);
    else cnt = func_0011aa18(a0, a1, pts);
    if (cnt == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < cnt; i++) vsubv(pts[i], pts[i], p);
    vcopy(n, &D_002C12F0);
    for (i = 0; i < cnt; i++) {
        vcross(c, pts[i], pts[idx[i]]);
        if (vdot(n, c) < 0.0f) return 0;
        vcopy(n, c);
    }
    return 1;
}

static inline void vscale(f32 *d, f32 *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyzw $vf6xyzw, $vf4xyzw, $vf5x\n"
        "sqc2 $vf6, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

typedef struct { f32 n[3]; f32 d; s32 x10; } Plane;
extern Plane *D_002A6238;

s32 func_00119a20(s32 i, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 t;
    f32 d;
    d = vdot(p, n) + D_002A6238[i].d;
    if (*maxd < d) return 0;
    if (d < 0.0f) return 0;
    vscale(t, n, d);
    vsubv(out, p, t);
    return func_001198c8(-1, i, out) != 0;
}

f32 func_00119e80(s32, s32, f32 *, f32 *);

s32 func_00119ef8(s32 a0, s32 a1, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 t;
    f32 d;
    d = func_00119e80(a0, a1, n, p);
    if (*maxd < d) return 0;
    if (d < 0.0f) return 0;
    vscale(t, n, d);
    vsubv(out, p, t);
    return func_001198c8(a0, a1, out) != 0;
}
