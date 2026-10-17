/* worker b06: hand-matched camera functions 0x001784c8..0x0017e428 */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
typedef struct {
    s32 x0; u8 pad4[0x30 - 4]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB;
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n; f32 x4; f32 x8; u8 padc[8]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; u8 pad58[4]; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Path *D_00362438;
extern Cam D_00575940;
void func_0017b308(void *, Seg *, s32, s32, s32);
void func_0017b250(void *, void *, f32);
s32 func_0017b860(void *, V4 *, f32 *, s32 *);
s32 func_0017b4f8(s32 *, f32 *, f32);
extern ActB *D_00575894;
extern s32 D_00575890;
extern f32 D_005758C0;
extern f32 D_005758C4;
extern V4 D_005758D0;
extern V4 D_005758E0;
extern V4 D_00362680;
extern f32 D_00362684;
extern f32 D_002BBDFC;
extern PadB D_002C5BB0;
extern u8 D_002C58A0[];
extern u8 D_002C58D0[];
f32 func_00120c88(f32);
s32 func_00118b58(void *);
s32 func_00119688(void *);
f32 func_00124d28(V4 *, V4 *);
void func_00176f08(s32, f32);
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
extern f32 D_005758F8;
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
        func_002675a8(&s.b, D_002C58A0);
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
extern f32 D_0057582C;
extern f32 D_00575830;
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
extern V4 D_00575840;
extern f32 D_00575850;
extern f32 D_00575854;
extern f32 D_00575858;
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
            func_002675a8(&b, D_002C58A0);
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
    func_002675a8(&b, D_002C58A0);
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
