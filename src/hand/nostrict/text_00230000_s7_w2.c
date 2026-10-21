/* session 7 w2: func_0023ec88 (CONTEXT_ONLY func_0023e160 and func_0023d528 above). */
#include "common.h"
#include "data/types/nostrict_text_00230000_s7_w2.h"
typedef struct { s32 a, b, c, d; u8 pad[0xC0 - 0x10]; } __attribute__((aligned(8))) Big;
typedef struct { u8 pad[0x40]; s32 unk40; u8 pad44[4]; s32 unk48; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x5C - 8];
    Big *unk5C;
    u8 pad60[4];
    Big *unk64;
    u8 pad68[4];
    s32 unk6C;
    u8 pad70[0x10];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0xA18 - 0x94];
    s32 unkA18;
    f32 unkA1C;
} Obj;
typedef struct { s32 unk0, unk4, unk8, unkC; } S16;
extern S16 D_00454A20;
extern Col D_004915D0;
typedef struct { s32 x, y, z, w; } I4b;
I4b *func_0023d208(s32 *, s32 *, f32, I4b *);
#define D208(a,b,c,f) func_0023d208(a,b,f,c)
s32 func_0023d1e0(f32);
CONTEXT_ONLY s32 func_0023e160(void *cv, void *rv, Col *colv, s32 dv, f32 a0, f32 a1, f32 al) {
    s32 *c = cv; s32 *r = rv; s32 *col = (s32 *)colv; I4b *d = (I4b *)dv;
    I4b *h;
    s32 i, n, m;
    ((u64 *)d)[0] = 0x1000000000008001ULL;
    ((u64 *)d)[1] = 1;
    d++;
    d->x = col[0];
    d->y = col[1];
    d->z = col[2];
    d->w = (u32)(col[3] * al);
    d++;
    h = d;
    d++;
    d->x = r[0];
    d->y = r[1];
    d->z = 0;
    d->w = 0;
    d = h + 2;
    d->x = c[0];
    d->y = c[1];
    d->z = 0;
    d->w = 0;
    d = D208(c, r, h + 3, a0);
    i = func_0023d1e0(a0) + 1;
    m = func_0023d1e0(a1);
    for (; i <= m; i++) {
        d = D208(c, r, d, i * 0.785398081f);
    }
    d = D208(c, r, d, a1);
    n = (d - h) - 1;
    ((u64 *)h)[0] = (n / 2) | 0x8000 | (0x82BBULL << 46);
    ((u64 *)h)[1] = 0x53;
    return (s32)d;
}
typedef struct { s32 x, y, z, w; } T16;
typedef struct { s32 unk0; u8 pad4[0x90]; s32 unk94; u8 pad98[4]; void *unk9C; } Ob9C;
extern T16 D_00454600[];
extern T16 D_00454650[];
extern T16 D_00454680[];
extern T16 D_004546C0[];
extern T16 D_00454700[];
void func_0024ac08(void *, s32 *);
CONTEXT_ONLY void func_0023d528(Obj *ov, s32 *p1, s32 *p2) {
    Ob9C *o = (Ob9C *)ov;
    s32 r[2];
    register T16 *t asm("$5");
    switch (o->unk0) {
    case 0:
        t = D_00454650;
        p1[0] = D_00454600[0].x;
        p1[1] = D_00454600[0].y;
        goto idx;
    case 1:
        p1[0] = D_00454600[1].x;
        p1[1] = D_00454600[1].y;
        p2[0] = D_00454680[0].x;
        p2[1] = D_00454680[0].y;
        break;
    case 2:
        p1[0] = D_00454600[2].x;
        p1[1] = D_00454600[2].y;
        p2[0] = D_004546C0[0].x;
        p2[1] = D_004546C0[0].y;
        break;
    case 3:
        t = D_00454700;
        p1[0] = D_00454600[3].x;
        p1[1] = D_00454600[3].y;
        goto idx;
    case 4:
        t = D_00454650;
        p1[0] = D_00454600[4].x;
        p1[1] = D_00454600[4].y;
    idx:
        p2[0] = t[o->unk94].x;
        p2[1] = t[o->unk94].y;
        break;
    }
    if (o->unk9C != 0) {
        func_0024ac08(o->unk9C, r);
        p2[0] += r[0];
        p2[1] += r[1];
    }
}
s32 func_0023d700(Big *, s32, s32, s32, s32, f32);

s32 func_0023ec88(Obj *e, s32 buf) {
    Col q = D_004915D0;
    s32 p1[4];
    s32 p2[4];
    s32 n, d, i, step;
    f32 k, v, w;
    if (e->unk0 == 4) {
        k = 0.52359867095947265625f;
        n = D_00454A20.unk8;
        d = 1;
    } else {
        k = 0.52359867095947265625f;
        d = 1;
        n = e->unk4->unk6C->unk48;
        if (n >= 21) n = 20;
    }
    if (e->unkA18 == 0) return buf;
    k *= n;
    v = 4.712388038635254f;
    if (v < k) { w = k; k = v; } else w = k;
    buf = func_0023e160(e->unk80, e->unk90 + 0x10, &q, buf, 0.0f, k, e->unkA1C);
    if (w <= v) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26;
    else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    n = (n - 9) / d;
    for (i = 0; i < n; i++) {
        buf = func_0023d700(e->unk5C, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= step;
    }
    if (e->unk0 == 0 || e->unk0 == 4) e->unk64->a = 440;
    else e->unk64->a = 397;
    return func_0023d700(e->unk64, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}
#include "data/pieces/D_004915D0.h"
