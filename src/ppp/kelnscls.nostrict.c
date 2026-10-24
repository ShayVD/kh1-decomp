/* The ppp lens flare classes' draws, -fno-strict-aliasing (docs/modules.md
 * "Session 50"): pppKeLnsLp (a loop), Arnd (around), Clm (column), Crn
 * (corona) and Fls (flash) draw their flare shapes with kelns.c's helpers
 * at the owner's position, the T versions over a copy of the screen that
 * func_00192958 stores with PlatGsExecStoreImage(the packet D_0061E250),
 * and pppKeLnsLpSftFrame shifts a pppKeLnsLp's angles.  kelnscls.c has the
 * Cons and helpers.  Types named NAME_xxxxx are one function's own view
 * (tools/shift/s50move/assemble.py).  Read from the code, not proved by a
 * boot. */

/* pppKeLnsLpDraw (from hand/nostrict/text_00180000_h40.c). */
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "ppp.h"
#include "data/bss_0061.h"
#include "data/types/nostrict_text_00180000_h40.h"
#define PPP_WORK(T, obj, e, k) ((T *) ((u8 *) (obj) + (e)->offsets[k] + 0xA0))
typedef unsigned int u128 __attribute__((mode(TI)));
typedef union {
    f32 f[4];
    u128 q;
} PppQv;
extern PppQv D_00615FC0[4];
extern PppQv D_00616040[4];
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
    u8 pad10[0x8D];
    u8 unk9D;  /* +0x9D */
} PppObject;
typedef struct {
    u8 pad[0x10];
    PppMtx m;    /* +0x10 */
    PppMtx m2;   /* +0x50 */
} PppMtxOwner;
extern PppMtxOwner *D_00615E68;
void func_001a9098(void *, f32 *);
typedef f32 PppVec4[4] __attribute__((aligned(16)));
void func_002672f8(PppVec4, f32 *, PppVec4);
typedef struct {
    s32 frame;
    f32 b, a;   /* +0x4 */
    u8 c, d;    /* +0xC */
    u8 e, f, g; /* +0xE (LnsLpT) */
} PppLnsKey;
typedef struct {
    u8 pad00[0x80];
    f32 pos[3];   /* +0x80 */
    u8 pad8C;
    u8 unk8D;     /* +0x8D */
    u8 c, d;      /* +0x8E */
    f32 v[3];     /* +0x90 */
    f32 b;        /* +0x9C */
    u8 padA0[8];
    f32 a;        /* +0xA8 */
    u8 padAC[0x14];
    u8 unkC0, unkC1; /* +0xC0 */
} PppLnsWork;
typedef struct {
    PppLnsWork *w;
    f32 *pos;
    void *m1;
    void *m2;
} PppLnsArg;
void func_001a57c0(PppLnsArg *);
void pppKeLnsLpDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppVec4 v;
    PppLnsArg arg;
    PppLnsWork *w = PPP_WORK(PppLnsWork, obj, e, 0);

    if (key->frame == obj->frame) {
        w->a += key->a;
        w->c = key->c;
        w->b += key->b;
        w->d = key->d;
    }
    if (w->d) {
        *(u128 *) v = 0;
        v[3] = v[2] = 1.0f;
        func_002672f8(v, D_00615E68->m[0], v);
        func_001a9098(w->v, v);
    }
    w->pos[0] = D_00615E68->m[3][0];
    w->pos[1] = D_00615E68->m[3][1];
    w->pos[2] = D_00615E68->m[3][2];
    arg.m1 = D_00615FC0;
    arg.m2 = D_00616040;
    arg.w = w;
    arg.pos = D_00615E68->m[3];
    func_001a57c0(&arg);
}

/* pppKeLnsArndDraw (from hand/nostrict/text_00190000_h63.c). */
#include "data/pieces/D_003701F0.h"
typedef struct {
    s32 unk0;
    u8 *inst;   /* +0x4 */
    s32 time;   /* +0x8 */
    s32 unkC;
} PppSlot;
typedef struct {
    u8 pad[0x30];
    f32 col[4];     /* +0x30 */
    u8 pad40[0x40];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem;
extern PppSystem *D_00615E60;
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_92048;
typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    void *p10;     /* +0x10 */
} PppLnsDraw;
typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
} PppLnsKey_92048;
void func_00191fc8(PppObject_92048 *, PppLnsKey_92048 *, PppEntry *);
void func_001a60e8(PppLnsDraw *, s32);
#define D_00616040 ((u8 *) D_00616040)
void pppKeLnsArndDraw(PppObject_92048 *obj, PppLnsKey_92048 *key, PppEntry *e) {
    PppLnsDraw d;

    func_00191fc8(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.p10 = D_003701F0;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    func_001a60e8(&d, 0);
}
#undef D_00616040

/* pppKeLnsClmDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_922c0;
typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    f32 f10;       /* +0x10 */
    void *p14;     /* +0x14 */
} PppLnsClmDraw;
typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
    u16 h10, h12;  /* +0x10 */
    u16 h14;       /* +0x14 */
} PppLnsClmKey;
void func_00192208(PppObject_922c0 *, PppLnsClmKey *, PppEntry *);
void func_001a5ce8(PppLnsClmDraw *, s32);
#define D_00616040 ((u8 *) D_00616040)
void pppKeLnsClmDraw(PppObject_922c0 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsClmDraw d;

    func_00192208(obj, key, e);
    d.f10 = key->h14;
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a5ce8(&d, 0);
}
#undef D_00616040

/* pppKeLnsCrnDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_92538;
typedef struct {
    void *work;    /* +0x00 */
    u8 col[4];     /* +0x04 */
    void *p08;     /* +0x08 */
    f32 f0C;       /* +0x0C */
    u16 h10, h12;  /* +0x10 */
    void *p14;     /* +0x14 */
} PppLnsCrnDraw;
void func_001924a8(PppObject_92538 *, PppLnsClmKey *, PppEntry *);
void func_001a62c0(PppLnsCrnDraw *, s32);
#define D_00616040 ((u8 *) D_00616040)
void pppKeLnsCrnDraw(PppObject_92538 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnDraw d;

    func_001924a8(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.h10 = key->h10;
    d.h12 = key->h12;
    d.f0C = key->f0C;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a62c0(&d, 0);
}
#undef D_00616040

/* pppKeLnsFlsDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_92788;
void func_00192708(PppObject_92788 *, PppLnsClmKey *, PppEntry *);
void func_001a6550(PppLnsCrnDraw *, s32);
#define D_00616040 ((u8 *) D_00616040)
void pppKeLnsFlsDraw(PppObject_92788 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnDraw d;

    func_00192708(obj, key, e);
    d.col[0] = key->col[0] * D_00615E60->col[0];
    d.col[1] = key->col[1] * D_00615E60->col[1];
    d.col[2] = key->col[2] * D_00615E60->col[2];
    d.col[3] = key->col[3] * D_00615E60->col[3];
    d.p08 = D_00616040;
    d.f0C = key->f0C;
    d.h10 = key->h10;
    d.h12 = key->h12;
    d.work = PPP_WORK(void, obj, e, 0);
    d.p14 = D_003701F0;
    func_001a6550(&d, 0);
}
#undef D_00616040

/* func_00192958 (from hand/nostrict/text_00190000_s18_s18m2.c). */
typedef int u128_92958 __attribute__((mode(TI)));
typedef struct { u64 fbp:9, pad0:7, fbw:6, pad1:2, psm:6, pad2:2, fbmsk:32; } GsFrame;
typedef struct { u64 zbp:9, pad3:15, psmz:4, pad4:4, zmsk:1, pad5:31; } GsZbuf;
typedef struct { u64 ofx:16, pad6:16, ofy:16, pad7:16; } GsXyoff;
typedef struct { u64 scx0:11, pad8:5, scx1:11, pad9:5, scy0:11, pad10:5, scy1:11, pad11:5; } GsScissor;
typedef struct {
    GsFrame frame;
    u64 frame_a;
    GsZbuf zbuf;
    u64 zbuf_a;
    GsXyoff xyoffset;
    u64 xyoffset_a;
    GsScissor scissor;
    u64 scissor_a;
    u64 prmodecont;
    u64 prmodecont_a;
    u64 colclamp;
    u64 colclamp_a;
    u64 dthe;
    u64 dthe_a;
    u64 test;
    u64 test_a;
} __attribute__((aligned(16))) FlarePkt;
extern FlarePkt D_0061E250;
typedef struct {
    u8 pad[0x7C];
    f32 f7C;
    u8 pad80[0xC];
    u8 b8C, b8D;
    u8 pad8E[0x1E];
    f32 fAC;
    f32 pos[4];   /* +0xB0 */
    u8 bC0, bC1;
} FlareObj;
typedef struct { u8 b[0x70]; } __attribute__((aligned(16))) GsStoreImage;
void func_002675e0(s32 *, f32 *);
u8 *func_001aa950(s32);
void func_001aa9d0(s32);
/* func_00192958: MATCHED (session 18, s18m2), hand/nostrict. From s10 w11's 17w draft (nonmatchings/session10/w11__00192958_17w.c). FLAGGED: five local register variables (plain C, no inline asm): the scissor and xyoffset TI header constants pinned to a1/a3 (`register u128_92958 ks asm("$5")`, `kx asm("$7")`; without them local-alloc gives zbuf/xy/scissor birth order on a live-length tie, 17w), and the scy0 chain split as e (a1, the raw field), t (a3, the s32 truncate) and u (a1, t << 4), so the truncate is untied from its source as in the original and the o->pos argument move issues after the addu. b[] in order b0, b1, b2, b3 (exhaustive order search). Each pin is needed: without e 7w, without kx 12w, `u + oy` 1w. Unlike s18m1's 001f2630 f4 pin, these pinned computed values are not dissolved: a truncate and a shift into a hard register survive cse. */
void func_00192958(FlareObj *o, s32 a1, s32 frame) {
    s32 v[4] __attribute__((aligned(16)));
    s32 r[4];
    s32 b[4];
    GsStoreImage si;
    s32 sx, sy;
    FlarePkt *pk = &D_0061E250;
    GsXyoff *xy = &pk->xyoffset;
    GsScissor *sc = &pk->scissor;
    s32 ox, oy;
    s32 w, h, w8, h4;
    u8 *buf;
    u8 *p;
    f32 cnt;
    u32 thr;
    s32 i, j;
    register s32 u asm("$5");
    register u64 e asm("$5");
    register s32 t asm("$7");
    register u128_92958 ks asm("$5");
    register u128_92958 kx asm("$7");

    *(u128_92958 *) &pk->frame = 0x800d0;
    pk->frame_a = 76;
    *(u128_92958 *) &pk->zbuf = 0x31000070;
    pk->zbuf_a = 78;
    kx = 0x740000007000ULL;
    *(u128_92958 *) xy = kx;
    pk->xyoffset_a = 24;
    ks = 0x17f000001ff0000ULL;
    *(u128_92958 *) sc = ks;
    pk->scissor_a = 64;
    *(u128_92958 *) &pk->prmodecont = 0;
    pk->prmodecont_a = 26;
    *(u128_92958 *) &pk->colclamp = 1;
    pk->colclamp_a = 70;
    *(u128_92958 *) &pk->dthe = 0;
    pk->dthe_a = 69;
    *(u128_92958 *) &pk->test = 0x5000d;
    pk->test_a = 71;
    if (o->f7C == 0.0f)
        return;
    j = o->b8D + 1;
    if (o->b8C % j != frame % j) {
        o->f7C *= o->fAC;
        return;
    }
    ox = xy->ofx;
    oy = pk->xyoffset.ofy;
    b[0] = ox + ((s32) sc->scx0 << 4);
    e = sc->scy0;
    t = e;
    u = t << 4;
    b[1] = oy + u;
    b[2] = ox + (((s32) sc->scx1 + 1) << 4);
    b[3] = oy + (((s32) sc->scy1 + 1) << 4);
    func_002675e0(v, o->pos);
    sx = o->bC0;
    sy = o->bC1;
    r[0] = v[0] - sx * 8;
    r[1] = v[1] - sy * 8;
    r[2] = v[0] + sx * 8;
    r[3] = v[1] + sy * 8;
    if (r[0] < b[0]) r[0] = b[0]; else if (b[2] < r[0]) r[0] = b[2];
    if (r[1] < b[1]) r[1] = b[1]; else if (b[3] < r[1]) r[1] = b[3];
    if (r[2] < b[0]) r[2] = b[0]; else if (b[2] < r[2]) r[2] = b[2];
    if (r[3] < b[1]) r[3] = b[1]; else if (b[3] < r[3]) r[3] = b[3];
    w = (r[2] - r[0] + 15) >> 4;
    h = (r[3] - r[1] + 15) >> 4;
    if (w <= 0 || h <= 0) {
        o->f7C = 0.0f;
        o->fAC = 0.0f;
        return;
    }
    w8 = (w + 7) & ~7;
    h4 = (h + 3) & ~3;
    ox = (r[0] - ox) >> 4;
    oy = (r[1] - oy) >> 4;

    buf = func_001aa950(0x3060);
    PlatGsSetDefStoreImage(&si, pk->zbuf.zbp << 5, pk->frame.fbw, 0x31, ox, oy, w8, h4);
    PlatFlushCache(0);
    PlatGsExecStoreImage(&si, buf + 96);
    p = buf + 96;
    PlatGsSyncPath(0, 0);
    cnt = 0.0f;
    thr = v[2] >> 4;
    for (j = 0; j < h; j++) {
        for (i = 0; i < w; i++) {
            if ((u32) (p[0] | (p[1] << 8) | (p[2] << 16)) < thr)
                cnt += 1.0f;
            p += 3;
        }
        p += (w8 - w) * 3;
    }
    func_001aa9d0(0x3060);
    cnt /= (f32) (sx * sy);
    o->fAC = cnt;
    o->f7C = o->f7C * cnt;
}

/* pppKeLnsLpTDraw (from hand/nostrict/text_00180000_h40.c). */
void func_00267560(f32 *, PppVec4, f32);
void pppKeLnsLpTDraw(PppObject *obj, PppLnsKey *key, PppEntry *e) {
    PppVec4 v;
    PppLnsWork *w;
    f32 one;

    pppKeLnsLpDraw(obj, key, e);
    w = PPP_WORK(PppLnsWork, obj, e, 0);
    if (key->frame == obj->frame) {
        w->unkC0 = key->e << 3;
        w->unkC1 = key->f << 2;
        w->unk8D = key->g;
    }
    one = 1.0f;
    v[3] = one;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    func_002672f8(v, D_00615E68->m2[0], v);
    func_00267560((f32 *) ((u8 *) w + 0xB0), v, one / v[3]);
    func_00192958(w, 0, 0);
}

/* pppKeLnsArndTDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_92fc8;
void func_002675a8(PppVec4, f32 *);
typedef struct {
    s32 frame;
    s32 unk4;
    u8 col[4];     /* +0x8 */
    f32 f0C;       /* +0xC */
} PppLnsKey_92fc8;
typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
} PppLnsArndT;
void func_00192f78(PppLnsArndT *, s32, s32);
void pppKeLnsArndTDraw(PppObject_92fc8 *obj, PppLnsKey_92fc8 *key, PppEntry *e) {
    PppLnsArndT *w = PPP_WORK(PppLnsArndT, obj, e, 0);

    func_00191fc8(obj, key, e);
    if (key->frame == obj->frame)
        w->f20 = key->f0C;
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_00192f78(w, 0, 0);
}

/* func_001931a8 (from hand/nostrict/text_00180000_s6_11.c). */
typedef struct {
    u8 pad[0x30];
    u8 v30[0x10];
    f32 f40, f44;
    s32 i48;
} A8Obj;
typedef struct {
    A8Obj *o;
    s32 i;
    void *m;
    f32 f44;
    f32 f40;
    void *v;
} A8Arg;
#define D_00616040 ((u8 *) D_00616040)
void func_001931a8(A8Obj *o) {
    A8Arg a;
    a.o = o;
    a.f40 = o->f40;
    a.i = o->i48;
    a.f44 = o->f44;
    a.m = D_00616040;
    a.v = o->v30;
    func_001a5ce8(&a, 0);
}
#undef D_00616040

/* pppKeLnsClmTDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_93200;
typedef struct {
    u8 pad[0x30];
    PppVec4 v;     /* +0x30 */
    f32 f40;       /* +0x40 */
    f32 f44;       /* +0x44 */
    u8 col[4];     /* +0x48 */
} PppLnsClmT;
#define func_001931a8 ((void (*)(PppLnsClmT *, s32, s32)) func_001931a8)
void pppKeLnsClmTDraw(PppObject_93200 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsClmT *w = PPP_WORK(PppLnsClmT, obj, e, 0);

    func_00192208(obj, key, e);
    if (key->frame == obj->frame) {
        w->f44 = key->f0C;
        w->f40 = key->h14;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_001931a8(w, 0, 0);
}
#undef func_001931a8

/* pppKeLnsCrnTDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_934c0;
typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
    f32 f28, f2C;  /* +0x28 */
} PppLnsCrnT;
void func_00193408(PppLnsCrnT *, s32, s32);
void pppKeLnsCrnTDraw(PppObject_934c0 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsCrnT *w = PPP_WORK(PppLnsCrnT, obj, e, 0);

    func_001924a8(obj, key, e);
    if (key->frame == obj->frame) {
        w->f20 = key->f0C;
        w->f28 = key->h10;
        w->f2C = key->h12;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_00193408(w, 0, 0);
}

/* pppKeLnsFlsTDraw (from hand/nostrict/text_00190000_h63.c). */
typedef struct {
    s32 unk00, unk04, unk08;
    s32 frame; /* +0x0C */
} PppObject_93748;
typedef struct {
    u8 pad[0x10];
    PppVec4 v;     /* +0x10 */
    f32 f20;       /* +0x20 */
    u8 col[4];     /* +0x24 */
    f32 f28;       /* +0x28 */
    u16 h2C;       /* +0x2C */
} PppLnsFlsT;
void func_001936c0(PppLnsFlsT *, s32, s32);
void pppKeLnsFlsTDraw(PppObject_93748 *obj, PppLnsClmKey *key, PppEntry *e) {
    PppLnsFlsT *w = PPP_WORK(PppLnsFlsT, obj, e, 0);

    func_00192708(obj, key, e);
    if (key->frame == obj->frame) {
        w->f20 = key->f0C;
        w->f28 = key->h10;
        w->h2C = key->h12;
    }
    w->col[0] = key->col[0] * D_00615E60->col[0];
    w->col[1] = key->col[1] * D_00615E60->col[1];
    w->col[2] = key->col[2] * D_00615E60->col[2];
    w->col[3] = key->col[3] * D_00615E60->col[3];
    func_002675a8(w->v, (f32 *) D_003701F0);
    func_001936c0(w, 0, 0);
}

/* pppKeLnsLpSftFrame (from hand/nostrict/text_00180000_h40.c). */
typedef struct {
    u8 pad[0x80];
    PppSlot *slots; /* +0x80 */
    u8 pad84[0x2C];
    u64 flags;      /* +0xB0 */
} PppSystem_93940;
extern s32 D_0061621C;
typedef struct {
    s32 frame;
    f32 a, b; /* +0x4 */
} PppKey2f;
#define D_00615E60 ((PppSystem_93940 *) D_00615E60)
void pppKeLnsLpSftFrame(PppObject *obj, PppKey2f *key, PppEntry *e) {
    f32 *v;
    PppLnsWork *w;

    if (D_0061621C != 0 || (D_00615E60->flags & 0xFF0000FF00ULL))
        return;
    v = PPP_WORK(f32, obj, e, 0);
    w = PPP_WORK(PppLnsWork, obj, e, 1);
    if (obj->frame == key->frame) {
        v[0] += key->a;
        v[1] += key->b;
        if (obj->frame == 0 && obj->unk9D == 0)
            return;
    }
    w->b += v[0];
    w->a += v[1];
}
#undef D_00615E60

