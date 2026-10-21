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
typedef struct { u8 pad[0x4c]; u16 id; } S130;
typedef struct { u8 pad[0x130]; S130 *p; } SC;
typedef struct { u8 pad[0xc]; SC *c; } SArg;

typedef struct { u32 state; s32 cnt; u8 pad[0x18]; u8 sub[1]; } S5cd0;
typedef struct { s32 state; s32 cnt; u8 pad[0x28]; u8 sub[1]; } S70d0;
typedef struct { u8 pad0[0x30]; u8 a[0xc0]; u8 b[0xc0]; u8 c[0x780]; } E930;
typedef struct { u8 pad[0x180]; B192 b; } L240;
typedef struct { u32 state; f32 t; s32 x8; s32 xc; s32 x10; u8 pad[0xa8c]; s32 xaa0; } S8370;
typedef struct { u8 r, g, b, a; } RGBA;
typedef struct {
    s32 x0; s32 x4; u8 pad8[0x10]; s32 x18; s32 x1c; s32 x20;
    u8 pad24[8]; s32 x2c; s32 x30;
} Ctx;
typedef struct { s32 x0; Ctx *c; } S8140;

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
typedef struct { u8 pad[0x491]; u8 cur; } Sys;

extern u8 D_0045BC10[];
extern E860 D_00662A30[10];
extern u8 D_0045D240[];
extern u8 D_0045D248[];
Panel D_00667F60 ALIGNED(32);
Q4 *D_00667F50 ALIGNED(16);
Q4 *D_00667F54 ALIGNED(4);
S7df0 D_00667DF0 ALIGNED(16);
extern Q4 D_00351E10[];
extern u8 D_00668040[];
extern u8 D_0045D280[];
extern u8 D_0045D6D0[];
extern B192 D_00668060;
Panel D_00668290 ALIGNED(16);
extern Q4 *D_00668280;
extern S8370 D_00668370; /* src/data/bss_0066.c: s32 D_00668370[0x2ac] */
extern f32 D_002BBDFC;
Panel D_00668F90 ALIGNED(16);
extern Q4 *D_00668F80;
extern u8 D_0045E1F0[];
extern E930 D_0045FAC0[10];
extern u8 D_0045FA80[];
extern u8 D_0045FA88[];
extern u8 D_0045FA90[];
Panel D_006691E0 ALIGNED(32);
extern Q4 *D_006691D0;
extern Q4 *D_006691D4;
extern s32 D_00467408;
extern s32 D_0046740C;
Panel D_00669620 ALIGNED(32);
extern Q4 *D_00669610;
extern s32 D_00469C94;
extern s32 D_00469C98;
S7df0 D_006697C0 ALIGNED(64);
extern Q4 *D_00669920; /* src/data/bss_0066.c: s32 D_00669920 */
Q4 *D_00669924 ALIGNED(4);
extern void *D_00669A10[];
extern u8 D_004267F0[];
extern V4 D_00491830;
extern s32 D_0046A60C;
extern s32 D_0046A610;
extern HddCfg D_0046A688;
extern s32 D_0046A614;
extern u32 D_0046A608;
extern Sys *D_00304BE8;
extern s32 D_002C5C4C;
extern s32 D_002C5C50;
extern s32 D_0046A6B0[];
extern s32 D_0066AAA0;
extern void (*D_0066AA80)(void);

void *memset(void *, s32, u32);
s32 sprintf(char *, const char *, ...);
u32 strlen(const char *);
void func_0011ef10(s32, void *);
s32 func_0011ef38(void *);
s32 func_0013c318(u16);
Q4 *func_001f12c0(Q4 *, s32, s32, s32, s32, s32, s32);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
Q4 *func_002388b8(void *, s32, Q4 *);
void func_002393d8(void);
s32 func_00242bf0(s32);
void func_00245b08(s32, S5cd0 *);
void func_00245da0(void);
void func_00246120(SArg *, s32, f32);
s32 func_00246320(void);
void func_00246750(s32, s32, s32, f32);
void func_00246ed8(s32, S70d0 *);
void func_00247190(void);
void func_00247b50(Ctx *);
void func_00247bd0(Ctx *);
void func_00247c50(Ctx *);
void func_00247cf8(Ctx *);
void func_002480d8(Ctx *);
s32 func_0024a1c0(void *);
void func_0024aa48(s32, void *, s32);
void func_0024aac8(void *);
void func_0024af40(void *, void *, void *);
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

void func_00245e40(void) {
    s32 i;
    E860 *p;
    func_0024aac8(D_0045BC10);
    p = D_00662A30;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045D240, p->a, D_0045BC10);
        func_0024af40(D_0045D248, p->b, D_0045BC10);
        p++;
    }
    if (func_0011ef38(func_00245da0) == 0)
        func_0011ef10(0x28489, func_00245da0);
}

void func_00246038(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00667F60;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00667F60.q[i].d = D_00667F60.q[i].d * s;
    }
    D_00667F50 = func_002388b8(&D_00667F60, 1, D_00667F50);
}

void func_002461f8(SArg *a0, s32 a1, f32 f) {
    s32 t, k;
    func_002370c8(&D_00667DF0);
    D_00667DF0.xe0 = 5;
    D_00667DF0.x60 = 0x30003;
    func_00237018(&D_00667DF0, 22, 1);
    D_00667F54 = D_00351E10;
    D_00667F50 = D_00351E10 + 1;
    func_00246120(a0, a1, f);
    t = func_0013c318(a0->c->p->id);
    if (t == 1) k = 1;
    else if (t == 2) k = 2;
    if (func_00242bf0(k)) {
        func_00237018(D_00667F54, D_00667F50 - D_00667F54, 1);
    }
}

void func_00246438(void) {
    L240 l;
    memset(D_00668040, 0, 32);
    func_0024aac8(D_0045D280);
    func_0024af40(D_0045D6D0, &l, D_0045D280);
    D_00668060 = l.b;
    if (func_0011ef38(func_00246320) == 0)
        func_0011ef10(0x28489, func_00246320);
}

void func_00246570(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668290;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668290.q[i].d = D_00668290.q[i].d * s;
    }
    D_00668280 = func_002388b8(&D_00668290, 1, D_00668280);
}

void func_00246dc0(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_00668F90;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_00668F90.q[i].d = D_00668F90.q[i].d * s;
    }
    D_00668F80 = func_002388b8(&D_00668F90, 1, D_00668F80);
}

void func_002470d0(S70d0 *p) {
    s32 r = 0;
    switch (p->state) {
    case 0:
        return;
    case 1:
        p->state = 2;
        r = 1;
        break;
    case 2:
        if (func_0024a1c0(p->sub) & 4) p->state++;
        break;
    case 3:
        p->state = 0;
        break;
    }
    p->cnt++;
    func_00246ed8(r, p);
}

void func_00247258(void) {
    s32 i;
    E930 *p;
    func_0024aac8(D_0045E1F0);
    p = D_0045FAC0;
    for (i = 0; i < 10; i++) {
        func_0024af40(D_0045FA80, p->a, D_0045E1F0);
        func_0024af40(D_0045FA88, p->b, D_0045E1F0);
        func_0024af40(D_0045FA90, p->c, D_0045E1F0);
        p++;
    }
    if (func_0011ef38(func_00247190) == 0)
        func_0011ef10(0x28489, func_00247190);
}

void func_002474e8(s32 a0, s32 a1, s32 dx, s32 dy, f32 s) {
    s32 i;
    Panel *d = &D_006691E0;
    func_0024aa48(a0, d, a1);
    for (i = 0; i < 4; i++) { s32 *r = &d->r[i].b; r[-1] += dx << 4; r[0] += dy << 4; }
    for (i = 0; i < 4; i++) {
        D_006691E0.q[i].d = D_006691E0.q[i].d * s;
    }
    D_006691D0 = func_002388b8(&D_006691E0, 1, D_006691D0);
}

void func_002475d0(s32 a0, s32 a1, u8 *c, char *a3, s32 a4, f32 f) {
    RGBA col;
    col.r = *c++;
    col.g = *c++;
    col.b = *c++;
    col.a = (u32)(f * 128.0f);
    D_006691D0 = func_001f12c0(D_006691D0, 1, *(s32 *)&col, a0, a1, (s32)a3, a4);
}

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
    c = D_00304BE8->cur;
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

void func_00245cd0(S5cd0 *p) {
    s32 r = 0;
    switch (p->state) {
    case 0:
        return;
    case 1:
        r = 1;
        p->state++;
        break;
    case 2: case 3: case 4:
        p->state++;
        break;
    case 5:
        if (func_0024a1c0(p->sub) & 4) p->state++;
        break;
    case 6:
        p->state = 0;
        return;
    }
    p->cnt++;
    func_00245b08(r, p);
}

s32 func_00246aa8(void) {
    S8370 *p = &D_00668370;
    s32 f = p->xaa0;
    p->xaa0 = 0;
    switch (p->state) {
    case 0:
        return 0;
    case 1:
        p->t = 0.0f;
        p->state++;
        break;
    case 2:
        p->t += D_002BBDFC * 0.199999988079071044921875f;
        if (p->t >= 1.0f) {
            p->t = 1.0f;
            p->state++;
        }
        break;
    case 3:
        if (f == 0) p->state++;
        break;
    case 4:
        p->state++;
        p->t = 1.0f;
        break;
    case 5:
        p->t -= D_002BBDFC * 0.199999988079071044921875f;
        if (p->t <= 0.0f) {
            p->t = 0.0f;
            p->state = 0;
        }
        break;
    }
    func_00246750(p->xc, p->x10, f, p->t);
    return 0;
}

void func_00248010(Ctx *p) {
    char buf[16];
    u8 col[3];
    s32 x;
    col[0] = 0xff;
    col[1] = 0xff;
    col[2] = 0xff;
    sprintf(buf, "%d", p->x1c);
    x = 69;
    func_002475d0(x, 22, col, buf, D_00467408, 1.0f);
    x += strlen(buf) * 13;
    sprintf(buf, "m");
    func_002475d0(x + 2, 24, col, buf, D_0046740C, 1.0f);
}

/* func_00248010 must stay above this one (beqz vs beqzl). */
void func_00248140(S8140 *a) {
    Ctx *c;
    D_006691D4 = D_00351E10;
    D_006691D0 = D_00351E10 + 1;
    c = a->c;
    func_002393d8();
    if (c->x20) {
        if (c->x30 == 0) func_00247c50(c);
        else if (c->x2c == 0) func_00247bd0(c);
        else func_00247b50(c);
    }
    if (c->x4 || c->x18) func_002480d8(c);
    if (c->x4) func_00247cf8(c);
    if (c->x18) func_00248010(c);
    func_00237018(D_006691D4, D_006691D0 - D_006691D4, 1);
}

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
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_00491830.h"
