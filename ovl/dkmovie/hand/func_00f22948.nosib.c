/* dkmovie.x func_00f22948: matched by hand. */
#include "ovl.h"

typedef struct { s32 f0; s32 f4; s32 f8; s32 fc; s32 f10; s32 f14; s32 f18; s32 f1c; s32 f20; s32 f24; s32 f28; } Mv;
void func_00f255e8(void);
s32 sceGsSyncPath(s32, s32);
void FlushCache(s32);
void func_0024e6e8(s32, s32);
void func_00f22c58(s32, s32, s32, s32, s32, s32, s32);
void func_00f22ca8(s32, s64, s32, s32, s32, s32, s32, s32);
void func_00f22d28(s32, s32, s32, s32, s32);
void func_00f22db0(s32, s32, s32);
void func_00f22d80(s32, s32, s32, s32);
void func_00f22dd8(s32, s32);

void func_00f22948(Mv *m) {
    s32 x0;
    s32 ny;
    u32 qw;
    u32 step;
    s32 yinc;
    s32 nx;
    s32 src;
    s32 f28;
    s32 bp;
    s32 psm;
    s32 p;
    s32 y;
    s32 i;
    s32 j;
    s32 eop;

    nx = m->f10 >> 4;
    src = m->f4;
    yinc = m->f20;
    ny = m->f14 >> 4;
    f28 = m->f28;
    if (src & 0xF) {
        func_00f255e8();
    }
    step = m->f24 == 0 ? 0x400 : 0x200;
    if (f28 == 0) {
        sceGsSyncPath(0, 0);
        FlushCache(0);
        step = 0x300;
        func_0024e6e8(src, m->f10 * m->f14);
    }
    bp = m->f18 / 64;
    psm = m->f24 ? 2 : (f28 == 0);
    p = m->f0 | 0x20000000;
    x0 = m->f8;
    y = m->fc;
    func_00f22c58(p, 0, 0, 0, 1, 0, 3);
    p += 16;
    qw = step >> 4;
    func_00f22ca8(p, 14, 1, 0, 0, 0, 0, 2);
    p += 16;
    func_00f22d28(p, m->f1c, bp, psm, f28);
    p += 16;
    func_00f22db0(p, 16, 16);
    p += 16;
    for (j = 0; j < ny; j++) {
        for (i = 0; i < nx; i++) {
            eop = 0;
            if (j == ny - 1) {
                eop = i == nx - 1;
            }
            func_00f22c58(p, 0, 0, 0, 1, 0, 4);
            p += 16;
            func_00f22ca8(p, 14, 1, 0, 0, 0, 0, 2);
            p += 16;
            func_00f22d80(p, 0, x0 + i * 16, y + j * 16);
            p += 16;
            func_00f22dd8(p, 0);
            p += 16;
            func_00f22ca8(p, 0, 0, 2, 0, 0, eop, qw);
            p += 16;
            func_00f22c58(p, 0, src, 0, 3, 0, qw);
            src += step;
            p += 16;
        }
        if (yinc) {
            y += 16;
        }
    }
    func_00f22c58(p, 0, 0, 0, 7, 0, 0);
}
