/* Hand-matched functions near 0x152ff8-0x15b098 (worker 58). Built without
 * strict aliasing. */
#include "common.h"
#include "platform/math.h"

typedef struct { f32 x, y, z, w; } V4;
typedef struct { s32 a, b; } P8;
typedef struct {
    u32 w0; s32 w4; s32 w8; s32 wC; s32 x10; f32 f14; s32 x18; f32 f1c; s32 x20; u8 pad24[0xc]; V4 v30; f32 f40; f32 f44; s32 x48; s32 x4c;
} S144;
typedef struct {
    u8 pad0[0x10]; V4 pos; u8 pad20[0x10]; V4 v30; u8 pad40[0x30]; s32 x70; u8 pad74[0xf0]; s32 x164;
} S98;
typedef struct { u8 pad0[5]; u8 b5; u8 pad6[0xe]; struct { u8 pad0[1]; u8 b1; } *x14; } S134;
#define ACT_BODY(T144) \
    u32 w0; u8 pad4[4]; s32 x8; u8 padc[4]; V4 pos; V4 x20; V4 x30; V4 x40; u8 pad50[0x18]; s32 x68; struct { u8 pad[0x3c]; s32 x3c; } *x6c; s32 x70; P8 x74; u8 pad7c[0xc]; s32 x88; s32 x8c; u64 x90; S98 *x98; u8 pad9c[0x24]; V4 xc0; f32 xd0[4][4]; u8 pad110[0x10]; V4 x120; \
    struct { u8 pad[0x44]; f32 x44; s16 x48; u8 pad4a[2]; u16 x4c; } *x130; S134 *x134; u8 pad138[0xc]; T144 *x144; \
    struct { u8 pad[0x160]; V4 v160; } *x148; u8 pad14c[0x1d4]; V4 x320; u8 pad330[0x40]; u64 x370; u8 pad378[0x26]; u8 x39e; u8 pad39f[0x11]; f32 x3b0; u8 pad3b4[0xc]; V4 x3c0; u8 pad3d0[0x14]; f32 x3e4; u8 pad3e8[8]; V4 x3f0; s32 x400; u8 pad404[0x9c]; void *x4a0;
typedef struct { ACT_BODY(S144) } Act;

void func_001315c0(void *, s32, void *, f32);
void func_00267530(void *, void *, void *);
void func_00267518(void *, void *, void *);
void func_00267560(void *, void *, f32);
void func_002675a8(void *, void *);
void func_00137688(void *, f32);
s32 func_001375d8(void *);
s32 func_001443a8(void *);
void func_0014f658(void *, s32);
void func_00152d50(void *, s32, void *);
extern f32 D_002BBDFC;
extern V4 D_002C58A0[];
typedef union { u64 d; s32 w; struct { u32 lo; u32 x:6; u32 kind:4; u32 hi:22; } b; } F8;
typedef struct { u8 pad[8]; F8 f8; } Msg;
void func_00147138(void *, s32);
s32 func_00153300(void *, Msg *);
void func_00153360(void *, Msg *);
void func_001533d0(void *, Msg *);
void func_00145008(void *, s32);
s32 func_001532c8(Msg *);
void func_00152598(void *);
void func_001525f0(void *);
extern P8 D_002E31B0;
s32 func_0012cc38(s32, s32);
void func_0012ec60(s32, s32, void *);
void func_00130340(void *, s32, f32);
void *func_00130578(void *, s32, f32);
void func_0013dfa0(void *);
void func_00152520(void *, void *);
void func_00152688(void *, void *, s32);
void func_00152dc8(void *, s32);
void func_00153c50(void *, s32);
void *func_00121e28(s32, void *);
s32 func_001538d8(void *);
void func_001528f0(void *);
void func_00146678(void *, void *);
extern void (*D_00351970[])(void *);
s32 func_00153668(Act *, S98 *, s32);
void func_00153418(void *, Msg *);
void func_00153500(Act *, Msg *);
void func_00130398(void *, s32, f32);
void func_00157a30(Act *, s32, Act *);
void func_00153e80(void *);
s32 func_00148908(void *);
void func_001358b8(void *, s32);
void func_001586a8(s32);
void func_001373f8(void *, f32);
s32 func_0013c968(s32, s32);
typedef union { u32 w; struct { u32 b0:1; u32 b1:1; u32 p2:14; u32 b16:1; u32 p17:6; u32 b23:1; u32 b24:1; u32 b25:1; u32 p26:6; } b; } F5958;
extern F5958 D_002C5958;
typedef struct { u8 pad[0x7c]; u8 x7c[0x14]; f32 x90; u8 pad94[0x60]; u16 xf4[1]; } S8CDC;
extern S8CDC *D_00308CDC;
s32 D_00F20000(s32, s32);
f32 func_00267390(void *, void *);
s32 func_00122ff8(void *);
extern Act *D_002E26A0[];
s32 func_0014f600(void *);
void *func_00147ed8(s32, s32, s32, void *);
void func_00121fc4(void *, void *);
f32 func_00176850(void);
void func_001247e8(void *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
s32 func_00120748(char *, void *, void *, s32);

/* ---- func_00152ff8 ---- */
void func_00152ff8(Act *a) {
    V4 tmp;
    V4 v;
    V4 buf;
    V4 *p = &a->x120;
    S98 *q;
    s32 k;

    func_001315c0(a->x98, 48, &buf, 0.0f);
    func_00267530(p, &buf, &a->pos);
    if (a->x144->f1c > 0.0f) {
        a->x144->f1c -= D_002BBDFC;
        if (a->x144->f1c > 0.0f) {
            func_00267560(&tmp, &a->x144->v30, a->x144->f1c / 12.0f);
            func_00267518(p, p, &tmp);
            a->w0 |= 0x20;
        }
    }
    func_00137688(a, a->x98->v30.w + a->x144->f14);
    if (a->x98->x70 == 28 && !func_001375d8(a->x98) && !a->x90 && !a->x8 && !func_001443a8(a->x98))
        return;
    func_0014f658(a, 0);
    q = a->x98;
    k = q->x164;
    if (k >= 72 && (k < 74 || k == 76)) {
        func_002675a8(&v, &q->v30);
    } else {
        func_00267530(&v, &D_002C58A0[0], &q->v30);
    }
    func_002675a8(p, &D_002C58A0[1]);
    func_00152d50(a, 1, &v);
}

/* ---- func_00153668 ---- */
s32 func_00153668(Act *a, S98 *b, s32 c) {
    S144 *p = a->x144;
    f32 d;
    s32 k;
    if (!p) return 0;
    switch (c) {
    case -1:
        k = p->w4;
        if (k) {
            if (k >= 0) {
                if (k < 3) func_0012cc38(0, 30);
            }
            break;
        }
        if (a->x8c) break;
        d = b->pos.y - a->pos.y;
        if (!(d > -10.0f && d < 110.0f)) break;
        switch (b->x70) {
        case 0:
            func_0012cc38(3, 28);
            break;
        case 6:
        case 28:
            if (p->w0 & 1) func_0012cc38(3, 29);
            break;
        }
        break;
    case 28:
        func_00152520(a, b);
        func_0013dfa0(b);
        a->x144->w4 = 1;
        a->x144->f1c = 12.0f;
        func_002675a8(&a->x3c0, &D_002C58A0[1]);
        func_0014f658(a, 4);
        break;
    case 29:
        func_00153c50(b, D_002E31B0.a);
        break;
    case 30:
        func_00130340(b, 0x10000bb, 8.0f);
        func_00130578(b, 0x40000000, 0.0f);
        a->x74 = D_002E31B0;
        func_00152dc8(a, 2);
        if (a->x74.a) {
            *(u64 *)&a->x144->w0 |= 2;
            func_0012ec60(a->x74.a, a->x74.b, &a->x144->v30);
        }
        func_00152688(a, b, a->x130->x4c == 0xcc ? 20 : 17);
        break;
    }
    return 0;
}

/* ---- func_001539c0 ---- */
void func_001539c0(Act *a) {
    S144 *p = a->x144;
    S134 *q;
    s32 v;
    if (!p) {
        p = func_00121e28(80, &a->x144);
        p->w0 = 0;
        q = a->x134;
        if (q && q->b5 && (u8)(q->x14->b1 - 2) < 2) *(u64 *)&p->w0 |= 1;
        p->w4 = 0;
        p->w8 = 0;
        p->x10 = 0;
        p->x18 = 0;
        p->f40 = 0;
        p->f44 = 0;
        p->x4c = 0;
        switch (a->x130->x4c) {
        case 202:
            p->wC = 5;
            break;
        case 203:
            p->wC = 5;
            break;
        case 204:
            p->wC = 1;
            break;
        }
        a->x4a0 = func_00153668;
    }
    a->w0 &= ~0x20;
    if (p->f44 > 0.0f && func_001538d8(a)) return;
    if ((a->w0 & 0x400) && a->x70 == 2) {
        p->x20 = 4;
        func_001528f0(a);
    }
    func_00146678(a, a->x130->x4c == 203 ? (void *)func_00153500 : (void *)func_00153418);
    D_00351970[p->w4](a);
}

/* ---- func_00155ef8 ---- */
typedef struct { union { u32 w; struct { u8 b[3]; u8 st; } s; } u; char n1[32]; char n2[32]; void *x44; } E550400;
extern E550400 D_00550400[];
typedef struct { u8 pad[0x1c]; s32 x1c; s32 x20; } R8;
typedef struct { s32 x0; u32 x4; R8 *x8; u8 padc[0x49]; s8 b55; s8 b56; u8 pad57[9]; char *x60; char *x64; } R14;
typedef struct { u8 pad[0x14]; R14 *x14; void (*x18)(s32); } T155ef8;
s32 func_00155d70(s32, const char *);
void func_00155ad8(s32, s32);
s32 func_00155e48(s32, s32, char *);
s32 func_00146b90(void *, s32, void *, void *);
void func_00155c68(), func_00155cf8(), func_00155ee8();
s32 func_00155ef8(T155ef8 *a) {
    R14 *r = a->x14;
    E550400 *e = &D_00550400[r->b55];
    switch (e->u.s.st) {
    case 0:
        e->u.s.st = 1;
        if (!func_00155d70(r->b55, r->x60)) {
            func_00155ad8(r->b55, r->b56);
            func_00120748(r->x60, r->x8, func_00155c68, 0);
            strcpy(e->n1, r->x60);
            e->n2[0] = 0;
            e->x44 = r->x8;
            return 8;
        }
        e->u.s.st++;
    case 2:
        e->u.s.st++;
        if (!func_00155e48(r->b55, r->b56, r->x64)) {
            func_00155ad8(r->b55, r->b56);
            func_00120748(r->x64, e->x44, func_00155cf8, 0);
            strcpy(e->n2, r->x64);
            return 8;
        }
        e->u.s.st++;
    case 4:
        e->u.s.st++;
        if (!(r->x4 & 0x4000) && r->x8->x20 - r->x8->x1c > 0) {
            e->u.w |= 0x10000;
            if (func_00146b90((u8 *)r->x8 + r->x8->x1c, -6, func_00155ee8, e)) return 8;
        }
        e->u.s.st++;
    case 6:
        e->u.w |= 0x40000;
        if (a->x18) a->x18(r->x0);
        return 4;
    }
    return 8;
}

/* ---- func_001564e0 ---- */
s32 func_0014f5c8(void *);
s32 func_001562d0(void *, void *);
s32 func_001563e0(void *, void *);
f32 powf(f32, f32);
void func_001564e0(Act *a, V4 *o) {
    V4 v;
    V4 w;
    f32 *dt = &D_002BBDFC;
    func_00267560(&v, &a->x3f0, a->x3f0.w * *dt);
    a->x3f0.w *= powf(0.7999999523162842f, *dt);
    v.y = 0.0f;
    if (a->x70 == 17) {
        func_00121fc4(&w, &v);
        if (!func_001563e0(a, &w)) func_002675a8(o, &v);
    } else if (func_0014f5c8(a) || func_0014f600(a)) {
        o->x = v.x;
        o->z = v.z;
    } else {
        func_00121fc4(&w, &v);
        if (!func_001562d0(a, &w)) func_002675a8(o, &v);
    }
    if (a->x3f0.w < 1.0f) a->x88 &= ~0x40;
}

/* ---- func_00156768 ---- */
typedef struct { u8 pad[0x60]; } Sub768;
typedef struct { union { u64 d; struct { u8 b0, n; } s; } u; u8 pad8[8]; V4 pos; u8 pad20[0x10]; Sub768 sub[1]; } Node768;
typedef struct { Node768 *p; u8 pad4[0xc]; V4 v; f32 d; s32 idx; } Out768;
extern Node768 *D_00551600; /* src/data/bss_0055.c: u8 *D_00551600 */
s32 func_001566d8(Sub768 *, V4 *);
Node768 *func_00156768(V4 *pos, Out768 *o) {
    Node768 *p = D_00551600;
    s32 idx;
    s32 i;
    Sub768 *s;
    V4 d;
    f32 dist;
    o->p = 0;
    o->d = 0.0f;
    o->idx = 0;
    for (idx = 1; p->u.s.b0; idx++) {
        if (!(p->u.d & 0x10000)) {
            func_00267530(&d, pos, &p->pos);
            dist = func_00267390(&d, &d);
            if (p->u.s.n) {
                for (i = 0; i < p->u.s.n; i++) {
                    if (func_001566d8(&p->sub[i], pos)) {
                        o->p = p;
                        func_002675a8(&o->v, &d);
                        o->d = PlatSqrtf(dist);
                        o->idx = idx;
                        return p;
                    }
                }
            } else if (!o->p || dist < o->d) {
                o->p = p;
                func_002675a8(&o->v, &d);
                o->d = dist;
                o->idx = idx;
            }
        }
        p = (Node768 *)((u8 *)p + p->u.s.n * 0x60 + 0x30);
    }
    o->d = PlatSqrtf(o->d);
    return o->p;
}

/* ---- func_001568e8 (needs func_00156768 defined above) ---- */
typedef struct { u8 x0; u8 pad1[7]; f32 x8; f32 xc; u8 pad10[0x10]; f32 x20[3]; f32 x2c_; } B4Q68;
typedef struct { u8 pad[0x160]; f32 x160[4]; } B4H160;
typedef struct B4A68 {
    u8 pad0[0x50]; f32 x50[4]; u8 pad60[0x98 - 0x60]; struct B4A68 *x98; u8 pad9c[0xc0 - 0x9c]; f32 xc0[4];
    u8 padd0[0x148 - 0xd0]; B4H160 *x148;
} B4A68;
extern u32 D_002C5978;
extern f32 D_002C58B0[];
void func_002673b8(void *, void *);
void func_00267370(void *, void *, void *);
void func_00267e90(void *, void *, f32);
s32 func_0014f5c8(void *);
f32 sinf(f32);
#define D_002C5958 (*(u32 *)&D_002C5958)
void func_001568e8(B4A68 *e, f32 *out) {
    f32 buf[12];
    f32 d[4];
    f32 c[4];
    B4Q68 *q;
    f32 sp;
    f32 tgt;
    f32 cur;
    f32 t;
    s32 r;
    f32 f;
    func_002675a8(out, D_002C58B0);
    if (!D_00551600) return;
    if ((D_002C5958 >> 15) & 1) return;
    if ((D_002C5978 >> 13) & 1) return;
    if (!e->x148) return;
    if (!e->x98) q = (B4Q68 *)func_00156768((V4 *)e->x50, (Out768 *)buf);
    else q = (B4Q68 *)func_00156768((V4 *)e->x98->x50, (Out768 *)buf);
    if (!q) {
        if (e->x148->x160[3] == 0.0f) return;
        func_002675a8(d, e->x148->x160);
        tgt = 0.0f;
        sp = D_002BBDFC * 0.199999988079071044921875f;
    } else {
        sp = q->x2c_ * D_002BBDFC;
        tgt = q->xc;
        switch (q->x0) {
        case 1:
            func_002675a8(d, q->x20);
            break;
        case 2:
            func_00267530(d, q->x20, e->x50);
            func_002673b8(d, d);
            break;
        }
        if (0.0f < q->x8) {
            f = 1.0f - buf[8] / q->x8;
            if (!(0.0f < f)) f = 0.0f;
            tgt *= sinf(f * 3.1415928f * 0.5f);
        }
    }
    func_00267560(d, d, sp);
    func_00267518(d, e->x148->x160, d);
    cur = e->x148->x160[3];
    if (cur < tgt) {
        cur += sp;
        if (tgt < cur) cur = tgt;
    } else if (tgt < cur) {
        cur -= sp;
        if (cur < 0.0f) cur = 0.0f;
    }
    func_002673b8(d, d);
    d[3] = 1.0f;
    func_00267560(e->x148->x160, d, cur);
    func_00267560(out, e->x148->x160, D_002BBDFC);
    if (func_0014f5c8(e)) return;
    if (func_0014f600(e)) {
        out[1] = 0.0f;
        return;
    }
    out[1] = 0.0f;
    t = out[3];
    func_002673b8(out, out);
    func_00267370(c, e->xc0, out);
    func_002673b8(c, c);
    func_00267370(out, c, e->xc0);
    func_002673b8(out, out);
    func_00267e90(out, out, t);
}
#undef D_002C5958

/* ---- func_001584c0 ---- */
extern V4 D_00351A20;
V4 D_005516D0 ALIGNED(16);
void func_002673b8(void *, void *);
void func_00267370(void *, void *, void *);
f32 func_001376e8(void *, void *);
void func_001584c0(Act *a, V4 *o) {
    V4 m;
    V4 t;
    f32 f;
    if (a->x20.w > 0.0f) {
        func_00267560(o, &a->x20, a->x20.w * D_002BBDFC);
        func_00267518(o, o, &a->x3c0);
        func_00121fc4(o, o);
    } else {
        func_00121fc4(o, &a->x3c0);
        o->w -= D_002BBDFC * 0.199999988079071044921875f;
    }
    if (o->w < 0.0f) f = 0.0f;
    else if (o->w > 20.0f) f = 20.0f;
    else f = o->w;
    func_00267560(&a->x3c0, o, f);
    func_002673b8(&m, &a->x148->v160);
    func_00267370(o, &D_00351A20, &m);
    func_002673b8(o, o);
    func_00267560(o, o, a->x3c0.x);
    func_00267518(&t, o, &a->x148->v160);
    func_00137688(a, func_001376e8(a, &t));
    func_00267560(o, o, D_002BBDFC);
    func_002675a8(&D_005516D0, o);
}

/* ---- func_00158780 ---- */
typedef struct { u8 a, b; } P2;
extern P2 D_00351A30[];
typedef struct { u8 pad[0xe]; u16 xe; } R478c8;
R478c8 *func_001478c8(s32);
f32 func_0012ed88(Act *, void *, V4 *, V4 *);
s32 func_00153d78(Act *);
s32 func_0012f040(Act *, s32);
s32 func_00141288(Act *, s32);
s32 func_00158780(s32 k) {
    V4 m;
    V4 d;
    Act *p = D_002E26A0[0];
    R478c8 *r = func_001478c8(D_00351A30[k].b);
    s32 i;
    f32 f = func_0012ed88(p, &D_002E31B0, &m, &d);
    if (r->xe <= f) return 0;
    switch (D_00351A30[k].b) {
    case 75:
        if (p->pos.y - m.y > 160.0f) return 0;
        break;
    case 90:
        if (p->pos.y - m.y < 160.0f) return 0;
        break;
    case 82:
        for (i = 1; i < 3; i++) {
            if (!D_002E26A0[i] || func_00153d78(D_002E26A0[i]) || !func_0012f040(D_002E26A0[i], -1)) return 0;
            func_00267530(&d, &D_002E26A0[i]->pos, &D_002E26A0[0]->pos);
            if (func_00267390(&d, &d) > 250000.0f) return 0;
        }
        break;
    }
    return func_00141288(p, D_00308CDC->xf4[k]) ? 2 : 1;
}

/* ---- func_00158960 ---- */
extern s16 D_002C595A;
extern u32 D_002E31A8;
extern s32 D_00351A48;
extern u8 D_00351A40[];
extern u32 D_005516EC; /* src/data/bss_0055.c: s32 D_005516EC */
void func_0012ccb0(s32);
s32 func_00158780(s32);
void func_00158960(void) {
    s32 i, k, r, best, bk;
    if (D_002C595A & 1) return;
    if ((D_002E31A8 >> 1) & 1) return;
    if (D_002E26A0[0]->x70) return;
    if (D_00351A48 != 5) return;
    if (!func_00122ff8((Act *)D_002E31B0.a)) return;
    if (((s32)(((Act *)D_002E31B0.a)->x370 >> 37) & 3) != 2) return;
    best = 0;
    bk = -1;
    for (i = 0; i < 5; i++) {
        k = D_00351A40[i];
        if (D_005516EC & (1 << k)) {
            r = func_00158780(k);
            if (best < r) {
                best = r;
                bk = k;
            }
        }
    }
    if (bk >= 0 && func_0012cc38(3, D_00351A30[bk].b) && best != 2) func_0012ccb0(3);
}

/* ---- func_00159440 ---- */
s32 func_00137618(void *);
void func_0012bd98(void *, s32, u32, void *);
void func_00159440(Act *a, V4 *o) {
    V4 m;
    V4 t;
    s32 k = 0;
    u32 fl = 0x80000100;
    func_002675a8(&m, &a->x148->v160);
    m.y = 0.0f;
    func_002673b8(&m, &m);
    if (o->w > 0.0f) {
        o->w = 0.3f;
        func_00267370(&t, &m, o);
        if (t.y > 0.9f) {
            fl = 0x40000100;
            k = 203;
        } else if (t.y < -0.9f) {
            fl = 0x20000100;
            k = 206;
        }
    }
    if (func_00137618(a)) func_00130398(a, k | 0x40000000, 8.0f);
    func_0012bd98(a, a->x39e, fl, &a->pos);
    func_002675a8(&a->x20, o);
    func_00267560(&t, &m, a->x148->v160.w);
    func_00267518(&t, &t, &a->x3c0);
    func_001376e8(a, &t);
}

/* ---- func_001595a8 ---- */
f32 func_00121748(void *, void *);
void func_00267e90(void *, void *, f32);
void func_001595a8(Act *a, V4 *o) {
    V4 m;
    f32 f;
    if (a->x20.w > 0.0f) {
        func_00267560(o, &a->x20, a->x20.w * D_002BBDFC);
        func_00267518(o, o, &a->x3c0);
        func_00121fc4(o, o);
    } else {
        func_00121fc4(o, &a->x3c0);
        if (func_00121748(o, &a->x148->v160) > -0.7f)
            o->w -= D_002BBDFC * 0.05f;
        else
            o->w -= D_002BBDFC * 0.3f;
    }
    if (o->w < 0.0f) f = 0.0f;
    else if (o->w > 6.0f) f = 6.0f;
    else f = o->w;
    func_00267560(&a->x3c0, o, f);
    func_00267370(&m, &a->xc0, o);
    func_002673b8(&m, &m);
    func_00267370(o, &m, &a->xc0);
    func_002673b8(o, o);
    func_00267e90(o, o, f * D_002BBDFC);
}

/* ---- func_00159978 ---- */
typedef struct { Act *p; s32 w4; } Arg159178;
extern u32 D_002E3168;
s32 func_00123368(Act *);
Act *func_001230a0(Act *);
void func_0013dfb8(Act *, V4 *);
void func_00159178(Act *, s32, Arg159178 *, V4 *);
void func_00159978(Act *a, V4 *o) {
    Arg159178 s;
    V4 d;
    Act *p = D_002E26A0[0];
    if (!func_00122ff8(p)) return;
    a->x98 = (S98 *)p;
    func_00267530(o, &p->x320, &a->pos);
    o->y = 0.0f;
    func_00121fc4(o, o);
    if (o->w < 200.0f) {
        func_00267530(o, &D_002C58A0[0], o);
        o->w = 1.0f;
    } else if (o->w > 250.0f) {
        o->w = 1.0f;
    } else {
        o->w = 0.0f;
    }
    if (D_002E3168 & 1) {
        func_0013dfb8(a, o);
        return;
    }
    s.p = 0;
    s.w4 = 0;
    while ((s.p = func_001230a0(s.p)) != 0) {
        if (((s32)(s.p->x370 >> 37) & 3) == 1) continue;
        if (!func_00123368(s.p)) continue;
        func_001315c0(s.p, 0x8003, &d, 0.0f);
        func_00267530(&d, &d, &a->pos);
        func_00121fc4(&d, &d);
        if (d.w < 300.0f && func_00267390(&d, &a->x30) > 0.7f) {
            func_00159178(a, 11, &s, o);
            return;
        }
    }
}

/* ---- func_00159cd8 ---- */
typedef struct { s32 w0; Act *obj; s32 pad[2]; V4 a; V4 b; f32 f30; f32 f34; } Tr700;
typedef struct { union { u64 d; s32 w; } h; u8 pad8[0x208]; V4 v210; V4 v220; } Trail;
extern Tr700 D_00551700;
extern Trail D_00551740;
extern s32 D_002E27A8;
extern V4 D_002E2790, D_002E2780;
void sceVu0CopyMatrix(void *, void *);
void func_002674f0(void *, void *, void *, f32);
void func_00159b48(V4 *);
void func_002672f8(void *, void *, void *);
void func_00159c10(f32, V4 *);
void func_00124c68(f32);
s32 func_00159cd8(void) {
    f32 m[4][4];
    V4 u;
    V4 w;
    if (!func_00122ff8(D_00551700.obj)) return 4;
    if (D_002C5958.b.b1 || D_002E27A8 == 9) return 0;
    if (!(D_00551700.w0 & 1)) {
        sceVu0CopyMatrix(m, D_00551700.obj->xd0);
        if (func_0014f600(D_00551700.obj))
            func_002674f0(m[3], &D_00551700.obj->pos, &D_00551700.obj->x320, 0.5f);
        else
            func_002675a8(m[3], &D_00551700.obj->pos);
        func_00159b48((V4 *)m[3]);
        func_002672f8(&u, D_00551700.obj->xd0, &D_00551700.a);
        func_00159c10(D_00551700.f34, (V4 *)m[3]);
        func_002672f8(&w, m, &D_00551700.b);
        if (D_00551740.h.w & 1) {
            func_002675a8(&D_00551740.v220, &u);
            func_002675a8(&D_00551740.v210, &w);
            D_00551740.h.d &= ~1;
        } else {
            func_002674f0(&D_00551740.v220, &u, &D_00551740.v220, D_00551700.f30);
            func_002674f0(&D_00551740.v210, &w, &D_00551740.v210, D_00551700.f30);
        }
    }
    func_002675a8(&D_002E2790, &D_00551740.v220);
    func_002675a8(&D_002E2780, &D_00551740.v210);
    func_00124c68(70.0f);
    return 0;
}

/* ---- func_0015a5b8 ---- */
typedef struct { V4 *v; } E144;
typedef struct { ACT_BODY(E144) } ActY;
extern s32 D_0029B418;
void func_0015a470();
void *func_00147c98(s32, s32, s32);
s32 func_0015a498(ActY *, s32);
void func_0015a5b8(ActY *a) {
    V4 t;
    V4 d;
    Act *p;
    f32 f;
    E144 *e;
    if (!a->x4a0) a->x4a0 = func_0015a470;
    p = D_002E26A0[0];
    if (!func_00122ff8(p)) return;
    func_00267530(&d, &a->pos, &p->pos);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    f = func_00267390(&d, &p->x30);
    e = a->x144;
    if (!e) {
        if (!(f > 0.0f && d.w < 10000.0f)) return;
        e = a->x144 = func_00147c98(D_0029B418, 1, 20000);
    }
    if (f < 0.0f && d.w > 2000.0f) {
        func_001247e8(a);
        return;
    }
    func_002675a8(e->v, &a->pos);
    if (func_0015a498(a, 25)) {
        func_001315c0((void *)a->x8, 0x8003, &t, 0.0f);
        t.x = (t.x + a->pos.x) * 0.5f;
        t.z = (t.z + a->pos.z) * 0.5f;
        func_00147ed8(D_0029B418, 2, 20000, &t);
    }
}

/* ---- func_0015a758 ---- */
void func_0015a758(Act *a, f32 *prm) {
    V4 d;
    Act *p = D_002E26A0[0];
    f32 *dt;
    if (!func_00122ff8(p)) return;
    func_00267530(&d, &a->pos, &p->pos);
    d.y = 0.0f;
    func_00121fc4(&d, &d);
    if (a->x70 == 0) {
        if (d.w < a->x130->x44) {
            func_0014f658(a, 2);
            a->x3c0.x = func_00176850() * prm[2] - prm[2] * 0.5f;
            a->x3c0.y = 0.0f;
            a->x3c0.z = func_00176850() * prm[2] - prm[2] * 0.5f;
            a->x3b0 = 0.0f;
        }
    } else {
        if (func_00267390(&d, &p->x30) < 0.0f && d.w > 2000.0f) {
            func_001247e8(a);
            return;
        }
        dt = &D_002BBDFC;
        a->x20.x = 0.0f;
        a->x20.y = 1.0f;
        a->x20.z = 0.0f;
        a->x3b0 += prm[0] * *dt;
        if (prm[1] <= a->x3b0) a->x3b0 = prm[1];
        a->x20.w = a->x3b0;
        func_00267560(&d, &a->x3c0, *dt);
        func_00267518(&a->x30, &a->x30, &d);
    }
}

/* needs make: uses rodata */

/* ---- func_00153f88 ---- */
void func_00153f88(Act *a) {
    f32 s;
    if (!(a->x88 & 0x30)) return;
    if (a->x6c->x3c > 0) {
        func_00157a30(a, 24, 0);
        func_00153e80(a);
    } else {
    if (!(a->w0 & 4)) {
        switch (a->x70) {
        case 0:
        case 24:
        case 25:
            func_00130398(a, 0x1000043, 16.0f);
            break;
        case 17:
            func_00130398(a, 0x100006c, 16.0f);
            break;
        case 8:
            func_00130398(a, 0x100008d, 16.0f);
            break;
        case 2:
            break;
        default:
            return;
        }
    }
    if (a->x88 & 0x10) {
        a->x3e4 = D_00308CDC->x7c[a->x130->x4c] * 60.0f;
        a->x88 = (a->x88 & ~0x10) | 0x20;
        if (!a->x400) {
            a->x400 = func_00148908(a);
            func_001358b8(a, 10);
        }
        func_001586a8(14);
    }
    func_001373f8(a, 30.0f);
    s = D_002BBDFC;
    if (!(D_002C5958.b.b0)) s *= D_00308CDC->x90;
    if (func_0013c968(9, a->x130->x4c) > 0) s += s;
    a->x3e4 -= s;
    if (a->x3e4 <= 0.0f) {
        if ((D_002C5958.b.b0) || ((s32)(a->x370 >> 35) & 1)) func_00157a30(a, 25, 0);
        func_00153e80(a);
    }
    }
}

/* ---- func_00154e38 ---- */
typedef void (*Fn6)(void *, s32, s32);
void func_001542f8(), func_00154768(), func_00154af8(), func_00154be0(), func_001543f8(), func_00154880(), func_00154c60();
void func_001544a0(), func_001549b8(), func_00154d60(), func_00154548(), func_001545f0(), func_001546b8();
typedef struct { Fn6 f[4]; } Tbl6;
s32 func_00154e38(Act *a, s32 k, s32 b, s32 c) {
    Tbl6 t0 = { { func_001542f8, func_00154768, func_00154af8, func_00154be0 } };
    Tbl6 t1 = { { func_001543f8, func_00154880, func_00154c60, func_00154c60 } };
    Tbl6 t2 = { { func_001544a0, func_001549b8, func_00154d60, func_00154d60 } };
    Tbl6 t3 = { { func_00154548, func_00154548, 0, 0 } };
    Tbl6 t4 = { { func_001545f0, func_001545f0, 0, 0 } };
    Tbl6 t5 = { { func_001546b8, func_001546b8, 0, 0 } };
    Tbl6 *t;
    switch (a->x70) {
    case 0: case 1: case 12: case 28: case 32: case 38:
        func_0014f658(a, 0);
        t = &t0;
        break;
    case 24: case 25:
        func_0014f658(a, 24);
        t = &t0;
        break;
    case 8:
        t = &t2;
        break;
    case 17:
        t = &t3;
        break;
    case 30: case 31:
        t = &t4;
        break;
    case 29:
        t = &t5;
        break;
    case 39:
        D_00F20000(10, 0);
        t = 0;
        break;
    default:
        t = &t1;
        break;
    }
    if (t) switch (k) {
    case 0: case 1: case 2:
        break;
    case 3:
        t->f[0](a, b, c);
        return 1;
    case 4: case 5:
        t->f[1](a, b, c);
        return 1;
    case 6:
        t->f[2](a, b, c);
        return 0;
    case 7:
        t->f[3](a, b, c);
        break;
    }
    return 0;
}

/* ---- func_001571a8 ---- */
#include "data/types/nostrict_text_00150000_h58.h"
extern E1608 D_00551608[];
extern s8 D_005516C0[];
extern s32 D_002BC128;
extern char D_00351990[];
typedef struct { s32 x0; s32 x4; void *x8; u8 padc[4]; void (*x10)(void); } Tk;
void func_00112298(s32, s32, s32, char *);
char *func_0013dbb0(s32);
s32 strcmp(const char *, const char *);
void *func_001559f0(s32, s32);
void *func_001208e0(void *);
void func_001570d0();
s32 func_001571a8(s32 i, void (*cb)(void)) {
    s32 k, n, j, j0;
    E1608 *e;
    Tk *t;
    void *x;
    if (!D_002BC128) {
        D_005516C0[i] = -1;
        goto done;
    }
    if (i < 3) {
        func_00112298(D_002BC128, 0, 0, D_00351990 + 6);
        D_00351990[8] = '_';
        strcpy(D_00351990 + 9, func_0013dbb0(i));
    } else {
        strcpy(D_00351990 + 6, func_0013dbb0(i));
    }
    strcat(D_00351990, ".vsb");
    k = -1;
    if (i == 0) { j0 = 0; n = 1; } else { j0 = 1; n = 3; }
    for (e = &D_00551608[j0], j = j0; j < n; j++, e++) {
        if (e->b0 == i && !strcmp(e->name, D_00351990)) {
            e->b1 |= 1;
        done:
            if (cb) cb();
            return 0;
        }
        if (k < 0 && !(e->b1 & 1)) k = j;
    }
    e = &D_00551608[k];
    e->b0 = i;
    e->b1 |= 1;
    strcpy(e->name, D_00351990);
    D_005516C0[i] = k;
    x = func_001559f0(54, 2);
    func_00120748(D_00351990, x, 0, 0);
    t = func_00121e28(20, (u8 *)func_001208e0(func_001570d0) + 72);
    t->x10 = cb;
    t->x4 = k;
    t->x8 = x;
    t->x0 = 0;
    return 1;
}

/* ---- func_00157c60 ---- */
typedef struct { s8 b0, b1, b2, b3; void *w4; f32 w8; s32 wC; s32 w10; } E551670;
extern E551670 D_00551670[];
void func_0011ddd0(void);
void func_00157818(void *, s32);
s32 func_001ecfd8(void);
void func_001577a0(E551670 *);
void func_001576a8(E551670 *);
s32 func_001ecd08(s32, s32, s32);
s32 func_00157c60(void) {
    s32 i;
    s32 busy = 0;
    E551670 *e;
    func_0011ddd0();
    for (i = 0, e = D_00551670; i < 4; i++, e++) {
        switch (e->b0) {
        case 0:
            break;
        case 1:
            e->w8 -= D_002BBDFC;
            if (e->w8 < 0.0f) func_00157818(e->w4, e->b3);
            break;
        case 2:
            if (e->b1 == 1 && busy) break;
            if (func_001ecfd8()) break;
            func_001577a0(e);
            e->b0 = 3;
            if (e->b1 == 1) busy = 1;
            break;
        case 3:
            e->b0 = 4;
            break;
        case 4:
            func_001576a8(e);
            switch (e->b1) {
            case 0:
                if (!func_001ecd08(e->b2, e->b3, 0)) e->b0 = 0;
                break;
            case 1:
                if (!func_001ecd08(-1, -1, e->wC)) e->b0 = 0;
                break;
            }
            break;
        }
    }
    return 0;
}

/* ---- func_00158ec8 ---- */
typedef struct { u8 pad[0x1c]; s32 x1c; } R16E4;
extern R16E4 *D_005516E4; /* src/data/bss_0055.c: s32 *D_005516E4 */
extern s32 D_00351A48;
s32 func_00158c78(void);
void *func_00155a50(void);
s32 func_00158d30(void);
s32 func_00146878(void);
s32 func_00157090(void);
void func_00158df8(), func_00158d70();
s32 func_00146b90(void *, s32, void *, void *);

s32 func_00158ec8(void) {
    D_002C5958.b.b25 = 0;
    if (D_002C5958.b.b16) {
        if (D_002C5958.b.b23) {
            D_002C5958.b.b16 = 0;
            D_002C5958.b.b23 = 0;
        } else {
            if (D_00F20000(5, 0)) return 0;
            D_002C5958.b.b23 = 1;
        }
    } else
    switch (D_00351A48) {
    case 0:
        D_00351A48 = 1;
        break;
    case 1:
        if (func_00158c78()) {
            func_00120748("xl_limit.dat", func_00155a50(), func_00158df8, 0);
            D_00351A48 = 2;
            D_002C5958.b.b25 = 1;
        }
        break;
    case 2:
    case 4:
        D_002C5958.b.b25 = 1;
        break;
    case 3:
        if (!func_00158d30()) {
            D_00351A48 = 0;
        } else if (func_00146878() && !func_00157090()) {
            D_00351A48 = 4;
            if (!func_00146b90((u8 *)D_005516E4 + D_005516E4->x1c, -7, func_00158d70, 0)) D_00351A48 = 0;
        }
        D_002C5958.b.b25 = 1;
        break;
    case 5:
        if (func_00158d30()) return 0;
        D_00351A48 = 0;
        break;
    case 6:
        return 4;
    default:
        return 0;
    }
    return 0;
}

/* ---- func_0015ae48 ---- */
typedef struct { u8 b0, b1, b2, b3, b4, b5, b6, b7; u8 pad8[0x10]; u8 b18; u8 pad19[8]; u8 b21; u8 pad22[0x4e]; } Sub116;
typedef struct { s32 x0; Sub116 s; } Ent116;
typedef struct { u8 pad[0x40]; s32 x40; u8 pad44[4]; s32 x48; s32 x4c; s32 x50; u8 pad54[0x8c]; s32 xe0; } St6c;
typedef struct { u8 pad[0x6c]; St6c *x6c; } P6c;
extern Ent116 *D_00304BE8;
P6c *func_0013daf8(s32);
void func_00141468(P6c *, s32);
void func_00141540(P6c *, s32);
void func_0013c8c8(s32, s32);
void func_0015ae48(s32 i, u32 k) {
    Sub116 *s = &D_00304BE8[i].s;
    P6c *p = func_0013daf8(i);
    s32 v;
    switch (k) {
    case 0:
        break;
    case 1:
        s->b2 += 3;
        if (p) {
            p->x6c->x40 += 3;
            func_00141468(p, 3);
            return;
        }
        s->b1 += 3;
        break;
    case 2:
        s->b4 += 1;
        if (p) {
            p->x6c->x48 += 1;
            func_00141540(p, 1);
            return;
        }
        s->b3 += 1;
        break;
    case 3:
        s->b5 = s->b5 + 2 > 100 ? 100 : s->b5 + 2;
        if (p) {
            v = p->x6c->xe0 + 2;
            p->x6c->xe0 = v < 101 ? v : 100;
        }
        break;
    case 4:
        s->b6 = s->b6 + 2 > 100 ? 100 : s->b6 + 2;
        if (p) {
            v = p->x6c->x4c + 2;
            p->x6c->x4c = v < 101 ? v : 100;
        }
        break;
    case 5:
        s->b7 = s->b7 + 2 > 100 ? 100 : s->b7 + 2;
        if (p) {
            v = p->x6c->x50 + 2;
            p->x6c->x50 = v < 101 ? v : 100;
        }
        break;
    case 6:
        s->b21++;
        break;
    case 7:
        s->b18++;
        break;
    default:
        func_0013c8c8(k & ~0x80, i);
        break;
    }
}


void func_00157910(void *, s32, s32);
void func_00157a00(void *a, s32 v, s32 b) {
    func_00157910(a, v, b);
    func_001358b8(a, 35);
}
typedef struct { s8 id; s8 w; } Ent12;
typedef struct { u8 b0; Ent12 e[5]; } Rec12;
extern s32 D_003519B0[];
extern s32 D_002BC128, D_002BC130, D_002BC134;
Rec12 *func_001477c8(s32);
void func_00157a00(void *, s32, s32);
void func_00157a30(Act *a, s32 k, Act *b) {
    s32 cand[5];
    s32 n = 0;
    Rec12 *t = func_001477c8(D_003519B0[a->x130->x4c]) + k;
    s32 r = func_00176850() * 100.0f;
    s32 i;
    s32 v;
    if (D_002BC128 == 3 && D_002BC130 == 2 && D_002BC134 == D_002BC130) b = 0;
    for (i = 0; i < 5; i++) {
        switch (t->e[i].id) {
        case -2:
            v = -1;
            break;
        case -1:
            continue;
        case -3:
            if (!func_00122ff8(b)) continue;
            if (b->x130->x4c >= 10) continue;
            if (b->x130->x4c == a->x130->x4c) continue;
            if (r < t->e[i].w) {
                func_00157a00(a, b->x130->x4c, t->b0);
                return;
            }
            continue;
        default:
            v = t->e[i].id;
            break;
        }
        if (t->e[i].w > 0) {
            r -= t->e[i].w;
            if (r < 0) {
                if (v >= 0) func_00157a00(a, v, t->b0);
                return;
            }
        } else {
            cand[n] = v;
            n++;
        }
    }
    if (n > 0) {
        v = cand[(s32)(func_00176850() * n)];
        if (v >= 0) func_00157a00(a, v, t->b0);
    }
}

typedef struct { u8 b[32]; } E551970;
E551970 D_00551970[0x20] ALIGNED(16);
extern s32 D_00351AC0;

char *func_0015b060(void) {
    E551970 *r = &D_00551970[D_00351AC0++];
    if (D_00351AC0 >= 32) D_00351AC0 = 0;
    return (char *)r;
}

/* needs make: uses rodata */
typedef struct { s32 x0; char *x4; } R478a0;
extern s32 D_00351B20[][2];
extern s32 D_002BBDE4;
char *func_00147808(s32);
R478a0 *func_001478a0(s32);
void func_00244670(s32, char *, char *);
void func_0015b098(s32 a, s32 *ids) {
    char *buf[2];
    s32 i;
    R478a0 *r;
    for (i = 0; i < 2; i++) {
        buf[i] = 0;
        if (ids[i] == 0) continue;
        if (ids[i] >= 0) {
            if (ids[i] < 8) {
                char *b = func_0015b060();
                buf[i] = b;
                strcpy(b, func_00147808(D_00351B20[ids[i]][i]));
                continue;
            }
        }
        r = func_001478a0(ids[i] & ~0x80);
        buf[i] = func_0015b060();
        switch (D_002BBDE4) {
        case 0:
        case 4:
        case 7:
            strcpy(buf[i], r->x4);
            strcat(buf[i], func_00147808(344));
            break;
        case 1:
        case 2:
        case 5:
        case 6:
            strcpy(buf[i], func_00147808(344));
            strcat(buf[i], r->x4);
            strcat(buf[i], "h");
            break;
        case 3:
            strcpy(buf[i], func_00147808(344));
            strcat(buf[i], r->x4);
            break;
        }
    }
    if (buf[0]) func_00244670(a, buf[0], buf[1]);
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
void func_00152880();
void func_00152928();
void func_00152e10();
void func_00152f10();
void func_001531c0();
void func_00153210();
void (*D_00351970[0x8])(void *) ALIGNED(16) = {
    (void *)func_00153210, (void *)func_00152f10, (void *)func_00152ff8, (void *)func_00152e10,
    (void *)func_00152928, (void *)func_001531c0, (void *)func_00152880, 0,
};

/* At the end, not with the includes: declaring D_005516C0 earlier changes how func_0015b060 forms
   the D_00551970 address (gcc 2.96 rtx ordering), so the header comes after the code here. */
#include "data/bss_0055.h"
