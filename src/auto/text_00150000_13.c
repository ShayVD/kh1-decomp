/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern void *D_00308CDC;
s32 func_0013c968(s32, s32);
void func_001358b8(s32, s32);
void func_001373f8(s32, f32);
void func_00141468(s32, s32);
void func_00148068(s32, f32);

void func_00153d88(s32 arg0) {
    s32 temp_a0;

    if (M2C_FIELD(arg0, s32 *, 0x88) & 0x20) {
        func_001373f8(arg0, 30.0f);
    }
    M2C_FIELD(arg0, s32 *, 0x88) = (s32) (M2C_FIELD(arg0, s32 *, 0x88) & ~0x30);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x3C) == 0) {
        if (func_0013c968(9, (s32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), u16 *, 0x4C)) > 0) {
            func_00141468(arg0, M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40));
        } else {
            func_00141468(arg0, (s32) ((f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x6C), s32 *, 0x40) * M2C_FIELD(D_00308CDC, f32 *, 0x8C)));
        }
    }
    temp_a0 = M2C_FIELD(arg0, s32 *, 0x400);
    if (temp_a0 == 0) {
        return;
    }
    func_00148068(temp_a0, 12.0f);
    M2C_FIELD(arg0, s32 *, 0x400) = 0;
    func_001358b8(arg0, 0xC);
}
