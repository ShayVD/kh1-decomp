#include "common.h"
typedef struct { u8 lo : 3; u8 st : 2; u8 hi : 3; } HddSt;
extern HddSt D_002C5968;
extern s32 D_0046A610;
s32 WaitSema(s32);
s32 iSignalSema(s32);
s32 func_0025e990(const char *);
s32 func_0025dd48(const char *, s32, s32, s32, s32, s32);
void func_0024d5d0(s32);
s32 func_0026aca8(void *);
s32 func_0024d4a0(void);

void func_0024d618(s32 sema) {
    u8 buf[16];
    for (;;) {
        WaitSema(sema);
        D_002C5968.st = 2;
        if (func_0025e990("hdd") < 0 || func_0025dd48("hdd:", 0x4807, 0, 0, 0, 0) == 3) {
            while (func_0025dd48("dev9x:", 0x4402, 0, 0, 0, 0) < 0) func_0024d5d0(100000);
        } else {
            func_0025dd48("pfs:", 0x5003, 0, 0, 0, 0);
            while (func_0025dd48("hdd:", 0x4806, 0, 0, 0, 0) < 0) func_0024d5d0(100000);
        }
        while (func_0026aca8(buf) == 0) func_0024d5d0(100000);
        D_002C5968.st = 3;
        D_0046A610++;
    }
}

void func_0024d7b0(s32 sema) {
    D_002C5968.st = 1;
    if (func_0024d4a0()) iSignalSema(sema);
}
