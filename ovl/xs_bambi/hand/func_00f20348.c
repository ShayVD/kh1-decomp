/* xs_bambi.x func_00f20348: matched by hand (session 131b). */
#include "ovl.h"

extern u8 *D_00F20900;
extern u8 D_00F20A10[], D_00F20A30[];
void func_00f20600(void *, void *, s32, f32 *);
void func_00f20348(void) {
    OvlVec v;
    PlatVu0CopyVector(v, D_00F20900 + 0x10);
    func_00f20600(D_00F20A10, D_00F20A30, 0x80, v);
}
