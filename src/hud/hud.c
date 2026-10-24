/* The HUD's set up (docs/modules.md "Session 45"), 0x00236f00-0x00236fd8.
 * func_00236f18 (called from the start up in h13 and in
 * text_00100000_9.c) clears the draw list D_00425F80 (256 buckets
 * at D_00425F88) and calls the set up of each part from 0x0023b570 to
 * 0x00249250 (most likely the battle HUD: the gauges drawn as arcs up to
 * 3/2 pi, the command menu; not proved by a boot); func_00239488 is the
 * matching step.  func_00236f00 loads a 16x16 CLUT (func_00239368) at
 * start up.  func_00236fc0 / func_00236fc8 / func_00236fd0 are empty hooks
 * (no C caller). */
#include "common.h"
#include "gfx/drawlist.h"
#include "data/data_0042.h"

extern DrawList D_00425F80;
extern DrawBucket D_00425F88[256];
void func_00239368(void);
void func_0023b570(void);
void func_0023c968(void);
void func_00242a38(void);
void func_00243a90(void);
void func_00244500(void);
void func_00245148(void);
void func_002456e8(void);
void func_00245e40(void);
void func_00246438(void);
void func_00246bc8(void);
void func_00247258(void);
void func_00248400(void);
void func_00248ea0(void);
void func_00249250(void);

void func_00236f00(void) {
    func_00239368();
}

void func_00236f18(void) {
    func_00237660(&D_00425F80, D_00425F88, 8);
    func_0023b570();
    func_0023c968();
    func_00242a38();
    func_00243a90();
    func_00244500();
    func_00245148();
    func_002456e8();
    func_00245e40();
    func_00246438();
    func_00246bc8();
    func_00247258();
    func_00248400();
    func_00248ea0();
    func_00249250();
    D_00425F78 = 0;
}

void func_00236fc0(void) {
}

void func_00236fc8(void) {
}

s32 func_00236fd0(void) {
    return 0;
}
