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
typedef union Tag {
    u128 q;
    struct { s32 tag; union Tag *next; union Tag *self; s32 pad; } s;
} Tag;
extern Tag D_0061EEA0[];
extern u8 D_0061E800[];
extern u8 D_0061E8B0[];
void func_001aa6b0(void *, s32, s32, s32);
void func_001aa700(void *, s32, s32, s32);
void func_001a9f88(void) {
    Tag *p = D_0061EEA0;
    u128 k = 0x20000000;
    s32 i;
    for (i = 0; i < 288; i++) {
        __asm__ volatile("sq %0, 0(%1)" : : "r"(k), "r"(p));
        p->s.next = p + 1;
        p->s.self = p;
        p++;
    }
    __asm__ volatile("sq %0, 0(%1)" : : "r"(k), "r"(p));
    p->s.tag = 0x70000000;
    func_001aa6b0(D_0061E800, 7, 0, 0);
    func_001aa700(D_0061E8B0, 7, 15, 0);
}


s32 rand(void);
void func_001aa080(void) {
    s32 r;
    r = rand();
    __asm__ volatile(
        "qmtc2 %0, $vf31\n"
        "vrxor R, $vf31x\n"
        : : "r"(r) : "$2");
}

extern s32 D_00623220;
extern s32 D_00623224;
void func_001bb7b0(void);
s32 func_00120748(char *, void *, void *, s32);
void func_001bfac8(void);
s32 func_001bb7c8(char *a, void *b) {
    D_00623220 = 1;
    D_00623224 = -1;
    func_00120748(a, b, func_001bb7b0, 0);
    while (D_00623220) func_001bfac8();
    return D_00623224;
}

typedef union { u16 h; struct { u16 x : 4; u16 y : 4; u16 z : 4; u16 w : 4; } b; } N3;
typedef struct { s8 x, y, z, w; } V4c;
extern V4c D_0037A130[];
typedef struct {
    u16 f0;
    N3 rot;
    u16 id;
} Obj;
s32 func_001bb6d0(s32);
s32 func_001bbdf0(Obj *o) {
    N3 s, r;
    s32 ax, ay, az;
    
    s.h = func_001bb6d0(o->id - 1);
    ax = D_0037A130[o->rot.b.x].x * s.b.x;
    ay = D_0037A130[o->rot.b.x].y * s.b.x;
    az = D_0037A130[o->rot.b.x].z * s.b.x;
    ax += D_0037A130[o->rot.b.y].x * s.b.y;
    ay += D_0037A130[o->rot.b.y].y * s.b.y;
    az += D_0037A130[o->rot.b.y].z * s.b.y;
    ax += D_0037A130[o->rot.b.z].x * s.b.z;
    ay += D_0037A130[o->rot.b.z].y * s.b.z;
    az += D_0037A130[o->rot.b.z].z * s.b.z;
    r.b.x = abs(ax);
    r.b.y = abs(ay);
    r.b.z = abs(az);
    return r.h;
}
