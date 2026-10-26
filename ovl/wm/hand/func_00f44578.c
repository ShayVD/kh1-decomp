/* wm.x func_00f44578: matched by hand. */
#include "ovl.h"

s32 func_001bb500(s32, s32);
void func_001bb7c8(void *, s32);
extern s32 D_00F87054;
extern s32 D_00F87068;
extern s32 D_00F9B320;
extern s32 D_00F9B324;
extern s32 D_00FB73C8;
extern s32 D_00FB73E0;
extern s32 D_00FB73F8;
extern s32 D_010808E8[];
extern s32 D_010808F8[];
extern s32 D_01080904;

void func_00f44578(void) {
    s32 i;
    /* pinned: gcc otherwise swaps s0/s1 for these two addresses (pure register swap) */
    register s32 *p904 KH1_REG("$16");
    register s32 *pB324 KH1_REG("$17");
    for (i = 0; i < 3; i++) {
        D_010808E8[i] = func_001bb500(0x87000, 0x80);
        D_010808F8[i] = func_001bb500(0x20000, 0x80);
    }
    D_00F87068 = D_010808F8[2] + 0x10;
    p904 = &D_01080904;
    *p904 = func_001bb500(0x40000, 0x80);
    D_00F9B320 = func_001bb500(0x4000, 0x80);
    pB324 = &D_00F9B324;
    *pB324 = func_001bb500(0x4000, 0x80);
    D_00F87054 = func_001bb500(0x10000, 0x80);
    func_001bb7c8(&D_00FB73C8, *p904);
    func_001bb7c8(&D_00FB73E0, D_00F9B320);
    func_001bb7c8(&D_00FB73F8, *pB324);
}
