#include "common.h"
#include "data/bss_0052.h"
/* Hand-matched functions (session 6, worker w606), all -fno-strict-aliasing. */

/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */

typedef struct {
    u8 lv;
    u8 x1;
    u8 x2;
    u8 x3;
    u8 pad04[0x38 - 0x4];
    s16 x38;
    u8 pad3a[2];
    s32 exp;
    u8 name[0x30];
    u8 bits;
    u8 pad71[3];
} W606Mem;

typedef struct {
    u8 pad000[4];
    W606Mem m[10];
    u8 x48c;
    u8 x48d;
    u8 party[4];
    u8 pad492[0x599 - 0x492];
    u8 list599[0x30];
    u8 pad5c9[0x5CC - 0x5C9];
    u32 bits5cc[(0x7D0 - 0x5CC) / 4];
    s8 x7d0[7];
    u8 pad7d7[0x844 - 0x7D7];
    s8 x844[3];
    u8 pad847[0x878 - 0x847];
    u64 x878;
} W606Save;

extern W606Save *D_00304BE8;

typedef struct W606Ch W606Ch;
struct W606Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    f32 x18;
    f32 x1c;
    u8 pad020[0x6c - 0x20];
    void *x6c;
    s32 x70;
    u8 pad074[0x130 - 0x74];
    u8 *info;
    u8 pad134[0x148 - 0x134];
    s32 x148;
    u8 pad14c[0x2D4 - 0x14C];
    f32 x2d4;
    u8 pad2d8[0x360 - 0x2D8];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W606Ch *x398;
};

extern u32 *D_0052AE38; /* src/data/bss_0052.c: s32 D_0052AE38 */
extern s32 D_0052AE60;
extern s32 D_00350CE0;
extern u32 *D_002E26A0[];
extern u8 D_0052AD68[];
void func_0014f658(void *, s32);
s32 func_00130340(void *, s32, f32);
void func_001373f8(void *o, f32 f);
s32 func_00148768(s32, s32, void *, s32, f32);
void func_00124ce0(f32);
void func_001336d8(void);
void func_002414a8(s32 a, s32 b);
void func_00145080(s32 a, s32 b);
void *func_0011f090(void *, s32, void *);
void func_0011ef10(s32, void *);
s32 func_0013ab30();
void func_0013abf8();
s32 func_0013b050(void) {
    s32 i;
    s32 *pp;
    func_0014f658(D_0052AE38, 40);
    func_00130340(D_0052AE38, 0x1010040, 20.0f);
    func_001373f8(D_0052AE38, 0.0f);
    *D_0052AE38 |= 0x200000;
    pp = &D_0052AE60;
    *pp = func_00148768(D_00350CE0, 0, D_0052AE38, 28, 0.5f);
    func_00124ce0(53.0f);
    func_001336d8();
    func_002414a8(0, 3);
    func_002414a8(1, 3);
    func_002414a8(2, 3);
    func_00145080(1, 4);
    for (i = 0; i < 2; i++) {
        if (D_002E26A0[i + 1]) *D_002E26A0[i + 1] |= 0x1000000;
    }
    func_0011f090(D_0052AD68, 0, func_0013ab30);
    func_0011ef10(100000, func_0013abf8);
    return 1;
}

extern W606Save *D_00304BE8;
extern u16 *D_00304BB0[];
extern u16 *D_00304B88[];
void *func_001477c8(void *p);
u16 *func_0013c3f8(s32 i);
void func_0015b268(s32 i);
void func_0015b438(s32 i);
s32 func_0013c458(s32 i, s32 n) {
    W606Mem *m = &D_00304BE8->m[i];
    u16 *p = func_0013c3f8(i);
    s32 lv = 1;
    s32 first = 1;
    s32 e = n + m->exp;
    if (e > 999999) e = 999999;
    m->exp = e;
    while (lv < 100) {
        e -= *p++;
        if (e < 0) break;
        lv++;
        if (m->lv < lv) {
            func_0015b268(i);
            if (first) {
                first = 0;
                func_0015b438(i);
            }
        }
    }
    return m->exp;
}

typedef struct { u8 pad[0x38]; s16 x38; } W606T12c8;
typedef struct { u8 pad[0x40]; s32 x40; s32 x44; s32 x48; u8 pad4c[0xbe - 0x4c]; s16 xbe; u8 padc0[8]; W606T12c8 *xc8; } W606T12s;
typedef struct { u8 pad[0x6c]; W606T12s *x6c; } W606T12o;
void func_00141468(W606T12o *o, s32 a);
s32 func_00141540(W606T12o *o, s32 a);
void func_00141218(W606T12o *o) {
    s32 n;
    if (o == 0) return;
    func_00141468(o, o->x6c->x40);
    n = o->x6c->x48;
    if (o->x6c->x44 < n) {
        func_00141540(o, n);
        o->x6c->xbe = 0;
        if (o->x6c->xc8) o->x6c->xc8->x38 = 0;
    }
}

f32 func_00144368(W606Ch *o);
s32 func_00142618(W606Ch *o) {
    W606Ch *p = o->x398;
    s32 r;
    f32 d;
    if (p != 0 && !((p->x370 >> 39) & 1)) {
        r = p->info[0x5d];
    } else {
    r = o->x360;
    if (o->x14 >= o->x2d4) {
        d = func_00144368(o);
        if (d < 20.0f) r = 10;
        else if (d < 50.0f) r = 11;
        else r = 12;
    }
    }
    return r;
}

typedef struct { f32 x, y, z, w; } W606V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; W606V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; } W606S148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    W606V4f pos;
    u8 pad20[0x148 - 0x20];
    W606S148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    W606V4f v2a0;
    W606V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    W606V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
} W606F3;
s32 func_001166e8(W606V4f *);
void func_002673b8(W606V4f *, W606V4f *);
void func_00267e90(W606V4f *, W606V4f *, f32);
void func_00267530(W606V4f *, W606V4f *, W606V4f *);
s32 func_001429f8(W606V4f *, W606V4f *, W606V4f *);

s32 func_00143080(W606F3 *o, W606V4f *v) {
    W606V4f t, hit;
    s32 r = 1;
    if (!func_001166e8(&o->v2a0) && !(o->w2d0 & 1)) return r;
    func_002673b8(&t, v);
    func_00267e90(&t, &t, o->f2c0 + 10.0f);
    t.y = -200.0f;
    t.w = 200.0f;
    if (func_001429f8(&o->v2a0, &t, &hit)) goto zero;
    func_00267530(&o->v2b0, &hit, &o->v2a0);
    o->v2b0.w = 1.0f;
    if (func_001166e8(&o->v2a0) && (o->w2d0 & 1)) goto zero;
    return 1;
zero:
    return 0;
}

typedef struct { f32 f; s32 pad; } W606F8;
extern W606F8 D_00304D60[];
s32 func_001443a8(W606Ch *o) {
    if (o->x148 != 0 && ((s32)(o->x370 >> 56) & 1)) {
        if (D_00304D60[*(u16 *)(o->info + 0x4c)].f < o->x14 - o->x2d4) return 1;
    }
    return 0;
}

typedef struct { u8 pad[0xc]; f32 xc; } W606T7v;
typedef struct { u8 pad[0xc]; W606T7v *xc; u8 pad10[4]; u32 x14; } W606T7a;
typedef struct { u8 pad[0x14]; W606T7a *x14; u8 pad18[4]; f32 x1c; } W606T7o;
extern f32 D_002BBDFC;
void func_00176310();
s32 func_00147ff0(W606T7o *o) {
    W606T7a *a = o->x14;
    W606T7v *v;
    f32 f;
    if (a != 0) {
        if ((a->x14 & 3) == 1) {
            v = a->xc;
            f = v->xc - o->x1c * D_002BBDFC;
            if (!(f <= 0.0f)) goto st;
            func_00176310(a, o);
        } else {
            return 4;
        }
    }
    return 4;
st:
    v->xc = f;
    return 0;
}

