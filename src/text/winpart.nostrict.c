/* The functions of src/text/winpart.c that need nostrict
 * (docs/modules.md "Session 38"), 0x00200000-0x00206e28: the parts of a
 * menu window, each a GIF packet sent through path 2 (with bit 0 of +0x48
 * every point is scaled by +0x74 / +0x78 around the anchor):
 * func_00200038 the row highlights (+0xdc), func_00200648 a list frame of
 * the shape table D_003F2BD8, func_002016b0 / 1988 / 1c60 the three scroll
 * arrows, func_00201f38 the pulsing frame, func_00203028 / func_00203a10
 * the page tabs, func_002040f8 ... the scroll bars, func_002053e8 ...
 * func_00206b70 boxes, lines and sprites. */
#include "common.h"
#include "platform/dma.h"
#include "text/textwin.h"
#include "data/pieces/D_003F1E70.h"
#include "data/pieces/D_003F1A70.h"
#include "data/pieces/D_003F34B0.h"

typedef Q_3f1a70 Q3;
typedef struct { u64 a, b; } QW;
typedef QW Q;
typedef struct { s32 u, v, p0, p1; s32 x, y, z, f; } UX;
typedef UX UVXY;
typedef struct { s32 x, y, z, f; } XY;
typedef struct { s32 x, y, z, w; } V4;
typedef struct { u64 col, q; u32 u, v, p0, p1; s32 x, y, z, f; } V48;
typedef struct { u64 rgba; u64 q; V4 v; } PkV;
typedef struct { u64 a, b; V4 v[2]; } Seg;
typedef struct { u64 tag, regs; s32 r, g, b, a; u64 tag2, regs2; UVXY v[12]; } Blk;
typedef struct { u64 tag, ad, d2, d3, d4, d5, d6, d7, d8, d9, d10, d11; } PH;
typedef struct { u64 tag2, regs2; V48 v[24]; } PQ;
typedef struct {
    u64 tag, regs;
    u64 rgba, q;
    s32 u0, v0, p28, p2c;
    s32 x0, y0, z0, f0;
    s32 u1, v1, p48, p4c;
    s32 x1, y1, z1, f1;
} SprG;
typedef struct {
    s32 r, g, b, a;
    s32 u0, v0, p18, p1c;
    s32 x0, y0, z0, f0;
    s32 u1, v1, p38, p3c;
    s32 x1, y1, z1, f1;
} Spr2;
typedef struct {
    u64 tag, regs;
    UX s[4];
    u64 tag2, regs2;
    u64 col2, q2;
    XY v[2];
    u64 col, q;
    XY w[2];
} P;
typedef struct { u64 tag, regs; UX s[8]; } P2;
typedef struct { u64 tag, regs; UX s[2]; } H2;
typedef struct { u64 h[4]; PkV e[4]; } Pk4;
typedef struct { u64 h[2]; Seg s[5]; } Pk6;
typedef struct { u64 tex; u16 u, v, w, h; s16 x, y; u16 dw, dh; s32 col; } Spr;
typedef struct { u64 tag, ad; u64 d2, d3; u64 d4, d5; s32 x0, y0, z0, w0; s32 x1, y1, z1, w1; } Pk;

#define SC(v, c, fc, s) (s32)((fc) + (f32)((v) - (c)) * (s))

extern u16 D_003F2BD8[][16];

f32 sinf(f32);
u64 *func_0011fb38(s32, s32, u64 *);
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
u32 func_001eddc0(u32, u32, f32);
s32 func_001f4378(TextWin *);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);
s32 func_001fd538(TextWin *);
s32 sceGsSyncPath(s32, s32);

static inline s32 inl_sc(s32 v, s32 c, f32 fc, f32 s) { return fc + (f32)(v - c) * s; }
static inline s32 inl_sc2(s32 v, s32 c, f32 s) { return (f32)c + (f32)(v - c) * s; }

/* func_00200038 (hand/nostrict), s11w72. FLAGGED unnatural shape: every store in the strip loop
 * goes through s32 *p = &blk[i].v[11].x (the last vertex's XYZF qword) with negative indices.
 * loop.c's combine_givs then picks that pointer (it inherits the i*432 chain benefit) as the
 * reduced giv, giving the original's base register blk+416 (addiu t8,s6,528). Any b->field
 * form makes b itself (blk + i*432, no-constant addend +1) the base at offset 0.
 * Natural parts: header qword pairs, flood in struct order after `r = g = b = c` (b, g, r),
 * (x0 + w) written inline (its temp gives the original's stack-slot order), y1 = y + h in each
 * arm, `i` declared between cnt and k (it becomes the dbra counter at 28(sp)). */
void func_00200038(TextWin *o) {
    void *u;
    s32 fl;
    s32 cx;
    s32 cy;
    s32 h;
    s32 fz;
    s32 a;
    s32 cnt;
    s32 i;
    s32 k;
    u64 *buf;
    QW *q;
    s32 *p;
    Blk *blk;
    s32 c;
    s32 n;
    s32 n1;
    s32 w;
    s32 off;
    s32 y;
    s32 y1;
    s32 x0;
    s32 X0;
    s32 X1;
    s32 X2;
    s32 X3;
    s32 Y0;
    s32 Y1;
    f32 sx;
    f32 sy;
    if (o->xcc == 0) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    q = (QW *)(buf + 2);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    q->a = 0x50ab400000000001;
    q->b = 0xeeeee;
    q++;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->a = 0x4007bf8001300000;
    q->b = 22;
    q++;
    q->a = 0x7bf8001400000;
    q->b = 22;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    n = o->xce;
    n1 = n + 1;
    cnt = n;
    h = o->xc4;
    k = ((s16)o->ud0.u.xd0 >> 4) % n1;
    w = o->xc2;
    fz = (w < 832) << 15;
    off = h * (o->ud0.u.xd0 & 0xf) / 16;
    x0 = o->xb0 + o->xbe;
    y = o->xb4 + o->xc0 - off;
    if (off) cnt++;
    fl = o->u48.w.lo & 1;
    a = o->x90;
    if (fl) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
    }
    blk = (Blk *)q;
    for (i = 0; i < cnt; i++, q += 27) {
        p = &blk[i].v[11].x;
        ((u64 *)p)[-52] = 0x1000000000008001;
        ((u64 *)p)[-51] = 1;
        c = o->xdc[k];
        p[-98] = c;
        p[-99] = c;
        p[-100] = c;
        p[-97] = a;
        ((u64 *)p)[-48] = 0x200000000000800c;
        ((u64 *)p)[-47] = 0x43;
        p[-92] = 24;
        p[-91] = 600;
        p[-86] = 0x100000;
        p[-85] = 0x8000;
        p[-84] = 424;
        p[-83] = 1000;
        p[-78] = 0x100000;
        p[-77] = 0;
        p[-76] = 472;
        p[-75] = 600;
        p[-70] = 0x100000;
        p[-69] = 0x8000;
        p[-68] = 872;
        p[-67] = 1000;
        p[-62] = 0x100000;
        p[-61] = fz;
        p[-60] = 920;
        p[-59] = 600;
        p[-54] = 0x100000;
        p[-53] = 0x8000;
        p[-52] = 1320;
        p[-51] = 1000;
        p[-46] = 0x100000;
        p[-45] = 0;
        p[-44] = 1368;
        p[-43] = 600;
        p[-38] = 0x100000;
        p[-37] = 0x8000;
        p[-36] = 1768;
        p[-35] = 1000;
        p[-30] = 0x100000;
        p[-29] = 0;
        p[-28] = 1816;
        p[-27] = 600;
        p[-22] = 0x100000;
        p[-21] = 0x8000;
        p[-20] = 2216;
        p[-19] = 1000;
        p[-14] = 0x100000;
        p[-13] = fz;
        p[-12] = 2264;
        p[-11] = 600;
        p[-6] = 0x100000;
        p[-5] = 0x8000;
        p[-4] = 2664;
        p[-3] = 1000;
        p[2] = 0x100000;
        p[3] = 0;
        if (fl) {
            y1 = y + h;
            X0 = (f32)cx + (f32)(x0 - cx) * sx;
            Y0 = (f32)cy + (f32)(y - cy) * sy;
            X1 = (f32)cx + (f32)(x0 + 416 - cx) * sx;
            Y1 = (f32)cy + (f32)(y1 - cy) * sy;
            X2 = (f32)cx + (f32)((x0 + w) - 416 - cx) * sx;
            X3 = (f32)cx + (f32)((x0 + w) - cx) * sx;
            p[-88] = p[-40] = X0; p[-87] = p[-39] = Y0;
            p[-80] = p[-32] = X1; p[-79] = p[-31] = Y1;
            p[-72] = p[-24] = X1; p[-71] = p[-23] = Y0;
            p[-64] = p[-16] = X2; p[-63] = p[-15] = Y1;
            p[-56] = p[-8] = X2; p[-55] = p[-7] = Y0;
            p[-48] = p[0] = X3; p[-47] = p[1] = Y1;
        } else {
            y1 = y + h;
            p[-88] = p[-40] = x0; p[-87] = p[-39] = y;
            p[-80] = p[-32] = x0 + 416; p[-79] = p[-31] = y1;
            p[-72] = p[-24] = x0 + 416; p[-71] = p[-23] = y;
            p[-64] = p[-16] = (x0 + w) - 416; p[-63] = p[-15] = y1;
            p[-56] = p[-8] = (x0 + w) - 416; p[-55] = p[-7] = y;
            p[-48] = p[0] = (x0 + w); p[-47] = p[1] = y1;
        }
        y = y1;
        k = (k + 1) % n1;
    }
    buf[0] = (((s32)q - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00200648(TextWin *o, s32 type, s32 px, s32 py, s32 pw, s32 *cols) {
    u16 *t;
    u64 *buf;
    u64 *pk;
    u32 ub;
    s32 k, X, Y, W, X1, X2, XR, Y1;
    u32 c0, c1, c2, c3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1536, 128);
    pk = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    ((PH *)pk)->tag = 0x5000000000000001;
    ((PH *)pk)->ad = 0xeeeee;
    ((PH *)pk)->d2 = 0;
    ((PH *)pk)->d3 = 63;
    ((PH *)pk)->d4 = 0x7bf8621413d7c;
    ((PH *)pk)->d5 = 6;
    ((PH *)pk)->d6 = 0x4007bf8001300000;
    ((PH *)pk)->d7 = 22;
    ((PH *)pk)->d8 = 0x7bf8001400000;
    ((PH *)pk)->d9 = 22;
    ((PH *)pk)->d10 = 68;
    ((PH *)pk)->d11 = 66;
    k = o->x90;
    pk = buf + 14;
    c0 = func_001edd88(cols[0], k);
    c1 = func_001edd88(cols[1], k);
    c2 = func_001edd88(cols[2], k);
    c3 = func_001edd88(cols[3], k);

    t = D_003F2BD8[type];
    X = o->xb0 + px * 16;
    Y = o->xb4 + py * 16;
    Y1 = Y + 416;
    W = pw << 4;
    if (W < 832) W = 832;
    XR = X + W;
    X1 = X + 416;
    X2 = XR - 416;
    ((PQ *)pk)->tag2 = 0x30ae400000008018;
    ((PQ *)pk)->regs2 = 1086;
    ((PQ *)pk)->v[0].col = c0;
    ((PQ *)pk)->v[0].q = 1;
    ((PQ *)pk)->v[0].u = t[0];
    ((PQ *)pk)->v[0].v = t[2];
    ((PQ *)pk)->v[0].x = X;
    ((PQ *)pk)->v[0].y = Y;
    ((PQ *)pk)->v[0].z = 0x100000;
    ((PQ *)pk)->v[0].f = 0x8000;
    ((PQ *)pk)->v[1].col = c1;
    ((PQ *)pk)->v[1].q = 1;
    ((PQ *)pk)->v[1].u = t[0];
    ((PQ *)pk)->v[1].v = t[6];
    ((PQ *)pk)->v[1].x = X;
    ((PQ *)pk)->v[1].y = Y1;
    ((PQ *)pk)->v[1].z = 0x100000;
    ((PQ *)pk)->v[1].f = 0x8000;
    ((PQ *)pk)->v[2].col = c0;
    ((PQ *)pk)->v[2].q = 1;
    ((PQ *)pk)->v[2].u = t[4];
    ((PQ *)pk)->v[2].v = t[2];
    ((PQ *)pk)->v[2].x = X1;
    ((PQ *)pk)->v[2].y = Y;
    ((PQ *)pk)->v[2].z = 0x100000;
    ((PQ *)pk)->v[2].f = 0;
    ((PQ *)pk)->v[3].col = c1;
    ((PQ *)pk)->v[3].q = 1;
    ((PQ *)pk)->v[3].u = t[4];
    ((PQ *)pk)->v[3].v = t[6];
    ((PQ *)pk)->v[3].x = X1;
    ((PQ *)pk)->v[3].y = Y1;
    ((PQ *)pk)->v[3].z = 0x100000;
    ((PQ *)pk)->v[3].f = 0;
    ((PQ *)pk)->v[4].col = c0;
    ((PQ *)pk)->v[4].q = 1;
    ((PQ *)pk)->v[4].u = 472;
    ((PQ *)pk)->v[4].v = 600;
    ((PQ *)pk)->v[4].x = X1;
    ((PQ *)pk)->v[4].y = Y;
    ((PQ *)pk)->v[4].z = 0x100000;
    ((PQ *)pk)->v[4].f = 0x8000;
    ((PQ *)pk)->v[5].col = c1;
    ((PQ *)pk)->v[5].q = 1;
    ((PQ *)pk)->v[5].u = 472;
    ((PQ *)pk)->v[5].v = 1000;
    ((PQ *)pk)->v[5].x = X1;
    ((PQ *)pk)->v[5].y = Y1;
    ((PQ *)pk)->v[5].z = 0x100000;
    ((PQ *)pk)->v[5].f = 0x8000;
    ((PQ *)pk)->v[6].col = c0;
    ((PQ *)pk)->v[6].q = 1;
    ((PQ *)pk)->v[6].u = 872;
    ((PQ *)pk)->v[6].v = 600;
    ((PQ *)pk)->v[6].x = X2;
    ((PQ *)pk)->v[6].y = Y;
    ((PQ *)pk)->v[6].z = 0x100000;
    ((PQ *)pk)->v[6].f = 0;
    ((PQ *)pk)->v[7].col = c1;
    ((PQ *)pk)->v[7].q = 1;
    ((PQ *)pk)->v[7].u = 872;
    ((PQ *)pk)->v[7].v = 1000;
    ((PQ *)pk)->v[7].x = X2;
    ((PQ *)pk)->v[7].y = Y1;
    ((PQ *)pk)->v[7].z = 0x100000;
    ((PQ *)pk)->v[7].f = 0;
    ((PQ *)pk)->v[8].col = c0;
    ((PQ *)pk)->v[8].q = 1;
    ((PQ *)pk)->v[8].u = t[8];
    ((PQ *)pk)->v[8].v = t[10];
    ((PQ *)pk)->v[8].x = X2;
    ((PQ *)pk)->v[8].y = Y;
    ((PQ *)pk)->v[8].z = 0x100000;
    ((PQ *)pk)->v[8].f = 0x8000;
    ((PQ *)pk)->v[9].col = c1;
    ((PQ *)pk)->v[9].q = 1;
    ((PQ *)pk)->v[9].u = t[8];
    ((PQ *)pk)->v[9].v = t[14];
    ((PQ *)pk)->v[9].x = X2;
    ((PQ *)pk)->v[9].y = Y1;
    ((PQ *)pk)->v[9].z = 0x100000;
    ((PQ *)pk)->v[9].f = 0x8000;
    ((PQ *)pk)->v[10].col = c0;
    ((PQ *)pk)->v[10].q = 1;
    ((PQ *)pk)->v[10].u = t[12];
    ((PQ *)pk)->v[10].v = t[10];
    ((PQ *)pk)->v[10].x = XR;
    ((PQ *)pk)->v[10].y = Y;
    ((PQ *)pk)->v[10].z = 0x100000;
    ((PQ *)pk)->v[10].f = 0;
    ((PQ *)pk)->v[11].col = c1;
    ((PQ *)pk)->v[11].q = 1;
    ((PQ *)pk)->v[11].u = t[12];
    ((PQ *)pk)->v[11].v = t[14];
    ((PQ *)pk)->v[11].x = XR;
    ((PQ *)pk)->v[11].y = Y1;
    ((PQ *)pk)->v[11].z = 0x100000;
    ((PQ *)pk)->v[11].f = 0;
    ((PQ *)pk)->v[12].col = c2;
    ((PQ *)pk)->v[12].q = 1;
    ((PQ *)pk)->v[12].u = t[1];
    ((PQ *)pk)->v[12].v = t[3];
    ((PQ *)pk)->v[12].x = X;
    ((PQ *)pk)->v[12].y = Y;
    ((PQ *)pk)->v[12].z = 0x100000;
    ((PQ *)pk)->v[12].f = 0x8000;
    ((PQ *)pk)->v[13].col = c3;
    ((PQ *)pk)->v[13].q = 1;
    ((PQ *)pk)->v[13].u = t[1];
    ((PQ *)pk)->v[13].v = t[7];
    ((PQ *)pk)->v[13].x = X;
    ((PQ *)pk)->v[13].y = Y1;
    ((PQ *)pk)->v[13].z = 0x100000;
    ((PQ *)pk)->v[13].f = 0x8000;
    ((PQ *)pk)->v[14].col = c2;
    ((PQ *)pk)->v[14].q = 1;
    ((PQ *)pk)->v[14].u = t[5];
    ((PQ *)pk)->v[14].v = t[3];
    ((PQ *)pk)->v[14].x = X1;
    ((PQ *)pk)->v[14].y = Y;
    ((PQ *)pk)->v[14].z = 0x100000;
    ((PQ *)pk)->v[14].f = 0;
    ((PQ *)pk)->v[15].col = c3;
    ((PQ *)pk)->v[15].q = 1;
    ((PQ *)pk)->v[15].u = t[5];
    ((PQ *)pk)->v[15].v = t[7];
    ((PQ *)pk)->v[15].x = X1;
    ((PQ *)pk)->v[15].y = Y1;
    ((PQ *)pk)->v[15].z = 0x100000;
    ((PQ *)pk)->v[15].f = 0;
    ((PQ *)pk)->v[16].col = c2;
    ((PQ *)pk)->v[16].q = 1;
    ((PQ *)pk)->v[16].u = 1816;
    ((PQ *)pk)->v[16].v = 600;
    ((PQ *)pk)->v[16].x = X1;
    ((PQ *)pk)->v[16].y = Y;
    ((PQ *)pk)->v[16].z = 0x100000;
    ((PQ *)pk)->v[16].f = 0x8000;
    ((PQ *)pk)->v[17].col = c3;
    ((PQ *)pk)->v[17].q = 1;
    ((PQ *)pk)->v[17].u = 1816;
    ((PQ *)pk)->v[17].v = 1000;
    ((PQ *)pk)->v[17].x = X1;
    ((PQ *)pk)->v[17].y = Y1;
    ((PQ *)pk)->v[17].z = 0x100000;
    ((PQ *)pk)->v[17].f = 0x8000;
    ((PQ *)pk)->v[18].col = c2;
    ((PQ *)pk)->v[18].q = 1;
    ((PQ *)pk)->v[18].u = 2216;
    ((PQ *)pk)->v[18].v = 600;
    ((PQ *)pk)->v[18].x = X2;
    ((PQ *)pk)->v[18].y = Y;
    ((PQ *)pk)->v[18].z = 0x100000;
    ((PQ *)pk)->v[18].f = 0;
    ((PQ *)pk)->v[19].col = c3;
    ((PQ *)pk)->v[19].q = 1;
    ((PQ *)pk)->v[19].u = 2216;
    ((PQ *)pk)->v[19].v = 1000;
    ((PQ *)pk)->v[19].x = X2;
    ((PQ *)pk)->v[19].y = Y1;
    ((PQ *)pk)->v[19].z = 0x100000;
    ((PQ *)pk)->v[19].f = 0;
    ((PQ *)pk)->v[20].col = c2;
    ((PQ *)pk)->v[20].q = 1;
    ((PQ *)pk)->v[20].u = t[9];
    ((PQ *)pk)->v[20].v = t[11];
    ((PQ *)pk)->v[20].x = X2;
    ((PQ *)pk)->v[20].y = Y;
    ((PQ *)pk)->v[20].z = 0x100000;
    ((PQ *)pk)->v[20].f = 0x8000;
    ((PQ *)pk)->v[21].col = c3;
    ((PQ *)pk)->v[21].q = 1;
    ((PQ *)pk)->v[21].u = t[9];
    ((PQ *)pk)->v[21].v = t[15];
    ((PQ *)pk)->v[21].x = X2;
    ((PQ *)pk)->v[21].y = Y1;
    ((PQ *)pk)->v[21].z = 0x100000;
    ((PQ *)pk)->v[21].f = 0x8000;
    ((PQ *)pk)->v[22].col = c2;
    ((PQ *)pk)->v[22].q = 1;
    ((PQ *)pk)->v[22].u = t[13];
    ((PQ *)pk)->v[22].v = t[11];
    ((PQ *)pk)->v[22].x = XR;
    ((PQ *)pk)->v[22].y = Y;
    ((PQ *)pk)->v[22].z = 0x100000;
    ((PQ *)pk)->v[22].f = 0;
    ((PQ *)pk)->v[23].col = c3;
    ((PQ *)pk)->v[23].q = 1;
    ((PQ *)pk)->v[23].u = t[13];
    ((PQ *)pk)->v[23].v = t[15];
    ((PQ *)pk)->v[23].x = XR;
    ((PQ *)pk)->v[23].y = Y1;
    ((PQ *)pk)->v[23].z = 0x100000;
    ((PQ *)pk)->v[23].f = 0;

    if (o->u48.w.lo & 1) {
        s32 cx = func_001f4570(o);
        s32 cy = func_001f45e0(o);
        f32 fcy, fcx, sy, sx;
        s32 nY, nY1, nX, nXR, nX1, nX2;
        sx = o->x74; sy = o->x78;
        fcy = cy; fcx = cx;
        nX = SC(((PQ *)pk)->v[0].x, cx, fcx, sx);
        nY = SC(((PQ *)pk)->v[0].y, cy, fcy, sy);
        nY1 = SC(((PQ *)pk)->v[1].y, cy, fcy, sy);
        nX1 = SC(((PQ *)pk)->v[2].x, cx, fcx, sx);
        nX2 = SC(((PQ *)pk)->v[6].x, cx, fcx, sx);
        nXR = SC(((PQ *)pk)->v[10].x, cx, fcx, sx);
        ((PQ *)pk)->v[0].x = nX; ((PQ *)pk)->v[0].y = nY;
        ((PQ *)pk)->v[1].x = nX; ((PQ *)pk)->v[1].y = nY1;
        ((PQ *)pk)->v[2].x = nX1; ((PQ *)pk)->v[2].y = nY;
        ((PQ *)pk)->v[3].x = nX1; ((PQ *)pk)->v[3].y = nY1;
        ((PQ *)pk)->v[4].x = nX1; ((PQ *)pk)->v[4].y = nY;
        ((PQ *)pk)->v[5].x = nX1; ((PQ *)pk)->v[5].y = nY1;
        ((PQ *)pk)->v[6].x = nX2; ((PQ *)pk)->v[6].y = nY;
        ((PQ *)pk)->v[7].x = nX2; ((PQ *)pk)->v[7].y = nY1;
        ((PQ *)pk)->v[8].x = nX2; ((PQ *)pk)->v[8].y = nY;
        ((PQ *)pk)->v[9].x = nX2; ((PQ *)pk)->v[9].y = nY1;
        ((PQ *)pk)->v[10].x = nXR; ((PQ *)pk)->v[10].y = nY;
        ((PQ *)pk)->v[11].x = nXR; ((PQ *)pk)->v[11].y = nY1;
        ((PQ *)pk)->v[12].x = nX; ((PQ *)pk)->v[12].y = nY;
        ((PQ *)pk)->v[13].x = nX; ((PQ *)pk)->v[13].y = nY1;
        ((PQ *)pk)->v[14].x = nX1; ((PQ *)pk)->v[14].y = nY;
        ((PQ *)pk)->v[15].x = nX1; ((PQ *)pk)->v[15].y = nY1;
        ((PQ *)pk)->v[16].x = nX1; ((PQ *)pk)->v[16].y = nY;
        ((PQ *)pk)->v[17].x = nX1; ((PQ *)pk)->v[17].y = nY1;
        ((PQ *)pk)->v[18].x = nX2; ((PQ *)pk)->v[18].y = nY;
        ((PQ *)pk)->v[19].x = nX2; ((PQ *)pk)->v[19].y = nY1;
        ((PQ *)pk)->v[20].x = nX2; ((PQ *)pk)->v[20].y = nY;
        ((PQ *)pk)->v[21].x = nX2; ((PQ *)pk)->v[21].y = nY1;
        ((PQ *)pk)->v[22].x = nXR; ((PQ *)pk)->v[22].y = nY;
        ((PQ *)pk)->v[23].x = nXR; ((PQ *)pk)->v[23].y = nY1;
    }
    buf[0] = ((((s32)((PQ *)pk + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_002016b0(TextWin *o, s32 x, s32 y, u32 c) {
    u64 *buf;
    Q *q;
    SprG *s;
    void *u;
    s32 cx, cy, X, Y;
    f32 fx, fy, a, b, d, e;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    q = (Q *)buf + 1;
    q->a = 0x50ab400000000001;
    q->b = 0xeeeee;
    q++;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    s = (SprG *)q;
    c = func_001edd88(c, o->x90);
    X = o->xb0 + (x << 4);
    Y = o->xb4 + (y << 4);
    s->tag = 0x5000000000008001;
    s->regs = 0x4343e;
    s->rgba = c;
    s->x0 = X;
    s->y0 = Y;
    s->z0 = 0x100000;
    s->q = 1;
    s->u0 = 24;
    s->f1 = 0;
    s->v0 = 1048;
    s->f0 = 0x8000;
    s->u1 = 680;
    s->v1 = 1384;
    s->x1 = X + 672;
    s->y1 = Y + 352;
    s->z1 = 0x100000;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        a = o->x74;
        fx = cx;
        fy = cy;
        b = o->x78;
        s->x0 = fx + (f32)(s->x0 - cx) * a;
        s->y0 = fy + (f32)(s->y0 - cy) * b;
        s->x1 = fx + (f32)(s->x1 - cx) * a;
        s->y1 = fy + (f32)(s->y1 - cy) * b;
    }
    buf[0] = 0x7000000c;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00201988(TextWin *o, s32 x, s32 y, u32 c) {
    u64 *buf;
    Q *q;
    SprG *s;
    void *u;
    s32 cx, cy, X, Y;
    f32 fx, fy, a, b, d, e;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    q = (Q *)buf + 1;
    q->a = 0x50ab400000000001;
    q->b = 0xeeeee;
    q++;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    s = (SprG *)q;
    c = func_001edd88(c, o->x90);
    X = o->xb0 + (x << 4);
    Y = o->xb4 + (y << 4);
    s->tag = 0x5000000000008001;
    s->regs = 0x4343e;
    s->rgba = c;
    s->x0 = X;
    s->y0 = Y;
    s->z0 = 0x100000;
    s->q = 1;
    s->u0 = 1320;
    s->f1 = 0;
    s->v0 = 2952;
    s->f0 = 0x8000;
    s->u1 = 2216;
    s->v1 = 3272;
    s->x1 = X + 896;
    s->y1 = Y + 320;
    s->z1 = 0x100000;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        a = o->x74;
        fx = cx;
        fy = cy;
        b = o->x78;
        s->x0 = fx + (f32)(s->x0 - cx) * a;
        s->y0 = fy + (f32)(s->y0 - cy) * b;
        s->x1 = fx + (f32)(s->x1 - cx) * a;
        s->y1 = fy + (f32)(s->y1 - cy) * b;
    }
    buf[0] = 0x7000000c;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00201c60(TextWin *o, s32 x, s32 y, u32 c) {
    u64 *buf;
    Q *q;
    SprG *s;
    void *u;
    s32 cx, cy, X, Y;
    f32 fx, fy, a, b, d, e;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    q = (Q *)buf + 1;
    q->a = 0x50ab400000000001;
    q->b = 0xeeeee;
    q++;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    s = (SprG *)q;
    c = func_001edd88(c, o->x90);
    X = o->xb0 + (x << 4);
    Y = o->xb4 + (y << 4);
    s->tag = 0x5000000000008001;
    s->regs = 0x4343e;
    s->rgba = c;
    s->x0 = X;
    s->y0 = Y;
    s->z0 = 0x100000;
    s->q = 1;
    s->u0 = 712;
    s->f1 = 0;
    s->v0 = 2776;
    s->f0 = 0x8000;
    s->u1 = 1240;
    s->v1 = 3112;
    s->x1 = X + 544;
    s->y1 = Y + 352;
    s->z1 = 0x100000;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        a = o->x74;
        fx = cx;
        fy = cy;
        b = o->x78;
        s->x0 = fx + (f32)(s->x0 - cx) * a;
        s->y0 = fy + (f32)(s->y0 - cy) * b;
        s->x1 = fx + (f32)(s->x1 - cx) * a;
        s->y1 = fy + (f32)(s->y1 - cy) * b;
    }
    buf[0] = 0x7000000c;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00201f38(TextWin *o) {
    u64 *buf;
    Spr2 *s;
    void *u;
    s32 cx, cy, t, w, c, d, X, Y, xa, ya, k;
    f32 fx, fy, a, b;
    if (o->xcc == 0) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    s = (Spr2 *)(buf + 2);

    ((u64 *)s)[0] = 0x50ab400000000001;
    ((u64 *)s)[2] = 0;
    ((u64 *)s)[1] = 0xeeeee;
    ((u64 *)s)[3] = 63;
    ((u64 *)s)[4] = 0x7bf8621413d7c;
    ((u64 *)s)[5] = 6;
    ((u64 *)s)[7] = 22;
    ((u64 *)s)[6] = 0x4007bf8001300000;
    ((u64 *)s)[8] = 0x407bf8001400000;
    ((u64 *)s)[9] = 22;
    ((u64 *)s)[10] = 72;
    ((u64 *)s)[11] = 66;
    ((u64 *)s)[12] = 0x5000000000008001;
    ((u64 *)s)[13] = 0x43431;

    s = (Spr2 *)(buf + 16);
    t = o->x94;
    w = sinf((f32)(t % 32) * 0.03125f * 3.141592801f) * 240.0f + 480.0f;
    d = o->ud0.s.xd2;
    c = o->xdc[d >> 4] * 2 - 128;
    k = o->xc2;
    xa = o->xb0 + o->xbe + k;
    X = xa - w / 2;
    ya = o->xb4 + o->xc0 + o->xc4 * d / 16;
    s->b = c;
    s->g = c;
    s->r = c;
    s->a = o->x90;
    s->u0 = 3608;
    s->v0 = 920;
    s->f0 = 0x8000;
    s->u1 = 4072;
    s->v1 = 1384;
    s->z0 = 0x100000;
    s->z1 = 0x100000;
    s->f1 = 0;
    Y = ya - w / 2;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        a = o->x74;
        b = o->x78;
        fx = cx;
        fy = cy;
        s->x0 = fx + (f32)(X - cx) * a;
        s->y0 = fy + (f32)(Y - cy) * b;
        s->x1 = fx + (f32)(X + w - cx) * a;
        s->y1 = fy + (f32)(Y + w - cy) * b;
    } else {
        s->x1 = X + w;
        s->y1 = Y + w;
        s->x0 = X;
        s->y0 = Y;
    }
    s++;
    buf[0] = (((s32)s - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00202300(TextWin *w, s32 a1, s32 a2) {
    u64 *buf, *p;
    s32 *q;
    u32 ub, al;
    s32 x, y, cx, cy, l, t, r, b;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x50ab400000000001;
    p[1] = 0xeeeee;
    p[2] = 0;
    p[3] = 63;
    p[4] = 0x0007bf8621413d7c;
    p[5] = 6;
    p[6] = 0x4007bf8001300000;
    p[7] = 22;
    p[8] = 0x0407bf8001400000;
    p[9] = 22;
    p[10] = 72;
    p[11] = 66;
    p[12] = 0x5000000000008001;
    p[13] = 0x4343e;
    al = (u32)((sinf((f32)((s32)w->x94 % 32) * 0.03125f * 3.1415928f) * 64.0f + 64.0f) * (f32)w->x90) >> 7;
    q = (s32 *)p;
    x = w->xb0 + a1 * 16;
    y = w->xb4 + a2 * 16;
    l = x - 240; t = y - 240; r = x + 240; b = y + 240;
    p[14] = (al << 24) | 0x808080;
    p[15] = 1;
    q[32] = 3608;
    q[33] = 920;
    q[36] = l;
    q[37] = t;
    q[38] = 0x100000;
    q[39] = 0x8000;
    q[40] = 4072;
    q[41] = 1384;
    q[44] = r;
    q[45] = b;
    q[46] = 0x100000;
    q[47] = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (q[36] - cx) * sx;
        t1 = fcy + (q[37] - cy) * sy;
        t2 = fcx + (q[44] - cx) * sx;
        q[36] = t0;
        q[37] = t1;
        t3 = fcy + (q[45] - cy) * sy;
        q[45] = t3;
        q[44] = t2;
    }
    buf[0] = ((((s32)p - (s32)buf + 192) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00203028(TextWin *o, s32 x0, s32 y, s32 x1, s32 c) {
    s32 xs[2];
    s32 yy[2];
    u64 *buf;
    Q *h;
    Q *q;
    u32 ub;
    s32 Y, n, hf, a, b, cur, i, fl, cx, cy;
    f32 sx, sy, fcx, fcy;
    s32 X0, Y0, X1, Y2, X4, X5;
    if (o->xd8 < 2) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(2048, 128);
    h = (Q *)buf + 1;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    h->a = 0x6000000000008001;
    h->b = 0xeeeeee;
    q = h + 1;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    q->a = func_001edd88(c, o->x90);
    q->b = 1;
    q++;
    xs[0] = o->xb0 + (x0 << 4);
    xs[1] = o->xb0 + (x1 << 4);
    Y = o->xb4 + (y << 4);
    n = (((xs[1] - xs[0]) >> 4) - 11) / 4 - 2;
    if (n < 0) n = 0;
    else if (n > 50) n = 50;
    hf = n / 2;
    cur = func_001fd538(o);
    a = cur;
    if (n < a) a = n;
    b = o->xd8 - cur - 1;
    if (n < b) b = n;
    if (n < a + b) {
        if (a == n) {
            if (hf < b) { b = hf; a = b; }
            else a -= b;
        } else if (b == n) {
            if (hf < a) { b = hf; a = b; }
            else b -= a;
        } else if (!(a < hf)) {
            if (!(b < hf)) { b = hf; a = b; }
            else a = n - b;
        } else if (!(b < hf)) {
            b = n - a;
        }
    }
    ((P2 *)q)->tag = 0x80aa400000008002;
    ((P2 *)q)->regs = 0x43434343;
    if (a) {
        ((P2 *)q)->s[0].u = 2280; ((P2 *)q)->s[0].v = 1064; ((P2 *)q)->s[1].u = 2120; ((P2 *)q)->s[1].v = 1064;
        ((P2 *)q)->s[2].u = 2280; ((P2 *)q)->s[2].v = 1256; ((P2 *)q)->s[3].u = 2120; ((P2 *)q)->s[3].v = 1256;
    } else {
        ((P2 *)q)->s[0].u = 2472; ((P2 *)q)->s[0].v = 1064; ((P2 *)q)->s[1].u = 2312; ((P2 *)q)->s[1].v = 1064;
        ((P2 *)q)->s[2].u = 2472; ((P2 *)q)->s[2].v = 1256; ((P2 *)q)->s[3].u = 2312; ((P2 *)q)->s[3].v = 1256;
    }
    if (b) {
        ((P2 *)q)->s[4].u = 2120; ((P2 *)q)->s[4].v = 1064; ((P2 *)q)->s[5].u = 2280; ((P2 *)q)->s[5].v = 1064;
        ((P2 *)q)->s[6].u = 2120; ((P2 *)q)->s[6].v = 1256; ((P2 *)q)->s[7].u = 2280; ((P2 *)q)->s[7].v = 1256;
    } else {
        ((P2 *)q)->s[4].u = 2328; ((P2 *)q)->s[4].v = 1064; ((P2 *)q)->s[5].u = 2488; ((P2 *)q)->s[5].v = 1064;
        ((P2 *)q)->s[6].u = 2328; ((P2 *)q)->s[6].v = 1256; ((P2 *)q)->s[7].u = 2488; ((P2 *)q)->s[7].v = 1256;
    }

    ((P2 *)q)->s[0].x = xs[0];
    ((P2 *)q)->s[0].y = Y;
    ((P2 *)q)->s[0].z = 0x100000;
    ((P2 *)q)->s[0].f = 0x8000;
    ((P2 *)q)->s[1].x = xs[0] + 144;
    ((P2 *)q)->s[1].y = Y;
    ((P2 *)q)->s[1].z = 0x100000;
    ((P2 *)q)->s[1].f = 0x8000;
    ((P2 *)q)->s[2].x = ((P2 *)q)->s[0].x;
    ((P2 *)q)->s[2].y = Y + 192;
    ((P2 *)q)->s[2].z = 0x100000;
    ((P2 *)q)->s[2].f = 0;
    ((P2 *)q)->s[3].x = ((P2 *)q)->s[1].x;
    ((P2 *)q)->s[3].y = Y + 192;
    ((P2 *)q)->s[3].z = 0x100000;
    ((P2 *)q)->s[3].f = 0;
    ((P2 *)q)->s[4].x = xs[1];
    ((P2 *)q)->s[4].y = Y;
    ((P2 *)q)->s[4].z = 0x100000;
    ((P2 *)q)->s[4].f = 0x8000;
    ((P2 *)q)->s[5].x = xs[1] + 144;
    ((P2 *)q)->s[5].y = Y;
    ((P2 *)q)->s[5].z = 0x100000;
    ((P2 *)q)->s[5].f = 0x8000;
    ((P2 *)q)->s[6].x = ((P2 *)q)->s[4].x;
    ((P2 *)q)->s[6].y = Y + 192;
    ((P2 *)q)->s[6].z = 0x100000;
    ((P2 *)q)->s[6].f = 0;
    ((P2 *)q)->s[7].x = ((P2 *)q)->s[5].x;
    ((P2 *)q)->s[7].y = Y + 192;
    ((P2 *)q)->s[7].z = 0x100000;
    ((P2 *)q)->s[7].f = 0;

    fl = o->u48.w.lo & 1;
    if (fl) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fcx = cx;
        fcy = cy;
        X0 = inl_sc(((P2 *)q)->s[0].x, cx, fcx, sx);
        Y0 = inl_sc(((P2 *)q)->s[0].y, cy, fcy, sy);
        X1 = inl_sc(((P2 *)q)->s[1].x, cx, fcx, sx);
        Y2 = inl_sc(((P2 *)q)->s[2].y, cy, fcy, sy);
        X4 = inl_sc(((P2 *)q)->s[4].x, cx, fcx, sx);
        X5 = inl_sc(((P2 *)q)->s[5].x, cx, fcx, sx);
        ((P2 *)q)->s[0].x = X0; ((P2 *)q)->s[0].y = Y0;
        ((P2 *)q)->s[1].x = X1; ((P2 *)q)->s[1].y = Y0;
        ((P2 *)q)->s[2].x = X0; ((P2 *)q)->s[2].y = Y2;
        ((P2 *)q)->s[3].x = X1; ((P2 *)q)->s[3].y = Y2;
        ((P2 *)q)->s[4].x = X4; ((P2 *)q)->s[4].y = Y0;
        ((P2 *)q)->s[5].x = X5; ((P2 *)q)->s[5].y = Y0;
        ((P2 *)q)->s[6].x = X4; ((P2 *)q)->s[6].y = Y2;
        ((P2 *)q)->s[7].x = X5; ((P2 *)q)->s[7].y = Y2;
    }
    buf[0] = ((((s32)((P2 *)q + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    yy[0] = ((P2 *)q)->s[0].y;
    yy[1] = ((P2 *)q)->s[2].y;
    ((H2 *)h)->tag = 0x40ab400000008001;
    ((H2 *)h)->regs = 0x4343;
    xs[0] += 176;
    ((H2 *)h)->s[0].u = 2040; ((H2 *)h)->s[0].v = 1064;
    ((H2 *)h)->s[0].y = yy[0]; ((H2 *)h)->s[0].z = 0x100000; ((H2 *)h)->s[0].f = 0x8000;
    ((H2 *)h)->s[1].u = 2056; ((H2 *)h)->s[1].v = 1224;
    ((H2 *)h)->s[1].y = yy[1]; ((H2 *)h)->s[1].z = 0x100000; ((H2 *)h)->s[1].f = 0;
    buf[0] = ((((s32)((H2 *)h + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    for (i = a; i > 0; i--) {
        ((H2 *)h)->s[0].x = xs[0];
        ((H2 *)h)->s[1].x = xs[0] + 32;
        if (fl) {
            ((H2 *)h)->s[0].x = inl_sc(((H2 *)h)->s[0].x, cx, cx, sx);
            ((H2 *)h)->s[1].x = inl_sc(((H2 *)h)->s[1].x, cx, cx, sx);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        sceGsSyncPath(0, 0);
        xs[0] += 64;
    }
    xs[1] -= 64;
    for (i = b; i > 0; i--) {
        ((H2 *)h)->s[0].x = xs[1];
        ((H2 *)h)->s[1].x = xs[1] + 32;
        if (fl) {
            ((H2 *)h)->s[0].x = inl_sc(((H2 *)h)->s[0].x, cx, cx, sx);
            ((H2 *)h)->s[1].x = inl_sc(((H2 *)h)->s[1].x, cx, cx, sx);
        }
        PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
        sceGsSyncPath(0, 0);
        xs[1] -= 64;
    }
    func_001220b8(buf);
}


void func_00203a10(TextWin *o, s32 x) {
    s32 ys[2];
    s32 ms[2];
    u64 *buf;
    Q *q;
    u32 ub, al, col;
    s32 t, a, b, X, h;
    s32 u0, v0, u1, v1;
    s32 cx, cy;
    f32 r, sx, sy, fcx, fcy;
    s32 X0, X1, X2, X3, Y0, Y1, Y2, Y3, Y4, Y5, Y6, Y7;
    if (o->xcc == 0) return;
    if (!(o->xce < o->xcc)) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    q = (Q *)buf + 1;
    q->a = 0x6000000000008001;
    q->b = 0xeeeeee;
    q++;
    q->b = 63;
    q->a = 0;
    q++;
    q->a = 0x7bf8621413d7c;
    q->b = 6;
    q++;
    q->b = 22;
    q->a = 0x4007bf8001300000;
    q++;
    q->b = 22;
    q->a = 0x7bf8001400000;
    q++;
    q->a = 68;
    q->b = 66;
    q++;
    t = o->x94;
    al = o->x90;
    al <<= 24;
    r = sinf((f32)(t % 64) * 0.015625f * 3.1415928f);
    a = (s32)(r * 64.0f) + 64;
    b = (s32)(r * 16.0f) + 64;
    col = (a | al) | ((b << 16) | (a << 8));
    q->b = 1;
    q->a = col;
    q++;
    ((P *)q)->tag = 0x40ab400000008002;
    ((P *)q)->regs = 0x4343;
    X = o->xb0 + (x << 4);
    ys[0] = o->xb4 + o->xc0;
    ys[1] = ys[0] + (((o->xc4 >> 4) * o->xce - (o->xc8 >> 4) - 9) << 4);
    if (o->ud0.s.xd0 >> 4) {
        ((P *)q)->s[0].u = 1768; ((P *)q)->s[0].v = 1048; ((P *)q)->s[1].u = 1960; ((P *)q)->s[1].v = 1192;
    } else {
        ((P *)q)->s[0].u = 1768; ((P *)q)->s[0].v = 1240; ((P *)q)->s[1].u = 1960; ((P *)q)->s[1].v = 1384;
    }
    if (o->xcc != (o->ud0.s.xd0 >> 4) + o->xce) {
        ((P *)q)->s[2].u = 1768; ((P *)q)->s[2].v = 1176; ((P *)q)->s[3].u = 1960; ((P *)q)->s[3].v = 1032;
    } else {
        ((P *)q)->s[2].u = 1768; ((P *)q)->s[2].v = 1368; ((P *)q)->s[3].u = 1960; ((P *)q)->s[3].v = 1224;
    }
    ((P *)q)->s[0].x = X; ((P *)q)->s[0].y = ys[0]; ((P *)q)->s[0].z = 0x100000; ((P *)q)->s[0].f = 0x8000;
    ((P *)q)->s[1].x = X + 192; ((P *)q)->s[1].y = ys[0] + 144; ((P *)q)->s[1].z = 0x100000; ((P *)q)->s[1].f = 0;
    ((P *)q)->s[2].x = X; ((P *)q)->s[2].y = ys[1]; ((P *)q)->s[2].z = 0x100000; ((P *)q)->s[2].f = 0x8000;
    ((P *)q)->s[3].x = X + 192; ((P *)q)->s[3].y = ys[1] + 144; ((P *)q)->s[3].z = 0x100000; ((P *)q)->s[3].f = 0;
    ((P *)q)->tag2 = 0x3023400000008002;
    ((P *)q)->regs2 = 0x44e;
    ys[0] += 176;
    ys[1] -= 32;
    ((P *)q)->col2 = al | 0x404040;
    ((P *)q)->q2 = 1;
    ((P *)q)->v[0].x = ((P *)q)->s[0].x; ((P *)q)->v[0].y = ys[0]; ((P *)q)->v[0].z = 0x100000; ((P *)q)->v[0].f = 0;
    ((P *)q)->v[1].x = ((P *)q)->s[1].x; ((P *)q)->v[1].y = ys[1]; ((P *)q)->v[1].z = 0x100000; ((P *)q)->v[1].f = 0;
    h = ys[1] - ys[0];
    ms[0] = ys[0] + (h * o->ud0.s.xd0 >> 4) / o->xcc;
    ms[1] = ms[0] + h * o->xce / o->xcc;
    ((P *)q)->col = col;
    ((P *)q)->q = 1;
    ((P *)q)->w[0].x = ((P *)q)->s[0].x + 48; ((P *)q)->w[0].y = ms[0]; ((P *)q)->w[0].z = 0x100000; ((P *)q)->w[0].f = 0x8000;
    ((P *)q)->w[1].x = ((P *)q)->s[1].x - 48; ((P *)q)->w[1].y = ms[1]; ((P *)q)->w[1].z = 0x100000; ((P *)q)->w[1].f = 0;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fcx = cx;
        fcy = cy;
        X0 = inl_sc(((P *)q)->s[0].x, cx, fcx, sx);
        X1 = inl_sc(((P *)q)->s[1].x, cx, fcx, sx);
        Y0 = inl_sc(((P *)q)->s[0].y, cy, fcy, sy);
        Y1 = inl_sc(((P *)q)->s[1].y, cy, fcy, sy);
        Y2 = inl_sc(((P *)q)->s[2].y, cy, fcy, sy);
        Y3 = inl_sc(((P *)q)->s[3].y, cy, fcy, sy);
        Y4 = inl_sc(((P *)q)->v[0].y, cy, fcy, sy);
        Y5 = inl_sc(((P *)q)->v[1].y, cy, fcy, sy);
        X2 = inl_sc(((P *)q)->w[0].x, cx, fcx, sx);
        Y6 = inl_sc(((P *)q)->w[0].y, cy, fcy, sy);
        X3 = inl_sc(((P *)q)->w[1].x, cx, fcx, sx);
        Y7 = inl_sc(((P *)q)->w[1].y, cy, fcy, sy);
        ((P *)q)->s[0].x = X0; ((P *)q)->s[0].y = Y0;
        ((P *)q)->s[1].x = X1; ((P *)q)->s[1].y = Y1;
        ((P *)q)->s[2].x = X0; ((P *)q)->s[2].y = Y2;
        ((P *)q)->s[3].x = X1; ((P *)q)->s[3].y = Y3;
        ((P *)q)->v[0].x = X0; ((P *)q)->v[0].y = Y4;
        ((P *)q)->v[1].x = X1; ((P *)q)->v[1].y = Y5;
        ((P *)q)->w[0].x = X2; ((P *)q)->w[0].y = Y6;
        ((P *)q)->w[1].x = X3; ((P *)q)->w[1].y = Y7;
    }
    buf[0] = ((((s32)((P *)q + 1) - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


/* func_002040f8: hand/nostrict, block-local y in the first scaled branch */
void func_002040f8(TextWin *o) {
    s32 col[3][4];
    u64 *buf, *p, *p0;
    u32 ub;
    s32 x, y, y2, d, k, al, cx, cy;
    f32 f, sx, sy;
    if (o->xcc == 0) return;
    if (!(o->xce < o->xcc)) return;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p = func_0011fb38(66, 68, buf + 4);
    p[0] = 0x2026400000008003;
    p[1] = 65;
    p += 2;
    p0 = p;
    f = (f32)((s32)o->x94 % 32) / 32.0f;
    if (func_001f4378(o)) {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 192;
    } else {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 96;
    }
    x = o->xb0 + o->xbe + o->xc2 / 2;
    al = o->x90;
    if (o->u48.w.lo & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        if (o->ud0.s.xd0 >> 4) {
            s32 y = o->xb4 + o->xc0 + (s32)(sinf(f * 3.1415928f) * -384.0f);
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x, cx, sx);
            ((XY *)p)->y = inl_sc2(y - 400, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x - 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y + 80, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x + 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y + 80, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
        if ((o->ud0.s.xd0 >> 4) + o->xce < o->xcc) {
            p = p0;
            y2 = o->xb4 + ((s32)(sinf(f * 3.1415928f) * 384.0f) + (((o->xce * 18 + 10) << 4) + o->xc0));
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x - 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 - 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x + 240, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 - 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = inl_sc2(x, cx, sx);
            ((XY *)p)->y = inl_sc2(y2 + 240, cy, sy);
            ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
    } else {
        if (o->ud0.s.xd0 >> 4) {
            y = o->xb4 + o->xc0 + (s32)(sinf(f * 3.1415928f) * -384.0f);
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x; ((XY *)p)->y = y - 400; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            y += 80;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x - 240; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x + 240; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
        if ((o->ud0.s.xd0 >> 4) + o->xce < o->xcc) {
            p = p0;
            d = sinf(f * 3.1415928f) * 384.0f;
            y2 = (o->xb4 + d) + (((o->xce * 18 + 10) << 4) + o->xc0);
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x - 240; ((XY *)p)->y = y2 - 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x + 240; ((XY *)p)->y = y2 - 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = al; p += 2;
            ((XY *)p)->x = x; ((XY *)p)->y = y2 + 240; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
            buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
            PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
            sceGsSyncPath(0, 0);
        }
    }
    func_001220b8(buf);
}


void func_00204948(TextWin *w, s32 a1, s32 a2, s32 a3) {
    s32 col[3][4];
    u64 *buf, *p;
    u32 ub;
    s32 x, y, cx, cy, l, r, t, b;
    f32 f, sx, sy, fcx, fcy;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p = func_0011fb38(66, 68, buf + 4);
    p[0] = 0x2026400000008003;
    p[1] = 65;
    p += 2;
    if (func_001f4378(w)) {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 192;
    } else {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 96;
    }
    f = (f32)((s32)w->x94 % 20) / 20.0f;
    x = w->xb0 + a2 * 16;
    y = w->xb4 + a3 * 16;
    if (a1) {
        x -= (s32)(sinf(f * 3.1415928f) * 160.0f);
    }
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(x - 160, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y - 160, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(x + 160, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = inl_sc(x - 160, cx, fcx, sx);
        ((V4 *)p)->y = inl_sc(y + 160, cy, fcy, sy);
        ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
    } else {
        l = x - 160; t = y - 160; r = x + 160; b = y + 160;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = l; ((V4 *)p)->y = t; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][0]; ((V4 *)p)->y = col[1][0]; ((V4 *)p)->z = col[2][0]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = r; ((V4 *)p)->y = y; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
        ((V4 *)p)->x = col[0][1]; ((V4 *)p)->y = col[1][1]; ((V4 *)p)->z = col[2][1]; ((V4 *)p)->w = w->x90; p += 2;
        ((V4 *)p)->x = l; ((V4 *)p)->y = b; ((V4 *)p)->z = 0x100000; ((V4 *)p)->w = 0; p += 2;
    }
    buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00204d80(TextWin *w, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 xs[2];
    s32 col[3][4];
    u64 *buf, *p;
    u32 ub;
    s32 y, cx, cy, d;
    f32 f, sx, sy, fcx, fcy;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008001;
    p[1] = 14;
    p = func_0011fb38(66, 68, buf + 4);
    p[0] = 0x2026400000008006;
    p[1] = 65;
    p += 2;
    if (func_001f4378(w)) {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 192;
    } else {
        col[0][1] = 64;
        col[0][0] = 192;
        col[1][0] = 192;
        col[2][0] = 192;
        col[1][1] = 192;
        col[2][1] = 96;
    }
    f = (f32)((s32)w->x94 % 16) / 16.0f;
    d = sinf(f * 3.1415928f) * 96.0f;
    xs[0] = w->xb0 + a2 * 16;
    xs[1] = w->xb0 + a3 * 16;
    y = w->xb4 + a4 * 16;
    if (a1) {
        xs[0] -= d;
        xs[1] += d;
    }
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[0] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y - 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] + 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = inl_sc(xs[1] - 96, cx, fcx, sx);
        ((XY *)p)->y = inl_sc(y + 96, cy, fcy, sy);
        ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
    } else {
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] + 96; ((XY *)p)->y = y - 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] - 96; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[0] + 96; ((XY *)p)->y = y + 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] - 96; ((XY *)p)->y = y - 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][0]; ((XY *)p)->y = col[1][0]; ((XY *)p)->z = col[2][0]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] + 96; ((XY *)p)->y = y; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0x8000; p += 2;
        ((XY *)p)->x = col[0][1]; ((XY *)p)->y = col[1][1]; ((XY *)p)->z = col[2][1]; ((XY *)p)->f = w->x90; p += 2;
        ((XY *)p)->x = xs[1] - 96; ((XY *)p)->y = y + 96; ((XY *)p)->z = 0x100000; ((XY *)p)->f = 0; p += 2;
    }
    buf[0] = ((((s32)p - (s32)buf) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_002053e8(TextWin *o, s32 px, s32 py, s32 pw, s32 ph, s32 col) {
    Q3 *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    buf = (Q3 *)func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0 + px * 16;
    p->y0 = y = o->xb4 + py * 16;
    p->z0 = 0x100000;
    p->x1 = x + pw * 16;
    p->w0 = 0;
    p->w1 = 0;
    p->z1 = 0x100000;
    p->y1 = y + ph * 16;
    if (o->u48.w.lo & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = 0x70000005;
    PlatDmaSend(PlatDmaGetChan(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00205618(TextWin *w, s32 a1, s32 a2, s32 a3, s32 a4, s32 *col) {
    u64 *buf;
    Pk4 *p;
    u32 ub;
    s32 al, cx, cy, x0, y0, x1, y1, nx0, ny0, nx1, ny1;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = (Pk4 *)(buf + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    al = w->x90;
    p->h[0] = 0x9026400000008001;
    p->h[1] = 0x4e4e4e4ee;
    p->h[2] = 68;
    p->h[3] = 66;
    p->e[0].rgba = func_001edd88(col[0], al);
    p->e[0].q = 1;
    p->e[0].v.x = w->xb0 + a1 * 16;
    p->e[0].v.y = w->xb4 + a2 * 16;
    p->e[0].v.z = 0x100000;
    p->e[0].v.w = 0;
    p->e[1].rgba = func_001edd88(col[1], al);
    p->e[1].q = 1;
    p->e[1].v.x = p->e[0].v.x + a3 * 16;
    p->e[1].v.y = p->e[0].v.y;
    p->e[1].v.z = 0x100000;
    p->e[1].v.w = 0;
    p->e[2].rgba = func_001edd88(col[2], al);
    p->e[2].q = 1;
    p->e[2].v.x = p->e[0].v.x;
    p->e[2].v.y = p->e[0].v.y + a4 * 16;
    p->e[2].v.z = 0x100000;
    p->e[2].v.w = 0;
    p->e[3].rgba = func_001edd88(col[3], al);
    p->e[3].q = 1;
    p->e[3].v.x = p->e[1].v.x;
    p->e[3].v.y = p->e[2].v.y;
    p->e[3].v.z = 0x100000;
    p->e[3].v.w = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (p->e[0].v.x - cx) * sx;
        t1 = fcy + (p->e[0].v.y - cy) * sy;
        t2 = fcx + (p->e[1].v.x - cx) * sx;
        t3 = fcy + (p->e[2].v.y - cy) * sy;
        p->e[0].v.x = t0;
        p->e[0].v.y = t1;
        p->e[1].v.x = t2;
        p->e[1].v.y = t1;
        p->e[2].v.x = t0;
        p->e[2].v.y = t3;
        p->e[3].v.x = t2;
        p->e[3].v.y = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 160) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00205938(TextWin *o, s32 col) {
    Q3 *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1A70);
    buf = (Q3 *)func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0;
    p->y0 = y = o->xb4;
    p->z0 = 0x100000;
    p->w0 = 0;
    p->x1 = x + o->xb8;
    p->y1 = y + o->xba;
    p->z1 = 0x100000;
    p->w1 = 0;
    if (o->u48.w.lo & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = 0x70000005;
    PlatDmaSend(PlatDmaGetChan(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00205b30(TextWin *w, s32 *r) {
    u64 *buf;
    Pk4 *p;
    u32 ub;
    s32 al, cx, cy, x0, y0, x1, y1, nx0, ny0, nx1, ny1;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = (Pk4 *)(buf + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    al = w->x90;
    p->h[0] = 0x9026400000008001;
    p->h[1] = 0x4e4e4e4ee;
    p->h[2] = 68;
    p->h[3] = 66;
    p->e[0].rgba = func_001edd88(r[4], al);
    p->e[0].q = 1;
    p->e[0].v.x = w->xb0 + r[0] * 16;
    p->e[0].v.y = w->xb4 + r[1] * 16;
    p->e[0].v.z = 0x100000;
    p->e[0].v.w = 0;
    p->e[1].rgba = func_001edd88(r[5], al);
    p->e[1].q = 1;
    p->e[1].v.x = p->e[0].v.x + r[2] * 16;
    p->e[1].v.y = p->e[0].v.y;
    p->e[1].v.z = 0x100000;
    p->e[1].v.w = 0;
    p->e[2].rgba = func_001edd88(r[6], al);
    p->e[2].q = 1;
    p->e[2].v.x = p->e[0].v.x;
    p->e[2].v.y = p->e[0].v.y + r[3] * 16;
    p->e[2].v.z = 0x100000;
    p->e[2].v.w = 0;
    p->e[3].rgba = func_001edd88(r[7], al);
    p->e[3].q = 1;
    p->e[3].v.x = p->e[1].v.x;
    p->e[3].v.y = p->e[2].v.y;
    p->e[3].v.z = 0x100000;
    p->e[3].v.w = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (p->e[0].v.x - cx) * sx;
        t1 = fcy + (p->e[0].v.y - cy) * sy;
        t2 = fcx + (p->e[1].v.x - cx) * sx;
        t3 = fcy + (p->e[2].v.y - cy) * sy;
        p->e[0].v.x = t0;
        p->e[0].v.y = t1;
        p->e[1].v.x = t2;
        p->e[1].v.y = t1;
        p->e[2].v.x = t0;
        p->e[2].v.y = t3;
        p->e[3].v.x = t2;
        p->e[3].v.y = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 160) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00205e30(TextWin *w, s32 *col) {
    u64 *buf;
    Pk4 *p;
    u32 ub;
    s32 al, cx, cy, x0, y0, x1, y1, nx0, ny0, nx1, ny1;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1A70));
    buf = func_00122048(1024, 128);
    p = (Pk4 *)(buf + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    al = w->x90;
    p->h[0] = 0x9026400000008001;
    p->h[1] = 0x4e4e4e4ee;
    p->h[2] = 68;
    p->h[3] = 66;
    p->e[0].rgba = func_001edd88(col[0], al);
    p->e[0].q = 1;
    p->e[0].v.x = w->xb0;
    p->e[0].v.y = w->xb4;
    p->e[0].v.z = 0x100000;
    p->e[0].v.w = 0;
    p->e[1].rgba = func_001edd88(col[1], al);
    p->e[1].q = 1;
    p->e[1].v.x = p->e[0].v.x + w->xb8;
    p->e[1].v.y = p->e[0].v.y;
    p->e[1].v.z = 0x100000;
    p->e[1].v.w = 0;
    p->e[2].rgba = func_001edd88(col[2], al);
    p->e[2].q = 1;
    p->e[2].v.x = p->e[0].v.x;
    p->e[2].v.y = p->e[0].v.y + w->xba;
    p->e[2].v.z = 0x100000;
    p->e[2].v.w = 0;
    p->e[3].rgba = func_001edd88(col[3], al);
    p->e[3].q = 1;
    p->e[3].v.x = p->e[1].v.x;
    p->e[3].v.y = p->e[2].v.y;
    p->e[3].v.z = 0x100000;
    p->e[3].v.w = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (p->e[0].v.x - cx) * sx;
        t1 = fcy + (p->e[0].v.y - cy) * sy;
        t2 = fcx + (p->e[1].v.x - cx) * sx;
        t3 = fcy + (p->e[2].v.y - cy) * sy;
        p->e[0].v.x = t0;
        p->e[0].v.y = t1;
        p->e[1].v.x = t2;
        p->e[1].v.y = t1;
        p->e[2].v.x = t0;
        p->e[2].v.y = t3;
        p->e[3].v.x = t2;
        p->e[3].v.y = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 160) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00206130(TextWin *o, s32 px, s32 py, s32 pw, s32 ph, s32 col) {
    Q3 *buf;
    Pk *p;
    void *ub;
    s32 a, b, x, y;
    f32 fa, fb, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), &D_003F1E70);
    buf = (Q3 *)func_00122048(1024, 128);
    p = (Pk *)(buf + 1);
    ub = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    p->tag = 0x4023400000008001;
    p->ad = 0x44ee;
    p->d2 = 68;
    p->d3 = 66;
    p->d4 = func_001edd88(col, o->x90);
    p->d5 = 1;
    p->x0 = x = o->xb0 + px * 16;
    p->y0 = y = o->xb4 + py * 16;
    p->z0 = 0x100000;
    p->x1 = x + pw * 16;
    p->w0 = 0;
    p->w1 = 0;
    p->z1 = 0x100000;
    p->y1 = y + ph * 16;
    if (o->u48.w.lo & 1) {
        a = func_001f4570(o);
        b = func_001f45e0(o);
        sx = o->x74;
        sy = o->x78;
        fa = a;
        fb = b;
        t0 = fa + (p->x0 - a) * sx;
        t1 = fb + (p->y0 - b) * sy;
        t2 = fa + (p->x1 - a) * sx;
        p->x0 = t0;
        p->y0 = t1;
        t3 = fb + (p->y1 - b) * sy;
        p->y1 = t3;
        p->x1 = t2;
    }
    buf->a = ((Q3 *)(p + 1) - buf - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00206370(TextWin *w, s32 px, s32 py, s32 pw, s32 ph, s32 k0, s32 k1, s32 k2, s32 k3) {
    u64 *buf;
    Pk4 *p;
    u32 ub;
    s32 al, cx, cy, x, y, x1, y1;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = (Pk4 *)(buf + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p->h[0] = 0x9026400000008001;
    p->h[1] = 0x4e4e4e4ee;
    p->h[2] = 68;
    p->h[3] = 66;
    al = w->x90;
    k0 = func_001edd88(k0, al);
    k1 = func_001edd88(k1, al);
    k2 = func_001edd88(k2, al);
    k3 = func_001edd88(k3, al);
    p->e[0].rgba = (u32)k0;
    p->e[0].q = 1;
    p->e[0].v.x = x = w->xb0 + px * 16;
    p->e[0].v.y = y = w->xb4 + py * 16;
    p->e[0].v.z = 0x100000;
    p->e[0].v.w = 0;
    p->e[1].rgba = (u32)k1;
    p->e[1].q = 1;
    p->e[1].v.x = x1 = x + pw * 16;
    p->e[1].v.y = y;
    p->e[1].v.z = 0x100000;
    p->e[1].v.w = 0;
    p->e[2].rgba = (u32)k2;
    p->e[2].q = 1;
    p->e[2].v.x = x;
    p->e[2].v.y = y1 = y + ph * 16;
    p->e[2].v.z = 0x100000;
    p->e[2].v.w = 0;
    p->e[3].rgba = (u32)k3;
    p->e[3].q = 1;
    p->e[3].v.x = x1;
    p->e[3].v.y = y1;
    p->e[3].v.z = 0x100000;
    p->e[3].v.w = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (p->e[0].v.x - cx) * sx;
        t1 = fcy + (p->e[0].v.y - cy) * sy;
        t2 = fcx + (p->e[1].v.x - cx) * sx;
        t3 = fcy + (p->e[2].v.y - cy) * sy;
        p->e[0].v.x = t0;
        p->e[0].v.y = t1;
        p->e[1].v.x = t2;
        p->e[1].v.y = t1;
        p->e[2].v.x = t0;
        p->e[2].v.y = t3;
        p->e[3].v.x = t2;
        p->e[3].v.y = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 160) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00206748(TextWin *w, s32 f1, s32 f2, s32 px, s32 py, s32 pw, s32 ph) {
    u32 c[2];
    u64 *buf;
    Pk6 *p;
    u32 ub, k;
    s32 cx, cy, x0, y0, x1, y1;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3, t4, t5, t6, t7;
    PlatDmaSend(PlatDmaGetChan(2), (*(u8 (*)[0x400])&D_003F1E70));
    buf = func_00122048(1024, 128);
    p = (Pk6 *)(buf + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p->h[0] = 0xf022400000008001;
    p->h[1] = 0x044e44e44e44e44e;
    k = (w->x90 << 24) | 0x202020;
    if (f1 == 0) {
        c[0] = 72;
        c[1] = 66;
    } else {
        c[0] = 66;
        c[1] = 72;
    }
    if (f2) {
        px -= 2;
        py -= 2;
        pw += 4;
        ph += 4;
    }
    p->s[0].a = k;
    p->s[0].b = 1;
    p->s[0].v[0].x = x0 = w->xb0 + px * 16;
    p->s[0].v[0].y = y0 = w->xb4 + py * 16;
    p->s[0].v[0].z = 0x100000;
    p->s[0].v[0].w = 0;
    p->s[0].v[1].x = x0 + 32;
    p->s[0].v[1].y = y0 + 32;
    p->s[0].v[1].z = 0x100000;
    p->s[0].v[1].w = 0;
    x1 = x0 + pw * 16;
    y1 = y0 + ph * 16;
    p->s[1].a = c[0];
    p->s[1].b = 66;
    p->s[1].v[0].x = x1;
    p->s[1].v[0].y = y0;
    p->s[1].v[0].z = 0x100000;
    p->s[1].v[0].w = 0;
    p->s[1].v[1].x = x1 - 32;
    p->s[1].v[1].y = y0 + 32;
    p->s[1].v[1].z = 0x100000;
    p->s[1].v[1].w = 0;
    p->s[2].a = c[1];
    p->s[2].b = 66;
    p->s[2].v[0].x = x1;
    p->s[2].v[0].y = y1;
    p->s[2].v[0].z = 0x100000;
    p->s[2].v[0].w = 0;
    p->s[2].v[1].x = x1 - 32;
    p->s[2].v[1].y = y1 - 32;
    p->s[2].v[1].z = 0x100000;
    p->s[2].v[1].w = 0;
    p->s[3].a = c[1];
    p->s[3].b = 66;
    p->s[3].v[0].x = x0;
    p->s[3].v[0].y = y1;
    p->s[3].v[0].z = 0x100000;
    p->s[3].v[0].w = 0;
    p->s[3].v[1].x = x0 + 32;
    p->s[3].v[1].y = y1 - 32;
    p->s[3].v[1].z = 0x100000;
    p->s[3].v[1].w = 0;
    p->s[4].a = c[0];
    p->s[4].b = 66;
    p->s[4].v[0].x = x0;
    p->s[4].v[0].y = y0;
    p->s[4].v[0].z = 0x100000;
    p->s[4].v[0].w = 0;
    p->s[4].v[1].x = x0 + 32;
    p->s[4].v[1].y = y0 + 32;
    p->s[4].v[1].z = 0x100000;
    p->s[4].v[1].w = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (p->s[0].v[0].x - cx) * sx;
        t1 = fcy + (p->s[0].v[0].y - cy) * sy;
        t2 = fcx + (p->s[0].v[1].x - cx) * sx;
        t3 = fcy + (p->s[0].v[1].y - cy) * sy;
        t4 = fcx + (p->s[1].v[0].x - cx) * sx;
        t5 = fcx + (p->s[1].v[1].x - cx) * sx;
        t6 = fcy + (p->s[2].v[0].y - cy) * sy;
        t7 = fcy + (p->s[2].v[1].y - cy) * sy;
        p->s[0].v[0].x = t0;
        p->s[0].v[0].y = t1;
        p->s[0].v[1].x = t2;
        p->s[0].v[1].y = t3;
        p->s[1].v[0].x = t4;
        p->s[1].v[0].y = t1;
        p->s[1].v[1].x = t5;
        p->s[1].v[1].y = t3;
        p->s[2].v[0].x = t4;
        p->s[2].v[0].y = t6;
        p->s[2].v[1].x = t5;
        p->s[2].v[1].y = t7;
        p->s[3].v[0].x = t0;
        p->s[3].v[0].y = t6;
        p->s[3].v[1].x = t2;
        p->s[3].v[1].y = t7;
        p->s[4].v[0].x = t0;
        p->s[4].v[0].y = t1;
        p->s[4].v[1].x = t2;
        p->s[4].v[1].y = t3;
    }
    buf[0] = ((((s32)p - (s32)buf + 256) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


void func_00206b70(TextWin *w, Spr *r) {
    u64 *buf, *p;
    s32 *q;
    u32 ub;
    s32 u, v, x, y, cx, cy;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x1000000000008006;
    p[1] = 14;
    p[2] = 0x4000d;
    p[3] = 71;
    p[4] = 0;
    p[5] = 63;
    p[6] = r->tex;
    p[7] = 6;
    p[8] = 97;
    p[9] = 20;
    p[10] = 68;
    p[11] = 66;
    p[12] = func_001edd88(r->col, w->x90);
    p[13] = 1;
    p[14] = 0x20ab400000008002;
    p[15] = 67;
    q = (s32 *)p;
    q[32] = u = r->u * 16 + 8;
    q[33] = v = r->v * 16 + 8;
    q[36] = x = w->xb0 + r->x * 16;
    q[37] = y = w->xb4 + r->y * 16;
    q[38] = 0x100000;
    q[39] = 0x8000;
    q[40] = u + ((r->w - 1) << 4);
    q[41] = v + ((r->h - 1) << 4);
    q[44] = x + r->dw * 16;
    q[45] = y + r->dh * 16;
    q[46] = 0x100000;
    q[47] = 0;
    if (w->u48.w.lo & 1) {
        cx = func_001f4570(w);
        cy = func_001f45e0(w);
        sx = w->x74;
        sy = w->x78;
        fcx = cx;
        fcy = cy;
        t0 = fcx + (q[36] - cx) * sx;
        t1 = fcy + (q[37] - cy) * sy;
        t2 = fcx + (q[44] - cx) * sx;
        q[36] = t0;
        q[37] = t1;
        t3 = fcy + (q[45] - cy) * sy;
        q[45] = t3;
        q[44] = t2;
    }
    buf[0] = ((((s32)p - (s32)buf + 192) >> 4) - 1) | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}


#include "data/pieces/D_003F2BD8.h"
