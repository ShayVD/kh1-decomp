/* An object's motion: the motion table lookups (func_00130070 maps a motion
 * id through the object's table), the motion change every class calls
 * (func_00130340, func_00130398(o, motion, blend), func_00130578), the blend
 * and the per-frame motion update of the bone matrices (func_00130660,
 * func_00130f18). Flag mode: default (the other modes are in the sibling
 * files). Read from the code, not proved by a boot (docs/modules.md "Session
 * 53"). */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_002E31A8.h"
#include "data/pieces/D_00304BE8.h"
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002BC0F0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00350D88.h"
#include "data/bss_0051.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_002E31B8.h"
#include "data/types/text_00120000_h31_p.h"
#include "data/pieces/D_002E26AC.h"
#include "data/types/text_00120000_h31.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002BC098.h"
#include "data/pieces/D_002C58A0.h"
#include "vm/script_vm.h"

/* func_00130000 (from auto/text_00130000.c). */
s32 func_00130000(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x178) > 0;
}

/* func_00130010 (from auto/text_00130000.c). */
s32 func_00130010(void *arg0) {
    s32 var_v0;

    var_v0 = 1;
    if (!(M2C_FIELD(arg0, f32 *, 0x170) > 0.0f)) {
        var_v0 = 0;
    }
    return var_v0;
}

/* func_00130030 (from auto/text_00130000.c). */
s32 func_00130030(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x1CC) & 0x400000;
}

/* func_00130040 (from hand/text_00130000_h6.c). */
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
s32 func_00130040(W6Obj *o, s32 i) {
    if (o->s1d0.p == 0) {
        return 0;
    }
    return (o->s1d0.p[i] & 0xFFF) != 0xFFF;
}

/* func_00130070 (from hand/text_00120000_h31.c). */
extern u32 D_002C5958;
typedef struct { u8 pad[8]; u32 *f8; } O070;
u32 func_00130070(O070 *o, u32 v, s32 a2, s32 a3) {
    u32 *t;
    u32 w;
    u32 n, r;
    if ((v & 0x20000000) || !(t = o->f8)) return v;
    r = v & 0xffff;
    w = t[r];
    n = w & 0xfff;
    v &= 0xffff0000;
    if (n == 0xfff) return v | 0x200000;
    r = n;
    switch ((w >> 12) & 7) {
    case 1:
        r = n | 0x10000000;
        break;
    case 3:
        if (a2) {
            if (!((D_002C5958 >> 12) & 1) && a3) r = n + 2;
            else r = n + 1;
        }
        break;
    case 0:
        r = n | 0x8000000;
        break;
    case 4:
        if (!((D_002C5958 >> 12) & 1)) {
            if (a3 && a2) r = n + 1;
        }
        break;
    case 2:
        break;
    }
    if ((w >> 15) & 1) v |= 0x4000000;
    return r | v;
}

/* func_00130190 (from auto/text_00130000_17.c). */
#define func_00130070 ((s32 (*)(s32, s32, s32, s32)) func_00130070)
s32 func_00130190(s32 arg0, s32 arg1) {
  s32 var_a2;
  int new_var;
  new_var = arg0 + 0x1D0;
  var_a2 = 0;
  if (((*((s32 *) (((s8 *) arg0) + 0))) & 0x4000) || ((*((s32 *) (((s8 *) arg0) + 0x14C))) == 0))
  {
    var_a2 = 1;
  }
  return func_00130070(new_var, arg1, var_a2, ((s32) ((s32) ((s32) (((u64) (*((u64 *) (((s8 *) arg0) + 0x370)))) >> 0x32)))) & 1);
}
#undef func_00130070

/* func_001301d8 (from auto/text_00130000_13.c). */
#define func_00130070 ((s32 (*)()) func_00130070)
s32 func_001301d8(void *arg0) {
    return *(M2C_UNK *)((s32) (((func_00130070() & 0xFFFF) * 4)) + (s32) (M2C_FIELD(arg0, s32 *, 4)));
}
#undef func_00130070

/* func_00130210 (from auto/text_00130000_17.c). */
s32 func_00148a40(s32, s32);
void func_00130210(s32 arg0, s32 arg1) {
  s32 temp_a1;
  s32 temp_v1;
  s8 *new_var;
  new_var = (s8 *) (arg0 + 0x1D0);
  if (!(arg1 & 0x20000000))
  {
    temp_a1 = *((s32 *) (new_var + 8));
    if (temp_a1 != 0)
    {
      temp_v1 = (*((u16 *) (((s8 *) (((arg1 & 0xFFFF) * 4) + temp_a1)) + 2))) & 0xFFF;
      if (temp_v1 > 0)
      {
        func_00148a40(arg0, temp_v1 - 1);
      }
    }
  }
}

/* func_00130270 (from auto/text_00130000_4.c). */
s32 func_00130270(s32 *arg0, s32 arg1) {
    s32 temp_a2;
    s32 var_a1;

    var_a1 = arg1;
    if (var_a1 & 0x01000000) {
        temp_a2 = *arg0 | 4;
        var_a1 &= 0xFEFFFFFF;
        *arg0 = temp_a2;
        if (temp_a2 & 0x80) {
            *arg0 = temp_a2 | 0x100000;
        }
    }
    if (var_a1 & 0x800000) {
        *arg0 |= 0x1000;
    }
    return var_a1;
}

/* func_001302d0 (from hand/text_00130000_h6.c). */
W6Ent *func_001302d0(W6Obj *o, u32 flags, f32 a, f32 b) {
    W6Ent *e;
    if (flags & 0x1000000) {
        o->flags0 |= 4;
        flags &= ~0x1000000;
    }
    e = &o->ent[o->count++];
    e->flags = flags;
    e->a = a;
    e->b = b;
    e->d = 0;
    o->u160.f.b4 = 0;
    return e;
}

/* func_00130340 (from hand/text_00130000_h6.c). */
#define func_00130270 ((s32 (*)(W6Obj *o)) func_00130270)
W6Ent *func_00130340(W6Obj *o, f32 x) {
    W6Ent *e;
    o->count = 0;
    e = func_001302d0(o, func_00130270(o), 0.0f, x);
    o->u160.f.b0 = 1;
    return e;
}
#undef func_00130270

/* func_00130578 (from auto/text_00130000_4.c). */
#define func_001302d0 ((void *(*)(s32, s32, f32, f32)) func_001302d0)
void *func_00130578(s32 arg0, s32 arg1, f32 fparg0) {
    return func_001302d0(arg0, arg1, 0.0f, fparg0);
}
#undef func_001302d0

/* func_00130648 (from auto/text_00130000_4.c). */
void func_00130648(Actor *arg0) {
    arg0->unk290 = 0;
    arg0->unk288 = 0;
    arg0->unk28C = (f32) arg0->unk280;
}

/* func_00130898 (from hand/text_00120000_b02.c). */
typedef FVec4 V4;
typedef union { u64 x; struct { u32 b0:2; u32 b2:1; u32 b3:1; u32 b4:1; u32 b5:1; u32 b6:1; u32 b7:4; u32 b11:1; u32 b12:1; u32 r13:19; s32 hi; } b; } F160;
typedef union { u64 x; struct { u32 lo; u32 r0:13; u32 b45:1; u32 r46:4; u32 b50:1; u32 r51:13; } b; } F370;
typedef struct { s32 f0; f32 f4; f32 f8; f32 fc; } Q8e;
typedef struct {
    u32 f0;
    u8 p4[0x40 - 4];
    V4 f40;
    u8 p50[0x160 - 0x50];
    F160 f160;
    s32 f168;
    s32 f16c;
    f32 f170;
    s32 f174;
    s32 n;
    Q8e q[8];
    u8 p1fc[0x210 - 0x1fc];
    V4 f210;
    V4 f220;
    V4 f230;
    u8 p240[0x370 - 0x240];
    F370 f370;
} Ob8;
typedef struct { u8 p0[0x30]; V4 f30; } Ct8;
extern void func_001219c8(V4 *, V4 *, V4 *);
extern void func_00131500(Ob8 *);
extern void func_0013df40(Ob8 *, s32);
extern void func_0013dfa0(Ob8 *);
extern void func_00130660(Ob8 *, Ct8 *, s32, f32, f32);
#define func_00130190 ((s32 (*)(Ob8 *, s32)) func_00130190)
#define func_00130210 ((void (*)(Ob8 *, s32)) func_00130210)
void func_00130898(Ob8 *o, Ct8 *c) {
    V4 a;
    f32 b[4][4];
    Q8e *s = o->q;
    s32 r, hi, i;

    if (o->f160.b.b2) {
        if (s->f8 == 0.0f) {
            PlatVu0AddVector(&c->f30, &c->f30, &o->f210);
            PlatVu0CopyVector(&o->f220, &D_002C58A0);
        } else {
            PlatVu0TransposeMatrix(b, &o->f230);
            PlatVu0CopyVector(&a, &o->f210);
            a.w = 0.0f;
            PlatVu0ApplyMatrix(&o->f220, b, &a);
            if (o->f370.b.b45) func_001219c8(&o->f220, &o->f220, &o->f40);
        }
    } else {
        PlatVu0CopyVector(&o->f220, &D_002C58A0);
    }
    PlatVu0CopyVector(&o->f210, &D_002C58A0);
    if ((o->f160.b.hi = *(u16 *)s)) o->f370.b.b50 = D_002C5958 & 1;
    r = func_00130190(o, s->f0);
    if (o->f160.b.b5 && (r & 0x200000)) {
        func_00131500(o);
        r = func_00130190(o, s->f0);
    }
    hi = r & 0xffff0000;
    r &= 0xffff;
    if (hi & 0x10000000) {
        func_0013df40(o, 1);
        if (!(hi & 0x80000)) o->f370.b.b50 = 1;
    } else if (hi & 0x8000000) {
        func_0013dfa0(o);
    }
    if (hi & 0x40000000) o->f0 &= ~4;
    if (hi & 0x800000) o->f0 |= 0x1000;
    else o->f0 &= ~0x1000;
    o->f160.b.b12 = o->f160.b.b2;
    if (hi & 0x4000000) o->f160.b.b2 = 1;
    else o->f160.b.b2 = 0;
    o->f160.b.b3 = (hi >> 16) & 1;
    o->f160.b.b11 = (hi >> 18) & 1;
    o->f160.b.b6 = 0;
    func_00130660(o, c, r, s->f4, s->f8);
    for (i = 1; i < o->n; i++) o->q[i - 1] = o->q[i];
    o->n--;
    if (o->f170 == 0.0f) func_00130210(o, o->f160.b.hi);
}
#undef func_00130190
#undef func_00130210

/* func_00130c28 (from hand/text_00120000_h31.c). */
typedef struct { u32 f0; u8 pad[0x15c - 4]; s32 f15c; u8 pad160[0x324 - 0x160]; f32 f324; u8 pad328[0x39e - 0x328]; u8 f39e; } E10;
typedef struct { s32 type; u16 a; u16 b; s32 c; s32 d; } Ec28;
typedef struct { u8 pad0[0x15c]; s32 f15c; u8 pad160[8]; s32 f168; u8 pad16c[0x1d4 - 0x16c]; s32 *f1d4; } Oc28;
extern s32 func_00164f18(s32, s32, Ec28 *, s32, f32, f32);
extern void func_00146ff0(Oc28 *, u16, u16, s32);
void func_00130c28(Oc28 *e, f32 lo, f32 hi) {
    Ec28 buf[8];
    s32 n, j;
    n = func_00164f18(e->f15c, e->f1d4[e->f168], buf, 8, lo, hi);
    for (j = 0; j < n; j++) {
        switch (buf[j].type) {
        case 0:
            if (!((D_002C5958 >> 8) & 1)) func_0012c010((E10 *)e, buf[j].a, buf[j].b);
            break;
        case 1:
            if (!((D_002C5958 >> 10) & 1)) func_00146ff0(e, buf[j].a, buf[j].b, buf[j].c);
            break;
        }
    }
}

/* func_00130d20 (from hand/text_00120000_h31.c). */
typedef struct { u8 pad0[0x164]; s32 f164; s32 f168; u8 pad16c[0x1d4 - 0x16c]; s32 *f1d4; } Od20;
extern f32 func_0013fe10(Od20 *);
extern void func_00167698(s32);
f32 func_00130d20(Od20 *e) {
    f32 t;
    if ((u32)(e->f164 - 21) >= 2) return -1.0f;
    t = func_0013fe10(e);
    func_00167698(e->f1d4[e->f168]);
    if (e->f164 == 21) t = 1.0f - t;
    return (t < 0.0f) ? 0.0f : ((1.0f < t) ? 1.0f : t);
}

/* func_00130dd0 (from auto/text_00130000_4.c). */
f32 func_0026b9c0(f32, f32);
f32 func_00130dd0(Actor *arg0) {
    f32 var_f0;
    void *temp_a0;

    var_f0 = -1.0f;
    if (arg0->unk164 == 0xBF) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x98);
        var_f0 = M2C_FIELD(temp_a0, f32 *, 0x16C) / M2C_FIELD(temp_a0, f32 *, 0x280);
        if (arg0->unk000 & 0x800000) {
            var_f0 = func_0026b9c0(var_f0 + 0.5f, 1.0f);
        }
    }
    return var_f0;
}

