/* Effects started on objects: func_0012bd98(o, kind, mask, pos) asks the
 * effect manager D_0029B410 (func_00176578) for an effect of the object's
 * class (D_002E2FB8) and places it, func_0012c010 at a bone; effect tasks
 * (func_0012c180, func_0012c238, func_0012c328) and a timed one keyed by the
 * tuning block D_00308CDC (func_0012c560); func_0012c760 / func_0012c880 end
 * them. Flag mode: nostrict (the other modes are in the sibling files). Read
 * from the code, not proved by a boot (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_004F.h"
#include "data/bss_0052.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002C5C80.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002E31A4.h"
#include "data/pieces/D_00304BE8.h"
#include "m2c.h"

/* func_0012bd98 (from hand/nostrict/text_00120000_h54.c). */
typedef FVec4 V4;
typedef struct { u8 pad[0x4c]; u16 f4c; } I3;
typedef struct { u32 f0; u8 p4[0x2c]; f32 f30[3]; f32 f3c; f32 f40[2]; u8 p48[0xc0-0x48]; V4 fc0; u8 pd0[0x130-0xd0]; I3 *f130; u8 p134[0x2d4-0x134]; f32 f2d4; u8 p2d8[0x350-0x2d8]; s32 f350[3]; } E3;
typedef struct { u8 p0[4]; s32 *rot; u8 p8[4]; f32 *scl; } R3;
extern s32 D_0029B410;
extern s8 D_002E2FB8[];
extern s32 func_00176578(s32, s32, u32, s64);
extern R3 *func_00147ed8(s32, s32, s32, f32 *);
extern void func_00121a78(V4 *, f32 *);
R3 *func_0012bd98(E3 *e, s32 kind, u32 c, f32 *out) {
    V4 m;
    V4 a;
    V4 b;
    V4 pad;
    f32 ang[3];
    s32 j;
    s32 idx;
    R3 *r;
    s32 i;
    if (!D_0029B410) return 0;
    if (e->f130->f4c < 20) j = D_002E2FB8[e->f130->f4c];
    else j = 16;
    if (j < 0) return 0;
    idx = func_00176578(D_0029B410, 1 << kind, c, 1 << j);
    r = 0;
    if (idx < 0) goto end;
    switch (kind) {
    case 0:
        ang[0] = 0;
        ang[1] = e->f3c;
        ang[2] = 0;
        break;
    case 10: case 11: case 12:
        ang[0] = 0;
        ang[1] = e->f3c;
        ang[2] = 0;
        if (e->f0 & 0x400000) out[1] = e->f2d4;
        break;
    default:
        PlatVu0SubVector(&a, &D_002C58A0, &e->fc0);
        PlatVu0OuterProduct(&b, (V4 *)e->f30, &a);
        PlatVu0Normalize(&b, &b);
        PlatVu0OuterProduct(&m, &a, &b);
        PlatVu0Normalize(&m, &m);
        func_00121a78(&m, ang);
        break;
    }
    r = func_00147ed8(D_0029B410, idx, 10000, out);
    if (r) {
        r->rot[0] = (u16)(s32)(ang[0] / 6.2831855f * 65536.0f);
        r->rot[1] = (u16)(s32)(ang[1] / 6.2831855f * 65536.0f);
        r->rot[2] = (u16)(s32)(ang[2] / 6.2831855f * 65536.0f);
        for (i = 0; i < 3; i++) r->scl[i] = e->f350[i] * 0.0078125f;
        r->scl[3] = 1.0f;
    }
end:
    return r;
}

/* func_0012c328 (from hand/nostrict/text_00120000_h54.c). */
typedef struct { u8 pad[0x4c]; u16 f4c; } I4;
typedef struct { u8 pad[0x6c]; u32 *f6c; } O4;
typedef struct { u8 pad[0x130]; I4 *f130; u8 p134[0x164-0x134]; s32 f164; } A4;
typedef struct { s32 state; s32 f4; s32 f8; O4 *fc; u8 p10[0x20]; s32 f30; } W4;
typedef struct { u8 pad[0x10]; A4 *f10; u8 p14[8]; f32 f1c; W4 *f20; } T4;
extern f32 D_002BBDFC;
extern s32 func_00122ff8(void *);
extern s32 func_001375d8(A4 *);
extern void func_001315c0(void *, s32, f32 *, f32);
extern void func_0013c9e0(s32, s32);
extern void func_0012c238(A4 *, s32, void *);
extern void func_001586a8(s32);
extern void func_00121eb0(W4 *);
s32 func_0012c328(T4 *t) {
    W4 *w = t->f20;
    s32 done;
    s32 i;
    f32 buf[4];
    if (w->f30 == 0xfff) w->f30 = t->f10->f164;
    t->f1c -= D_002BBDFC;
    if (!func_00122ff8(t->f10) || func_001375d8(t->f10)) goto kill;
    done = 0;
    switch (w->state) {
    case 0:
        if (t->f1c < 0.0f) {
            A4 *a = t->f10;
            if (a->f164 == w->f30) {
                u16 k = a->f130->f4c;
                func_001315c0(a, k == 6 ? 29 : 28, buf, k == 9 ? 3.0f : 1.0f);
                func_00147ed8(D_00350CE0, w->f4, 20000, buf);
            }
            w->state = 1;
            t->f1c = 30.0f;
        }
        break;
    case 1:
        if (w->fc) {
            if (!func_00122ff8(w->fc) || (*w->fc->f6c >> 2 & 1)) {
kill:
                done = 1;
                func_0013c9e0(w->f8, t->f10->f130->f4c);
                break;
            }
        }
        if (t->f1c < 0.0f) {
            A4 *a;
            done = 1;
            a = t->f10;
            if (w->fc) {
                func_0012c238(a, w->f8, w->fc);
                a = t->f10;
            } else {
                for (i = 0; i < 3; i++) {
                    if (D_002E26A0[i]) {
                        func_0012c238(a, w->f8, D_002E26A0[i]);
                        a = t->f10;
                    }
                }
            }
            if (a->f130->f4c == 0) func_001586a8(12);
        }
        break;
    }
    if (done) {
        func_00121eb0(w);
        return 4;
    }
    return 0;
}

/* func_0012c560 (from hand/nostrict/text_00120000_h31.c). */
typedef struct { u8 pad[0x4c]; u16 f4c; } S4c;
typedef struct { u8 pad[0x130]; S4c *f130; } E11;
typedef struct { u8 pad[0x10]; E11 *f10; s32 f14; u8 pad18[4]; f32 f1c; u8 f20[0x40]; } T11;
typedef struct { s32 f0, f4, f8; E11 *fc; u8 pad10[0x20]; s32 f30; } P11;
extern T11 *func_00147d18(void *);
extern P11 *func_00121e28(s32, void *);
extern void func_0013cae8(s32, s32);
void func_0012c560(E11 *e, E11 *t, s32 fl) {
    T11 *k = func_00147d18(func_0012c328);
    P11 *p;
    k->f10 = e;
    k->f14 = 0;
    p = func_00121e28(0x40, k->f20);
    p->f30 = 0xfff;
    p->f0 = 0;
    p->f8 = fl;
    p->fc = t;
    if (t == 0 || e == t) {
        p->f4 = 1;
        k->f1c = (*(Cfg_308cdc **)&D_00308CDC)->t[e->f130->f4c].a;
    } else {
        p->f4 = 2;
        k->f1c = (*(Cfg_308cdc **)&D_00308CDC)->t[e->f130->f4c].b;
    }
    if (!(fl & 0x400)) {
        if (e->f130->f4c == 0) { s32 o = ((s32)D_00304BE8); (D_002E31A4 + o)[38] = 0; }
        else func_0013cae8(e->f130->f4c, fl);
    }
}

/* func_0012c760 (from hand/nostrict/text_00120000_h31.c). */
typedef struct { u8 pad[0x10]; u8 *f10; u32 f14; } O13;
typedef struct { u8 pad[0x1c]; O13 *f1c; s32 f20; s32 f24; } S13;
typedef struct { u64 flags; u8 pad[0x14c - 8]; S13 *f14c; u8 pad150[0x1cc - 0x150]; u32 f1cc; } E13;
extern O13 *func_00148968(E13 *, s32, s32);
extern void func_00176310(O13 *);
void func_0012c760(E13 *e) {
    S13 *s = e->f14c;
    O13 *o = s->f1c;
    if (o) {
        s32 k = o->f14 & 3;
        if (k != 1) {
            s->f1c = 0;
            return;
        }
        if ((e->flags & 0xc001) != 0xc001) {
            func_00176310(o);
            e->f14c->f1c = 0;
            return;
        }
        if (!(e->f1cc & 0x800000)) *o->f10 = k;
        return;
    }
    if (s->f24 < 0) return;
    if (s->f24 & 0x40000000) {
        s->f24 &= ~0x40000000;
        return;
    }
    if (!(e->f1cc & 0x800000)) return;
    if (func_00122ff8(e)) {
        O13 *n = func_00148968(e, e->f14c->f20, e->f14c->f24);
        e->f14c->f1c = n;
        if (n) n->f14 &= ~0x20;
    }
    e->f14c->f24 = -1;
}

/* func_0012c8e8 (from hand/nostrict/text_00120000.c). */
f32 atan2f(f32, f32);
f32 func_00120c18(M2C_UNK *);
#define func_0012bd98 ((void *(*)(void *, M2C_UNK, M2C_UNK, void *)) func_0012bd98)
s32 func_0012c8e8(void *arg0) {
    s32 sp[8];    s32 var_v0;
    void *temp_v0;

    if ((M2C_FIELD(arg0, f32 *, 0x2D4) - M2C_FIELD(arg0, f32 *, 0x14)) < 5e+01f) {
        PlatVu0CopyVector(sp, arg0 + 0x10);
        PlatVu0SubVector(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, M2C_FIELD(arg0, s32 *, 0x148) + 0xF0);
        if (func_00120c18(arg0 + 0x3C0) > 4.0f) {
            if (func_00120c18(&M2C_FIELD(sp, M2C_UNK *, 0x10)) > 1e+02f) {
                M2C_FIELD(sp, f32 *, 0x4) = M2C_FIELD(arg0, f32 *, 0x2D4);
                PlatVu0CopyVector(M2C_FIELD(arg0, s32 *, 0x148) + 0xF0, sp);
                temp_v0 = func_0012bd98(arg0, 0, 0x08000100, sp);
                var_v0 = 1;
                if (temp_v0 != NULL) {
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 0) = 0;
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 4) = (s32) ((s32) ((atan2f(M2C_FIELD(arg0, f32 *, 0x3C0), M2C_FIELD(arg0, f32 *, 0x3C8)) / 6.2831855f) * 65536.0f) & 0xFFFF);
                    M2C_FIELD(M2C_FIELD(temp_v0, void **, 4), s32 *, 8) = 0;
                    goto block_5;
                }
                /* Duplicate return node #8. Try simplifying control flow for better match */
                return var_v0;
            }
block_5:
            return 1;
        }
    }
    var_v0 = 0;
    return var_v0;
}
#undef func_0012bd98

