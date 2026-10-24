#include "common.h"
#include "data/bss_0062.h"
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) QV;
s32 func_001a8f30(void) {
    f32 r;
    __asm__ volatile(
        "addi $8, $0, -1\n"
        "qmtc2 $8, $vf2\n"
        "vrxor R, $vf2x\n"
        "vitof0.x $vf2x, $vf2x\n"
        "vrnext.x $vf1x, R\n"
        "vadd.x $vf1x, $vf1x, $vf2x\n"
        "qmfc2 %0, $vf1\n"
        : "=r"(r) : : "$8");
    return r * 32768.0f;
}

typedef struct {
    f32 o[4];
    f32 d[4];
    f32 r;
    f32 t;
} Ray;
f32 func_001a9328(f32);
s32 func_001a8f70(Ray *s) {
    f32 a, b, c, disc;
    s32 ret = 0;
    a = s->d[0] * s->d[0];
    a += s->d[1] * s->d[1];
    a += s->d[2] * s->d[2];
    b = s->d[0] * s->o[0];
    b += s->d[1] * s->o[1];
    b += s->d[2] * s->o[2];
    b *= 2.0f;
    c = s->o[0] * s->o[0];
    c += s->o[1] * s->o[1];
    c += s->o[2] * s->o[2];
    c -= s->r * s->r;
    disc = b * b - a * 4.0f * c;
    c = -b;
    b = 2.0f * a;
    if (!(disc < 0.0f)) {
        ret = 1;
        s->t = (c - func_001a9328(disc)) / b;
    }
    return ret;
}

f32 func_001a9058(f32 a, f32 b) {
    QV r;
    r.x = a;
    r.y = b;
    __asm__ volatile(
        "lqc2 $vf1, %1\n"
        "vmaxy.x $vf1x, $vf1x, $vf1y\n"
        "sqc2 $vf1, %0\n"
        : "=m"(r) : "m"(r));
    return r.x;
}

f32 func_001a9328(f32 a) {
    QV r;
    f32 o;
    r.y = a;
    __asm__ volatile(
        "lqc2 $vf10, %1\n"
        "vsqrt Q, $vf10y\n"
        "vwaitq\n"
        "cfc2 $2, $vi22\n"
        "mtc1 $2, %0\n"
        : "=f"(o) : "m"(r) : "$2");
    return o;
}

f32 func_001a9350(f32 *v) {
    QV r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vmove.xyz $vf9xyz, $vf10xyz\n"
        "vaddx.y $vf9y, $vf9y, $vf9x\n"
        "vaddy.z $vf9z, $vf9z, $vf9y\n"
        "vsqrt Q, $vf9z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "sqc2 $vf10, %0\n"
        : "=m"(r) : "r"(v));
    return r.x;
}

typedef int u128 __attribute__((mode(TI)));
