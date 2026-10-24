/* Effect objects: the 256 records D_00547C00 (0x3C bytes each) handed out
 * round-robin from D_0054B800 (func_00147c30), their tasks (func_00147d18,
 * func_001480d0, func_00148438), func_00148768 starts an effect on an
 * object, func_00147e08 sets one's rotation from a matrix, func_00148e98
 * frees them all. Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0053.h"
#include "data/bss_0054.h"
#include "vm/script_vm.h"
#include "data/types/text_00140000_h8.h"
#include "data/pieces/D_0035C710.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350CE8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304C70.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_00350D88.h"
#include "platform/math.h"
#include "data/types/text_00140000_h34.h"

/* func_00147a68 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0xc]; f32 xc; } W8Fc;
typedef struct { u8 pad[0x8]; f32 *x8; W8Fc *xc; u8 pad10[0x14 - 0x10]; u32 x14; u8 pad18[0x30 - 0x18]; s32 x30; u8 pad34[0x38 - 0x34]; s32 x38; } W8O60;
typedef struct { u8 pad[0x2c]; f32 x2c; } W8F2c;
typedef struct { f32 m[4][4]; W8O60 sub; s32 x7c; s32 x80; W8F2c *x84; } W8Mdl;
extern W8Mdl D_0054C120;
void func_00147e08(W8O60 *, W8Mdl *);
u8 *func_001623e0(s32);
s32 func_00147a68(void) {
    W8Mdl *m = &D_0054C120;
    W8O60 *s = &m->sub;
    f32 v[4];
    if (&m->sub == 0 || (s->x14 & 3) != 1) return 4;
    if (m->x84) {
        f32 f = m->x84->x2c;
        v[2] = f;
        v[1] = f;
        v[0] = f;
        PlatVu0CopyVector((void *)m->sub.x8, v);
    }
    func_00147e08(s, m);
    PlatVu0CopyMatrix(m, func_001623e0(m->x7c) + m->x80 * 64);
    return 0;
}

/* func_00147be0 (from hand/text_00140000_h8.c). */
extern W8O60 D_00547C00[];
W8O60 *func_00147be0(s32 a) {
    s32 i;
    for (i = 0; i < 256; i++) {
        W8O60 *p = &D_00547C00[i];
        if (p && (p->x14 & 3) == 1 && p->x38 == a) return p;
    }
    return 0;
}

/* func_00147c30 (from hand/text_00140000_h8.c). */
extern W8O60 *D_0054B800;
W8O60 *func_00147c30(void) {
    s32 i;
    for (i = 0; i < 256; i++) {
        D_0054B800++;
        if (D_0054B800 >= &D_00547C00[256]) D_0054B800 = D_00547C00;
        if (!(D_0054B800->x14 & 3)) return D_0054B800;
    }
    return 0;
}

/* func_00147c98 (from hand/text_00140000_h8.c). */
s32 func_00176488(s32, W8O60 *, s32, s32);
W8O60 *func_00147c98(s32 a, s32 b, s32 c) {
    W8O60 *e;
    if (!a) return 0;
    e = func_00147c30();
    if (e) {
        if (func_00176488(a, e, b & 0x7ff, c)) return e;
        e->x14 = 0;
    }
    return 0;
}

/* func_00147d18 (from auto/text_00140000_4.c). */
extern u8 D_0054B808[];
s32 func_0011f090(s32, s32, s32);
#define D_0054B808 (*(M2C_UNK (*)) &D_0054B808)
s32 func_00147d18(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_0011f090((s32) &D_0054B808, 0, arg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x1C) = 0;
    }
    return temp_v0;
}
#undef D_0054B808

/* func_00147ed8 (from auto/text_00140000_5.c). */
#define func_00147c98 ((s32 *(*)()) func_00147c98)
s32 *func_00147ed8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *temp_v0;

    temp_v0 = func_00147c98(arg0, arg1, arg2);
    if (temp_v0 != NULL) {
        PlatVu0CopyVector(*temp_v0, arg3);
    }
    return temp_v0;
}
#undef func_00147c98

/* func_00147f20 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0x10]; s32 x10; W8O60 *x14; s32 x18; f32 x1c; u8 x20[0x10]; } W8Task;
extern f32 D_002BBDFC;
s32 func_00147f20(W8Task *t) {
    W8O60 *e = t->x14;
    W8Fc *p;
    f32 v;
    s32 r;
    if (!e || (e->x14 & 3) != 1) return 4;
    p = e->xc;
    v = p->xc - t->x1c * D_002BBDFC;
    r = 0;
    if (v <= 0.0f) { v = 0.0f; r = 4; }
    p->xc = v;
    return r;
}

/* func_00147f88 (from auto/text_00140000_16.c). */
#define func_00147d18 ((void *(*)(M2C_UNK *)) func_00147d18)
void func_00147f88(void *arg0, f32 fparg0) {
  float new_var;
  void *temp_v0;
  temp_v0 = func_00147d18(&func_00147f20);
  if (temp_v0 != 0)
  {
    *((void **) (((s8 *) temp_v0) + 0x14)) = arg0;
 new_var = 1.0f / fparg0; do { *((s32 *) (((s8 *) temp_v0) + 0x18)) = (s32) (*((s32 *) (((s8 *) arg0) + 0x30))); } while (0);
    *((f32 *) (((s8 *) temp_v0) + 0x1C)) = (f32) new_var;
  }
}
#undef func_00147d18

/* func_00148068 (from hand/text_00140000_h8.c). */
s32 func_00147ff0(W8Task *t);
#define func_0011f090 ((W8Task *(*)(void *, s32, void *)) func_0011f090)
void func_00148068(W8O60 *o, f32 f) {
    W8Task *t = func_0011f090(D_0054B808, -1, func_00147ff0);
    t->x14 = o;
    t->x18 = (s32)((W8O60 **)o)[12];
    t->x1c = 1.0f / f;
}
#undef func_0011f090

/* func_00148438 (from hand/text_00140000_h8.c). */
void func_00176340(s32);
typedef struct { u8 pad[0x54]; s32 x54; f32 x58; f32 x5c; f32 x60; } W8C;
typedef struct { s32 x0; s32 x4:8; s32 x5:8; s32 x6:16; s32 x8; f32 xc; s32 x10; f32 x14; s32 x18; s32 x1c; u8 pad20[0x6c - 0x20]; W8C *x6c; } W8R;
typedef W8R W8B;
s32 func_001480d0();
W8R *func_00121e28(s32, void *);
#define func_00147d18 ((W8Task *(*)(void *)) func_00147d18)
W8R *func_00148438(W8O60 *o, W8B *b) {
    W8Task *t = func_00147d18(func_001480d0);
    W8R *r;
    s32 v;
    if (!t) {
        func_00176340((s32)o);
        return 0;
    }
    *(s32 *)&t->x14 = (s32)o;
    v = o->x30;
    t->x10 = (s32)b;
    t->x18 = v;
    r = func_00121e28(112, t->x20);
    r->x6 = -2;
    r->x0 = 0;
    o->x14 |= 0x20;
    return r;
}
#undef func_00147d18

/* func_00148570 (from auto/text_00140000_10.c). */
void func_001318e8(s32, s32, s32);
#define func_00148438 ((s32 (*)(s32, s32)) func_00148438)
#define func_00147e08 ((void (*)(s32, s32)) func_00147e08)
s32 func_00148570(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    s32 temp_v0;

    func_001318e8(arg1, arg2 & 0xFFFEFFFF, (s32) sp);
    func_00147e08(arg0, (s32) sp);
    temp_v0 = func_00148438(arg0, arg1);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 4) = 2;
        PlatVu0CopyMatrix(temp_v0 + 0x30, (s32) sp);
    }
    return temp_v0;
}
#undef func_00148438
#undef func_00147e08

/* func_00148600 (from auto/text_00140000_11.c). */
M2C_UNK func_001315c0(s32, s32, M2C_UNK *, f32);
#define func_001318e8 ((M2C_UNK (*)(s32, s32, void *)) func_001318e8)
#define func_00147e08 ((M2C_UNK (*)(s32, void *)) func_00147e08)
#define func_00148438 ((void *(*)(s32, s32)) func_00148438)
void *func_00148600(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 sp[16];    void *temp_v0;

    func_001318e8(arg1, arg2 & 0xFFFEFFFF, sp);
    func_001315c0(arg1, arg2, &M2C_FIELD(sp, M2C_UNK *, 0x30), fparg0);
    func_00147e08(arg0, sp);
    temp_v0 = func_00148438(arg0, arg1);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 4) = 3;
        M2C_FIELD(temp_v0, f32 *, 0xC) = fparg0;
        PlatVu0CopyMatrix(temp_v0 + 0x30, sp);
    }
    return temp_v0;
}
#undef func_001318e8
#undef func_00147e08
#undef func_00148438

/* func_001486b0 (from auto/text_00140000.c). */
#define func_00148570 ((M2C_UNK (*)()) func_00148570)
s32 func_001486b0(s32 arg0, s32 arg1, s32 arg2) {
    func_00148570(arg0, arg1, arg2);
    return arg0;
}
#undef func_00148570

/* func_001486d8 (from hand/text_00140000_h8.c). */
typedef union { s32 i; u32 u; f32 f; void *p; u8 b[4]; s16 h[2]; } W8Arg;
W8R *func_001486d8(W8O60 *a, W8B *b) {
    W8Arg *r = (W8Arg *)func_00148438(a, b);
    f32 f;
    if (r) {
        f = b->x6c->x60;
        a->x8[2] = f;
        a->x8[1] = f;
        a->x8[0] = f;
        r[1].b[0] = 1;
        r[2].i = b->x6c->x54;
        r[3].f = b->x6c->x58;
        r[4].i = 0;
        r[5].f = b->x6c->x5c;
        r[6].i = 0;
        r[7].i = 0;
        return (W8R *)a;
    }
    return (W8R *)r;
}

/* func_00148768 (from auto/text_00140000_6.c). */
s32 func_001484c8(s32, s32, s32, f32);
#define func_00147c98 ((s32 (*)(s32, s32, s32)) func_00147c98)
s32 func_00148768(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_00147c98(arg0, arg1, 0x4E20);
    if (temp_v0 != 0) {
        temp_v0_2 = func_001484c8(temp_v0, arg2, arg3, fparg0);
        if ((temp_v0_2 != 0) && (arg1 & 0x800)) {
            M2C_FIELD(temp_v0_2, s16 *, 6) = -1;
        }
    }
    return temp_v0;
}
#undef func_00147c98

/* func_001487f8 (from hand/text_00140000_h8.c). */
#define func_00148570 ((W8R *(*)(W8O60 *, s32, s32)) func_00148570)
W8O60 *func_001487f8(s32 a, s32 b, s32 c, s32 d) {
    W8O60 *e = func_00147c98(a, b, 20000);
    if (e) {
        W8R *r = func_00148570(e, c, d);
        if (r && (b & 0x800)) r->x6 = -1;
    }
    return e;
}
#undef func_00148570

/* func_00148878 (from auto/text_00140000_4.c). */
#define func_00147c98 ((s32 (*)(s32, s32, s32)) func_00147c98)
#define func_00148600 ((s32 (*)(s32, s32, s32, f32)) func_00148600)
s32 func_00148878(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_00147c98(arg0, arg1, 0x4E20);
    if (temp_v0 != 0) {
        temp_v0_2 = func_00148600(temp_v0, arg2, arg3, fparg0);
        if ((temp_v0_2 != 0) && (arg1 & 0x800)) {
            M2C_FIELD(temp_v0_2, s16 *, 6) = -1;
        }
    }
    return temp_v0;
}
#undef func_00147c98
#undef func_00148600

/* func_00148908 (from hand/text_00140000_h8.c). */
typedef struct { u8 pad[0x370]; union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } x370; } W8Ply;
W8O60 *func_00148908(W8Ply *a) {
    W8O60 *e = func_00147c98(D_00350CE0, a->x370.b.kind == 1 ? 24 : 19, 20000);
    if (e) e = (W8O60 *)func_001486d8(e, (W8B *)a);
    return e;
}

/* func_00148a40 (from auto/text_00140000_4.c). */
s32 func_00148968(s32, s32, s32);
s32 func_00148a40(s32 arg0, s32 arg1) {
    return func_00148968(arg0, M2C_FIELD(arg0, s32 *, 0x68), arg1);
}

/* func_00148b70 (from auto/text_00140000_4.c). */
s32 func_00148b70(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    return func_00148768(M2C_FIELD(arg0, s32 *, 0x68), arg1, arg0, arg2, fparg0);
}

/* func_00148b98 (from auto/text_00140000_10.c). */
#define func_001487f8 ((void *(*)(s32, s32, s32, s32)) func_001487f8)
void *func_00148b98(s32 arg0, s32 arg1, s32 arg2) {
    return func_001487f8(M2C_FIELD(arg0, s32 *, 0x68), arg1, arg0, arg2);
}
#undef func_001487f8

/* func_00148bc0 (from hand/text_00140000_h34.c). */
s32 func_00122ff8(s32);
void func_00121eb0(void *);
typedef struct { u8 pad[4]; u8 kind; u8 id; u8 pad6[2]; s32 a; f32 f; } W34T20;
typedef struct { u8 pad[0x10]; s32 x10; u8 pad14[8]; f32 t; W34T20 *x20; } W34Tsk;
#define func_00148a40 ((void (*)(s32, s32)) func_00148a40)
#define func_00148b70 ((void (*)(s32, s32, s32, f32)) func_00148b70)
s32 func_00148bc0(W34Tsk *a) {
    W34T20 *s = a->x20;
    if (func_00122ff8(a->x10)) {
        if (!(a->t <= 0.0f)) goto dec;
        switch (s->kind) {
        case 0: func_00148a40(a->x10, s->id); break;
        case 1: func_00148b70(a->x10, s->id, s->a, s->f); break;
        case 2: func_00148b98(a->x10, s->id, s->a); break;
        }
    }
    func_00121eb0(s);
    return 4;
dec:
    a->t -= D_002BBDFC;
    return 0;
}
#undef func_00148a40
#undef func_00148b70

/* func_00148cb0 (from auto/text_00140000_5.c). */
#define func_00121e28 ((s32 (*)(s32, s32)) func_00121e28)
s32 func_00148cb0(s32 arg0, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00147d18((s32) &func_00148bc0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 0x10) = arg0;
        M2C_FIELD(temp_v0, f32 *, 0x1C) = fparg0;
        return func_00121e28(0x70, temp_v0 + 0x20);
    }
    return temp_v0;
}
#undef func_00121e28

/* func_00148d18 (from auto/text_00140000_4.c). */
void func_00148d18(s32 arg0, s32 arg1, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00148cb0(arg0, fparg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s8 *, 5) = (s8) arg1;
        M2C_FIELD(temp_v0, s8 *, 4) = 0;
    }
}

/* func_00148d50 (from hand/text_00140000_h8.c). */
#define func_00148cb0 ((W8R *(*)(s32, f32)) func_00148cb0)
void func_00148d50(s32 a, f32 x, f32 y, s32 b, s32 c) {
    W8R *r = func_00148cb0(a, y);
    if (r) {
        r->xc = x;
        r->x5 = b;
        r->x8 = c;
        r->x4 = 1;
    }
}
#undef func_00148cb0

/* func_00148db0 (from auto/text_00140000_4.c). */
void func_00148db0(s32 arg0, s32 arg1, s32 arg2, f32 fparg0) {
    s32 temp_v0;

    temp_v0 = func_00148cb0(arg0, fparg0);
    if (temp_v0 != 0) {
        M2C_FIELD(temp_v0, s32 *, 8) = arg2;
        M2C_FIELD(temp_v0, s8 *, 5) = (s8) arg1;
        M2C_FIELD(temp_v0, s8 *, 4) = 2;
    }
}

/* func_00148df8 (from auto/text_00140000_10.c). */
M2C_UNK func_0011f130(M2C_UNK *, M2C_UNK);
#define D_0054B808 (*(M2C_UNK (*)) &D_0054B808)
s32 func_00148df8(void) {
    func_0011f130(&D_0054B808, 0);
    return 0;
}
#undef D_0054B808

/* func_00148e20 (from auto/text_00140000.c). */
extern M2C_UNK D_00348CE0;
M2C_UNK D_00547BC0[0x10] ALIGNED(64);  /* moved from auto/text_00140000.c (session 53) */
#define func_00176488 ((M2C_UNK (*)(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK)) func_00176488)
M2C_UNK *func_00148e20(void) {
    func_00176488(&D_00348CE0, &D_00547BC0, 0, 0x4E20);
    return &D_00547BC0;
}
#undef func_00176488

/* func_00148e60 (from auto/text_00140000.c). */
M2C_UNK func_001763f0(M2C_UNK *);
extern M2C_UNK D_00308CE0;
void func_00148e60(void) {
    (*(M2C_UNK **)&D_00350CE0) = &D_00308CE0;
    func_001763f0(&D_00308CE0);
    func_001763f0(&D_00348CE0);
}

/* func_00148e98 (from auto/text_00140000_5.c). */
M2C_UNK func_00176310(M2C_UNK *);
#define D_00547C00 (*(M2C_UNK (*)) &D_00547C00)
void func_00148e98(void) {
    s8 *var_s0;
    s32 var_s1;

    var_s0 = &D_00547C00;
    var_s1 = 0xFF;
    do {
        if ((var_s0 != NULL) && ((M2C_FIELD(var_s0, s32 *, 0x14) & 3) == 1)) {
            func_00176310(var_s0);
        }
        var_s1 -= 1;
        var_s0 += 0x3C;
    } while (var_s1 >= 0);
}
#undef D_00547C00

/* func_00148f08 (from hand/text_00140000_h34.c). */
void func_0011efa8(void *, void *, s32, s32);
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
u8 D_0054B818[0x908] ALIGNED(8);  /* moved from hand/text_00140000_h34.c (session 53) */
extern W34Mdl3C D_00547C00_00148f08[256] __asm__("D_00547C00");
#define D_00547C00 D_00547C00_00148f08
extern W34Mdl3C *D_0054B800_00148f08 __asm__("D_0054B800");
#define D_0054B800 D_0054B800_00148f08
void func_00148f08(void) {
    s32 i;
    for (i = 0; i < 256; i++) D_00547C00[i].x14 = 0;
    D_0054B800 = D_00547C00;
    func_0011efa8(D_0054B808, D_0054B818, 36, 64);
    if (func_0011ef38(func_00148df8) == 0) func_0011ef10(0x222DF, func_00148df8);
}
#undef D_00547C00
#undef D_0054B800

