#include "common.h"
typedef struct { u16 x0; u8 pad2[10]; u8 xc; } W29Sub;
typedef struct {
    s32 x0;
    s32 x4;
    s16 x8, xa;
    u16 xc, xe;
    u8 x10, x11, x12, x13;
    s32 x14;
    f32 x18, x1c;
    W29Sub *x20;
    void *x24;
    s32 x28;
} W29Obj;
extern s32 D_004D59F0[];
extern s32 D_004D5AF0;
void *func_00121e28(s32, void *);
void func_00121ee0(void *);
void func_0010d470(W29Obj *, W29Sub *);

s32 func_0010ef90(s32 a, s32 *out) {
    struct { W29Obj *o; W29Sub *s; } l;
    W29Obj *p, *p2, *p3, *p4, *p5;
    s32 i, m;
    p = l.o = func_00121e28(0x2C, &l.o);
    p->x12 = 0;
    p2 = l.o;
    p2->x10 = 1;
    p2->x0 = 0;
    p3 = l.o;
    p3->x4 = a;
    p3->x13 |= 2;
    p3->x8 = 0;
    p3->xa = 0;
    p3->x24 = 0;
    p3->x14 = 0;
    p4 = l.o;
    p4->x11 = 0;
    p5 = l.o;
    p5->xc = 0;
    p5->xe = 0;
    p5->x18 = 0;
    p5->x1c = 0;
    p5->x20 = 0;
    p5->x28 = 0;
    l.s = func_00121e28(0x1890, &l.s);
    func_0010d470(l.o, l.s);
    func_00121ee0(l.s);
    func_00121ee0(l.o);
    m = 0;
    for (i = 0; i < D_004D5AF0; i++) {
        if (m < D_004D59F0[i]) m = D_004D59F0[i];
    }
    *out = D_004D5AF0;
    return m;
}

typedef struct { u8 pad[6]; u16 v; u8 pad8[8]; } W29Ent;
typedef struct { u16 n; u8 pad[0xe]; W29Ent e[1]; } W29Tbl;
typedef struct { u8 pad[0x88]; u16 x88; u8 pad8a[0x16]; W29Tbl *xa0; } W29Mdl;
typedef struct { s32 a, b; } W29Pair;
typedef struct { s32 x0, x4; } W29Cnt;
extern W29Pair *D_004D5AF4;

void func_0010f258(W29Cnt *c, W29Mdl *m) {
    s32 idx[32];
    W29Tbl *t;
    s32 i, k;
    u16 id;
    k = 0;
    t = m->xa0;
    c->x0--;
    c->x4--;
    id = m->x88;
    for (i = 0; i < t->n - 1; i++) {
        if (t->e[i].v != t->e[i + 1].v) idx[k++] = i;
    }
    idx[k++] = t->n - 1;
    D_004D5AF4 = func_00121e28(k * 8, &D_004D5AF4);
    for (i = 0; i < k; i++) {
        s32 j = idx[i];
        D_004D5AF4[i].a = id;
        D_004D5AF4[i].b = ((W29Ent *)t)[j + 1].v;
    }
}

typedef struct { u64 d[14]; } W29S70;
extern s32 D_004D9240;
extern W29S70 D_002C5AD0[2];
extern W29S70 D_002BCA00[2];
s32 func_0010f8a0(void);
void func_0011f668(void);
void func_001ba4a8(void);

void func_0010fd40(void) {
    s32 i;
    func_0010f8a0();
    if (D_004D9240) {
        for (i = 0; i < 2; i++) D_002C5AD0[i] = D_002BCA00[i];
    }
    func_0011f668();
    for (i = 0; i < 2; i++) D_002BCA00[i] = D_002C5AD0[i];
    if (D_004D9240) func_001ba4a8();
}

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct { u64 d, a; } W29Ad;
typedef struct {
    union {
        u128 q;
        struct {
            u64 nloop : 15;
            u64 eop : 1;
            u64 pad16 : 16;
            u64 id : 14;
            u64 pre : 1;
            u64 prim : 11;
            u64 flg : 2;
            u64 nreg : 4;
            u64 regs : 4;
            u64 regs_hi : 60;
        } b;
    } tag;
    W29Ad r[31];
} W29Env;
W29Env D_004D8EF0 ALIGNED(16);
extern u64 D_002BC750[];
extern u64 D_002BC7C0[];
extern u64 D_002BC830[];
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void sceGsPutDrawEnv(void *);

void func_001100a8(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        D_004D8EF0.r[i].d = D_002BC830[i];
        D_004D8EF0.r[i].a = D_002BC750[i];
        D_004D8EF0.r[i + 13].d = D_002BC830[i];
        D_004D8EF0.r[i + 13].a = D_002BC7C0[i];
    }
    D_004D8EF0.tag.q = 0;
    D_004D8EF0.tag.b.nloop = 31;
    D_004D8EF0.tag.b.eop = 1;
    D_004D8EF0.tag.b.nreg = 1;
    D_004D8EF0.tag.b.regs = 0xe;
    D_004D8EF0.r[26].d = 1;
    D_004D8EF0.r[26].a = 0x1a;
    D_004D8EF0.r[27].d = 1;
    D_004D8EF0.r[27].a = 0x46;
    D_004D8EF0.r[28].d = 0;
    D_004D8EF0.r[28].a = 0x45;
    D_004D8EF0.r[29].d = 0;
    D_004D8EF0.r[29].a = 0x49;
    D_004D8EF0.r[30].d = -4;
    D_004D8EF0.r[30].a = 0x44;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsPutDrawEnv(&D_004D8EF0);
}

extern s32 D_002BBE04, D_002BBE14, D_002BBE18, D_002A6208, D_002A61F4, D_002BC738, D_002A6204, D_002A61F0;
extern s32 D_002BC060[4];
extern s32 D_002BC080[4];
extern s32 D_002BC0B0[4];
void func_00110360(void);

void func_001103a0(void) {
    D_002BBE04 = 0;
    D_002BBE14 = 0;
    D_002BBE18 = 0;
    D_002A6208 = 0;
    D_002A61F4 = 0;
    D_002BC738 = 0;
    D_002A6204 = 0;
    D_002A61F0 = 0;
    D_002BC060[0] = D_002BC060[1] = D_002BC060[2] = 0;
    D_002BC060[3] = 0x80;
    D_002BC080[0] = D_002BC080[1] = D_002BC080[2] = 0x80;
    D_002BC080[3] = 0x60;
    D_002BC0B0[0] = D_002BC0B0[1] = D_002BC0B0[2] = 0xFF;
    D_002BC0B0[3] = 0;
    func_00110360();
}

extern volatile s32 D_004D90F4;
extern f32 D_002BBDEC;
extern f32 D_002BBDFC;
extern f32 D_002BBE00;
extern s32 D_002BBE0C;
extern s32 D_002BBE10;
extern s32 D_002BC740;
void func_0010c348(void);

void func_001104e0(void) {
    s32 i;
    func_0010c348();
    D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
    if (D_004D90F4 < D_002BBE0C + 1) {
        for (i = 0; i < D_002BBE0C; i++) {
            func_0010c348();
            D_002BBDFC = (f32)D_004D90F4 * D_002BBDEC;
        }
    }
    if (D_002BBE10) D_002BBDFC = D_002BBDEC + D_002BBDEC;
    D_002BBDFC = D_002BBDFC * D_002BBE00;
    if (D_002BC740 != 1) {
        if (D_002BBDFC > 5.0f) D_002BBDFC = 5.0f;
    } else {
        D_002BBDFC = 128.0f;
    }
    D_004D90F4 = 0;
}

typedef struct { u8 x0; u8 w; u8 d[1]; } W29Map;
extern s32 D_002BBD90[];
extern W29Map *D_002BBD48[];
void func_00111600(s32, s32, u8);

void func_001116b0(s32 id, s32 row) {
    W29Map *m;
    u8 *hdr, *r;
    s32 i;
    if (D_002BBD90[id] == 0) return;
    m = D_002BBD48[id];
    hdr = m->d;
    r = hdr + m->w * (row + 1);
    for (i = 0; i < m->w; i++) {
        if (r[i] != '#') func_00111600(id, hdr[i] - 1, r[i] - 'a');
    }
}

u32 func_00111b08(u32);

u32 func_00111be8(u32 a) {
    u32 t, h, m, s;
    t = func_00111b08(a);
    h = t / 216000;
    t = t % 216000;
    m = t / 3600;
    t = t % 3600;
    s = t / 60;
    t = t % 60;
    {
        f32 r = (f32)t;
        r *= 1.6666667f;
        return (u32)r;
    }
}

extern s32 D_004D925C;
extern s32 D_002BCC1C;
extern s32 D_004D9254;
extern volatile u32 D_002BBDF0;
extern u32 D_004D9250;

s32 func_00111cb8(void) {
    switch (D_004D925C) {
    case 2:
        return 4;
    case 0:
        if (D_002BCC1C < D_004D9254) {
            D_002BCC1C = (f32)(D_002BBDF0 - D_004D9250) * D_002BBDEC;
            return 0;
        }
        D_002BCC1C = D_004D9254;
        return 4;
    case 1:
        return 0;
    }
    return 0;
}

extern void (*D_004D9258)(void);

s32 func_00111e00(void) {
    switch (D_004D925C) {
    case 2:
        return 4;
    case 0:
        if (D_002BCC1C > 0) {
            D_002BCC1C = (f32)D_004D9254 - (f32)(D_002BBDF0 - D_004D9250) * D_002BBDEC;
            return 0;
        }
        D_002BCC1C = 0;
        D_004D9258();
        return 4;
    case 1:
        return 0;
    }
    return 0;
}

typedef struct { s32 f, s, m, h; } W29Time;
typedef struct {
    s32 x0, x4, x8, xc, x10, x14, x18, x1c, x20, x24, x28, x2c, x30;
    W29Time t[2];
} W29Clock;
extern W29Clock D_004D9288;
s32 func_00111b10(s32);
s32 func_00111b48(s32);
s32 func_00111b90(s32);

void func_00112018(s32 which, s32 t) {
    s32 h, m, s, f;
    if (t < 0) t = 0;
    h = func_00111b10(t);
    m = func_00111b48(t);
    s = func_00111b90(t);
    f = func_00111be8(t);
    if (which == 0) {
        D_004D9288.t[0].f = f;
        D_004D9288.t[0].s = s;
        D_004D9288.t[0].m = m;
        D_004D9288.t[0].h = h;
    } else {
        D_004D9288.t[1].f = f;
        D_004D9288.t[1].s = s;
        D_004D9288.t[1].m = m;
        D_004D9288.t[1].h = h;
    }
}

extern s32 D_002BCC20;
extern s32 D_004D9260;
extern s32 D_004D9274;
extern s32 D_004D9280;
void func_002485b8(W29Clock *);
void func_001120c8(void);
void func_0011ef10(s32, void (*)(void));

void func_00112150(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7, s32 s0, s32 s8) {
    D_004D9288.x20 = a1;
    D_004D9288.x0 = a0;
    D_004D9260 = a4;
    D_004D9288.x30 = a2;
    D_004D9288.x4 = a3;
    D_004D9288.x18 = a5;
    D_004D9288.xc = a6;
    D_004D9288.x8 = s8;
    D_004D9288.x24 = s0;
    D_004D9288.x1c = D_002BCC20;
    D_004D9288.x28 = 0;
    func_00112018(0, D_002BCC1C);
    func_00112018(1, D_004D9260);
    D_004D9288.x2c = a7;
    D_004D9288.x10 = D_002BCC20;
    D_004D9288.x14 = D_004D9274;
    func_002485b8(&D_004D9288);
    D_004D9280 = 0;
    func_0011ef10(0x280A0, func_001120c8);
}

extern s32 D_002BCDB4, D_002BCDB8, D_002BCDBC, D_002BCDC0, D_002BCDC4, D_002BCDD8;
extern void *D_004D92DC;
extern u8 D_009A0000[];
extern u8 D_002BCCA0[];
extern s32 D_002BC138;
extern s32 D_002BC128;
void func_00112320(void);
void func_00176170(void);
void func_001761b0(void);
void func_001124f8(void);
void func_00112928(void);
void func_00112820(void);
void func_00112968(void);
void func_00120748(void *, void *, void (*)(void), s32);

s32 func_001129c8(void) {
    if (D_002BCDBC == 1 && D_002BCDC0 == 0) return 0;
    func_00112320();
    D_002BCDB4 = 0;
    D_002BCDB8 = 0;
    D_002BCDC4 = 1;
    D_004D92DC = D_009A0000;
    func_00176170();
    func_001761b0();
    if (D_002BC138 == D_002BC128) D_002BCDB4 = 1;
    if (D_002BCDB4 == 1) {
        func_001124f8();
        if (D_002BCDD8) func_00112928();
        else func_00112820();
    } else {
        func_00120748(D_002BCCA0, D_004D92DC, func_00112968, 0);
    }
    return 4;
}

typedef struct { u32 lo:13; u32 b13:1; u32 hi:18; } W29Flg;
typedef struct { s32 x0; u8 pad[0x3c]; } W29Rec40;
extern W29Flg D_002C5958;
extern W29Rec40 *D_002BCDA0;
extern W29Rec40 *D_002BCDAC;
extern s32 D_002BC13C;
extern void *D_002A3F3C;
extern char D_002BCCE0[];
extern char D_0048D008[];
void func_00112400(s32);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void *func_001559f0(s32, s32);
void *func_001137c8(void *, s32);
void func_00112c08(void);

void func_00112c20(s32 i) {
    char buf[64];
    s32 id;
    if (D_002C5958.b13 == 1) return;
    id = D_002BCDAC[D_002BCDA0[i].x0].x0;
    if (D_002BC13C == id) return;
    D_002BCDBC = 1;
    func_00112400(id);
    strcpy(buf, D_002BCCE0);
    strcat(buf, D_0048D008);
    D_002A3F3C = func_001559f0(0x34, 8);
    D_002A3F3C = func_001137c8(D_002A3F3C, 0x80);
    func_00120748(buf, D_002A3F3C, func_00112c08, 0);
}

typedef struct { s32 a, b; } W29P8;
typedef struct { W29P8 p; u8 pad[0x88]; } W29Cell;
extern const W29P8 D_0048BFD0;
extern W29Cell D_004DBC20[2][64];
typedef struct { u8 b[0x50]; } W29E50;
W29E50 D_004D9380[2] ALIGNED(64);
W29E50 D_004D9420[0x40][2] ALIGNED(32);
void func_00114c18(void *, s32, s32);

void func_00114e50(void) {
    s32 i, j;
    for (i = 0; i < 64; i++) {
        for (j = 0; j < 2; j++) {
            D_004DBC20[j][i].p.a = D_0048BFD0.a;
            D_004DBC20[j][i].p.b = D_0048BFD0.b;
        }
    }
    func_00114c18(D_004D9380, -1, 2);
    for (j = 0; j < 64; j++) func_00114c18(&D_004D9420[j], j, 2);
}

typedef struct { u8 pad[0x10]; void *x10; } W29Task;
typedef struct { s32 x0; u8 pad[8]; u32 b0:1; u32 rest:31; } W29E10;
extern s32 D_00351BD0;
extern W29E10 D_003044D8[];
void func_00108d90(void);
W29Task *func_0015ed80(void *, void (*)(void));
void func_00114db0(s32, s32);

void func_00114f50(void *a, s32 i) {
    if (i == -1) {
        func_0015ed80(a, func_00108d90)->x10 = &D_004D9380[D_00351BD0];
        return;
    }
    func_00114db0(i, D_003044D8[i].x0);
    func_0015ed80(a, func_00108d90)->x10 = &D_004D9420[i][D_00351BD0];
}

static inline f32 w29_dot(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

static inline void w29_scale(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyz $vf4xyz, $vf4xyz, $vf5x\n"
        "sqc2 $vf4, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

static inline void w29_add(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vadd.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

s32 func_00115200(void *p0, void *dir, void *p1, void *n, void *out) {
    f32 den, t;
    den = w29_dot(n, dir);
    if (den >= 0.0f) return 0;
    t = (w29_dot(n, p1) - w29_dot(n, p0)) / den;
    if (t > 1.0f) return 0;
    w29_scale(out, dir, t);
    w29_add(out, out, p0);
    return 1;
}

typedef struct { f32 v[4]; } __attribute__((aligned(16))) W29V4;
void func_00104f10(void *, W29V4 *);
void func_00104eb0(void *, W29V4 *);

s32 func_001152c8(void *obj, void *p0, void *dir, void *out) {
    W29V4 nrm, pt;
    f32 den, t;
    func_00104f10(obj, &nrm);
    den = w29_dot(&nrm, dir);
    if (den >= 0.0f) return 0;
    func_00104eb0(obj, &pt);
    t = (w29_dot(&nrm, &pt) - w29_dot(&nrm, p0)) / den;
    if (t < 0.0f) return 0;
    if (t > 1.0f) return 0;
    w29_scale(out, dir, t);
    w29_add(out, out, p0);
    return 1;
}

static inline void w29_sub(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void w29_outer(void *d, void *a, void *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4, $vf5\n"
        "vopmsub.xyz $vf6, $vf5, $vf4\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

extern s32 D_002BD150[];
extern s32 D_002BD160[];
s32 func_00104ae0(void *, W29V4 *);

s32 func_00115600(void *obj, void *p) {
    W29V4 e, d, c, v[4];
    s32 n, i, *idx;
    n = func_00104ae0(obj, v);
    if (n == 3) idx = D_002BD150;
    else idx = D_002BD160;
    for (i = 0; i < n; i++) {
        w29_sub(&e, &v[idx[i]], &v[i]);
        w29_sub(&d, p, &v[i]);
        w29_outer(&c, &e, &d);
        if (c.v[1] < 0.0f) return 0;
    }
    return 1;
}

typedef struct { s32 f; u8 pad[12]; } W29Mark;
typedef struct { u8 hdr[8]; W29Mark e[1]; } W29MarkTbl;
extern W29MarkTbl *D_004E0420;
extern s32 D_004E0428[];
extern u16 **D_002A623C;
extern s32 D_002BD170;
s32 func_00104940(void *, s32 *, s32);

s32 func_00115d58(void *a) {
    s32 buf[1024];
    s32 n, i, j, k, cnt;
    u16 *l;
    n = func_00104940(a, buf, 1024);
    if (n == -1) return D_002BD170;
    cnt = 0;
    for (i = 0; i < n; i++) {
        l = D_002A623C[buf[i]];
        if (l == (u16 *)-1) continue;
        k = l[0];
        for (j = 0; j < k; j++) {
            u16 id = l[j + 1];
            if (D_004E0420->e[id].f == 0) {
                D_004E0420->e[id].f = 1;
                D_004E0428[cnt++] = id;
            }
        }
    }
    for (k = 0; k < cnt; k++) D_004E0420->e[D_004E0428[k]].f = 0;
    D_002BD170 = cnt;
    return cnt;
}

static inline void w29_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}

extern W29V4 D_002BD1E0;

s32 func_00118db0(void *p, W29V4 *v) {
    W29V4 c, prev, e[4];
    s32 i;
    s32 *idx = D_002BD160;
    for (i = 0; i < 4; i++) w29_sub(&e[i], &v[i], p);
    w29_copy(&prev, &D_002BD1E0);
    for (i = 0; i < 4; i++) {
        w29_outer(&c, &e[i], &e[idx[i]]);
        if (w29_dot(&prev, &c) < 0.0f) return 0;
        w29_copy(&prev, &c);
    }
    return 1;
}

typedef struct { f32 mn[3]; f32 mx[3]; } W29Box;
void func_00267518(W29V4 *, W29V4 *, W29V4 *);

void func_001195d8(W29V4 *a, W29Box *b) {
    W29V4 t;
    func_00267518(&t, a, a + 1);
    {
        f32 p, q; q = t.v[0]; p = a->v[0];
        if (q > p) { b->mn[0] = p; b->mx[0] = q; }
        else { b->mx[0] = p; b->mn[0] = q; }
    }
    {
        f32 p, q; q = t.v[1]; p = a->v[1];
        if (q > p) { b->mn[1] = p; b->mx[1] = q; }
        else { b->mx[1] = p; b->mn[1] = q; }
    }
    {
        f32 p = a->v[2], q = t.v[2];
        if (p < q) { b->mn[2] = p; b->mx[2] = q; }
        else { b->mx[2] = p; b->mn[2] = q; }
    }
}

static inline void w29_scale4(void *d, void *s, f32 t) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lw $8, 0(%2)\n"
        "qmtc2 $8, $vf5\n"
        "vmulx.xyzw $vf6xyzw, $vf4xyzw, $vf5x\n"
        "sqc2 $vf6, 0(%0)\n"
        : : "r"(d), "r"(s), "r"(&t) : "$8", "memory");
}

typedef struct { f32 n[3]; f32 d; s32 x10; } W29Plane;
extern W29Plane *D_002A6238;
s32 func_001198c8(s32, s32, void *);

s32 func_00119fc0(s32 i, void *n, void *p, void *out, f32 *maxd) {
    W29V4 t;
    f32 d;
    d = w29_dot(p, n) + D_002A6238[i].d;
    if (*maxd < d) return 0;
    w29_scale4(&t, n, d);
    w29_sub(out, p, &t);
    return func_001198c8(-1, i, out) != 0;
}

extern s32 D_003044D0;
extern u8 D_002BF250[];
typedef struct { u32 h; s32 i; void *p; } W29Lnk;
typedef struct { u8 pad[0x18]; u16 x18; u8 pad1a[2]; s32 x1c; W29Lnk l[1]; } W29Grp;
s32 func_0011a728(W29Grp *, s32);
void func_0011a410(s32);
void *func_0011af48(s32, W29Grp *, s32, void *);

void func_0011b108(W29Grp *g, s32 k) {
    void *prev = D_002BF250;
    s32 i;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].b0 != 1 && func_0011a728(g, i)) {
            void *r;
            func_0011a410(i);
            r = func_0011af48(i, g, 1, prev);
            if (g->x18 != 0) {
                g->x1c++;
                g->l[k].h = g->x18;
                g->l[k].i = i;
                g->l[k].p = prev;
                k++;
            }
            prev = r;
        }
    }
}

/* needs make: uses rodata */
typedef struct { u8 pad[0x158]; s32 x158; } W29Ply;
extern W29Ply *D_002BCB60;
void func_0013c7d8(s32);

void func_001119d0(void) {
    switch (D_002BC128) {
    case 5:
        if (D_002BCB60->x158 & 0x8) func_0013c7d8(3);
        break;
    case 8:
        if (D_002BCB60->x158 & 0x20) func_0013c7d8(5);
        break;
    case 9:
        if (D_002BCB60->x158 & 0x40) func_0013c7d8(6);
        break;
    case 10:
        if (D_002BCB60->x158 & 0x80) func_0013c7d8(7);
        break;
    case 13:
        if (D_002BCB60->x158 & 0x100) func_0013c7d8(8);
        break;
    case 15:
        if (D_002BCB60->x158 & 0x200) func_0013c7d8(9);
        break;
    }
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
s32 D_002BD170 ALIGNED(16) = 0;
