/* The gauges (include/hud/gauge.h, docs/modules.md "Session 47"): the parts
 * built with -fno-strict-aliasing.  The bar drawers (func_0023e160 a round
 * bar from angle a0 to a1 in eighths of a turn through func_0023d208, the
 * straight pieces past 270 degrees through nofill's func_0023d700), each
 * kind's bars (func_0023e5b0 / func_0023e330 kind 3's values, func_0023e8f0 /
 * func_0023f0d8 / func_0023f250 the round gauge, func_0023ec88 / func_0023f700
 * the second one, func_0023fad0 / func_0023fb90 / func_0023fd58 the player's
 * third, func_0023feb8 ... func_002401f0 kind 3's, func_00240400 the world
 * map's parts with tt_gaugeWorldmap's barrier count), the step
 * (func_00240b68: fade, the sprite playing, the low warning func_00240810 and
 * its sound func_0023d148), the draw of each kind (func_00240fa0 the world
 * map, func_002410b8 kind 3, func_00241260 the others) and the draw hook
 * func_002416a8, the slots' set ups (func_00241a38, func_00241c60) and the
 * sprite tables (func_00241d60), the face pictures (func_00242c08 /
 * func_00242ef8: a TIM2 sent to the GS directly).  The meanings of the
 * values (HP / MP) are guesses. */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "hud/gauge.h"
#include "data/types/nostrict_text_00230000_b16_p.h" /* Col */
#include "data/types/nostrict_text_00240000_s6_g1.h" /* Blob */
#include "data/data_0045.h"
#include "data/pieces/D_00426880.h"
#include "data/pieces/D_004268E0.h"
#include "data/pieces/D_00426910.h"
#include "data/pieces/D_00426940.h"
#include "data/pieces/D_00454A20.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_0044A830.h"
#include "data/pieces/D_0044C5A0.h"
#include "data/pieces/D_0044DFD0.h"
#include "data/pieces/D_0044F380.h"
#include "data/pieces/D_0044F4D0.h"
#include "data/pieces/D_00451040.h"
#include "data/pieces/D_00426970.h"
#include "data/pieces/D_0042B790.h"
#include "data/pieces/D_004305B0.h"

typedef struct { s32 x, y, z, w; } I4b;
typedef struct { f32 v[4]; } __attribute__((aligned(16))) V4f;
typedef struct { u32 b0:3; u32 b3:1; u32 rest:28; } F2C5958;
/* The drawing environment of the gauges (a 0x160-byte GS packet). */
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } QA;

extern GaugeTbl D_00651E50;
extern Gauge D_00651E70[];
extern QW D_00351E10[]; /* the staging arena as quadwords */
extern QW *D_00651D60;
extern QW *D_00651D64;
extern Col D_004915B0, D_004915C0, D_004915D0, D_004915E0, D_004915F0;
extern Col D_00491600, D_00491610, D_00491620;

s32 func_0011d768(s32);
void func_0011d790(s32, s32);
s32 func_001375d8(s32);
void *func_00122048(s32, s32);
void *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
void *func_0011fb38(s32, u64, void *);
void func_0011fb78(void *, s32, void *);
void func_001220b8(void *);
void __assert(const char *, s32, const char *);
f32 sinf(f32);
f32 cosf(f32);
f32 tanf(f32);
void func_00236fd8(QW *, QW *);
QW *func_00237008(u64, u64, QW *);
void func_00237018(void *, s32, s32);
void func_002370c8(void *);
void func_00249a48(void *, s32);
void func_002492d0(void *, f32, f32, f32, f32);
s32 func_002492e8(void *, s32);
void func_00249820(s32 *, s32 *);
f32 func_00249950(f32 *, f32, f32);
void func_0024a0e0(void *, void *);
s32 func_0024a1c0(void *);
void func_0024ac08(void *, s32 *);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0024b008(UiSpr *, void *);

/* gauge.c */
void func_0023d128(s32);
void func_0023d1a0(void);
s32 func_0023d1e0(f32);
void func_0023d528(Gauge *, s32 *, s32 *);
QW *func_0023dfc0(Gauge *, QW *);
QW *func_0023f688(Gauge *, QW *);
QW *func_00240118(Gauge *, QW *);
QW *func_002403d0(Gauge *, QW *);
void func_002407b0(Gauge *, s32);
void func_00240978(GActor *);
void func_002409b0(GActor *);
QW *func_00240ae0(GFade *, s32, s32, QW *, f32);
s32 func_00240b28(Gauge *);
void func_00241560(void);
Gauge *func_00241b60(s32, s32);
void func_00242bd0(void);
/* gauge.nofill.c */
void func_0023cfe8(void *, s32, void *);
s32 func_0023d490(Gauge *);
QW *func_0023d700(UiSpr *, Tex_4268b0 *, s32, s32, QW *, f32);
/* gauge.nostrict_nofill.c */
QW *func_0023d7e8(s32, s32 (*)[4], s32 (*)[4], s32 (*)[4], Tex_4268b0 *, QW *);
QW *func_0023dfd8(Gauge *, QW *);
QW *func_0023e330(Gauge *, QW *);
QW *func_0023f920(Gauge *, QW *);

void func_0023d148(s32 arg0) {
    if (D_00651E50.unk4120 == 0) {
        func_0011d768(0x2D);
        func_0011d790(0x2D, arg0);
        D_00651E50.unk4120 = 1;
    }
}

I4b *func_0023d208(I4b *a, I4b *b, I4b *o, f32 ang) {
    s32 n = func_0023d1e0(ang);
    f32 h = b->z >> 4;
    s32 k;
    s32 i;
    ang -= (f32)n * 0.78539807f;
    if (!(n & 1)) i = (s32)(tanf(ang) * h);
    else i = (s32)(tanf(0.78539807f - ang) * h);
    k = (s32)((f32)i * 16.0f + 0.5f);
    switch (n) {
    case 0:
        o->x = b->x - b->z;
        o->y = b->y - k;
        o++;
        o->x = a->x - b->z;
        o->y = a->y - k;
        break;
    case 1:
        o->x = b->x - k;
        o->y = b->y - b->z;
        o++;
        o->x = a->x - k;
        o->y = a->y - b->z;
        break;
    case 2:
        o->x = b->x - k;
        o->y = b->y - b->z;
        o++;
        o->x = a->x + k;
        o->y = a->y - b->z;
        break;
    case 3:
        o->x = b->x - b->z;
        o->y = b->y - k;
        o++;
        o->x = a->x + b->z;
        o->y = a->y - k;
        break;
    case 4:
        o->x = b->x - b->z;
        o->y = b->y - k;
        o++;
        o->x = a->x + b->z;
        o->y = a->y + k;
        break;
    default:
        o->x = b->x - k;
        o->y = b->y - b->z;
        o++;
        o->x = a->x + k;
        o->y = a->y + b->z;
        break;
    }
    o->z = 0;
    o->w = 0;
    return o + 1;
}

/* func_0023e160 calls func_0023d208 with the f32 before the output pointer
 * (EABI passes it in $f12 either way); the argument order changes the code,
 * so the PS2 build calls through that prototype. */
#ifdef KH1_PS2
#define D208(a, b, c, f) ((I4b *(*)(s32 *, s32 *, f32, I4b *))func_0023d208)(a, b, f, c)
#else
#define D208(a, b, c, f) func_0023d208((I4b *)(a), (I4b *)(b), c, f)
#endif

/* A copy of gauge.c's func_0023d528 (the slot's position: the kind's base and
 * offset, plus the playing sprite's offset): func_0023f250 and func_00241260
 * branch like the original (beqz, not beqzl) only with it defined above. */
extern I4b D_00454600[];
extern I4b D_00454650[];
extern I4b D_00454680[];
extern I4b D_004546C0[];
extern I4b D_00454700[];
CONTEXT_ONLY void func_0023d528(Gauge *o, s32 *p1, s32 *p2) {
    s32 r[2];
    register I4b *t KH1_REG("$5");
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

void func_0023d698(s32 a) {
    if (a == 0) {
        func_00249a48(&D_00426970, 1);
    } else if (a == 1) {
        func_00249a48(&D_0042B790, 1);
    } else {
        func_00249a48(&D_004305B0, 1);
    }
}

QW *func_0023da08(Gauge *g, s32 (*src)[4], s32 (*uv)[4], s32 ang, s32 off, QW *buf) {
    s32 m[4][4];
    s32 m2[4][4];
    s32 m3[4][4];
    s32 i, j;
    f32 a;
    s32 dx, dy;
    s32 bx, by;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            m[i][j] = src[i][j];
    for (j = 0; j < 4; j++)
        m[j][0] -= off;
    a = (f32)ang * 3.141592562f / 180.0f;
    for (j = 0; j < 4; j++) {
        s32 x = (f32)m[j][0] * cosf(a) - (f32)m[j][1] * sinf(a);
        s32 y = (f32)m[j][0] * sinf(a) + (f32)m[j][1] * cosf(a);
        m[j][0] = x;
        m[j][1] = y;
    }
    dy = 0;
    dx = 0;
    if (ang < 41) dx = -1;
    else if (ang < 56) dy = -1;
    else if (ang < 90) dy = -1;
    else if (ang == 90) dx = -1;
    else if (ang < 136) dy = -1;
    else if (ang < 180) ;
    else if (ang == 180) dy = -1;
    else if (ang < 221) dx = 1;
    else if (ang < 236) ;
    else if (ang == 240) ;
    else if (ang < 271) dy = 1;
    bx = (g->unk80[0] - 0x7000) >> 4;
    by = (g->unk80[1] - 0x7400) >> 4;
    for (j = 0; j < 4; j++) {
        m[j][0] = m[j][0] + bx + dx;
        m[j][1] = m[j][1] + by + dy;
    }
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            m2[i][j] = uv[i][j];
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++) {
            if (j == 3) m3[i][j] = g->unkA1C * 128.0f;
            else m3[i][j] = 128;
        }
    return func_0023d7e8(ang, m, m2, m3, g->unk6C, buf);
}

QW *func_0023e160(s32 *c, s32 *r, Col *col, QW *dq, f32 a0, f32 a1, f32 al) {
    I4b *d = (I4b *)dq;
    I4b *h;
    s32 i, n, m;
    ((u64 *)d)[0] = 0x1000000000008001ULL;
    ((u64 *)d)[1] = 1;
    d++;
    d->x = col->r;
    d->y = col->g;
    d->z = col->b;
    d->w = (u32)(col->a * al);
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
    return (QW *)d;
}

/* func_0023f0d8 calls func_0023e160 with the three floats before the colour:
 * the other prototype order schedules the argument moves differently. */
#ifdef KH1_PS2
#define E160_F(c, r, a0, a1, al, col, d) ((QW *(*)(void *, void *, f32, f32, f32, Col *, QW *))func_0023e160)(c, r, a0, a1, al, col, d)
#else
#define E160_F(c, r, a0, a1, al, col, d) func_0023e160(c, r, col, d, a0, a1, al)
#endif

QW *func_0023e5b0(Gauge *e, QW *buf) {
    s32 p1[4];
    s32 p2[4];
    UiSpr big;
    UiSpr c;
    Col q = D_004915B0;
    f32 v;
    s32 i, n, t, rem;
    f32 fr;
    v = *e->unkA90 * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90[0], &q, buf, 0.0f, v, e->unkA1C);
    v = *e->unkA90 * 0.0001745328918332234025001526f;
    if (v <= 4.712388038635254f) return buf;
    func_0023d528(e, p1, p2);
    c = *e->unk48[4];
    c.s.r[0] += 26;
    t = *e->unkA90 - 27000.0f;
    n = t / 3000;
    for (i = 0; i < n; i++) {
        if (i == 0) buf = func_0023d700(e->unk48[3], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        else buf = func_0023d700(&c, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= 26;
    }
    rem = t % 3000;
    if (rem != 0) {
        fr = rem / 3000.0f;
        p2[0] = p2[0] + (1.0f - fr) * 26.0f;
        if (n == 0) big = *e->unk48[3];
        else big = c;
        big.s.r[2] = big.s.r[2] * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += 26;
    }
    e->unk48[6]->s.r[0] = 414;
    return func_0023d700(e->unk48[6], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

QW *func_0023e8f0(Gauge *e, QW *buf) {
    s32 p1[4];
    s32 p2[4];
    UiSpr big;
    UiSpr c;
    Col q;
    f32 v, k;
    s32 i, n, t, rem, d, th, step, m;
    f32 fr;
    q = D_004915C0;
    if (e->unk0 == 4) {
        k = 0.06544983573f;
        n = D_00454A2C;
        d = 8;
        th = 72;
    } else {
        k = 0.08726644702f;
        d = 6;
        th = 54;
        n = e->unk4->unk6C->unk40;
        if (n >= 121) n = 120;
    }
    v = k * n;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90[0], &q, buf, 0.0f, v, e->unkA1C);
    if (th >= n) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26; else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    c = *e->unk48[4];
    c.s.r[0] += step;
    t = n - th;
    m = t / d;
    for (i = 0; i < m; i++) {
        if (i == 0) buf = func_0023d700(e->unk48[3], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        else buf = func_0023d700(&c, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= step;
    }
    rem = t % d;
    if (rem != 0) {
        fr = (f32)rem / (f32)d;
        p2[0] = p2[0] + (f32)step * (1.0f - fr);
        if (m == 0) big = *e->unk48[3];
        else big = c;
        big.s.r[2] = big.s.r[2] * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += step;
    }
    if (e->unk0 == 0 || e->unk0 == 4) e->unk48[6]->s.r[0] = 414; else e->unk48[6]->s.r[0] = 380;
    return func_0023d700(e->unk48[6], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

QW *func_0023ec88(Gauge *e, QW *buf) {
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
    buf = func_0023e160(e->unk80, e->unk90[1], &q, buf, 0.0f, k, e->unkA1C);
    if (w <= v) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26;
    else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    n = (n - 9) / d;
    for (i = 0; i < n; i++) {
        buf = func_0023d700(e->unk48[5], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= step;
    }
    if (e->unk0 == 0 || e->unk0 == 4) e->unk48[7]->s.r[0] = 440;
    else e->unk48[7]->s.r[0] = 397;
    return func_0023d700(e->unk48[7], e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

/* func_0023ee80 branches like the original only with a func_0023e330
 * (gauge.nostrict_nofill.c) defined above. */
CONTEXT_ONLY QW *func_0023e330(Gauge *o, QW *r) { return r; }

QW *func_0023ee80(Gauge *o, QW *r) {
    typedef union {
        u64 v;
        struct { u64 tbp0:14, tbw:6, psm:6, tw:4, th:4, tcc:1, tfx:2, cbp:14, cpsm:4, csm:1, csa:5, cld:3; } b;
    } Tex0;
    s32 a[4];
    s32 b[2];
    s32 i, x, y;
    u64 t;
    Tex0 tx;
    func_0023d528(o, a, b);
    x = b[0];
    y = b[1];
    for (i = 0; i < o->unk38; i++) {
        r = func_0023d700(o->unk28[i], &D_004268B0, x, y, r, o->unkA1C);
    }
    for (i = 0; i < o->unk24; i++) {
        if (((o->unkA18 == 0 && o->unk0 == 0) || (o->unk0 == 3 && o->unkA94 == 0)) && i == 5) continue;
        r = func_0023d700(o->unk8[i], o->unk6C, x, y, r, o->unkA1C);
    }
    r->lo = 0x2000000000008001;
    r->hi = 0xEE;
    r++;
    t = o->unk6C->tb.unk18;
    tx.v = t;
    tx.b.csa = 0;
    tx.b.cld = 1;
    tx.b.psm = 0x13;
    r->lo = tx.v;
    r->hi = 6;
    r++;
    r->lo = t;
    r->hi = 6;
    r++;
    switch (o->unk0) {
    case 3:
        r = func_0023e5b0(o, r);
        if (o->unkA94) r = func_0023e330(o, r);
        break;
    case 0:
    case 1:
    case 2:
    case 4:
        r = func_0023ec88(o, func_0023e8f0(o, r));
        break;
    }
    return r;
}

QW *func_0023f0d8(Gauge *e, QW *buf) {
    Col q = D_004915E0;
    Col c;
    s32 a, b;
    f32 k, v;
    if (e->unk0 == 4) {
        k = 0.06544983386993408203125f;
        b = D_00454A20.unk4;
        a = D_00454A20.unkC;
    } else {
        k = 0.087266445159912109375f;
        b = e->unk4->unk6C->unk3C;
        a = e->unk4->unk6C->unk40;
        if (a >= 121) a = 120;
        if (b >= 121) b = 120;
    }
    if (e->unkA24 == 2) {
        func_0024a0e0(&e->unkA0[5], &c);
        v = k * a;
        if (v > 4.712388038635254f) v = 4.712388038635254f;
        buf = E160_F(e->unk80, e->unk90[2], 0.0f, v, e->unkA1C, &c, buf);
    }
    v = k * b;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    return E160_F(e->unk80, e->unk90[2], 0.0f, v, e->unkA1C, &q, buf);
}

QW *func_0023f250(Gauge *o, QW *r) {
    s32 a[4];
    s32 b[2];
    UiSpr c;
    V4f m;
    UiSpr d;
    s32 base;
    s32 cur, max, step, w, len, i, n, k;
    f32 f, t;
    if (o->unk0 == 4) {
        f = 0.06544983386993408203125f;
        max = D_00454A20.unk4;
        cur = D_00454A20.unkC;
        step = 8;
        base = 72;
    } else {
        GStat *p = o->unk4->unk6C;
        f = 0.087266445159912109375f;
        step = 6;
        base = 54;
        max = p->unk3C;
        cur = p->unk40;
        if (max > 120) max = 120;
        if (cur > 120) cur = 120;
    }
    if (f * cur <= 4.71238803863525390625f) return r;
    if (o->unk0 == 0 || o->unk0 == 4) w = 26;
    else w = 17;
    if (o->unkA24 == 2) {
        len = cur - base;
        func_0023d528(o, a, b);
        func_0024a0e0(&o->unkA0[5], &m);
        n = len / step;
        d = *o->unk48[0];
        func_0024b008(&d, &m);
        for (i = 0; i < n; i++) {
            r = func_0023d700(&d, o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= w;
        }
        k = len % step;
        if (k != 0) {
            t = (f32)k / (f32)step;
            b[0] = b[0] + w * (1.0f - t);
            c = d;
            c.s.r[2] = c.s.r[2] * (t + 0.0625f);
            r = func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
        }
    }
    if (base >= max) return r;
    {
        len = max - base;
        func_0023d528(o, a, b);
        b[0]--;
        n = len / step;
        for (i = 0; i < n; i++) {
            r = func_0023d700(o->unk48[0], o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= w;
        }
        k = len % step;
        if (k == 0) return r;
        t = (f32)k / (f32)step;
        b[0] = b[0] + w * (1.0f - t);
        c = *o->unk48[0];
        c.s.r[2] = c.s.r[2] * (t + 0.0625f);
        return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
    }
}

QW *func_0023f700(Gauge *o, QW *a1) {
    Col c = D_004915F0;
    s32 v;
    a1 = func_0023e160(o->unk80, o->unk90[3], &c, a1, 0.0f, o->unk9E4, o->unkA1C);
    if (o->unk9EC[1] != 0.0f) {
        v = o->unk9EC[0];
        c.a = 128;
        c.b = v;
        c.g = v;
        c.r = v;
        a1 = func_0023e160(o->unk80, o->unk90[3], &c, a1, o->unk9E4, o->unk9E8, o->unkA1C);
    }
    return a1;
}

QW *func_0023fad0(Gauge *o, QW *d) {
    Col q = D_00491600;
    d = func_0023e160(o->unk80, o->unk90[4], &q, d, 0.0f, o->unkA00, o->unkA1C);
    if (o->unkA08[1] != 0.0f) {
        q.b = 128;
        q.g = 128;
        q.r = 128;
        q.a = o->unkA08[0];
        return func_0023e160(o->unk80, o->unk90[4], &q, d, o->unkA00, o->unkA04, o->unkA1C);
    }
    return d;
}

QW *func_0023fb90(Gauge *o, QW *r) {
    s32 a[4];
    s32 b[2];
    UiSpr c;
    s32 n, m, i, k;
    f32 t, w;
    n = o->unk4->unk6C->unkBE;
    if (n > 600) n = 600;
    if (n < 271) return r;
    if (o->unk0 != 0) return r;
    func_0023d528(o, a, b);
    m = n - 270;
    i = m / 30;
    if (i > 0) {
        k = i;
        do {
            k--;
            r = func_0023d700(o->unk48[2], o->unk70, b[0], b[1], r, o->unkA1C);
            b[0] -= 26;
        } while (k);
    }
    k = m % 30;
    if (k == 0) return r;
    t = (f32)k / 30.0f;
    c = *o->unk48[2];
    w = c.s.r[2];
    c.s.r[2] = w * t;
    c.s.t[0] = c.s.t[0] + (c.s.t[2] - c.s.t[0]) * t;
    c.s.r[0] = c.s.r[0] + (1.0f - t) * w;
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

QW *func_0023fd58(Gauge *o, QW *r) {
    s32 n = o->unk4->unk6C->unkBE;
    f32 a, b;
    s32 p;
    a = n * 0.017453289f;
    if (a > 4.71238803863525390625f) a = 4.71238803863525390625f;
    p = o->unk9FC;
    b = p * 0.017453289f;
    if (b > 4.71238803863525390625f) b = 4.71238803863525390625f;
    if (n < p) {
        o->unkA00 = a;
        o->unkA04 = b;
        func_002492d0(o->unkA08, 128.0f, -12.799999237060546875f, 0.0f, 128.0f);
    } else if (p < n) {
        o->unkA00 = b;
        o->unkA04 = a;
        func_002492d0(o->unkA08, 0.0f, 12.799999237060546875f, 0.0f, 128.0f);
    }
    if (func_002492e8(o->unkA08, D_002BBDFC) == 1) {
        o->unkA00 = o->unkA04;
    }
    r = func_0023fb90(o, func_0023fad0(o, r));
    o->unk9FC = n;
    return r;
}

QW *func_0023feb8(Gauge *e, QW *b) {
    Col q = D_00491610;
    f32 *p = e->unkA88;
    f32 v = *p * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    return func_0023e160(e->unk80, e->unk90[2], &q, b, 0.0f, v, e->unkA1C);
}

QW *func_0023ff38(Gauge *o, QW *r) {
    s32 a[4];
    s32 b[2];
    UiSpr c;
    s32 m, i, n, k;
    f32 t;
    if (*o->unkA88 * 0.00017453289547120220959f <= 4.71238803863525390625f) return r;
    func_0023d528(o, a, b);
    m = *o->unkA88 - 27000.0f;
    n = m / 3000;
    for (i = 0; i < n; i++) {
        r = func_0023d700(o->unk48[0], o->unk70, b[0], b[1], r, o->unkA1C);
        b[0] -= 26;
    }
    k = m % 3000;
    if (k == 0) return r;
    t = (f32)k / 3000.0f;
    b[0] = b[0] + (1.0f - t) * 26.0f;
    c = *o->unk48[0];
    c.s.r[2] = c.s.r[2] * (t + 0.0625f);
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

QW *func_00240170(Gauge *e, QW *b) {
    Col q = D_00491620;
    f32 *p = e->unkA8C;
    f32 v = *p * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    return func_0023e160(e->unk80, e->unk90[3], &q, b, 0.0f, v, e->unkA1C);
}

QW *func_002401f0(Gauge *o, QW *r) {
    s32 a[4];
    s32 b[2];
    UiSpr c;
    s32 m, i, n, k;
    f32 t;
    if (*o->unkA8C * 0.00017453289547120220959f <= 4.71238803863525390625f) return r;
    func_0023d528(o, a, b);
    m = *o->unkA8C - 27000.0f;
    n = m / 3000;
    for (i = 0; i < n; i++) {
        r = func_0023d700(o->unk48[1], o->unk70, b[0], b[1], r, o->unkA1C);
        b[0] -= 26;
    }
    k = m % 3000;
    if (k == 0) return r;
    t = (f32)k / 3000.0f;
    b[0] = b[0] + (1.0f - t) * 26.0f;
    c = *o->unk48[1];
    c.s.r[2] = c.s.r[2] * (t + 0.0625f);
    return func_0023d700(&c, o->unk70, b[0], b[1], r, o->unkA1C);
}

QW *func_00240400(Gauge *e, QW *buf) {
    s32 p1[4];
    s32 p2[4];
    UiSpr c;
    s32 x, y, i;
    struct GaugeWm *t = &e->unkA34;
    func_0023d528(e, p1, p2);
    x = p2[0];
    y = p2[1];
    switch (D_00454A20.mode) {
    case 0: break;
    case 1:
        c = *t->b;
        c.s.r[2] = c.s.r[2] * D_00454A20.scale;
        for (i = 0; i < 5; i++) buf = func_0023d700(t->a[i], D_00426880, x, y, buf, e->unkA1C);
        buf = func_0023d700(&c, D_004268E0, x, y, buf, e->unkA1C);
        break;
    case 2:
        for (i = 0; i < 4; i++) buf = func_0023d700(t->c[i], D_00426880, x, y, buf, e->unkA1C);
        if (!(D_00454A20.barrier >= 0 && D_00454A20.barrier <= 5)) __assert("ttlib/ui_gauge.c", 2727, "tt_gaugeWorldmap.barrier >= 0 && tt_gaugeWorldmap.barrier <= 5");
        for (i = 0; i < D_00454A20.barrier; i++) buf = func_0023d700(t->d[i], D_00426880, x, y, buf, e->unkA1C);
        break;
    case 3:
        c = *t->b;
        c.s.r[2] = c.s.r[2] * D_00454A20.scale;
        for (i = 0; i < 5; i++) buf = func_0023d700(t->a[i], D_00426880, x, y, buf, e->unkA1C);
        buf = func_0023d700(&c, D_004268E0, x, y, buf, e->unkA1C);
        for (i = 0; i < 3; i++) buf = func_0023d700(t->c[i], D_00426880, x, y, buf, e->unkA1C);
        if (!(D_00454A20.barrier >= 0 && D_00454A20.barrier <= 5)) __assert("ttlib/ui_gauge.c", 2747, "tt_gaugeWorldmap.barrier >= 0 && tt_gaugeWorldmap.barrier <= 5");
        for (i = 0; i < D_00454A20.barrier; i++) buf = func_0023d700(t->d[i], D_00426880, x, y, buf, e->unkA1C);
        break;
    }
    return buf;
}

s32 func_00240810(Gauge *o) {
    s32 r;
    GStat *p;
    if (o->unk0 == 4) {
        r = 0;
        if (D_00454A20.unk4 != 0) {
            if ((f32)D_00454A20.unk4 < (f32)D_00454A20.unkC * 0.3f) r = 1;
        }
    } else {
        r = 0;
        if (o->unk0 != 3) {
            p = o->unk4->unk6C;
            if (p->unk3C > 0) {
                r = p->unk3C < 9;
                if (p->unk40 >= 45) {
                    if ((f32)p->unk3C / (f32)p->unk40 < 0.199999988079071044921875f) r = 1;
                    else r = 0;
                }
            }
        }
    }
    return r;
}

void func_002409e0(GFade *o) {
    switch (o->unk250) {
    case 0:
        break;
    case 1:
        o->unk254 = 0;
        o->unk0 = &o->unk10;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 2:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) o->unk250++;
        break;
    case 3:
        o->unk0 = &o->unkD0;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 4:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) {
            if (o->unk254 == 0) do { func_0024ae00(o->unk0); } while (0);
            else o->unk250++;
        }
        break;
    case 5:
        o->unk0 = &o->unk190;
        func_0024ae00(o->unk0);
        o->unk250++;
        break;
    case 6:
        func_0024af00(o->unk0);
        if (func_0024a1c0(o->unk0) & 4) o->unk250 = 0;
        break;
    }
}

void func_00240b68(Gauge *e) {
    s32 p1[4];
    s32 p2[4];
    s32 n, r;
    if (e->unkA20 != 0.0f) {
        if (!((*(u32 *)&D_002C5960) & 1)) e->unkA1C += e->unkA20 * D_002BBDFC;
        if (e->unkA1C <= 0.0f) {
            e->unkA20 = e->unkA1C = 0.0f;
        } else if (1.0f <= e->unkA1C) {
            e->unkA1C = 1.0f;
            e->unkA20 = 0.0f;
        }
    }
    if (e->unk0 == 0) {
        n = func_0023d490(e);
        if (e->unk98 != n) {
            e->unk98 = n;
            if (n == 0) func_002407b0(e, 0);
            else if (n == 1) func_002407b0(e, 0);
            else if (n == 2) func_002407b0(e, 1);
        }
    }
    if (e->unk9C) {
        func_0024af00(e->unk9C);
        if (e->unk9C->s.c.flags & 4) {
            e->unk9C = 0;
            e->unk94 = e->unk98;
        }
    }
    func_0023d528(e, p1, p2);
    e->unk80[0] = (p1[0] + p2[0]) * 16 + 0x7000;
    e->unk80[1] = (p1[1] + p2[1]) * 16 + 0x7400;
    r = func_00240810(e);
    switch (e->unkA24) {
    case 0:
        if (r) e->unkA24 = 1;
        break;
    case 1:
        func_0024ae00(&e->unkA0[5]);
        e->unkA24++;
        break;
    case 2:
        func_0024af00(&e->unkA0[5]);
        if (func_0024a1c0(&e->unkA0[5]) & 4) func_0024ae00(&e->unkA0[5]);
        if (!r) e->unkA24++;
        break;
    case 3:
        e->unkA24 = 0;
        break;
    }
    if (e->unk0 == 0) {
        if (e->unkA28 == 0) {
            if (r == 1 && e->unkA1C > 0.0f && !func_001375d8((s32)e->unk4)) {
                if ((D_002C5958 & 1) == r) {
                    if (D_00651E50.unk4120 == 0) func_0023d148(0);
                    else func_0023d128(0);
                } else {
                    if (D_00651E50.unk4120 == 0) func_0023d148(1);
                    else func_0023d128(1);
                }
            }
            if (D_00651E50.unk4120 != 0) {
                if (r == 0 || e->unkA1C == 0.0f || func_001375d8((s32)e->unk4) == 1) func_0023d1a0();
            }
        } else {
            if (D_00651E50.unk4120 != 0) func_0023d1a0();
        }
    }
    if (e->unk0 == 4) {
        if (D_00651E50.unk4120 == 0) {
            if (r == 1 && e->unkA1C > 0.0f) func_0023d148(0);
        } else {
            if (r == 0 || e->unkA1C == 0.0f) func_0023d1a0();
        }
    }
    if (e->unk0 == 1 || e->unk0 == 2) {
        func_002409e0(&e->unk520);
        if (e->unk4->unk6C->unk3C <= 0) func_00240978(e->unk4);
        if (e->unk4->unk6C->unk3C > 0) func_002409b0(e->unk4);
        func_002409e0(&e->unk780);
    }
    if (e->unk0 == 3) func_002409e0(&e->unkAA0);
    if (e->unk0 == 0) e->unkA2C = func_00240b28(e);
}

void func_00240fa0(Gauge *o) {
    D_00651D64 = D_00351E10;
    D_00651D60 = D_00351E10 + 1;
    func_00240b68(o);
    D_00651D60 = func_0023ee80(o, D_00651D60);
    D_00651D60 = func_0023dfc0(o, D_00651D60);
    D_00651D60->lo = 0x1000000000008001;
    D_00651D60->hi = 14;
    D_00651D60++;
    D_00651D60->lo = o->unk70->tb.unk18;
    D_00651D60->hi = 6;
    D_00651D60++;
    D_00651D60 = func_0023f920(o, D_00651D60);
    D_00651D60 = func_0023f688(o, D_00651D60);
    D_00651D60 = func_0023dfd8(o, D_00651D60);
    D_00651D60 = func_00240400(o, D_00651D60);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}

void func_002410b8(Gauge *o) {
    s32 a[4];
    s32 b[2];
    QW **bp = &D_00651D64;
    QW **pp = &D_00651D60;
    QW *q;
    *bp = D_00351E10;
    *pp = D_00351E10 + 1;
    func_00240b68(o);
    *pp = func_0023ee80(o, *pp);
    *pp = func_0023dfc0(o, *pp);
    (*pp)->lo = 0x1000000000008001;
    (*pp)->hi = 14;
    (*pp)++;
    (*pp)->lo = o->unk70->tb.unk18;
    (*pp)->hi = 6;
    (*pp)++;
    *pp = func_00240118(o, *pp);
    if (o->unkA8C) *pp = func_002403d0(o, *pp);
    q = *pp;
    *pp = q + 1;
    *pp = func_00237008(0x42, 0x8000000048, q + 1);
    func_00236fd8(q, *pp);
    func_0023d528(o, a, b);
    q = func_00240ae0(&o->unkAA0, b[0], b[1], *pp, o->unkA1C);
    *pp = q + 1;
    *pp = func_00237008(0x42, 0x8000000044, q + 1);
    func_00236fd8(q, *pp);
    func_00237018(*bp, *pp - *bp, 1);
}

/* func_00241260 calls func_00240ae0 with the f32 before the packet pointer:
 * with the QW * last, the a3 load is emitted after the $f12 load and lands
 * in the jal slot. */
#ifdef KH1_PS2
#define AE0_F(f, x, y, a, q) ((QW *(*)(GFade *, s32, s32, f32, QW *))func_00240ae0)(f, x, y, a, q)
#else
#define AE0_F(f, x, y, a, q) func_00240ae0(f, x, y, q, a)
#endif

void func_00241260(Gauge *o) {
    s32 a[4];
    s32 b[2];
    QW *q;
    QW *p = D_00351E10;
    D_00651D64 = p;
    D_00651D60 = p + 1;
    func_00240b68(o);
    D_00651D60 = func_0023ee80(o, D_00651D60);
    D_00651D60 = func_0023dfc0(o, D_00651D60);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
    D_00651D64 = p;
    { QW *t = p + 1; u64 lo = 0x1000000000008001; t->hi = 14; t->lo = lo; }
    p += 2;
    D_00651D60 = p;
    q = D_00651D60;
    q->lo = o->unk70->tb.unk18;
    D_00651D60->hi = 6;
    D_00651D60++;
    if (o->unkA18) D_00651D60 = func_0023f920(o, D_00651D60);
    D_00651D60 = func_0023f688(o, D_00651D60);
    if (o->unk0 == 0 && o->unk4->unk130->unk4C == 0 && o->unkA18) D_00651D60 = func_0023fd58(o, D_00651D60);
    D_00651D60 = func_0023dfd8(o, D_00651D60);
    if (o->unk0 == 1 || o->unk0 == 2) {
        func_0023d528(o, a, b);
        q = D_00651D60;
        D_00651D60 = q + 1;
        D_00651D60 = func_00237008(0x42, 0x8000000048, q + 1);
        func_00236fd8(q, D_00651D60);
        D_00651D60 = AE0_F(&o->unk520, b[0], b[1], o->unkA1C, D_00651D60);
        q = AE0_F(&o->unk780, b[0], b[1], o->unkA1C, D_00651D60);
        D_00651D60 = q + 1;
        D_00651D60 = func_00237008(0x42, 0x8000000044, q + 1);
        func_00236fd8(q, D_00651D60);
    }
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}

void func_002414a8(s32 i, s32 a) {
    Gauge *e = &D_00651E70[i];
    switch (a) {
    case 0:
        e->unkA1C = 1.0f;
        e->unkA20 = -0.0999999940395355224609375f;
        break;
    case 1:
        e->unkA20 = 0.0999999940395355224609375f;
        e->unkA1C = 0.0f;
        break;
    case 2:
        e->unkA1C = 1.0f;
        e->unkA20 = 0.0f;
        break;
    case 3:
        e->unkA20 = 0.0f;
        e->unkA1C = 0.0f;
        break;
    }
}

void func_002415f0(Gauge *o) {
    s32 a[4];
    s32 b[2];
    s32 x, y;
    D_00651D64 = D_00351E10;
    D_00651D60 = D_00351E10 + 1;
    func_0023d528(o, a, b);
    x = b[0];
    y = b[1];
    func_0023d698(2);
    D_00651D60 = func_0023d700(o->unkA84, D_00426940, x, y, D_00651D60, o->unkA1C);
    func_00237018(D_00651D64, D_00651D60 - D_00651D64, 1);
}

void func_00242c08(GActor *o, s32 idx, s32 *pos, f32 alpha);
void func_00241a38(s32);
QA D_00651C00 ALIGNED(64);

s32 func_002416a8(void) {
    s32 t[4];
    s32 i;
    f32 a, b;
    Gauge *e;
    func_00241560();
    if (D_00651E50.unk4124 == 0 && ((F2C5958 *)&D_002C5958)->b3 == 1) {
        func_002414a8(0, 3);
        func_002414a8(1, 3);
        func_002414a8(2, 3);
    } else if (D_00651E50.unk4124 == 1 && !((F2C5958 *)&D_002C5958)->b3) {
        func_002414a8(0, 2);
        func_002414a8(1, 2);
        func_002414a8(2, 2);
        func_00241a38(0);
        func_00241a38(1);
        func_00241a38(2);
    }
    D_00651E50.unk4124 = ((F2C5958 *)&D_002C5958)->b3;
    if (D_00651E50.unk4124) {
        func_0023d1a0();
        return 0;
    }
    func_002370c8(&D_00651C00);
    D_00651C00.unkE0 = 5;
    D_00651C00.unk60 = 0x30003;
    func_00237018(&D_00651C00, 22, 1);
    for (i = 0; i < 5; i++) {
        if (D_00651E50.used[i] == 0) continue;
        e = &D_00651E50.ent[i];
        if (e->unk0 == 4) {
            func_0023d698(0);
            func_00240fa0(e);
            func_002415f0(e);
        } else if (e->unk0 == 3) {
            a = *e->unkA88;
            func_00249950(e->unkA88, 0.0f, 65000.0f);
            if (e->unkA8C) {
                b = *e->unkA8C;
                func_00249950(e->unkA8C, 0.0f, 65000.0f);
            }
            func_0023d698(1);
            func_002410b8(e);
            func_00242c08(e->unk4, 0, e->unk80, e->unkA1C);
            *e->unkA88 = a;
            if (e->unkA8C) *e->unkA8C = b;
        } else {
            func_0023d698(0);
            func_00241260(e);
            if (e->unk0 == 0) {
                func_00242c08(e->unk4, e->unkA2C, e->unk80, e->unkA1C);
            } else {
                func_00249820(t, e->unk80);
                t[1]--;
                func_00242c08(e->unk4, 0, t, e->unkA1C);
            }
        }
    }
    return 0;
}

void func_00241a38(s32 i) {
    Gauge *e;
    GStat *p;
    s32 a;
    u16 b;
    if (D_00651E50.used[i] == 0) return;
    e = &D_00651E50.ent[i];
    if (e->unk0 == 4) return;
    if (e->unk0 == 3) return;
    p = e->unk4->unk6C;
    a = p->unk44;
    b = p->unkBE;
    e->unk9E0 = a;
    e->unk9E4 = a * 0.5235987f;
    func_002492d0(e->unk9EC, 0.0f, 0.0f, 0.0f, 128.0f);
    e->unk9FC = b;
    e->unkA00 = b * 0.017453289f;
    func_002492d0(e->unkA08, 0.0f, 0.0f, 0.0f, 128.0f);
}

void func_00241c60(s32 b, s32 i) {
    Gauge *e;
    if (b == 0 && i != 4) {
        D_00651E50.used[i] = 0;
        return;
    }
    e = func_00241b60(i, b);
    if (i == 0) {
        func_0023d1a0();
        func_00242bd0();
    }
    if (i == 4) {
        e->unk9E0 = D_00454A20.unk0;
        e->unk9E4 = D_00454A20.unk0 * 0.5235987f;
        func_002492d0(e->unk9EC, 0.0f, 0.0f, 0.0f, 128.0f);
        func_0023cfe8(&e->unkA34, D_00454A20.mode, &D_00451040);
    } else {
        func_00241a38(i);
        e->unkA2C = 0;
        e->unkA30 = 0;
    }
}

#define BASE(B) (b = &B, (UiSpr *)((u8 *)b + b->off))

/* rodata: jump table jtbl_004916D0 */
void func_00241d60(void) {
    s32 i, j;
    Gauge *s;
    UiSpr *base, *src;
    Blob *b;

    for (i = 0; i < 5; i++) {
        s = &D_00651E70[i];
        switch (i) {
        case 0:
            base = BASE(D_0044A830);
            s->unk24 = 6;
            for (j = 0; j < s->unk24; j++) s->unk8[j] = base + D_00454430[j];
            s->unk44 = 2;
            for (j = 0; j < s->unk44; j++) s->unk3C[j] = base + D_004544C0[j];
            s->unk68 = 8;
            for (j = 0; j < s->unk68; j++) s->unk48[j] = base + D_004544D8[j];
            s->unk38 = 4;
            for (j = 0; j < s->unk38; j++) s->unk28[j] = base + D_00454488[j];
            s->unk6C = D_00426880;
            s->unk70 = D_004268E0;
            s->unk90 = (void *)D_00454730;
            base = BASE(D_0044DFD0);
            s->unkA0[0] = base[3];
            s->unkA0[1] = base[4];
            s->unkA0[2] = base[0];
            s->unkA0[3] = base[1];
            s->unkA0[4] = base[2];
            base = BASE(D_0044F380);
            s->unkA0[5] = base[0];
            break;
        case 1:
        case 2:
            base = BASE(D_0044C5A0);
            s->unk24 = 1;
            for (j = 0; j < s->unk24; j++) s->unk8[j] = base + D_00454448[j];
            s->unk44 = 2;
            for (j = 0; j < s->unk44; j++) s->unk3C[j] = base + D_004544C8[j];
            s->unk68 = 8;
            for (j = 0; j < s->unk68; j++) s->unk48[j] = base + D_004544F8[j];
            s->unk38 = 1;
            for (j = 0; j < s->unk38; j++) s->unk28[j] = base + D_00454498[j];
            s->unk6C = &D_004268B0;
            s->unk70 = D_004268E0;
            s->unk90 = (void *)D_00454780;
            s->unk520.unk10 = base[26];
            s->unk520.unkD0 = base[27];
            s->unk520.unk190 = base[28];
            s->unk780.unk10 = base[29];
            s->unk780.unkD0 = base[30];
            s->unk780.unk190 = base[31];
            base = BASE(D_0044DFD0);
            s->unkA0[0] = base[8];
            s->unkA0[1] = base[9];
            s->unkA0[2] = base[5];
            s->unkA0[3] = base[6];
            s->unkA0[4] = base[7];
            base = BASE(D_0044F380);
            s->unkA0[5] = base[0];
            break;
        case 3:
            base = BASE(D_0044F4D0);
            s->unk24 = 6;
            for (j = 0; j < s->unk24; j++) s->unk8[j] = base + D_00454450[j];
            s->unk68 = 8;
            for (j = 0; j < s->unk68; j++) s->unk48[j] = base + D_00454518[j];
            s->unk38 = 4;
            for (j = 0; j < s->unk38; j++) s->unk28[j] = base + D_004544A0[j];
            s->unk6C = D_00426880;
            s->unk70 = D_00426910;
            s->unk90 = (void *)D_004547C0;
            s->unkAA0.unk10 = base[32];
            s->unkAA0.unkD0 = base[33];
            s->unkAA0.unk190 = base[34];
            break;
        case 4:
            base = BASE(D_00451040);
            s->unk24 = 7;
            for (j = 0; j < s->unk24; j++) s->unk8[j] = base + D_00454468[j];
            s->unk38 = 4;
            for (j = 0; j < s->unk38; j++) s->unk28[j] = base + D_004544B0[j];
            s->unk68 = 8;
            for (j = 0; j < s->unk68; j++) s->unk48[j] = base + D_00454538[j];
            s->unk44 = 2;
            for (j = 0; j < s->unk44; j++) s->unk3C[j] = base + D_004544D0[j];
            s->unkA84 = &base[68];
            s->unk6C = D_00426880;
            s->unk70 = D_004268E0;
            s->unk90 = (void *)D_00454730;
            base = BASE(D_0044DFD0);
            s->unkA0[0] = base[3];
            s->unkA0[1] = base[4];
            s->unkA0[2] = base[0];
            s->unkA0[3] = base[1];
            s->unkA0[4] = base[2];
            base = BASE(D_0044F380);
            s->unkA0[5] = base[0];
            break;
        }
    }
}

void func_00242c08(GActor *o, s32 idx, s32 *pos, f32 alpha) {
    GImg *t = o->unk140;
    QW *buf;
    QW *r;
    QW *top;
    QW *pk;
    if (t == 0) return;
    buf = func_00122048(0, 16);
    r = func_0011fbb0(0x3C00, 0, 0, 0, 0, 16, 16, 64, (u8 *)t + 16, buf);
    pk = func_0011fbb0(0x3A00, 4, 19, 0, 0, t->w, t->h, t->w * t->h / 16, (u8 *)t + 0x410, r);
    top = pk++;
    pk->lo = 0x80AB400000008001ULL;
    pk->hi = 0x53531EEE;
    pk++;
    pk = func_0011fb38(63, 0, pk);
    pk = func_0011fb38(6, 0x20078005A1313A00ULL, pk);
    pk = func_0011fb38(20, 0, pk);
    ((I4b *)pk)->z = ((I4b *)pk)->y = ((I4b *)pk)->x = 128;
    ((I4b *)pk)->w = (u32)(alpha * 128.0f);
    pk++;
    ((I4b *)pk)->x = (t->h * idx) << 4;
    ((I4b *)pk)->y = 0;
    pk++;
    ((I4b *)pk)->x = pos[0] - ((t->h / 2) << 4);
    ((I4b *)pk)->y = pos[1] - ((t->h / 2) << 4);
    ((I4b *)pk)->z = 0;
    ((I4b *)pk)->w = 0x8000;
    pk++;
    ((I4b *)pk)->x = (t->h * (idx + 1)) << 4;
    ((I4b *)pk)->y = t->h << 4;
    pk++;
    ((I4b *)pk)->x = pos[0] + ((t->h / 2) << 4);
    ((I4b *)pk)->y = pos[1] + ((t->h / 2) << 4);
    ((I4b *)pk)->z = 0;
    ((I4b *)pk)->w = 0;
    pk++;
    func_0011fb78(top, 7, pk);
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), (void *)(((u32)buf & 0x0FFFFFFF) | 0x80000000));
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_00242ef8(GActor *o, s32 n, s32 a2, s32 *pos, s32 *col) {
    GImg *im = o->unk140;
    I4b *buf, *p, *q;
    s32 d;
    if (im == NULL) return;
    q = func_00122048(0, 16);
    buf = q;
    q = func_0011fbb0(0x3C00, 0, 0, 0, 0, 16, 16, 64, im->clut, q);
    q = func_0011fbb0(0x3A00, 4, 19, 0, 0, im->w, im->h, im->w * im->h / 16, im->img, q);
    p = q;
    q++;
    *(u64 *)&q->x = 0x80AB400000008001;
    *(u64 *)&q->z = 0x53531EEE;
    q = func_0011fb38(63, 0, q + 1);
    q = func_0011fb38(6, 0x20078005A1313A00, q);
    q = func_0011fb38(20, 0, q);
    q->x = col[0];
    q->y = col[1];
    q->z = col[2];
    q->w = col[3];
    d = n / 2 * 16;
    q++;
    q->x = 0;
    q->y = 0;
    q++;
    q->x = pos[0] - d;
    q->y = pos[1] - d;
    q->w = 0x8000;
    q->z = 0;
    q++;
    q->x = im->h * 16;
    q->y = im->h * 16;
    q++;
    q->x = pos[0] + d;
    q->y = pos[1] + d;
    q->z = 0;
    q->w = 0;
    func_0011fb78(p, 7, q + 1);
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), (void *)(((u32)buf & 0x0FFFFFFF) | 0x80000000));
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

