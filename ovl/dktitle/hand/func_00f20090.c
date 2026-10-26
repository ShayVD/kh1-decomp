/* dktitle.x func_00f20090: matched by hand. */
#include "ovl.h"

typedef struct { u32 w[4]; } Q;
extern Q D_00F276F0[];
extern s32 D_00F2C6F4;
extern char D_00F272A8[];
void printf(char *, ...);
s32 exit(s32);
Q *func_00f20090(s32 addr, s32 qwc) {
    D_00F276F0[D_00F2C6F4].w[0] = qwc + 0x30000000;
    D_00F276F0[D_00F2C6F4].w[1] = addr;
    D_00F276F0[D_00F2C6F4].w[2] = D_00F276F0[D_00F2C6F4].w[3] = 0;
    D_00F2C6F4++;
    if (D_00F2C6F4 >= 256) { printf(D_00F272A8); exit(1); }
    return &D_00F276F0[D_00F2C6F4 - 1];
}
