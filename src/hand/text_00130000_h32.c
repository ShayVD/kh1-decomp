/* Hand-matched functions near 0x130000 (worker 32). */
#include "common.h"

typedef struct {
    s32 id;
    u32 flags;
    s32 x8;
    u8 pad0c[0x4C - 0xC];
    u16 key;
    u8 pad4e[0x58 - 0x4E];
    u8 x58;
    u8 pad59[0x78 - 0x59];
} W32Rec;

typedef struct {
    u8 pad00[0xC];
    s32 n;
    W32Rec *recs;
    s32 x14;
    s32 x18;
    s32 x1c;
    s32 x20;
    s32 x24;
    s32 x28;
    u8 pad2c[0x30 - 0x2C];
} W32Tbl;

extern W32Tbl D_00525298;
extern W32Tbl D_005252C8;
extern W32Tbl D_005252F8;
extern W32Tbl D_00525328;
extern W32Rec *D_00525354;
extern s32 D_0052535C;
extern void (*D_00525360)(void);

s32 func_001560f8(s32 a, void *b);

void func_00131e40(s32 a) {
    while (D_00525354 < D_00525298.recs + D_00525298.n) {
        if (D_00525354->x58 == D_0052535C && func_001560f8(D_00525354->id, func_00131e40)) {
            D_00525354++;
            return;
        }
        D_00525354++;
    }
    if (D_00525360) D_00525360();
}

W32Rec *func_001320a8(u32 a) {
    W32Rec *r;
    s32 n, i;
    switch ((s32)((a >> 16) & 0xFF)) {
    case 7: r = D_005252F8.recs; n = D_005252F8.n; break;
    case 8: r = D_005252C8.recs; n = D_005252C8.n; break;
    case 12: r = D_00525328.recs; n = D_00525328.n; break;
    default: r = D_00525298.recs; n = D_00525298.n; break;
    }
    if (((a >> 16) & 0xFF) == 1) {
        for (i = 0; i < n; i++, r++) {
            if (r->key == (a & 0xFFFF)) return r;
        }
    } else {
        for (i = 0; i < n; i++, r++) {
            if (r->id == a) return r;
        }
    }
    return 0;
}
typedef struct { s32 x0; s32 off[9]; } W32Hdr;
typedef struct {
    u8 pad00[0x68];
    s32 x68;
    u8 pad6c[0x134 - 0x6C];
    s32 x134;
    s32 x138;
    s32 x13c;
    s32 x140;
    u8 pad144[0x154 - 0x144];
    void *x154;
    s32 x158;
    s32 x15c;
    u8 pad160[0x1D0 - 0x160];
    s32 x1d0;
    s32 x1d4;
    u8 pad1d8[0x4A8 - 0x1D8];
    s32 x4a8;
} W32Obj;
void func_00162070(void *a, s32 *b, s32 *c, s32 *d);
void func_001321a0(s32 *a, W32Hdr *b);
void func_001238c0(W32Obj *o, f32 a, f32 b);
void func_00167f68(s32 a, void *b);
void func_00132260(W32Obj *o, W32Hdr *h, W32Hdr *g) {
    o->x154 = (u8 *)h + h->off[0];
    func_00162070(o->x154, &o->x158, &o->x1d4, &o->x15c);
    func_001321a0(&o->x1d0, g);
    if (h->off[2] - h->off[1] > 0) o->x68 = (s32)h + h->off[1];
    if (h->off[3] - h->off[2] > 0) o->x140 = (s32)h + h->off[2];
    if (h->off[4] - h->off[3] > 0) o->x13c = (s32)h + h->off[3];
    if (h->off[5] - h->off[4] > 0) {
        f32 *v = (f32 *)((u8 *)h + h->off[4]);
        o->x134 = (s32)v;
        func_001238c0(o, v[3], v[2]);
    }
    if (h->off[6] - h->off[5] > 0) o->x138 = (s32)h + h->off[5];
    else o->x138 = 0;
    if (h->off[8] - h->off[7] > 0) o->x4a8 = (s32)h + h->off[7];
    if (g) func_00167f68(o->x15c, (u8 *)g + g->off[0]);
}
void func_00176838(void);
void func_0014f1b8(s32 a);
void func_00168500(s32 a);
s32 func_00142240(s32 a);
void func_00124218(s32 a);
void func_0017d9c8(s32 a);
void func_0017eb88(void);
void func_001252f8(void);
void func_00156c18(s32 a);
void func_001590a8(void);
extern s32 D_002E26A0;
extern f32 D_00304C40;
void func_00132550(void) {
    W32Rec *r;
    s32 i;
    func_00176838();
    func_0014f1b8(D_00525298.x18);
    func_00168500(D_00525298.x24);
    r = D_00525298.recs;
    for (i = 0; i < D_00525298.n; i++, r++) {
        if (!(r->flags & 2) && r->x8 != 0) {
            if (!(r->flags & 0x10000) || func_00142240(r->id) != 1) {
                func_00124218(r->id);
            }
        }
    }
    if (D_00525298.x20) func_0017d9c8(D_00525298.x20);
    if (D_002E26A0) func_0017eb88();
    func_001252f8();
    func_00156c18(D_00525298.x28);
    func_001590a8();
    D_00304C40 = 30.0f;
}

typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    u32 x14;
    void (*x18)(void);
} W32Chan;
extern W32Chan D_00525368[];
extern s32 D_003041F0[][3][3];
void func_001330c8(s32 a);
s32 func_001477c8(s32 a);
void func_001330e8(s32 a, s32 b, s32 key) {
    W32Chan *c = D_00525368;
    s32 i;
    s32 v;
        for (i = 0; i < 7; i++, c++) {
        if (c->x8 == key) break;
    }
    func_001330c8(key);
    c->x4 = key;
    c->xc = func_001477c8(D_003041F0[i][c->x0 - 1][1]);
    c->x10 = D_003041F0[i][c->x0 - 1][2] >= 0 ? func_001477c8(D_003041F0[i][c->x0 - 1][2]) : 0;
    if (c->x18) c->x18();
}
typedef struct {
    u8 pad000[0x170];
    u64 x170;
} W32Sub;
typedef struct {
    u8 pad000[0x148];
    W32Sub *x148;
} W32Obj2;
typedef struct {
    W32Obj2 *a;
    s32 b;
} W32Pair;
void func_001373f8(W32Obj2 *o, f32 f);
s32 func_001332f0(W32Obj2 *a0, W32Obj2 *a1, s32 a2, void *a3, void *a4, s32 a5, s32 a6);
s32 func_001333e0(W32Obj2 *o, s32 i, W32Pair *q) {
    W32Chan *c = &D_00525368[i];
    W32Hdr *h;
    if (c->x0 != 0) {
    if (i == 3 && q->a == o && ((s32)(o->x148->x170 >> 38) & 1)) {
        func_001373f8(o, 0.0f);
    }
    h = (W32Hdr *)c->x4;
    return func_001332f0(o, q->a, q->b, (u8 *)h + h->off[1], (u8 *)h + h->off[0], c->xc, c->x10);
    }
    return 0;
}
