#include "common.h"

/* worker b06: hand-matched functions 0x001784c8..0x0017e428 (camera code) */

typedef struct { f32 x, y, z, w; } V4;
/* ray / segment block passed to func_00118b58 / func_00119688 */
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
/* the object D_00575894 points to */
typedef struct {
    s32 x0;             /* 0x00 flags */
    u8 pad4[0x3c - 4];
    f32 x3c;            /* 0x3C yaw */
    u8 pad40[0x64 - 0x40];
    f32 x64;            /* 0x64 */
    u8 pad68[0xd0 - 0x68];
    f32 xd0[4][4];      /* 0xD0 matrix */
} ActB;
/* pad state at D_002C5BB0 */
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;

extern ActB *D_00575894;
extern s32 D_00575890;
extern f32 D_005758C0;
extern f32 D_005758F8;
extern f32 D_0057582C;
extern f32 D_00575830;
extern V4 D_005758D0;
extern V4 D_005758E0;
extern V4 D_00362510;
extern V4 D_00362680;
extern f32 D_00362684;
extern f32 D_003624C8;
extern f32 D_003624CC;
extern f32 D_003624D0;
extern f32 D_003624D4;
extern f32 D_002BBDFC;
extern PadB D_002C5BB0;
extern u8 D_002C58A0[];
extern u8 D_002C58D0[];

f32 func_00120c88(f32);
s32 func_001770b8(void);
s32 func_00118b58(void *);
f32 func_00124d28(V4 *, V4 *);
void func_00176f08(s32, f32);
void func_001315c0(void *, s32, void *, f32);
void func_00267768(void *, void *, f32);
void sceVu0MulMatrix(void *, void *, void *);
void func_002672f8(void *, void *, void *);
void func_002675a8(void *, void *);

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

