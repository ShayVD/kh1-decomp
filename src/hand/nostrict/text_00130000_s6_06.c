#include "common.h"
#include "data/bss_0052.h"
/* Hand-matched functions (session 6, worker w606), all -fno-strict-aliasing. */

/* Hand-matched functions near 0x13C000-0x145000 (worker 7). */

#include "data/pieces/D_00304BE8_s.h"
typedef W606Mem_304be8 W606Mem;

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
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
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
        if (D_002E26A0[i + 1]) *((u32 *)D_002E26A0[i + 1]) |= 0x1000000;
    }
    func_0011f090(D_0052AD68, 0, func_0013ab30);
    func_0011ef10(100000, func_0013abf8);
    return 1;
}

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
    s32 e = n + m->sub.exp;
    if (e > 999999) e = 999999;
    m->sub.exp = e;
    while (lv < 100) {
        e -= *p++;
        if (e < 0) break;
        lv++;
        if (m->sub.lv < lv) {
            func_0015b268(i);
            if (first) {
                first = 0;
                func_0015b438(i);
            }
        }
    }
    return m->sub.exp;
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

#include "data/pieces/D_002BBDFC.h"
