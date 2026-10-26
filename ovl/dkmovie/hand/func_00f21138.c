/* dkmovie.x func_00f21138: matched by hand. */
#include "ovl.h"

typedef struct { s32 data; s32 addr; s32 size; s32 mode; } SifDma;
void FlushCache(s32);
s32 sceSifSetDma(SifDma *, s32);
s32 sceSifDmaStat(s32);
extern SifDma D_00F28600;
extern s32 D_00F28640;
extern s32 D_00F28644;
s32 func_00f21138(s32 dst, s32 src, s32 size) {
    s32 *id;
    D_00F28600.data = src;
    D_00F28600.addr = dst;
    D_00F28600.size = size;
    D_00F28600.mode = 0;
    FlushCache(0);
    id = &D_00F28640;
    *id = sceSifSetDma(&D_00F28600, 1);
    while (sceSifDmaStat(D_00F28640) >= 0) {
    }
    D_00F28644 = 1;
    return size;
}
