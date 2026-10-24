/* The HDD install (src/game/hdd.c, docs/modules.md "Session 47"): the parts
 * built with no delay-slot fill.  func_0024d618 is the thread func_0024d808
 * starts: each time its semaphore is signalled it marks D_002C5968 busy
 * (2), checks the "hdd" device (func_0025e990), and either sets up pfs
 * (0x5003) and waits for "hdd:" (0x4806) or, when there is no drive or
 * "hdd:" answers 3 to 0x4807, waits for "dev9x:" (0x4402); then it waits on
 * func_0026aca8 and marks it done (3; D_0046A610 counts the rounds).
 * func_0024d7b0 is the handler func_00269960 installs: it marks D_002C5968
 * 1 and, when the modules loaded (func_0024d4a0), signals the thread.  The
 * ioctl numbers' meanings are not known; not proved by a boot. */
#include "common.h"
#include "data/data_0046.h"
#include "data/pieces/D_002C5968.h"

s32 WaitSema(s32);
s32 iSignalSema(s32);
s32 func_0025dd48(const char *, s32, s32, s32, void *, s32);
s32 func_0025e990(const char *);
s32 func_0026aca8(void *);
/* hdd.c */
s32 func_0024d4a0(void);
void func_0024d5d0(s32);

static inline s32 hdd_ok(void) { return func_0025e990("hdd"); }
static inline s32 hdd_ctl(s32 cmd) { return func_0025dd48("hdd:", cmd, 0, 0, 0, 0); }
static inline void wait_dev9x(void) {
    while (func_0025dd48("dev9x:", 0x4402, 0, 0, 0, 0) < 0) func_0024d5d0(100000);
}
static inline void pfs_ctl(void) { func_0025dd48("pfs:", 0x5003, 0, 0, 0, 0); }

void func_0024d618(s32 sema) {
    u8 buf[16];
    for (;;) {
        WaitSema(sema);
        (*(volatile Sema_2c5968 *)&D_002C5968).mode = 2;
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
        (*(volatile Sema_2c5968 *)&D_002C5968).mode = 3;
        D_0046A610++;
    }
}

void func_0024d7b0(s32 sema) {
    (*(volatile Sema_2c5968 *)&D_002C5968).mode = 1;
    if (func_0024d4a0()) iSignalSema(sema);
}
