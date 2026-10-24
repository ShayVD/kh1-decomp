#include "common.h"
#include "data/bss_0054.h"

typedef struct {
    union { u64 flags; s32 w; } u;
    u8 pad8[4];
    f32 f0c;
    f32 v10[4];
    s32 i20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x34-0x2c];
    s32 i34;
    u8 pad38[0x3c-0x38];
    f32 f3c;
    f32 v40[4];
    u8 pad50[0x54-0x50];
    s32 i54;
    u8 pad58[0x70-0x58];
    f32 v70[4];
    f32 v80[4];
    s32 i90;
    u8 pad94[0x9c-0x94];
    s32 i9c;
    u8 pada0[0xc0-0xa0];
} Src57_c130;
typedef struct { s32 kind; s32 a4; s32 a8; s32 src; s32 a10; f32 f14; f32 f18; s32 pad1c; f32 v[4]; } Ent57_c130;
typedef struct { u8 x[20]; } Col57_c130;
typedef struct { u8 pad0[6]; u8 n; u8 pad7[0x18-7]; Col57_c130 *cols; } ColSet57_c130;
typedef struct {
    u8 pad0[0x134];
    ColSet57_c130 *cs;
    u8 pad138[0x370-0x138];
    u64 f370;
    u8 pad378[0x3a8-0x378];
    u32 mask;
    u8 pad3ac[0x3e0-0x3ac];
    s32 f3e0;
} Chr57_c130;
typedef struct { u8 pad0[0x100]; u64 f100; } Sub57_c850;
typedef struct {
    u8 pad0[0x30];
    f32 v30[3];
    f32 f3c;
    u8 pad40[0x148-0x40];
    Sub57_c850 *o148;
    u8 pad14c[0x150-0x14c];
    f32 f150;
    u8 pad154[0x170-0x154];
    f32 f170;
    u8 pad174[0x3c0-0x174];
    f32 v3c0[4];
    u8 pad3d0[4];
    f32 f3d4;
} Obj57_c850;
#include "data/types/nostrict_text_00140000_h57.h"
#include "data/types/nostrict_text_00140000_h57_p.h"

extern u32 D_002C5958;
extern Src57_c130 D_0054C440[64];
extern s32 D_0054F440; /* src/data/bss_0054.c: u32 D_0054F440 */
extern f32 D_002BBDFC;
extern f32 D_002C5970;
extern f32 D_0054F444;

Ent57_c130 *func_00121e28(s32, s32);
void func_00121ee0(Ent57_c130 *);
Chr57_c130 *func_001230a0(Chr57_c130 *);
s32 func_00123368(Chr57_c130 *);
s32 func_0014bdc0(Ent57_c130 *);
void func_0014b550(Ent57_c130 *, Ent57_c130 *, s32);
void func_0015bad0(Chr57_c130 *, Col57_c130 *, void *);
void func_002675a8(f32 *, f32 *);
f32 func_00120c18(f32 *);
f32 func_00120bf8(f32 *);
void func_00267560(f32 *, f32 *, f32);

s32 func_0014c130(void) {
    Ent57_c130 *tbl;
    s32 cnt;
    Ent57_c130 *e;
    Chr57_c130 *p;
    Chr57_c130 *q;
    Src57_c130 *s;
    Col57_c130 *c;
    s32 i;

    if ((D_002C5958 >> 14) & 1) return 0;
    tbl = func_00121e28(0x3000, 0);
    cnt = func_0014bdc0(tbl);
    e = &tbl[cnt];
    e->a10 = 1;
    e->src = 0;
    for (q = 0; (p = func_001230a0(q)) != 0; q = p) {
        if (!func_00123368(p)) continue;
        e->kind = (s32)(p->f370 >> 37) & 3;
        e->a4 = (s32)p;
        c = p->cs->cols;
        for (i = 0; i < p->cs->n; i++, c++) {
            if (!(p->mask & (1 << i))) {
                func_0015bad0(p, c, &e->a10);
                e->a8 = c->x[0];
                func_0014b550(e, tbl, cnt);
            }
        }
    }
    func_00121ee0(tbl);
    s = D_0054C440;
    for (i = 0; i < 64; i++, s++) {
        if ((s32)(s->u.flags >> 15) & 1) {
            func_002675a8(s->v70, s->v10);
            func_002675a8(s->v80, s->v40);
            s->u.flags |= 0x10000;
        } else {
            s->u.flags &= ~0x10000;
        }
        s->i9c &= D_0054F440;
    }
    p = 0;
    while ((p = func_001230a0(p)) != 0) {
        p->f3e0 &= D_0054F440;
    }
    return (s32)p;
}

void func_0014c850(Obj57_c850 *o, f32 *v) {
    f32 d;
    f32 lim;
    f32 k;
    f32 t;

    if ((s32)(o->o148->f100 >> 32) & 1) {
        lim = 16.0f;
        k = 2.0f;
        if (o->f3d4 < 70.0f) {
            t = o->f3d4 / 70.0f;
            k = (t * t * 0.800000026822f + 0.199999991804f) * 2.0f;
        }
    } else {
        lim = 8.0f;
        k = 1.19999995828f;
    }
    d = func_00120c18(o->v3c0);
    if (d < lim) {
        d += D_002BBDFC * 0.399999983609f;
        if (lim < d) d = lim;
    }
    func_002675a8(v, o->v30);
    func_00267560(v, v, d * D_002BBDFC);
    if (k * D_002BBDFC < o->v3c0[1]) {
        v[1] = k;
    } else {
        if (o->v3c0[1] < 0.0f) {
            o->v3c0[1] *= 0.799999967217f;
        }
        v[1] = o->v3c0[1] + D_002BBDFC * 0.484693862498f;
    }
    func_00267560(o->v3c0, v, D_002C5970);
    o->v3c0[1] = v[1];
    D_0054F444 = func_00120bf8(v);
}
#include "data/bss_0054_typed.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C5970.h"
