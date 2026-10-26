/* dkmovie.x func_00f27fc8: matched by hand. */
#include "ovl.h"

s32 sceOpen(s32, s32, ...);
void func_00f23480(void);
s32 sceRead(s32, void *, s32);
s32 sceIoctl(s32, s32, void *);
void FlushCache(s32);
extern s32 D_0003DD20;
extern s32 D_0003DD24;
extern s32 D_0003DD48;
extern s32 D_0003DEF4;
extern s32 D_0003DF1C;
typedef struct { s32 f0; s32 f4; s16 f8; s16 fa; s32 fc; } Hdr;
#define G(s) (*(s32 *)(arg2 + O_##s))
#define O_D_0003DD20 0x3DD20
#define O_D_0003DD24 0x3DD24
#define O_D_0003DD48 0x3DD48
#define O_D_0003DEF4 0x3DEF4
#define O_D_0003DF1C 0x3DF1C

s32 func_00f27fc8(s32 arg0, Hdr *arg1, s32 arg2) {
    s32 stat[4];
    s32 fd;
    s32 n;

    G(D_0003DEF4) = 0;
    fd = sceOpen(arg0, 0x8001);
    G(D_0003DD48) = fd;
    if (fd < 0) {
        for (;;) func_00f23480();
    }
    sceRead(fd, arg1, 32);
    while (sceIoctl(fd, 1, stat), stat[0] != 0) func_00f23480();
    FlushCache(0);
    G(D_0003DEF4) += 32;
    G(D_0003DF1C) = arg1->fc;
    G(D_0003DD20) = arg1->f8;
    G(D_0003DD24) = arg1->fa;
    sceRead(fd, arg1, 16);
    while (sceIoctl(fd, 1, stat), stat[0] != 0) func_00f23480();
    FlushCache(0);
    G(D_0003DEF4) += 16;
    n = arg1->f4;
    sceRead(fd, arg1, n);
    while (sceIoctl(fd, 1, stat), stat[0] != 0) func_00f23480();
    FlushCache(0);
    G(D_0003DEF4) += n;
    return 1;
}
