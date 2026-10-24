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

/* GS texture header: TEX0-style bitfield word at +0x18. */

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
