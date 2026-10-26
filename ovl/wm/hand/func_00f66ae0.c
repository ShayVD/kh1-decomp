/* wm.x func_00f66ae0: the twin of gb.x func_00f3f9e8 (tools/ovl/twins.py). */
#include "ovl.h"

extern u64 *D_0108F030;

u64 *func_00f66ae0(u64 *p) {
    *D_0108F030 = (u32)((((u32)p - (u32)D_0108F030) >> 4) - 1 | 0x70000000); D_0108F030[1] = 0; return D_0108F030;
}
