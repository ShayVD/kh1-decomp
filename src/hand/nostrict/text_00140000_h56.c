#include "common.h"
void func_002675a8(f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267530(f32 *, f32 *, f32 *);
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
void func_00142fe0(Ch2 *, Ch2 *);


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
s8 func_00142388(f32 *, s32 *);
s8 func_00142618(Ch3 *);
void func_00143a70(Ch3 *, f32 *, void *);

void func_00143d20(Ch3 *o, f32 *v, void *arg) {
    f32 a[4];
    f32 b[4];
    f32 c[8];
    s32 i;

    func_002675a8(a, v);
    func_002675a8(b, o->pos);
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
        func_00267518(o->pos, o->pos, a);
        o->f3d4 = 0.0f;
        if ((u32)(o->kind - 2) < 2) {
            func_002675a8(b, o->v50);
            b[1] -= 100.0f;
            o->b39e = func_00142388(b, o->w350);
        } else if (o->o3a0 && o->o3a0->kind == 3) {
            for (i = 0; i < 4; i++) {
                o->w350[i] = o->o3a0->w350[i];
            }
        }
    }
    func_00267530(a, o->pos, b);
}

typedef void (*MvFn)(void *, f32 *);
typedef struct { u32 f0; u8 pad4[0xc]; MvFn f10; void *f14; u8 pad18[8]; } MvTab;
extern MvTab D_00350D88[];
extern f32 D_002C58A0[];
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
void func_00267e90(f32 *, f32 *, f32);
void func_0014f798(Mv *, f32 *);
void func_001568e8(Mv *, f32 *);
void func_001564e0(Mv *, f32 *);

/* needs make: uses rodata */
void func_00143eb8(Mv *o, f32 *v) {
    f32 t[4];
    MvFn fn;

    switch (o->st70) {
    case 9:
    case 10:
    case 22:
    case 23:
        func_00267e90(v, o->v20, o->f2c * D_002BBDFC);
        break;
    case 18:
        func_00267e90(v, o->v20, D_002BBDFC);
        break;
    case 20:
        func_002675a8(v, o->v20);
        break;
    case 19:
        func_002675a8(v, D_002C58A0);
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
        func_00267518(v, v, t);
    }
    if (o->w88 & 0x40) {
        func_001564e0(o, v);
    }
    if ((s32)(o->w160 >> 2) & 1) {
        func_00267518(v, v, o->v200);
    }
    func_00267518(v, v, o->v120);
}

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
s32 func_0014f5c8(St *);
s32 func_0014f600(St *);
void func_0012c698(St *);
s32 func_001443a8(St *);

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
extern f32 D_002C58B0[];
void func_00267560(f32 *, f32 *, f32);
void func_0014cc88(Pl *, f32);
s32 func_0014f658(Pl *, s32);
void func_00121fc4(f32 *, f32 *);

void func_001441b8(Pl *o) {
    f32 v[4];
    s32 st;

    func_002675a8(o->v490, o->pos);
    o->d90 = 0;
    if (!func_001232f0((Ch3 *)o)) {
        func_002675a8(o->v3c0, D_002C58B0);
        func_00267560(v, o->v20, o->f2c * D_002BBDFC);
        if ((s32)(o->w160 >> 2) & 1) {
            func_00267518(v, v, o->v200);
        }
        func_00267518(v, v, o->v120);
        func_00143d20((Ch3 *)o, v, 0);
    } else {
        func_00143eb8((Mv *)o, v);
        func_00143d20((Ch3 *)o, v, 0);
        st = func_00144060((St *)o);
        if (func_0014f658(o, st) && st == 2) {
            func_0014cc88(o, 0.0f);
            o->flags &= ~4;
            func_00267560(v, v, D_002C5970);
            func_00121fc4(v, v);
            if (v[3] > 8.0f) {
                v[3] = 8.0f;
            }
            func_00267560(o->v3c0, v, v[3]);
        }
    }
    func_002675a8(o->v120, D_002C58B0);
}

typedef struct { u8 pad[0xa0]; f32 va0[3]; f32 fac; f32 fb0; f32 fb4; f32 fb8; } Cam148;
typedef struct {
    u32 flags;
    u8 pad4[0x88 - 4];
    u32 w88;
    u8 pad8c[0x148 - 0x8c];
    Cam148 *c148;
    u8 pad14c[0x2d4 - 0x14c];
    f32 f2d4;
    u8 pad2d8[0x39e - 0x2d8];
    u8 b39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 v3c0[4];
} Pk;
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_001315c0(Pk *, s32, f32 *, f32);
void func_00153e80(Pk *, s32, f32);
void func_0012bd98(Pk *, u8, u32, f32 *);
void func_00146c98(Pk *, s32);
void func_00130398(Pk *, s32, f32);

void func_00144650(Pk *o) {
    f32 v[4];

    if (D_002BC128 == 13 && D_002BC130 == 8) return;
    func_001315c0(o, 0x8003, v, 0.0f);
    if (v[1] > o->f2d4) {
        func_0014f658((Pl *)o, 17);
        func_002675a8(o->c148->va0, o->v3c0);
        o->c148->va0[1] = 0.0f;
        func_00121fc4(o->c148->va0, o->c148->va0);
        o->c148->fb8 = o->c148->fac * 0.7f;
        o->c148->fb0 = 40.0f;
        o->c148->fb4 = 30.0f;
        if (o->w88 & 0x20) {
            func_00153e80(o, 45, 16.0f);
        } else {
            func_00130398(o, 45, 16.0f);
            o->flags &= ~4;
        }
        func_0012bd98(o, o->b39e, 0x80000008, v);
        func_00146c98(o, 10);
    }
}

typedef struct { u8 cnt[7]; struct { u8 pct; u8 id; } drop[3]; } DropDef;
extern f32 D_00306844;
extern f32 D_00306848;
extern s32 D_002C5C4C;
DropDef *func_00144e88(void *);
void func_00146188(s32, f32 *, s32);
void func_001515d0(u8, void *, s32);
f32 func_00176850(void);

void func_00144eb0(void *o, void *pos) {
    DropDef *d;
    s32 i, j, n, c;
    s32 flag = D_002C5C4C != 0;

    d = func_00144e88(o);
    for (i = 0; i < 7; i++) {
        n = d->cnt[i] * D_00306844;
        for (j = 0; j < n; j++) {
            func_00146188(i, pos, flag);
        }
    }
    for (i = 0; i < 3; i++) {
        c = d->drop[i].pct * D_00306848;
        if ((s32)(func_00176850() * 100.0f) < c) {
            func_001515d0(d->drop[i].id, pos, flag);
        }
    }
}

typedef struct { f32 p[4]; f32 d[4]; f32 r20; f32 r24; s32 w28; u8 pad2c[0x14]; f32 out[4]; } Hit;
typedef struct { f32 h; f32 f4; s32 f8; s32 fc; s32 f10; } HtTab;
typedef struct {
    u8 pad0[0x10];
    union {
        u64 d;
        struct { u16 h10; u16 h12; u16 idx; u8 b16; u8 b17; } s;
        struct { u64 b0:2; u64 mode:2; u64 f4:1; u64 rest:59; } b;
    } u;
    f32 f18;
    s32 w1c;
    f32 vel[4];
} Bo;
extern Hit *D_00531B60;
extern HtTab D_00304DB0[];
extern f32 D_002C58A0[];
void func_00116660(Hit *);
void func_001166e8(Hit *);

void func_00145858(Bo *o, f32 *pos) {
    f32 t[4];
    Hit **pp = &D_00531B60;
    f32 h = D_00304DB0[o->u.s.idx].h;

    func_00116660((*pp));
    (*pp)->r20 = 55.0f;
    (*pp)->r24 = 60.0f;
    func_002675a8((*pp)->p, pos);
    (*pp)->p[1] += h;
    func_00121fc4(t, o->vel);
    if (t[3] > 45.0f) {
        func_00267560(o->vel, t, 45.0f);
    }
    func_002675a8((*pp)->d, o->vel);
    (*pp)->d[3] = 1.0f;
    (*pp)->w28 = 33;
    func_001166e8((*pp));
    func_00267530(t, (*pp)->out, (*pp)->p);
    if (fabsf(t[0] - o->vel[0]) > 0.0999999940395355224609375f) {
        o->vel[0] = -o->vel[0];
    }
    if (fabsf(t[2] - o->vel[2]) > 0.0999999940395355224609375f) {
        o->vel[2] = -o->vel[2];
    }
    func_002675a8(pos, (*pp)->out);
    pos[1] -= h;
    pos[3] = 1.0f;
    if (o->vel[1] < 0.0f) {
        o->vel[1] += o->vel[3];
    } else {
        o->vel[3] += -0.05f;
        o->vel[1] += o->vel[3];
        if (o->vel[1] < 0.0f) {
            func_002675a8(o->vel, D_002C58A0);
            o->u.s.b16 = 1;
        }
    }
    o->vel[0] *= 0.95f;
    o->vel[2] *= 0.95f;
    if (o->vel[1] > 0.0f) {
        o->u.d |= 2;
    }
}

typedef struct {
    f32 v[4];
    f32 f10;
    f32 f14;
    union {
        u8 id;
        struct { u64 lo:8; u64 f8:1; u64 f9:1; u64 f10:1; u64 rest:53; } b;
    } u;
} Spr;
extern Spr D_0035C710[];
extern u8 D_0052EB50[];
extern Bo D_0052EB60[];
Bo *func_0011f090(void *, s32, void *);
void func_00145ce8();

void func_00146188(s32 id, f32 *pos, s32 mode) {
    Bo *b;
    Spr *e;

    b = func_0011f090(D_0052EB50, 0, func_00145ce8);
    if (b == 0) return;
    e = &D_0035C710[b - D_0052EB60];
    func_002675a8(e->v, pos);
    e->v[3] = 1.0f;
    e->u.id = id;
    e->f10 = 1.0f;
    e->f14 = 1.0f;
    e->u.b.f8 = 1;
    e->u.b.f10 = 1;
    e->u.b.f9 = 0;
    b->u.s.h10 = 0;
    b->u.b.mode = mode;
    b->u.b.f4 = 1;
    b->u.s.idx = id;
    b->u.s.b16 = 0;
    b->u.s.b17 = 0;
    b->vel[0] = func_00176850() * 40.0f - 20.0f;
    b->vel[2] = func_00176850() * 40.0f - 20.0f;
    b->f18 = 900.0f;
    b->w1c = 0;
    b->u.s.h12 = 0;
    switch (mode) {
    case 0:
        b->vel[1] = func_00176850() * 20.0f + -40.0f;
        break;
    case 1:
        {
            f32 r = func_00176850() * 10.0f;
            b->vel[3] = 1.0f;
            b->vel[1] = r + -20.0f;
        }
        break;
    case 2:
        b->f18 = -1.0f;
        break;
    }
}

typedef struct { u64 d0; u32 w8; void *pc; } Fx;
typedef struct {
    u32 flags;
    s32 w4;
    u8 pad8[0x50 - 8];
    f32 v50[4];
    u8 pad60[0x9c - 0x60];
    u32 w9c;
    u8 padA0[0x370 - 0xa0];
    union { u64 x; struct { u32 lo0; u32 lo:5; u32 kind:2; u32 hi:25; } b; } u370;
    u8 pad378[0x39e - 0x378];
    u8 b39e;
} Pf;
extern u32 D_002C5958;
extern s8 D_0030884F[];
s32 func_001063c8(Pf *);
void func_00146fb8(Pf *, s32, s32);

void func_00146ff0(Pf *o, s32 kind, s32 arg, s32 bit) {
    Fx *fx;
    s32 n;

    if ((D_002C5958 >> 9) & 1) return;
    if (o->w9c & (1 << bit)) return;
    if (func_001063c8(o)) return;
    if (o->u370.b.kind != 2 && !(o->flags & 1)) return;
    switch (kind) {
    case 0:
        fx = func_001473a8(arg, o->w4 + 1, o->v50);
        if (fx) {
            fx->pc = o;
            fx->d0 |= 4;
        }
        break;
    case 25:
        func_00146fb8(o, o->w4 + 1, arg);
        break;
    default:
        arg = D_0030884F[kind];
        if (arg < 0) break;
        if (arg == 10 && (u8)(o->b39e - 11) < 2) break;
        func_00146c98((Pk *)o, arg);
        break;
    }
}

typedef struct {
    u8 pad0[0x88];
    u32 w88;
    u8 pad8c[0x164 - 0x8c];
    s32 w164;
} Tgt;
typedef struct {
    union { u64 d; struct { u32 w; s32 w4; } s; } u;
    u16 h8;
    u16 ha;
    Tgt *tgt;
    u8 pad10[0x10];
} Snd32;
extern Snd32 D_00532B90[];
extern u8 D_00531F70[];
extern s32 D_00532B80;
s32 func_0011d6f0(u16, s32);
void func_00147338(u16, s32);
s32 func_00122ff8(Tgt *);
void func_00147300(Snd32 *);
void func_00146778(Snd32 *, s32);
s32 func_0011f130(void *, s32);

s32 func_001474a0(void) {
    Snd32 *p = D_00532B90;
    s32 i;
    s32 f;

    for (i = 0; i < 128; i++, p++) {
        if (!(p->u.s.w & 1)) continue;
        if ((s32)(p->u.d >> 1) & 1) {
            p->u.d = (p->u.d & ~2) | 8;
            if ((s32)(p->u.d >> 2) & 1) {
                p->ha = p->tgt->w164;
            }
        } else if ((s32)(p->u.d >> 3) & 1) {
            p->u.d &= ~8;
        } else if (!func_0011d6f0(p->h8, p->u.s.w4)) {
            func_00147338(p->h8, p->u.s.w4);
        } else {
            f = 0;
            if ((D_002C5958 >> 14) & 1) f = 1;
            if ((s32)(p->u.d >> 2) & 1) {
                if (!func_00122ff8(p->tgt) || p->ha != p->tgt->w164) {
                    func_00147300(p);
                } else if (p->tgt->w88 & 1) {
                    f = 1;
                }
            }
            func_00146778(p, f);
        }
    }
    D_00532B80 = func_0011f130(D_00531F70, 0);
    return 0;
}

typedef struct { u8 pad[0xc]; void *pc; u8 pad10[4]; } Rel20;
typedef struct { u32 w0; void *p4; void *p8; } Rel12;
extern u8 D_0048E398[];
extern u8 D_00533BA0[];
extern void *volatile D_00308CDC;
extern void *volatile D_003044A0;
extern Rel20 *volatile D_00547BA0;
extern void *volatile D_00547BA4;
extern Rel12 *volatile D_00547BA8;
extern void *volatile D_00547BAC;
extern void *volatile D_00547BB0;
void func_001205f0(void *, void *);
u32 func_001477c8(u32);

void func_001478e0(void) {
    void **p;
    s32 i;

    func_001205f0(D_0048E398, D_00533BA0);
    D_00308CDC = (void *)func_001477c8(0x58);
    D_003044A0 = (void *)func_001477c8(0);
    D_00547BA0 = (void *)func_001477c8(0x1a58);
    D_00547BA4 = (void *)func_001477c8(0x2e58);
    D_00547BA8 = (void *)func_001477c8(0x33d8);
    D_00547BAC = (void *)func_001477c8(0xa58);
    D_00547BB0 = (void *)func_001477c8(0xc6a8);
    p = (void *)func_001477c8(0x258);
    for (i = 0; i < 512; i++) {
        *p = (void *)func_001477c8((u32)*p);
        p++;
    }
    for (i = 0; i < 255; i++) {
        D_00547BA0[i].pc = (void *)func_001477c8((u32)D_00547BA0[i].pc);
    }
    for (i = 0; i < 63; i++) {
        D_00547BA8[i].p4 = (void *)func_001477c8((u32)D_00547BA8[i].p4);
        D_00547BA8[i].p8 = (void *)func_001477c8((u32)D_00547BA8[i].p8);
    }
}

typedef struct { u8 pad[4]; u8 b[8]; u8 padc[0x74 - 0xc]; } Ent74;
typedef struct { u8 pad[0x40]; s32 w40; s32 w44; s32 w48; u8 pad4c[0xf0 - 0x4c]; } StBuf;
extern Ent74 *D_00304BE8;
typedef struct { u8 b0, b1, b2, b3; s16 h4; s16 h6; } Itm;
Itm *func_00147840(s32);
void func_00141b10(s32, StBuf *);

s32 func_00149440(s32 kind, s32 id) {
    StBuf st;
    u8 *e;
    s32 a, b, r;
    u8 m = func_00147840(kind)->b2;

    if (m != 0 && m != 12) return 0;
    e = D_00304BE8[id].b;
    func_00141b10(id, &st);
    a = e[1] < st.w40;
    b = e[3] < st.w48;
    r = 0;
    switch (kind) {
    case 1:
    case 2:
    case 6:
    case 142:
        r = a | 2;
        break;
    case 3:
    case 7:
        r = b | 4;
        break;
    case 4:
    case 8:
    case 143:
    case 144:
        r = (a | b) | 8;
        break;
    case 152:
        r = 16;
        if (e[6] < 100) r = 17;
        break;
    case 153:
        r = 32;
        if (e[7] < 100) r = 33;
        break;
    case 154:
        r = 64;
        if (e[5] < 100) r = 65;
        break;
    }
    return r;
}
