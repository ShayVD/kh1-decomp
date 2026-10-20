#include "common.h"
typedef f32 V4[4] __attribute__((aligned(16)));
typedef int u128 __attribute__((mode(TI)));

static inline void vsubv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}
static inline void vaddv(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
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
static inline f32 vdist2(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
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
static inline void vcopy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}
extern s32 D_002BD150[];
extern s32 D_002BD160[];
extern V4 D_002C12E0;
s32 func_00104ae0(s32, V4 *);
s32 func_0011aa18(s32, s32, V4 *);
s32 func_001197e0(f32 *, f32 *, f32 *);

s32 func_00119ad8(s32 a0, s32 a1, f32 *n, f32 *p, f32 *out, f32 *maxd) {
    V4 d, e0, e1, w;
    V4 pts[4];
    V4 hits[4];
    f32 t;
    s32 nhit;
    s32 cnt, i, best, bk;
    s32 *idx;
    f32 r2, dd, min, m1;
    f32 *src;
    r2 = *maxd * *maxd;
    nhit = 0;
    if (a0 == -1) cnt = func_00104ae0(a1, pts);
    else cnt = func_0011aa18(a0, a1, pts);
    if (cnt == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < cnt; i++) {
        vcopy(e0, pts[i]);
        vcopy(e1, pts[idx[i]]);
        vsubv(d, e1, pts[i]);
        vsubv(w, e0, p);
        t = -(vdot(w, d) / vdot(d, d));
        vscale(d, d, t);
        vaddv(out, d, e0);
        if (vdist2(p, out) <= r2) {
            vaddv(e1, e1, D_002C12E0);
            vaddv(e0, e0, D_002C12E0);
            if (!func_001197e0(e1, e0, out)) {
                vcopy(hits[nhit++], out);
            }
        }
    }
    if (nhit) {
        best = 0;
        m1 = 1.0e12f;
        for (i = 0; i < nhit; i++) {
            vsubv(out, p, hits[i]);
            dd = vdot(out, out);
            if (dd < m1) { m1 = dd; best = i; }
        }
        vcopy(out, hits[best]);
        return 1;
    } else {
        bk = cnt;
        min = r2;
        for (i = 0; i < cnt; i++) {
            dd = vdist2(p, pts[i]);
            if (dd <= min) { min = dd; bk = i; }
        }
        if (cnt != bk) {
            vcopy(out, pts[bk]);
            return 1;
        }
    }
    return 0;
}
#include "data/data_002B.h"
