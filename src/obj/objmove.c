/* An object's movement on the ground: the ground ray (func_00142388),
 * steering toward a target (func_00142cf0, func_00142e30), the move with
 * wall collision against the collision entries D_003044D8 (func_00143180
 * itself stays in hand/nostrict/text_00130000_c02.c: a CONTEXT_ONLY copy is
 * here), and the per-state velocity through the class table D_00350D88
 * (func_00143eb8, func_00144060). Flag mode: default (the other modes are in
 * the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/bss_0052.h"
#include "data/bss_0053.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_002E26A0.h"
#include "data/types/text_00130000_h7.h"
#include "data/pieces/D_00304C70.h"
#include "m2c.h"
#include "actor.h"
#include "data/bss_0054.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00350D88.h"
#include "data/pieces/D_002C58B0.h"

/* func_00142470 (from hand/text_00130000_h7.c). */
typedef kh1_u128 u128;
typedef struct {
    u8 pad[0x350];
    u128 x350;
} W7Q;
void func_00142470(W7Q *o, u128 *v) {
    o->x350 = *v;
}

/* func_001425d0 (from auto/text_00140000.c). */
s32 func_001425d0(Actor *arg0) {
    s32 var_a1;

    var_a1 = 0;
    if ((arg0->unk000 & 0x200000) || (arg0->unk088 & 1) || (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), f32 *, 0x18) == 0.0f)) {
        var_a1 = 1;
    }
    return var_a1;
}

/* func_001426a8 (from hand/text_00130000_h7.c). */
void func_00118668(void *p);
typedef struct {
    f32 p[4];
    f32 d[4];
    u8 pad20[4];
    f32 x24;
    u8 pad28[8];
    s16 x30;
    u8 pad32[0x40 - 0x32];
} W7Ray;
s32 func_001426a8(f32 *pos, f32 r) {
    W7Ray t;
    PlatVu0CopyVector(t.p, pos);
    t.p[1] -= r;
    t.d[0] = 0.0f;
    t.p[3] = 1.0f;
    t.d[3] = 1.0f;
    t.d[1] = r + r;
    t.d[2] = 0.0f;
    func_00118668(&t);
    if (t.x30 >= 0) {
        pos[1] = t.x24;
        return t.x30 + 1;
    }
    return 0;
}

/* func_00142730 (from hand/text_00130000_h7.c). */
typedef struct {
    u8 pad00[0x48];
    s16 x48;
    s16 x4a;
    u16 x4c;
    u8 pad4e[0x54 - 0x4E];
    s8 x54;
    u8 pad55[0x5D - 0x55];
    u8 x5d;
} W7Info;
typedef struct {
    u8 pad00[0x5C];
    s32 x5c;
    u8 pad60[0x90 - 0x60];
    s32 x90;
    s32 x94;
    u8 pad98[0xB0 - 0x98];
    s32 xb0;
    u8 padb4[0xBC - 0xB4];
    s32 xbc;
} W7Ai;
typedef struct W7Ch W7Ch;
struct W7Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    u8 pad018[0x70 - 0x18];
    s32 x70;
    u8 pad074[0x130 - 0x74];
    W7Info *info;
    u8 pad134[0x148 - 0x134];
    union {
        W7Ai *p;
        s32 i;
    } x148;
    u8 pad14c[0x2CC - 0x14C];
    s32 x2cc;
    u8 pad2d0[0x2D4 - 0x2D0];
    f32 x2d4;
    u8 pad2d8[0x2DC - 0x2D8];
    union {
        u16 h;
        s32 i;
    } x2dc;
    u8 pad2e0[0x360 - 0x2E0];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W7Ch *x398;
};
s32 func_00137450(s32 a);
s32 func_00142730(W7Ch *o, s32 *out) {
    switch (o->x70) {
    case 13:
        *out = -1;
        return o->x148.p->x5c;
    case 15:
    case 16:
        *out = func_00137450(o->x148.p->x94);
        return o->x148.p->x90;
    }
    *out = o->x2cc;
    return o->x2dc.h;
}

/* func_00142b30 (from hand/text_00140000_h56.c). */
typedef struct { f32 x, y, z, w; } V4;
typedef struct {
    V4 p;
    V4 d;
    V4 h;
    s16 idx;
    s16 pad;
    s32 sub;
    s32 pad2[2];
} Ray;
void func_00118608(Ray *);
s32 func_00105b68(s32, s32);
#define func_00118668 ((void (*)(Ray *)) func_00118668)
s32 func_00142b30(u8 *o, f32 *v) {
    Ray r;
    f32 *pos = (f32 *)(o + 0x10);
    s32 res = 0;
    f32 t, d;

    PlatVu0CopyVector(&r.p.x, pos);
    r.p.y -= *(f32 *)(o + 0x2c4) * 0.5f;
    r.d.x = v[0];
    r.d.z = v[2];
    r.p.w = 1.0f;
    r.d.y = 0.0f;
    r.d.w = 1.0f;
    func_00118608(&r);
    if (r.idx >= 0) {
        if (func_00105b68(r.sub, r.idx)) res = 3;
    }
    PlatVu0AddVector(&r.p.x, pos, v);
    r.p.w = 1.0f;
    r.d.w = 1.0f;
    r.d.x = 0.0f;
    r.d.z = 0.0f;
    r.d.y = v[3] - v[1];
    func_00118668(&r);
    if (r.idx < 0) {
        res = 3;
    } else {
        d = r.h.y - *(f32 *)(o + 0x14);
        t = *(f32 *)(o + 0x2c4);
        if (d < -t * 0.5f) {
            res = 1;
        } else if (t < d) {
            res = 2;
        }
    }
    return res;
}
#undef func_00118668

/* func_00142c80 (from auto/text_00140000_15.c). */
#define func_00142b30 ((s32 (*)(void *, void *)) func_00142b30)
s32 func_00142c80(void *arg0, void *arg1) {
    s32 sp[4];    void *temp_v0;

    PlatVu0Normalize(sp, arg1);
    PlatVu0ScaleVector(sp, sp, 2.0f * M2C_FIELD(arg0, f32 *, 0x2C0));
    temp_v0 = M2C_FIELD(arg0, void **, 0x6C);
    M2C_FIELD(sp, f32 *, 0x4) = -M2C_FIELD(temp_v0, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(temp_v0, f32 *, 0x10) * 0.7f;
    return func_00142b30(arg0, sp);
}
#undef func_00142b30

/* func_00142e30 (from hand/text_00140000_s9_w1.c). */
typedef struct { f32 x, y, z, w; } V4f;
typedef struct { u8 pad[4]; f32 x4; f32 x8; f32 xc; f32 x10; } E30s;
typedef struct {
    u32 flags;
    u8 pad4[0x20 - 4];
    V4f x20;
    u8 pad30[0x6c - 0x30];
    E30s *x6c;
    s32 x70;
    u8 pad74[0x3d0 - 0x74];
    s32 x3d0;
} E30o;
extern f32 D_002BBDFC;
void func_0014cce0(E30o *o, f32 f);
void func_00130398(E30o *o, s32 k, f32 f);
void func_0014f658(E30o *o, s32 k);
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    V4f pos;
    V4f v20;
    V4f v30;
    u8 pad40[0x150 - 0x40];
    f32 f150;
} O2cf0;
void func_00121fc4(V4f *, V4f *);
f32 func_00121840(V4f *, V4f *);
void func_00121860(V4f *, V4f *, V4f *, f32);
f32 atan2f(f32, f32);
void func_00137688(O2cf0 *, f32);
CONTEXT_ONLY f32 func_00142cf0(O2cf0 *o, V4f *tg, f32 spd, f32 r) {
    V4f t;
    f32 d;
    PlatVu0SubVector(&t, tg, &o->pos);
    if (!(o->flags & 0x10)) t.y = 0;
    func_00121fc4(&t, &t);
    if (r == 0.0f) {
        f32 k;
        r = func_00121840(&o->v30, &t);
        k = t.w / spd * 0.3f;
        if (k > 1.0f) r /= k;
    }
    d = t.w;
    if (d < spd) spd = d;
    func_00121860(&o->v30, &t, &t, r);
    o->f150 = atan2f(t.x, t.z);
    func_00137688(o, o->f150);
    t.w = spd;
    PlatVu0CopyVector(&o->v20, &t);
    return d;
}
/* func_00142e30: needs CONTEXT_ONLY func_00142cf0 and func_00142c80 above (plain beq/bnezl slots).
   One shared `end: return d;` (no return-value local): d has 3 refs, so z (0.0f) wins f21. */
f32 func_00142e30(E30o *o, V4f *tg, s32 mode) {
    s32 an = -1;
    f32 spd;
    f32 z;
    f32 d;
    s32 n;
    switch (mode & 0xffff) {
    case 0:
        an = 1;
        spd = o->x6c->x4;
        break;
    case 1:
        an = 2;
        spd = o->x6c->x8;
        break;
    case 2:
        spd = o->x6c->xc;
        break;
    default:
        spd = 0.0f;
        break;
    }
    z = 0.0f;
    d = func_00142cf0((O2cf0 *)o, tg, spd, z);
    if (d < spd * D_002BBDFC) return z;
    if (o->x70 == 2) goto end;
    if (o->flags & 0x100) goto end;
    n = ((s32 (*)(E30o *, V4f *)) func_00142c80)(o, &o->x20);
    if (n > 0) {
        if (n >= 3) {
            if (n == 3) return -1.0f;
        } else {
            if (mode & 0x10000) return -1.0f;
            an = -1;
            func_0014cce0(o, o->x6c->x10);
            func_00130398(o, (o->x3d0 + 4) | 0x10000, z);
            func_0014f658(o, 2);
        }
    }
    if (an >= 0) func_00130398(o, an, 8.0f);
end:
    return d;
}

/* func_00142fe0 (from auto/text_00140000_2.c). */
M2C_UNK func_001374a8(void *);
void func_00142fe0(void *arg0, void *arg1) {
    void *temp_v0;
    void *temp_v0_2;

    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) == 0) {
        func_001374a8(arg1);
    }
    temp_v0 = M2C_FIELD(arg0, void **, 8);
    if ((temp_v0 == NULL) || ((u16) M2C_FIELD(M2C_FIELD(arg1, void **, 0x130), u16 *, 0x4C) < (u16) M2C_FIELD(M2C_FIELD(temp_v0, void **, 0x130), u16 *, 0x4C))) {
        M2C_FIELD(arg0, void **, 8) = arg1;
    }
    temp_v0_2 = M2C_FIELD(arg1, void **, 8);
    if ((temp_v0_2 == NULL) || ((u16) M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C) < (u16) M2C_FIELD(M2C_FIELD(temp_v0_2, void **, 0x130), u16 *, 0x4C))) {
        M2C_FIELD(arg1, void **, 8) = arg0;
    }
}

/* func_00143660 (from hand/text_00140000_h56.c). */
typedef struct { u8 pad[0x18]; f32 f18; u8 pad1c[0x54 - 0x1c]; s8 b54; } Prm130;
typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    u8 pad20[0x70 - 0x20];
    s32 st70;
    u8 pad74[0x120 - 0x74];
    f32 v120[4];
    Prm130 *p130;
} Ch;
f32 func_00121748(f32 *, f32 *);
#define func_001425d0 ((s32 (*)(Ch *)) func_001425d0)
void func_00143660(Ch *a, f32 *dir, Ch *b, f32 *out) {
    f32 t[4];
    f32 fa, fb;

    if (func_001425d0(a)) {
        if (func_001425d0(b)) {
            switch (a->st70) {
            case 10:
                if (func_00121748(out, dir) > 0.0f) {
                    PlatVu0CopyVector(out, dir);
                    out[1] = 0.0f;
                    return;
                }
                break;
            case 13:
                PlatVu0SubVector(out, b->pos, a->pos);
                if (func_00121748(out, dir) >= 0.0f) {
                    PlatVu0CopyVector(out, dir);
                    return;
                }
                break;
            default:
                PlatVu0CopyVector(out, dir);
                return;
            }
        } else if (a->p130->b54 == 9) {
            PlatVu0SubVector(out, b->pos, a->pos);
            if (func_00121748(out, dir) >= 0.5f) {
                PlatVu0CopyVector(out, dir);
                return;
            }
        }
        PlatVu0CopyVector(out, (*(f32 (*)[0x4])&D_002C58B0));
    } else if (!func_001425d0(b)) {
        fa = a->p130->f18;
        fb = b->p130->f18;
        PlatVu0ScaleVector(t, out, fa / (fa + fb));
        PlatVu0ScaleVector(out, t, fb / fa);
        PlatVu0AddVector(b->v120, b->v120, t);
    }
}
#undef func_001425d0

/* func_00143818 (from hand/text_00140000_h56.c). */
typedef struct { u8 x[20]; } Col20;
typedef struct { u8 pad[5]; u8 n; u8 pad6[0xe]; Col20 *cols; } ColSet;
typedef struct {
    u8 pad0[0x98];
    void *o98;
    u8 pad9c[0x134 - 0x9c];
    ColSet *cs;
    u8 pad138[0x398 - 0x138];
    void *o398;
    u8 pad39c[0x3a4 - 0x39c];
    u32 mask;
} Ch2;
typedef struct { f32 a[4]; f32 b[4]; f32 c[8]; } Cap;
s32 func_00123330(Ch2 *);
Cap *func_00122048(s32, s32);
void func_001220b8(Cap *);
Ch2 *func_001230a0(Ch2 *);
void func_0015bad0(Ch2 *, Col20 *, void *);
s32 func_0015b998(Cap *, void *);
void func_0015c5d0(Cap *, void *, f32 *);
#define func_00142fe0 ((void (*)(Ch2 *, Ch2 *)) func_00142fe0)
void func_00143818(Ch2 *a, f32 *v) {
    Cap *cap;
    Ch2 *o;
    s32 i, j;
    f32 t[4];

    if (!func_00123330(a)) return;
    cap = func_00122048(0x40, 0x10);
    for (i = 0; i < a->cs->n; i++) {
        if (a->mask & (1 << i)) continue;
        o = NULL;
        func_0015bad0(a, &a->cs->cols[i], cap);
        PlatVu0AddVector(cap->b, cap->b, v);
        while ((o = func_001230a0(o)) != NULL) {
            if (o == a) continue;
            if (!func_00123330(o)) continue;
            if (o == a->o398) continue;
            if (o->o398 == a) continue;
            if (o == a->o98) continue;
            if (o->o98 == a) continue;
            for (j = 0; j < o->cs->n; j++) {
                if (o->mask & (1 << j)) continue;
                func_0015bad0(o, &o->cs->cols[j], cap->c);
                if (func_0015b998(cap, cap->c)) {
                    func_0015c5d0(cap, cap->c, t);
                    func_00143660((Ch *)a, v, (Ch *)o, t);
                    PlatVu0SubVector(cap->b, cap->b, t);
                    PlatVu0SubVector(v, v, t);
                    func_00142fe0(a, o);
                }
            }
        }
    }
    func_001220b8(cap);
}
#undef func_00142fe0

