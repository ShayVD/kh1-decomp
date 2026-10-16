/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK func_00183b20(s32, s32);
M2C_UNK func_0019e3f0(s32);
M2C_UNK func_0019e710(s32);
M2C_UNK func_0019ea58(s32);
M2C_UNK func_001a62a8(s32);
M2C_UNK func_001a6538(s32);
M2C_UNK func_001a67a0(s32);
M2C_UNK func_002672f8(M2C_UNK *, s32, s32);
M2C_UNK func_00267328(s32, M2C_UNK *, s32);
M2C_UNK func_002673b8(M2C_UNK *, s32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_002675b8(s32, M2C_UNK *);
extern M2C_UNK D_003701D0;
extern M2C_UNK D_003701F0;
extern M2C_UNK D_00615E70;
extern M2C_UNK D_00616040;
extern s32 D_00615E64;
extern s32 D_00615E68;
void func_001a60d0(s32);
void func_001a60e8(s32, s32);

void func_00192f78(s32 arg0) {
    s32 sp[8];
    M2C_FIELD(sp, s32 *, 0x4) = M2C_FIELD(arg0, s32 *, 0x24);
    M2C_FIELD(sp, f32 *, 0xC) = M2C_FIELD(arg0, f32 *, 0x20);
    M2C_FIELD(sp, M2C_UNK * *, 0x8) = &D_00616040;
    M2C_FIELD(sp, s32 *, 0x10) = arg0 + 0x10;
    M2C_FIELD(sp, s32 *, 0x0) = arg0;
    func_001a60e8((s32) sp, 0);
}

void func_00193178(s32 arg0, void *arg1) {
    func_001a62a8(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0);
}

void func_001931a0(void) {

}

void func_001933c0(s32 arg0, s32 arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0;
    func_001a60d0(temp_s0);
    M2C_FIELD(temp_s0, s8 *, 8) = 4;
}

void func_00193690(s32 arg0, void *arg1) {
    func_001a6538(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0);
}

void func_001936b8(void) {

}

void func_00193910(s32 arg0, void *arg1) {
    func_001a67a0(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0);
}

void func_00193938(void) {

}

void func_00194360(void *arg0) {
    s32 sp[20];    s32 temp_a0;
    s32 temp_s0;
    s32 temp_s1;

    temp_s0 = M2C_FIELD(arg0, s32 *, 4);
    temp_s1 = temp_s0 + 0x10;
    func_002673b8(sp, temp_s1);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x10), temp_s0 + 0x20);
    func_002673b8(&M2C_FIELD(sp, M2C_UNK *, 0x20), temp_s0 + 0x30);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), temp_s1, D_00615E68 + 0x40);
    temp_a0 = D_00615E68 + 0x10;
    func_00267328(temp_a0, sp, temp_a0);
    func_002675a8(D_00615E68 + 0x40, &M2C_FIELD(sp, M2C_UNK *, 0x40));
}

void func_001985a8(s32 arg0, void *arg1) {
    func_002675b8(arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4) + 0xA0, &D_00615E70);
}

void func_00198648(s32 arg0, void *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    func_002675a8(temp_s0 + 0xA0, &D_003701D0);
    func_002675a8(temp_s0 + 0xB0, &D_003701F0);
}

void func_00198768(s32 arg0, void *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 4);
    func_002675a8(temp_s0 + 0xA0, &D_003701D0);
    func_002675a8(temp_s0 + 0xB0, &D_003701F0);
}

void func_0019d8a8(s32 arg0, void *arg1) {
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_v0;
    void *temp_s0;

    temp_s0 = arg0 + M2C_FIELD(M2C_FIELD(arg1, void **, 0xC), s32 *, 8) + 0xA0;
    temp_v0 = M2C_FIELD(temp_s0, s32 *, 0x50);
    if (temp_v0 != 0) {
        func_00183b20(D_00615E64, temp_v0);
        M2C_FIELD(temp_s0, s32 *, 0x50) = 0;
    }
    temp_a1 = M2C_FIELD(temp_s0, s32 *, 0x54);
    if (temp_a1 != 0) {
        func_00183b20(D_00615E64, temp_a1);
        M2C_FIELD(temp_s0, s32 *, 0x54) = 0;
    }
    temp_a1_2 = M2C_FIELD(temp_s0, s32 *, 0x58);
    if (temp_a1_2 != 0) {
        func_00183b20(D_00615E64, temp_a1_2);
        M2C_FIELD(temp_s0, s32 *, 0x58) = 0;
    }
}

void func_0019ee68(s32 arg0, s32 arg1, void *arg2) {
    s32 temp_s0;

    temp_s0 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
    func_0019e3f0(temp_s0);
    func_0019e710(temp_s0);
    func_0019ea58(temp_s0);
}
