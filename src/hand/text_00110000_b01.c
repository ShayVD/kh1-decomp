#include "common.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_b01.h"
typedef struct { u8 pad[0x10]; V4_01 x10; } Obj01;
typedef struct { u32 b0:1; u32 p1:3; u32 k:4; u32 p8:9; u32 b17:1; u32 p18:11; u32 b29:1; u32 p30:2; } Bits01;
#include "data/types/text_00110000_b01_p2.h"
#include "data/pieces/D_002C1260.h"
extern s32 D_002C12C4;
#include "data/pieces/D_002BD250.h"
extern s32 D_004E0428[];
#include "data/types/text_00110000_b01_p.h"
#include "data/pieces/D_002A6244.h"
#include "data/pieces/D_002A6238.h"
typedef struct { u8 pad[0x18]; s16 cnt; } Qry01;
s32 func_00115d58(Qry01 *);
void func_001158c8(Qry01 *);
void func_00115940(s32);

static inline s32 ov01(f32 *mn, f32 *mx) {
    if (mn[0] <= D_002C1260.mx[0][0] && D_002C1260.mn[0][0] <= mx[0] && D_002C1260.mx[1][0] >= mn[1] &&
        D_002C1260.mn[1][0] <= mx[1] && D_002C1260.mx[2][0] >= mn[2] && D_002C1260.mn[2][0] <= mx[2]) return 1;
    return 0;
}
static inline s32 in01(f32 *mn, f32 *mx) {
    if (D_002C1260.mn[0][0] < mn[0] && D_002C1260.mx[0][0] > mx[0] && D_002C1260.mn[1][0] < mn[1] &&
        D_002C1260.mx[1][0] > mx[1] && D_002C1260.mn[2][0] < mn[2] && D_002C1260.mx[2][0] > mx[2]) return 1;
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
                    f = &D_002A6238[id].f.w;
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
                    f = &D_002A6238[id].f.w;
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
                f = &D_002A6238[id].f.w;
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
                f = &D_002A6238[id].f.w;
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
#include "data/pieces/D_002BBDE0.h"
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

/* 0x126c10 (needs func_00125dc8 defined above) */
#define FLD(T, p, off) (*(T *)((u8 *)(p) + (off)))
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
