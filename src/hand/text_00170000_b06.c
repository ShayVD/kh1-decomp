/* worker b06: hand-matched camera functions 0x001784c8..0x0017e428 */
#include "common.h"
#include "data/bss_0057.h"
#include "data/types/text_00170000_b06.h"
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB;
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Path *D_00362438;
extern Cam D_00575940;
void func_0017b308(void *, Seg *, s32, s32, s32);
void func_0017b250(void *, void *, f32);
s32 func_0017b860(s32, V4 *, f32 *, s32 *);
s32 func_0017b4f8(s32 *, f32 *, f32);
extern ActB *D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
extern s32 D_00575890;
extern f32 D_005758C0;
extern f32 D_005758C4;
extern V4 D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern V4 D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
extern V4 D_00362680;
extern f32 D_00362684;
extern f32 D_002BBDFC;
extern PadB D_002C5BB0;
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58D0.h"
f32 func_00120c88(f32);
s32 func_00118b58(void *);
s32 func_00119688(void *);
f32 func_00124d28(V4 *, V4 *);
void func_00176f08(s32, f32);
void func_0017bc90(s32);
void func_0017cb88(void);
void func_00267768(void *, void *, f32);
void func_00267810(void *, void *, f32);
void func_002672f8(void *, void *, void *);
void func_002675a8(void *, void *);
void func_00267518(void *, void *, void *);
void func_00267530(void *, void *, void *);
void func_00121fc4(void *, void *);
void func_00267e90(void *, void *, f32);
s32 func_00177608(void *, void *, void *);
s32 func_001772c8(ActB *);
f32 sinf(f32);
f32 cosf(f32);

/* ---- func_00178a98 ---- */
f32 D_005758F8 ALIGNED(8);
extern f32 D_003624C8;
extern f32 D_003624CC;
extern f32 D_003624D0;
extern f32 D_003624D4;
s32 func_001770b8(void);

void func_00178a98(void) {
    Ray s;
    f32 d, t, ad;

    if (fabsf(D_003624C8 - D_00575894->x3c) < 0.52359875f && func_001770b8()) {
        D_003624D4 += D_002BBDFC;
        if (D_003624D4 > 60.0f) {
            D_003624D4 = 60.0f;
            D_003624D0 += D_002BBDFC;
            if (D_003624D0 > 90.0f) D_003624D0 = 90.0f;
        }
    } else {
        D_003624D4 = 0.0f;
        D_003624D0 = 0.0f;
    }
    if (D_005758F8 <= 0.0f && D_003624D4 > 0.0f) {
        func_002675a8(&s.b, ((u8 *)&D_002C58A0));
        func_002675a8(&s.a, &D_005758E0);
        s.c.y = 0.0f;
        s.c.x = 250.0f;
        if (func_00118b58(&s) || (func_002675a8(&s.a, &D_005758D0), func_00118b58(&s))) {
            D_003624CC += D_002BBDFC;
            if (D_003624CC > 60.0f) D_003624CC = 60.0f;
            if (D_003624D0 != 0.0f) D_003624D0 = 90.0f;
        } else {
            D_003624CC -= D_002BBDFC * 0.2999999896f;
            if (D_003624CC < 0.0f) D_003624CC = 0.0f;
        }
        d = func_00120c88(D_00575894->x3c + 3.1415928f - D_00362680.y);
        t = D_003624CC / 60.0f * 0.02000000002f + D_003624D0 / 90.0f * 0.02000000002f;
        ad = fabsf(d);
        if (ad < 2.094394982f) D_00362680.y += d * t;
        else D_00362680.y += d * t * (1.0f - (ad - 2.094394982f) / 1.047197491f);
    }
    D_003624C8 = D_00575894->x3c;
}

/* ---- func_00179a80 ---- */
f32 D_0057582C ALIGNED(4);
f32 D_00575830 ALIGNED(16);
extern V4 D_00362510;
void func_001315c0(void *, s32, void *, f32);
void sceVu0MulMatrix(void *, void *, void *);

void func_00179a80(void) {
    f32 m[4][4];
    u32 b;
    PadB *p;

    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        D_0057582C = 0.0f;
        D_00575830 = D_005758C0;
    }
    if (D_00575830 > 0.0f) {
        D_00575830 -= D_002BBDFC;
        if (D_00575830 <= 0.0f) {
            D_00575894->x0 &= ~1;
            D_00575830 = 0.0f;
        }
    }
    func_001315c0(D_00575894, 0, &D_005758D0, 0.5f);
    func_00267768(m, D_002C58D0, D_0057582C);
    sceVu0MulMatrix(m, D_00575894->xd0, m);
    func_002675a8(m[3], &D_005758D0);
    m[3][3] = 1.0f;
    func_002672f8(&D_005758E0, m, &D_00362510);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    p = &D_002C5BB0;
    b = p->x4;
    if (b & 0x10) {
        D_0057582C -= D_002BBDFC * 0.01745329099f;
        if (D_0057582C < -1.396263272f) D_0057582C = -1.396263272f;
    } else if (b & 0x40) {
        D_0057582C += D_002BBDFC * 0.01745329099f;
        if (D_0057582C > 1.047197491f) D_0057582C = 1.047197491f;
    } else {
        if (D_0057582C > D_002BBDFC * 0.01745329099f) D_0057582C -= D_002BBDFC * 0.01745329099f;
        else if (D_0057582C < D_002BBDFC * -0.01745329099f) D_0057582C += D_002BBDFC * 0.01745329099f;
        else D_0057582C = 0.0f;
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x200) {
        D_00575894->x0 |= 1;
        func_00176f08(1, 30.0f);
    }
}

/* ---- func_0017a958 ---- */
V4 D_00575840 ALIGNED(16);
f32 D_00575850 ALIGNED(16);
f32 D_00575854 ALIGNED(4);
f32 D_00575858 ALIGNED(8);
extern V4 D_003625C0;
extern V4 D_003625D0;
extern f32 D_003625E0;

void func_0017a958(void) {
    V4 a;
    V4 b;
    f32 m[4][4];
    Ray r;
    f32 s;
    f32 p;
    u32 k;

    if (D_00575890 & 2) {
        func_002675a8(&D_00575840, &D_003625C0);
        D_00575890 &= ~2;
    }
    if (D_005758C4 <= 0.0f) {
        k = D_002C5BB0.x4;
        s = 0.0f;
        if (k & 0x1000) s = 1.0f;
        if (k & 0x2000) s = -1.0f;
        if (s != 0.0f) {
            p = D_00575840.x + func_00120c88(s * 0.04363322724f * D_002BBDFC);
            func_00267768(m, D_002C58D0, func_00120c88(p));
            func_00267810(m, m, func_00120c88(D_00575850));
            func_002675a8(&b, ((u8 *)&D_002C58A0));
            b.z = D_00575840.w;
            func_002672f8(&b, m, &b);
            func_002672f8(&D_005758E0, D_00575894->xd0, &D_003625D0);
            func_00267518(&a, &D_005758E0, &b);
            func_00267530(&r.b, &a, &D_005758E0);
            func_002675a8(&r.a, &D_005758E0);
            if (func_00119688(&r) == -1) {
                D_00575840.x = p;
                if (p > 0.8726645261f) D_00575840.x = 0.8726645261f;
                else if (p < -0.8726645261f) D_00575840.x = -0.8726645261f;
            }
        }
    } else {
        D_00575850 = D_00575894->x3c;
    }
    if ((u32)(&D_002C5BB0)->x8 & 0x200) {
        D_003625E0 = 15.0f;
        D_00575854 = D_00575840.x;
        D_00575858 = 0.3490658179f - D_00575840.x;
    }
    if (D_003625E0 > 0.0f) {
        D_003625E0 -= D_002BBDFC;
        if (D_003625E0 < 0.0f) D_003625E0 = 0.0f;
        s = sinf((1.0f - D_003625E0 / 15.0f) * 3.1415928f * 0.5f);
        D_00575840.x = D_00575854 + D_00575858 * s;
    }
    D_00575840.y = func_00120c88(D_00575850);
    func_00267768(m, D_002C58D0, func_00120c88(D_00575840.x));
    func_00267810(m, m, D_00575840.y);
    func_002675a8(&b, ((u8 *)&D_002C58A0));
    b.z = D_00575840.w;
    func_002672f8(&b, m, &b);
    func_002672f8(&D_005758E0, D_00575894->xd0, &D_003625D0);
    func_00267518(&a, &D_005758E0, &b);
    func_00267530(&b, &a, &D_005758D0);
    func_00121fc4(&b, &b);
    b.w -= 100.0f;
    if (b.w > 0.0f) {
        func_00267e90(&b, &b, b.w);
        D_005758D0.x += b.x;
        D_005758D0.z += b.z;
    }
    D_005758D0.y = a.y;
    if (func_00177608(&b, &D_005758E0, &D_005758D0)) func_002675a8(&D_005758D0, &b);
    D_00362684 = func_00124d28(&D_005758D0, &D_005758E0);
    if (!func_001772c8(D_00575894)) func_00176f08(1, 30.0f);
}

/* ---- func_0017e170 ---- */
typedef struct { V4 x0; s32 x10; f32 x14[4]; f32 x24[4]; u8 pad34[0x44 - 0x34]; s32 x44; } CamB;
extern CamB D_005759B0;

s32 func_0017e170(s32 a0)
{
    Ray ray;
    V4 v40;
    V4 v50;
    V4 v60;
    f32 m[4][4];
    f32 y;
    f32 d;
    f32 a;
    s32 i;
    s32 first;
    s32 n;

    first = 1;
    n = 4;
    d = D_005759B0.x24[a0];
    y = D_00362680.y;
    if (D_005759B0.x44 == 0) {
        for (i = 0; i < 5; i++) {
            a = y + d * ((f32)i / (f32)n);
            func_002675a8(&v40, &v50);
            func_00267768(m, D_002C58D0, func_00120c88(D_00362680.x));
            func_00267810(m, m, func_00120c88(a));
            func_002675a8(&v60, ((u8 *)&D_002C58A0));
            v60.z = D_00362680.w;
            func_002672f8(&v60, m, &v60);
            func_00267518(&v50, &D_005759B0, &v60);
            v50.w = 1.0f;
            if (first) {
                func_002675a8(&v40, &v50);
                first = 0;
            } else {
                func_002675a8(&ray.a, &v40);
                func_00267530(&ray.b, &v50, &v40);
                if (func_00119688(&ray) != -1) {
                    return 1;
                }
            }
        }
    } else {
        a = y + d;
        func_00267768(m, D_002C58D0, func_00120c88(D_00362680.x));
        func_00267810(m, m, func_00120c88(a));
        func_002675a8(&v60, ((u8 *)&D_002C58A0));
        v60.z = D_00362680.w;
        func_002672f8(&v60, m, &v60);
        func_00267518(&v50, &D_005759B0, &v60);
        v50.w = 1.0f;
    }
    func_002675a8(&ray.a, &D_005759B0);
    func_00267530(&ray.b, &v50, &D_005759B0);
    return func_00119688(&ray) != -1;
}

/* ---- func_0017e428 ---- */
f32 fabsf(f32);

extern s32 D_00362420;
extern V4 D_00362600;
extern f32 D_00362610[];
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
void func_0012fc58(void);
void func_00267560(void *, void *, f32);
s32 func_0017dbb8(void);
void func_00177900(void *, void *, f32);

s32 func_0017e428(V4 *a, V4 *b)
{
    s32 tab[2];
    f32 cur;
    f32 ang;
    f32 t;
    f32 d;
    f32 spd;
    s32 i;
    s32 best;
    s32 prev;
    s32 next;
    s32 n;

    func_0012fc58();
    D_00362420 = 1;
    D_005759B0.x10 = 4;
    func_00267518(&D_005759B0, a, b);
    func_00267560(&D_005759B0, &D_005759B0, 0.5f);
    func_00267518(&D_005759B0, &D_005759B0, &D_00362600);
    D_00362680.y = func_00124d28(((V4 *)&D_002E2780), ((V4 *)&D_002E2790));
    cur = D_00362680.y;
    ang = func_00124d28(a, b);
    D_005759B0.x44 = func_0017dbb8();
    if (D_005759B0.x44 != 0) {
        D_00362680.y = ang;
        cur = D_00362680.y;
        func_00177900(((V4 *)&D_002E2780), ((V4 *)&D_002E2790), cur);
        func_002675a8(((V4 *)&D_002E2790), &D_005759B0);
        spd = 0.0f;
    } else {
        spd = 16.0f;
    }
    for (i = 0; i < 4; i++) {
        t = func_00120c88(D_00362610[i] + ang);
        D_005759B0.x14[i] = t;
        d = t - cur;
        D_005759B0.x24[i] = d;
        if (3.141592801f < fabsf(d)) {
            if (d < 0.0f) {
                D_005759B0.x24[i] = d + 6.2831855f;
            } else {
                D_005759B0.x24[i] = d - 6.2831855f;
            }
        }
    }
    best = 0;
    for (i = 1; i < 4; i++) {
        if (fabsf(D_005759B0.x24[i]) < fabsf(D_005759B0.x24[best])) {
            best = i;
        }
    }
    if (func_0017e170(best) == 0) {
        D_005759B0.x10 = best;
    } else {
        prev = best - 1;
        next = best + 1;
        if (prev < 0) {
            prev = 3;
        }
        n = 0;
        if (next < 4) {
            n = next;
        }
        if (fabsf(D_005759B0.x24[prev]) < fabsf(D_005759B0.x24[n])) {
            tab[0] = prev;
            tab[1] = n;
        } else {
            tab[0] = n;
            tab[1] = prev;
        }
        for (i = 0; i < 2; i++) {
            if (func_0017e170(tab[i]) == 0) {
                D_005759B0.x10 = tab[i];
                break;
            }
        }
        if (D_005759B0.x10 == 4) {
            n = (n + 1 < 4) ? n + 1 : 0;
            if (func_0017e170(n) == 0) {
                D_005759B0.x10 = n;
            }
        }
    }
    func_00176f08(7, spd);
    D_005758C4 = 0;
    return D_005759B0.x10;
}
#include "data/data_0036.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00362510.h"
#include "data/pieces/D_003625C0.h"
#include "data/pieces/D_003625D0.h"
#include "data/pieces/D_00362600.h"
