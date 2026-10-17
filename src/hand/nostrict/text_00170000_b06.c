/* worker b06: hand-matched camera functions (built without strict aliasing) */
#include "common.h"
typedef struct { f32 x, y, z, w; } V4;
typedef struct { V4 a; V4 b; V4 c; V4 d; } Ray;
typedef struct {
    s32 x0; u8 pad4[0x10 - 4]; V4 x10; u8 pad20[0x10]; f32 x30[3]; f32 x3c; u8 pad40[0x64 - 0x40]; f32 x64;
    u8 pad68[0x70 - 0x68]; s32 x70; u8 pad74[0xd0 - 0x74]; f32 xd0[4][4];
} ActB;
typedef struct { u32 x0, x4; u64 x8; u8 pad10[0x44 - 0x10]; f32 x44; } PadB;
typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n; f32 x4; f32 x8; f32 xc; u8 pad10[4]; f32 x14; s32 flags; u8 pad1c[4]; Seg seg[1];
} Path;
typedef struct Cam {
    V4 x0; V4 x10; V4 x20; V4 x30;
    s32 x40; s32 x44; f32 x48; f32 x4c; f32 x50; f32 x54; f32 x58; f32 x5c; f32 x60;
    u8 x64; u8 x65; u8 x66;
} Cam;
extern Path *D_00362438;
extern Cam D_00575940;
void func_0017b308(void *, Seg *, s32, s32, s32);
void func_0017b250(void *, void *, f32);
s32 func_0017b860(s32, V4 *, f32 *, s32 *);
s32 func_0017b4f8(s32 *, f32 *, f32);
extern ActB *D_00575894;
extern s32 D_00575890;
extern f32 D_005758C0;
extern f32 D_005758C4;
extern V4 D_005758D0;
extern V4 D_005758E0;
extern V4 D_00362680;
extern f32 D_00362684;
extern f32 D_002BBDFC;
extern PadB D_002C5BB0;
extern u8 D_002C58A0[];
extern u8 D_002C58D0[];
f32 func_00120c88(f32);
s32 func_00118b58(void *);
s32 func_00119688(void *);
f32 func_00124d28(V4 *, V4 *);
void func_00176f08(s32, f32);
void func_0017bc90(s32);
void func_0017cb88(void);
void func_00267768(void *, void *, f32);
void func_00267810(void *, void *, f32);
void func_002672f8(void *, void *, void *);
void func_002675a8(void *, void *);
void func_00267518(void *, void *, void *);
void func_00267530(void *, void *, void *);
void func_00121fc4(void *, void *);
void func_00267e90(void *, void *, f32);
s32 func_00177608(void *, void *, void *);
s32 func_001772c8(ActB *);
f32 sinf(f32);
f32 cosf(f32);

/* ---- func_0017bc90 ---- */
void func_0017bc90(s32 a0) {
    f32 m[4][4];
    V4 p;
    f32 d;
    s32 f;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 dir;
    f32 bt;
    s32 bi;
    f32 i;

    loop = 0;
    if (path->flags & 1) loop = 1;
    if (D_00575940.x60 <= 0.0f) {
        dir = 0.0f;
        f = 1;
        func_0017b308(m, path->seg, path->n, D_00575940.x40, loop);
        func_0017b250(&p, m, D_00575940.x48);
        func_0017b860(a0, &p, &d, &f);
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = 1.0f;
        }
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, -10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = -1.0f;
        }
        if (dir == 0.0f) return;
    } else {
        dir = D_00575940.x50;
        D_00575940.x60 -= D_002BBDFC;
    }
    bt = 0.0f;
    f = 1;
    t = D_00575940.x48;
    d = 0.0f;
    idx = D_00575940.x40;
    func_0017b308(m, path->seg, path->n, idx, loop);
    bi = -1;
    for (i = 0.0f; i < 100.0f; i += 1.0f) {
        func_0017b250(&p, m, t);
        if (func_0017b860(a0, &p, &d, &f)) {
            bi = idx;
            bt = t;
        }
        if (func_0017b4f8(&idx, &t, dir)) func_0017b308(m, path->seg, path->n, idx, loop);
    }
    func_0017b308(m, path->seg, path->n, bi, loop);
    func_0017b250(&D_00575940.x10, m, bt);
    D_00575940.x44 = bi;
    D_00575940.x4c = bt;
    D_00575940.x50 = dir;
}

/* ---- func_0017cb88 ---- */
f32 func_00120c18(void *);

void func_0017cb88(void) {
    f32 m[4][4];
    V4 p;
    f32 d;
    s32 f;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 dir;
    f32 bt;
    s32 bi;
    f32 i;

    loop = 0;
    if (path->flags & 1) loop = 1;
    if (D_00575940.x60 <= 0.0f) {
        dir = 0.0f;
        f = 1;
        func_0017b308(m, path->seg, path->n, D_00575940.x40, loop);
        func_0017b250(&p, m, D_00575940.x48);
        func_0017b860(1, &p, &d, &f);
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = 1.0f;
        }
        idx = D_00575940.x40;
        t = D_00575940.x48;
        func_0017b308(m, path->seg, path->n, idx, loop);
        if (func_0017b4f8(&idx, &t, -10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            D_00575940.x60 = 20.0f;
            dir = -1.0f;
        }
        if (dir == 0.0f) return;
    } else {
        dir = D_00575940.x50;
        D_00575940.x60 -= D_002BBDFC;
    }
    bt = 0.0f;
    d = 0.0f;
    idx = D_00575940.x40;
    t = D_00575940.x48;
    f = 1;
    func_0017b308(m, path->seg, path->n, idx, loop);
    bi = -1;
    for (i = 0.0f; i < path->x4; i += 10.0f) {
        func_0017b250(&p, m, t);
        if (func_0017b860(1, &p, &d, &f)) {
            bi = idx;
            bt = t;
            if (d < -0.5f) break;
        }
        func_00267530(&p, &D_00575940.x30, &p);
        if (func_00120c18(&p) < path->xc) break;
        if (func_0017b4f8(&idx, &t, dir * 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
    }
    func_0017b308(m, path->seg, path->n, bi, loop);
    func_0017b250(&D_00575940.x10, m, bt);
    D_00575940.x44 = bi;
    D_00575940.x4c = bt;
    D_00575940.x50 = dir;
}

/* ---- func_0017d628 ---- */
typedef struct Box { V4 min; V4 max; void *x20; s32 x24; u8 pad28[8]; } Box;
extern Box *D_00362430;
extern void *D_00362434;
extern Box *D_0036243C;
extern s32 D_00362448;
extern s32 D_00362424;
extern s32 D_002E27A8;
extern u32 D_002C5960;
typedef struct { s32 x0; f32 x4; u8 pad8[8]; V4 x10; } S920;
extern S920 D_00575920;

s32 func_0017d628(void) {
    V4 pos;
    s32 i;
    s32 found = 0;
    Box *e;

    if (D_002E27A8 == 7) return 0;
    if (D_002E27A8 == 2) return 0;
    if (!D_00362424) return 0;
    if ((D_002C5960 >> 4) & 1) return 0;
    func_002675a8(&pos, &D_00575894->x10);
    pos.y -= 100.0f;
    for (i = 0; i < D_00362448; i++) {
        e = &D_00362430[i];
        if (e->min.x <= pos.x && pos.x <= e->max.x && e->min.y <= pos.y && pos.y <= e->max.y
            && e->min.z <= pos.z && pos.z <= e->max.z) {
            if (e->x20) {
                if (D_002E27A8 != 9) {
                    if ((e->x24 & 2) && !(D_00575890 & 1)) D_00575940.x65 = 1;
                    func_00176f08(9, 30.0f);
                } else if (D_0036243C && D_0036243C != e && (D_0036243C->x24 & 2) && (e->x24 & 2)
                           && e->x20 != D_0036243C->x20 && !(D_00575890 & 1)) {
                    D_00575940.x65 = 1;
                }
                if (e->x24 & 2) {
                    D_00362434 = 0;
                    D_00362438 = e->x20;
                } else {
                    D_00362434 = e->x20;
                    D_00362438 = 0;
                }
            } else if (D_002E27A8 == 9) {
                if (D_0036243C && (D_0036243C->x24 & 2)) {
                    if (D_00575920.x0) func_00176f08(3, 30.0f);
                    else func_00176f08(1, 30.0f);
                } else {
                    func_00176f08(1, 0.0f);
                }
                D_00362434 = 0;
                D_00362438 = 0;
            } else if (D_0036243C != e) {
                func_00176f08(1, 30.0f);
            }
            D_0036243C = e;
            found = 1;
            break;
        }
    }
    if (i == D_00362448 && D_0036243C) {
        if (D_0036243C->x24 & 1) {
            if (D_0036243C->x24 & 2) {
                if (D_00575920.x0) {
                    func_002675a8(&D_00575920.x10, &D_005758E0);
                    func_00176f08(3, 30.0f);
                } else {
                    func_00176f08(1, 30.0f);
                }
            } else {
                func_00176f08(1, 30.0f);
            }
            D_00362434 = 0;
            D_00362438 = 0;
            D_0036243C = 0;
        }
    }
    return found;
}

/* ---- zz_ro_func_0017c190 ---- */
/* needs make: uses rodata (-0.0f folded from the clamp, at 0x0048EAE4) */
extern V4 D_00575860;
extern f32 D_003625E4;
f32 func_00267390(void *, void *);
void func_002673b8(void *, void *);
f32 func_0017c110(s32, f32);

s32 func_0017c190(void) {
    f32 m[4][4];
    V4 p;
    s32 idx;
    f32 t;
    Path *path = D_00362438;
    s32 loop;
    f32 base, a, d, c, k, s, t0;
    s32 i0;

    loop = 0;
    if (path->flags & 1) loop = 1;
    base = func_00124d28(&D_005758D0, &D_00575940.x30);
    a = base;
    if (D_00575940.x66 == 2) {
        func_002675a8(&D_00575860, D_00575894->x30);
        D_00575860.y = 0.0f;
        func_002673b8(&D_00575860, &D_00575860);
        D_00575940.x66 = 3;
        D_003625E4 = 0.0f;
    }
    func_00267530(&p, &D_005758D0, &D_00575940.x30);
    p.y = 0.0f;
    func_002673b8(&p, &p);
    d = func_00267390(&p, &D_00575860);
    k = (-1.0f - (d < -1.0f ? -1.0f : (-0.9f < d ? -0.9f : d))) / -0.1f;
    if (k < 0.1f) return 0;
    s = k * 0.1221730355f;
    idx = D_00575940.x40;
    t = D_00575940.x48;
    func_0017b308(m, path->seg, path->n, idx, loop);
    while (fabsf(func_00120c88(a - base)) < s * D_002BBDFC) {
        t0 = t;
        i0 = idx;
        func_0017b250(&p, m, t0);
        a = func_00124d28(&p, &D_00575940.x30);
        D_003625E4 += 10.0f;
        if (func_0017b4f8(&idx, &t, D_00575940.x50 * 10.0f)) func_0017b308(m, path->seg, path->n, idx, loop);
        if (i0 == idx && t == t0) return 0;
    }
    if (!(func_0017c110(idx, t) > 150.0f)) return 0;
    D_00575940.x40 = idx;
    D_00575940.x44 = idx;
    D_00575940.x48 = t;
    D_00575940.x4c = t;
    func_0017b308(m, path->seg, path->n, idx, loop);
    func_0017b250(&D_00575940.x10, m, t);
    if (path->x4 < D_003625E4) return 0;
    return 1;
}
