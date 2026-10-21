/* Hand-matched functions (worker c04). */
#include "common.h"

#include "data/types/text_00160000_c04.h"
typedef struct { V4 a; V4 b; V4 c; s16 h30; u8 pad32[0xE]; } RayC4;
typedef struct {
    u8 pad0[0x10]; V4 x10; u8 pad20[0x10]; V4 x30; u8 pad40[0x30]; s32 x70; u8 pad74[0x5C]; V4 xD0; u8 padE0[0x2E0]; V4 x3c0;
} CamC4;

extern CamC4 *D_00575894; /* src/data/bss_0057.c: void *D_00575894 */
extern V4 D_005758D0; /* src/data/bss_0057.c: f32 D_005758D0[4] */
extern V4 D_005758E0; /* src/data/bss_0057.c: f32 D_005758E0[4] */
V4 D_00575810 ALIGNED(16);
#include "data/pieces/D_002C58A0.h"
extern f32 D_002BBDFC;
extern f32 D_003624BC;
extern f32 D_003624C0;
extern f32 D_003624C4;
extern V4 D_00362680;
extern V4 D_00362660;

s32 func_00177168(void);
s32 func_00177070(void);
s32 func_001772f8(CamC4 *);
s32 func_00119688(RayC4 *);
void func_00118d78(RayC4 *);
f32 func_00120c88(f32);
f32 func_00120bf8(V4 *);
void func_002675a8(V4 *, V4 *);
void func_00267530(V4 *, V4 *, V4 *);
void func_00267518(V4 *, V4 *, V4 *);
void func_00267560(V4 *, V4 *, f32);
void func_002673b8(V4 *, V4 *);

s32 func_00177ef8(void) {
    RayC4 r;
    V4 t;
    s32 hit = 0;
    s32 busy;
    s32 n;
    f32 d;
    if (func_00177168()) {
        if (D_00575894->x70 == 2) {
            func_002675a8(&r.a, &D_005758E0);
            func_002675a8(&r.b, ((V4 *)&D_002C58A0));
            r.b.y = 1000.0f;
            if (func_00119688(&r) == -1) hit = 1;
            else if (D_00575894->x3c0.y > 5.0f) {
                func_002673b8(&t, &D_00575894->x3c0);
                func_00267560(&t, &t, 250.0f);
                func_002675a8(&r.b, &t);
                func_002675a8(&r.a, &D_00575894->x10);
                hit = func_00119688(&r) == -1;
            }
        }
        D_003624C4 = 0.0f;
    } else if (func_00177070()) {
        if (D_003624C4 > 60.0f) {
            func_002675a8(&r.a, &D_00575894->x10);
            func_00267560(&r.b, &D_00575894->x30, 100.0f);
            n = func_00119688(&r);
            if (n == -1) {
                func_002675a8(&r.a, &D_00575894->x30);
                func_00267560(&r.a, &r.a, 30.0f);
                func_00267518(&r.a, &r.a, &D_00575894->x10);
                r.a.y -= 100.0f;
                func_002675a8(&r.b, ((V4 *)&D_002C58A0));
                r.b.y = 500.0f;
                if (func_00119688(&r) == n) hit = 1;
            }
        } else {
            D_003624C4 += D_002BBDFC;
        }
    }
    func_002675a8(&D_00575810, &D_00575894->x10);
    busy = func_001772f8(D_00575894) != 0;
    if (hit && !busy) {
        D_00362680.x += D_003624BC / 30.0f * 0.0523598725f;
        D_00362680.x = func_00120c88(D_00362680.x);
        if (D_00362680.x > 1.483529598f) D_00362680.x = 1.483529598f;
        D_003624BC += D_002BBDFC;
        if (D_003624BC > 30.0f) D_003624BC = 30.0f;
    } else {
        D_003624BC = 0.0f;
    }
    func_002675a8(&r.a, &D_005758D0);
    func_002675a8(&r.b, ((V4 *)&D_002C58A0));
    r.b.y = 55.0f;
    func_00118d78(&r);
    if (r.h30 != -1 && !busy) {
        func_00267530(&t, &r.c, &D_005758D0);
        d = func_00120bf8(&t);
        if (d < 49.49999714f) {
            d = d / 55.0f;
            D_00362680.x += (1.0f - d) * (D_003624C0 / 30.0f) * 0.0523598725f;
            D_00362680.x = func_00120c88(D_00362680.x);
            if (D_00362680.x > 1.483529598f) D_00362680.x = 1.483529598f;
            D_003624C0 += D_002BBDFC;
            if (D_003624C0 > 30.0f) D_003624C0 = 30.0f;
        }
    } else {
        if (func_00177168()) D_003624C0 -= D_002BBDFC * 0.2999999896f;
        if (D_003624C0 < 0.0f) D_003624C0 = 0.0f;
        if (D_003624C0 <= 0.0f) D_00362680.x += func_00120c88(D_00362660.x - D_00362680.x) * 0.0299999998f;
    }
    func_00267530(&r.b, &D_005758E0, &D_005758D0);
    r.b.y -= 100.0f;
    func_002675a8(&r.a, &D_005758D0);
    return func_00119688(&r) == -1;
}

typedef struct { V4 a; V4 b; f32 r; u8 pad24[0xC]; V4 out; } SweepC4;
typedef struct { V4 r[4]; } M4;
typedef struct { u8 pad[8]; s32 w8; } PadC4;

extern u32 D_00575890; /* src/data/bss_0057.c: s32 D_00575890 */
extern f32 D_005758C4;
extern V4 D_00362670;
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_00362434.h"
extern s32 D_00362438;
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C5960.h"
extern u32 D_002C5958;
extern PadC4 D_002C5BB0;

f32 func_00124d28(V4 *, V4 *);
void func_00124c68(f32);
void func_001779e8(V4 *, V4 *, f32);
void func_001784b0(void);
void func_00177a98(void);
void func_002672f8(V4 *, void *, V4 *);
s32 func_00177440(V4 *, V4 *);
void func_00121fc4(V4 *, V4 *);
void func_00267e90(V4 *, V4 *, f32);
void func_00178e10(void);
void func_00178890(void);
void func_00178a98(void);
void func_00178468(void);
void func_00267768(M4 *, M4 *, f32);
void func_00267810(M4 *, M4 *, f32);
s32 func_00118868(SweepC4 *);
s32 func_00177740(V4 *);
s32 func_00177608(V4 *, V4 *, V4 *);
void func_00178d90(void);
s32 func_001375d8(CamC4 *);
void func_001784c8(void);
s32 func_00177358(CamC4 *);
void func_00176f08(s32, f32);
void func_0011d768(s32);
void func_001773b0(void);

void func_00178ef8(void) {
    V4 p;
    V4 a;
    V4 b;
    M4 m;
    SweepC4 s;
    f32 t;
    f32 d;
    f32 e;
    s32 r;
    f32 lim;

    if (D_00575890 & 2) {
        D_00575890 &= ~2;
        D_00362680.x = D_00362660.x;
        D_00362680.y = func_00124d28(((V4 *)&D_002E2780), ((V4 *)&D_002E2790));
        D_00362680.w = D_00362660.w;
        func_00124c68(53.0f);
        func_001779e8(&D_005758D0, &D_005758E0, D_00362680.y);
        D_00362434 = 0;
        D_00362438 = 0;
    }
    if (D_00575890 & 1) {
        D_00575890 &= ~1;
        func_001784b0();
        func_00177a98();
    }
    if (D_00575890 & 4) {
        D_00575890 &= ~4;
    }
    if (D_005758C4 > 0.0f) {
        func_002672f8(&D_005758E0, &D_00575894->xD0, &D_00362670);
    } else {
        func_002672f8(&a, &D_00575894->xD0, &D_00362670);
        func_002675a8(&b, &D_00362670);
        b.z = 0.0f;
        b.x = 0.0f;
        func_002672f8(&b, &D_00575894->xD0, &b);
        if (func_00177440(&b, &a)) func_002675a8(&a, &b);
        func_00267530(&a, &a, &D_005758E0);
        t = a.y;
        a.y = 0.0f;
        func_00121fc4(&a, &a);
        func_00267e90(&a, &a, a.w * 0.1999999918f);
        if (t > 0.0f) a.y = t * 0.5f;
        else a.y = t * 0.0999999959f;
        func_00267518(&D_005758E0, &D_005758E0, &a);
    }
    func_00178e10();
    func_00178890();
    if (func_00177070()) {
        func_00178a98();
        if (!((D_002C5960 >> 4) & 1)) func_00178468();
        t = func_00120c88(D_00362680.y);
        func_00267768(&m, ((M4 *)&D_002C58D0), func_00120c88(D_00362680.x));
        func_00267810(&m, &m, t);
        func_002675a8(&b, ((V4 *)&D_002C58A0));
        b.z = D_00362680.w;
        func_002672f8(&b, &m, &b);
        func_00267518(&p, &D_005758E0, &b);
        func_00267530(&b, &p, &D_005758E0);
        if (D_00362660.w + 300.0f < func_00120bf8(&b)) func_001779e8(&p, &D_005758E0, D_00362680.y);
        if ((D_002C5960 >> 4) & 1) {
            func_002675a8(&D_005758D0, &p);
        } else {
            lim = 20.0f;
            do {
                func_002675a8(&s.a, &D_005758D0);
                func_00267530(&b, &p, &D_005758D0);
                d = func_00120bf8(&b);
                if (d >= 1000.0f) {
                    func_002675a8(&D_005758D0, &p);
                    break;
                }
                if (d >= lim) func_00267560(&b, &b, lim / d);
                func_002675a8(&s.b, &b);
                s.r = 40.0f;
                r = func_00118868(&s);
                func_002675a8(&D_005758D0, &s.out);
            } while (r == 0 && d >= lim);
        }
        if (!func_00177740(&D_005758D0)) func_001779e8(&D_005758D0, &D_005758E0, D_00362680.y);
    } else {
        if (!((D_002C5960 >> 4) & 1)) func_00177ef8();
        t = func_00120c88(D_00362680.y);
        func_00267768(&m, ((M4 *)&D_002C58D0), func_00120c88(D_00362680.x));
        func_00267810(&m, &m, t);
        func_002675a8(&b, ((V4 *)&D_002C58A0));
        b.z = D_00362680.w;
        func_002672f8(&b, &m, &b);
        func_00267518(&p, &D_005758E0, &b);
        func_002675a8(&D_005758D0, &p);
        func_00267530(&b, &p, &D_005758E0);
        func_00121fc4(&b, &b);
        func_00267560(&b, &b, 60.0f);
        func_00267518(&p, &p, &b);
        if (func_00177608(&p, &D_005758E0, &p)) {
            func_00267530(&b, &D_005758E0, &p);
            func_00121fc4(&b, &b);
            if (b.w > 60.0f) {
                func_00267560(&b, &b, 60.0f);
                func_00267518(&D_005758D0, &p, &b);
            } else {
                func_002675a8(&D_005758D0, &p);
            }
        }
        func_00267530(&b, &D_005758E0, &D_005758D0);
        d = func_00120bf8(&b);
        if (d < 20.0f) {
            d = 20.0f - d;
            func_002673b8(&b, &b);
            func_00267560(&b, &b, d);
            func_00267518(&D_005758E0, &D_005758E0, &b);
        }
    }
    if (func_00177070()) func_00178d90();
    func_00267530(&b, &D_005758D0, &D_005758E0);
    if ((D_002C5BB0.w8 & 0x200) && !func_001375d8(D_00575894)) func_001784c8();
    if ((D_002C5BB0.w8 & 0x8000) && func_00177358(D_00575894) && !func_001375d8(D_00575894)) {
        if (!((D_002C5958 >> 13) & 1)) {
            func_00176f08(2, 30.0f);
            func_001784b0();
        } else {
            func_0011d768(4);
        }
    }
    if (func_00177070()) {
        func_00267530(&b, &D_005758D0, &D_005758E0);
        e = func_00120bf8(&b);
        D_00362680.w = e + (D_00362660.w - e) * 0.0999999959f;
    } else {
        D_00362680.w = D_00362660.w;
    }
    D_00362680.y = func_00124d28(&D_005758D0, &D_005758E0);
    func_001773b0();
}
#include "data/data_0036.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_00362660.h"
#include "data/pieces/D_00362670.h"
#include "data/pieces/D_00362680.h"
#include "data/pieces/D_002BBDFC.h"
