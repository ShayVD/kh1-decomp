/* The model renderer's DMA and GS side, default flags (docs/modules.md
 * "Session 52"): the DMA channel 1 / 2 handlers (func_0015eda8 adds them,
 * func_0015ee10 removes them, func_0015efc0 is the handler) and the packet
 * list helpers.  The rest is in mdlgs.nostrict.c.  Read from the code, not proved by a boot. */
#include "m2c.h"
#include "actor.h"
#include "data/pieces/D_00304BE8.h"
#include "data/bss_0055.h"
#include "data/pieces/D_002E26A0.h"
#include "data/pieces/D_002C58B0.h"
#include "data/pieces/D_002E31B0.h"
#include "data/pieces/D_00350CE0.h"
#include "common.h"
#include "platform/thread.h"
#include "platform/gs.h"
#include "data/pieces/D_00304BE8_s.h"
#include "data/pieces/D_00351A30.h"
#include "data/pieces/D_00308CDC.h"
#include "data/pieces/D_002C58A0.h"
#include "data/pieces/D_002BBDF8.h"
#include "data/pieces/D_00351BC8.h"

/* func_0015ed80 (from auto/text_00150000.c). */
M2C_UNK func_0011f090(s32, s32, s32);
extern s32 D_00559DB0;
void func_0015ed80(s32 arg0, s32 arg1) {
    func_0011f090(D_00559DB0, arg0, arg1);
}

/* func_0015eda8 (from auto/text_00150000_2.c). */
s32 func_0015efc0();
extern s32 D_00351BC0;
extern s32 D_00351BC4;
void func_0015eda8(void) {
    PlatDisableDmac(1);
    PlatDisableDmac(2);
    D_00351BC0 = PlatAddDmacHandler(1, &func_0015efc0, 0);
    D_00351BC4 = PlatAddDmacHandler(2, &func_0015efc0, 0);
}

/* func_0015ee10 (from auto/text_00150000_3.c). */
#define D_00351BC0 (*(volatile s32 (*)) &D_00351BC0)
#define D_00351BC4 (*(volatile s32 (*)) &D_00351BC4)
void func_0015ee10(void) {
    PlatDisableDmac(1);
    PlatDisableDmac(2);
    PlatRemoveDmacHandler(1, D_00351BC0);
    PlatRemoveDmacHandler(2, D_00351BC4);
    D_00351BC0 = -1;
    D_00351BC4 = -1;
}
#undef D_00351BC0
#undef D_00351BC4

/* func_0015ee78 (from auto/text_00150000.c). */
extern s32 D_0055BDE0;
void func_0015ee78(s32 arg0, s32 arg1) {
    func_0011f090(D_0055BDE0, arg0, arg1);
}

/* func_0015ef60 (from hand/text_00150000_h10.c). */
extern volatile s32 D_00559DB4;
void func_0015ef60(void) {
    D_002BBDF8;
    while (D_00559DB4) ;
    PlatGsSyncPath(0, 0);
    PlatDisableDmac(1);
    PlatDisableDmac(2);
}

/* func_0015efc0 (from hand/text_00150000_s6.c). */
s32 func_0015ea98(void);
/* Runs func_0015ea98 with the interrupt-safe cache flush installed in the
 * flush hook, then restores FlushCache and re-enables interrupts. */
s32 func_0015efc0(void)
{
    void **p = ((void **)&D_00351BC8);

    *p = iFlushCache;
    func_0015ea98();
    *p = FlushCache;
    __asm__ volatile("sync\n\tei");
    return 0;
}

/* func_0015f010 (from auto/text_00150000.c). */
void func_0015f010(void) {

}

/* func_0015f108 (from auto/text_00150000.c). */
M2C_UNK func_00216180();
M2C_UNK func_00232ad0(M2C_UNK);
void func_0015f108(void) {
    func_00232ad0(6);
    func_00216180();
}

