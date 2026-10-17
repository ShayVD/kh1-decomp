#include "common.h"

/* worker b06: hand-matched functions 0x001784c8..0x0017e428 */
typedef struct { f32 x, y, z, w; } V4;
typedef struct { u8 pad[0x3c]; f32 x3c; } Act3c;
typedef struct { V4 a; V4 b; f32 c; f32 d; f32 e, f; V4 g; } Seg2;
extern Act3c *D_00575894;
extern V4 D_00362680;
extern f32 D_003624C8;
extern f32 D_003624CC;
extern f32 D_003624D0;
extern f32 D_003624D4;
extern f32 D_002BBDFC;
extern f32 D_005758F8;
extern V4 D_005758D0;
extern V4 D_005758E0;
extern u8 D_002C58A0[];
f32 func_00120c88(f32);
s32 func_001770b8(void);
s32 func_00118b58(void *);
void func_002675a8(void *, void *);

void func_00178a98(void) {
    Seg2 s;
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
        s.d = 0.0f;
        s.c = 250.0f;
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
