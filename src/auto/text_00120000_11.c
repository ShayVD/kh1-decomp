/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00136d38(void *);
M2C_UNK func_002675a8(void *, s32);
extern s32 D_00350D80;
f32 atan2f(f32, f32);
void *func_00123488();

void func_00123ab8(s32 arg0, s32 arg1) {
    void *temp_v0;

    temp_v0 = func_00123488();
    M2C_FIELD(temp_v0, s64 *, 0x370) = (s64) (M2C_FIELD(temp_v0, s64 *, 0x370) | ((s64) 0x8000 << 0x1D));
    func_002675a8(temp_v0 + 0x30, arg1);
    func_00136d38(temp_v0);
}

void func_00129530(void *arg0) {
    s32 sp[4];
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0);
    func_002675a8(sp, M2C_FIELD(arg0, s32 *, 4));
    M2C_FIELD(temp_s0, f32 *, 0x150) = atan2f(M2C_FIELD(sp, f32 *, 0x0), M2C_FIELD(sp, f32 *, 0x8));
}

void func_00129d68(void **arg0) {
    void *temp_a1;

    temp_a1 = *arg0;
    M2C_FIELD(temp_a1, s64 *, 0x370) = (s64) (M2C_FIELD(temp_a1, s64 *, 0x370) | ((s64) 0x8000 << 0x24));
}

void func_0012a198(void **arg0) {
    void *temp_a3;

    temp_a3 = *arg0;
    if (!(((u64) M2C_FIELD(temp_a3, u64 *, 0x370) >> 0x36) & 1)) {
        D_00350D80 -= M2C_FIELD(M2C_FIELD(temp_a3, void **, 0x130), u8 *, 0x59);
        M2C_FIELD(temp_a3, u64 *, 0x370) = (u64) (M2C_FIELD(temp_a3, u64 *, 0x370) | ((s64) 0x8000 << 0x27));
    }
}

void func_0012a338(void **arg0) {
    void *temp_a1;

    temp_a1 = *arg0;
    M2C_FIELD(temp_a1, s64 *, 0x370) = (s64) (M2C_FIELD(temp_a1, s64 *, 0x370) | ((s64) 0x8000 << 0x25));
}
