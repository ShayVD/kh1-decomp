#include "common.h"

f32 sinf(f32);
f32 cosf(f32);
typedef struct { u8 pad0[0x6C]; s32 unk6C; u8 pad70[0x10]; s32 unk80; s32 unk84; u8 pad88[0xA1C - 0x88]; f32 unkA1C; } Gda;
s32 func_0023d7e8(s32, s32 (*)[4], s32 (*)[4], s32 (*)[4], s32, s32);

s32 func_0023da08(Gda *g, s32 (*src)[4], s32 (*uv)[4], s32 ang, s32 off, s32 buf) {
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
    bx = (g->unk80 - 0x7000) >> 4;
    by = (g->unk84 - 0x7400) >> 4;
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

typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
typedef struct { s32 a, b, c, d; u8 pad[0xC0 - 0x10]; } __attribute__((aligned(8))) Big;
typedef struct { u8 pad[0x40]; s32 unk40; s32 unk44; s32 unk48; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct {
    s32 unk0;
    Ow *unk4;
    u8 pad8[0x54 - 8];
    Big *unk54;
    Big *unk58;
    u8 pad5C[4];
    Big *unk60;
    u8 pad64[8];
    void *unk6C;
    u8 pad70[0x10];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0xA1C - 0x94];
    f32 unkA1C;
    u8 padA20[0xA90 - 0xA20];
    f32 *unkA90;
} Gb;
extern Col D_004915C0;
extern s32 D_00454A2C;
void func_0023d528(void *, s32 *, s32 *);
s32 func_0023d700(void *, void *, s32, s32, s32, f32);
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

extern Col D_004915B0;

s32 func_0023e5b0(Gb *e, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    Big big;
    Big c;
    Col q = D_004915B0;
    f32 v;
    s32 i, n, t, rem;
    f32 fr;
    v = *e->unkA90 * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90, &q, buf, 0.0f, v, e->unkA1C);
    v = *e->unkA90 * 0.0001745328918332234025001526f;
    if (v <= 4.712388038635254f) return buf;
    func_0023d528(e, p1, p2);
    c = *e->unk58;
    c.a += 26;
    t = *e->unkA90 - 27000.0f;
    n = t / 3000;
    for (i = 0; i < n; i++) {
        if (i == 0) buf = func_0023d700(e->unk54, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        else buf = func_0023d700(&c, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= 26;
    }
    rem = t % 3000;
    if (rem != 0) {
        fr = rem / 3000.0f;
        p2[0] = p2[0] + (1.0f - fr) * 26.0f;
        if (n == 0) big = *e->unk54;
        else big = c;
        big.c = big.c * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += 26;
    }
    e->unk60->a = 414;
    return func_0023d700(e->unk60, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

s32 func_0023e8f0(Gb *e, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    Big big;
    Big c;
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
    buf = func_0023e160(e->unk80, e->unk90, &q, buf, 0.0f, v, e->unkA1C);
    if (th >= n) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26; else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    c = *e->unk58;
    c.a += step;
    t = n - th;
    m = t / d;
    for (i = 0; i < m; i++) {
        if (i == 0) buf = func_0023d700(e->unk54, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        else buf = func_0023d700(&c, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= step;
    }
    rem = t % d;
    if (rem != 0) {
        fr = (f32)rem / (f32)d;
        p2[0] = p2[0] + (f32)step * (1.0f - fr);
        if (m == 0) big = *e->unk54;
        else big = c;
        big.c = big.c * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += step;
    }
    if (e->unk0 == 0 || e->unk0 == 4) e->unk60->a = 414; else e->unk60->a = 380;
    return func_0023d700(e->unk60, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

typedef struct { s32 w, h; u8 pad8[8]; u8 clut[0x400]; u8 img[1]; } Tx;
typedef struct { u8 pad[0x140]; Tx *unk140; } Ow42;
typedef struct { u64 lo, hi; } QW;
typedef struct { s32 x, y, z, w; } V4;
QW *func_00122048(s32, s32);
QW *func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, QW *);
QW *func_0011fb38(s32, u64, QW *);
void func_0011fb78(QW *, s32, QW *);
void FlushCache(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);
void func_001220b8(QW *);

void func_00242c08(Ow42 *o, s32 idx, s32 *pos, f32 alpha) {
    Tx *t = o->unk140;
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
    ((V4 *)pk)->z = ((V4 *)pk)->y = ((V4 *)pk)->x = 128;
    ((V4 *)pk)->w = (u32)(alpha * 128.0f);
    pk++;
    ((V4 *)pk)->x = (t->h * idx) << 4;
    ((V4 *)pk)->y = 0;
    pk++;
    ((V4 *)pk)->x = pos[0] - ((t->h / 2) << 4);
    ((V4 *)pk)->y = pos[1] - ((t->h / 2) << 4);
    ((V4 *)pk)->z = 0;
    ((V4 *)pk)->w = 0x8000;
    pk++;
    ((V4 *)pk)->x = (t->h * (idx + 1)) << 4;
    ((V4 *)pk)->y = t->h << 4;
    pk++;
    ((V4 *)pk)->x = pos[0] + ((t->h / 2) << 4);
    ((V4 *)pk)->y = pos[1] + ((t->h / 2) << 4);
    ((V4 *)pk)->z = 0;
    ((V4 *)pk)->w = 0;
    pk++;
    func_0011fb78(top, 7, pk);
    FlushCache(0);
    func_00266f38(func_00266c08(2), (void *)(((u32)buf & 0x0FFFFFFF) | 0x80000000));
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

typedef struct { u8 pad[0x9C]; s32 unk9C; } Gm;
typedef struct { s32 mode; s32 unk8; f32 unkC; } Sub;
typedef struct {
    s32 state;
    Sub sub;
    s32 cnt;
} S61D0;
extern Gm *D_00656230, *D_00656254, *D_00656278, *D_0065629C;
typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0 - 0x68]; u64 unkE0; } Q;
extern S61D0 D_006561D0;
extern Q D_00655F80;
extern QW *D_006560E4;
extern QW *D_006560E0;
extern QW D_00351E10[];
extern u8 D_004267C0[], D_004267F0[];
void func_002370c8(Q *);
void func_00237018(void *, s32, s32);
void func_0011d768(s32);
void func_00243508(s32, Gm *, void *, void *, s32, s32, s32, s32, f32);

void func_002436c0(s32 arg) {
    s32 f2 = 0, f3 = 0;
    Sub *g = 0;
    if (D_006561D0.state == 0) return;
    func_002370c8(&D_00655F80);
    D_00655F80.unkE0 = 5;
    D_00655F80.unk60 = 0x30003;
    func_00237018(&D_00655F80, 22, 1);
    D_006560E4 = D_00351E10;
    D_006560E0 = D_00351E10 + 1;
    switch (D_006561D0.state) {
    case 1:
        f2 = 1;
        D_006561D0.state = 2;
        if (D_006561D0.sub.mode != 2) func_0011d768(31);
        break;
    case 2:
        break;
    case 3:
        D_006561D0.state = 4;
        f3 = 1;
        break;
    }
    g = &D_006561D0.sub;
    switch (g->mode) {
    case 0:
        if (D_006561D0.state == 2) func_00243508(f2, D_00656230, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        else func_00243508(f3, D_00656278, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        break;
    case 1:
        if (D_006561D0.state == 2) func_00243508(f2, D_00656230, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        else func_00243508(f3, D_0065629C, D_004267C0, D_004267F0, 160, 344, g->unk8, 0, g->unkC);
        break;
    case 2:
        func_00243508(f2, D_00656254, D_004267C0, D_004267F0, 160, 344, g->unk8, 1, g->unkC);
        break;
    }
    if (D_006561D0.state == 2) {
        D_006561D0.cnt++;
        if (D_006561D0.cnt >= 61 || (arg && D_006561D0.cnt >= 21)) D_006561D0.state = 3;
    }
    func_00237018(D_006560E4, D_006560E0 - D_006560E4, 1);
    if (D_006561D0.state == 4) {
        g->unkC -= 0.1428571381f;
        if (g->unkC < 0.0f) g->unkC = 0.0f;
        switch (D_006561D0.sub.mode) {
        case 0:
            if (D_00656278->unk9C & 4) D_006561D0.state++;
            break;
        case 1:
            if (D_0065629C->unk9C & 4) D_006561D0.state++;
            break;
        case 2:
            D_006561D0.state++;
            break;
        }
    }
    if (D_006561D0.state == 5) D_006561D0.state = 0;
}

/* needs make: uses rodata */

typedef struct { s32 x, y, z, w; } V4i;
s32 func_0023d1e0(f32);
f32 tanf(f32);

V4i *func_0023d208(V4i *a, V4i *b, V4i *o, f32 ang) {
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

typedef struct {
    u8 pad0[0xA1C];
    f32 unkA1C;
    u8 padA20[0xA34 - 0xA20];
    struct GP { void *a[5]; Big *b; void *c[4]; void *d[5]; } unkA34;
} Ga;
typedef struct { s32 unk0, unk4, unk8, unkC, mode; f32 scale; s32 barrier; } GW;
extern GW D_00454A20;
extern u8 D_00426880[], D_004268E0[];
void __assert(const char *, s32, const char *);

s32 func_00240400(Ga *e, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    Big c;
    s32 x, y, i;
    struct GP *t = &e->unkA34;
    func_0023d528(e, p1, p2);
    x = p2[0];
    y = p2[1];
    switch (D_00454A20.mode) {
    case 0: break;
    case 1:
        c = *t->b;
        c.c = c.c * D_00454A20.scale;
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
        c.c = c.c * D_00454A20.scale;
        for (i = 0; i < 5; i++) buf = func_0023d700(t->a[i], D_00426880, x, y, buf, e->unkA1C);
        buf = func_0023d700(&c, D_004268E0, x, y, buf, e->unkA1C);
        for (i = 0; i < 3; i++) buf = func_0023d700(t->c[i], D_00426880, x, y, buf, e->unkA1C);
        if (!(D_00454A20.barrier >= 0 && D_00454A20.barrier <= 5)) __assert("ttlib/ui_gauge.c", 2747, "tt_gaugeWorldmap.barrier >= 0 && tt_gaugeWorldmap.barrier <= 5");
        for (i = 0; i < D_00454A20.barrier; i++) buf = func_0023d700(t->d[i], D_00426880, x, y, buf, e->unkA1C);
        break;
    }
    return buf;
}
