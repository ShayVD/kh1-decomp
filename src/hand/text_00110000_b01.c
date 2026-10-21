#include "common.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_b01.h"
typedef struct { u8 pad[0x10]; V4_01 x10; } Obj01;
typedef struct { u32 b0:1; u32 p1:3; u32 k:4; u32 p8:9; u32 b17:1; u32 p18:11; u32 b29:1; u32 p30:2; } Bits01;
typedef struct { f32 minx, p0[3], miny, p1[3], minz, p2[3], maxx, p3[3], maxy, p4[3], maxz, p5[3]; } Box01;
extern Box01 D_002C1260;
extern s32 D_002C12C4;
extern s32 D_002BD250[];
extern s32 D_004E0428[];
typedef struct { f32 mn[3]; f32 mx[3]; u16 n; u16 ids[1]; } Node01;
extern Node01 **D_002A6244;
typedef struct { u32 a, b, c, d; u32 f; } Tri01;
extern Tri01 *D_002A6238;
typedef struct { u8 pad[0x18]; s16 cnt; } Qry01;
s32 func_00115d58(Qry01 *);
void func_001158c8(Qry01 *);
void func_00115940(s32);

static inline s32 ov01(f32 *mn, f32 *mx) {
    if (mn[0] <= D_002C1260.maxx && D_002C1260.minx <= mx[0] && D_002C1260.maxy >= mn[1] &&
        D_002C1260.miny <= mx[1] && D_002C1260.maxz >= mn[2] && D_002C1260.minz <= mx[2]) return 1;
    return 0;
}
static inline s32 in01(f32 *mn, f32 *mx) {
    if (D_002C1260.minx < mn[0] && D_002C1260.maxx > mx[0] && D_002C1260.miny < mn[1] &&
        D_002C1260.maxy > mx[1] && D_002C1260.minz < mn[2] && D_002C1260.maxz > mx[2]) return 1;
    return 0;
}

void func_00117db0(Qry01 *q) {
    s32 n, i, j;
    Node01 *e;
    u16 *p;
    s32 id;
    s32 *ip;
    D_002C12C4 = 0;
    n = func_00115d58(q);
    ip = D_004E0428;
    func_001158c8(q);
    for (i = 0; i < n; i++) {
        e = D_002A6244[*ip++];
        if (ov01(e->mn, e->mx)) {
            if (in01(e->mn, e->mx)) {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f;
                    if (!(*f & 1)) {
                        D_002BD250[D_002C12C4] = id;
                        D_002C12C4++;
                    }
                }
            } else {
                p = e->ids;
                for (j = 0; j < e->n; j++) {
                    u32 *f;
                    id = *p++;
                    f = &D_002A6238[id].f;
                    if (!(*f & 1)) func_00115940(id);
                }
            }
        }
    }
    q->cnt = D_002C12C4;
}

/* needs make: uses rodata */
extern V4_01 D_002BD1F0[];
s32 func_00115200(Obj01 *, f32 *, V4_01 *, f32 *, f32 *);
s32 func_00118db0(f32 *, V4_01 *);

static inline f32 dot01(f32 *a, f32 *b) {
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

s32 func_00118ea0(Obj01 *id, f32 *n, f32 *mn, f32 *mx, s32 k) {
    V4_01 t[4];
    V4_01 out;
    s32 i;
    if (k < 6) return 1;
    t[0][3] = t[1][3] = t[2][3] = t[3][3] = 1.0f;
    for (i = 0; i < 6; i++) {
        if (dot01(D_002BD1F0[i], n) >= 0.0f) continue;
        switch (i) {
        case 0:
            t[0][0] = mn[0]; t[0][1] = mn[1]; t[0][2] = mx[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mn[0]; t[3][1] = mn[1]; t[3][2] = mn[2];
            break;
        case 1:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mn[0]; t[1][1] = mx[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mx[1]; t[2][2] = mn[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 2:
            t[0][0] = mn[0]; t[0][1] = mx[1]; t[0][2] = mn[2];
            t[1][0] = mn[0]; t[1][1] = mn[1]; t[1][2] = mn[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 3:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mn[1]; t[2][2] = mx[2];
            t[3][0] = mn[0]; t[3][1] = mx[1]; t[3][2] = mx[2];
            break;
        case 4:
            t[0][0] = mn[0]; t[0][1] = mx[1]; t[0][2] = mx[2];
            t[1][0] = mn[0]; t[1][1] = mn[1]; t[1][2] = mx[2];
            t[2][0] = mn[0]; t[2][1] = mn[1]; t[2][2] = mn[2];
            t[3][0] = mn[0]; t[3][1] = mx[1]; t[3][2] = mn[2];
            break;
        case 5:
            t[0][0] = mx[0]; t[0][1] = mx[1]; t[0][2] = mn[2];
            t[1][0] = mx[0]; t[1][1] = mn[1]; t[1][2] = mn[2];
            t[2][0] = mx[0]; t[2][1] = mn[1]; t[2][2] = mx[2];
            t[3][0] = mx[0]; t[3][1] = mx[1]; t[3][2] = mx[2];
            break;
        }
        if (func_00115200(id, n, t, D_002BD1F0[i], out) && func_00118db0(out, t)) return 1;
    }
    return 0;
}

s32 func_00119128(s32, Obj01 *, f32 *);
s32 func_001151a8(s32, f32 *);

s32 func_001191c8(Qry01 *q, Obj01 *o, s32 mode) {
    s32 i;
    s32 *ip;
    s32 n, j;
    Node01 *e;
    u16 *p;
    s32 id;
    u32 w;
    u32 *f;
    s32 c;
    D_002C12C4 = 0;
    n = func_00115d58(q);
    ip = D_004E0428;
    func_001158c8(q);
    for (i = 0; i < n; i++) {
        e = D_002A6244[*ip++];
        if (!ov01(e->mn, e->mx)) continue;
        if (in01(e->mn, e->mx)) {
            if (!func_00118ea0(o, o->x10, e->mn, e->mx, e->n)) continue;
            p = e->ids;
            for (j = 0; j < e->n; j++) {
                s32 k;
                id = *p++;
                f = &D_002A6238[id].f;
                w = *f;
                if (w & 1) continue;
                if (mode != 8) {
                    if (mode != 11) continue;
                    if (((Bits01 *)f)->b29 == 1) continue;
                }
                k = (w >> 4) & 0xf;
                if (k == 7) continue;
                if (k == 9) continue;
                if ((w >> 17) & 1) continue;
                if (k == 5) continue;
                if (func_00119128(id, o, o->x10)) return 1;
            }
        } else {
            if (!func_00118ea0(o, o->x10, e->mn, e->mx, e->n)) continue;
            p = e->ids;
            for (j = 0; j < e->n; j++) {
                s32 k;
                id = *p++;
                f = &D_002A6238[id].f;
                w = *f;
                if (w & 1) continue;
                if (mode != 8) {
                    if (mode != 11) continue;
                    if (((Bits01 *)f)->b29 == 1) continue;
                }
                k = (w >> 4) & 0xf;
                if (k == 7) continue;
                if (k == 9) continue;
                if ((w >> 17) & 1) continue;
                if (k == 5) continue;
                if (func_001151a8(id, o->x10)) {
                    c = D_002C12C4;
                    func_00115940(id);
                    if (D_002C12C4 != c && func_00119128(id, o, o->x10)) return 1;
                }
            }
        }
    }
    return -1;
}

/* needs make: uses rodata */
typedef struct { s32 id; f32 *pos; s32 x8, handle, x10; u8 active, on, kind, x17; } Snd01;
extern volatile s32 D_002BBDE0;
extern s32 D_002C1370;
extern s32 D_003F34A4;
extern s32 D_002C1360;
extern s32 D_002C1384;
extern V4_01 D_004E3A20; /* src/data/bss_004E.c: V4 D_004E3A20 */
extern V4_01 D_004E3A30; /* src/data/bss_004E.c: V4 D_004E3A30 */
s32 func_00104f10(f32 *, V4_01);
s32 func_00119fc0(f32 *, V4_01, V4_01, V4_01, f32 *);
s32 func_00119ad8(s32, f32 *, V4_01, V4_01, V4_01, f32 *);

static inline f32 vd01(void *a, void *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

void func_0011d7e0(Snd01 *e, s32 *a, s32 *b) {
    V4_01 hit;
    V4_01 n;
    f32 md;
    V4_01 unused;
    f32 *t;
    f32 *p;
    f32 s, d;
    if (e->x8 == 0x3fff) return;
    if ((D_002BBDE0 == 5 || D_002BBDE0 == 7) && D_002C1370) {
        *a = 0x3fff;
        *b = 0x3fff;
        return;
    }
    if (D_003F34A4) {
        *a = 0;
        *b = 0;
        return;
    }
    p = e->pos;
    s = 0.0f;
    switch (e->kind) {
    case 0:
        s = D_002C1360;
        break;
    case 1:
    case 2:
    case 4:
        s = D_002C1384;
        break;
    case 3:
        md = 5000.0f;
        func_00104f10(p, n);
        t = D_004E3A20;
        s = 50.0f;
        if (func_00119fc0(p, n, t, hit, &md) || func_00119ad8(-1, p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *a = 16383.0f - d * d / s;
        } else {
            *a = 0;
        }
        t = D_004E3A30;
        if (func_00119fc0(p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *b = 16383.0f - d * d / s;
        } else if (func_00119ad8(-1, p, n, t, hit, &md)) {
            d = vd01(t, hit);
            *b = 16383.0f - d * d / s;
        } else {
            *b = 0;
        }
        return;
    }
    d = vd01(D_004E3A20, p);
    *a = 16383.0f - d * d / s;
    d = vd01(D_004E3A30, p);
    *b = 16383.0f - d * d / s;
}

/* needs make: uses rodata */
typedef struct { s32 x0, x4, x8; } Sl01;
typedef struct { s32 a, b; } Pr01;
extern s32 D_004E3A18;
extern s32 D_004E3A1C;
extern s32 D_004E3A40;
extern Pr01 D_004E39F8[]; /* src/data/bss_004E.c: Pair D_004E39F8[0x4] */
extern Sl01 *D_004E3454; /* src/data/bss_004E.c: Slot12 *D_004E3454 */
extern s32 D_004E344C;
extern Snd01 *D_004E3450; /* src/data/bss_004E.c: SndSlot *D_004E3450 */
void func_0011dc28(Snd01 *, s32 *, s32 *);
void func_0011dba0(s32 *, s32 *, s32, s32);
void func_0011dc98(Snd01 *);
void func_0011c838(s32, s32, s32, s32, s32);
void func_0011c880(s32, s32, s32, s32, s32);
void func_0011c850(s32, s32, s32);
void func_0011e248(s32);
void func_0011e368(s32, s32);
void func_0011ddd0(void);
void func_001edba0(void);

void func_0011de90(void) {
    s32 l, r;
    s32 i;
    Sl01 *sl;
    Snd01 *s;
    sl = D_004E3454;
    D_004E3A18 = 0;
    for (i = 0; i < 4; i++) {
        if (D_004E39F8[i].b) {
            D_004E3A18 = 1;
            D_004E39F8[i].b--;
        }
    }
    D_004E3A1C = 0;
    for (i = 0; i < D_004E344C; i++, sl++) {
        if (sl->x8) {
            sl->x8--;
            D_004E3A1C = 1;
        }
    }
    func_0011e248(0);
    func_0011e368(-1, -1);
    func_0011ddd0();
    s = D_004E3450;
    for (i = 0; i < D_004E344C; i++, s++) {
        switch (s->active) {
        case 0:
            break;
        case 1:
            func_0011d7e0(s, &l, &r);
            func_0011dc28(s, &l, &r);
            func_0011dba0(&l, &r, s->x8, s->kind);
            func_0011c838(s->handle, s->id, s->x10, l, r);
            s->active = 3;
            func_0011dc98(s);
            break;
        case 2:
            if (D_004E3A40 == 0) {
                func_0011d7e0(s, &l, &r);
                func_0011dba0(&l, &r, s->x8, s->kind);
                if (l || r) {
                    func_0011c838(s->handle, s->id, s->x10, l, r);
                    s->on = 1;
                }
                s->active = 4;
            }
            break;
        case 3:
            func_0011d7e0(s, &l, &r);
            func_0011dba0(&l, &r, s->x8, s->kind);
            func_0011c880(s->handle, s->id, s->x10, l, r);
            break;
        case 4:
            if (D_004E3A40 == 0) {
                func_0011d7e0(s, &l, &r);
                func_0011dba0(&l, &r, s->x8, s->kind);
                if (l == 0 && r == 0) {
                    s->on = 0;
                    func_0011c850(s->handle, s->id, s->x10);
                    break;
                }
                if (s->on == 0) {
                    func_0011c838(s->handle, s->id, s->x10, l, r);
                } else if (l != 0x3fff || r != 0x3fff) {
                    func_0011c880(s->handle, s->id, s->x10, l, r);
                }
                s->on = 1;
            } else {
                s->on = 0;
                func_0011c850(s->handle, s->id, s->x10);
            }
            break;
        }
    }
    func_001edba0();
}

/* needs make: uses rodata */
typedef struct { u8 pad[41]; u8 x29; } Sub14c;
typedef struct { u8 pad[0xcc]; f32 xcc; } Sub6c;
typedef struct { u8 pad[272]; V4_01 v; } Sub148;
typedef struct {
    u8 pad0[0x68];
    s32 x68;
    Sub6c *x6c;
    u8 pad70[0x148 - 0x70];
    Sub148 *x148;
    Sub14c *x14c;
    u8 pad150[0x3c0 - 0x150];
    V4_01 x3c0;
} Obj25;
typedef struct { u8 pad[8]; f32 x8; } Prm25;
typedef struct { s8 k, a, b; } Tr25;
Prm25 *func_0013dc10(Obj25 *, u32);
void func_00130578(Obj25 *, s32, f32);
void func_002673b8(f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002675a8(f32 *, f32 *);
void func_0014db78(Obj25 *, f32 *);
void func_00125cf0(Obj25 *, f32, f32);
void func_00121fc4(f32 *, f32 *);
void func_0014cce0(Obj25 *, f32);
void func_001376e8(Obj25 *, f32 *);
void func_001586a8(s32);
void func_00148a40(Obj25 *, s32);
void func_00148768(s32, s32, Obj25 *, s32, f32);

void func_00125dc8(Obj25 *o, u32 mode, f32 *v) {
    Tr25 tbl[5] = { { 3, 0, 1 }, { 4, 3, -1 }, { 5, 4, 5 }, { 7, 6, 7 }, { -1, -1, -1 } };
    Prm25 *pr;
    f32 sp;
    f32 z;
    s32 i;
    pr = func_0013dc10(o, mode);
    sp = pr->x8;
    switch (mode) {
    case 15:
    case 16:
    case 17:
    case 18:
        func_00130578(o, 0x40000006, 0.0f);
        func_002673b8(v, v);
        if (o->x14c->x29 == 1) {
            v[3] = 8.0f;
        } else if (mode - 15 < 2) {
            v[3] = 12.0f;
        } else {
            v[3] = 4.0f;
        }
        func_00267560(o->x3c0, v, v[3]);
        v[3] = 0.0f;
        break;
    case 2:
        v[3] = 8.0f;
        func_00130578(o, 0x40000006, 0.0f);
        o->x14c->x29 = 1;
        break;
    case 0:
    case 1:
        sp = v[1];
        func_00130578(o, 0x40000006, 0.0f);
        o->x14c->x29 = 1;
        break;
    case 19:
    case 20:
    case 21:
        o->x6c->xcc = 0.19634955f;
        sp = 0.0f;
        v[1] = sp;
        func_002673b8(v, v);
        v[3] = pr->x8;
        func_0014db78(o, v);
        func_00125cf0(o, 0.5f, 8.0f);
        func_00130578(o, 0x40000075, 16.0f);
        break;
    case 59:
        func_002675a8(v, o->x148->v);
        v[1] = 0.0f;
        func_00121fc4(v, v);
        func_00130578(o, 0x40000006, 0.0f);
        break;
    case 22:
    case 24:
    case 25:
    case 26:
        func_00125cf0(o, 0.2f, 8.0f);
    default:
        z = 0.0f;
        func_00130578(o, 0x40000000, z);
        v[3] = z;
        break;
    }
    if (sp > 0.0f) func_0014cce0(o, sp);
    func_001376e8(o, v);
    func_001586a8(19);
    for (i = 0; tbl[i].k >= 0; i++) {
        if (tbl[i].k == mode) {
            func_00148a40(o, tbl[i].a | 0x800);
            if (tbl[i].b >= 0) func_00148a40(o, tbl[i].b | 0x800);
            break;
        }
    }
    if (mode == 4) func_00148768(o->x68, 2, o, 48, 0.8f);
}

/* 0x126c10 (needs func_00125dc8 defined above) */
typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V53;
#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
typedef struct { s32 a, b; } P8;
typedef struct { u8 type; P8 p; } C3190;
extern C3190 D_002E3190;
void *memset(void *, s32, u32);
void func_0013ed88(u8 *, C3190 *, V53 *);
void func_0013ee40(u8 *, C3190 *, V53 *);
s32 func_00126360(u8 *, s32 *, V53 *);
s32 func_00126838(u8 *, s32 *, V53 *);
s32 func_001269d8(u8 *, s32 *, V53 *);
void func_00126ba0(u8 *, s32 *, V53 *);
s32 func_00125b68(u8 *);
void func_00125be8(u8 *, P8 *);
s32 func_0012f040(s32, s32);

void func_00126c10(u8 *o, V53 *v) {
    P8 s;
    u8 *p;
    func_0013ed88(o, &D_002E3190, v);
    switch (D_002E3190.type) {
    case 1:
        if (FLD(u32, o, 0x1cc) & 0x400000) {
            p = FLD(u8 *, o, 0x14c);
            if (FLD(s32, p, 0x30) == 0) break;
            FLD(u8, p, 0x29)++;
        } else {
            FLD(u8, FLD(u8 *, o, 0x14c), 0x29) = 1;
        }
        if (func_0012f040(D_002E3190.p.a, D_002E3190.p.b)) {
            s = D_002E3190.p;
        } else {
            s.a = 0;
            s.b = 0;
        }
        FLD(P8, FLD(u8 *, o, 0x14c), 0x34) = s;
        switch (FLD(s32, o, 0x70)) {
        case 0:
            func_00125dc8((Obj25 *)o, func_00126360(o, (s32 *)&s, v), (f32 *)v);
            break;
        case 2:
            func_00125dc8((Obj25 *)o, func_00126838(o, (s32 *)&s, v), (f32 *)v);
            break;
        case 8:
            func_00126ba0(o, (s32 *)&s, v);
            func_00125dc8((Obj25 *)o, func_00126838(o, (s32 *)&s, v) + 3, (f32 *)v);
            break;
        case 24:
            func_00126ba0(o, (s32 *)&s, v);
            func_00125dc8((Obj25 *)o, func_001269d8(o, (s32 *)&s, v), (f32 *)v);
            break;

        case 12:
            func_00125dc8((Obj25 *)o, 59, (f32 *)v);
            break;
        }
        break;
    case 3:
        func_0013ee40(o, &D_002E3190, v);
        break;
    case 2:
        if (func_00125b68(o)) {
            func_00125be8(o, &D_002E3190.p);
        } else {
            func_0013ee40(o, &D_002E3190, v);
        }
        break;
    case 99:
        FLD(u8, FLD(u8 *, o, 0x14c), 0x29)++;
        func_00125dc8((Obj25 *)o, 62, (f32 *)v);
        break;
    default:
        func_0013ee40(o, &D_002E3190, v);
        break;
    }
    memset(&D_002E3190, 0, 12);
}
#undef FLD


/* Split out of func_0011d7e0 / func_0011de90's old layout entries. */
void func_0011db50(s32 *a, s32 *b) {
    if (*a < 0) *a = 0;
    if (*b < 0) *b = 0;
    if (*a >= 0x4000) *a = 0x3fff;
    if (*b >= 0x4000) *b = 0x3fff;
}

void func_0011e1c8(s32 x) {
    s32 i;
    i = 0;
    do {
        if (D_004E39F8[i].a == 0) break;
        i++;
    } while (i < 4);
    D_004E39F8[i].a = x;
    D_004E39F8[i].b = 2;
}

#include "data/data_002C.h"
#include "data/data_003F.h"
#include "data/pieces/D_002BD1F0.h"
