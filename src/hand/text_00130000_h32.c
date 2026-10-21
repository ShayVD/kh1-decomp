/* Hand-matched functions near 0x130000 (worker 32). */
#include "common.h"
#include "data/bss_0052.h"

#include "data/types/text_00130000_h32.h"


extern W32Tbl D_00525298;
extern W32Tbl D_005252C8;
extern W32Tbl D_005252F8;
extern W32Tbl D_00525328;
extern W32Rec *D_00525354; /* src/data/bss_0052.c: s32 D_00525354 */
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
extern void *D_002E26A0[3];
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
    if (D_002E26A0[0]) func_0017eb88();
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
extern W32Chan D_00525368[]; /* src/data/bss_0052.c: M2C_UNK D_00525368 */
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
typedef struct {
    u8 pad00[0x70];
    u8 x70;
    u8 pad71[0x74 - 0x71];
} W32SEnt;
typedef struct {
    u8 pad000[4];
    W32SEnt ent[10];
    u8 pad48c[0x492 - 0x48C];
    u8 b492[8];
    u8 pad49a[0x874 - 0x49A];
    s32 x874;
} W32Save;
#include "data/pieces/D_00304BE8.h"
s32 func_001331d8(s32 i, s32 j, void (*cb)(void));
void func_00133550(void);
typedef struct {
    u8 pad00[0x48];
    void (*x48)(s32);
} W32Proc;
W32Proc *func_001208e0(void (*f)(void));
void func_00133578(void (*cb)(s32)) {
    s32 i;
    s32 n = 0;
    s32 j;
    for (i = 0; i < 7; i++) {
        j = ((W32Save *)D_00304BE8)->b492[i];
        if (j > 0) {
            if (func_001331d8(i, j, 0) >= 0) n++;
        }
    }
    if (n > 0) {
        func_001208e0(func_00133550)->x48 = cb;
    } else {
        cb(-1);
    }
}
typedef struct {
    s32 used;
    u8 pad04[0x60 - 0x4];
} W32Slot;
extern W32Slot D_00525A40[32]; /* src/data/bss_0052.c: W32Node D_00525A40[32] */
extern W32E12 D_00526640[32];
void func_00133a88(void);
void func_00133738(void);
s32 func_0011ef38(void (*f)(void));
void func_0011ef10(s32 a, void (*f)(void));
void func_00134718(void) {
    s32 i;
    for (i = 0; i < 32; i++) D_00525A40[i].used = 0;
    if (func_0011ef38(func_00133a88) == 0) func_0011ef10(0x1387E, func_00133a88);
    for (i = 0; i < 32; i++) D_00526640[i].x0 = -1;
    if (func_0011ef38(func_00133738) == 0) func_0011ef10(0xB798, func_00133738);
}
typedef struct {
    u32 flags;
    u8 pad004[0x1C - 0x4];
    f32 x1c;
    u8 pad020[0x60 - 0x20];
    f32 x60;
    u8 pad064[0xA0 - 0x64];
    f32 xa0[4];
    u8 pad0b0[0xD0 - 0xB0];
    f32 xd0[4][4];
    f32 x110[2];
    f32 x118;
    f32 x11c;
    u8 pad120[0x154 - 0x120];
    s32 x154;
    u8 pad158[0x350 - 0x158];
    s32 tgt[4];
    u8 pad360[0x370 - 0x360];
    union {
        u64 x;
        u8 c[4];
    } u370;
    u8 pad378[0x38C - 0x378];
    s32 x38c;
    u8 pad390[0x394 - 0x390];
    s32 x394;
} W32Col;
void func_00135d38(W32Col *o) {
    s32 i;
    if ((s32)(o->u370.x >> 46) & 1) {
        for (i = 0; i < 4; i++) {
            u8 *q = &o->u370.c[i];
            s32 cur = *q;
            s32 d = o->tgt[i] - cur;
            s32 c;
                        if (d >= -4) c = cur + (d < 5 ? d : 4);
            else c = cur - 4;
            *q = c;
        }
    } else {
        for (i = 0; i < 4; i++) o->u370.c[i] = o->tgt[i];
    }
    o->u370.x |= 1ULL << 46;
}
f32 func_0017f440(W32Col *o);
void func_00135df0(W32Col *o, f32 *out) {
    s32 i;
    if ((s32)(o->u370.x >> 52) & 1) {
        for (i = 0; i < 3; i++) out[i] = o->xa0[i] * 128.0f;
    } else {
        for (i = 0; i < 3; i++) out[i] = o->u370.c[i] * o->xa0[i];
    }
    out[3] = o->xa0[3] * 128.0f * o->x60;
    out[3] *= func_0017f440(o);
}
f32 func_00135ca0(f32 a);
void func_00122588(W32Col *o);
void func_00267548(f32 *d, f32 *a, f32 *b);
s32 func_00135bb0(W32Col *o);
void func_00136428(W32Col *o, s32 a, s32 b, f32 *c, f32 f);
void func_00128218(W32Col *o, f32 f);
#include "data/pieces/D_002BC0A8.h"
extern f32 D_002C6450[4];
void func_001368e8(W32Col *o) {
    f32 v[4] __attribute__((aligned(16)));
    f32 k = func_00135ca0(o->x118);
    func_00122588(o);
    func_00135df0(o, v);
    func_00267548(v, v, D_002C6450);
    if (v[3] > 0.0f && func_00135bb0(o) && (o->flags & 1)) {
        if (D_002BC0A8.i & 1) {
            o->u370.x |= 1ULL << 35;
            if (o->x154 == 0) return;
            func_00136428(o, o->x38c, o->x394, v, k);
        }
    }
    if (o->flags & 2) func_00128218(o, v[3] * k * 3.063725307583809e-05f);
}
extern s32 D_002BC128;
extern s32 D_002BC130;
void func_00136ab8(W32Col *o) {
    f32 v[4] __attribute__((aligned(16)));
    f32 k = func_00135ca0(o->x118);
    func_00122588(o);
    func_00135df0(o, v);
    if (v[3] > 0.0f && func_00135bb0(o) && (o->flags & 1)) {
        o->u370.x |= 1ULL << 35;
        if (o->x154 == 0) return;
        func_00136428(o, o->x38c, o->x394, v, k);
    }
    if (D_002BC128 == 1 && D_002BC130 == 5) return;
    if (o->flags & 2) func_00128218(o, v[3] * k * 3.063725307583809e-05f);
}
typedef struct {
    u8 pad00[0x10];
    W32Col *obj;
    void (*cb)(W32Col *o);
} W32Job;
#include "data/pieces/D_002E2700.h"
extern u32 D_002C5958;
void func_00120ef0(f32 *a, void *b, f32 *c);
s32 func_00136bc0(W32Job *j) {
    W32Col *o = j->obj;
    if ((s32)(o->u370.x >> 33) & 1) return 4;
    o->u370.x &= ~(1ULL << 35);
    o->x1c = 1.0f;
    func_00120ef0(o->x110, ((u8 *)&D_002E2700), o->xd0[3]);
    o->x11c = 1.0f;
        if (((s32)(o->u370.x >> 34) & 1) && o->x154 != 0 && !((D_002C5958 >> 6) & 1)) {
        func_00135d38(o);
        j->cb(o);
    }
    return 0;
}
s32 D_0052ABF0[2][32] ALIGNED(16);
extern s32 D_0052ACF0[2];
extern s32 D_0052ACF8;
void func_001337e0(s32 a, s32 b, s32 c);
void func_001374a8(s32 id) {
    s32 i;
    s32 o;
    for (i = 0; i < D_0052ACF0[D_0052ACF8]; i++) {
        if (D_0052ABF0[D_0052ACF8][i] == id) return;
    }
    D_0052ABF0[D_0052ACF8][D_0052ACF0[D_0052ACF8]++] = id;
    o = D_0052ACF8 ^ 1;
    for (i = 0; i < D_0052ACF0[o]; i++) {
        if (D_0052ABF0[o][i] == id) return;
    }
    func_001337e0(1, id, 0);
}
typedef struct {
    u8 pad000[0x6C];
    u32 *x6c;
    u8 pad070[0x88 - 0x70];
    u32 x88;
    u8 pad08c[0x164 - 0x8C];
    s32 x164;
    u8 pad168[0x480 - 0x168];
    f32 x480;
    f32 x484;
} W32Bob;
f32 sinf(f32 x);
f32 func_00120c88(f32 x);
void func_00137748(W32Bob *o) {
    f32 t;
    if (o->x164 == 0x66 || o->x164 == 0x68 || o->x164 == 0x67) return;
    if (*o->x6c & 1) return;
    if (o->x88 & 4) {
        t = (o->x480 - 0.7999999523162842f) * 0.95f + 0.7999999523162842f;
        o->x480 = t - sinf(o->x484) * 0.05f;
        o->x484 = func_00120c88(o->x484 + 1.5707964f);
    } else {
        if (o->x480 < 1.0f) {
            o->x480 += 0.05f;
            if (o->x480 > 1.0f) o->x480 = 1.0f;
        }
        o->x484 = 0.0f;
    }
    o->x88 &= ~4;
}
typedef struct {
    u8 pad00[0x54];
    s8 x54;
} W32Info;
typedef struct {
    u8 pad00[0x1C];
    s32 x1c;
} W32Sub2;
typedef struct {
    u8 pad000[0x6C];
    s32 x6c;
    u8 pad070[0x130 - 0x70];
    W32Info *x130;
    u8 pad134[0x144 - 0x134];
    s32 x144;
    s32 x148;
    W32Sub2 *x14c;
    u8 pad150[0x370 - 0x150];
    u64 x370;
    u8 pad378[0x398 - 0x378];
    s32 x398;
    u8 pad39c[0x400 - 0x39C];
    s32 x400;
} W32Ch;
void func_0012b9b0(s32 a);
void func_00121eb0(s32 a);
s32 func_00137330(W32Ch *o, s32 a, s32 b);
void func_00141ab8(s32 a);
void func_00176310(s32 a);
void func_00145240(W32Ch *o);
void func_00137448(W32Ch *o);
void func_00135658(W32Ch *o);
void func_00137868(W32Ch *o) {
    if ((s32)(o->x370 >> 48) & 1) {
        if (o->x144) func_0012b9b0(o->x144);
    } else {
        s32 k = o->x130->x54;
        if (k != 1) {
            if (k <= 0) goto call;
            if (k >= 11) goto call;
            if (k < 9) goto call;
            if (o->x144) func_00121eb0(o->x144);
            goto done;
        call:
            func_00137330(o, 0, -2);
        }
    }
done:
    if (o->x6c) func_00141ab8(o->x6c);
    if (o->x400) func_00176310(o->x400);
    if (o->x148) func_00145240(o);
    if (o->x398) func_00137448(o);
    if (o->x14c && o->x14c->x1c) func_00176310(o->x14c->x1c);
    func_00135658(o);
}
typedef struct {
    u8 pad00[0x10];
    u8 *x10;
    u32 x14;
} W32Eff;
typedef struct {
    u64 x0;
    u8 pad008[0x70 - 0x8];
    s32 x70;
    u8 pad074[0xB0 - 0x74];
    W32Eff *xb0;
} W32Pc;
extern u32 D_002C5958;
#include "data/pieces/D_00350CE0.h"
s32 func_001063c8(void);
W32Eff *func_00148768(s32 a, s32 b, W32Pc *o, s32 c, f32 f);
void func_00137db0(W32Pc *o) {
    if (o->xb0 && (o->xb0->x14 & 3) != 1) o->xb0 = 0;
    if (func_001063c8()) {
        if (o->xb0) {
            func_00176310((s32)o->xb0);
            o->xb0 = 0;
        }
        return;
    }
    if (o->x70 == 8 && (o->x0 & 0x8001) == 0x8001 && !(D_002C5958 & 0x104000) && !func_001063c8()) {
        if (o->xb0 == 0) o->xb0 = func_00148768(D_00350CE0, 20, o, 0x8003, 0.0f);
        return;
    }
    if (o->xb0) {
        *o->xb0->x10 = 1;
        o->xb0 = 0;
    }
}
#include "data/types/text_00130000_h32_p.h"
extern s32 D_0052AA68;
extern W32Obj3 *D_0052AA70[]; /* src/data/bss_0052.c: O15 *D_0052AA70[0x60] */
#include "data/pieces/D_00304AD8.h"
extern f32 D_002BBDFC;
void func_002675a8(f32 *d, f32 *s);
void func_00130f18(W32Obj3 *o, f32 f);
s32 func_00138130(void) {
    s32 i;
    for (i = 0; i < D_0052AA68; i++) {
        W32Obj3 *o = D_0052AA70[i];
        D_00304AD8 = o;
        if (((s32)(o->x370 >> 39) & 1) || o->x154 == 0) {
            func_002675a8(o->x50, o->x10);
        } else if (!(o->x130->x4 & 0x20000) || ((s32)(o->x370 >> 35) & 1)) {
            func_00130f18(o, (o->x88 & 1) ? 0.0f : D_002BBDFC);
            o->x370 |= 1ULL << 43;
        }
    }
    D_0052AA68 = 0;
    return 0;
}
typedef struct {
    u64 flags;
    u8 pad08[0x10 - 0x8];
    f32 x10[4];
} W32Tgt;
typedef struct {
    u8 pad00[0x30];
    f32 x30[4];
} W32Src;
s32 func_001389c0(W32Src *o, W32Tgt *t);
void func_00138c30(W32Src *o, W32Tgt *t);
void func_00138ca0(W32Src *o, W32Tgt *t, f32 d);
void func_00138d88(W32Src *o, W32Tgt *t, f32 d);
s32 func_0014f5c8(W32Src *o);
s32 func_0014f600(W32Src *o);
f32 func_00267390(f32 *a, f32 *b);
void func_00138e58(W32Src *o, W32Tgt *t) {
    f32 d;
    if (func_001389c0(o, t)) {
        func_00138c30(o, t);
    } else {
        d = func_00267390(o->x30, t->x10);
        if (func_0014f5c8(o)) func_00138ca0(o, t, d);
        else if (func_0014f600(o)) func_00138d88(o, t, d);
        else func_00138ca0(o, t, d);
    }
    t->flags |= 2;
}
void func_00138f28(W32Src *o, W32Tgt *t, f32 d);
void func_00139040(W32Src *o, W32Tgt *t, f32 d);
void func_00139170(W32Src *o, W32Tgt *t) {
    f32 d;
    if (func_001389c0(o, t)) {
        func_00138c30(o, t);
    } else {
        d = func_00267390(o->x30, t->x10);
        if (func_0014f5c8(o)) func_00138f28(o, t, d);
        else if (func_0014f600(o)) func_00139040(o, t, d);
        else func_00138f28(o, t, d);
    }
    t->flags |= 2;
}
typedef struct {
    u8 pad00[0x28];
    f32 x28;
    f32 x2c;
    f32 x30;
    f32 x34;
} W32Prm;
typedef struct {
    u8 pad00[0xC4];
    f32 xc4;
} W32Scl;
typedef struct {
    u8 pad00[0x30];
    f32 x30[4];
    u8 pad40[0x6C - 0x40];
    W32Scl *x6c;
    u8 pad70[0x3C0 - 0x70];
    f32 x3c0[4];
} W32Act;
typedef struct {
    u8 pad00[0x40];
    u32 x40;
} W32Atk;
typedef struct {
    u8 pad00[0x8];
    s32 x8;
    u8 pad0c[0x2C - 0xC];
    W32Atk *x2c;
} W32Hit;
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_00308CDC.h"
void func_00267530(f32 *d, f32 *a, f32 *b);
void func_00156260(W32Act *o, f32 *v);
s32 func_00130340(W32Act *o, u32 f, f32 x);
void *func_00130578(void *o, s32 k, f32 f);
void func_001399a8(W32Act *o, W32Hit *h) {
    f32 v[4] __attribute__((aligned(16)));
    u32 f = h->x2c->x40;
    if (h->x8 < 0 && (f & 0x400000)) {
        f32 t;
        func_00267530(v, (*(f32 (*)[0x4])&D_002C58A0), o->x30);
        t = (f32)-h->x8 * (*(W32Prm **)&D_00308CDC)->x28;
                v[3] = (t < (*(W32Prm **)&D_00308CDC)->x2c ? t : (*(W32Prm **)&D_00308CDC)->x2c) * o->x6c->xc4;
        func_00156260(o, v);
        f &= ~0x400000;
    }
    func_00130340(o, f | 0x1000000, 0.0f);
    func_00130578(o, 0x40000000, 8.0f);
}
typedef struct {
    u8 pad00[0xC];
    void (*xc)(void);
} W32Ev;
typedef struct {
    u8 pad000[0x20];
    f32 x20[3];
    s32 x2c;
    f32 x30[4];
    u8 pad040[0x88 - 0x40];
    u32 x88;
    u8 pad08c[0x164 - 0x8C];
    s32 x164;
    u8 pad168[0x3D0 - 0x168];
    s32 x3d0;
    u8 pad3d4[0x3EA - 0x3D4];
    u16 x3ea;
} W32Mot;
void func_00130398(W32Mot *o, s32 k, f32 f);
void func_00138948(void);
void func_00139ff8(W32Mot *o) {
    s32 b = o->x3ea;
    s32 m = o->x164;
    W32Ev *e;
    if (m == b || m == b + 1) {
        func_00130398(o, b + 2, 0.0f);
        e = func_00130578(o, o->x3ea + 3, 0.0f);
        if (o->x88 & 2) e->xc = func_00138948;
    } else if (m == b + 5 || m == b + 6) {
        func_00130398(o, b + 7, 0.0f);
        e = func_00130578(o, o->x3ea + 8, 0.0f);
        if (o->x88 & 2) e->xc = func_00138948;
    } else {
        func_00130398(o, (o->x3d0 + 7) | 0x1000000, 0.0f);
        func_00130578(o, 0x40000000, 8.0f);
    }
    func_002675a8(o->x20, o->x30);
    o->x2c = 0;
}
typedef struct {
    u8 pad00[0x4C];
    u16 x4c;
} W32Pi;
typedef struct {
    u32 flags;
    u8 pad004[0x130 - 0x4];
    W32Pi *x130;
} W32Ply;
void func_00123460(W32Ply *p);
void func_00135800(W32Ply *p, f32 a, f32 b);
s32 func_0012f040(void *o, s32 a);
s32 func_0013c318(s32 k);
void func_002414a8(s32 a, s32 b);
void func_0013a810(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        W32Ply *p = (W32Ply *)D_002E26A0[i + 1];
        if (p == 0) continue;
        if (p->flags & 0x8000) continue;
        func_00123460(p);
        func_00135800(p, 0.0f, 0.0f);
        func_00135800(p, 1.0f, 30.0f);
        p->flags &= ~0x1000000;
        func_001373f8((W32Obj2 *)p, 30.0f);
        if (func_0012f040((void *)p, -1)) func_002414a8(func_0013c318(p->x130->x4c), 1);
    }
}
typedef struct {
    u8 pad00[0x30];
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3c;
} W32Spr;
typedef struct {
    u16 flags;
    u8 pad02[0x10 - 0x2];
    f32 x10;
} W32Fade;
W32Spr *D_0052AD00 ALIGNED(16);
W32Spr *func_001226f0(s32 a, s32 b, s32 c);
void func_00122768(W32Spr *s);
void func_00100ae0(void);
s32 func_0013ab30(W32Fade *f) {
    if (f->flags & 0x10) {
        D_0052AD00 = func_001226f0(1, 9, 0);
        D_0052AD00->x3c = 1.0f;
        f->x10 = 50.0f;
    }
    f->x10 -= D_002BBDFC;
    if (f->x10 <= 0.0f) {
        func_00122768(D_0052AD00);
        func_00100ae0();
        return 4;
    }
    D_0052AD00->x30 = D_0052AD00->x34 = D_0052AD00->x38 = f->x10 / 50.0f;
    return 0;
}
extern s32 D_0052AE54;
extern s32 D_0052AE50;
extern s32 D_00304B00[];
extern s32 D_00304B40;
extern s32 D_00304B44;
extern char D_0048DCB0[];
extern void *D_0052AE5C;
void D_00F20000(s32 a, s32 b);
s32 func_001ecfd8(void);
void func_00157668(void);
s32 sprintf(char *buf, const char *fmt, ...);
s32 func_00120748(char *name, void *dst, void (*cb)(void), s32 d);
void func_0013b1a0(void);
void func_0013b238(void);
void func_0011ef10(s32 a, void (*f)(void));
s32 func_0013b3d0(void) {
    char buf[32];
    if (D_0052AE54 != 2 || func_001ecfd8()) return 0;
    func_00157668();
    D_0052AE54 = 3;
    sprintf(buf, D_0048DCB0, D_00304B00[D_0052AE50], D_00304B40);
    func_00120748(buf, D_0052AE5C, 0, 0);
    sprintf(buf, D_0048DCB0, D_00304B00[D_0052AE50], D_00304B44);
    func_00120748(buf, (void *)D_00F20000, func_0013b1a0, 0);
    func_0011ef10(0xB798, func_0013b238);
    return 1;
}
extern s32 D_0052AE54;
extern void *D_0052AE5C;
void func_00155b70(void *p);
void func_00155be0(void *p);
void func_001763f0(void *p);
void func_00146928(s32 a);
void func_00146a68(void *p, s32 a, void (*cb)(void), s32 b);
void func_0013ba08(void);
void func_0013ba18(s32 size, s32 b, W32Hdr *h) {
    s32 *st;
    if (h->off[1] - h->off[0] > 0) func_00155b70((u8 *)h + h->off[0]);
    if (h->off[2] - h->off[1] > 0) func_00155be0((u8 *)h + h->off[1]);
    if (h->off[3] - h->off[2] > 0) func_00155be0((u8 *)h + h->off[2]);
    if (h->off[5] - h->off[4] > 0) func_001763f0((u8 *)h + h->off[4]);
    st = &D_0052AE54;
    *st = 1;
    if (h->off[7] - h->off[6] > 0) {
        func_00146928(-7);
        func_00146a68((u8 *)h + h->off[6], -7, func_0013ba08, 0);
    } else {
        *st = 2;
    }
    D_0052AE5C = (void *)((((u32)h + size + 0x7F) >> 7) << 7);
}
void func_0011ef58(void (*f)(void));
void func_0013b958(void);
void func_00133708(void);
void func_00100ab0(void);
#include "data/pieces/D_00304B84.h"
#include "data/pieces/D_00304B78.h"
void func_0013bd08(void) {
    u32 *f = &D_002C5958;
    u32 *g;
    if ((*f >> 13) & 1) {
        D_00F20000(2, 0);
        func_0011ef58(func_0013b958);
        func_002414a8(0, 1);
        func_002414a8(1, 2);
        func_002414a8(2, 2);
    }
    if (*f & 0x104000) {
        func_00133708();
        func_00100ab0();
    }
    g = &D_00304B78;
    *f &= ~0x2000;
    *f &= ~0x4000;
    *f &= ~0x100000;
    *g &= ~8;
    D_00304B84 = 0;
}
typedef struct { u16 x0; u16 x2; } W32Ent;
extern W32Ent *func_001478a0(s32 id);
void func_0013bfb8(u8 *a) {
    s32 i, j;
    u8 t;
    for (i = 47; i > 0; i--) {
        if (a[i] == 0) continue;
        for (j = 0; j < i; j++) {
            W32Ent *p = func_001478a0(a[j]);
            W32Ent *q = func_001478a0(a[j + 1]);
            if (p->x2 > q->x2) {
                t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
        }
    }
}
/* needs make: uses rodata */
typedef struct {
    u8 pad00[6];
    u8 kind;
} W32Kind;
extern u8 D_0052A100[];
void *func_0011f090(void *a, s32 b, void *c);
void func_00136768(W32Col *o);
void func_001369e8(W32Col *o);
void func_001371f0(W32Kind *o) {
    W32Job *j = func_0011f090(D_0052A100, 0, func_00136bc0);
    j->obj = (W32Col *)o;
    switch (o->kind) {
    case 4:
    case 9:
        j->cb = func_001368e8;
        break;
    case 5:
    case 10:
        j->cb = func_001369e8;
        break;
    case 8:
        j->cb = func_00136ab8;
        break;
    default:
        j->cb = func_00136768;
        break;
    }
}
void func_0014cce0(W32Act *o, f32 f);
void func_00267560(f32 *d, f32 *s, f32 f);
void func_00139a90(W32Act *o, W32Hit *h) {
    func_00130340(o, (h->x2c->x40 & ~0x400000) | 0x1000000, 0.0f);
    func_00130578(o, 0x40000006, 0.0f);
    func_0014cce0(o, 20.0f);
    if (h->x8 < 0) {
                f32 t = (f32)h->x8 / 100.0f * (*(W32Prm **)&D_00308CDC)->x30;
        func_00267560(o->x3c0, o->x30, (-(*(W32Prm **)&D_00308CDC)->x34 < t ? t : -(*(W32Prm **)&D_00308CDC)->x34) * o->x6c->xc4);
        return;
    }
    func_002675a8(o->x3c0, (*(f32 (*)[0x4])&D_002C58A0));
}

/* Pointer tables only this file uses (phase 4, tools/shift/define_ptr_tables.py). */
extern u8 D_0048DCA0[];
s32 D_00304B40 ALIGNED(16) = (s32)D_0048DCA0;
extern u8 D_0048DCA8[];
s32 D_00304B44 ALIGNED(4) = (s32)D_0048DCA8;
#include "data/data_002B.h"
#include "data/data_0030.h"
#include "data/data_0048.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDFC.h"
#include "data/pieces/D_002BC128.h"
#include "data/pieces/D_002C6450.h"
#include "data/pieces/D_003041F0.h"
