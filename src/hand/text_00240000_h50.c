#include "common.h"
#include "data/bss_0066.h"

/* 16-byte list entries; the D_00667F50/D_00667F54-style globals are
 * [end, begin) pointers into such lists. */
#include "data/types/text_00240000_h50.h"

/* Panel state blocks (D_00667F60, D_00668290, D_00668F90, D_006691E0). */
typedef struct { u8 pad[0x60]; Q4 q[4]; Q4 r[4]; } Panel;

typedef int u128 __attribute__((mode(TI)));

/* Render-packet headers set up before func_00237018 (D_00667DF0, D_006697C0). */
typedef struct { u8 pad[0x60]; u64 x60; u64 x68; u64 x70; u8 pad2[0x68]; u64 xe0; u8 tail[0x160 - 0xE8]; } S7df0;

#include "data/types/text_00240000_h50_p.h"
typedef union { f32 m[4][4]; u128 q[4]; } M44;

/* GS texture header: TEX0-style bitfield word at +0x18. */
typedef struct {
    u64 f0:14; u64 f14:6; u64 f20:6; u64 f26:11; u64 f37:14; u64 f51:5; u64 f56:5; u64 f61:3;
} TexBits;
typedef struct {
    u8 pad[8]; s32 x8; u8 padc[8]; s16 w; s16 h;
    TexBits tb;
    u8 pad20[0x10];
} GsTexHdr;
typedef struct { u8 pad[0x10]; GsTexHdr h; } GsTex;

/* ttlib/ui.c: 0xC0-byte UI elements with three keyframe tracks
 * (+0x64 and +0x8C: 32-byte frames, +0x78: 80-byte frames). Each track
 * is followed by a flags word; bit 2 is set when the track ends. The
 * flags at +0x60 are read both as a u64 (ld) and as a u32 (lw). */
typedef struct { s32 dur; u8 pad[0xc]; f32 v[4]; } Frame;
typedef struct { s32 dur; u8 pad[0x4c]; } Frame50;
typedef struct { s32 time; s32 idx; s32 n; Frame *fr; } Anim;
typedef struct { s32 time; s32 idx; s32 n; Frame50 *fr; } Anim50;
typedef union {
    struct { u8 pad[0x60]; u64 flags; } h;
    struct {
        u8 pad[0x60]; u32 flags;
        Anim a; u32 aflags;
        Anim50 b; u32 bflags;
        Anim c; u32 cflags;
        u8 pad2[0x20];
    } s;
} Ui;

typedef struct { u8 stat[0x40]; char name[256]; u8 pad[0x10]; } Dirent;
typedef struct { s32 x0; char *(*name)(void); char *(*pass)(void); s32 xc; s32 mounted; } HddCfg;
#include "data/pieces/D_00304BE8_s.h"
extern Q4 D_00351E10[];
Panel D_00669620 ALIGNED(32);
extern Q4 *D_00669610;
extern s32 D_00469C94;
extern s32 D_00469C98;
S7df0 D_006697C0 ALIGNED(64);
extern Q4 *D_00669920; /* src/data/bss_0066.c: s32 D_00669920 */
Q4 *D_00669924 ALIGNED(4);
extern void *D_00669A10[];
#include "data/pieces/D_004267F0.h"
extern V4 D_00491830;
extern s32 D_0046A60C;
extern s32 D_0046A610;
extern HddCfg D_0046A688;
extern s32 D_0046A614;
#include "data/pieces/D_0046A608.h"
extern s32 D_002C5C4C;
extern s32 D_002C5C50;
extern s32 D_0046A6B0[];
extern s32 D_0066AAA0;
extern void (*D_0066AA80)(void);
s32 sprintf(char *, const char *, ...);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
s32 func_0024a1c0(void *);
void func_0024aa48(s32, void *, s32);
Q4 *func_001f0638(Q4 *, s32, s32, s32, s32, s32);
void func_00248fb8(void *, void *);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_002673b8(V4 *, V4 *);
void func_00267370(V4 *, V4 *, V4 *);
void __assert(const char *, s32, const char *);
s32 func_00120a20(const char *, s32, char *, s32 *);
void func_0024d808(void);
s32 func_0025d880(const char *, const char *, s32, s32, s32);
const char *func_0024d8e0(void);
s32 func_0025b588(const char *, s32);
s64 func_0025db10(s32, s32, s32);
s32 func_0025b810(s32);
s32 func_0025cd70(const char *);
s32 func_0025cfa0(s32, Dirent *);
s32 func_0025ce38(s32);
s32 strcmp(const char *, const char *);
s32 func_001560f8(s32, void *);
void func_0024f1d0(void);

void func_00248798(s32 a0, s32 a1, s32 dx, s32 dy) {
    s32 i;
    Panel *d = &D_00669620;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    D_00669610 = func_002388b8(&D_00669620, 1, D_00669610);
}

void func_002488a8(s32 x, s32 y, s32 a2, s32 sel, f32 f) {
    u8 col[4];
    u8 *p;
    if (sel) {
        p = col; *p++ = 0x73; *p++ = 0x73; *p++ = 0x73;
        *p = (u32)(f * 128.0f);
    } else {
        p = col; *p++ = 0xe6; *p++ = 0xe6; *p++ = 0xe6;
        *p = (u32)(f * 128.0f);
    }
    D_00669610 = func_001f0638(D_00669610, 1, *(s32 *)col,
        ((((x + D_00469C94) << 4) + 0x7000) >> 4) - 0x700,
        ((((y + D_00469C98) << 4) + 0x7400) >> 4) - 0x740, a2);
}

void func_00249010(void) {
    s32 i;
    func_002370c8(&D_006697C0);
    D_006697C0.xe0 = 5;
    D_006697C0.x60 = 0x30003;
    D_006697C0.x70 = 0x8000000048ULL;
    func_00237018(&D_006697C0, 22, 1);
    D_00669924 = D_00351E10;
    D_00669920 = D_00351E10 + 1;
    for (i = 0; i < 2; i++) {
        func_00248fb8(D_00669A10[i], D_004267F0);
    }
    func_00237018(D_00669924, D_00669920 - D_00669924, 1);
}

void func_002490f0(s32 *st) {
    s32 i;
    switch (*st) {
    case 1:
        for (i = 0; i < 2; i++) func_0024ae00(D_00669A10[i]);
        (*st)++;
        break;
    case 2:
        for (i = 0; i < 2; i++) func_0024af00(D_00669A10[i]);
        if (func_0024a1c0(D_00669A10[0]) & 4) (*st)++;
        break;
    case 3:
        *st = 0;
        return;
    }
    func_00249010();
}

GsTexHdr *func_00249f08(GsTex *t, s32 a, s32 b, s32 c, s32 d, s32 e) {
    TexBits *tb = &t->h.tb;
    tb->f0 = a;
    tb->f20 = b;
    tb->f37 = c;
    tb->f56 = d;
    tb->f61 = e;
    return &t->h;
}

void func_0024a0e0(Ui *u, s32 *out) {
    Anim *a = &u->s.a;
    s32 i;
    if (a->idx < a->n - 1) {
        f32 t = (f32)a->time / (f32)a->fr[a->idx].dur;
        Frame *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i] + (f[1].v[i] - f->v[i]) * t;
    } else {
        Frame *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i];
    }
}

void func_0024a588(Ui *u, s32 *out) {
    Anim *a = &u->s.c;
    s32 i;
    if (a->idx < a->n - 1) {
        f32 c0[4], c1[4];
        f32 t = (f32)a->time / (f32)a->fr[a->idx].dur;
        Frame *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++) {
            c0[i] = f->v[i];
            c1[i] = f[1].v[i];
            out[i] = c0[i] + (c1[i] - c0[i]) * t;
        }
    } else {
        Frame *f = &a->fr[a->idx];
        for (i = 0; i < 4; i++)
            out[i] = f->v[i];
    }
}

s32 func_0024d9f0(void) {
    s32 *st = &D_0046A614;
    s32 fd, r;
    s64 sz;
    *st = 90;
    fd = func_0025b588(func_0024d8e0(), 1);
    *st = 100;
    if (fd < 0) {
        r = 1;
    } else {
        sz = func_0025db10(fd, 0, 2);
        *st = 110;
        func_0025b810(fd);
        *st = 120;
        r = 1;
        if (D_0046A608 == sz) r = 0;
    }
    return r;
}

s32 func_0024dcc8(const char *path, const char *name) {
    Dirent d;
    s32 fd, n, found = 0;
    fd = func_0025cd70(path);
    if (fd < 0) return 0;
    n = 0;
    while (func_0025cfa0(fd, &d) > 0) n++;
    func_0025ce38(fd);
    if (n == 0) return 0;
    fd = func_0025cd70(path);
    if (fd < 0) return 0;
    while (func_0025cfa0(fd, &d) > 0) {
        if (strcmp(d.name, name) == 0) found = 1;
    }
    func_0025ce38(fd);
    return found;
}

s32 func_0024f210(s32 a, void (*cb)(void)) {
    u8 c;
    s32 id;
    D_0066AAA0 = a;
    D_0066AA80 = cb;
    c = D_00304BE8->x48e[3];
    id = D_0046A6B0[c];
    if (D_002C5C4C) {
        if (c == 1) id = 0xc000a;
        else if (c == 2) id = 0xc000b;
    } else if (D_002C5C50) {
        if (c == 1) id = 0xc0008;
        else if (c == 2) id = 0xc0009;
    }
    func_001560f8(id, func_0024f1d0);
    return id;
}

/* ---- the functions below need make: they use rodata (jump tables,
 * string literals) ---- */

/* func_00248010 must stay above this one (beqz vs beqzl). */

void func_00249420(M44 *m, V4 *dir) {
    V4 x, y, z, up;
    up = D_00491830;
    func_002673b8(&z, dir);
    func_00267370(&x, &up, &z);
    func_00267370(&y, &z, &x);
    func_002673b8(&x, &x);
    func_002673b8(&y, &y);
    m->m[0][0] = x.x; m->m[0][1] = x.y; m->m[0][2] = x.z; m->m[0][3] = 0;
    m->m[1][0] = y.x; m->m[1][1] = y.y; m->m[1][2] = y.z; m->m[1][3] = 0;
    m->m[2][0] = z.x; m->m[2][1] = z.y; m->m[2][2] = z.z; m->m[2][3] = 0;
    m->q[3] = 0;
    m->m[3][3] = 1.0f;
}

void func_00249fb0(Ui *u, s32 dt) {
    if ((u->h.flags & 10) == 10) {
        Anim *ra = &u->s.a;
        if (!ra) __assert("ttlib/ui.c", 14, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.aflags |= 4;
                    break;
                }
            }
        }
    }
}

void func_0024a1c8(Ui *u, s32 dt) {
    if ((u->h.flags & 0xc0) == 0xc0) {
        Anim50 *ra = &u->s.b;
        if (!ra) __assert("ttlib/ui.c", 100, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.bflags |= 4;
                    break;
                }
            }
        }
    }
}

void func_0024a490(Ui *u, s32 dt) {
    if ((u->h.flags & 0x14) == 0x14) {
        Anim *ra = &u->s.c;
        if (!ra) __assert("ttlib/ui.c", 199, "ra");
        if (ra->idx < ra->n - 1) {
            ra->time += dt;
            while (ra->time >= ra->fr[ra->idx].dur) {
                ra->time -= ra->fr[ra->idx].dur;
                ra->idx++;
                if (ra->idx == ra->n - 1) {
                    u->s.cflags |= 4;
                    break;
                }
            }
        }
    }
}

s32 func_0024d4b0(void) {
    char hddarg[11] = "-o\0" "1\0" "-n\0" "20";
    char pfsarg[16] = "-m\0" "1\0" "-o\0" "1\0" "-n\0" "28";
    s32 res;
    D_0046A610 = 0;
    D_0046A60C = 0;
    func_00120a20("dev9.irx", 0, 0, &res);
    if (func_00120a20("atad.irx", 0, 0, &res) < 0) return 1;
    if (func_00120a20("hdd.irx", 10, hddarg, &res) < 0) return 1;
    if (func_00120a20("pfs.irx", 18, pfsarg, &res) < 0) return 1;
    D_0046A60C = 1;
    func_0024d808();
    return 0;
}

s32 func_0024d8f0(void) {
    HddCfg *c = &D_0046A688;
    if (c->mounted == 0) {
        char buf[128];
        char *n = c->name();
        s32 r;
        sprintf(buf, "hdd0:%s,%s", n, c->pass());
        r = func_0025d880("pfs0:", buf, 0, 0, 0);
        if (r < 0) return (r == -5) ? -1 : 1;
        c->mounted = 1;
    }
    return 0;
}
#include "data/bss_0066_typed.h"
#include "data/data_002C.h"
#include "data/data_0046.h"
#include "data/data_0045.h"
#include "data/pieces/D_00491830.h"
