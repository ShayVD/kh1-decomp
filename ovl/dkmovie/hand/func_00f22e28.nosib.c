/* dkmovie.x func_00f22e28: matched by hand. */
#include "ovl.h"

void FlushCache(s32);
void func_00f22c58(s32, s32, s32, s32, s32, s32, s32);
void func_00f22ca8(s32, s64, s32, s32, s32, s32, s32, s32);
void func_00f22d28(s32, s32, s32, s32, s32);
void func_00f22db0(s32, s32, s32);
void func_00f22d80(s32, s32, s32, s32);
void func_00f22dd8(s32, s32);

void func_00f22e28(s32 p, s32 src, s32 step, s32 w, s32 h, s32 dbp, s32 mode, s32 f28, s32 y0) {
    s32 ny;
    s32 qw;
    s32 nx;
    s32 bp;
    s32 psm;
    s32 i;
    s32 j;
    s32 eop;

    ny = h >> 4;
    nx = w >> 4;
    FlushCache(0);
    if (f28 == 0) {
        step = 0x300;
    }
    if (mode == 0) {
        qw = 64;
        psm = f28 == 0;
    } else {
        qw = 32;
        psm = 2;
    }
    bp = (w + 63) / 64;
    p |= 0x20000000;
    func_00f22c58(p, 0, 0, 0, 1, 0, 3);
    p += 16;
    func_00f22ca8(p, 14, 1, 0, 0, 0, 0, 2);
    p += 16;
    func_00f22d28(p, dbp, bp, psm, f28);
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
            func_00f22d80(p, 0, i * 16, y0 + j * 16);
            p += 16;
            func_00f22dd8(p, 0);
            p += 16;
            func_00f22ca8(p, 0, 0, 2, 0, 0, eop, qw);
            p += 16;
            func_00f22c58(p, 0, src, 0, 3, 0, qw);
            src += step;
            p += 16;
        }
    }
    func_00f22c58(p, 0, 0, 0, 7, 0, 0);
}
