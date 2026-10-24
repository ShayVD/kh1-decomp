/* Page 5's section 2 (D_003F5A00[2]; src/menu/journal_s2.c, docs/modules.md
 * "Session 42"): the two functions that match only with -fno-strict-aliasing.
 * func_0021e120 draws a 64x64 picture of entry k (D_003F5028[k], two textures
 * uploaded through func_0011fbb0, one GS sprite packet + sceGsSyncPath);
 * func_0021e8d8 is the section's detail window (scroll, confirm asks for the
 * model of entry D_00643274, then a window from D_003F5E30).
 *
 * func_0021e120: MATCHED (session 19, s19m1). From s18m1's 3w pinned basin
 * (nonmatchings/session18/s18m1__0021e120_3w.c: 66 in t0 and 68 in a0 as local
 * register variables). The 63 and 0x2006D0059D30B600 header constants are
 * pinned too, to a2/a3 (`register u64 k5 asm("$6"), k6 asm("$7")`): the
 * a2/a3/t0 argument moves of the 2nd func_0011fbb0 call then share an output
 * dependence on a pinned header set, so they keep source order. `p[0] = k0;`
 * after the k6 set came from an exhaustive two-line position search.
 * FLAGGED: four register variables (plain C, no inline asm). */
#include "common.h"
#include "platform/gs.h"
#include "platform/dma.h"
#include "data/bss_0064.h"

typedef struct {
    u8 pad0[0x24];
    s32 x24, x28, x2c;
    u8 pad30[0x48 - 0x30];
    s32 x48;
    u8 pad4c[0x74 - 0x4c];
    f32 sx, sy;
    u8 pad7c[0x90 - 0x7c];
    s32 x90;
    u8 pad94[0xb0 - 0x94];
    s32 xb0, xb4;
    u8 padb8[0xd8 - 0xb8];
    s16 xd8, xda;
} Wnd;
typedef struct { s32 u, v; u64 pad; u64 rgba, q; s32 x, y, z, f; } Vx;
typedef struct { u8 pad0[0x24]; f32 x24; s32 x28; s32 x2c; s32 x30; } Eff;
typedef struct { u8 pad0[0x10]; s32 x10; } S3110;
#include "data/types/nostrict_text_00210000_s19_s19m1.h"
#include "data/pieces/D_00425BC8.h"
#include "data/pieces/D_003E8E08.h"
#include "vm/script_vm.h"
extern s32 D_0064324C;
extern C16 D_003F5E00[];
extern u8 D_003F5028[];
extern u8 *D_003F3510;
extern u8 D_00643290[];
extern u8 D_00643340[];
extern s32 D_00643250;
extern s32 D_00643274;
extern S3110 *D_00643110; /* src/data/bss_0064.c: s32 D_00643110 */
extern s32 D_00643114;
extern s32 D_00643118;
extern u8 D_003F5E30[];
extern f32 D_003F53C0[];
extern u16 D_003F56A0[];
extern s32 D_003F34F8;
void func_00205618(Wnd *, s32, s32, s32, s32, s32 *);
void func_0011fbb0(s32, s32, s32, s32, s32, s32, s32, s32, void *, void *);
u64 *func_00122048(s32, s32);
void func_001220b8(void *);
s32 func_001f4570(Wnd *);
s32 func_001f45e0(Wnd *);
s32 func_001f42b8(void);
void func_0021e538(void);
void func_0011d768(s32);
void func_0021b5c8(s32, s32, s32, s32, f32);
s32 func_001fd668(Wnd *);
s32 func_0021e898(s32);
void func_0021b4c8(s32);
s32 func_0021b7f0(void);
Eff *func_001f31a8(void *, s32);
void func_001f3e48(Eff *, Wnd *);
void func_001f3758(s32);
void func_0021b820(void);
void func_0021cba8(Wnd *, s32, s32, s32, s32);
void func_0021cb88(Wnd *, s32, s32, s32, s32);
s32 func_0021b170(s32);
void func_00203788(Wnd *, s32, s32, s32, u32);
void func_0021c9a0(Wnd *, s32, s32);
void func_0021cb00(Wnd *, s32, s32, s32, s32);
s32 func_0021dc38(s32);
void func_0010edb0(s32, s32, s32, s32, s32, s32);
s32 func_0021b800(s32);
void func_001f94f0(Wnd *, s32, s32, s32, s32, s32, u32);

void func_0021e120(Wnd *o, s32 x, s32 y, s32 k) {
    u64 *buf;
    u64 *p;
    void *u;
    u8 *q;
    s32 cx, cy, X, Y;
    u32 c;
    f32 fx, fy, sx, sy;
    register u64 k66 asm("$8"); register u64 k68 asm("$4"); register u64 k6 asm("$7"); register u64 k5 asm("$6");
    u64 t1, k0, k2, k3, k7, k8, k9, k10, k11, k12, k13;
    s32 nx, ny, nx2, ny2;
    func_00205618(o, x, y, 64, 64, D_003F5E00[D_0064324C].a);
    q = D_003F3510 + D_003F5028[k] * 0x1400;
    func_0011fbb0(0x3600, 2, 19, 0, 0, 64, 64, 256, q, D_00643290);
    func_0011fbb0(0x3680, 1, 0, 0, 0, 16, 16, 64, q + 0x1000, D_00643340);
    PlatDmaSend(PlatDmaGetChan(2), D_00643290);
    x <<= 4;
    PlatDmaSend(PlatDmaGetChan(2), D_00643340);
    buf = func_00122048(1024, 128);
    p = buf + 2;
    u = (void *)(((u32)buf & 0x0fffffff) | 0x80000000);
    t1 = 0xEEEEE;
    k0 = 0x5000000000008001;
    k5 = 63;
    p[1] = t1;
    p[2] = 0x4000D;
    k3 = 71;
    k6 = 0x2006D0059D30B600;
    p[0] = k0;
    p[5] = k5;
    p[4] = 0;
    p[7] = 6;
    k9 = 20;
    p[6] = k6;
    p[8] = 97;
    p[12] = 0x30AE400000008004;
    p[3] = k3;
    k68 = 68;
    k66 = 66;
    p[11] = k66;
    p[10] = k68;
    y <<= 4;
    p[9] = k9;
    p[13] = 1251;
    p += 14;
    c = (u32)(o->x90 << 24 | 0x808080);
    X = o->xb0 + x;
    Y = o->xb4 + y;
    ((Vx *)p)[0].u = 8;
    ((Vx *)p)[0].v = 8;
    ((Vx *)p)[0].rgba = c;
    ((Vx *)p)[0].q = 1;
    ((Vx *)p)[0].x = X;
    ((Vx *)p)[0].y = Y;
    ((Vx *)p)[0].z = 0x100000;
    ((Vx *)p)[0].f = 0;
    ((Vx *)p)[1].u = 1016;
    ((Vx *)p)[1].v = 8;
    ((Vx *)p)[1].rgba = c;
    ((Vx *)p)[1].q = 1;
    ((Vx *)p)[1].x = X + 1024;
    ((Vx *)p)[1].y = Y;
    ((Vx *)p)[1].z = 0x100000;
    ((Vx *)p)[1].f = 0;
    ((Vx *)p)[2].u = 8;
    ((Vx *)p)[2].v = 1016;
    ((Vx *)p)[2].rgba = c;
    ((Vx *)p)[2].q = 1;
    ((Vx *)p)[2].x = X;
    ((Vx *)p)[2].y = Y + 1024;
    ((Vx *)p)[2].z = 0x100000;
    ((Vx *)p)[2].f = 0;
    ((Vx *)p)[3].u = 1016;
    ((Vx *)p)[3].v = 1016;
    ((Vx *)p)[3].rgba = c;
    ((Vx *)p)[3].q = 1;
    ((Vx *)p)[3].x = X + 1024;
    ((Vx *)p)[3].y = Y + 1024;
    ((Vx *)p)[3].z = 0x100000;
    ((Vx *)p)[3].f = 0;
    if (o->x48 & 1) {
        cx = func_001f4570(o);
        cy = func_001f45e0(o);
        sx = o->sx;
        sy = o->sy;
        fx = cx;
        fy = cy;
        nx = fx + (f32)(((Vx *)p)[0].x - cx) * sx;
        ny = fy + (f32)(((Vx *)p)[0].y - cy) * sy;
        nx2 = fx + (f32)(((Vx *)p)[1].x - cx) * sx;
        ny2 = fy + (f32)(((Vx *)p)[2].y - cy) * sy;
        ((Vx *)p)[0].x = nx;
        ((Vx *)p)[0].y = ny;
        ((Vx *)p)[1].x = nx2;
        ((Vx *)p)[1].y = ny;
        ((Vx *)p)[2].x = nx;
        ((Vx *)p)[2].y = ny2;
        ((Vx *)p)[3].x = nx2;
        ((Vx *)p)[3].y = ny2;
    }
    buf[0] = (((s32)((Vx *)p + 4) - (s32)buf) >> 4) - 1 | 0x70000000;
    PlatDmaSend(PlatDmaGetChan(2), u);
    PlatGsSyncPath(0, 0);
    func_001220b8(buf);
}

void func_0021e8d8(Wnd *o) {
    s32 ch, n, k;
    Eff *p;
    s32 t;
    if (func_001f42b8()) {
        func_0021e538();
        if (o->x28 == 0) {
            if (D_00425BC8->x8 & 0x4000) {
                func_0011d768(3);
                func_0021b5c8(0xC009B, 0, 128, 128, 5.0f);
                o->x28 = 1;
            } else {
                switch (o->x2c) {
                case 0:
                    ch = 0;
                    n = o->xd8;
                    if (D_00425BC8->x10 & 0x80000480) {
                        if (o->xda > 0) {
                            o->xda -= 16;
                            ch = 1;
                        }
                    } else if (D_00425BC8->x10 & 0x20000820) {
                        if (o->xda < (n - 1) << 4) {
                            o->xda += 16;
                            ch = 1;
                        }
                    }
                    if (ch) func_0011d768(ch);
                    D_00643250 = func_001fd668(o);
                    if (D_00425BC8->x8 & 0x1000) {
                        if (func_0021e898(D_00643274)) {
                            func_0011d768(4);
                        } else {
                            func_0011d768(2);
                            func_0021b4c8(D_00643274);
                            o->x2c++;
                        }
                    }
                    break;
                case 1:
                    if (func_0021b7f0()) {
                        p = func_001f31a8(D_003F5E30, 50);
                        if (p) {
                            func_001f3e48(p, o);
                            k = D_00643274;
                            p->x24 = D_003F53C0[k];
                            p->x2c = 256;
                            p->x28 = 0;
                            p->x30 = D_003F56A0[k];
                        }
                        o->x2c++;
                    }
                    break;
                case 2:
                    o->x2c = 0;
                    break;
                }
            }
        } else {
            if (func_0021b7f0()) {
                func_001f3758(D_00643110->x10);
                D_00643114 = 1;
            }
        }
    }
    func_0021b820();
    if (func_0021e898(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 2);
    } else if (o->x2c != 2) {
        func_0021cb88(o, 176, 8, 320, 2);
    } else if (func_0021b170(D_00643274)) {
        func_0021cba8(o, 176, 8, 320, 3);
    } else {
        func_0021cb88(o, 176, 8, 320, 3);
    }
    func_00203788(o, 372, 40, 486, 0x80C8C8C8);
    func_0021c9a0(o, 16, 72);
    func_0021cb00(o, 32, 108, 9, 30);
    func_0021cb00(o, 280, 108, 9, 30);
    t = (s32)func_001c2df0((s8 *)D_003F34F8, func_0021dc38(D_00643274));
    func_0010edb0(((o->xb0 - 0x7000) >> 4) + 32, ((o->xb4 - 0x7400) >> 4) + 84, 256, D_00643250 * 2, o->x90, t);
    if (((*(s32 *)&D_003E8E08) = o->x24) && o->xd8 - 1 == func_001fd668(o)) {
        func_001f94f0(o, 0, 282, 328, func_0021b800(6), 15, 0x50461E00);
    }
    if (D_00643118 == 2) func_0021e120(o, 416, 88, D_00643274);
}
#include "data/pieces/D_003F5E00.h"
