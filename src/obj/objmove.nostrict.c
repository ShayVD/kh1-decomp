/* An object's movement on the ground: the ground ray (func_00142388),
 * steering toward a target (func_00142cf0, func_00142e30), the move with
 * wall collision against the collision entries D_003044D8 (func_00143180),
 * and the per-state velocity through the class table D_00350D88
 * (func_00143eb8, func_00144060). Flag mode: nostrict (the other modes are
 * in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 53"). */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/bss_0053.h"
#include "data/pieces/D_002C58A0.h"
#include "data/types/nostrict_text_00140000_h33.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_00304B78.h"
#include "data/pieces/D_003044E0.h"
#include "data/pieces/D_002E27C8.h"
#include "data/bss_0052.h"
#include "data/types/nostrict_text_00130000_h55.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_0037A378.h"
#include "vm/script_vm.h"
#include "data/pieces/D_00350CE0.h"
#include "data/pieces/D_00351BC8.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_003044D8.h"
#include "data/pieces/D_0035C710.h"
#include "data/types/nostrict_text_00130000_b03_p3.h"
#include "data/pieces/D_00304BE8.h"
#include "data/pieces/D_00350D88.h"

/* func_00142388 (from hand/nostrict/text_00140000_h33.c). */
typedef FVec4 V4f;
typedef struct { V4f p; V4f d; V4f hit; s16 h30; s32 w34; u8 pad38[8]; } Ray;
typedef struct { u8 pad[0x350]; s32 a[4]; } Mdl;
void func_00118668(Ray *);
void func_00105c98(s32, s32 *);
s32 func_00105bc0(s32, s32);
s32 func_00142388(V4f *p, s32 *out) {
    Ray r;
    s32 i;
    PlatVu0CopyVector(&r.p, p);
    r.p.w = 1.0f;
    r.d.x = 0;
    r.d.y = 100000.0f;
    r.d.z = 0;
    r.d.w = 1.0f;
    func_00118668(&r);
    if (r.h30 >= 0) {
        if (r.w34 == -1) {
            func_00105c98(r.h30, out);
        } else {
            Mdl *m = D_003044E0[r.w34].x0;
            for (i = 0; i < 4; i++) {
                out[i] = m->a[i];
            }
        }
        return func_00105bc0(r.w34, r.h30);
    }
    return 0;
}

/* func_00142480 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { f32 pos[4]; f32 dir[4]; f32 hit[4]; s16 id; s16 pad32; s32 x34; } W55Ray;
s32 func_00105b68(s32 a, s32 b);
void func_00118628(W55Ray *r, s32 m);
f32 func_00120c18(f32 *v);
s32 func_00142480(f32 *from, f32 *vec, s32 mask, f32 *out) {
    W55Ray r;
    s32 n, i;
    PlatVu0CopyVector(r.pos, from);
    n = func_00120c18(vec) / 100.0f;
    if (n >= 2) {
        PlatVu0ScaleVector(r.dir, vec, 1.0f / n);
    } else {
        PlatVu0CopyVector(r.dir, vec);
        n = 1;
    }
    r.dir[3] = 1.0f;
    for (i = 0; i < n; i++) {
        r.pos[3] = 1.0f;
        func_00118628(&r, mask);
        if (r.id >= 0) {
            PlatVu0CopyVector(out, r.hit);
            return func_00105b68(r.x34, r.id);
        }
        PlatVu0AddVector(r.pos, r.pos, r.dir);
    }
    return -1;
}

/* func_00142618 (from hand/nostrict/text_00130000_s6_06.c). */
typedef struct W606Ch W606Ch;
struct W606Ch {
    u32 flags;
    f32 x4[4];
    f32 x14;
    f32 x18;
    f32 x1c;
    u8 pad020[0x6c - 0x20];
    void *x6c;
    s32 x70;
    u8 pad074[0x130 - 0x74];
    u8 *info;
    u8 pad134[0x148 - 0x134];
    s32 x148;
    u8 pad14c[0x2D4 - 0x14C];
    f32 x2d4;
    u8 pad2d8[0x360 - 0x2D8];
    s32 x360;
    u8 pad364[0x370 - 0x364];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    W606Ch *x398;
};
f32 func_00144368(W606Ch *o);
s32 func_00142618(W606Ch *o) {
    W606Ch *p = o->x398;
    s32 r;
    f32 d;
    if (p != 0 && !((p->x370 >> 39) & 1)) {
        r = p->info[0x5d];
    } else {
    r = o->x360;
    if (o->x14 >= o->x2d4) {
        d = func_00144368(o);
        if (d < 20.0f) r = 10;
        else if (d < 50.0f) r = 11;
        else r = 12;
    }
    }
    return r;
}

/* func_001427d0 (from hand/nostrict/text_00130000_h55.c). */
typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor_427d0 {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 pos[4];
    f32 x20[4];
    u8 pad30[0x3c - 0x30];
    f32 x3c;
    f32 x40;
    f32 x44;
    u8 pad48[0x6c - 0x48];
    W55Mv *x6c;
    u32 x70;
    u8 pad74[0x98 - 0x74];
    void *x98;
    u8 pad9c[0x120 - 0x9c];
    f32 x120[4];
    W55Inf *x130;
    W55Mdl *x134;
    u8 pad138[0x148 - 0x138];
    f32 *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x2c0 - 0x154];
    f32 x2c0;
    f32 x2c4;
    u8 pad2c8[0x2de - 0x2c8];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x316 - 0x30e];
    u16 x316;
    u8 pad318[0x370 - 0x318];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 b39:1; u32 hi:24; } b; } x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x3c0 - 0x39c];
    f32 x3c0[4];
    u8 pad3d0[0x444 - 0x3d0];
    s32 x444;
    u8 pad448[0x488 - 0x448];
    W55Fx *x488;
    s32 x48c;
} W55Ob;
typedef struct { f32 pos[4]; u8 pad10[0x10]; f32 x20; f32 x24; s32 x28; } W55Col;
s32 func_0014f5c8(W55Ob *o);
s32 func_0014f600(W55Ob *o);
f32 func_001427d0(W55Ob *o, W55Col *c) {
    if ((u32)(o->x70 - 18) < 2) {
        c->x24 = o->x134->x10->x8;
        c->x20 = 25.0f;
    } else if (o->x0 & 0x4000000) {
        c->x24 = o->x134->x10->x8;
        c->x20 = o->x134->x10->xc;
    } else {
        c->x24 = o->x134->x10->x8 * o->x44;
        c->x20 = o->x134->x10->xc * o->x40;
    }
    PlatVu0CopyVector(c->pos, o->pos);
    c->pos[3] = 1.0f;
    c->x28 = 0;
    if (o->x398 || func_0014f5c8(o) || func_0014f600(o)) c->x28 |= 1;
    if (o->x370.b.b39 || (o->x130->x4 & 0x200)) c->x28 |= 2;
    if (o->x370.b.kind == 2 || (o->x0 & 0x100)) {
        if (func_0014f5c8(o)) c->x28 |= 0x10;
        else c->x28 |= 4;
    } else {
        switch (((u8 *)o)[6]) {
        case 9: case 10:
            if (o->x130->x54 == 9) c->x28 |= 8;
            else c->x28 |= 0x40;
            break;
        case 8:
            c->x28 |= 0x20;
            break;
        }
    }
    return (c->x20 < c->x24 ? c->x20 : c->x24) * 0.7f;
}

/* func_001429f8 (from hand/nostrict/text_00130000_s6_na.c). */
typedef struct { f32 x, y, z, w; } V4f_429f8;
typedef struct { V4f_429f8 p; V4f_429f8 d; V4f_429f8 hit; s16 h30; s32 w34; u8 pad38[8]; } Ray_429f8;
s32 func_00119688(Ray_429f8 *);
void func_00118648(Ray_429f8 *);
void func_00118608(Ray_429f8 *);
s32 func_001429f8(V4f_429f8 *a, V4f_429f8 *b, V4f_429f8 *c) {
    Ray_429f8 r;
    f32 x, y, z;
    f32 one;
    x = a->x;
    one = 1.0f;
    y = a->y + b->y;
    z = a->z;
    r.p.x = x;
    r.p.z = z;
    r.p.y = y;
    r.p.w = one;
    PlatVu0ScaleVector(&r.d, b, 1.5f);
    r.d.w = one;
    r.d.y = 0;
    if (func_00119688(&r) >= 0) return 3;
    func_00118648(&r);
    if (r.h30 >= 0) return 3;
    r.p.x += b->x;
    r.p.z += b->z;
    r.d.x = 0;
    r.d.y = b->w - b->y;
    r.d.z = 0;
    func_00118608(&r);
    if (r.h30 < 0) return 3;
    PlatVu0CopyVector(c, &r.hit);
    func_00118648(&r);
    if (r.h30 >= 0 && r.hit.y < c->y) return 3;
    return 0;
}

/* func_00142cf0 (from hand/nostrict/text_00140000_h33.c). */
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
f32 func_00142cf0(O2cf0 *o, V4f *tg, f32 spd, f32 r) {
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

/* func_00143080 (from hand/nostrict/text_00130000_s6_06.c). */
typedef struct { f32 x, y, z, w; } W606V4f;
typedef struct { u8 pad[0x30]; u64 d30; u8 pad38[8]; W606V4f p; f32 f50; f32 f54; u8 pad58[4]; s32 w5c; } W606S148;
typedef struct {
    u32 flags;
    u8 pad4[0xC];
    W606V4f pos;
    u8 pad20[0x148 - 0x20];
    W606S148 *p148;
    u8 pad14c[0x1CC - 0x14C];
    u32 w1cc;
    u8 pad1d0[0x2A0 - 0x1D0];
    W606V4f v2a0;
    W606V4f v2b0;
    f32 f2c0;
    u8 pad2c4[0x2D0 - 0x2C4];
    u32 w2d0;
    u8 pad2d4[0x2F0 - 0x2D4];
    W606V4f v2f0;
    f32 f300;
    f32 f304;
    u8 pad308[0x314 - 0x308];
    u16 h314;
} W606F3;
s32 func_001166e8(W606V4f *);
#define func_001429f8 ((s32 (*)(W606V4f *, W606V4f *, W606V4f *)) func_001429f8)
s32 func_00143080(W606F3 *o, W606V4f *v) {
    W606V4f t, hit;
    s32 r = 1;
    if (!func_001166e8(&o->v2a0) && !(o->w2d0 & 1)) return r;
    PlatVu0Normalize(&t, v);
    PlatVu0ScaleVectorXYZ(&t, &t, o->f2c0 + 10.0f);
    t.y = -200.0f;
    t.w = 200.0f;
    if (func_001429f8(&o->v2a0, &t, &hit)) goto zero;
    PlatVu0SubVector(&o->v2b0, &hit, &o->v2a0);
    o->v2b0.w = 1.0f;
    if (func_001166e8(&o->v2a0) && (o->w2d0 & 1)) goto zero;
    return 1;
zero:
    return 0;
}
#undef func_001429f8

/* func_00143180 (from hand/nostrict/text_00130000_c02.c, session 54). */
typedef f32 C02V4[4] __attribute__((aligned(16)));
typedef struct {
    C02V4 v00;      /* 0x2A0 */
    C02V4 v10;      /* 0x2B0 */
    u8 pad20[0x28 - 0x20];
    u32 x28;        /* 0x2C8 */
    u8 pad2c[0x30 - 0x2C];
    u32 x30;        /* 0x2D0 */
    u8 pad34[0x3E - 0x34];
    u16 x3e;        /* 0x2DE */
    C02V4 v40;      /* 0x2E0 */
    u8 pad50[0x6E - 0x50];
    u16 x6e;        /* 0x30E */
    u8 pad70[0x80 - 0x70];
} C02Mv;
typedef struct {
    u8 pad00[4];
    u32 x4;
} C02Desc2;
typedef struct {
    u8 pad00[0x90];
    s32 x90;
} C02Tgt;
typedef struct Actor_43180 {
    u32 x0;
    u8 pad04[0x70 - 0x4];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    u64 x90;
    u8 pad98[0x130 - 0x98];
    C02Desc2 *desc;
    u8 pad134[0x148 - 0x134];
    C02Tgt *x148;
    u8 pad14c[0x2A0 - 0x14C];
    C02Mv mv;
    u8 pad320[0x370 - 0x320];
    union {
        u64 w;
        struct {
            u64 lo : 53;
            u64 b53 : 1;
            u64 b54 : 2;
            u64 b56 : 1;
            u64 b57 : 1;
            u64 hi : 6;
        } b;
    } fl;
    u8 pad378[0x398 - 0x378];
    s32 x398;
} C02Ob2;
void func_00142fe0(C02Ob2 *o, C02Ob2 *p);
void func_0014d070(C02Ob2 *o, f32 *v);
f32 func_00121748(void *a, f32 *v);
f32 func_00120bf8(void *a);
#define func_001166e8 ((u64 (*)(C02Mv *m)) func_001166e8)
#define func_00143080 ((s32 (*)(C02Ob2 *o, f32 *v)) func_00143080)
void func_00143180(C02Ob2 *o, f32 *v)
{
    C02V4 d;
    C02Mv save;
    C02Mv tmp;
    u32 fl0;
    s32 i, n;
    u16 k;

    if ((o->desc->x4 & 0x2000) && ((s32)(o->fl.w >> 53) & 1) && o->x398 == 0
        && v[0] == 0.0f && v[1] == 0.0f && v[2] == 0.0f)
        return;
    fl0 = o->mv.x30;
    for (;;) {
        PlatVu0CopyVector(o->mv.v10, v);
        o->mv.v10[3] = 1.0f;
        save = o->mv;
        PlatVu0CopyVector(save.v40, o->mv.v00);
        if (o->x0 & 0x100) {
            if (!func_00143080(o, v)) {
                o->mv = save;
                PlatVu0CopyVector(o->mv.v40, o->mv.v00);
            }
        } else {
            n = 0;
            o->x90 = func_001166e8(&o->mv);
            for (i = 0; i < 32; i++) {
                if ((o->x90 >> i) & 1) {
                    if (i > 0) {
                        func_00142fe0(o, ((C02Ob2 *)D_003044D8[i - 1].x8));
                        if ((s32)(((C02Ob2 *)D_003044D8[i - 1].x8)->fl.w >> 57) & 1)
                            n++;
                    } else {
                        n++;
                    }
                }
            }
            if (n >= 2) {
                tmp = o->mv;
                PlatVu0CopyVector(tmp.v00, tmp.v40);
                PlatVu0CopyVector(tmp.v10, &D_002C58A0);
                if (func_001166e8(&tmp)) {
                    o->mv = save;
                    o->mv.x28 |= 0x80000000;
                }
            }
        }
        switch (o->x70) {
        case 2:
        case 3:
            func_0014d070(o, v);
            break;
        case 10:
            PlatVu0SubVector(o->mv.v10, o->mv.v40, o->mv.v00);
            if (v[0] != 0.0f || v[2] != 0.0f) {
                if (o->mv.x3e == 0xFFFF || func_00121748(o->mv.v10, v) < 1.0f) {
                    v[2] = 0.0f;
                    v[0] = 0.0f;
                    continue;
                }
            } else if (o->mv.x3e == 0xFFFF) {
                PlatVu0CopyVector(v, &D_002C58A0);
                PlatVu0CopyVector(o->mv.v40, o->mv.v00);
                o->mv.x3e = 0;
            }
            break;
        case 15:
            PlatVu0SubVector(d, o->mv.v40, o->mv.v00);
            if (func_00120bf8(d) > 15.0f)
                o->x148->x90 = 0xFFFF;
            PlatVu0CopyVector(o->mv.v40, o->mv.v00);
            break;
        case 18:
            if (o->mv.x6e == 0xFFFF) {
                if (o->mv.x30 & 0x20) {
                    o->mv.x6e = 0;
                } else if (!(fl0 & 0x20)) {
                    if (v[0] == 0.0f && v[2] == 0.0f) {
                        PlatVu0CopyVector(o->mv.v40, o->mv.v00);
                        o->mv.x6e = 0;
                    } else {
                        v[0] = v[2] = 0.0f;
                        continue;
                    }
                }
            }
            break;
        }
        break;
    }
    PlatVu0SubVector(v, o->mv.v40, o->mv.v00);
    o->fl.b.b53 = 1;
    o->fl.b.b56 = 1;
}
#undef func_001166e8
#undef func_00143080

/* func_00143a70 (from hand/nostrict/text_00130000_b03.c). */
s32 func_0015c738(B3Ob *, f32 *);
void func_00137440(B3Ob *, s32);
void func_00143818(B3Ob *, f32 *, s32);
void func_00151b98(B3Ob *, f32 *);
void func_001337e0(s32 a, void *b, s32 c);
void func_00117710(f32 *, f32 *);
#define func_001427d0 ((f32 (*)(B3Ob *, f32 *)) func_001427d0)
#define func_00121fc4 ((void (*)(f32 *, f32 *)) func_00121fc4)
#define func_00143180 ((void (*)(B3Ob *, f32 *)) func_00143180)
void func_00143a70(B3Ob *o, f32 *v, s32 a2) {
    f32 t[4];
    f32 f, step;
    u32 fl;
    u16 last;
    B3Ob *p;
    s32 i;
    u16 k;

    f = func_001427d0(o, o->x2a0);
    step = (f < o->x4ac) ? f : o->x4ac;
    o->x4ac = f;
    if (o->x398) o->x370 &= ~0x20000000000000ULL;
    func_00137440(o, func_0015c738(o, v));
    func_00143818(o, v, a2);
    func_00121fc4(t, v);
    if (t[3] / step > 4.0f) t[3] = step * 4.0f;
    last = 0;
    fl = 1;
    do {
        if (step < t[3]) {
            PlatVu0ScaleVector(v, t, step);
            t[3] -= step;
        } else {
            PlatVu0ScaleVector(v, t, t[3]);
            t[3] = 0.0f;
        }
        func_001427d0(o, o->x2a0);
        func_00143180(o, v);
        fl |= o->x2d0 & ~1;
        fl &= (o->x2d0 & 1) | ~1;
        if (o->x130->x4c == 201) func_00151b98(o, v);
        PlatVu0AddVector(o->x10, o->x10, v);
        if (o->x2d8) {
            k = o->x2d8;
            if (k != last) {
                if ((o->x2d0 & 4) || o == D_002E26A0[0]) {
                    func_001337e0(-2, o, k);
                }
                last = o->x2d8;
            }
        }
        o->x448 = o->x2d8;
    } while (t[3] > 0.0f);
    o->x2d0 = fl;
    func_00117710(o->x2a0, o->x320);
    PlatVu0Normalize(o->xc0, o->x340);
    o->xcc = 1.0f;
    p = o->x398;
    if (o->x2cc != -1) {
        p = D_003044E0[o->x2cc].x0;
        if (!(o->x2d0 & 1)) func_00137440(o, (s32)p);
    }
    if (p) {
        for (i = 0; i < 4; i++) o->x350[i] = p->x350[i];
    }
}
#undef func_001427d0
#undef func_00121fc4
#undef func_00143180

/* func_00143d20 (from hand/nostrict/text_00140000_h56.c). */
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
s32 func_00123330(Ch2 *);
void func_0015bad0(Ch2 *, Col20 *, void *);
typedef struct Ch3 {
    u8 pad0[6];
    u8 kind;
    u8 pad7[9];
    f32 pos[4];
    u8 pad20[0x50 - 0x20];
    f32 v50[4];
    u8 pad60[0x324 - 0x60];
    f32 f324;
    u8 pad328[0x350 - 0x328];
    s32 w350[4];
    u8 pad360[0x398 - 0x360];
    Ch2 *o398;
    u8 pad39c[2];
    s8 b39e;
    u8 pad39f;
    struct Ch3 *o3a0;
    u8 pad3a4[0x3d4 - 0x3a4];
    f32 f3d4;
} Ch3;
s32 func_001232f0(Ch3 *);
#define func_00142388 ((s8 (*)(f32 *, s32 *)) func_00142388)
#define func_00142618 ((s8 (*)(Ch3 *)) func_00142618)
#define func_00143a70 ((void (*)(Ch3 *, f32 *, void *)) func_00143a70)
void func_00143d20(Ch3 *o, f32 *v, void *arg) {
    f32 a[4];
    f32 b[4];
    f32 c[8];
    s32 i;

    PlatVu0CopyVector(a, v);
    PlatVu0CopyVector(b, o->pos);
    if (func_001232f0(o)) {
        func_00143a70(o, a, arg);
        o->b39e = func_00142618(o);
        if (o->o398 && func_00123330(o->o398)) {
            func_0015bad0(o->o398, o->o398->cs->cols, c);
            o->f3d4 = c[5] - c[2] - o->pos[1];
        } else {
            o->f3d4 = o->f324 - o->pos[1];
        }
    } else {
        PlatVu0AddVector(o->pos, o->pos, a);
        o->f3d4 = 0.0f;
        if ((u32)(o->kind - 2) < 2) {
            PlatVu0CopyVector(b, o->v50);
            b[1] -= 100.0f;
            o->b39e = func_00142388(b, o->w350);
        } else if (o->o3a0 && o->o3a0->kind == 3) {
            for (i = 0; i < 4; i++) {
                o->w350[i] = o->o3a0->w350[i];
            }
        }
    }
    PlatVu0SubVector(a, o->pos, b);
}
#undef func_00142388
#undef func_00142618
#undef func_00143a70

/* func_00143eb8 (from hand/nostrict/text_00140000_h56.c). */
typedef void (*MvFn)(void *, f32 *);
extern f32 D_002BBDFC;
typedef struct {
    u8 pad0[0x20];
    f32 v20[3];
    f32 f2c;
    u8 pad30[0x70 - 0x30];
    s32 st70;
    u8 pad74[0x88 - 0x74];
    s32 w88;
    u8 pad8c[0x120 - 0x8c];
    f32 v120[4];
    u8 pad130[0x160 - 0x130];
    u64 w160;
    u8 pad168[0x200 - 0x168];
    f32 v200[4];
} Mv;
void func_0014f798(Mv *, f32 *);
void func_001568e8(Mv *, f32 *);
void func_001564e0(Mv *, f32 *);
void func_00143eb8(Mv *o, f32 *v) {
    f32 t[4];
    MvFn fn;

    switch (o->st70) {
    case 9:
    case 10:
    case 22:
    case 23:
        PlatVu0ScaleVectorXYZ(v, o->v20, o->f2c * D_002BBDFC);
        break;
    case 18:
        PlatVu0ScaleVectorXYZ(v, o->v20, D_002BBDFC);
        break;
    case 20:
        PlatVu0CopyVector(v, o->v20);
        break;
    case 19:
        PlatVu0CopyVector(v, (*(f32 (*)[0x4])&D_002C58A0));
        break;
    default:
        fn = D_00350D88[o->st70].f10;
        if (fn) {
            fn(o, v);
        } else {
            func_0014f798(o, v);
        }
        break;
    }
    if ((D_00350D88[o->st70].f0 >> 3) & 1) {
        func_001568e8(o, t);
        PlatVu0AddVector(v, v, t);
    }
    if (o->w88 & 0x40) {
        func_001564e0(o, v);
    }
    if ((s32)(o->w160 >> 2) & 1) {
        PlatVu0AddVector(v, v, o->v200);
    }
    PlatVu0AddVector(v, v, o->v120);
}

/* func_00144060 (from hand/nostrict/text_00140000_h56.c). */
typedef s32 (*StFn)(void *, s32);
typedef struct {
    u32 flags;
    u8 pad4[0x10];
    f32 y;
    u8 pad18[0x70 - 0x18];
    s32 st70;
    u8 pad74[0x2d0 - 0x74];
    u32 w2d0;
    f32 f2d4;
    u8 pad2d8[0x398 - 0x2d8];
    void *o398;
} St;
void func_0012c698(St *);
s32 func_001443a8(St *);
#define func_0014f5c8 ((s32 (*)(St *)) func_0014f5c8)
#define func_0014f600 ((s32 (*)(St *)) func_0014f600)
s32 func_00144060(St *o) {
    s32 s1;
    StFn fn;

    if (o->y >= o->f2d4) {
        if ((func_0014f5c8(o) || func_0014f600(o)) && !(o->flags & 0x400000)) {
            func_0012c698(o);
        }
        o->flags |= 0x400000;
    } else {
        o->flags &= ~0x400000;
    }
    s1 = 0;
    if (o->w2d0 & 1) {
        s1 = o->o398 == 0;
    }
    switch (o->st70) {
    case 11:
    case 19:
    case 20:
    case 22:
    case 23:
        return o->st70;
    case 16:
        if (s1) return o->st70;
        break;
    case 17:
        if (func_001443a8(o)) return o->st70;
        if (s1) return o->st70;
        break;
    default:
        fn = (StFn)D_00350D88[o->st70].f14;
        if (fn) return fn(o, s1);
        if (s1) goto two;
        break;
    }
    if (!(o->flags & 0x1000)) return 0;
two:
    return 2;
}
#undef func_0014f5c8
#undef func_0014f600

/* func_001441b8 (from hand/nostrict/text_00140000_h56.c). */
typedef struct {
    u32 flags;
    u8 pad4[0xc];
    f32 pos[4];
    f32 v20[3];
    f32 f2c;
    u8 pad30[0x90 - 0x30];
    u64 d90;
    u8 pad98[0x120 - 0x98];
    f32 v120[4];
    u8 pad130[0x160 - 0x130];
    u64 w160;
    u8 pad168[0x200 - 0x168];
    f32 v200[4];
    u8 pad210[0x3c0 - 0x210];
    f32 v3c0[4];
    u8 pad3d0[0x490 - 0x3d0];
    f32 v490[4];
} Pl;
extern f32 D_002C5970;
void func_0014cc88(Pl *, f32);
s32 func_0014f658(Pl *, s32);
#define func_00121fc4 ((void (*)(f32 *, f32 *)) func_00121fc4)
void func_001441b8(Pl *o) {
    f32 v[4];
    s32 st;

    PlatVu0CopyVector(o->v490, o->pos);
    o->d90 = 0;
    if (!func_001232f0((Ch3 *)o)) {
        PlatVu0CopyVector(o->v3c0, (*(f32 (*)[0x4])&D_002C58B0));
        PlatVu0ScaleVector(v, o->v20, o->f2c * D_002BBDFC);
        if ((s32)(o->w160 >> 2) & 1) {
            PlatVu0AddVector(v, v, o->v200);
        }
        PlatVu0AddVector(v, v, o->v120);
        func_00143d20((Ch3 *)o, v, 0);
    } else {
        func_00143eb8((Mv *)o, v);
        func_00143d20((Ch3 *)o, v, 0);
        st = func_00144060((St *)o);
        if (func_0014f658(o, st) && st == 2) {
            func_0014cc88(o, 0.0f);
            o->flags &= ~4;
            PlatVu0ScaleVector(v, v, D_002C5970);
            func_00121fc4(v, v);
            if (v[3] > 8.0f) {
                v[3] = 8.0f;
            }
            PlatVu0ScaleVector(o->v3c0, v, v[3]);
        }
    }
    PlatVu0CopyVector(o->v120, (*(f32 (*)[0x4])&D_002C58B0));
}
#undef func_00121fc4

