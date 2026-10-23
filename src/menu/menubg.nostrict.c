/* The gradients and sprites of src/menu/menubg.c that need -fno-strict-aliasing
 * (docs/modules.md "Session 39"). */
#include "common.h"
#include "text/textwin.h"

typedef struct { u64 rgba; u64 st; s32 x, y, z, w; } V;
typedef struct { u64 tag[2]; u64 a; u64 b; V v[4]; } G;
typedef struct { s32 u, v, u1, v1; u64 rgba, q; s32 x, y, z, w; } SprE;
typedef struct { u64 h[14]; SprE e[8]; } PkS;
typedef struct { u64 h[16]; SprE e[8]; } PkT;

extern s32 D_002BCC94;
extern s32 D_003F31F0[];
extern u8 D_00641080[];
extern u8 D_00641130[];

s32 FlushCache(s32);
s32 sceGsExecStoreImage(void *, void *);
s32 sceGsSyncPath(s32, s32);
void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
u32 func_001edf40(u32, u32);
s32 func_001f4570(TextWin *);
s32 func_001f45e0(TextWin *);
s32 func_002660c0(void *, s32, s32, s32, s32, s32, s32, s32);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);

#include "data/pieces/D_003F34B0.h"
#include "data/pieces/D_003F1A70.h"
#include "data/pieces/D_003F1E70.h"

void func_0020a9b0(s32 a) {
    u64 *p;
    G *g;
    u64 *q;
    void *u;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1A70));
    q = func_00122048(1024, 128);
    p = q++;
    q++;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    g = (G *)q;
    g->tag[0] = 0x9026400000008001;
    g->tag[1] = 0x4e4e4e4ee;
    g->a = 0x44;
    g->b = 0x42;
    g->v[1].rgba = g->v[0].rgba = func_001edd88(D_003F34B0[0] | (a << 24), 64);
    g->v[0].st = 1;
    g->v[0].x = 0x7000;
    g->v[0].y = 0x7400;
    g->v[0].z = 0x100000;
    g->v[0].w = 0;
    g->v[1].st = 1;
    g->v[1].x = 0x9000;
    g->v[1].y = 0x7400;
    g->v[1].z = 0x100000;
    g->v[1].w = 0;
    g->v[3].rgba = g->v[2].rgba = func_001edd88(D_003F34B0[1] | (a << 24), 64);
    g->v[2].st = 1;
    g->v[2].x = 0x7000;
    g->v[2].y = 0x8c00;
    g->v[2].z = 0x100000;
    g->v[2].w = 0;
    g->v[3].st = 1;
    g->v[3].x = 0x9000;
    g->v[3].y = 0x8c00;
    g->v[3].z = 0x100000;
    g->v[3].w = 0;
    q += 20;
    p[0] = (((s32)q - (s32)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}

void func_0020ab88(u32 a) {
    u32 c[3];
    u64 *buf;
    PkS *p;
    u32 ub, al;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1E70));
    p = (PkS *)func_00122048(1024, 128);
    buf = (u64 *)p;
    p = (PkS *)((u64 *)p + 2);
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    a = a * 36 >> 7;
    if (a > 128) a = 128;
    p->h[0] = 0x5000400000008001;
    p->h[1] = 0xeeeee;
    p->h[2] = 0;
    p->h[3] = 63;
    p->h[4] = 0x0007bf8621413d7c;
    p->h[5] = 6;
    p->h[6] = 0x4007bf8001300000;
    p->h[7] = 22;
    p->h[8] = 0x0007bf8001400000;
    p->h[9] = 22;
    p->h[10] = 72;
    p->h[11] = 66;
    p->h[12] = 0x30ae400000008008;
    p->h[13] = 1251;
    c[0] = D_003F34B0[0] | (a << 24);
    c[2] = D_003F34B0[1] | (a << 24);
    c[1] = func_001edf40(c[0], c[2]);
    p->e[0].u = 3992; p->e[0].v = 1000; p->e[0].rgba = c[0]; p->e[0].q = 1;
    p->e[0].x = 0x7000; p->e[0].y = 0x7400; p->e[0].z = 0x100000; p->e[0].w = 0;
    p->e[1].u = 4072; p->e[1].v = 1000; p->e[1].rgba = c[0]; p->e[1].q = 1;
    p->e[1].x = 0x9000; p->e[1].y = 0x7400; p->e[1].z = 0x100000; p->e[1].w = 0;
    p->e[2].u = 3992; p->e[2].v = 4072; p->e[2].rgba = c[1]; p->e[2].q = 1;
    p->e[2].x = 0x7000; p->e[2].y = 0x8000; p->e[2].z = 0x100000; p->e[2].w = 0;
    p->e[3].u = 4072; p->e[3].v = 4072; p->e[3].rgba = c[1]; p->e[3].q = 1;
    p->e[3].x = 0x9000; p->e[3].y = 0x8000; p->e[3].z = 0x100000; p->e[3].w = 0;
    p->e[4].u = 3992; p->e[4].v = 1000; p->e[4].rgba = c[1]; p->e[4].q = 1;
    p->e[4].x = 0x7000; p->e[4].y = 0x8000; p->e[4].z = 0x100000; p->e[4].w = 0;
    p->e[5].u = 4072; p->e[5].v = 1000; p->e[5].rgba = c[1]; p->e[5].q = 1;
    p->e[5].x = 0x9000; p->e[5].y = 0x8000; p->e[5].z = 0x100000; p->e[5].w = 0;
    p->e[6].u = 3992; p->e[6].v = 4072; p->e[6].rgba = c[2]; p->e[6].q = 1;
    p->e[6].x = 0x7000; p->e[6].y = 0x8c00; p->e[6].z = 0x100000; p->e[6].w = 0;
    p->e[7].u = 4072; p->e[7].v = 4072; p->e[7].rgba = c[2]; p->e[7].q = 1;
    p->e[7].x = 0x9000; p->e[7].y = 0x8c00; p->e[7].z = 0x100000; p->e[7].w = 0;
    buf[0] = ((((s32)p - (s32)buf + 496) >> 4) - 1) | 0x70000000;
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}

u64 *func_0020ae98(PkT *p, s32 tex, u32 a) {
    u32 c[3];
    u32 al, c1;
    p->h[0] = 0x6000400000008001;
    p->h[1] = 14;
    p->h[2] = 0x4000d;
    p->h[3] = 71;
    p->h[4] = 0;
    p->h[5] = 63;
    p->h[6] = 0x0007bf8621413d7c;
    p->h[7] = 6;
    p->h[8] = 0x4007bf8001300000;
    p->h[9] = 22;
    p->h[10] = 0x0007bf8001400000;
    p->h[11] = 22;
    p->h[12] = 72;
    p->h[13] = 66;
    p->h[14] = ((u64)tex << 15) | 0x30ae400000000008;
    p->h[15] = 1251;
    al = a * 36 >> 7;
    if (al > 128) al = 128;
    c[0] = D_003F34B0[0] | (al << 24);
    c[2] = D_003F34B0[1] | (al << 24);
    c1 = func_001edf40(c[0], c[2]);
    p->e[0].u = 3992; p->e[0].v = 1000; p->e[0].rgba = c[0]; p->e[0].q = 1;
    p->e[0].x = 0x7000; p->e[0].y = 0x7400; p->e[0].z = 0x100000; p->e[0].w = 0;
    p->e[1].u = 4072; p->e[1].v = 1000; p->e[1].rgba = c[0]; p->e[1].q = 1;
    p->e[1].x = 0x9000; p->e[1].y = 0x7400; p->e[1].z = 0x100000; p->e[1].w = 0;
    p->e[2].u = 3992; p->e[2].v = 4072; p->e[2].rgba = c1; p->e[2].q = 1;
    p->e[2].x = 0x7000; p->e[2].y = 0x8000; p->e[2].z = 0x100000; p->e[2].w = 0;
    p->e[3].u = 4072; p->e[3].v = 4072; p->e[3].rgba = c1; p->e[3].q = 1;
    p->e[3].x = 0x9000; p->e[3].y = 0x8000; p->e[3].z = 0x100000; p->e[3].w = 0;
    p->e[4].u = 3992; p->e[4].v = 1000; p->e[4].rgba = c1; p->e[4].q = 1;
    p->e[4].x = 0x7000; p->e[4].y = 0x8000; p->e[4].z = 0x100000; p->e[4].w = 0;
    p->e[5].u = 4072; p->e[5].v = 1000; p->e[5].rgba = c1; p->e[5].q = 1;
    p->e[5].x = 0x9000; p->e[5].y = 0x8000; p->e[5].z = 0x100000; p->e[5].w = 0;
    p->e[6].u = 3992; p->e[6].v = 4072; p->e[6].rgba = c[2]; p->e[6].q = 1;
    p->e[6].x = 0x7000; p->e[6].y = 0x8c00; p->e[6].z = 0x100000; p->e[6].w = 0;
    p->e[7].u = 4072; p->e[7].v = 4072; p->e[7].rgba = c[2]; p->e[7].q = 1;
    p->e[7].x = 0x9000; p->e[7].y = 0x8c00; p->e[7].z = 0x100000; p->e[7].w = 0;
    return (u64 *)(p + 1);
}

void func_0020b120(s32 prim, s32 al, u32 c0, u32 c1, u32 c2, u32 c3) {
    u64 *p;
    u64 *q;
    G *g;
    void *u;
    func_00266f38(func_00266c08(2), (*(u8 (*)[0x400])&D_003F1A70));
    q = func_00122048(1024, 128);
    p = q++;
    q++;
    u = (void *)(((u32)p & 0x0fffffff) | 0x80000000);
    c0 = func_001edd88(c0, al);
    c1 = func_001edd88(c1, al);
    c2 = func_001edd88(c2, al);
    c3 = func_001edd88(c3, al);
    g = (G *)q;
    g->tag[0] = 0x9026400000008001;
    g->tag[1] = 0x4e4e4e4ee;
    g->a = D_003F31F0[prim];
    g->b = 0x42;
    g->v[0].rgba = c0;
    g->v[0].st = 1;
    g->v[0].x = 0x7000;
    g->v[0].y = 0x7400;
    g->v[0].z = 0x100000;
    g->v[0].w = 0;
    g->v[1].rgba = c1;
    g->v[1].st = 1;
    g->v[1].x = 0x9000;
    g->v[1].y = 0x7400;
    g->v[1].z = 0x100000;
    g->v[1].w = 0;
    g->v[2].rgba = c2;
    g->v[2].st = 1;
    g->v[2].x = 0x7000;
    g->v[2].y = 0x8c00;
    g->v[2].z = 0x100000;
    g->v[2].w = 0;
    g->v[3].rgba = c3;
    g->v[3].st = 1;
    g->v[3].x = 0x9000;
    g->v[3].y = 0x8c00;
    g->v[3].z = 0x100000;
    g->v[3].w = 0;
    q += 20;
    p[0] = (((s32)q - (s32)p) >> 4) - 1 | 0x70000000;
    func_00266f38(func_00266c08(2), u);
    sceGsSyncPath(0, 0);
    func_001220b8(p);
}

void func_0020b3d8(TextWin *w, s32 px, s32 py) {
    u64 *buf, *p;
    s32 *q;
    u32 ub;
    s32 x, y, cx, cy;
    f32 fcx, fcy, sx, sy, t0, t1, t2, t3;
    func_00266f38(func_00266c08(2), D_00641080);
    func_00266f38(func_00266c08(2), D_00641130);
    buf = func_00122048(1024, 128);
    p = buf + 2;
    ub = ((u32)buf & 0x0fffffff) | 0x80000000;
    p[0] = 0x5000000000008001;
    p[1] = 0xeeeee;
    p[2] = 0x4000d;
    p[3] = 71;
    p[4] = 0;
    p[5] = 63;
    p[6] = 0x2006c8059d30b600;
    p[7] = 6;
    p[8] = 97;
    p[9] = 20;
    p[10] = 68;
    p[11] = 66;
    p[12] = 0x50ab400000008001;
    p[13] = 0x4343e;
    p[14] = func_001edd88(0x40808080, w->x90);
    p[15] = 1;
    q = (s32 *)p;
    q[32] = 8;
    q[33] = 8;
    q[36] = x = w->xb0 + px * 16;
    q[37] = y = w->xb4 + py * 16;
    q[38] = 0x100000;
    q[39] = 0x8000;
    q[40] = 1656;
    q[41] = 888;
    q[44] = x + 1664;
    q[45] = y + 896;
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
    func_00266f38(func_00266c08(2), (void *)ub);
    sceGsSyncPath(0, 0);
    func_001220b8(buf);
}
