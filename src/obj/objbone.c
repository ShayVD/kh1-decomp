/* Positions on an object's bones: func_001315c0(o, bone, out, t) a bone's
 * position, func_001318e8 a bone's matrix, and small accessors of the
 * object's model and motion. Flag mode: default (the other modes are in the
 * sibling files). Read from the code, not proved by a boot (docs/modules.md
 * "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_003044A0.h"
#include "m2c.h"
#include "actor.h"
#include "vm/script_vm.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0051.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002BC098.h"

/* func_00131438 (from hand/text_00130000_h6.c). */
typedef struct {
    s32 a;
    s32 b;
    u32 *p;
    s32 d;
} W6Slot;
typedef struct {
    u32 flags;
    f32 a;
    f32 b;
    s32 d;
} W6Ent;
typedef struct {
    u32 flags0;
    u8 pad004[0xD0 - 0x4];
    u8 x0d0[0x15C - 0xD0];
    s32 x15c;
    union {
        u64 bits;
        struct {
            u64 b0 : 1;
            u64 b1 : 1;
            u64 b2 : 1;
            u64 b3 : 1;
            u64 b4 : 1;
            u64 b5 : 1;
            u64 rest : 58;
        } f;
        s32 w;
    } u160;
    u8 pad168[0x170 - 0x168];
    f32 f170;
    u8 pad174[0x178 - 0x174];
    s32 count;
    W6Ent ent[5];
    u8 pad1cc[4];
    W6Slot s1d0;
    W6Slot s1e0;
    u8 pad1f0[0x284 - 0x1F0];
    f32 f284;
} W6Obj;
void func_00130660(W6Obj *o, void *p, s32 c, f32 a, f32 b);
void func_00131438(W6Obj *o) {
    o->f170 = 0.0f;
    o->f284 = 1.0f;
    o->u160.w = 0;
    o->count = 0;
    o->s1e0.a = 0;
    func_00130660(o, o->x0d0, 0, o->f170, o->f170);
    o->u160.f.b1 = 0;
}

/* func_00131498 (from hand/text_00130000_h6.c). */
void func_001321a0(W6Slot *s, void *a);
void func_00131498(W6Obj *o, void *a) {
    if (o->s1e0.a == 0) {
        o->s1e0 = o->s1d0;
    }
    func_001321a0(&o->s1d0, a);
    o->u160.f.b5 = 1;
}

/* func_00131500 (from hand/text_00130000_h6.c). */
void func_00131500(W6Obj *o) {
    if ((s32)(o->u160.bits >> 5) & 1) {
        o->s1d0 = o->s1e0;
        o->s1e0.a = 0;
        o->u160.f.b5 = 0;
    }
}

/* func_00131558 (from hand/text_00130000_h6.c). */
s32 func_00162348(s32 a, u32 b);
s32 func_00131558(W6Obj *o, s32 x) {
    s32 r = x;
    if (r & 0x4000) {
        r &= 0xFFF;
    } else if (o->s1d0.a == 0 || (r & 0x8000)) {
        r = -1;
    } else if (r & 0x1000) {
        r &= 0xFFF;
    } else {
        r = func_00162348(o->x15c, x);
    }
    return r;
}

/* func_001315c0 (from hand/text_00120000_b02.c). */
typedef FVec4 V4;
typedef struct { u8 p0[5]; u8 f5; u8 p6[0xe]; s32 f14; } Md9;
typedef struct { u8 p0[2]; u16 f2; f32 f4; f32 f8; } Bn9;
typedef struct { u8 p0[0x24]; f32 f24; f32 f28; } Rg9;
typedef struct { u8 p0[0x18]; Rg9 *f18; } Ln9;
typedef struct {
    u8 p0[0x10];
    V4 f10;
    u8 p20[0x24];
    f32 f44;
    u8 p48[8];
    V4 f50;
    u8 p60[0x70];
    f32 fd0[4][4];
    u8 p110[0x134 - 0x110];
    Md9 *f134;
    u8 p138[0x14c - 0x138];
    Ln9 *f14c;
    u8 p150[0x15c - 0x150];
    s32 f15c;
    u8 p160[0x370 - 0x160];
    u64 f370;
} Ob9;
typedef struct { f32 a[4]; V4 pos; } Tm9;
extern Bn9 *func_0015c960(Ob9 *, s32, s32, s32);
extern void func_0015bad0(Ob9 *, s32, Tm9 *);
extern void func_0012ec88(Ob9 *, V4 *);
extern void func_00162218(s32, s32, V4 *, f32);
#define func_00131558 ((s32 (*)(Ob9 *, s32)) func_00131558)
void func_001315c0(Ob9 *o, s32 id, V4 *out, f32 t) {
    V4 v;
    Tm9 tm;
    s32 mdl;
    Bn9 *b;
    Ln9 *ln;
    Rg9 *rg;
    Md9 *md;

    if (!o || !((s32)(o->f370 >> 32) & 1)) {
        PlatVu0CopyVector(out, &D_002C58A0);
        return;
    }
    if (id & 0x8000) {
        md = o->f134;
        mdl = (md && md->f5) ? md->f14 : 0;
        switch (id) {
        case 0x8005:
            b = func_0015c960(o, 1, -1, 0);
            if (!b) b = func_0015c960(o, 0, -1, 0);
            if (!b) b = (Bn9 *)mdl;
            if (!b) {
                PlatVu0CopyVector(out, &o->f10);
                break;
            }
            func_001315c0(o, b->f2, out, b->f4);
            out->y -= b->f8 * o->f44;
            break;
        case 0x8003:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                PlatVu0CopyVector(out, &tm.pos);
            } else {
                PlatVu0CopyVector(out, &o->f50);
            }
            break;
        case 0x8004:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                PlatVu0CopyVector(out, &tm.pos);
                out->y -= tm.a[2];
            } else {
                PlatVu0CopyVector(out, &o->f50);
            }
            break;
        case 0x8007:
            func_0012ec88(o, out);
            break;
        case 0x8006:
            if (mdl) {
                func_0015bad0(o, mdl, &tm);
                PlatVu0CopyVector(out, &tm.pos);
                out->y -= tm.a[2] * 1.5f;
            } else {
                PlatVu0CopyVector(out, &o->f50);
            }
            break;
        default:
            *(s32 *)&v.x = 0;
            *(s32 *)&v.y = 0;
            *(s32 *)&v.w = 0;
            v.z = t * 100.0f;
            switch (id) {
            case 0x8002:
                PlatVu0CopyVector(out, &o->f50);
                break;
            case 0x8008:
                v.x = v.z;
                *(s32 *)&v.z = 0;
                PlatVu0CopyVector(out, &o->f50);
                break;
            default:
                PlatVu0CopyVector(out, &o->f10);
                break;
            }
            PlatVu0ApplyMatrix(&v, o->fd0, &v);
            PlatVu0AddVector(out, out, &v);
            break;
        }
    } else {
        if (id == 48) {
            ln = o->f14c;
            if (ln) {
                rg = ln->f18;
                t = rg->f28 + t * (rg->f24 - rg->f28);
            }
        }
        id = func_00131558(o, id);
        if (id <= 0) PlatVu0CopyVector(out, &o->f10);
        else func_00162218(o->f15c, id, out, t);
    }
    out->w = 1.0f;
}
#undef func_00131558

/* func_001318e8 (from hand/text_00120000_h54.c). */
typedef struct { u8 pad[0xd0]; f32 fd0[4][4]; u8 p110[0x15c - 0x110]; s32 f15c; } E14;
extern s32 func_00122ff8(E14 *);
typedef f32 Mtx[4][4];
extern Mtx *func_001623e0(s32);
extern s32 func_00162368(s32, s32);
#define func_001315c0 ((void (*)(E14 *, s32, f32 *, f32)) func_001315c0)
#define func_00131558 ((s32 (*)(E14 *, s32)) func_00131558)
void func_001318e8(E14 *e, s32 id, f32 (*m)[4]) {
    if (!func_00122ff8(e)) {
        PlatVu0CopyMatrix(m, D_002C58D0);
        return;
    }
    if (id & 0x8000) {
        PlatVu0SubVector(m[0], &D_002C58A0, e->fd0[2]);
        PlatVu0SubVector(m[1], &D_002C58A0, e->fd0[1]);
        PlatVu0SubVector(m[2], &D_002C58A0, e->fd0[0]);
        func_001315c0(e, id, m[3], 0.0f);
    } else if (id & 0x2000) {
        id &= 0xfff;
        PlatVu0CopyMatrix(m, *(func_001623e0(e->f15c) + id));
    } else {
        id = func_00131558(e, id);
        if (id <= 0) {
            PlatVu0CopyMatrix(m, e->fd0);
        } else {
            id = func_00162368(e->f15c, id);
            PlatVu0CopyMatrix(m, *(func_001623e0(e->f15c) + id));
        }
    }
}
#undef func_001315c0
#undef func_00131558

/* func_00131a30 (from auto/text_00130000_8.c). */
void func_00121a78(s32, s32);
#define func_001318e8 ((void (*)(s32, s32, s32)) func_001318e8)
void func_00131a30(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[16];
    func_001318e8(arg0, arg1, (s32) sp);
    func_00121a78((s32) sp, arg2);
}
#undef func_001318e8

/* func_00131a68 (from auto/text_00130000_13.c). */
s32 func_00130190();
s32 func_00167698(s32);
f32 func_00131a68(void *arg0, s32 arg1) {
    return (f32) func_00167698(*(M2C_UNK *)((s32) (((func_00130190(arg0, arg1) & 0xFFFF) * 4)) + (s32) (M2C_FIELD(arg0, s32 *, 0x1D4))));
}

/* func_00131ab0 (from auto/text_00130000_8.c). */
extern f32 D_002BBDFC;
s32 func_00131ab0(void *arg0) {
    s32 var_v1;

    var_v1 = 0;
    if (!(M2C_FIELD(arg0, s32 *, 0x160) & 1) && (M2C_FIELD(arg0, f32 *, 0x170) == 0.0f) && (M2C_FIELD(arg0, f32 *, 0x280) <= (M2C_FIELD(arg0, f32 *, 0x16C) + (D_002BBDFC * M2C_FIELD(arg0, f32 *, 0x284))))) {
        var_v1 = 1;
    }
    return var_v1;
}

/* func_00131b08 (from auto/text_00130000.c). */
#define func_00131ab0 ((s32 (*)()) func_00131ab0)
s32 func_00131b08(void *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (func_00131ab0(arg0) != 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x178) == 0;
    }
    return var_v0;
}
#undef func_00131ab0

/* func_00131b50 (from hand/text_00120000_h31.c). */
typedef struct Ob50 Ob50;
typedef struct { u32 f0; u8 pad4[8]; void (*fc)(Ob50 *); } Sb50;
struct Ob50 { u32 f0; u8 pad4[0x15c]; u64 f160; u8 pad168[0x178 - 0x168]; s32 f178; Sb50 f17c; };
#define func_00131ab0 ((s32 (*)(Ob50 *)) func_00131ab0)
#define func_00131500 ((void (*)(Ob50 *)) func_00131500)
void func_00131b50(Ob50 *e) {
    Sb50 *s;
    e->f160 &= ~0x80;
    if (!func_00131ab0(e)) return;
    if (e->f178 <= 0) return;
    s = &e->f17c;
    if (s->f0 & 0x40000000) e->f0 &= ~4;
    if (s->f0 & 0x100000) func_00131500(e);
    if (s->fc) s->fc(e);
    e->f160 |= 0x80;
}
#undef func_00131ab0
#undef func_00131500

/* func_00131c08 (from auto/text_00130000_4.c). */
void func_00131c08(Actor *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    M2C_FIELD(arg0, f32 *, 0x288) = fparg0;
    arg0->unk160_64 = (s64) (arg0->unk160_64 | 0x40);
    arg0->unk28C = fparg1;
    M2C_FIELD(arg0, f32 *, 0x290) = fparg2;
}

/* func_00131c28 (from auto/text_00130000.c). */
void func_00131c28(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x284) = fparg0;
}

/* func_00131c30 (from auto/text_00130000.c). */
s32 func_00138858(u16);
void *func_001320a8();
s32 func_00131c30(u32 a) {
    void *temp_v0;

    temp_v0 = func_001320a8(a);
    if ((u16) M2C_FIELD(temp_v0, u16 *, 0x4C) >= 0x12CU) {
        return func_00138858(M2C_FIELD(temp_v0, u16 *, 0x4C));
    }
    return 0;
}

/* func_00131c78 (from hand/text_00130000_h6.c). */
typedef struct {
    u8 pad00[4];
    u32 flags;
    u8 pad08[0x1C - 0x8];
    f32 v1c[3];
    u8 pad28[4];
    f32 scale;
    u8 pad30[0x38 - 0x30];
    f32 v38[3];
} W6Node;
#define func_001320a8 ((W6Node *(*)(s32 a)) func_001320a8)
void func_00131c78(s32 a, s32 b) {
    W6Node *n = func_001320a8(a);
    if (b) {
        n->flags &= ~2;
    } else {
        n->flags |= 2;
    }
}
#undef func_001320a8

/* func_00131cc8 (from hand/text_00130000_h6.c). */
void func_00120c38(f32 *m, f32 *a, f32 *v);
void func_00121958(f32 *d, f32 *s, f32 *v);
#define func_001320a8 ((W6Node *(*)(s32 a)) func_001320a8)
void func_00131cc8(s32 a, f32 *m) {
    W6Node *n = func_001320a8(a);
    f32 v[4];
    f32 s;
    v[0] = n->v38[0];
    v[1] = n->v38[1];
    v[2] = n->v38[2];
    func_00120c38(m, D_002C58D0[0], v);
    v[0] = v[1] = v[2] = n->scale;
    func_00121958(m, m, v);
    m[12] = n->v1c[0];
    m[13] = n->v1c[1];
    m[14] = n->v1c[2];
    m[15] = 1.0f;
}
#undef func_001320a8

/* func_00131d68 (from auto/text_00130000_17.c). */
s32 func_001559a8(s32);
#define func_001320a8 ((s32 (*)(s32)) func_001320a8)
void func_00131d68(s32 arg0, s32 arg1) {
  s32 temp_a0;
  s32 temp_v0_2;
  s32 temp_v1;
  void *temp_s0;
  void *temp_v0;
  temp_s0 = func_001320a8(arg0);
 do { temp_v0 = *((void **) (((s8 *) temp_s0) + 8)); } while (0);
  temp_v1 = *((s32 *) (((s8 *) temp_v0) + 4));
  *((s32 *) (((s8 *) arg1) + 4)) = 0;
  *((void **) (((s8 *) arg1) + 0)) = (void *) (temp_v0 + temp_v1);
  *((s32 *) (((s8 *) arg1) + 8)) = func_001559a8(*((s32 *) (((s8 *) temp_s0) + 8)));
  temp_v0_2 = *((s32 *) (((s8 *) temp_s0) + 8));
  temp_a0 = *((s32 *) (((s8 *) temp_v0_2) + 8));
  if (((*((s32 *) (((s8 *) temp_v0_2) + 0xC))) - temp_a0) > 0)
  {
    *((s32 *) (((s8 *) arg1) + 0xC)) = (s32) (temp_v0_2 + temp_a0);
    return;
  }
  *((s32 *) (((s8 *) arg1) + 0xC)) = 0;
}
#undef func_001320a8

