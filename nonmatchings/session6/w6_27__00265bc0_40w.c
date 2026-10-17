/* sceGsSyncPath (0x265bc0), mode sdk/gcc991111, VU0 cfc2 via asm. 828 vs 788 bytes. Remaining: (1) dump block: orig fills each jal scePrintf delay slot with the volatile 'lw a1,0(v0)' (ours leaves nop: 991111 reorg will not move volatile loads; orig address still built with lui/ori, i.e. not folded); (2) cfc2 result: orig 'andi v0,a2' (ours andi a2,a2); (3) error-message selection uses v0 for lui in ours (orig a0 directly). */
#include "common.h"
s32 scePrintf(const char *, ...);
extern char D_00492998[], D_00492A78[], D_00492AA8[], D_00492AD8[], D_00492B00[];
extern char D_004929C8[], D_004929D8[], D_004929E8[], D_004929F8[], D_00492A08[];
extern char D_00492A18[], D_00492A28[], D_00492A38[], D_00492A48[], D_00492A60[];
#define R(a) (*(volatile u32 *)(a))

static inline u32 vu1stat(void) {
    register u32 r asm("$6");
    __asm__ volatile ("cfc2 %0, $vi29" : "=r"(r));
    return r;
}

s32 sceGsSyncPath(s32 mode, u16 timeout) {
    u32 cnt = 0;
    char *msg;
    if (mode == 0) {
        while (R(0x10009000) & 0x100) {
            if (cnt++ > 0x1000000) {
                msg = D_00492998;
                goto err;
            }
        }
        while (R(0x1000a000) & 0x100) {
            if (cnt++ > 0x1000000) {
                msg = D_00492A78;
                goto err;
            }
        }
        while (R(0x10003c00) & 0x1f000003) {
            if (cnt++ > 0x1000000) {
                msg = D_00492AA8;
                goto err;
            }
        }
        if (vu1stat() & 0x100) {
            do {
                if (cnt++ > 0x1000000) {
                    msg = D_00492AD8;
                    goto err;
                }
            } while (vu1stat() & 0x100);
        }
        while (R(0x10003020) & 0xc00) {
            if (cnt++ > 0x1000000) {
                msg = D_00492B00;
                goto err;
            }
        }
        return 0;
    err:
        scePrintf(msg);
        scePrintf(D_004929C8, R(0x10009000));
        scePrintf(D_004929D8, R(0x10009030));
        scePrintf(D_004929E8, R(0x10009010));
        scePrintf(D_004929F8, R(0x10009020));
        scePrintf(D_00492A08, R(0x1000a000));
        scePrintf(D_00492A18, R(0x1000a030));
        scePrintf(D_00492A28, R(0x1000a010));
        scePrintf(D_00492A38, R(0x1000a020));
        scePrintf(D_00492A48, R(0x10003c00));
        scePrintf(D_00492A60, R(0x10003020));
        return -1;
    } else {
        s32 r = (R(0x10009000) & 0x100) != 0;
        if (R(0x1000a000) & 0x100) r |= 2;
        if (R(0x10003c00) & 0x1f000003) r |= 4;
        if (vu1stat() & 0x100) r |= 8;
        if (R(0x10003020) & 0xc00) r |= 0x10;
        return r;
    }
}
