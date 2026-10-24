/* The player's moves by state (a guess from the code): func_001271b0 (called
 * from the player's move, src/obj/plctl.c) picks a handler by state
 * (func_00126c10, func_00126f18), with the move's motions (func_00125b68,
 * func_00125be8), effects and jump arcs (func_00125dc8), the state block
 * D_002E27C8 / D_002E3190; func_001252f8 checks the abilities
 * (func_0013c968) for the moves allowed. Flag mode: default (the other modes
 * are in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "actor.h"
#include "data/bss_004F.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_002C6440.h"
#include "data/pieces/D_002E26A0.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0051.h"
#include "data/bss_0052.h"
#include "data/types/text_00120000_h5.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/pieces/D_00308CDC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002E31A8.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_b01.h"
#include "data/types/text_00110000_b01_p2.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BD250.h"
#include "data/types/text_00110000_b01_p.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002C5968.h"
#include "data/types/text_00110000_h53_p.h"
#include "data/types/text_00110000_h53_p2.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/text_00110000_h53.h"
#include "data/pieces/D_002E27A4.h"
#include "data/pieces/D_002E2790.h"
#include "data/pieces/D_002E2780.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002E26C0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002A3F3C.h"
#include "data/pieces/D_0029B420.h"
#include "data/types/text_00100000_s7_w4.h"
#include "data/pieces/D_002E27D4.h"

/* func_001259b0 (from auto/text_00120000_3.c). */
extern s32 D_002C5958;
void func_001252f8(void);
void func_001259b0(s32 arg0) {
    if (arg0 != 0) {
        D_002C5958 |= 0x400000;
    } else {
        D_002C5958 &= 0xFFBFFFFF;
    }
    func_001252f8();
}

/* func_00125a00 (from hand/text_00120000_h5.c). */
typedef struct Actor_25a00 { u8 pad[0x70]; s32 f70; } S70;
s32 func_00125a00(s32 a) {
    S70 *p = D_002E26A0[0];
    if ((a & 1) && p->f70) return 0;
    return 1;
}

/* func_00125a28 (from hand/text_00120000_h31.c). */
extern f32 func_00121748(f32 *, f32 *);
typedef struct Actor_25a28 {
    u32 f0;
    u8 pad4[0x2c];
    f32 f30[4];
    u8 pad40[0x30];
    s32 f70;
    u8 pad74[0xf0];
    s32 f164;
    u8 pad168[0x172];
    u16 f2da;
    u8 pad2dc[0x94];
    u64 f370;
} O16;
typedef O16 E18;
typedef E18 E1;
extern f32 D_004F7800[];
extern s32 func_00137618(E1 *, s32);
extern void func_00105a30(s32, s32, f32 *);
extern u32 D_002C5958_00125a28 __asm__("D_002C5958");
#define D_002C5958 D_002C5958_00125a28
s32 func_00125a28(s32 a0) {
    E1 *e;
    f32 buf[4];
    if (D_002E31B8 == 3) goto ret0;
    if (D_002C5958 & 0x12000) return 0;
    if ((D_002E31A8 >> 1) & 1) goto ret0;
    e = D_002E26A0[0];
    if (a0 & 1) {
        if (!func_00137618(e, 3)) return 0;
        func_00105a30(-1, e->f2da, buf);
        if (func_00121748(e->f30, buf) > -0.7f) return 0;
        if (func_00121748(D_004F7800, buf) > -0.7f) return 0;
    }
    if (a0 & 2) {
        switch (e->f164) {
        case 3: case 7: case 8:
        ret0:
            return 0;
        case 1: case 2: case 4: case 5: case 6: case 9: case 10: case 11:
            break;
        default:
            return 0;
        }
    }
    if (a0 & 4) {
        if (e->f70) return 0;
    }
    return 1;
}
#undef D_002C5958

/* func_00125b68 (from hand/text_00120000_h5.c). */
extern u32 D_002E3190;
extern s32 func_00130030(void *);
typedef struct S164 { u8 pad[0x164]; s32 f164; } S164;
s32 func_00125b68(S164 *e) {
    if ((D_002E3190 >> 8) & 0xffff) goto no;
    switch (e->f164) {
    case 138:
    case 61:
        return 1;
    case 200:
    case 202:
        if (func_00130030(e)) return 1;
        goto no;
    default:
        return 0;
    }
no:
    return 0;
}

/* func_00125be8 (from hand/text_00120000_h31.c). */
typedef struct { u8 pad[0x70]; s32 f70; u8 pad74[0x3c0 - 0x74]; f32 f3c0[4]; } E2;
extern void func_00130340(E2 *, s32, f32);
extern void func_00130578(E2 *, s32, f32);
extern void func_001333e0(E2 *, s32, s32);
void func_00125be8(E2 *e, s32 a1) {
    switch (e->f70) {
    case 2:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000006, 0.0f);
        PlatVu0ScaleVector(e->f3c0, e->f3c0, (*(Cfg_308cdc **)&D_00308CDC)->ff0);
        break;
    case 8:
        func_00130340(e, 0x100008a, 8.0f);
        func_00130578(e, 0x40000075, 8.0f);
        PlatVu0ScaleVector(e->f3c0, e->f3c0, (*(Cfg_308cdc **)&D_00308CDC)->ff0);
        break;
    default:
        func_00130340(e, 0x100003d, 8.0f);
        func_00130578(e, 0x40000000, 0.0f);
        break;
    }
    func_001333e0(e, 0, a1);
}

/* func_00125cf0 (from hand/text_00120000_h31.c). */
extern s32 func_00122ff8(void *);
extern f32 func_0012ec60(struct Actor *, s32, f32 *);
extern float fabsf(float);
typedef struct { u8 pad[0x10]; f32 f10[16]; u8 pad50[0x3c4 - 0x50]; f32 f3c4; } E3;
void func_00125cf0(E3 *e, f32 k, f32 lim) {
    f32 v[4];
    f32 t, r;
    if (func_00122ff8((void *)D_002E31B0.f0) == 0) return;
    func_0012ec60(D_002E31B0.f0, D_002E31B0.f4, v);
    v[1] += 100.0f;
    PlatVu0SubVector(v, v, e->f10);
    if (fabsf(v[1]) > 50.0f) {
        t = e->f3c4 + v[1] * k;
        if (t < -lim) r = -lim;
        else if (lim < t) r = lim;
        else r = t;
        e->f3c4 = r;
    }
}

/* func_00125dc8 (from hand/text_00110000_b01.c). */
typedef struct { u8 pad[41]; u8 x29; } Sub14c;
typedef struct { u8 pad[0xcc]; f32 xcc; } Sub6c;
typedef struct { u8 pad[272]; V4_01 v; } Sub148;
typedef struct {
    u8 pad0[0x68];
    s32 x68;
    Sub6c *x6c;
    u8 pad70[0x148 - 0x70];
    Sub148 *x148;
    Sub14c *x14c;
    u8 pad150[0x3c0 - 0x150];
    V4_01 x3c0;
} Obj25;
typedef struct { u8 pad[8]; f32 x8; } Prm25;
typedef struct { s8 k, a, b; } Tr25;
Prm25 *func_0013dc10(Obj25 *, u32);
void func_0014db78(Obj25 *, f32 *);
void func_00121fc4(f32 *, f32 *);
void func_0014cce0(Obj25 *, f32);
void func_001376e8(Obj25 *, f32 *);
void func_001586a8(s32);
void func_00148a40(Obj25 *, s32);
void func_00148768(s32, s32, Obj25 *, s32, f32);
#define func_00130578 ((void (*)(Obj25 *, s32, f32)) func_00130578)
#define func_00125cf0 ((void (*)(Obj25 *, f32, f32)) func_00125cf0)
/* 0x126c10 (needs func_00125dc8 defined above) */
void func_00125dc8(Obj25 *o, u32 mode, f32 *v) {
    Tr25 tbl[5] = { { 3, 0, 1 }, { 4, 3, -1 }, { 5, 4, 5 }, { 7, 6, 7 }, { -1, -1, -1 } };
    Prm25 *pr;
    f32 sp;
    f32 z;
    s32 i;
    pr = func_0013dc10(o, mode);
    sp = pr->x8;
    switch (mode) {
    case 15:
    case 16:
    case 17:
    case 18:
        func_00130578(o, 0x40000006, 0.0f);
        PlatVu0Normalize(v, v);
        if (o->x14c->x29 == 1) {
            v[3] = 8.0f;
        } else if (mode - 15 < 2) {
            v[3] = 12.0f;
        } else {
            v[3] = 4.0f;
        }
        PlatVu0ScaleVector(o->x3c0, v, v[3]);
        v[3] = 0.0f;
        break;
    case 2:
        v[3] = 8.0f;
        func_00130578(o, 0x40000006, 0.0f);
        o->x14c->x29 = 1;
        break;
    case 0:
    case 1:
        sp = v[1];
        func_00130578(o, 0x40000006, 0.0f);
        o->x14c->x29 = 1;
        break;
    case 19:
    case 20:
    case 21:
        o->x6c->xcc = 0.19634955f;
        sp = 0.0f;
        v[1] = sp;
        PlatVu0Normalize(v, v);
        v[3] = pr->x8;
        func_0014db78(o, v);
        func_00125cf0(o, 0.5f, 8.0f);
        func_00130578(o, 0x40000075, 16.0f);
        break;
    case 59:
        PlatVu0CopyVector(v, o->x148->v);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        func_00130578(o, 0x40000006, 0.0f);
        break;
    case 22:
    case 24:
    case 25:
    case 26:
        func_00125cf0(o, 0.2f, 8.0f);
    default:
        z = 0.0f;
        func_00130578(o, 0x40000000, z);
        v[3] = z;
        break;
    }
    if (sp > 0.0f) func_0014cce0(o, sp);
    func_001376e8(o, v);
    func_001586a8(19);
    for (i = 0; tbl[i].k >= 0; i++) {
        if (tbl[i].k == mode) {
            func_00148a40(o, tbl[i].a | 0x800);
            if (tbl[i].b >= 0) func_00148a40(o, tbl[i].b | 0x800);
            break;
        }
    }
    if (mode == 4) func_00148768(o->x68, 2, o, 48, 0.8f);
}
#undef func_00130578
#undef func_00125cf0

/* func_00126838 (from hand/text_00110000_h53.c). */
#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
typedef struct { s16 id; u8 pad[18]; } E7810;
extern E7810 *D_004F7810;
#define func_0012ec60 ((void (*)(s32, s32, V53 *)) func_0012ec60)
s32 func_00126838(u8 *o, s32 *a, V53 *v) {
    s32 t[68];
    s32 i;
    for (i = 15; i < 19; i++) t[i] = 0;
    if (!(FLD(u8, FLD(u8 *, o, 0x14c), 0x29) < FLD(u8, FLD(u8 *, o, 0x6c), 0xd1))) t[16] = 1;
    if (a[0]) {
        func_0012ec60(a[0], a[1], v);
        PlatVu0SubVector(v, v, (V53 *)(o + 0x10));
        if (v->y < -100.0f) {
            t[17] = 1;
        } else {
            t[18] = 1;
            if (FLD(s32, o, 0x70) == 2 && D_002E27C8.b25) t[15] = t[16];
        }
        v->y = 0.0f;
    } else {
        t[18] = 1;
    }

    for (i = 15; i < 19; i++) {
        if (t[i] > 0 && D_004F7810[i].id != FLD(s32, o, 0x164)
) return i;
    }
    for (i = 18; i >= 15; i--) {
        if (D_004F7810[i].id != FLD(s32, o, 0x164)
) return i;
    }
    return 18;
}
#undef func_0012ec60

/* func_001269d8 (from hand/text_00100000_s7_w4.c). */
typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct { u8 pad[0xd0]; u8 xd0; } S6c;
typedef struct { u8 pad[0x6c]; S6c *x6c; u8 pad70[0xdc]; S14c *x14c; u8 pad150[0x14]; s32 x164; } Obj164;
typedef struct { s16 x0; u8 pad[18]; } E20;
extern Pair8 D_002E27C0[4];
extern f32 D_002E27D0;
extern f32 D_002E27CC;
void func_00126238(Obj164 *, s32, s32 *);
f32 func_0012ed88(Obj164 *, s32 *, f32 *, s32);
#define D_004F7810 (*(E20 *(*)) &D_004F7810)
u8 func_001269d8(Obj164 *o, s32 *a1, s32 a2) {
    s32 buf[66];
    f32 tmp[4];
    s32 i;
    u32 j;
    f32 d;
    for (i = 65; i >= 0; i--) buf[i] = 0;
    if (o->x14c->x29 >= o->x6c->xd0) buf[8] = 1;
    if (*a1 == 0) {
        func_00126238(o, a2, buf);
    } else {
        d = func_0012ed88(o, a1, tmp, a2);
        if (d < D_002E27D0 && D_002E27CC < d) buf[14] = 1;
        else func_00126238(o, a2, buf);
    }
    for (i = 0; i < 66; i++) {
        for (j = 0; j < 4; j++) {
            if (buf[D_002E27C0[j].a] > 0 && D_004F7810[D_002E27C0[j].b].x0 != o->x164) return D_002E27C0[j].b;
        }
    }
    if (o->x14c->x29 < 2) goto r25;
    if (o->x164 == D_004F7810[26].x0) {
        if (buf[14] > 0) return 25;
    }
    if (o->x164 != D_004F7810[24].x0) return 24;
r25:
    return 25;
}
#undef D_004F7810

/* func_00126ba0 (from auto/text_00120000_15.c). */
#define func_0012ed88 ((f32 (*)(s32, s32, s32, s32)) func_0012ed88)
#define func_00122ff8 ((s32 (*)(s32)) func_00122ff8)
void func_00126ba0(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    if (func_00122ff8(*(M2C_UNK *)arg1) != 0) {
        func_0012ed88(arg0, arg1, (s32) sp, arg2);
        M2C_FIELD(arg2, s32 *, 4) = 0;
        return;
    }
    PlatVu0CopyVector(arg2, arg0 + 0x30);
}
#undef func_0012ed88
#undef func_00122ff8

/* func_00126c10 (from hand/text_00110000_b01.c). */
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V53_26c10;
typedef struct { s32 a, b; } P8;
typedef struct { u8 type; P8 p; } C3190;
void *memset(void *, s32, u32);
void func_0013ed88(u8 *, C3190 *, V53_26c10 *);
void func_0013ee40(u8 *, C3190 *, V53_26c10 *);
s32 func_00126360(u8 *, s32 *, V53_26c10 *);
s32 func_0012f040(s32, s32);
#define D_002E3190 (*(C3190 (*)) &D_002E3190)
#define func_00126838 ((s32 (*)(u8 *, s32 *, V53_26c10 *)) func_00126838)
#define func_001269d8 ((s32 (*)(u8 *, s32 *, V53_26c10 *)) func_001269d8)
#define func_00126ba0 ((void (*)(u8 *, s32 *, V53_26c10 *)) func_00126ba0)
#define func_00125b68 ((s32 (*)(u8 *)) func_00125b68)
#define func_00125be8 ((void (*)(u8 *, P8 *)) func_00125be8)
void func_00126c10(u8 *o, V53_26c10 *v) {
    P8 s;
    u8 *p;
    func_0013ed88(o, &D_002E3190, v);
    switch (D_002E3190.type) {
    case 1:
        if (FLD(u32, o, 0x1cc) & 0x400000) {
            p = FLD(u8 *, o, 0x14c);
            if (FLD(s32, p, 0x30) == 0) break;
            FLD(u8, p, 0x29)++;
        } else {
            FLD(u8, FLD(u8 *, o, 0x14c), 0x29) = 1;
        }
        if (func_0012f040(D_002E3190.p.a, D_002E3190.p.b)) {
            s = D_002E3190.p;
        } else {
            s.a = 0;
            s.b = 0;
        }
        FLD(P8, FLD(u8 *, o, 0x14c), 0x34) = s;
        switch (FLD(s32, o, 0x70)) {
        case 0:
            func_00125dc8((Obj25 *)o, func_00126360(o, (s32 *)&s, v), (f32 *)v);
            break;
        case 2:
            func_00125dc8((Obj25 *)o, func_00126838(o, (s32 *)&s, v), (f32 *)v);
            break;
        case 8:
            func_00126ba0(o, (s32 *)&s, v);
            func_00125dc8((Obj25 *)o, func_00126838(o, (s32 *)&s, v) + 3, (f32 *)v);
            break;
        case 24:
            func_00126ba0(o, (s32 *)&s, v);
            func_00125dc8((Obj25 *)o, func_001269d8(o, (s32 *)&s, v), (f32 *)v);
            break;

        case 12:
            func_00125dc8((Obj25 *)o, 59, (f32 *)v);
            break;
        }
        break;
    case 3:
        func_0013ee40(o, &D_002E3190, v);
        break;
    case 2:
        if (func_00125b68(o)) {
            func_00125be8(o, &D_002E3190.p);
        } else {
            func_0013ee40(o, &D_002E3190, v);
        }
        break;
    case 99:
        FLD(u8, FLD(u8 *, o, 0x14c), 0x29)++;
        func_00125dc8((Obj25 *)o, 62, (f32 *)v);
        break;
    default:
        func_0013ee40(o, &D_002E3190, v);
        break;
    }
    memset(&D_002E3190, 0, 12);
}
#undef D_002E3190
#undef func_00126838
#undef func_001269d8
#undef func_00126ba0
#undef func_00125b68
#undef func_00125be8

/* func_00126e80 (from hand/text_00120000_h5.c). */
typedef struct FV { f32 f0, f4, f8, f0c; } FV;
typedef struct FTbl { f32 f0, f4, f8; } FTbl;
typedef struct S6c_26e80 { u8 pad[0x20]; u8 f20[0x4c]; FTbl *tbl; } S6c_26e80;
void func_00126e80(S6c_26e80 *a, s32 b, FV *p) {
    if (0.0f < p->f0c) {
        if (p->f0c > 0.7999999523162842f) p->f0c = a->tbl->f8;
        else p->f0c = a->tbl->f4;
        return;
    }
    if (p->f0 == 0.0f && p->f8 == 0.0f) PlatVu0CopyVector(p, a->f20);
    p->f4 = 0;
    p->f0c = 0;
}

/* func_001271b0 (from hand/text_00110000_h53.c). */
typedef struct { u8 type; u8 pad1[2]; s8 flag; s32 a, b; } C3190b;
extern u8 D_002C5BB0[];
void func_00124e08(u8 *o, u8 *p, V53 *out);
void func_00126f18(u8 *, u8 *, V53 *);
u8 *func_0013dfb8(u8 *, V53 *);
#define D_002E3190 (*(C3190b (*)) &D_002E3190)
#define D_004F7800 (*(V53 (*)) &D_004F7800)
#define func_00137618 ((s32 (*)(u8 *, V53 *)) func_00137618)
#define func_00126c10 ((void (*)(u8 *, V53 *)) func_00126c10)
void func_001271b0(u8 *o, V53 *v) {
    V53 s;
    u8 *p;
    if (func_00137618(o, v)) {
        func_00124e08(o, D_002C5BB0, v);
        PlatVu0CopyVector(&D_004F7800, v);
        if ((*(s32 (*(*))(u8*,u8*,V53*))&D_002E27D4)) {
            if ((*(s32 (*(*))(u8*,u8*,V53*))&D_002E27D4)(o, D_002C5BB0, v)) func_00126f18(o, D_002C5BB0, v);
        } else {
            func_00126f18(o, D_002C5BB0, v);
        }
    }
    if (D_002E3190.flag & 1) {
        if ((FLD(s32, o, 0x164) == 7 || FLD(s32, o, 0x164) == 12) && (FLD(s32, o, 0x70) == 0 || FLD(s32, o, 0x70) == 12)) {
            FLD(u32, o, 0) &= ~4;
            PlatVu0CopyVector(&s, &D_002C58A0);
            p = func_0013dfb8(o, &s);
            if (p) FLD(f32, o, 0x3b0) = FLD(f32, p, 4) = 2.0f;
        }
    } else if (D_002E3190.type) {
        func_00126c10(o, v);
    }
    memset(&D_002E3190, 0, 12);
    p = FLD(u8 *, o, 0x14c);
    if (p && FLD(u8 *, p, 0x2c) && (FLD(u32, FLD(u8 *, p, 0x2c), 4) & 1)) func_001586a8(11);
}
#undef D_002E3190
#undef D_004F7800
#undef func_00137618
#undef func_00126c10

