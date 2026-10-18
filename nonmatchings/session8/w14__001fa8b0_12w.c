/* 001fa8b0: 12w by LCS (17 pos), hand/nostrict_nogcse, s6 draft unchanged. New finding (w14): the diff is the glyph-block head. Ours: loop pass 2 hoists %hi(D_003E8E28) (pseudo 175, life 3 = high, deleted lo_sum note, k<<3, load; 114 real insns; loop.c threshold here is 63-64, so life>=2 moves at <=126 insns) and sched1 dual-issues the E8E28 lw with c-32 at cycle 0 (prio 48, memory unit), so local-alloc puts the c-32 chain in v0 instead of v1. Orig issues that lw after the lhu (k). Tried: c -= 32 (chain gets v1 but schedule worse), u8/s16/s32 c, k types, g = D+k, k*8 first (life 2, still moved), dead debug counters (deleted before loop), literal 18/0x100000 in the loop, volatile tables, goto loop, -fno-rerun-loop-opt (E8E28 not hoisted but lui+lw still issued at cycle 0/1: hoisting alone is not the cause). Open: something that makes the E8E28 load depend on, or rank below, the D_003E8D40 lhu. */
#include "common.h"

typedef struct { u16 code; u16 f2; u16 f4; u8 w; u8 f7; } Glyph;
typedef struct { u64 a, b; } Q;
typedef struct { u64 d0; u64 d1; s32 w[16]; } GP;
typedef struct {
    u8 pad0[0x48];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 x74;
    f32 x78;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0;
    s32 xb4;
} Txt9;

extern Glyph *D_003E8E28;
extern s32 D_003E8D00[];
extern s32 D_003E8E00;
extern s32 D_003F1A64;
extern u16 D_003E8D40[];
extern Q D_003F2270[];
extern s32 D_003F2BD0;
extern s32 D_003F2BD4;

u64 *func_00122048(s32, s32);
void func_001220b8(void *);
u32 func_001edd88(u32, s32);
s32 func_001eff50(s32);
s32 func_001f0340(u8 *, s32);
s32 func_001f4570(Txt9 *);
s32 func_001f45e0(Txt9 *);
s32 func_00266c08(s32);
void func_00266f38(s32, void *);
s32 sceGsSyncPath(s32, s32);

void func_001fa8b0(Txt9 *o, s32 x, s32 y, u8 *s, s32 sz, s32 col) {
    u64 *base;
    u32 tag;
    s32 sz16;
    s32 ox;
    s32 org;
    s32 fl;
    s32 x16;
    s32 ax, ay;
    u64 *q;
    s32 xx, yy;
    f32 fx, fy;
    u32 c;
    s32 n, z, k;
    Glyph *g;
    s32 w, wp, f2, f4;
    u8 f7;
    s32 x40, y44, ww, a;
    u64 tex;
    f32 fa, fb, t0, t1, t2, t3;



    func_00266f38(func_00266c08(2), D_003F2270);
    x16 = x * 16;
    sz16 = sz * 16;
    base = func_00122048(1024, 128);
    q = base + 2;
    tag = ((u32)base & 0x0fffffff) | 0x80000000;
    q[0] = 0x4000000000000001;
    q[1] = 0xeeee;
    q[3] = 63;
    q[4] = 0x4007ff8001300000;
    q[2] = 0;
    q[5] = 22;
    q[6] = 68;
    q[7] = 66;
    q[8] = func_001edd88(col, o->x90);
    q[9] = 1;
    q[10] = 0x50ab400000008001;
    q[11] = 0x4343e;
    base[0] = 0x7000000b;
    q = base + 14;
    ox = o->xb0;
    fl = o->x48 & 1;
    org = o->xb4;
    xx = ox + x16;
    yy = org + y * 16;
    if (fl) {
        ax = func_001f4570(o);
        ay = func_001f45e0(o);
        fx = o->x74;
        fy = o->x78;
    }
    n = 18;
    z = 0x100000;
    for (;;) {
        c = *s;
        if (c == 0) goto done;
        if (c == '\n') {
            s++;
            yy += D_003F1A64;
            xx = ox + x16;
            continue;
        }
        s++;
        if (c < 31) continue;
        if (c == ' ') {
            xx += (sz << 8) / n;
            continue;
        }
        if (c >= 128) continue;
/*P*/
        k = D_003E8D40[c - 32];
        g = &D_003E8E28[k];
        f2 = g->f2;
        w = g->w << 4;
        ww = w + D_003E8E00;
        wp = ww * sz / n;
        f4 = g->f4;
        a = w * sz / n;
        f7 = g->f7;
        tex = ((u64)D_003E8D00[f7 >> 4] << 20) | ((u64)(f7 & 0xf) << 56) | (0xfff0ULL << 35);
        ((GP *)q)->w[0] = f2;
        ((GP *)q)->d0 = tex;
        y44 = yy + sz16;
        ((GP *)q)->d1 = 22;
        ((GP *)q)->w[7] = 0x8000;
        ((GP *)q)->w[8] = f2 + w;
        ((GP *)q)->w[5] = yy;
        ((GP *)q)->w[4] = xx;
        ((GP *)q)->w[1] = f4;
        x40 = xx + a;
        ((GP *)q)->w[12] = x40;
        ((GP *)q)->w[6] = z;
        ((GP *)q)->w[14] = z;
        ((GP *)q)->w[9] = f4 + 288;
        ((GP *)q)->w[15] = 0;
        ((GP *)q)->w[13] = y44;
/*Q*/
        if (fl) {
            fa = ax;
            fb = ay;
            t0 = fa + (xx - ax) * fx;
            t1 = fb + (yy - ay) * fy;
            t2 = fa + (x40 - ax) * fx;
            t3 = fb + (y44 - ay) * fy;
            ((GP *)q)->w[4] = t0;
            ((GP *)q)->w[5] = t1;
            ((GP *)q)->w[12] = t2;
            ((GP *)q)->w[13] = t3;
        }
        xx += wp;
        func_00266f38(func_00266c08(2), (void *)tag);
        sceGsSyncPath(0, 0);
    }
done:
    func_001220b8(base);
    D_003F2BD0 = (xx - ox) >> 4;
    D_003F2BD4 = (yy - org) >> 4;
}
