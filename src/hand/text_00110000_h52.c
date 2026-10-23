#include "common.h"
#include "data/bss_004D.h"
typedef struct { u16 active; u8 x2, x3; u32 cur; union { u64 d; u32 w; } press; u64 rep; } Pad52;
extern Pad52 D_002C5AD0;
typedef struct { s32 min, max; void (*fn)(s32); } Range52;
typedef struct { s32 a, b; } Pair52;
extern s32 D_004D5AF8;
extern Pair52 *D_004D5AF4; /* src/data/bss_004D.c: s32 D_004D5AF4 */
extern s32 D_002BBBA0;
extern s32 D_002C5BB8;
void func_0011d768(s32);
void func_0010f0d0(s32, s32, s32);
void func_00121ee0(void *);

s32 func_0010f368(Range52 *r, s32 arg) {
    s32 old;
    if (D_002C5AD0.rep & 0x10100010) {
        old = D_004D5AF8;
        D_004D5AF8 = old - 1;
        if (D_004D5AF8 < r->min) {
            if (D_002C5AD0.press.d & 0x10100010) {
                D_004D5AF8 = r->max;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    } else if (D_002C5AD0.rep & 0x40400040) {
        old = D_004D5AF8;
        D_004D5AF8 = old + 1;
        if (r->max < D_004D5AF8) {
            if (D_002C5AD0.press.d & 0x40400040) {
                D_004D5AF8 = r->min;
                func_0011d768(1);
            } else {
                D_004D5AF8 = old;
            }
        } else {
            func_0011d768(1);
        }
    }
    if (!D_002BBBA0 && (D_002C5AD0.press.w & 0x4000)) {
        if (D_004D5AF8 != r->max) func_0011d768(3);
        D_004D5AF8 = r->max;
    }
    func_0010f0d0(D_004D5AF4[D_004D5AF8].a, D_004D5AF4[D_004D5AF8].b, arg);
    if (D_002C5BB8 & 1) {
        func_0011d768(2);
        r->fn(D_004D5AF8 + 1);
        func_00121ee0(D_004D5AF4);
        D_004D5AF4 = 0;
        return 1;
    }
    return 0;
}

extern s32 D_002BBDE8;
extern volatile s32 D_002BD114;
extern s32 D_002BCC24;
#include "data/pieces/D_002BBDF0.h"
#include "data/pieces/D_002BBDF4.h"
#include "data/pieces/D_002BBDF8.h"
extern volatile u32 D_004D90F0; /* src/data/bss_004D.c: volatile s32 D_004D90F0 */
extern volatile s32 D_004D90F4;
s32 func_00111798(void);
void func_001117b8(void);
void func_0010c378(void);

s32 func_00110218(void) {
    if (*(volatile u64 *)0x12001000 & 0x2000) {
        D_002BBDE8 = 1;
    } else {
        D_002BBDE8 = 0;
    }
    if (D_002BD114 == 0 && D_002BCC24 == 0) {
        D_002BBDF0++;
    }
    if (D_002BBDF4 < D_004D90F0) {
        D_002BBDF4 = D_002BBDF4 + 1;
    } else if (func_00111798() < 3) {
        if (D_002BBDF4 < D_004D90F0 + 60) {
            D_002BBDF4 = D_002BBDF4 + 1;
        } else {
            func_001117b8();
            D_002BBDF4 = 0;
        }
    } else {
        D_002BBDF4 = D_004D90F0;
    }
    D_002BBDF8++;
    D_004D90F4++;
    func_0010c378();
    return 0;
}

#include "data/types/text_00110000_h52.h"
#include "data/pieces/D_002BBF20.h"
#include "data/pieces/D_002BBEE0.h"
#include "data/pieces/D_002BBEA0.h"
#include "data/pieces/D_002BBE60.h"
#include "data/pieces/D_002BBE20.h"
#include "data/pieces/D_002BBF60.h"
extern Mtx52 D_004D8E40, D_004D9100, D_004D9140, D_004D9180, D_004D91C0, D_004D8E80;
extern f32 D_004D90F8;
void func_00110ce0(void);
void sceVu0CopyMatrix(void *, void *);
void func_00110618(void *, void *, void *, void *, void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32);

void func_00110a48(f32 x) {
    func_00110ce0();
    sceVu0CopyMatrix(D_004D8E40, D_002BBE20);
    sceVu0CopyMatrix(D_004D9100, D_002BBE60);
    sceVu0CopyMatrix(D_004D9140, D_002BBEA0);
    sceVu0CopyMatrix(D_004D9180, D_002BBEE0);
    sceVu0CopyMatrix(D_004D91C0, D_002BBF20);
    sceVu0CopyMatrix(D_004D8E80, D_002BBF60);
    func_00110618(D_002BBE20, D_002BBE60, D_002BBEA0, D_002BBEE0, D_002BBF20, D_002BBF60, x,
                  0.7999999523162842f, 0.839999854564666748046875f, 2048.0f, 2048.0f, 1.0f, 16777000.0f, 1.0f,
                  400000000.0f, D_004D90F8);
}

#include "data/pieces/D_002BD118.h"
extern s32 D_002BD11C;
#include "data/pieces/D_0037A378.h"
typedef Bits_37a378 Bits52;
extern s32 D_004D9320;
extern Bits52 D_002C5958;
extern s32 D_002C1308, D_002C130C;
#include "data/pieces/D_002BBDE0.h"
extern s32 D_002BC0BC, D_002A6204;
#include "data/pieces/D_002BC070.h"
s32 func_001336a0(void);

s32 func_001140a0(void) {
    s32 *p;
    if (D_004D9320 == 0) {
        p = &D_002BD118;
        *p = 0;
        if (D_002C5958.b0 == 1) *p = 2;
        if (D_002C5958.b4 == 1) *p = 2;
        if ((*(Bits_37a378 *)&D_0037A378).b1 == 1) *p = 1;
        if ((*(Bits_37a378 *)&D_0037A378).b3 == 1) *p = 3;
        if (D_002BD11C == 1) *p = D_002BD11C;
        if (D_002C1308) *p = 4;
        if (D_002C130C) *p = 5;
        if (D_002BBDE0 == 5) *p = 7;
        if (func_001336a0()) *p = 2;
        if (*p == 0) {
            if ((*(s32 *)&D_002BC070) != 128 || D_002BC0BC || D_002A6204) D_002BD118 = 1;
        }
    }
    return D_002BD118;
}

#include "data/types/text_00110000_h52_p.h"
typedef struct { V4i52 a; s32 x10; void *x14; s32 x18; s32 x1c; V4i52 x20; V4i52 x30; V4i52 x40; } Ent52;
#include "data/pieces/D_0048C630.h"
typedef Blk32_48c630 Tpl52;
typedef struct { u8 b[0x90]; } E90_52;
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_0048C6F0.h"
extern V4i52 D_00472150, D_00486300;
extern E90_52 D_004DBC20[2][64];

void func_00114c18(Ent52 *o, s32 idx, s32 col) {
    s32 i;
    if (idx == -1) {
        o[0].x14 = D_0048C630.x14;
        o[1].x14 = D_0048C690.x14;
    } else {
        o[0].x14 = &D_004DBC20[0][idx];
        o[1].x14 = &D_004DBC20[1][idx];
    }
    o[0].x10 = D_0048C630.x10;
    o[0].x18 = D_0048C630.x18;
    o[0].x1c = D_0048C630.x1c;
    o[1].x10 = D_0048C690.x10;
    o[1].x18 = D_0048C690.x18;
    o[1].x1c = D_0048C690.x1c;
    o[0].x20.v[0] = D_0048C630.x20.v[0];
    o[0].x20.v[1] = D_0048C630.x20.v[1];
    o[0].x20.v[2] = D_0048C630.x20.v[2];
    o[0].x20.v[3] = D_0048C630.x20.v[3];
    o[1].x20.v[0] = D_0048C690.x20.v[0];
    o[1].x20.v[1] = D_0048C690.x20.v[1];
    o[1].x20.v[2] = D_0048C690.x20.v[2];
    o[1].x20.v[3] = D_0048C690.x20.v[3];
    for (i = 0; i < 2; i++) {
        o[i].a.v[0] = D_0048C6F0[col].v[0];
        o[i].a.v[1] = D_0048C6F0[col].v[1];
        o[i].a.v[2] = D_0048C6F0[col].v[2];
        o[i].a.v[3] = D_0048C6F0[col].v[3];
        o[i].x40.v[0] = D_00472150.v[0];
        o[i].x40.v[1] = D_00472150.v[1];
        o[i].x40.v[2] = D_00472150.v[2];
        o[i].x40.v[3] = D_00472150.v[3];
        o[i].x30.v[0] = D_00486300.v[0];
        o[i].x30.v[1] = D_00486300.v[1];
        o[i].x30.v[2] = D_00486300.v[2];
        o[i].x30.v[3] = D_00486300.v[3];
    }
}

typedef f32 V4_52[4] __attribute__((aligned(16)));
#include "data/pieces/D_002A6238.h"
typedef PlaneBits_2a6238 Bf52;
typedef Ent20_2a6238 Plane52;
void func_00104eb0(s32, V4_52);
void func_00104f10(s32, V4_52);
s32 func_00104ae0(s32, V4_52 *);
f32 fabsf(f32);

static inline void v52_sub(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vsub.xyzw $vf6xyzw, $vf4xyzw, $vf5xyzw\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void v52_cross(f32 *d, f32 *a, f32 *b) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "lqc2 $vf5, 0(%2)\n"
        "vopmula.xyz ACC, $vf4xyz, $vf5xyz\n"
        "vopmsub.xyz $vf6xyz, $vf5xyz, $vf4xyz\n"
        "vsub.w $vf6w, $vf6w, $vf6w\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(a), "r"(b) : "memory");
}

static inline void v52_normalize(f32 *d, f32 *s) {
    __asm__ volatile(
        "lqc2 $vf4, 0(%1)\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf4xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "vsqrt Q, $vf5x\n"
        "vwaitq\n"
        "vaddq.x $vf5x, $vf0x, Q\n"
        "vdiv Q, $vf0w, $vf5x\n"
        "vsub.xyzw $vf6xyzw, $vf0xyzw, $vf0xyzw\n"
        "vwaitq\n"
        "vmulq.xyz $vf6xyz, $vf4xyz, Q\n"
        "sqc2 $vf6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "memory");
}

static inline f32 v52_dot(f32 *a, f32 *b) {
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

void func_00115408(s32 id, f32 *pos, f32 *out, s32 mode) {
    V4_52 pt, e, f, n;
    V4_52 v[4];
    f32 d;
    func_00104eb0(id, pt);
    func_00104f10(id, n);
    if (mode != 1 && fabsf(n[1]) > 0.0999999940395355224609375f) {
        *out = (-D_002A6238[id].d - (n[0] * pos[0] + n[2] * pos[2])) / n[1];
        return;
    }
    func_00104ae0(id, v);
    v52_sub(e, v[0], v[1]);
    v52_sub(f, v[2], v[1]);
    v52_cross(n, e, f);
    v52_normalize(n, n);
    d = v52_dot(n, pt);
    if (n[1] != 0.0f) {
        *out = (d - (n[0] * pos[0] + n[2] * pos[2])) / n[1];
    } else {
        *out = 1000000.0f;
    }
}

extern s32 D_002A62E8;
#include "data/pieces/D_002A3F48.h"
typedef struct { u8 pad[0x28]; s32 x28; s32 x2c; u8 pad30[4]; f32 x34; u8 pad38[4]; u16 x3c; u8 pad3e[2]; V4_52 x40; u8 pad50[0x18]; f32 x68; } Src52;
typedef struct { V4_52 p; s32 x10[4]; s32 x20; f32 x24; s32 x28; f32 x2c; V4_52 x30; s32 x40; } Dst52;
void func_001150d8(void);
void func_002675a8(void *, void *);
void func_001156f0(s32, void *);
void func_0011aac8(s32, void *, s32);
Bf52 *func_0011ab38(); /* called with 2 and 3 args */

void func_00117710(Src52 *a, Dst52 *b) {
    s32 id;
    Bf52 *bp;
    s32 k;
    a->x34 = 123456.0f;
    if (a->x28 >= 0) return;
    if (D_002A62E8) func_001150d8();
    func_002675a8(b->x30, ((V4_52 *)D_002A3F48));
    id = a->x3c;
    a->x28 &= 0x7fffffff;
    b->x40 = 0;
    if (id == 0xffff) {
        func_002675a8(b, a->x40);
        b->x20 = 0;
        b->x24 = 1.0f;
        b->x28 = 0;
        b->x2c = 1.0f;

        return;
    }
    b->p[0] = a->x40[0];
    b->p[1] = a->x68;
    b->p[2] = a->x40[2];
    b->p[3] = 1.0f;
    if (a->x2c == -1) {
        func_001156f0(id, b);
        b->x40 = (&D_002A6238[id].f.p)->x40;
        k = (&D_002A6238[id].f.p)->k;
    } else {
        func_0011aac8(id, b, a->x2c);
        bp = func_0011ab38(a->x2c, id);
        b->x40 = bp->x40;
        k = bp->k;
    }
    func_002675a8(b->x30, ((V4_52 *)D_002A3F48)[k]);
}

extern s32 D_002BD150[];
extern s32 D_002BD160[];
typedef struct { u16 poly; u16 i0; u16 i1; } Edge52;
s32 func_00104a90(s32, s32 *);
void func_0011a818(s32 *, s32 *, Edge52 *);
s32 func_0011a7c0(s32, s32, s32 *);

s32 func_00117948(Edge52 *e, s32 n, s32 *list, s32 grp) {
    s32 v[4];
    s32 a, b;
    s32 i, j, cnt, id;
    s32 *idx;
    u32 *f, *g;
    if (grp == -1) {
        s32 ta = D_002A6238[e->poly].v[e->i0];
        s32 tb = D_002A6238[e->poly].v[e->i1];
        a = ta;
        b = tb;
        for (i = 0; i < n; i++) {
            id = list[i];
            f = &D_002A6238[id].f.w;
            if (e->poly == id) continue;
            cnt = func_00104a90(id, v);
            if (cnt == 3) idx = D_002BD150;
            else idx = D_002BD160;
            for (j = 0; j < cnt; j++) {
                if (b == v[j] && a == v[idx[j]]) return (*f & 0x406) != 0x400;
            }
        }
        return 1;
    }
    func_0011a818(&a, &b, e);
    for (i = 0; i < n; i++) {
        id = list[i];
        g = (u32 *)func_0011ab38(grp, id, grp);
        if (e->poly == id) continue;
        cnt = func_0011a7c0(grp, id, v);
        idx = cnt == 3 ? D_002BD150 : D_002BD160;
        for (j = 0; j < cnt; j++) {
            if (b == v[j] && a == v[idx[j]]) return (*g & 0x406) != 0x400;
        }
    }
    return 1;
}

typedef struct { V4_52 pts[512]; V4_52 tmp; s32 ids[512]; } Hits52;
#include "data/pieces/D_002BD250.h"
void *func_00122048(s32, s32);
void func_001220b8(void *);
s32 func_001152c8(s32, void *, void *, void *);
s32 func_001198c8(s32, s32, f32 *);

static inline void v52_copy(void *d, void *s) {
    __asm__ volatile(
        "lq $6, 0(%1)\n"
        "sq $6, 0(%0)\n"
        "nop\n"
        : : "r"(d), "r"(s) : "$6", "memory");
}

static inline f32 v52_dist2(f32 *a, f32 *b) {
    f32 r;
    __asm__ volatile(
        "lqc2 $vf6, 0(%1)\n"
        "lqc2 $vf4, 0(%2)\n"
        "vsub.xyzw $vf5xyzw, $vf6xyzw, $vf4xyzw\n"
        "vmove.xyzw $vf4xyzw, $vf5xyzw\n"
        "vmul.xyz $vf5xyz, $vf4xyz, $vf5xyz\n"
        "vaddy.x $vf5x, $vf5x, $vf5y\n"
        "vaddz.x $vf5x, $vf5x, $vf5z\n"
        "qmfc2 $2, $vf5\n"
        "mtc1 $2, %0\n"
        : "=f"(r) : "r"(a), "r"(b) : "$2");
    return r;
}

s32 func_00117c08(s32 n, f32 *p, void *dir, f32 *out) {
    Hits52 *w;
    s32 i, cnt, id;
    s32 *q;
    f32 d, bd;
    cnt = 0;
    w = func_00122048(sizeof(Hits52), 4);
    for (i = 0; i < n; i++) {
        id = D_002BD250[i];
        if (func_001152c8(id, p, dir, w->tmp) && func_001198c8(-1, id, w->tmp)) {
            v52_copy(w->pts[cnt], w->tmp);
            w->ids[cnt] = id;
            cnt++;
        }
    }
    i = 0;
    if (cnt != 0) {
        bd = 1e12f;
        id = 0;
        for (; i < cnt; i++) {
            d = v52_dist2(p, w->pts[i]);
            if (d < bd) {
                bd = d;
                id = i;
            }
        }
        v52_copy(out, w->pts[id]);
        i = w->ids[id];
        func_001220b8(w);
        return i;
    }
    func_001220b8(w);
    return -1;
}

typedef struct { V4_52 pos; V4_52 dir; V4_52 out; s16 x30; s32 x34; } Ray52;
typedef struct { u8 pad[0x18]; u16 x18; u8 pad1a[6]; V4_52 x20; V4_52 x30; } RayW52;
extern s32 D_002C1304;
extern s32 D_002A62EC;
void func_001195d8(Ray52 *, RayW52 *);
s32 func_0011c338(RayW52 *, Ray52 *, f32 *, f32 *, s32, s32 *);
void func_00116368(void *, s32);
void func_00117db0(); /* called with 1 and 2 args */
void func_002675a8(void *, void *);

static inline f32 v52_dist(f32 *a, f32 *b) {
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

void func_00118060(Ray52 *o, s32 a1, s32 a2, s32 a3) {
    s32 hit;
    s32 r1, r2;
    RayW52 *w;
    if (D_002C1304 == 1) {
        o->x30 = o->x34 = -1;
        return;
    }
    o->x34 = -1;
    r1 = -1;
    w = func_00122048(64, 4);
    func_001195d8(o, w);
    if (a2 == 0) r1 = func_0011c338(w, o, o->dir, w->x20, a3, &hit);
    if (D_002A62EC == 0) func_00116368(w, a1);
    else func_00117db0(w, a1);
    r2 = func_00117c08(w->x18, o->pos, o->dir, w->x30);
    if (r1 != -1) {
        if (r2 == -1) {
            func_002675a8(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else if (v52_dist(o->pos, w->x20) < v52_dist(o->pos, w->x30)) {
            func_002675a8(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else {
            func_002675a8(o->out, w->x30);
            o->x30 = r2;
        }
    } else {
            func_002675a8(o->out, w->x30);
            o->x30 = r2;
    }
    func_001220b8(w);
}

s32 func_00115600(s32, f32 *);
void func_00115408(s32, f32 *, f32 *, s32);

s32 func_00118230(s32 n, f32 *p, f32 *lim, f32 *out) {
    f32 h;
    s32 *buf;
    s32 i, cnt, best, id;
    f32 d, bd;
    cnt = 0;
    best = -1;
    buf = func_00122048(0x800, 4);
    for (i = 0; i < n; i++) {
        id = D_002BD250[i];
        if (func_00115600(id, p)) {
            buf[cnt] = id;
            cnt++;
        }
    }
    bd = lim[1];
    for (i = 0; i < cnt; i++) {
        func_00115408(buf[i], p, &h, 0);
        d = fabsf(p[1] - h);
        if (d < bd) {
            out[1] = h;
            bd = d;
            best = buf[i];
        }
    }
    out[0] = p[0];
    out[2] = p[2];
    func_001220b8(buf);
    return best;
}

void func_00118378(Ray52 *o, s32 a1, s32 a2, s32 a3) {
    s32 hit;
    s32 r1, r2;
    RayW52 *w;
    if (D_002C1304 == 1) {
        o->x30 = o->x34 = -1;
        return;
    }
    o->x34 = -1;
    r1 = -1;
    w = func_00122048(64, 4);
    func_001195d8(o, w);
    if (a2 == 0) r1 = func_0011c338(w, o, o->dir, w->x20, a3, &hit);
    if (D_002A62EC == 0) func_00116368(w, a1);
    else func_00117db0(w, a1);
    r2 = func_00118230(w->x18, o->pos, o->dir, w->x30);
    if (r1 != -1) {
        if (r2 == -1) {
            func_002675a8(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else if (v52_dist(o->pos, w->x20) < v52_dist(o->pos, w->x30)) {
            func_002675a8(o->out, w->x20);
            o->x30 = r1;
            o->x34 = hit;
        } else {
            func_002675a8(o->out, w->x30);
            o->x30 = r2;
        }
    } else {
            func_002675a8(o->out, w->x30);
            o->x30 = r2;
    }
    func_001220b8(w);
}

typedef struct { f32 mn[3]; f32 mx[3]; u16 cnt; } Box52;
typedef struct { V4_52 pos; V4_52 dir; f32 x20; f32 x24; } Probe52;
extern f32 D_002C1250;
void func_00267518(void *, void *, void *);
s32 func_00119a20(s32, void *, void *, void *, f32 *);
s32 func_00119ad8(s32, s32, void *, void *, void *, f32 *);

s32 func_001186a8(Probe52 *o) {
    V4_52 pt, x, n;
    Box52 box;
    s32 ids[512];
    s32 i, cnt, id;
    cnt = 0;
    D_002C1250 = o->x20 - 0.0079999999f;
    func_00267518(pt, o->pos, o->dir);
    pt[1] -= o->x24;
    box.mn[0] = pt[0] - D_002C1250;
    box.mn[2] = pt[2] - D_002C1250;
    box.mn[1] = pt[1] - D_002C1250;
    box.mx[0] = pt[0] + D_002C1250;
    box.mx[1] = pt[1] + D_002C1250;
    box.mx[2] = pt[2] + D_002C1250;
    func_00116368(&box, 2);
    for (i = 0; i < box.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, n);
        if (func_00119a20(id, n, pt, x, &D_002C1250)) return id;
        ids[cnt] = id;
        cnt++;
    }
    for (i = 0; i < cnt; i++) {
        id = ids[i];
        func_00104f10(id, n);
        if (func_00119ad8(-1, id, n, pt, x, &D_002C1250)) return id;
    }
    return 0xffff;
}

typedef struct { V4_52 a; V4_52 b; f32 r; s32 x24; u8 pad[0x58]; } Sph52;
s32 func_0011b6a0(Sph52 *, f32 *, s32);
void func_001047c8(void);
void func_00104528(void);

s32 func_00118b58(Probe52 *o) {
    V4_52 pt, x, n;
    Box52 box;
    s32 ids[512];
    Sph52 s;
    s32 i, cnt, id;
    o->dir[3] = o->pos[3] = 1.0f;
    D_002C1250 = o->x20 - 0.0079999999f;
    func_00267518(pt, o->pos, o->dir);
    s.r = o->x20;
    s.x24 = 0;
    if (func_0011b6a0(&s, pt, 1)) return 1;
    func_001047c8();
    box.mn[0] = pt[0] - o->x20;
    box.mn[2] = pt[2] - o->x20;
    box.mn[1] = pt[1] - o->x24;
    box.mx[0] = pt[0] + o->x20;
    box.mx[1] = pt[1] + o->x24;
    box.mx[2] = pt[2] + o->x20;
    if (D_002A62EC == 0) func_00116368(&box, 7);
    else func_00117db0(&box);
    x[3] = 1.0f;
    cnt = 0;
    for (i = 0; i < box.cnt; i++) {
        id = D_002BD250[i];
        func_00104f10(id, n);
        if (func_00119a20(id, n, pt, x, &D_002C1250)) {
            func_00104528();
            return 1;
        }
        ids[cnt] = id;
        cnt++;
    }
    for (i = 0; i < cnt; i++) {
        id = ids[i];
        func_00104f10(id, n);
        if (func_00119ad8(-1, id, n, pt, x, &D_002C1250)) {
            func_00104528();
            return 1;
        }
    }
    func_00104528();
    return 0;
}

typedef struct { Plane52 *tbl; u8 pad[60]; } Grp52;
extern Grp52 D_004E2458[];
#include "data/types/text_00110000_h52_p2.h"
#include "data/pieces/D_003044DC.h"
typedef struct { u8 pad[0x18]; s16 cnt; } Qry52;
void func_001158c8(Qry52 *);
s32 func_0011ab88(s32, s32, Qry52 *);

s32 *func_0011af48(s32 g, Qry52 *q, s32 mode, s32 *out) {
    Mdl52 *m;
    u16 *list;
    Plane52 *tbl;
    s32 cnt, i, id;
    cnt = 0;
    m = D_003044DC[g].m;
    tbl = D_004E2458[g].tbl;
    m = (Mdl52 *)((u8 *)m + m->x10);
    list = (u16 *)((u8 *)m + m->x20);
    func_001158c8(q);
    for (i = 0; i < list[0]; i++) {
        u32 *w;
        id = list[i + 1];
        w = &tbl[id].f.w;
        switch (mode) {
        case 0:
            if (!(*w & 0x106) && func_0011ab88(g, id, q)) {
                out[cnt] = id;
                cnt++;
            }
            break;
        case 1:
            if ((*w & 0x406) == 0x400 && func_0011ab88(g, id, q)) {
                out[cnt] = id;
                cnt++;
            }
            break;
        }
    }
    q->cnt = cnt;
    return out + cnt;
}

void func_0011a9c8(s32, s32, f32 *);
void func_0011a978(s32, s32, f32 *);
void func_0011aa18(s32, s32, V4_52 *);

void func_0011b9f8(s32 g, s32 id, f32 *p, f32 *out) {
    V4_52 a, n, e1, e2, tri[4];
    f32 d;
    func_0011a9c8(g, id, a);
    func_0011a978(g, id, n);
    d = v52_dot(n, a);
    if (fabsf(n[1]) > 0.09999999776f) {
        *out = (d - (n[0] * p[0] + n[2] * p[2])) / n[1];
        return;
    }
    func_0011aa18(g, id, tri);
    v52_sub(e1, tri[0], tri[1]);
    v52_sub(e2, tri[2], tri[1]);
    v52_cross(n, e1, e2);
    v52_normalize(n, n);
    d = v52_dot(n, a);
    if (n[1] != 0.0f) {
        *out = (d - (n[0] * p[0] + n[2] * p[2])) / n[1];
    } else {
        *out = 1000000.0f;
    }
}

extern s32 D_002BC128;
extern s32 D_002BC130;
#include "data/pieces/D_002C1300.h"
typedef struct { f32 x0, x4; u8 pad8[0x1c]; f32 x24; } Obj52;
s32 func_0011b908(s32, s32, f32 *);

s32 func_0011bbe8(Obj52 *o, f32 *p, s32 g, f32 *out) {
    s32 ids[512];
    f32 h[2];
    Mdl52 *m;
    u16 *list;
    s32 best, cnt, i, id;
    Plane52 *tbl;
    f32 e, dy;
    *out = 1000000.0f;
    best = -1;
    cnt = 0;
    m = D_003044DC[g].m;
    tbl = D_004E2458[g].tbl;
    m = (Mdl52 *)((u8 *)m + m->x10);
    list = (u16 *)((u8 *)m + m->x20);
    for (i = 0; i < list[0]; i++) {
        Bf52 *w;
        id = list[i + 1];
        w = &tbl[id].f.p;
        if (D_002BC128 == 10 && D_002BC130 == 7 && D_002C1300(w)) break;
        if (func_0011b908(g, id, p)) {
            ids[cnt] = id;
            cnt++;
        }
    }
    e = *out;
    for (i = 0; i < cnt; i++) {
        func_0011b9f8(g, ids[i], p, &h[1]);
        dy = fabsf(o->x4 - h[1]);
        if (dy < e) {
            if (h[1] < p[1] - o->x24) {
                if (dy < o->x24) {
                    e = dy;
                    *out = h[1];
                    best = ids[i];
                }
            } else {
                e = dy;
                *out = h[1];
                best = ids[i];
            }
        }
    }
    return best;
}

#include "data/pieces/D_003044D8.h"
extern s32 D_003044D0;
s32 func_0011a728(void *, s32);
void func_0011a410(s32);

s32 func_0011bdf8(Obj52 *o, f32 *p, s32 *og, f32 *out) {
    Box52 bx;
    s32 gs[64];
    f32 hs[64];
    s32 rs[64];
    s32 i, n, bi;
    f32 best;
    n = 0;
    bx.mn[0] = p[0];
    bx.mn[2] = p[2];
    bx.mx[0] = p[0];
    bx.mx[2] = p[2];
    bx.mn[1] = p[1] - o->x24;
    bx.mx[1] = p[1] + 1000000.0f;
    for (i = 0; i < D_003044D0; i++) {
        if (D_003044D8[i].flags.b0 == 1) continue;
        if (func_0011a728(&bx, i)) {
            func_0011a410(i);
            gs[n] = i;
            n++;
        }
    }
    if (n == 0) return -1;
    best = 1000000.0f;
    bi = 0;
    for (i = 0; i < n; i++) {
        rs[i] = func_0011bbe8(o, p, gs[i], &hs[i]);
        if (hs[i] < best) {
            best = hs[i];
            bi = i;
        }
    }
    *out = best;
    *og = gs[bi];
    return rs[bi];
}
#include "data/bss_004D_typed.h"
#include "data/data_002A.h"
#include "data/data_002B.h"
#include "data/data_002C.h"
#include "data/data_0030.h"
#include "data/pieces/D_0046E120.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002BCC24.h"
#include "data/pieces/D_002BD114.h"
#include "data/pieces/D_002C1308.h"
#include "data/pieces/D_00486300.h"
