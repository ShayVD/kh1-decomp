/* dktitle.x func_00f20118: matched by hand. */
#include "ovl.h"

typedef struct { u32 w[4]; } Q;
extern Q D_00F276F0[];
extern s32 D_00F2C6F4;
extern char D_00F272D0[];
void printf(char *, ...);
void func_00106b18(s32);
void func_00f20118(s32 arg) {
    D_00F276F0[D_00F2C6F4].w[0] = 0x70000000;
    D_00F276F0[D_00F2C6F4].w[1] = D_00F276F0[D_00F2C6F4].w[2] = D_00F276F0[D_00F2C6F4].w[3] = 0;
    D_00F2C6F4++;
    if (D_00F2C6F4 >= 256) printf(D_00F272D0);
    func_00106b18(arg);
}
