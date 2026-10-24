#include "common.h"
#include "data/bss_0062.h"
void func_002672f8(void *, void *, void *);

/* ---- func_001a26f0 ---- */
void *memset(void *, s32, u32);
f32 func_001a2178(void);
void func_002673b8(void *, void *);
void func_001a2248(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a26f0;
typedef struct { u8 pad[124]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a26f0;

static inline f32 vlen3_1a26f0(V4_1a26f0 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

void func_001a26f0(s32 a0, Emit_1a26f0 *e, V4_1a26f0 *m, void *b) {
    V4_1a26f0 t;
    f32 r, d;
    memset(m, 0, 96);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    func_002673b8(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a2178() - r;
        m->y = d * func_001a2178() - r;
        m->z = d * func_001a2178() - r;
    } while (r < vlen3_1a26f0(m));
    m->w = 1.0f;
    func_002672f8(m, D_00615F30, m);
    func_001a2248(e, m, b);
}

/* ---- func_001a30d8 ---- */
void sceVu0UnitMatrix(f32 (*)[4]);
void sceVu0MulMatrix(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_002676c0(f32 (*)[4], f32 (*)[4], f32);
void func_002675a8(f32 *, void *);
#include "data/pieces/D_003701F0.h"
extern f32 D_00615EB0[4][4]; /* src/data/bss_0061.c: u8 D_00615EB0[0x40] */
extern f32 D_00616040[4][4]; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
typedef struct { u8 pad[44]; f32 rot; u8 pad2[8]; f32 sx, sy; } Spr;
typedef struct { u8 pad[164]; f32 sc, of; } Cam;

f32 func_001a30d8(s32 a0, f32 (*m)[4], Cam *c, s32 a3, Spr *s) {
    f32 r;
    sceVu0UnitMatrix(m);
    m[0][0] = s->sx * D_003701F0[0];
    m[1][1] = s->sy * D_003701F0[1];
    m[2][2] = s->sx * D_003701F0[0];
    if (s->rot != 0.0f) func_002676c0(m, m, s->rot * 3.1415927f / 180.0f);
    func_002675a8(m[3], s);
    func_002672f8(m[3], D_00615EB0, m[3]);
    m[3][1] *= c->sc;
    r = m[3][2];
    m[3][1] += c->of;
    sceVu0MulMatrix(m, D_00616040, m);
    return r;
}

/* ---- func_001a4028 ---- */
void *memset(void *, s32, u32);
f32 func_001a3650(void);
void func_002673b8(void *, void *);
void func_001a3720(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a4028;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a4028;

static inline f32 vlen3_1a4028(V4_1a4028 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

void func_001a4028(s32 a0, Emit_1a4028 *e, V4_1a4028 *m, void *b) {
    V4_1a4028 t;
    f32 r, d;
    memset(m, 0, 160);
    if (b) memset(b, 0, 32);
    t.x = e->p[0];
    t.y = e->p[1];
    t.z = e->p[2];
    t.w = 1.0f;
    func_002673b8(m + 1, &t);
    r = e->r0 + e->r1;
    d = r + r;
    do {
        m->x = d * func_001a3650() - r;
        m->y = d * func_001a3650() - r;
        m->z = d * func_001a3650() - r;
    } while (r < vlen3_1a4028(m));
    m->w = 1.0f;
    func_002672f8(m, D_00615F30, m);
    func_001a3720(e, m, b);
}

/* ---- func_001a47b0 ---- */
void *memset(void *, s32, u32);
f32 func_001a3650(void);
void func_002673b8(void *, void *);
void func_001a3720(void *, void *, void *);
extern u8 D_00615F30[];
typedef struct { f32 x, y, z, w; } V4_1a47b0;
typedef struct { u8 pad[184]; f32 p[3]; u8 pad2[20]; f32 r0, r1; } Emit_1a47b0;

static inline f32 vlen3_1a47b0(V4_1a47b0 *v) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf10, 0(%1)\n"
        "vmul.xyz $vf10xyz, $vf10xyz, $vf10xyz\n"
        "vaddx.y $vf10y, $vf10y, $vf10x\n"
        "vaddy.z $vf10z, $vf10z, $vf10y\n"
        "vsqrt Q, $vf10z\n"
        "vwaitq\n"
        "vaddq.x $vf10x, $vf0x, Q\n"
        "qmfc2 $2, $vf10\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(v) : "$2", "memory");
    return r;
}

typedef struct { u8 pad[0xB0]; u64 flags; } PppSys;
extern s32 D_0061621C;
extern PppSys *D_00615E60; /* src/data/bss_0061.c: void *D_00615E60 */
typedef struct { u8 pad[32]; u16 alive; u8 pad2[126]; } Ptcl;
typedef struct { u8 pad[32]; } PtclX;
typedef struct { Ptcl *p; PtclX *x; s32 n; u8 pad[4]; u16 cnt; } PGrp;
typedef struct { u8 pad[4]; s32 id; u8 pad2[4]; u16 max; u16 ival; } PKey;
void func_001a4168(PGrp *, PKey *, Ptcl *, s32, PtclX *);

void func_001a47b0(PGrp *g, PKey *k, s32 a2) {
    Ptcl *p = g->p;
    PtclX *x = g->x;
    s32 n = g->n;
    s32 em = 0;
    s32 i;
    if (D_0061621C != 0) return;
    if (D_00615E60->flags & 0xFF0000FF00ULL) return;
    if (k->id == 0xffff) return;
    g->cnt++;
    for (i = 0; i < n; i++) {
        if (p->alive) {
            func_001a4168(g, k, p, a2, x);
        } else if (k->ival <= g->cnt && em < k->max) {
            func_001a4028((s32)g, (Emit_1a4028 *)k, (V4_1a4028 *)p, x);
            em++;
        }
        if (x) x++;
        p++;
    }
    if (em > 0) g->cnt = 0;
}

/* ---- func_001a5fd0 ---- */
typedef struct { s32 a; f32 r; } Ent8;
typedef struct { u8 pad[4]; s32 v; u8 n; u8 fl; u8 pad2[6]; Ent8 e[1]; } Rnd;
void func_001a5688(Ent8 *, s32);

void func_001a5fd0(Rnd *r, s32 v, s32 seed) {
    s32 i;
    r->v = v;
    for (i = 0; i < r->n; i++) func_001a5688(&r->e[i], v);
    if (!(u8)(r->fl & 1)) {
        s32 x = seed;
        for (i = 0; i < r->n; i++) {
            x = (x * 2061 + 7) & 0xffff;
            r->e[i].r = (f32)x / 65535.0f;
        }
        r->fl |= 1;
    }
}

/* ---- func_001a8828 ---- */
typedef struct Lnk { u8 p0[8]; struct Lnk *next; struct Lnk *pprev; } Lnk;
typedef struct { u8 p[48]; } Ent48;
typedef struct {
    u8 p0[8]; Lnk *next; Lnk *pprev; u8 p10[36];
    u16 h34; u8 p36[2]; u16 h38; u8 p3a[2]; u16 h3c; u16 h3e;
    Ent48 e[1];
} Hdr9;
void func_001a67b8(Ent48 *, s32);

void func_001a8828(Hdr9 *h) {
    Ent48 *e = h->e;
    s32 n = h->h3c;
    s32 f = h->h3e & 0x20;
    for (; n > 0; n--) func_001a67b8(e++, f);
    e = &h->e[h->h34];
    for (n = h->h38; n > 0; n--) func_001a67b8(e++, f);
    if (h->pprev) {
        if (h->next) h->next->pprev = h->pprev;
        *(Lnk **)h->pprev = h->next;
    }
}

/* ---- func_001a89f0 ---- */
typedef struct DL { struct DL *next; struct DL *prev; } DL;
typedef struct { DL l; u8 p8[40]; s32 w30; u8 p34[10]; u16 h3e; u8 e40[28]; s32 w5c; u8 e60[32]; } Hdr10;
typedef struct { DL *next; u8 f; } Grp10;
typedef struct { u8 p0; u8 n; } Pool10;
typedef struct { Hdr10 *h; u8 n; } Bld10;
Hdr10 *func_001a8900(Pool10 *);
void func_001a8780(Bld10 *);
void func_001a9098(void *, s32);

void func_001a89f0(Grp10 *g, Pool10 *pl, s32 a, s32 b) {
    Hdr10 *h = func_001a8900(pl);
    Bld10 bl;
    s32 fl;
    if (h == NULL) return;
    bl.h = h;
    bl.n = pl->n;
    fl = 0x100;
    func_001a8780(&bl);
    h->w5c = 0;
    h->w30 = 0;
    if (g->f & 4) fl = 0x180;
    if (g->f & 0x10) fl |= 0x200;
    if (g->f & 8) fl |= 0x400;
    if (g->f & 0x20) fl |= 0x1000;
    h->h3e |= fl;
    func_001a9098(h->e40, a);
    func_001a9098(h->e60, b);
    if (g->next) g->next->prev = &h->l;
    h->l.next = g->next;
    h->l.prev = (DL *)g;
    g->next = &h->l;
}

/* ---- func_001a9eb8 ---- */
extern u64 D_0061E800[];
extern u64 D_0061E8B0[];

void func_001a9eb8(void) {
    u64 *p = D_0061E800;
    p[2] = 0x5000000000008001ULL;
    p[3] = 0xEEEEE;
    p[6] = 0x131000070ULL;
    p[7] = 78;
    p[12] = 0x7000D;
    p[13] = 71;
    p[14] = 33;
    p[15] = 20;
    p[18] = 0;
    p[19] = 8;
    p[16] = 0x8000000000ULL;
    p[17] = 59;
    p = D_0061E8B0;
    p[2] = 0x5000000000008001ULL;
    p[3] = 0xEEEEE;
    p[6] = 0x31000070;
    p[7] = 78;
    p[12] = 0x7000D;
    p[13] = 71;
    p[14] = 33;
    p[15] = 20;
    p[18] = 0;
    p[19] = 8;
    p[16] = 0x8000000000ULL;
    p[17] = 59;
}

/* ---- func_001aa7a0 ---- */
typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    u8 p0[16]; u64 tag; u64 regs;
    union { u128 q; struct { u8 a; u8 p1[3]; u8 b; u8 p2[3]; u64 d; } s; } u20;
    u128 rgba; u128 xy0; u128 xy1;
} Spr7a;
void func_001aa700(void *, s32, s32, s32);

u8 *func_001aa7a0(p, col, a, b) Spr7a *p; u32 col; u8 a; u8 b; {
    u128 c;
    p->tag = 0x41A3400000008001ULL;
    p->regs = 0x441E;
    __asm__ volatile("sq $0, 32(%0)" : : "r"(p) : "memory");
    p->u20.s.a = a;
    p->u20.s.b = b;
    p->u20.s.d = 66;
    __asm__ volatile("pextlb %0, $0, %1\n\tpextlh %0, $0, %0\n\tsq %0, 48(%2)" : "=r"(c) : "r"(col), "r"(p) : "memory");
    p->xy0 = 0xFFFFFFFE0000780000007000;
    p->xy1 = 0xFFFFFFFE0000880000009000;
    func_001aa700(p, 6, 0, 0);
    return (u8 *)p + 96;
}

/* ---- func_001aaa70 ---- */
extern char D_0048FE18[];
s32 func_0025b588(char *, s32);
s32 func_0025b990(s32, s32, s32);
s32 func_0025bbc8(s32, void *, s32);
void func_0025b810(s32);
int printf(const char *, ...);
void exit(s32);
void FlushCache(s32);

s32 func_001aaa70(char *name, void *buf) {
    char tmp[1024];
    s32 fd, size;
    fd = func_0025b588(name, 1);
    if (fd < 0) {
        printf(D_0048FE18, name);
        exit(1);
    }
    size = func_0025b990(fd, 0, 2);
    func_0025b990(fd, 0, 0);
    if (size != func_0025bbc8(fd, buf, size)) size = 0;
    func_0025b810(fd);
    FlushCache(0);
    return size;
}

void func_001be820(void *, u32);

extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

#include "data/types/text_001a0000_h41.h"

void sceVu0UnitMatrix(f32 (*)[4]);

extern s32 D_00625640;

extern s32 D_00625640;
s32 func_001baad0(void);

extern s32 D_00625640;

typedef f32 Mtx[4][4];
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

float sqrtf(float);

float sqrtf(float);

typedef struct { f32 x, y, z, w; } Q;

/* needs make: uses rodata */

s32 func_001baad0(void);

#include "data/data_0037.h"
#include "data/data_0038.h"
#include "data/data_0048.h"
#include "data/data_003C.h"
#include "data/pieces/D_003773E0.h"
