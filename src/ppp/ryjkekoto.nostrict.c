/* The pppRyjDrawKekoto class, -fno-strict-aliasing (docs/modules.md
 * "Session 49"; s8_w11 renamed): func_001a1158 sets the eight UVs of a quad
 * strip from the key's three selectors (width 1 / 0.5 / 0.25, a quarter
 * offset); pppRyjDrawKekotoDraw builds its GS packet (ryjkekoto.c has the
 * Frame and Con).  Read from the code, not proved by a boot. */
#include "common.h"
#include "platform/vu.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "ppp.h"
#include "data/pieces/D_003701D0.h"

typedef FV4_3701d0 FV4;
typedef struct { u8 pad[0x31]; u8 a, b, c; } UvSrc;

void func_001a1158(UvSrc *s, FV4 *v) {
    f32 u0, u1, a, h, f;
    switch (s->a) {
    case 1: a = 0.49f; break;
    case 2: a = 0.24f; break;
    case 0: default: a = 0.99f; break;
    }
    switch (s->b) {
    case 1: h = 0.49f; break;
    case 2: h = 0.24f; break;
    case 0: default: h = 0.99f; break;
    }
    switch (s->c) {
    case 1: f = 0.25f; break;
    case 2: f = 0.5f; break;
    case 3: f = 0.75f; break;
    case 0: default: f = 0.0f; break;
    }
    u1 = f + a;
    u0 = f + 0.01f;
    v[7].x = u0;
    v[6].x = u0;
    v[1].x = u0;
    v[5].x = u1;
    v[4].x = u1;
    v[3].x = u1;
    v[7].y = h;
    v[5].y = h;
    v[3].y = h;
    v[6].y = 0.01f;
    v[4].y = 0.01f;
    v[2].y = 0.01f;
    v[7].z = 1.0f;
    v[6].z = 1.0f;
    v[5].z = 1.0f;
    v[4].z = 1.0f;
    v[3].z = 1.0f;
    v[2].z = 1.0f;
    v[1].z = 1.0f;
    v[1].y = h;
    v[0].z = 1.0f;
    v[2].x = u1;
    v[0].y = 0.01f;
    v[0].x = u0;
}

typedef kh1_s128 u128;
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

extern KkSys *D_00615E64; /* src/data/bss_0061.c: s32 D_00615E64 */
extern KkCam *D_00615E68; /* src/data/bss_0061.c: s32 D_00615E68 */
extern KkMtx D_00615FC0;
extern KkMtx D_00616040; /* src/data/bss_0061.c: u8 D_00616040[0x40] */
extern KkGs D_0061E800;
extern s8 D_00372EA0;
#include "data/pieces/D_00372EA8.h"

#include "platform/math.h"

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
        PlatVu0MulMatrix(mtx, D_00615FC0, D_00615E68->m);
        PlatVu0ApplyMatrix(a, mtx, v0);
        PlatVu0CopyVector(b, a);
        b[0] += key->len;
        PlatVu0ApplyMatrix(a, D_00616040, a);
        PlatVu0ApplyMatrix(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            PlatVu0ScaleVectorXYZ(a, a, a[3]);
            b[3] = 1.0f / b[3];
            PlatVu0ScaleVectorXYZ(b, b, b[3]);
            PlatVu0SubVector(a, a, b);
            r0 = PlatSqrtf(a[0] * a[0] + a[1] * a[1]);
        } else {
            r0 = 0.0f;
        }
        PlatVu0ApplyMatrix(a, mtx, v1);
        PlatVu0CopyVector(b, a);
        b[0] += key->len;
        PlatVu0ApplyMatrix(a, D_00616040, a);
        PlatVu0ApplyMatrix(b, D_00616040, b);
        if (a[3] > 0.0f && b[3] > 0.0f) {
            a[3] = 1.0f / a[3];
            PlatVu0ScaleVectorXYZ(a, a, a[3]);
            b[3] = 1.0f / b[3];
            PlatVu0ScaleVectorXYZ(b, b, b[3]);
            PlatVu0SubVector(a, a, b);
            r1 = kkSqrt(a[0] * a[0] + a[1] * a[1]);
        } else {
            r1 = 0.0f;
        }
        if (r0 == 0.0f && r1 == 0.0f) return;
    } else {
        PlatVu0MulMatrix(mtx2, D_00615FC0, D_00615E68->m);
        a2[0] = a2[1] = a2[2] = 0.0f;
        a2[3] = 1.0f;
        PlatVu0ApplyMatrix(a2, mtx2, a2);
        PlatVu0CopyVector(b2, a2);
        b2[0] += key->len;
        PlatVu0ApplyMatrix(a2, D_00616040, a2);
        PlatVu0ApplyMatrix(b2, D_00616040, b2);
        if (a2[3] > 0.0f && b2[3] > 0.0f) {
            a2[3] = 1.0f / a2[3];
            PlatVu0ScaleVectorXYZ(a2, a2, a2[3]);
            b2[3] = 1.0f / b2[3];
            PlatVu0ScaleVectorXYZ(b2, b2, b2[3]);
            PlatVu0SubVector(a2, a2, b2);
            r0 = r1 = PlatSqrtf(a2[0] * a2[0] + a2[1] * a2[1]);
        } else {
            r0 = r1 = 0.0f;
        }
    }
    PlatVu0ApplyMatrix(c[2], D_00615E68->m2, v0);
    PlatVu0ApplyMatrix(c[4], D_00615E68->m2, v1);
    if (c[2][3] <= 0.0f && c[4][3] <= 0.0f) return;
    if (c[2][3] > 0.0f) {
        inv[0] = c[2][3] = 1.0f / c[2][3];
        PlatVu0ScaleVectorXYZ(c[2], c[2], inv[0]);
    }
    if (c[4][3] > 0.0f) {
        inv[1] = c[4][3] = 1.0f / c[4][3];
        PlatVu0ScaleVectorXYZ(c[4], c[4], inv[1]);
    }
    dir[0] = c[4][0] - c[2][0];
    dir[1] = c[4][1] - c[2][1];
    dir[2] = 0.0f;
    dir[3] = 0.0f;
    PlatVu0Normalize(dir, dir);
    perp[0] = -dir[1];
    perp[1] = dir[0];
    perp[2] = 0.0f;
    perp[3] = 0.0f;
    PlatVu0ScaleVector(tmp, perp, r0);
    PlatVu0AddVector(c[3], c[2], tmp);
    PlatVu0ScaleVector(tmp, perp, r1);
    PlatVu0AddVector(c[5], c[4], tmp);
    perp[0] = -perp[0];
    perp[1] = -perp[1];
    PlatVu0ScaleVector(tmp, perp, r0);
    PlatVu0AddVector(c[2], c[2], tmp);
    PlatVu0ScaleVector(tmp, perp, r1);
    PlatVu0AddVector(c[4], c[4], tmp);
    PlatVu0ScaleVector(tmp, dir, r0);
    PlatVu0SubVector(c[0], c[2], tmp);
    PlatVu0SubVector(c[1], c[3], tmp);
    PlatVu0ScaleVector(tmp, dir, r1);
    PlatVu0AddVector(c[6], c[4], tmp);
    PlatVu0AddVector(c[7], c[5], tmp);
    for (i = 0; i < 8; i++) {
        PlatVu0FTOI4Vector(d[i], c[i]);
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
    cnt = 0;
    { KkShape *sh = D_00615E64->shapes + key->id; th = sh->tex; }
    tx = (KkTex *) ((u8 *) th + th->off4);
    p = (KkPkt *) kkPush(0x800);
    p->gif = 0x3000000000000001ULL;
    tag = &p->gif2;
    dma = ((s32) p & 0x0FFFFFFF) | 0x80000000;
    p->regs = 0xEEE;
    p->tex0[0] = tx->w8;
    p->tex0[1] = tx->wC;
    p->tex0r = 6;
    p->tex1[0] = th->b16;
    p->tex1[1] = th->b17;
    p->tex1r = 0x42;
    p->q = D_0061E800.q;
    out = (KkW *) (p + 1);
    src = pos;
    dp = d;
    for (i = 0; i < 8; i++, dp++, src++) {
        if (PlatVu0ClipScreen(c[i]) == 0) {
            if (key->flag) {
                if (i < 4) PlatVu0ScaleVector(tmp, pos[i], inv[0]);
                else PlatVu0ScaleVector(tmp, pos[i], inv[1]);
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
    PlatFlushCache(0);
    PlatDmaSend(PlatDmaGetChan(2), dma);
    PlatGsSyncPath(0, 0);
    { s8 *sp = &D_00372EA0; s32 k = *sp; *sp = k - 1; }
}

#include "data/data_0037.h"
