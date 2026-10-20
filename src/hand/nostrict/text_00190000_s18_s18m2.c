/* func_00192958: MATCHED (session 18, s18m2), hand/nostrict. From s10 w11's 17w draft (nonmatchings/session10/w11__00192958_17w.c). FLAGGED: five local register variables (plain C, no inline asm): the scissor and xyoffset TI header constants pinned to a1/a3 (`register u128 ks asm("$5")`, `kx asm("$7")`; without them local-alloc gives zbuf/xy/scissor birth order on a live-length tie, 17w), and the scy0 chain split as e (a1, the raw field), t (a3, the s32 truncate) and u (a1, t << 4), so the truncate is untied from its source as in the original and the o->pos argument move issues after the addu. b[] in order b0, b1, b2, b3 (exhaustive order search). Each pin is needed: without e 7w, without kx 12w, `u + oy` 1w. Unlike s18m1's 001f2630 f4 pin, these pinned computed values are not dissolved: a truncate and a shift into a hard register survive cse. */
#include "common.h"

typedef int u128 __attribute__((mode(TI)));

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
s32 func_002660c0(GsStoreImage *, s16, s16, s16, s16, s16, s16, s16);
void FlushCache(s32);
s32 sceGsExecStoreImage(GsStoreImage *, void *);
s32 sceGsSyncPath(s32, s32);

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
    register u128 ks asm("$5");
    register u128 kx asm("$7");

    *(u128 *) &pk->frame = 0x800d0;
    pk->frame_a = 76;
    *(u128 *) &pk->zbuf = 0x31000070;
    pk->zbuf_a = 78;
    kx = 0x740000007000ULL;
    *(u128 *) xy = kx;
    pk->xyoffset_a = 24;
    ks = 0x17f000001ff0000ULL;
    *(u128 *) sc = ks;
    pk->scissor_a = 64;
    *(u128 *) &pk->prmodecont = 0;
    pk->prmodecont_a = 26;
    *(u128 *) &pk->colclamp = 1;
    pk->colclamp_a = 70;
    *(u128 *) &pk->dthe = 0;
    pk->dthe_a = 69;
    *(u128 *) &pk->test = 0x5000d;
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
    func_002660c0(&si, pk->zbuf.zbp << 5, pk->frame.fbw, 0x31, ox, oy, w8, h4);
    FlushCache(0);
    sceGsExecStoreImage(&si, buf + 96);
    p = buf + 96;
    sceGsSyncPath(0, 0);
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
