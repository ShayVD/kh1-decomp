/* 0x00230000-0x0024FFFF game code by hand (batch 74). */
#include "common.h"

typedef struct Pk { struct Pk *next; s32 type; } Pk;
typedef struct { Pk *head; s32 pad; } Bk;
typedef struct { s32 bits; Bk *tbl; } Ht;
s32 *func_002378c8(Pk *, s32 *, s32);
s32 *func_00237790(Pk *, s32 *, s32);
s32 *func_00237d48(Pk *, s32 *, s32);
s32 *func_00237ec0(Pk *, s32 *, s32);
s32 *func_00266c08(s32);
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
void func_00266f38(s32 *, s32 *);

void func_00237f20(Ht *h, s32 *b0, s32 *b1, s32 a3, s32 a4) {
    s32 *buf = b0;
    s32 n = 1 << h->bits;
    Bk *bk = h->tbl;
    s32 *r, *q;
    Pk *p;
    s32 i;
    for (i = 0; i < n; i++, bk++) {
        if (bk->head != 0) {
            p = bk->head;
            do {
                r = buf;
                if (p->type == 2) r = func_002378c8(p, buf, a4);
                else if (p->type == 1) r = func_00237790(p, buf, a4);
                else if (p->type == 3) r = func_00237d48(p, buf, a4);
                else if (p->type == 4) r = func_00237ec0(p, buf, 0);
                if (r != buf) {
                    *r |= 0x70000000;
                    q = func_00266c08(2);
                    *q |= 0x40;
                    FlushCache(0);
                    sceGsSyncPath(0, 0);
                    func_00266f38(q, buf);
                    buf = (buf == b0) ? b1 : b0;
                }
                if (p->next == 0) break;
                p = p->next;
            } while (p != 0);
        }
    }
    sceGsSyncPath(0, 0);
}

typedef struct { s32 x, y, z, w; } I4b;
typedef struct { u8 pad[0x60]; s32 c[4][4]; I4b p[4]; } Spr6;
extern Spr6 D_00648900;
extern s32 D_006488F0;
extern f32 D_00650DD0;
extern f32 D_00650DD4;
void func_0024aa48(void *, Spr6 *, void *);
s32 func_002388b8(Spr6 *, s32, s32);

void func_00239630(void *a0, void *a1, s32 dx, s32 dy, f32 s) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239860(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 *src, s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

void func_00239b90(void *a0, void *a1, s32 dx, s32 dy, f32 s, s32 scale, s32 (*src)[4], s32 all) {
    s32 i, j;
    s32 *q;
    func_0024aa48(a0, &D_00648900, a1);
    for (i = 0; i < 4; i++) {
        q = &D_00648900.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (all || j != 3) D_00648900.c[i][j] = src[i][j];
            if (scale) D_00648900.c[i][j] = D_00648900.c[i][j] * s;
        }
    }
    for (i = 0; i < 4; i++) {
        D_00648900.c[i][3] = D_00648900.c[i][3] * D_00650DD4;
    }
    D_006488F0 = func_002388b8(&D_00648900, 1, D_006488F0);
}

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
Q D_00648630 ALIGNED(16);
extern u8 D_00351E10[];
extern u8 *D_006488F4;
typedef struct { u8 pad[0x1C4]; s32 unk1C4; } Obj1C4;
void func_002370c8(void *);
void func_00237018(void *, s32, s32);
void func_0023bb98(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);
void func_00239e30(s32, s32, s32, s32, Obj1C4 *, s32, s32, f32);

void func_0023a318(s32 a0, s32 a1, s32 a2, s32 a3, Obj1C4 *o, s32 a5, s32 a6, f32 f) {
    func_002370c8(&D_00648630);
    D_00648630.unkE0 = 5;
    D_00648630.unk60 = 0x30003;
    func_00237018(&D_00648630, 0x16, 1);
    D_006488F4 = D_00351E10;
    *(u8 **)&D_006488F0 = D_00351E10 + 0x10;
    if (a0 == 0 && o->unk1C4 == 0) {
        func_0023bb98(0, a1, a2, a3, o, a5, a6, f);
    } else {
        func_00239e30(a0, a1, a2, a3, o, a5, a6, f);
    }
    if (f != 0.0f) {
        func_00237018(D_006488F4, (*(u8 **)&D_006488F0 - D_006488F4) >> 4, 1);
    }
}

typedef struct { s32 unk0; u32 unk4; u8 pad8[0xC]; u8 unk14[3]; } Btn;
extern u8 D_0064FD60[];
extern u8 D_00426820[];
extern u8 D_004267F0[];
void func_0024ac08(void *, s32 *);
void func_00239558(s32, s32, s32, s32);

void func_0023a490(s32 a0, Btn *b, s32 x, s32 y, f32 f) {
    s32 pos[2];
    s32 i, k;
    u8 *p;
    D_00650DD4 = D_00650DD0 = f;
    func_00239630(D_0064FD60, D_00426820, x, y, 1.0f);
    func_00239630(D_0064FD60 + 192, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 384, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 576, D_004267F0, x, y, 1.0f);
    func_00239630(D_0064FD60 + 768, D_004267F0, x, y, 1.0f);
    func_0024ac08(D_0064FD60, pos);
    for (k = 20, i = 0, p = b->unk14; i < 3; i++) {
        func_00239558(*p, x + pos[0], y + k + pos[1], (b->unk4 & (1 << i)) ? 115 : 230);
        p++;
        k += 22;
    }
}


typedef struct { f32 x, y, z, w; } __attribute__((aligned(16))) V4;
typedef struct { s32 x, y, z, w; } __attribute__((aligned(16))) I4;
typedef struct { u8 pad0[4]; f32 t; u8 pad8[8]; u8 sub[0xC8]; s32 d8[2]; } Ob;
extern Spr6 D_00651210;
extern s32 D_00651200;
extern f32 D_002BBDFC;
extern u8 D_002E26C0[];
extern u8 D_00426850[];
s32 func_00122ff8(s32);
void func_0024ae00(void *);
void func_0024af00(void *);
void func_0012ec60(s32, s32, V4 *);
s32 func_00249580(V4 *);
f32 func_00237a48(I4 *, void *, V4 *, s32);
void func_00249558(I4 *, I4 *);

s32 func_0023c270(Ob *o) {
    I4 sc;
    s32 r[4];
    V4 v;
    s32 dx, dy, i;
    s32 *q;
    s32 *d = o->d8;
    if (func_00122ff8(d[0]) == 0) return 1;
    if (o->t == 0.0f) func_0024ae00(o->sub);
    o->t += D_002BBDFC;
    func_0012ec60(d[0], d[1], &v);
    if (func_00249580(&v)) return 0;
    func_00237a48(&sc, D_002E26C0, &v, 1);
    func_0024aa48(o->sub, &D_00651210, D_00426850);
    func_00249558(&sc, &sc);
    dx = sc.x;
    dy = sc.y;
    func_0024ac08(o->sub, r);
    dx -= r[2] / 2;
    dy -= r[3] / 2;
    for (i = 0; i < 4; i++) {
        q = &D_00651210.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    D_00651200 = func_002388b8(&D_00651210, 1, D_00651200);
    func_0024af00(o->sub);
    return 0;
}

extern void *D_006512F0;
extern void *D_006512F4;
extern void *D_006512F8;
extern void *D_006512FC;

void func_0023c5c8(s32 *d, s32 kind, s32 show) {
    I4 sc;
    s32 r[4];
    V4 v;
    s32 dx, dy, i;
    s32 *q;
    void *s = 0;
    if (func_00122ff8(d[0]) == 0) return;
    func_0012ec60(d[0], d[1], &v);
    if (func_00249580(&v)) return;
    func_00237a48(&sc, D_002E26C0, &v, 1);
    switch (kind) {
    case 1: s = D_006512F0; break;
    case 2: s = D_006512F8; break;
    case 3: s = D_006512F4; break;
    case 4: s = D_006512FC; break;
    }
    func_00249558(&sc, &sc);
    dx = sc.x;
    dy = sc.y;
    func_0024ac08(s, r);
    dx -= r[2] / 2;
    dy -= r[3] / 2;
    if (show) func_0024ae00(s);
    func_0024aa48(s, &D_00651210, D_00426850);
    for (i = 0; i < 4; i++) {
        q = &D_00651210.p[i].y;
        q[-1] += dx * 16;
        q[0] += dy * 16;
    }
    D_00651200 = func_002388b8(&D_00651210, 1, D_00651200);
    func_0024af00(s);
}

Q D_006510A0 ALIGNED(32);
extern u8 *D_00651204;
extern void *D_00651BE8[];
extern void *D_00651BD8[];
typedef struct { s32 unk0; f32 unk4; } Ob4;
s32 func_002485f0(void);
void func_0023ca48(void *, void *, s32, s32, f32);

void func_0023cb30(Ob4 *o) {
    s32 c = 24;
    s32 i;
    if (func_002485f0() & 1) c = 65;
    if (func_002485f0() & 2) c = 80;
    func_002370c8(&D_006510A0);
    D_006510A0.unkE0 = 5;
    D_006510A0.unk60 = 0x30003;
    func_00237018(&D_006510A0, 0x16, 1);
    D_00651204 = D_00351E10;
    *(u8 **)&D_00651200 = D_00351E10 + 0x10;
    for (i = 0; i < 3; i++) func_0023ca48(D_00651BE8[i], D_00426820, 16, c, o->unk4);
    for (i = 0; i < 3; i++) func_0023ca48(D_00651BD8[i], D_004267F0, 16, c, o->unk4);
    func_00237018(D_00651204, (*(u8 **)&D_00651200 - D_00651204) >> 4, 1);
}

void func_0023cc80(Ob4 *o) {
    s32 i;
    switch (o->unk0) {
    case 1:
        o->unk4 = 1.0f;
        for (i = 0; i < 3; i++) func_0024ae00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024ae00(D_00651BE8[i]);
        o->unk0++;
        break;
    case 2:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        break;
    case 3:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        o->unk4 = 1.0f;
        o->unk0++;
        break;
    case 4:
        for (i = 0; i < 3; i++) func_0024af00(D_00651BD8[i]);
        for (i = 0; i < 3; i++) func_0024af00(D_00651BE8[i]);
        o->unk4 -= D_002BBDFC * 0.16666666f;
        if (o->unk4 <= 0.0f) {
            o->unk4 = 0.0f;
            o->unk0 = 0;
        }
        break;
    }
    func_0023cb30(o);
}

typedef union { u64 x; struct { u64 lo:20; u64 b:6; u64 mid:30; u64 c:5; u64 d:3; } f; } Tag;
typedef struct { u64 tag; u64 n0; u64 tag2; u64 n1; I4b uv[4]; s32 c[4][4]; I4b p[4]; } LSpr;
typedef struct { u8 pad[0x18]; u64 tag; } TObj;

void func_0023d7e8(s32 a0, s32 (*pos)[4], s32 (*uv)[4], s32 (*col)[4], TObj *o, s32 buf) {
    LSpr s;
    Tag t;
    s32 i, j;
    t.x = o->tag;
    t.f.c = 0;
    t.f.d = 1;
    t.f.b = 0x13;
    s.tag = t.x;
    s.n0 = 6;
    s.tag2 = o->tag;
    s.n1 = 6;
    s.p[0].x = pos[0][0] * 16 + 0x7000;
    s.p[0].y = pos[0][1] * 16 + 0x7400;
    s.p[0].z = -256;
    s.p[0].w = 0;
    s.p[1].x = pos[1][0] * 16 + 0x7000;
    s.p[1].y = pos[1][1] * 16 + 0x7400;
    s.p[1].z = -256;
    s.p[1].w = 0;
    s.p[2].x = pos[2][0] * 16 + 0x7000;
    s.p[2].y = pos[2][1] * 16 + 0x7400;
    s.p[2].z = -256;
    s.p[2].w = 0;
    s.p[3].x = pos[3][0] * 16 + 0x7000;
    s.p[3].y = pos[3][1] * 16 + 0x7400;
    s.p[3].z = -256;
    s.p[3].w = 0;
    s.uv[0].x = uv[0][0] * 16 + 8;
    s.uv[0].y = uv[0][1] * 16 + 8;
    s.uv[1].x = uv[1][0] * 16 + 8;
    s.uv[1].y = uv[1][1] * 16 + 24;
    s.uv[2].x = uv[2][0] * 16 + 24;
    s.uv[2].y = uv[2][1] * 16 + 8;
    s.uv[3].x = uv[3][0] * 16 + 24;
    s.uv[3].y = uv[3][1] * 16 + 24;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            s.c[i][j] = col[i][j];
        }
    }
    func_002388b8(&s, 1, buf);
}

typedef struct { u8 pad[0x40]; s32 unk40; s32 unk44; s32 unk48; } St6C;
typedef struct { u8 pad[0x6C]; St6C *unk6C; } Ow;
typedef struct { s32 r, g, b, a; } __attribute__((aligned(16))) Col;
typedef struct { s32 a, b, c, d; u8 pad[0xC0 - 0x10]; } __attribute__((aligned(8))) Big;
typedef struct {
    s32 unk0;
    Ow *unk4;
    s32 unk8[7];
    s32 unk24;
    s32 unk28[4];
    s32 unk38;
    void *unk3C;
    void *unk40;
    u8 pad44[0x4C - 0x44];
    void *unk4C;
    u8 pad50[0x5C - 0x50];
    Big *unk5C;
    u8 pad60[4];
    Big *unk64;
    u8 pad68[4];
    TObj *unk6C;
    void *unk70;
    u8 pad74[0xC];
    u8 unk80[0x10];
    u8 *unk90;
    u8 pad94[0x9E0 - 0x94];
    s32 unk9E0;
    f32 unk9E4;
    f32 unk9E8;
    u8 unk9EC[0xA18 - 0x9EC];
    s32 unkA18;
    f32 unkA1C;
    u8 padA20[0xA90 - 0xA20];
    f32 *unkA90;
    f32 *unkA94;
} Obj;
typedef struct { s32 unk0, unk4, unk8, unkC; } S16;
extern S16 D_00454A20;
extern Col D_004915A0;
void func_0023d528(Obj *, s32 *, s32 *);
s32 func_0023d700(void *, void *, s32, s32, s32, f32);
s32 func_0023e160(void *, void *, Col *, s32, f32, f32, f32);

s32 func_0023dfd8(Obj *g, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    s32 x, y;
    s32 f1 = 0, f2 = 0;
    f32 a;
    if (g->unk0 == 4) {
        a = D_00454A20.unk0 * 0.52359867095947265625f;
        if (a > 1.57079616f) f1 = 1;
    } else if (g->unk0 == 3) {
        a = g->unk4->unk6C->unk40 * 0.000174532895471f;
        if (a > 1.57079616f) f1 = 1;
    } else {
        a = g->unk4->unk6C->unk48 * 0.52359867095947265625f;
        if (a > 1.57079616f) f1 = 1;
    }
    if (a > 3.1415922641754150391f) f2 = 1;
    if (!f1 && !f2) return buf;
    func_0023d528(g, p1, p2);
    x = p2[0];
    y = p2[1];
    if (f1) buf = func_0023d700(g->unk3C, g->unk6C, x, y, buf, g->unkA1C);
    if (f2) buf = func_0023d700(g->unk40, g->unk6C, x, y, buf, g->unkA1C);
    return buf;
}

s32 func_0023e330(Obj *e, s32 buf) {
    s32 p1[4];
    s32 p2[4];
    Big big;
    Col q = D_004915A0;
    f32 v;
    s32 i, n, t, rem;
    f32 fr;
    v = *e->unkA94 * 0.0001745328918332234025001526f;
    if (v > 4.712388038635254f) v = 4.712388038635254f;
    buf = func_0023e160(e->unk80, e->unk90 + 0x10, &q, buf, 0.0f, v, e->unkA1C);
    v = *e->unkA94 * 0.0001745328918332234025001526f;
    if (v <= 4.712388038635254f) return buf;
    func_0023d528(e, p1, p2);
    t = *e->unkA94 - 27000.0f;
    n = t / 3000;
    for (i = 0; i < n; i++) {
        buf = func_0023d700(e->unk5C, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
        p2[0] -= 26;
    }
    rem = t % 3000;
    if (rem != 0) {
        fr = rem / 3000.0f;
        p2[0] = p2[0] + (1.0f - fr) * 26.0f;
        big = *e->unk5C;
        big.c = big.c * (fr + 0.0625f);
        buf = func_0023d700(&big, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
    } else {
        p2[0] += 26;
    }
    e->unk64->a = 414;
    return func_0023d700(e->unk64, e->unk6C, p2[0], p2[1], buf, e->unkA1C);
}

s32 func_0023f7d8(Obj *e, s32 buf) {
    s32 p1[4]; s32 p2[4]; s32 n, d, i, step; f32 k;
    if (e->unk0 == 4) { d = 1; k = 0.52359867095947265625f; n = D_00454A20.unk0; }
    else { k = 0.52359867095947265625f; d = 1; n = e->unk4->unk6C->unk44; if (n >= 21) n = 20; }
    if (k * n <= 4.712388038635254f) return buf;
    if (e->unk0 == 0 || e->unk0 == 4) step = 26; else step = 17;
    func_0023d528(e, p1, p2);
    p2[0] -= 1;
    n = (n - 9) / d;
    for (i = 0; i < n; i++) { buf = func_0023d700(e->unk4C, e->unk70, p2[0], p2[1], buf, e->unkA1C); p2[0] -= step; }
    return buf;
}

extern f32 D_002BBDFC;
void func_002492d0(void *, f32, f32, f32, f32);
s32 func_002492e8(void *, s32);
s32 func_0023f700(Obj *, s32);
s32 func_0023f920(Obj *e, s32 buf) {
    s32 n; f32 k, a, b, lim;
    if (e->unk0 == 4) { k = 0.52359867095947265625f; n = D_00454A20.unk0; }
    else { k = 0.52359867095947265625f; n = e->unk4->unk6C->unk44; }
    lim = 4.712388038635254f;
    a = k * n; if (lim < a) a = lim;
    b = k * e->unk9E0; if (lim < b) b = lim;
    if (n < e->unk9E0) {
        e->unk9E4 = a; e->unk9E8 = b;
        func_002492d0(e->unk9EC, 128.0f, -12.8f, 0.0f, 128.0f);
    } else if (e->unk9E0 < n) {
        e->unk9E4 = b; e->unk9E8 = a;
        func_002492d0(e->unk9EC, 0.0f, 12.8f, 0.0f, 128.0f);
    }
    if (func_002492e8(e->unk9EC, (s32)D_002BBDFC) == 1) e->unk9E4 = e->unk9E8;
    e->unk9E0 = n;
    if (n == 0) return buf;
    return func_0023f7d8(e, func_0023f700(e, buf));
}

/* needs make: uses rodata (jump table) */
extern s32 D_00454800, D_00454804, D_00454808, D_0045480C;
extern u8 D_00454820[], D_004548A0[], D_00454860[], D_004548E0[];
extern u8 D_00454920[], D_004549A0[], D_00454960[], D_004549E0[];
s32 func_0023da08(Obj *, void *, void *, s32, s32, s32);

s32 func_0023dd48(Obj *g, s32 buf) {
    s32 a, b;
    switch (g->unk0) {
    case 0:
        a = g->unk4->unk6C->unk48 * 30;
        b = g->unk4->unk6C->unk40 * 5;
        if (a >= 271) a = 0;
        if (b >= 271) b = 0;
        if (a != 0 && g->unkA18 != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        break;
    case 1:
    case 2:
        a = g->unk4->unk6C->unk48 * 30;
        b = g->unk4->unk6C->unk40 * 5;
        if (a >= 271) a = 0;
        if (b >= 271) b = 0;
        if (a != 0) buf = func_0023da08(g, D_00454920, D_004549A0, a, D_0045480C, buf);
        if (b != 0) buf = func_0023da08(g, D_00454960, D_004549E0, b, D_00454808, buf);
        break;
    case 3:
        a = 0;
        b = *g->unkA90 / 100.0f;
        if (b >= 271) b = 0;
        if (g->unkA94 != 0) {
            a = *g->unkA94 / 100.0f;
            if (a >= 271) a = 0;
        }
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        if (a != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        break;
    case 4:
        a = D_00454A20.unk8 * 30;
        if (a >= 271) a = 0;
        b = D_00454A20.unkC * 3.75f;
        if (b >= 271) b = 0;
        if (b != 0) buf = func_0023da08(g, D_00454860, D_004548E0, b, D_00454800, buf);
        if (a != 0) buf = func_0023da08(g, D_00454820, D_004548A0, a, D_00454804, buf);
        break;
    }
    return buf;
}
