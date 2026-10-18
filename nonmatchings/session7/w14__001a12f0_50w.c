/* 001a12f0 pppRyjDrawKekotoDraw near miss (hand/nostrict): size correct (2688), 50 words, all in the packet-header setup after the colour clamp (0x1a1a28-0x1a1b08): orig loads key->id/D_00615E64 shape first, keeps k in one reg (lb; addiu), orders tex0/tex1 stores differently; statement-order hill-climb plateaus ~50. Needed: PlatSqrtf (bare sqrt.s), one kkSqrt with .set noreorder so gas does not fill the b slot, f32 inv[2] array (stack 320), i<4 tested at each site, pos declared before col (spill order), walkers for d/pos in the non-flag branch. */
#include "common.h"
#include "ppp.h"

typedef int u128 __attribute__((mode(TI)));
typedef f32 KkV4[4] __attribute__((aligned(16)));
typedef f32 KkMtx[4][4] __attribute__((aligned(16)));

typedef struct {
    u8 pad[0x10];
    KkMtx m;    /* +0x10 */
    KkMtx m2;   /* +0x50 */
} KkCam;

typedef struct {
    u8 pad0[8];
    u32 w8;
    u32 wC;
} KkTex;

typedef struct {
    u8 pad0[4];
    s32 off4;
    u8 pad8[0xE];
    u8 b16;
    u8 b17;
} KkTexHdr;

typedef struct {
    u8 pad0[0x1C];
    KkTexHdr *tex;
    u8 pad20[4];
} KkShape;

typedef struct {
    u8 pad0[0x10];
    KkShape *shapes;
} KkSys;

typedef struct {
    s32 frame;
    s32 id;        /* +0x4 */
    f32 w;         /* +0x8 */
    f32 len;       /* +0xC */
    f32 sc[8];     /* +0x10 */
    u8 flag;       /* +0x30 */
} KkKey;

typedef struct {
    u8 pad[8];
    u8 c[4];
} KkCol;

typedef struct {
    u128 tag;      /* +0x00 */
    u64 gif;       /* +0x10 */
    u64 regs;      /* +0x18 */
    u32 tex0[2];   /* +0x20 */
    u64 tex0r;     /* +0x28 */
    u32 tex1[2];   /* +0x30 */
    u64 tex1r;     /* +0x38 */
    u128 q;        /* +0x40 */
    u64 gif2;      /* +0x50 */
    u64 regs2;     /* +0x58 */
} KkPkt;

typedef union {
    f32 f;
    s32 i;
} KkW;

typedef struct {
    u8 pad[0x30];
    u128 q;
} KkGs;

extern KkSys *D_00615E64;
extern KkCam *D_00615E68;
extern KkMtx D_00615FC0;
extern KkMtx D_00616040;
extern KkGs D_0061E800;
extern s8 D_00372EA0;
extern s32 D_00372EA8[];

#include "platform/math.h"
void sceVu0MulMatrix(KkMtx, KkMtx, KkMtx);
void func_002672f8(f32 *, KkMtx, f32 *);
void func_002675a8(f32 *, f32 *);
void func_00267e90(f32 *, f32 *, f32);
void func_00267530(f32 *, f32 *, f32 *);
void func_00267518(f32 *, f32 *, f32 *);
void func_00267560(f32 *, f32 *, f32);
void func_002673b8(f32 *, f32 *);
void func_002675e0(s32 *, f32 *);
s32 func_00267ea8(f32 *);
void FlushCache(s32);
s32 func_00266c08(s32);
void func_00266f38(s32, s32);
void sceGsSyncPath(s32, s32);

static inline f32 kkSqrt(f32 x) {
    f32 r;
    __asm__ volatile(".set noreorder\n\tsqrt.s %0, %1\n\t.set reorder" : "=f"(r) : "f"(x));
    return r;
}

static inline s32 kkPush(s32 n) {
    s8 *sp = &D_00372EA0;
    s32 *st = D_00372EA8;
    s32 i = *sp;
    s32 v = st[i];
    i++;
    *sp = i;
    st[i] = v + n;
    return v;
}

void pppRyjDrawKekotoDraw(u8 *obj, KkKey *key, PppEntry *e)
{
    KkV4 v0, v1;
    KkV4 c[8];
    s32 d[8][4] __attribute__((aligned(16)));
    s32 col0[4], col1[4];
    f32 inv[2];
    KkV4 dir, perp, tmp;
    KkV4 a, b;
    KkMtx mtx;
    KkV4 a2, b2;
    KkMtx mtx2;
    KkV4 *pos;
    KkCol *col;
    f32 r0, r1;
    s32 i, j;
    s8 *spp;
    s32 *st;
    s32 k, k1, v;
    KkTexHdr *th;
    KkTex *tx;
    KkPkt *p;
    KkW *out;
    s32 dma;
    u64 *tag;
    s32 cnt;
    KkV4 *src;
    s32 (*dp)[4];
    s32 *cs;

    pos = (KkV4 *) (obj + e->offsets[2] + 0xA0);
    col = (KkCol *) (obj + e->offsets[0] + 0xA0);
    if (key->id == 0xFFFF) return;
    v0[0] = -key->w;
    v0[1] = 0.0f;
    v0[2] = 0.0f;
    v0[3] = 1.0f;
    v1[0] = key->w;
    v1[1] = 0.0f;
    v1[2] = 0.0f;
    v1[3] = 1.0f;
    if (key->flag) {
        sceVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
        func_002672f8(a, mtx, v0);
        func_002675a8(b, a);
        b[0] += key->len;
        func_002672f8(a, D_00616040, a);
        func_002672f8(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            func_00267e90(a, a, a[3]);
            b[3] = 1.0f / b[3];
            func_00267e90(b, b, b[3]);
            func_00267530(a, a, b);
            r0 = PlatSqrtf(a[0] * a[0] + a[1] * a[1]);
        } else {
            r0 = 0.0f;
        }
        func_002672f8(a, mtx, v1);
        func_002675a8(b, a);
        b[0] += key->len;
        func_002672f8(a, D_00616040, a);
        func_002672f8(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            func_00267e90(a, a, a[3]);
            b[3] = 1.0f / b[3];
            func_00267e90(b, b, b[3]);
            func_00267530(a, a, b);
            r1 = kkSqrt(a[0] * a[0] + a[1] * a[1]);
        } else {
            r1 = 0.0f;
        }
        if (r0 == 0.0f && r1 == 0.0f) return;
    } else {
        sceVu0MulMatrix(mtx2, D_00615FC0, D_00615E68->m);
        a2[0] = a2[1] = a2[2] = 0.0f;
        a2[3] = 1.0f;
        func_002672f8(a2, mtx2, a2);
        func_002675a8(b2, a2);
        b2[0] += key->len;
        func_002672f8(a2, D_00616040, a2);
        func_002672f8(b2, D_00616040, b2);
        if (a2[3] > 0.0f && b2[3] > 0.0f) {
            a2[3] = 1.0f / a2[3];
            func_00267e90(a2, a2, a2[3]);
            b2[3] = 1.0f / b2[3];
            func_00267e90(b2, b2, b2[3]);
            func_00267530(a2, a2, b2);
            r0 = r1 = PlatSqrtf(a2[0] * a2[0] + a2[1] * a2[1]);
        } else {
            r0 = r1 = 0.0f;
        }
    }
    func_002672f8(c[2], D_00615E68->m2, v0);
    func_002672f8(c[4], D_00615E68->m2, v1);
    if (c[2][3] <= 0.0f && c[4][3] <= 0.0f) return;
    if (c[2][3] > 0.0f) {
        inv[0] = c[2][3] = 1.0f / c[2][3];
        func_00267e90(c[2], c[2], inv[0]);
    }
    if (c[4][3] > 0.0f) {
        inv[1] = c[4][3] = 1.0f / c[4][3];
        func_00267e90(c[4], c[4], inv[1]);
    }
    dir[0] = c[4][0] - c[2][0];
    dir[1] = c[4][1] - c[2][1];
    dir[2] = 0.0f;
    dir[3] = 0.0f;
    func_002673b8(dir, dir);
    perp[0] = -dir[1];
    perp[1] = dir[0];
    perp[2] = 0.0f;
    perp[3] = 0.0f;
    func_00267560(tmp, perp, r0);
    func_00267518(c[3], c[2], tmp);
    func_00267560(tmp, perp, r1);
    func_00267518(c[5], c[4], tmp);
    perp[0] = -perp[0];
    perp[1] = -perp[1];
    func_00267560(tmp, perp, r0);
    func_00267518(c[2], c[2], tmp);
    func_00267560(tmp, perp, r1);
    func_00267518(c[4], c[4], tmp);
    func_00267560(tmp, dir, r0);
    func_00267530(c[0], c[2], tmp);
    func_00267530(c[1], c[3], tmp);
    func_00267560(tmp, dir, r1);
    func_00267518(c[6], c[4], tmp);
    func_00267518(c[7], c[5], tmp);
    for (i = 0; i < 8; i++) {
        func_002675e0(d[i], c[i]);
    }
    col0[0] = (f32) col->c[0] * key->sc[0];
    col0[1] = (f32) col->c[1] * key->sc[1];
    col0[2] = (f32) col->c[2] * key->sc[2];
    col0[3] = (f32) col->c[3] * key->sc[3];
    col1[0] = (f32) col->c[0] * key->sc[4];
    col1[1] = (f32) col->c[1] * key->sc[5];
    col1[2] = (f32) col->c[2] * key->sc[6];
    col1[3] = (f32) col->c[3] * key->sc[7];
    for (i = 0; i < 4; i++) {
        if (col0[i] < 0) col0[i] = 0;
        else if (col0[i] >= 256) col0[i] = 255;
        if (col1[i] < 0) col1[i] = 0;
        else if (col1[i] >= 256) col1[i] = 255;
    }
    th = D_00615E64->shapes[key->id].tex;
    p = (KkPkt *) kkPush(0x800);
    p->q = D_0061E800.q;
    p->gif = 0x3000000000000001ULL;
    cnt = 0;
    tx = (KkTex *) ((u8 *) th + th->off4);
    p->regs = 0xEEE;
    p->tex1[1] = th->b17;
    dma = ((s32) p & 0x0FFFFFFF) | 0x80000000;
    tag = &p->gif2;
    p->tex0r = 6;
    p->tex1[0] = th->b16;
    p->tex0[1] = tx->wC;
    p->tex1r = 0x42;
    p->tex0[0] = tx->w8;
    out = (KkW *) (p + 1);
    src = pos;
    dp = d;
    for (i = 0; i < 8; i++, dp++, src++) {
        if (func_00267ea8(c[i]) == 0) {
            if (key->flag) {
                if (i < 4) func_00267560(tmp, pos[i], inv[0]);
                else func_00267560(tmp, pos[i], inv[1]);
                out->f = tmp[0]; out++;
                out->f = tmp[1]; out++;
                out->f = tmp[2]; out++;
            } else {
                out->f = (*src)[0]; out++;
                out->f = (*src)[1]; out++;
                out->f = (*src)[2]; out++;
            }
            out->i = 0; out++;
            if (i < 4) {
                for (j = 0; j < 4; j++) {
                    out->i = col0[j]; out++;
                }
            } else {
                for (j = 0; j < 4; j++) {
                    out->i = col1[j]; out++;
                }
            }
            cnt++;
            out->i = (*dp)[0]; out++;
            out->i = (*dp)[1]; out++;
            out->i = (*dp)[2]; out++;
            out->i = 0; out++;
        }
    }
    tag[0] = cnt | 0x8000 | (0xC0B9ULL << 46);
    tag[1] = 0x412;
    __asm__ volatile("sync");
    p->tag = 0;
    *(s32 *) &p->tag = ((((u8 *) out - (u8 *) p) >> 4) - 1) | 0x70000000;
    FlushCache(0);
    func_00266f38(func_00266c08(2), dma);
    sceGsSyncPath(0, 0);
    { s8 *sp = &D_00372EA0; s32 k = *sp; *sp = k - 1; }
}
