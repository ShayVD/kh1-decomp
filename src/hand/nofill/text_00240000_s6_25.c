#include "common.h"
typedef struct { u8 lo : 3; u8 st : 2; u8 hi : 3; } HddSt;
extern volatile HddSt D_002C5968;
extern s32 D_0046A610;
s32 WaitSema(s32);
s32 iSignalSema(s32);
s32 func_0025e990(const char *);
s32 func_0025dd48(const char *, s32, s32, s32, s32, s32);
void func_0024d5d0(s32);
s32 func_0026aca8(void *);
s32 func_0024d4a0(void);

static inline s32 hdd_ok(void) { return func_0025e990("hdd"); }
static inline s32 hdd_ctl(s32 cmd) { return func_0025dd48("hdd:", cmd, 0, 0, 0, 0); }
static inline void wait_dev9x(void) {
    while (func_0025dd48("dev9x:", 0x4402, 0, 0, 0, 0) < 0) func_0024d5d0(100000);
}
static inline void pfs_ctl(void) { func_0025dd48("pfs:", 0x5003, 0, 0, 0, 0); }
/* rodata */
void func_0024d618(s32 sema) {
    u8 buf[16];
    for (;;) {
        WaitSema(sema);
        D_002C5968.st = 2;
        if (hdd_ok() >= 0) {
            if (hdd_ctl(0x4807) != 3) {
                pfs_ctl();
                goto hdd;
            }
            wait_dev9x();
            goto done;
        hdd:
            while (hdd_ctl(0x4806) < 0) func_0024d5d0(100000);
        } else {
            wait_dev9x();
        }
    done:
        while (func_0026aca8(buf) == 0) func_0024d5d0(100000);
        D_002C5968.st = 3;
        D_0046A610++;
    }
}

