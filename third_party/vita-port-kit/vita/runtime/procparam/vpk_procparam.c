/* The main thread's stack as the coroutines' pool (vpk_procparam.h).  Needs vita/runtime/costack.
 * From kh1-decomp host/vita/main.c @ e1575e1a. */
#include <psp2/kernel/threadmgr.h>
#include <string.h>
#include "vpk_procparam.h"
#include "../costack/vpk_costack.h"

unsigned int vpk_main_stack_to_costack(unsigned int own_bytes) {
    SceKernelThreadInfo ti;
    volatile unsigned char here;
    unsigned int pool = 0;
    memset(&ti, 0, sizeof ti);
    ti.size = sizeof ti;
    if (sceKernelGetThreadInfo(sceKernelGetThreadId(), &ti) < 0 || !ti.stack) return 0;
    if ((unsigned char *)&here - (unsigned char *)ti.stack > (int)own_bytes)
        vpk_costack_pool(ti.stack, pool = (unsigned int)((unsigned char *)&here - (unsigned char *)ti.stack) - own_bytes);
    /* the whole stack is the app's, the main thread's own part included (memory checks accept it) */
    if (ti.stackSize > 0) vpk_costack_stack(ti.stack, (unsigned int)ti.stackSize);
    return pool;
}
