/* An object's motion: the motion table lookups (func_00130070 maps a motion
 * id through the object's table), the motion change every class calls
 * (func_00130340, func_00130398(o, motion, blend), func_00130578), the blend
 * and the per-frame motion update of the bone matrices (func_00130660,
 * func_00130f18). Flag mode: nostrict (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002E3170.h"
#include "data/pieces/D_002E319C.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E31A0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/pieces/D_002E2780.h"
#include "data/types/nostrict_text_00120000_s6_05_p.h"
#include "data/pieces/D_002E3168.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E31A4.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002C58A0.h"
#include "m2c.h"

/* func_00130398 (from hand/nostrict/text_00120000_s6_05.c). */
extern f32 D_002BBDFC;
typedef struct Ob {
    u8 pad[6];
    u8 f6;
    u8 pad7[0x160 - 7];
    u32 b0:1;
    u32 b1:1;
    u32 b2:30;
    s32 f164;
    s32 f168;
    f32 f16c;
    u8 pad170[8];
    s32 f178;
    u8 pad17c[0x1d4 - 0x17c];
    s32 *f1d4;
    u64 pad1d8;
} Ob;
extern s32 func_00130190(Ob *, s32);
extern s32 func_00167698(s32);
extern s32 func_00130270(Ob *, s32);
extern s32 func_001302d0(Ob *, s32, f32, f32);
void func_00130398(Ob *o, s32 a1, f32 t) {
    s32 r, k, v;
    f32 f, a, b;
    o->f178 = 0;
    r = func_00130190(o, a1);
    if (!(r & 0x200000) && (r & 0xffff) == o->f168) return;
    if (o->f6 == 3) {
        k = (u16)a1;
        if (o->b1) {
            v = o->f164;
            if ((u32)(v - 1) < 2 || v == 172 || v == 173) {
                if ((u32)(k - 1) < 2 || k == 172 || k == 173) {
                    a = func_00167698(o->f1d4[o->f168]);
                    b = func_00167698(o->f1d4[r]);
                    f = b * ((o->f16c + D_002BBDFC + t) / a);
                    while (b <= f) f -= b;
                    goto call;
                }
            }
        }
        if (k == 1 && o->f164 == 0) f = t * 0.5f;
        else f = 0.0f;
    } else {
        f = 0.0f;
    }
call:
    func_001302d0(o, func_00130270(o, a1), f, t);
    o->b0 = 1;
}

/* func_00130598 (from hand/nostrict/text_00120000_h31.c). */
typedef struct { u8 pad0[0x40]; f32 f40[4]; u8 pad50[0x15c - 0x50]; s32 f15c; u8 pad160[0x220 - 0x160]; f32 f220[4]; u8 pad230[0x370 - 0x230]; u64 f370; } E598;
extern void func_001219c8(f32 *, f32 *, f32 *);
extern void func_00166570(f32 *, s32, f32);
void func_00130598(E598 *e, f32 *m, f32 a, f32 b) {
    f32 v[4];
    PlatVu0ScaleVectorXYZ(v, e->f220, b);
    v[3] = 0.0f;
    PlatVu0ApplyMatrix(v, m, v);
    if ((s32)(e->f370 >> 45) & 1) func_001219c8(v, v, e->f40);
    PlatVu0SubVector(m + 12, m + 12, v);
    m[15] = 1.0f;
    func_00166570(m, e->f15c, a);
}

/* func_00130660 (from hand/nostrict/text_00130660_s7_w37.c). */
typedef f32 C01Mat[4][4];
typedef struct { u8 pad[0x4c]; u16 x4c; } C01Sub130;
typedef struct {
    u32 flags0;
    u8 pad004[0x10 - 0x4];
    f32 x10[4];
    u8 pad020[0x50 - 0x20];
    f32 x50[4];
    u8 pad060[0xd0 - 0x60];
    C01Mat xd0;
    u8 pad110[0x130 - 0x110];
    C01Sub130 *x130;
    u8 pad134[0x15c - 0x134];
    s32 x15c;
    u32 b0 : 1;
    u32 b1 : 1;
    u32 b2 : 1;
    u32 b3 : 1;
    u32 b4 : 1;
    u32 b5 : 1;
    u32 b6 : 1;
    u32 b7 : 1;
    u32 b8 : 1;
    u32 b9 : 1;
    u32 b10 : 1;
    u32 b11 : 1;
    u32 rest : 20;
    s32 x164;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    s32 x178;
    u8 pad17c[0x180 - 0x17c];
    f32 f180;
    u8 pad184[0x1cc - 0x184];
    s32 x1cc;
    u8 pad1d0[4];
    s32 *x1d4;
    u8 pad1d8[0x1f0 - 0x1d8];
    u8 x1f0[0x10];
    f32 x200[4];
    f32 x210[4];
    u8 pad220[0x230 - 0x220];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
    f32 f288;
    f32 f28c;
    f32 f290;
} __attribute__((aligned(8))) C01Obj3;
void func_001655e0(C01Mat, s32, f32, s32);
typedef struct {
    u8 pad0[0x50];
    f32 x50[4];
    u8 pad60[0x15c - 0x60];
    s32 x15c;
    u64 flags;
    s32 x168;
    f32 f16c;
    f32 f170;
    f32 f174;
    u8 pad178[0x1d4 - 0x178];
    s32 *x1d4;
    u8 pad1d8[0x220 - 0x1d8];
    f32 x220[4];
    C01Mat x230;
    f32 x270[4];
    f32 f280;
    f32 f284;
} __attribute__((aligned(8))) O660;
void func_00166248(C01Mat, s32, s32, f32);
#ifdef KH1_PS2 /* portability rule 11: the EE passes the floats in their own registers */
void func_00165cf8(C01Mat, s32, f32, s32);
#else
void func_00165cf8(C01Mat, s32, s32, f32);
#define func_00165cf8(a1, a2, a3, a4) (func_00165cf8)(a1, a2, a4, a3)
#endif
void func_001676d8(s32, f32 *);
void func_001675c0(s32);
void func_00130648(C01Obj3 *);
#define func_00130598 ((void (*)(C01Obj3 *, C01Mat, f32, f32)) func_00130598)
/* func_00130660: closest draft (7 words off: f20/f21 swapped), context for func_00130f18. */
void func_00130660(C01Obj3 *a, C01Mat m, s32 idx, f32 d, f32 e) {
    O660 *o = (O660 *)a;
    f32 v[4];
    C01Mat t;
    f32 k = D_002BBDFC * o->f284;
    s32 s = o->x1d4[idx];
    if (((s32)(o->flags >> 1) & 1) && k < e) {
        if (0.0f < o->f170) {
            func_00166248(m, o->x15c, s, d);
        } else {
            PlatVu0CopyMatrix(t, m);
            if ((s32)(o->flags >> 12) & 1) {
                PlatVu0CopyVector(t[3], o->x50);
                t[3][3] = 1.0f;
            }
            func_00165cf8(t, o->x15c, d, s);
        }
        func_001676d8(o->x15c, v);
        v[3] = 0;
        PlatVu0TransposeMatrix(t, m);
        PlatVu0ApplyMatrix(o->x270, t, v);
        o->x270[3] = 0;
        o->f170 = e;
        o->f174 = k;
        PlatVu0CopyVector(v, o->x220);
        v[3] = 0;
        PlatVu0ApplyMatrix(v, o->x230, v);
        PlatVu0AddVector(m[3], m[3], v);
        func_00130598(a, m, k / e, 1.0f - k / e);
    } else {
        { f32 c = o->f170;
        k = 0.0f;
        if (k < c) func_001675c0(o->x15c); }
        o->f170 = k;
        func_001655e0(m, o->x15c, d, s);
        o->f280 = func_00167698(s);
        if (!((s32)(o->flags >> 6) & 1)) func_00130648(a);
    }
    if (s) o->flags |= 2;
    o->x168 = idx;
    o->f16c = d;
}
#undef func_00130598

/* func_00130e48 (from hand/nostrict/text_00130000.c). */
M2C_UNK func_00130c28(void *, f32, f32);
f32 func_00130d20();
f32 func_00130dd0(void *);
#define func_001655e0 ((M2C_UNK (*)(s32, s32, f32, s32)) func_001655e0)
s32 func_00130e48(void *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f1;
    f32 temp_f20;
    f32 var_f0;
    s32 var_v0;

    var_f0 = func_00130d20(arg0);
    if ((var_f0 >= 0.0f) || (var_f0 = func_00130dd0(arg0), var_v0 = 0, (var_f0 >= 0.0f))) {
        temp_f1 = M2C_FIELD(arg0, f32 *, 0x280);
        temp_f20 = temp_f1 * var_f0;
        temp_f12 = M2C_FIELD(arg0, f32 *, 0x16C);
        temp_f0 = temp_f20 - temp_f12;
        if (!(M2C_FIELD(arg0, s32 *, 0x160) & 1) && (temp_f0 > 0.0f) && (temp_f0 < temp_f1)) {
            func_00130c28(arg0, temp_f12, temp_f20);
        }
        M2C_FIELD(arg0, f32 *, 0x16C) = temp_f20;
        func_001655e0(arg1, M2C_FIELD(arg0, s32 *, 0x15C), temp_f20, *(M2C_UNK *)((s32) ((M2C_FIELD(arg0, s32 *, 0x168) * 4)) + (s32) (M2C_FIELD(arg0, s32 *, 0x1D4))));
        var_v0 = 1;
    }
    return var_v0;
}
#undef func_001655e0

/* func_00130f18 (from hand/nostrict/text_00120000_s6_05.c). */
extern void *D_002E31E8;
s32 func_0012ffd0(C01Obj3 *);
void func_00167688(s32, s32, void *);
void func_00130898(C01Obj3 *, C01Mat);
void func_00130210(C01Obj3 *, s32);
s32 func_00167680(s32);
void func_001752a0(s32, void *);
void func_001676b0(s32, f32 *);
void func_00167d70(s32, f32);
#define func_00130e48 ((s32 (*)(C01Obj3 *, C01Mat)) func_00130e48)
#define func_00130c28 ((void (*)(C01Obj3 *, f32, f32)) func_00130c28)
#define func_00130598 ((void (*)(C01Obj3 *, C01Mat, f32, f32)) func_00130598)
void func_00130f18(C01Obj3 *o, f32 dt) {
    f32 a[4];
    f32 b[4];
    C01Mat m;
    f32 *t3;
    s32 fl;
    s32 has4;
    s32 did;
    s32 old;
    f32 d;
    f32 n;
    f32 h;

    D_002E31E8 = (u8 *)o->x130 + 0x68;
    if (o->b4) return;
    PlatVu0CopyMatrix(m, o->xd0);
    if (o->b2) {
        t3 = o->x210;
        PlatVu0SubVector(m[3], m[3], t3);
        m[3][3] = 1.0f;
    } else {
        t3 = o->x210;
    }
    PlatVu0CopyVector(a, m[3]);
    fl = o->x1cc;
    if ((o->flags0 & 0x10) || o->b11) fl &= ~1;
    if (o->x130->x4c == 507) {
        has4 = fl & 4;
        fl &= ~4;
    } else {
        has4 = 0;
    }
    did = 0;
    func_00167688(o->x15c, func_0012ffd0(o) ? fl | 0x20 : fl, o->x1f0);
    o->b8 = 0;
    if (((s32 *)o)[0x160 / 4] & 1) {
        func_00130898(o, m);
        did = 1;
        func_00130e48(o, m);
        o->b0 = 0;
        o->b8 = 1;
    } else {
        dt *= o->f284;
        if (o->f170 > 0.0f) {
            n = o->f174 + dt;
            d = n - o->f170;
            o->f174 = n;
            if (!(d < 0.0f)) {
                func_00130c28(o, o->f16c, o->f16c + d);
                func_00130660(o, m, o->x168, o->f16c + d, 0.0f);
                func_00130210(o, o->x164);
            } else {
                h = n / o->f170;
                func_00130598(o, m, h, 1.0f - h);
            }
        } else if (!func_00130e48(o, m)) {
            h = o->f16c;
            n = h + dt;
            o->f16c = n;
            func_00130c28(o, h, n < o->f280 ? n : o->f280);
            d = o->f16c - o->f28c;
            if (d < 0.0f) {
                func_001655e0(m, o->x15c, o->f16c, o->x1d4[o->x168]);
            } else if (o->x178 > 0) {
                o->f180 += d;
                func_00130898(o, m);
                PlatVu0CopyVector(a, m[3]);
                func_00130e48(o, m);
            } else {
                if (o->b2) {
                    PlatVu0AddVector(m[3], m[3], t3);
                    PlatVu0CopyVector(a, m[3]);
                    PlatVu0CopyVector(t3, (*(f32 (*)[0x4])&D_002C58A0));
                }
                if (o->b3) {
                    func_00130660(o, m, o->x168, o->f280, 0.0f);
                } else {
                    func_00130660(o, m, o->x168, o->f288 + d, o->f290);
                    func_00130c28(o, o->f288, o->f288 + d);
                }
            }
        }
    }
    fl = o->x1cc;
    o->x1cc = func_00167680(o->x15c);
    if (fl & 1) o->x1cc |= 1;
    if (o->x1cc & 0x100000) o->flags0 &= ~0x1004;
    if (has4) {
        func_001752a0(o->x15c, o->x1f0);
        o->b10 = 1;
    } else {
        o->b10 = 0;
    }
    if (o->f170 > 0.0f) {
        PlatVu0ApplyMatrix(b, m, o->x270);
        PlatVu0AddVector(o->x50, o->x10, b);
    } else {
        func_001676b0(o->x15c, o->x50);
    }
    if (o->b2 && o->f170 <= 0.0f && !did) {
        PlatVu0SubVector(b, o->x50, a);
        PlatVu0SubVector(o->x200, b, t3);
        PlatVu0CopyVector(t3, b);
    } else {
        PlatVu0CopyVector(o->x200, (*(f32 (*)[0x4])&D_002C58A0));
        PlatVu0CopyVector(t3, (*(f32 (*)[0x4])&D_002C58A0));
    }
    PlatVu0CopyMatrix(o->x230, m);
    func_00167d70(o->x15c, dt);
}
#undef func_00130e48
#undef func_00130c28
#undef func_00130598

