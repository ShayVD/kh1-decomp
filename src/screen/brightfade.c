/* The screen's brightness fades (a guess at the name), 0x00105f28-0x00106b18:
 * D_002BC070 is the brightness (128 normal), func_00106780 / func_00106880
 * / func_00106978 / func_00106a58 start fades over n frames as tasks
 * (func_0011f090 on D_002BC720), func_001063f8 tells whether one is still
 * running, func_00105f28 / func_00106000 draw the fade's sprite. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "common.h"
#include "data/pieces/D_002A624C.h"
#include "data/bss_0049.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002A6274.h"
#include "data/types/text_00100000_h1.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0029B280.h"
#include "data/pieces/D_002A3F50.h"
#include "data/pieces/D_002A6208.h"
#include "data/pieces/D_002A6C10.h"
#include "data/pieces/D_002BC070.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_002BCAF0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
#include "m2c.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002A3F48.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00100000_s8_w9.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"
#include "data/pieces/D_002BCCE0.h"
#include "data/pieces/D_002B6778.h"
#include "data/pieces/D_0037A378.h"
#include "data/types/text_00100000_h28.h"
#include "data/pieces/D_002BC0C0.h"
#include "data/pieces/D_002A6234.h"
#include "data/types/text_00100000_h28_p.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002A62B0.h"
#include "data/pieces/D_002A3F60.h"
#include "data/pieces/D_002A4060.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002A3E20.h"
#include "data/pieces/D_002A3F30.h"
#include "data/pieces/D_002A62D0.h"
#include "data/pieces/D_002BBDE4.h"

/* func_00105f28 (from hand/text_00100000_h1.c). */
extern GsRegs D_002A6330;
extern u8 D_002A6500[];
extern s32 D_002BBE14;
extern s32 D_002BC060[4];
void func_00106b18(void *);
void func_00105f28(void) {
    if (D_002BBE14) {
        D_002A6330.d32 = 0x131000070;
        D_002A6330.d16 = 0x131000070;
    } else {
        D_002A6330.d32 = 0x31000070;
        D_002A6330.d16 = 0x31000070;
    }
    D_002A6330.d152 = (u64)D_002BC060[0] | ((u64)D_002BC060[1] << 8) | ((u64)D_002BC060[2] << 16) | ((u64)D_002BC060[3] << 24) | 0x100000000;
    func_00106b18(D_002A6500);
}

/* func_00105fc8 (from auto/text_00100000_3.c). */
M2C_UNK func_001f1ed8(M2C_UNK, M2C_UNK, M2C_UNK, s32, M2C_UNK);
s32 func_001efc10(M2C_UNK);
void func_00105fc8(void) {
    func_001f1ed8(0x80C0612C, 0x140, 0x194, func_001efc10(0xF), 0xF);
}

/* func_00106000 (from hand/text_00100000_s8_w9.c). */
extern Col D_002BC0B0;
extern s32 D_002BBE04;
extern s32 D_002BC744;
extern s32 D_002BC730;
extern s32 D_002BC740;
extern s32 D_002A6B80;
s32 D_00494A78 ALIGNED(8);
extern u64 D_002A68A0[];
extern u64 D_002A6658;
extern u64 D_002A6970[];
extern u8 D_002A6960[];
extern u8 D_002A6890[];
extern u8 D_002A6580[];
extern u8 D_002A61E0[];
extern u8 D_002A6540[];
extern u8 D_002A69D0[];
extern u8 D_002A65C0[];
s32 func_0010ffe0(void);
void func_00102da8(s32);
void func_0010ff60(s32);
s32 func_001110d0(void);
void func_0010fee8(s32, s32);
static inline u64 rgba(Col *c) { u64 w = (u64)c->r | 0x100000000; u64 v = (u64)c->b << 16 | (u64)c->g << 8; return (w | v) | ((u64)c->a << 24); }
#define func_00106b18 ((s32 (*)(void *)) func_00106b18)
/* func_00106000 (hand, rodata jtbl 0x48cc80: verified with rr.py). rgba inline computes w = r | 1<<32 before v; the else-branch D_002A6658 store goes through a block-local u64 *q; case 2 computes x/y after the [4]/[6] stores. */
void func_00106000(s32 a) {
    func_0010ffe0();
    switch (a) {
    case 1:
    case 4:
        func_00102da8(a);
        break;
    case 0:
    default:
        D_002BC730 = 0;
        break;
    }
    if (D_002BC0B0.a != 0) {
        D_002A6970[9] = rgba(&D_002BC0B0);
        D_002A6970[10] = 0x174007000;
        D_002A6970[11] = 0x18C009000;
        func_00106b18(D_002A69D0);
    }
    if (D_002A6208 != 0) {
        func_00106b18(D_002A61E0);
    }
    switch (a) {
    case 3:
        func_0010ff60(0);
        D_002BBE04 = 0;
    case 0:
    case 1:
    case 4:
        func_00106b18(D_002A6540);
        if (D_002BC740 == 1) {
            u64 *q = &D_002A6658;
            *q = 0x100000000;
            func_00106b18(D_002A6890);
            if (D_002BC744 == 0) {
                D_00494A78 = D_002BBDF8;
            }
            if ((u32)(D_002BBDF8 - D_00494A78) > 120) {
                func_00105fc8();
            }
        } else {
            u64 *q = &D_002A6658;
            *q = rgba(((Col *)&D_002BC070));
            func_00106b18(D_002A6890);
        }
        if (D_002A6B80 != 0) {
            D_002A6970[9] = 0x180FEFEFE;
            D_002A6970[10] = 0x174007000;
            D_002A6970[11] = 0x190009000;
            func_00106b18(D_002A69D0);
        }
        break;
    case 2: {
        s32 v, k, w, x, y;
        v = func_001110d0();
        func_0010fee8(v, 448);
        func_00106b18(D_002A6580);
        switch (v) {
        case 512: k = 9; break;
        case 640: k = 10; break;
        default: k = 1; break;
        }
        w = v / 64;
        D_002A68A0[4] = ((u64)w << 16) | 0x1000000;
        D_002A68A0[6] = ((u64)w << 14) | ((u64)k << 26) | 0x2008000240101180;
        x = v * 16;
        y = x + 0x7000;
        D_002A68A0[22] = (u64)(x + 8) | 0x1c080000;
        D_002A68A0[23] = (u64)y | 0xFFFFFFFE90000000;
        func_00106b18(D_002A6960);
        if (D_002A6B80 != 0) {
            D_002A6970[9] = 0x180FEFEFE;
            D_002A6970[10] = 0x174007000;
            D_002A6970[11] = (u64)y | 0x190000000;
            func_00106b18(D_002A69D0);
        }
        break;
    }
    }
    func_00106b18(D_002A65C0);
}
#undef func_00106b18

/* func_001063c8 (from auto/text_00100000_2.c). */
extern s32 D_002BC0BC;
s32 func_001063c8(void) {
    s32 var_a1;

    var_a1 = 0;
    if (((*(s32 *)&D_002BC070) == 0) || (D_002BC0BC == 0x80)) {
        var_a1 = 1;
    }
    return var_a1;
}

/* func_001063f8 (from hand/text_00100000_h1.c). */
extern s32 D_002A6204;
s32 func_001063f8(void) {
    if ((*(s32 *)&D_002BC070) == 128 && D_002BC0BC == 0 && D_002A6204 == 0) return 0;
    return 1;
}

/* func_00106438 (from auto/text_00100000_9.c). */
M2C_UNK func_001091f8(void *, void *);
void func_00106438(s32 arg0) {
    void *temp_a0;
    void *temp_a0_2;

    temp_a0 = arg0 + 0x10;
    temp_a0_2 = temp_a0 + M2C_FIELD(temp_a0, u16 *, 0xC);
    func_001091f8(temp_a0_2, temp_a0_2 + M2C_FIELD(temp_a0, s32 *, 8));
}

/* func_00106460 (from hand/text_00100000_h51.c). */
extern f32 D_00494A88;
extern u64 D_002A6AB0[];
extern u64 D_002A6A40[];
extern u64 D_002A6B70[];
extern u64 D_002A6AA0[];
extern u8 D_002C13A0[];
#define XYZ(x, y, z) ((u64)(x) | ((u64)(y) << 16) | ((u64)(z) << 32))
#define func_00106438 ((void (*)(void *)) func_00106438)
s32 func_00106460(void) {
    s32 n;

    if (D_002BC740 == 1) {
        D_00494A88 = 0.0f;
        return 4;
    }
    if (D_00494A88 == 0.0f) return 4;
    func_00106b18(D_002A6A40);
    D_00494A8C += D_00494A88;
    n = 800.0f / D_00494A8C;
    if (n <= D_00494A84) n = D_00494A84;
    if (D_00494A8C < 0.0f) n = 800;
    func_00106438(D_002C13A0);
    D_002A6AB0[21] = XYZ(D_00494A7C - n * 16, D_00494A80 - n * 28, 0xfffffffe);
    D_002A6AB0[23] = XYZ(D_00494A7C + n * 16, D_00494A80 + n * 28, 0xfffffffe);
    func_00106b18(D_002A6B70);
    func_00106b18(D_002A6AA0);
    return 0;
}
#undef func_00106438
#undef XYZ

/* func_001065a8 (from auto/text_00100000_4.c). */
s32 func_0011ef10(s32, s32);
void func_001065a8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00494A7C = (arg2 * 0x10) + 0x7000;
    D_00494A80 = (arg3 * 0x10) + 0x7400;
    D_00494A8C = 1.0f;
    D_00494A88 = (800.0f / (f32) arg1) / (f32) (arg0 - 1);
    D_00494A84 = arg1;
    func_0011ef10(0x2E646, (s32) &func_00106460);
}

/* func_00106648 (from hand/text_00100000_h28.c). */
#define func_0011ef10 ((s32 (*)(s32, void *)) func_0011ef10)
void func_00106648(s32 n, s32 m, s32 x, s32 y) {
    f32 t;

    D_00494A7C = x * 16 + 0x7000;
    D_00494A80 = y * 16 + 0x7400;
    t = 800.0f / (f32)m / (f32)(n - 1);
    D_00494A88 = -t;
    D_00494A8C = (f32)n * t + 1.0f;
    D_00494A84 = m;

    func_0011ef10(190022, func_00106460);
}
#undef func_0011ef10

/* func_001066f8 (from auto/text_00100000_2.c). */
extern s32 D_00494A88_001066f8 __asm__("D_00494A88");
#define D_00494A88 D_00494A88_001066f8
void func_001066f8(void) {
    D_00494A88 = 0;
}
#undef D_00494A88

/* func_00106708 (from auto/text_00100000_9.c). */
extern f32 D_002BBDFC;
s32 func_00106708(void *arg0) {
    f32 temp_f2;
    s32 temp_f1;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) + D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (M2C_FIELD(arg0, f32 *, 0x18) <= temp_f2) {
        D_002BC070[0] = 0x80;
        D_002BC070[3] = 0x80;
        D_002BC070[2] = 0x80;
        D_002BC070[1] = 0x80;
        return 4;
    }
    temp_f1 = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    D_002BC070[0] = temp_f1;
    D_002BC070[3] = temp_f1;
    D_002BC070[2] = temp_f1;
    D_002BC070[1] = temp_f1;
    return 0;
}

/* func_00106780 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; s32 w16; f32 f20; f32 f24; } Fade2;
void func_00106900(void);
void func_00106910(void);
void *func_0011f090(void *, s32, void *);
void func_00106780(s32 n) {
    Fade2 *o;
    func_00106900();
    func_00106910();
    o = func_0011f090(D_002BC720, 0, func_00106708);
    if (o) {
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

/* func_00106810 (from auto/text_00100000_9.c). */
s32 func_00106810(void *arg0) {
    f32 temp_f2;
    s32 temp_f1;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) - D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (temp_f2 <= 0.0f) {
        D_002BC070[0] = 0;
        D_002BC070[3] = 0;
        D_002BC070[2] = 0;
        D_002BC070[1] = 0;
        return 4;
    }
    temp_f1 = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    D_002BC070[0] = temp_f1;
    D_002BC070[3] = temp_f1;
    D_002BC070[2] = temp_f1;
    D_002BC070[1] = temp_f1;
    return 0;
}

/* func_00106880 (from hand/text_00100000_h1.c). */
typedef struct { u8 pad[16]; f32 f16; f32 f20; f32 f24; } Fade;
void func_00106880(s32 n) {
    Fade *o = func_0011f090(D_002BC720, 0, func_00106810);
    if (o) {
        o->f16 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

/* func_00106900 (from auto/text_00100000.c). */
extern s32 D_002B647C;
void func_00106900(void) {
    D_002B647C = 0;
}

/* func_00106910 (from auto/text_00100000_2.c). */
extern s32 D_002B6480;
void func_00106910(void) {
    D_002B6480 = 0;
}

/* func_00106920 (from auto/text_00100000_2.c). */
s32 func_00106920(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) + D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (M2C_FIELD(arg0, f32 *, 0x18) <= temp_f2) {
        D_002BC0BC = 0x80;
        return 4;
    }
    D_002BC0BC = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    return 0;
}

/* func_00106978 (from hand/text_00100000_h1.c). */
void func_00106978(s32 n) {
    Fade2 *o;
    func_00106900();
    func_00106910();
    o = func_0011f090(D_002BC720, 0, func_00106920);
    if (o) {
        o->w16 = 0;
        o->f24 = (f32)(n * 2);
        if (n == 0) n = 1;
        o->f20 = 128.0f / (f32)(n * 2);
    }
}

/* func_00106a08 (from auto/text_00100000_2.c). */
s32 func_00106a08(void *arg0) {
    f32 temp_f2;

    temp_f2 = M2C_FIELD(arg0, f32 *, 0x10) - D_002BBDFC;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f2;
    if (temp_f2 <= 0.0f) {
        D_002BC0BC = 0;
        return 4;
    }
    D_002BC0BC = (s32) (M2C_FIELD(arg0, f32 *, 0x14) * temp_f2);
    return 0;
}

/* func_00106a58 (from hand/text_00100000_h28.c). */
typedef struct { u8 pad[0x10]; f32 f10, f14; u8 pad18[4]; u8 b1c, b1d, b1e; } Task;
#define func_0011f090 ((Task *(*)(void *, s32, void (*)(void))) func_0011f090)
void func_00106a58(s32 n) {
    Task *t;
    if (D_002B647C == 1 || D_002B6480 == 1) {
        func_00106780(n);
        func_00106900();
        func_00106910();
        return;
    }
    if ((t = func_0011f090(D_002BC720, 0, func_00106a08)) != NULL) {
        t->f10 = n * 2;
        if (n == 0) n = 1;
        t->f14 = 128.0f / (f32)(n * 2);
    }

}
#undef func_0011f090

