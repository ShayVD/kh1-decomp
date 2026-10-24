/* Likely the summons (a guess from the code): func_0013a910 asks whether
 * summon n is allowed (the leader's class flag, MP against the tuning table,
 * the world / room), the state D_0052AE54 loads the summon's two files named
 * from D_00304B00[D_0052AE50] (func_0013b3d0; code at D_00F20000), the
 * summon object D_0052AE38 of class 40 (func_0013bf20 registers it), the
 * party swap and its end (func_0013bb60, func_0013bd08), the fade
 * func_0013ab30. Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/thread.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00304B6C.h"
#include "data/types/text_00130000_h32.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_00350CE0.h"
#include "data/types/text_00130000_h32_p.h"
#include "data/pieces/D_00304AD8.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2790.h"

/* func_0013a910 (from hand/text_00130000_h55.c). */
extern u32 D_002C5958;
typedef struct { u8 pad[0x44]; s32 x44; } W55Stat;
typedef struct Actor_3a910 {
    u8 pad00[0x6c];
    W55Stat *x6c;
    s32 x70;
} W55Pl;
typedef struct { u64 x0; u8 padx[0x18]; } W55Ent32;
extern s32 D_002BC128;
extern s32 D_002BC130;
s32 func_00153d78(W55Pl *p);
s32 func_0012f040(W55Pl *p, s32 a);
extern W55Pl *D_002E26A0_3a910[3] __asm__("D_002E26A0");
#define D_002E26A0 D_002E26A0_3a910
s32 func_0013a910(s32 n) {
    W55Pl **pp;
    s32 i;
    if ((D_002E31A8 >> 2) & 1) return 0;
    if (!((((W55Ent32 *)&D_00350D88)[D_002E26A0[0]->x70].x0 >> 7) & 1)) return 0;
    if ((D_002C5958 >> 16) & 1) return 0;
    if (D_002E26A0[0]->x6c->x44 < (*(u8 **)&D_00308CDC)[n * 8 + 0x98]) return 0;
    if (!(D_002C5958 & 1)) return 0;
    if (D_002BC128 == 3 && D_002BC130 == 20) return 1;
    if (D_00304B84 & (1 << n)) return 0;
    for (i = 0; i < 3; i++) {
        if (!D_002E26A0[i] || func_00153d78(D_002E26A0[i]) || !func_0012f040(D_002E26A0[i], -1)) return 0;
    }
    return 1;
}
#undef D_002E26A0

/* func_0013aa60 (from hand/text_00130000_h6.c). */
extern f32 D_00304B7C;
s32 func_0013aa60(void) {
    if (!(((*(u32 *)&D_00304B78) >> 3) & 1)) {
        return 1;
    }
    return D_00304B7C <= 0.0f;
}

/* func_0013aaa0 (from auto/text_00130000.c). */
void func_0013aaa0(void) {
    (*(u32 *)&D_00304B78) &= ~8;
}

/* func_0013aac0 (from auto/text_00130000_4.c). */
extern void *D_0052AE5C;
void func_00131498(s32, s32);
void func_0013aac0(s32 arg0) {
    s32 temp_v1;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0) {
        temp_v1 = M2C_FIELD(D_0052AE5C, s32 *, 8);
        if ((M2C_FIELD(D_0052AE5C, s32 *, 0xC) - temp_v1) > 0) {
            func_00131498(arg0, (s32) (D_0052AE5C + temp_v1));
        }
    }
}

/* func_0013ab08 (from auto/text_00130000_2.c). */
void func_0013ab08(void) {
    if ((*(M2C_UNK (*(*))())&D_00304B6C) != NULL) {
        (*(M2C_UNK (*(*))())&D_00304B6C)();
    }
}

/* func_0013ab30 (from hand/text_00130000_h32.c). */
extern f32 D_002BBDFC;
typedef struct {
    u8 pad00[0x30];
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
} W32Spr;
typedef struct {
    u16 flags;
    u8 pad02[0x10 - 0x2];
    f32 x10;
} W32Fade;
W32Spr *D_0052AD00 ALIGNED(16);  /* D_0052AD00, D_00304B40 and D_00304B44 moved from hand/text_00130000_h32.c (session 53) */
W32Spr *func_001226f0(s32 a, s32 b, s32 c);
void func_00122768(W32Spr *s);
void func_00100ae0(void);
s32 func_0013ab30(W32Fade *f) {
    if (f->flags & 0x10) {
        D_0052AD00 = func_001226f0(1, 9, 0);
        D_0052AD00->x3c = 1.0f;
        f->x10 = 50.0f;
    }
    f->x10 -= D_002BBDFC;
    if (f->x10 <= 0.0f) {
        func_00122768(D_0052AD00);
        func_00100ae0();
        return 4;
    }
    D_0052AD00->x30 = D_0052AD00->x34 = D_0052AD00->x38 = f->x10 / 50.0f;
    return 0;
}

/* func_0013abf8 (from hand/text_00130000_b03.c). */
extern f32 D_00304B20[4];
extern f32 D_00304B30[4];
f32 D_0052AD04 ALIGNED(4);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD08 ALIGNED(8);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD0C ALIGNED(4);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD10[4] ALIGNED(16);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD20[4] ALIGNED(16);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD30[4] ALIGNED(16);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD40[4] ALIGNED(16);  /* moved from hand/text_00130000_b03.c (session 53) */
f32 D_0052AD50 ALIGNED(16);  /* moved from hand/text_00130000_b03.c (session 53) */
extern u8 *D_0052AE38;
f32 atan2f(f32, f32);
f32 cosf(f32);
f32 func_00120bf8(f32 *);
f32 func_00120c18(f32 *);
f32 func_00120c88(f32);
void func_00121fc4(f32 *, f32 *);
void func_001625c8(void *, f32 *);
f32 func_00176850(void);
s32 func_0013abf8(u16 *o) {
    f32 a[4];
    f32 b[4];
    f32 rm[16];
    f32 m[16];
    f32 t, r;

    if (!((D_002C5958 >> 20) & 1)) return 4;
    if (*o & 0x10) {
        func_001625c8(D_0052AE38 + 0xd0, m);
        D_002E2780.w = D_002E2790.w = 1.0f;
        PlatVu0ApplyMatrix(D_0052AD20, m, &D_002E2780.x);
        PlatVu0ApplyMatrix(D_0052AD30, m, &D_002E2790.x);
        PlatVu0SubVector(D_0052AD10, D_00304B30, D_0052AD20);
        D_0052AD08 = func_00120bf8(D_0052AD10);
        PlatVu0SubVector(D_0052AD10, D_0052AD30, D_0052AD20);
        PlatVu0Normalize(D_0052AD10, D_0052AD10);
        PlatVu0ScaleVector(D_0052AD10, D_0052AD10, D_0052AD08);
        PlatVu0AddVector(D_0052AD30, D_0052AD10, D_0052AD20);
        PlatVu0SubVector(D_0052AD40, D_0052AD20, D_0052AD30);
        D_0052AD40[1] = 0.0f;
        func_00121fc4(D_0052AD40, D_0052AD40);
        D_0052AD08 = D_0052AD40[3];
        D_0052AD40[3] = 1.0f;
        PlatVu0SubVector(D_0052AD10, D_00304B20, D_00304B30);
        D_0052AD0C = func_00120c18(D_0052AD10) - D_0052AD08;
        r = atan2f(D_0052AD20[0] - D_0052AD30[0], D_0052AD20[2] - D_0052AD30[2]);
        D_0052AD04 = func_00120c88(atan2f(D_00304B20[0] - D_00304B30[0], D_00304B20[2] - D_00304B30[2]) - r);
        if (func_00176850() < 0.5f) {
            if (D_0052AD04 < 0.0f) {
                D_0052AD04 = D_0052AD04 + 6.2831855f;
            } else {
                D_0052AD04 = D_0052AD04 - 6.2831855f;
            }
        }
        if (func_00176850() < 0.5f) {
            D_0052AD04 = D_0052AD04 + 0.5235987901687622f;
        } else {
            D_0052AD04 = D_0052AD04 - 0.5235987901687622f;
        }
        D_0052AD50 = 40.0f;
    }
    D_0052AD50 -= D_002BBDFC;
    t = D_0052AD50 / 40.0f;
    if (t < 0.0f) t = 0.0f;
    t = (cosf(t * 3.1415928f) + 1.0f) * 0.5f;
    PlatVu0InterVector(b, D_00304B30, D_0052AD30, t);
    PlatVu0RotMatrixY(rm, D_002C58D0[0], func_00120c88(D_0052AD04 * t));
    PlatVu0ApplyMatrix(D_0052AD10, rm, D_0052AD40);
    PlatVu0ScaleVector(D_0052AD10, D_0052AD10, D_0052AD08 + D_0052AD0C * t);
    PlatVu0AddVector(a, b, D_0052AD10);
    a[3] = 1.0f;
    b[3] = 1.0f;
    a[1] = D_00304B20[1] * t + D_0052AD20[1] * (1.0f - t);
    PlatVu0ApplyMatrix(&D_002E2780.x, D_0052AE38 + 0xd0, a);
    PlatVu0ApplyMatrix(&D_002E2790.x, D_0052AE38 + 0xd0, b);
    return 0;
}

/* func_0013b1a0 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
} W6Blob;
extern s32 D_0052AE54;
void func_00155be0(void *p);
void func_001763f0(void *p);
extern W6Blob *D_0052AE5C_0013b1a0 __asm__("D_0052AE5C");
#define D_0052AE5C D_0052AE5C_0013b1a0
void func_0013b1a0(void) {
    if (D_0052AE5C->x8 - D_0052AE5C->x4 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x4);
    }
    if (D_0052AE5C->xc - D_0052AE5C->x8 > 0) {
        func_00155be0((u8 *)D_0052AE5C + D_0052AE5C->x8);
    }
    if (D_0052AE5C->x10 - D_0052AE5C->xc > 0) {
        func_001763f0((u8 *)D_0052AE5C + D_0052AE5C->xc);
    }
    PlatFlushCache(2);
    D_0052AE54 = 4;
}
#undef D_0052AE5C

/* func_0013b3d0 (from hand/text_00130000_h32.c). */
extern s32 D_00304B00[];
extern u8 D_0048DCA0[];
s32 D_00304B40 ALIGNED(16) = (s32)D_0048DCA0;
extern u8 D_0048DCA8[];
s32 D_00304B44 ALIGNED(4) = (s32)D_0048DCA8;
extern char D_0048DCB0[];
void D_00F20000(s32 a, s32 b);
s32 func_001ecfd8(void);
void func_00157668(void);
s32 sprintf(char *buf, const char *fmt, ...);
s32 func_00120748(char *name, void *dst, void (*cb)(void), s32 d);
void func_0013b238(void);
void func_0011ef10(s32 a, void (*f)(void));
s32 func_0013b3d0(void) {
    char buf[32];
    if (D_0052AE54 != 2 || func_001ecfd8()) return 0;
    func_00157668();
    D_0052AE54 = 3;
    sprintf(buf, D_0048DCB0, D_00304B00[D_0052AE50], D_00304B40);
    func_00120748(buf, D_0052AE5C, 0, 0);
    sprintf(buf, D_0048DCB0, D_00304B00[D_0052AE50], D_00304B44);
    func_00120748(buf, (void *)D_00F20000, func_0013b1a0, 0);
    func_0011ef10(0xB798, func_0013b238);
    return 1;
}

/* func_0013b8f0 (from hand/text_00130000_h6.c). */
extern u32 D_002C5978;
void func_0013a810(void);
#define D_00F20000 ((s32 (*)(s32 a, s32 b)) D_00F20000)
s32 func_0013b8f0(void) {
    if (((D_002C5978 >> 8) & 3) != 1) {
        if (D_00F20000(1, 0) != 0) {
            return 0;
        }
    }
    func_0013a810();
    D_002C5958 &= ~0x2000;
    (*(u32 *)&D_00304B78) = 0;
    return 1;
}
#undef D_00F20000

/* func_0013b958 (from hand/text_00130000_h6.c). */
u8 D_0052AD58[0x10] ALIGNED(8);  /* moved from hand/text_00130000_h6.c (session 53) */
extern u8 D_00304B48[];
void func_0013bde8();
void func_0011f130(void *a, s32 b);
s32 func_0013be00(void *a);
#define func_0013bde8 ((void (*)(void *a, void *b, s32 n)) func_0013bde8)
s32 func_0013b958(u16 *p) {
    if (*p & 0x10) {
        func_0013bde8(D_0052AD58, D_00304B48, 4);
    }
    func_0011f130(D_0052AD68, 0);
    return func_0013be00(D_0052AD58) ? 0 : 4;
}
#undef func_0013bde8

/* func_0013b9c8 (from auto/text_00130000_16.c). */
extern void *D_0052AE58;
void func_00132260(s32, s32, s32);
void func_0013b9c8(s32 arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(D_0052AE58, s32 *, 8);
    func_00132260(arg0, (s32) (D_0052AE58 + M2C_FIELD(D_0052AE58, s32 *, 4)), (s32) (((M2C_FIELD(D_0052AE58, s32 *, 0xC) - temp_v1) <= 0) ? NULL : (D_0052AE58 + temp_v1)));
}

/* func_0013ba08 (from auto/text_00130000_8.c). */
void func_0013ba08(void) {
    D_0052AE54 = 2;
}

/* func_0013ba18 (from hand/text_00130000_h32.c). */
typedef struct { s32 x0; s32 off[9]; } W32Hdr;
void func_00155b70(void *p);
void func_00146928(s32 a);
void func_00146a68(void *p, s32 a, void (*cb)(void), s32 b);
void func_0013ba18(s32 size, s32 b, W32Hdr *h) {
    s32 *st;
    if (h->off[1] - h->off[0] > 0) func_00155b70((u8 *)h + h->off[0]);
    if (h->off[2] - h->off[1] > 0) func_00155be0((u8 *)h + h->off[1]);
    if (h->off[3] - h->off[2] > 0) func_00155be0((u8 *)h + h->off[2]);
    if (h->off[5] - h->off[4] > 0) func_001763f0((u8 *)h + h->off[4]);
    st = &D_0052AE54;
    *st = 1;
    if (h->off[7] - h->off[6] > 0) {
        func_00146928(-7);
        func_00146a68((u8 *)h + h->off[6], -7, func_0013ba08, 0);
    } else {
        *st = 2;
    }
    D_0052AE5C = (void *)((((u32)h + size + 0x7F) >> 7) << 7);
}

/* func_0013bb60 (from hand/text_00130000_h55.c). */
typedef W55Bf_304b78 W55Bf;
extern u8 *D_00304B70;
extern f32 D_00304B80;
extern u8 D_0048DCB8[];
s32 D_00304B68 ALIGNED(8) = (s32)D_0048DCB8;  /* D_00304B68 and D_0052AD78 moved from hand/text_00130000_h55.c (session 53) */
u8 D_0052AD78[0xc0] ALIGNED(8);
f32 func_0013bb20(void);
void func_00141540(s32 a, s32 b);
void func_001575b0(s32 a);
void *func_001559f0(s32 a, s32 b);
void func_0011efa8(void *a, void *b, s32 c, s32 d);
extern s32 D_0052AE38_0013bb60 __asm__("D_0052AE38");
#define D_0052AE38 D_0052AE38_0013bb60
#define func_00120748 ((s32 (*)(char *name, void *dst, void (*cb)(), s32 d)) func_00120748)
#define func_0011ef10 ((void (*)(s32 a, void (*f)())) func_0011ef10)
void func_0013bb60(s32 o, s32 n) {
    char buf[32];
    u32 *fl = &D_002C5958;
    W55Bf *bf = &D_00304B78;
    u32 *msk = &D_00304B84;
    u8 **lv = ((u8 **)&D_00308CDC);
    f32 *fp;
    void **hp;
    *fl |= 0x102000;
    bf->lv = n;
    bf->on = 1;
    D_00304B70 = *lv + n * 8 + 0x98;
    *msk |= 1 << n;
    fp = &D_00304B7C;
    *fp = D_00304B80 = func_0013bb20();
    func_00141540(o, -(*lv)[n * 8 + 0x98]);
    D_0052AE38 = o;
    D_0052AE50 = n;
    func_001575b0(1);
    func_001575b0(2);
    func_001575b0(3);
    D_0052AE54 = 0;
    hp = &D_0052AE58;
    *hp = func_001559f0(52, 12);
    sprintf(buf, D_0048DCB0, D_00304B00[n], D_00304B68);
    func_00120748(buf, *hp, func_0013ba18, 0);
    func_0011efa8(D_0052AD68, D_0052AD78, 24, 8);
    func_0011ef10(0xcb20, func_0013b958);
}
#undef D_0052AE38
#undef func_00120748
#undef func_0011ef10

/* func_0013bd08 (from hand/text_00130000_h32.c). */
void func_002414a8(s32 a, s32 b);
void func_0011ef58(void (*f)(void));
void func_00133708(void);
void func_00100ab0(void);
void func_0013bd08(void) {
    u32 *f = &D_002C5958;
    u32 *g;
    if ((*f >> 13) & 1) {
        D_00F20000(2, 0);
        func_0011ef58(func_0013b958);
        func_002414a8(0, 1);
        func_002414a8(1, 2);
        func_002414a8(2, 2);
    }
    if (*f & 0x104000) {
        func_00133708();
        func_00100ab0();
    }
    g = ((u32 *)&D_00304B78);
    *f &= ~0x2000;
    *f &= ~0x4000;
    *f &= ~0x100000;
    *g &= ~8;
    D_00304B84 = 0;
}

/* func_0013bde8 (from auto/text_00130000_4.c). */
void func_0013bde8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
}

/* func_0013bef0 (from auto/text_00130000_8.c). */
M2C_UNK func_00137688(s32, f32);
f32 func_001376e8();
void func_0013bef0(s32 arg0) {
    func_00137688(arg0, func_001376e8());
}

/* func_0013bf20 (from hand/text_00130000_h6.c). */
void func_0014f778(void);
void func_0014f828(void);
void func_0014f830(s32 a, s32 b, s32 c, s32 d, void (*e)(void), void (*f)(void), void (*g)(void), s32 h, s32 i);
void func_0013bf20(void) {
    func_0014f830(40, 256, 0, 0, func_0013bef0, func_0014f778, func_0014f828, 0, 0);
}

