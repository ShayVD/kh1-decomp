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
void func_00146188(s32, void *, s32);
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
