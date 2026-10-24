/* The ppp effect system's interface, without strict aliasing (docs/modules.md
 * "Session 51"): func_00175be0 starts an effect in one of the three banks,
 * func_00176658 spawns an object of D_00364130 from an effect pack item.
 * pppapi.c has the rest.  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "data/pieces/D_0035BD40.h"
#include "data/pieces/D_002E27C8.h"
#include "data/pieces/D_0035C440.h"
#include "data/pieces/D_0035C460.h"
#include "data/pieces/D_002C58B0.h"
#include "data/types/nostrict_text_00170000_h61.h"

/* func_00175be0 (from hand/nostrict/text_00160000_s6_09.c). */
typedef kh1_s128 u128;
typedef struct { s32 x0; void *x4; s32 x8; void *xc; u8 pad10[4]; s32 x14; u8 pad18[4]; void *x1c; u8 pad20[0xC]; u8 *x2c; u8 pad30[0xC]; } Ent5B;
typedef struct { s32 x0; void *x4; void *x8; Ent5B ent[64]; s32 idx[64]; u8 pad[4]; f32 vec[64][4]; } W5B;
typedef struct { s32 id; s32 x4; s32 key; u8 padc[4]; f32 v10[4]; u128 q20; f32 v30[4]; f32 v40[4]; } It5B;
typedef struct { u8 pad0[4]; s32 n; u8 pad8[8]; It5B items[1]; } Hd5B;
s32 func_00176488(s32, Ent5B *, s32, s32);
CONTEXT_ONLY s32 func_00175ba0(W5B *w) {
    s32 i;
    for (i = 0; i < 64; i++) {
        if (!(w->ent[i].x14 & 3)) return i;
    }
    return -1;
}
s32 func_00175be0(W5B *w, s32 a1, void *hv, s32 id, s32 a4, s32 key, s32 b) { Hd5B *h = hv;
    It5B *it;
    s32 i, k;
    Ent5B *e;
    w->x0 = a1;
    w->x4 = h;
    w->x8 = it = h->items;
    for (i = 0; i < h->n; i++, it++) {
        if (it->id != id && id != -1) continue;
        if (it->key != key && key != -1) continue;
        k = func_00175ba0(w);
        e = &w->ent[k];
        if (func_00176488(a1, e, it->x4, a4)) {
            PlatVu0CopyVectorXYZ(e->x0, it->v10);
            PlatVu0CopyVectorXYZ(e->x8, it->v30);
            PlatVu0CopyVector(e->xc, it->v40);
            PlatVu0CopyVector(w->vec[k], it->v40);
            w->idx[k] = i;
            *(u128 *)e->x4 = it->q20;
            e->x1c = it;
            e->x2c[0xB5] = b;
        }
    }
    return 1;
}

/* func_00176658 (from hand/nostrict/text_00170000_h61.c). */
typedef struct Ppp {
u8 pad0[0x88];
s32 x88;
u8 pad8c[0x93 - 0x8c];
u8 x93;
void *x94;
s32 x98;
u8 pad9c[0xa8 - 0x9c];
s32 xa8;
} Ppp;
typedef struct Obj3C {
void *x0, *x4, *x8, *xc, *x10;
s32 x14;
void *x18, *x1c, *x20, *x24, *x28, *x2c;
s32 x30;
void *x34;
} Obj3C;
extern s32 D_0035C6F8;
extern s32 D_0035C6FC;
void func_00181fe0(Ppp **);
s32 func_00181410(s32);
void func_001803f0(s32, s32, s32 *, Ppp *);
s32 func_00181318(void);
s32 func_00181368(s32);
void func_00182c10(Ppp *, s32, s32);
void func_00182840(Ppp *);
s32 func_00176658(s32 a0, Obj3C *o, s32 size, s32 a3) {
    Ppp *p;
    s32 q;
    s32 ok = 1;
    q = 0;
    p = 0;
    func_00181fe0(&p);
    if (!p) {
        if (!func_00181410(a3)) {
            ok = 0;
            goto end;
        }
        func_00181fe0(&p);
    }
    p->x88 = a0;
    p->x93 = size;
    p->x94 = o;
    p->xa8 = D_0035C6F8++;
    o->x14 = 17;
    o->x0 = p;
    o->x4 = (u8 *)p + 16;
    o->x8 = (u8 *)p + 32;
    o->xc = (u8 *)p + 48;
    o->x10 = (u8 *)p + 133;
    o->x18 = (u8 *)p + 160;
    o->x20 = (u8 *)p + 177;
    o->x24 = (u8 *)p + 64;
    o->x28 = (u8 *)p + 96;
    o->x2c = p;
    o->x30 = D_0035C6FC++;
    o->x34 = (u8 *)p + 183;
    func_001803f0(a0, size, &q, p);
    p->x98 = a3;
    if (!q) {
        ok = 0;
    } else {
        if (func_00181318() > 0x7ffff) {
            do {
                if (!func_00181368(a3)) {
                    ok = 0;
                    goto end;
                }
            } while (func_00181318() > 0x7ffff);
        }
        func_00182c10(p, q, 1);
    }
end:
    if (!ok && p) func_00182840(p);
    return ok;
}

