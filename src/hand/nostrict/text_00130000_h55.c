/* Hand-matched functions near 0x13b000-0x143000 (worker 55), built without strict aliasing. */
#include "common.h"
#include "data/bss_0052.h"

typedef struct { u8 pad[8]; f32 x8; f32 xc; } W55Dim;
typedef struct { u8 pad[0x10]; W55Dim *x10; } W55Mdl;
typedef struct { u8 pad[4]; s32 x4; u8 pad8[0x4c - 0x8]; u16 x4c; u8 pad4e[0x54 - 0x4e]; s8 x54; } W55Inf;
typedef struct { u8 pad[0xcc]; f32 xcc; } W55Mv;
typedef struct { f32 *x0; } W55Fx;
typedef struct Actor {
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
typedef struct { u32 type:8; u32 id:16; u32 b24:1; u32 f25:1; u32 hi:6; void *x4; s32 x8; } W55Ev;
typedef struct { u8 x0, x1; s8 x2; } W55EvInf;
#include "data/types/nostrict_text_00130000_h55.h"

extern f32 D_002BBDFC;
extern u32 D_002C5958;
#include "data/pieces/D_002E26A0.h"
extern W55Ev D_002E3190;
extern s32 D_002E3194;
extern f32 D_00304C40;
W55Ob *D_0052AE3C ALIGNED(4);
f32 D_0052AE40[4] ALIGNED(16);
f32 D_0052AE68 ALIGNED(8);
extern s32 D_0029B410;

void D_00F20000(s32 a, void *b);
void func_00105a30(s32 a, s32 id, f32 *v);
u32 func_00105bc0(s32 a, s32 id);
s32 func_00117bb0(s32 id, f32 *a, f32 *b, f32 *c);
f32 func_00121550(f32 *o, f32 *a, f32 *d, f32 *p, f32 *v);
void func_00121fc4(f32 *d, f32 *s);
W55Ob *func_001230a0(W55Ob *p);
void func_0012c560(W55Ob *o, void *a, s32 id);
void func_0012ec60(void *a, s32 b, f32 *v);
void func_00130340(void *o, s32 a, f32 f);
void *func_00130578(void *, s32, f32);
s32 func_00133000(W55Ob *o, s32 id);
void func_001333e0(W55Ob *o, s32 id, void *p);
void func_001337e0(s32 a, void *b, s32 c);
void func_00137330(void *a, W55Ob *o, s32 t);
s32 func_001375f0(W55Ob *o);
void func_0013aaa0(void);
void func_0013e638(W55Ob *o, W55Ev *e, void *q);
void func_0013e978(W55Ob *o, W55Ev *e, void *q);
void func_0013ecf8(W55Ob *o, void *a, void *q);
W55Fx *func_00147c98(s32 a, s32 b, s32 c);
void func_00147d50(W55Fx *f, f32 *v);
W55EvInf *func_001478c8(s32 t);
void func_00150930(W55Ob *o, s32 a, void *q);
void func_00157a30(W55Ob *o, s32 k, void *a);
void func_00158b88(W55Ob *o, W55Ev *e, s32 t);
s32 func_00176578(s32 a, s32 b, s32 c, s64 d);
#include "vm/script_vm.h"
f32 func_00267390(f32 *a, f32 *b);
void func_002673b8(f32 *d, f32 *s);
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_00267560(f32 *d, f32 *s, f32 k);
void func_002675a8(f32 *d, f32 *s);
f32 fabsf(f32);

void func_0013dd40(void) {
    f32 v[4];
    W55Ob *pl, *p;
    s32 i, near;
    f32 lim;
    u32 *fl = &D_002C5958;
    if (*fl & 0x12010) { *fl |= 1; return; }
    if ((*fl >> 12) & 1) { *fl &= ~1; return; }
    lim = 1440000.0f;
    near = 0;
    for (i = 0; i < 3; i++) {
        pl = D_002E26A0[i];
        if (!pl) continue;
        for (p = 0; (p = func_001230a0(p));) {
            if (p->x370.b.kind != 2) continue;
            func_00267530(v, pl->pos, p->pos);
            v[1] = 0.0f;
            if (func_00267390(v, v) < lim) { near = 1; break; }
        }
    }
    if (D_00304C40 > 0.0f) D_00304C40 -= D_002BBDFC;
    if ((D_002C5958 & 1) != near) {
        if (D_00304C40 > 0.0f) {
            D_00304C40 = 0.0f;
            D_002C5958 = (D_002C5958 & ~1) | near;
        } else if ((D_0052AE68 -= D_002BBDFC) <= 0.0f) {
            D_002C5958 = (D_002C5958 & ~1) | near;
        }
        if ((D_002C5958 & 1) != near) return;
    }
    if (D_002C5958 & 1) D_0052AE68 = 120.0f;
    else D_0052AE68 = 45.0f;
}

void func_0013e000(W55Ob *o) {
    f32 v[4], w[4], pos[4], out[4];
    u32 id = o->x316;
    W55Fx *fx;
    u32 k;
    s32 h;
    s32 *gp;
    if (id == 0xffff) return;
    if (o->x0 & 0x1000080) return;
    func_00105a30(-1, id, v);
    v[1] = 0.0f;
    func_002673b8(v, v);
    func_002675a8(pos, o->pos);
    pos[1] -= o->x134->x10->x8 * o->x44;
    pos[3] = 1.0f;
    func_00267560(w, v, o->x134->x10->xc * o->x40 * -2.0f);
    w[3] = 1.0f;
    if (!func_00117bb0(id, pos, w, out)) return;
    fx = o->x488;
    if (!fx) {
        if (!D_0029B410) goto skip;
        k = func_00105bc0(-1, id);
        switch (k) {
        case 1: k = 2; break;
        case 2: k = 4; break;
        case 3: k = 8; break;
        default: k = 0; break;
        }
        gp = &D_0029B410;
        h = func_00176578(*gp, k, 0, (1 << o->x130->x4c) | 0x400);
        if (h >= 0) {
            fx = func_00147c98(*gp, h, 20000);
            o->x48c = id;
            o->x488 = fx;
        }
    } else if (o->x48c != id) fx = 0;
skip:
    if (fx) {
        func_002675a8(fx->x0, out);
        func_00147d50(fx, v);
    }
}

s32 func_0013ff00(W55Ob *o, f32 *seg, f32 *v, f32 *r) {
    f32 d[4], w[4], tmp[4];
    f32 t;
    if (fabsf(seg[1] - seg[5]) > 5.0f) seg += 4;
    func_00267530(d, seg + 4, seg);
    func_00121fc4(d, d);
    t = func_00121550(tmp, seg, d, o->pos, v);
    if (t < 0.0f) {
        if (t < -20.0f) return 0;
        t = 0.0f;
    } else if (d[3] < t) {
        if (d[3] + 20.0f < t) return 0;
        t = d[3];
    }
    func_00267560(w, v, o->x2c0 - 1.0f);
    r[0] = seg[0] + d[0] * t + w[0];
    r[1] = o->pos[1];
    r[2] = seg[2] + d[2] * t + w[2];
    r[3] = 1.0f;
    return 1;
}

/* needs make: uses rodata */
void func_0013eab0(W55Ob *o, W55Ev *e, f32 *q) {
    f32 v[4];
    switch (e->type) {
    case 2:
        if (func_00133000(o, e->id)) {
            if (e->x4) {
                func_0012ec60(e->x4, e->x8, v);
                func_00267530(q, v, o->pos);
                o->x6c->xcc = 0.19634955f;
            }
            if (!e->id) {
                func_00130340(o, 0x1000083, 0.0f);
                func_00130578(o, 138, 0.0f);
            } else {
                func_00130340(o, (e->id + 131) | 0x1000000, 0.0f);
            }
            func_00130578(o, 0x40000075, 8.0f);
            func_001333e0(o, e->id, &e->x4);
        }
        break;
    case 3:
        if (!e->x4 || e->x4 == o) {
            func_00130340(o, 0x100008b, 8.0f);
        } else {
            func_0012ec60(e->x4, e->x8, v);
            func_00267530(q, v, o->pos);
            func_00130340(o, 0x100008c, 8.0f);
        }
        func_00130578(o, 0x40000075, 8.0f);
        func_0012c560(o, e->x4, e->id);
        func_00267560(o->x3c0, o->x3c0, 0.7f);
        break;
    case 4:
        func_001337e0(0, e->x4, 0);
        break;
    case 5:
        func_001337e0(4, e->x4, 0);
        break;
    case 0: case 6: case 28: case 29: case 30:
        break;
    default:
        return;
    }
    func_00121fc4(q, q);
    q[3] = 0.0f;
}

void func_0013ee40(W55Ob *o, W55Ev *e, void *q) {
    W55EvInf *inf = func_001478c8(e->type);
    if (e->f25) {
        if (inf->x2 >= 0) func_00157a30(o, inf->x2, e->x4);
        else if (e->type == 2) func_00157a30(o, e->id + 7, e->x4);
    }
    switch (e->type) {
    case 29: case 30: case 70: case 81: case 84:
        func_00137330(o->x98, o, e->type);
        return;
    case 68:
        if (o->x70 == 0 || o->x70 == 26) func_00150930(o, D_002E3194, q);
        return;
    case 71:
        if (func_001375f0(o) && D_002E3190.f25) {
            func_0013ecf8(o, &D_002E3190.x4, q);
            D_00F20000(3, 0);
        }
        func_00137330(o->x98, o, D_002E3190.type);
        return;
    case 75: case 77: case 78: case 82: case 87: case 88: case 89: case 90: case 91:
    case 94: case 95: case 96:
        func_00158b88(o, &D_002E3190, e->type);
        return;
    case 79:
        func_0013aaa0();
        return;
    case 92: case 93:
        return;
    case 100:
        func_00137330(e->x4, o, e->type);
        return;
    }
    switch (o->x70) {
    case 0: case 6: case 24:
        func_0013e638(o, e, q);
        return;
    case 2:
        func_0013e978(o, e, q);
        return;
    case 8:
        func_0013eab0(o, e, q);
        break;
    }
}

/* uses rodata. func_001401d8 only matches with func_0013fe28 defined above it. */
f32 func_0013fe10();

s32 func_0013fe28(W55Ob *o) {
    f32 t = func_0013fe10(o);
    s32 r = 0;
    if (t < 0.015f || t > 0.985f) r = 1;
    return r;
}
#include "data/bss_0052_typed.h"
#include "data/data_0029.h"
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/data_002E.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
