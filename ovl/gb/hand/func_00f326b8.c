/* gb.x func_00f326b8: matched by hand. */
#include "ovl.h"

extern s32 D_00F61620;
extern s32 D_00F80710[];
extern s32 D_00F80750[];
extern u64 D_00F80790[];

void func_00f326b8(void) {
    s32 i;
    D_00F61620 = 0; for (i = 0; i < 16; i++) { D_00F80750[i] = 0; D_00F80710[i] = 1; D_00F80790[i] = 0x3F80000080808080; }
}
