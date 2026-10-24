#include "common.h"
#include "data/bss_0062.h"
void func_002672f8(void *, void *, void *);
void *func_00232cc0(s32);
void *func_001ba9d8(s32);
void func_001bcd10(void *, void *);
void func_00267578(void *, void *, void *);

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

/* ---- func_001b9ec0 ---- */
typedef struct { u8 sig[4]; s32 ver; } SaveHdr;
typedef struct { u8 p[68]; u8 b44; u8 p45[2]; u8 b47; } Rec9a8;
void func_001bb580(void);
void func_001be820(void *, u32);
void func_001baaf0(void *);
void func_001b9f78(s32);
Rec9a8 *func_001ba9a8(void);
void *func_001ba980(void);
void func_001baa20(void *);
void func_001bab80(s32, void *);
void func_001ba108(u8 *, s32);

void func_001b9ec0(void) {
    SaveHdr *s;
    Rec9a8 *r;
    func_001bb580();
    s = func_00232cc0(4);
    func_001be820(s, 0xB040);
    s->ver = 257;
    s->sig[0] = 'G';
    s->sig[1] = 'U';
    s->sig[2] = 'M';
    s->sig[3] = 'I';
    func_001baaf0(s);
    func_001b9f78(0);
    r = func_001ba9a8();
    r->b44 = 1;
    r->b47 = 1;
    func_001baa20(func_001ba980());
    func_001bab80(10, func_001ba9d8(0));
    func_001ba108(func_001ba9d8(0), 0);
}

/* ---- func_001ba060 ---- */
extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

void func_001ba060(u8 *p, s32 k) {
    u8 *d = p;
    u8 *s;
    u8 *t;
    s32 n, i;
    func_001be820(p, 3952);
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *d++ = *s++;
    t = func_001ba228(k + 71);
    for (i = 0; i < 32; i++) p[80 + i] = t[i];
}

/* ---- func_001ba108 ---- */
extern u8 D_006202A0[];
extern s32 D_00377648[];
extern u8 *D_00377748[];
void func_001be820(void *, u32);
u8 *func_001ba228(s32);

void func_001ba108(u8 *p, s32 k) {
    u8 *d = D_006202A0;
    u8 *s;
    u8 *t;
    s32 n, i;
    func_001be820(d, 3952);
    n = D_00377648[k];
    s = D_00377748[k];
    for (i = 0; i < n; i++) *d++ = *s++;
    func_001bcd10(p, D_006202A0);
    t = func_001ba228(k + 71);
    for (i = 0; i < 32; i++) p[80 + i] = t[i];
}

/* ---- func_001bb580 ---- */
#include "data/types/text_001a0000_h41.h"
extern ItTbl D_00377848;
extern ItTbl *D_00623210; /* src/data/bss_0062.c: s32 *D_00623210 */
extern s32 D_00623214;
extern s32 D_00623218;
extern It28 *D_0062321C; /* src/data/bss_0062.c: s32 D_0062321C */

void func_001bb580(void) {
    s32 i, j;
    D_00623210 = &D_00377848;
    D_0062321C = D_00377848.e;
    D_00623214 = 0;
    for (i = 0; D_0062321C[i].f4 != 0; i++) D_00623214++;
    for (j = 0; D_0062321C[i + j].f4 == 0; j++);
    D_00623218 = D_00623210->n - D_00623214 - j;
}

/* ---- func_001bbbd0 ---- */
typedef struct { s8 x, y, z, w; } C4;
extern C4 D_0037A130[16];
typedef struct { u16 h0; u16 rot; } Ori_1bbbd0;

void func_001bbbd0(f32 (*m)[4], Ori_1bbbd0 *o) {
    m[0][0] = D_0037A130[o->rot & 15].x;
    m[0][1] = D_0037A130[o->rot & 15].y;
    m[0][2] = D_0037A130[o->rot & 15].z;
    m[0][3] = 0;
    m[1][0] = D_0037A130[(o->rot >> 4) & 15].x;
    m[1][1] = D_0037A130[(o->rot >> 4) & 15].y;
    m[1][2] = D_0037A130[(o->rot >> 4) & 15].z;
    m[1][3] = 0;
    m[2][0] = D_0037A130[(o->rot >> 8) & 15].x;
    m[2][1] = D_0037A130[(o->rot >> 8) & 15].y;
    m[2][2] = D_0037A130[(o->rot >> 8) & 15].z;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1.0f;
}

/* ---- func_001bbce0 ---- */
typedef struct { u16 pos; u16 rot; } Ori_1bbce0;
typedef struct { f32 x, y, z, w; } V4_1bbce0;
s32 func_001bbdf0(Ori_1bbce0 *);
void sceVu0UnitMatrix(f32 (*)[4]);

void func_001bbce0(f32 (*m)[4], Ori_1bbce0 *o) {
    V4_1bbce0 t;
    s32 v = func_001bbdf0(o);
    t.x = (f32)(o->pos & 15) * 200.0f + (f32)(v & 15) * 200.0f * 0.5f;
    t.y = -((f32)((o->pos >> 4) & 15) * 200.0f + (f32)(((u16)v >> 4) & 15) * 200.0f * 0.5f);
    t.z = (f32)((o->pos >> 8) & 15) * 200.0f + (f32)(((u16)v >> 8) & 15) * 200.0f * 0.5f;
    t.w = 1.0f;
    sceVu0UnitMatrix(m);
    func_00267578(m, m, &t);
}

/* ---- func_001be010 ---- */
typedef struct { u8 id; u8 pad[3]; s32 n; } IdCnt;
extern s32 D_00625748;
extern IdCnt D_00625750[];
typedef struct { u8 p0[80]; u8 name[32]; } Chr_1be010;
extern void *D_006257D0; /* src/data/bss_0062.c: u8 *D_006257D0 */
extern s32 D_00625640;
extern u8 D_00623ED4[][96];
void func_001b9e40(s32, s32);
s32 func_001be110();
void func_001bd470(void);

s32 func_001be010(s32 k) {
    s32 i, r;
    Chr_1be010 *q, *p;
    for (i = 0; i < D_00625748; i++) func_001b9e40(D_00625750[i].id, D_00625750[i].n);
    q = D_006257D0;
    p = func_001ba9d8(k - D_00625640);
    for (i = 0; i < 32; i++) {
        p->name[i] = D_00623ED4[k][i];
        q->name[i] = D_00623ED4[k][i];
    }
    r = func_001be110(k - D_00625640, q);
    func_001bd470();
    return r + D_00625640;
}

/* ---- func_001be110 ---- */
typedef struct { u8 p0[12]; u8 b0c; u8 p0d[67]; u8 name[32]; } Chr_1be110;
typedef struct { u8 p0[36]; s32 w24; u8 p28[8]; } Info48;
void func_001bd090(Chr_1be110 *, Info48 *);
s32 func_001bb880(s32);

s32 func_001be110(s32 k, Chr_1be110 *c) {
    u8 buf[32];
    Info48 inf;
    Chr_1be110 *p;
    u8 save;
    s32 i;
    if (k < 10) {
        if (c == NULL) c = D_006257D0;
        func_001bd090(c, &inf);
        p = func_001ba9d8(k);
        save = p->b0c;
        for (i = 0; i < 32; i++) buf[i] = p->name[i];
        func_001bcd10(p, c);
        for (i = 0; i < 32; i++) p->name[i] = buf[i];
        if (inf.w24 != 0) p->b0c = save;
        else p->b0c = 0;
        return func_001bb880(k);
    }
}

/* ---- func_001be278 ---- */
extern s32 D_0037A128;
extern s32 D_00625640;
extern s32 D_00625648[];
s32 func_001baad0(void);
void func_001baaa8(s32);

s32 func_001be278(void) {
    s32 v, i;
    if (D_0037A128 != 0) return -1;
    v = func_001baad0();
    if (!(v & 0x80)) return v + D_00625640;
    for (i = 0; i < D_00625640; i++) {
        if (D_00625648[i] == (v & 0x7f)) return i;
    }
    func_001baaa8(0x80);
    return 0;
}

/* ---- func_001be4d8 ---- */
typedef struct { u8 p0[12]; u8 b0c; } Chr_1be4d8;
extern s32 D_00625640;
extern s32 D_00623E30;
extern u8 D_00623E49[][96];

void func_001be4d8(void) {
    s32 i;
    Chr_1be4d8 *c;
    for (i = D_00625640 + 1; i < D_00623E30; i++) {
        c = func_001ba9d8(i - D_00625640 - 1);
        if (D_00623E49[i][0]) c->b0c = D_00623E49[i][0] - (u8)D_00625640;
        else c->b0c = 0;
        if ((u8)(c->b0c - 1) >= 10) c->b0c = 0;
    }
}

typedef f32 Mtx[4][4];
void sceVu0UnitMatrix(Mtx);
void sceVu0MulMatrix(Mtx, Mtx, Mtx);

float sqrtf(float);

float sqrtf(float);

typedef struct { f32 x, y, z, w; } Q;

/* needs make: uses rodata */

/* ---- func_001bade8 ---- */
typedef struct { u16 id; u8 p[10]; } Ent12;
typedef struct { u16 n; u8 p2[110]; Ent12 e[1]; } Inv;
typedef struct { u8 p0[4]; Inv inv; } Sav2a0;
s32 func_001baad0(void);
void func_001ba930(s32, s32);

void func_001bade8(void) {
    Sav2a0 *sv = func_001ba9d8(func_001baad0());
    s8 a, b;
    s32 i;
    for (i = 0; i < sv->inv.n; i++) {
        switch (sv->inv.e[i].id) {
        case 45: case 46: a |= 0x40; break;
        case 47: case 48: a |= 0x80; break;
        case 51: a |= 4; break;
        case 52: a |= 8; break;
        case 53: a |= 0x10; break;
        case 54: a |= 0x20; break;
        case 55: a |= 1; break;
        case 56: a |= 2; break;
        case 49: b |= 2; break;
        case 50: b |= 1; break;
        case 57: b |= 4; break;
        case 58: b |= 8; break;
        }
    }
    func_001ba930(28, b);
    func_001ba930(29, a);
}

#include "data/data_0037.h"
#include "data/data_0038.h"
#include "data/data_0048.h"
#include "data/data_003C.h"
#include "data/pieces/D_003773E0.h"
