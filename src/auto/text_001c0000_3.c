/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00122768(s32);
extern M2C_UNK D_00388CC4;
extern M2C_UNK D_0038CD3C;
extern f32 D_003C5630;
extern f32 D_003C5634;
extern s32 D_002BBE04;
extern s32 D_002C5958;
void func_001c6890(void);
void func_001c6a20(void);
void func_001ec7c0(s32);
void func_00242bd0(void);

s32 func_001c83c8(s32 arg0) {
    func_001c6890();
    D_003C5630 = (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    func_001c6a20();
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001c8420(s32 arg0) {
    func_001c6890();
    D_003C5634 = (f32) M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184);
    func_001c6a20();
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cded0(void) {
    D_002BBE04 = 0;
    func_001ec7c0(0);
    func_00242bd0();
    return 2;
}

s32 func_001ce358(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x204);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    if (temp_v1 >= 0x800) {
        *(M2C_UNK *)((s8 *)&D_00388CC4 + (temp_v1 * 4)) = 1;
    }
    return 2;
}

s32 func_001ce390(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x204);
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    if (temp_v1 >= 0x800) {
        *(M2C_UNK *)((s8 *)&D_00388CC4 + (temp_v1 * 4)) = 0;
    }
    return 2;
}

s32 func_001cee90(void *arg0) {
    func_00122768(*(M2C_UNK *)((s8 *)&D_0038CD3C + (M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x180) * 4) + arg0), s32 *, 0x184) * 4)));
    M2C_FIELD(arg0, s32 *, 0x180) = (s32) (M2C_FIELD(arg0, s32 *, 0x180) - 1);
    return 2;
}

s32 func_001cfed8(void) {
    D_002C5958 = D_002C5958 & ~4 & 0xF7FFFFFF;
    return 2;
}
#include "data/data_003C.h"
