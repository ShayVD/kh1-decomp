/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0018a7e0();
M2C_UNK func_0018a8f8();
M2C_UNK func_0018aa10();
M2C_UNK func_001a8920(s32, M2C_UNK, M2C_UNK);
M2C_UNK func_0024edf0(void *, s32);
M2C_UNK func_002672f8(s32, s32, s32);
M2C_UNK func_00267328(void *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceGsExecLoadImage(void *, void *);
M2C_UNK sceGsSetDefLoadImage(void *, s16, s16, s16, s16, s16, s16, s16);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_002BBFA0;
extern M2C_UNK D_00615E70;
extern s32 D_00615E64;
extern s32 D_00615E68;
extern s32 D_00616214;
void func_00183a00(s32, s32, s32);
void memset(s32, s32, s32);

void func_00180ab8(void *arg0, s16 arg1) {
    s32 sp[24];
    s16 var_v1;

    var_v1 = M2C_FIELD(arg0, s16 *, 0);
    if (var_v1 >= 0x3800) {
        var_v1 = (var_v1 + arg1) - 0x3800;
    }
    sceGsSetDefLoadImage(sp, var_v1, M2C_FIELD(arg0, s16 *, 4), M2C_FIELD(arg0, s16 *, 6), M2C_FIELD(arg0, s16 *, 8), M2C_FIELD(arg0, s16 *, 0xA), M2C_FIELD(arg0, s16 *, 0xC), M2C_FIELD(arg0, s16 *, 0xE));
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(sp, arg0 + 0x20);
}

void func_001812d0(void *arg0) {
    s32 sp[16];
    func_00267328(sp, &D_002BBFA0, &D_00615E70);
    func_0024edf0(sp, M2C_FIELD(arg0, s32 *, 0x8C));
}

void func_00182840(s32 arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x94);
    if (temp_v0 != NULL) {
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
        memset(arg0, 0, 0xC0);
    }
}

void func_00182e78(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_00615E64 = arg0;
    if (arg1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x10) = (s32) M2C_FIELD(arg1, s32 *, 0x14);
        M2C_FIELD(arg0, s32 *, 0x14) = (s32) M2C_FIELD(arg1, s32 *, 0x18);
        M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg1, s32 *, 0x1C);
    }
    func_00183a00(arg0, arg2, arg3);
}

void func_00185c50(void *arg0) {
    s32 temp_a0;

    temp_a0 = D_00615E68 + 0x40;
    func_002672f8(temp_a0, M2C_FIELD(arg0, s32 *, 4) + 0x10, temp_a0);
}

void func_001860a8(void) {

}

void func_00186158(s32 arg0, s32 arg1, void *arg2) {
    D_00616214 = arg0 + *M2C_FIELD(arg2, s32 **, 0xC) + 0xA0;
}

void func_0018a808(void) {
    func_0018a7e0();
}

void func_0018a918(void) {
    func_0018a8f8();
}

void func_0018aa38(void) {
    func_0018aa10();
}

void func_0018c658(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 3);
}

void func_0018c688(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 8);
}

void func_0018c6b8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 8);
}

void func_0018c6e8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 0x80, 8);
}

void func_0018c718(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x10);
}

void func_0018c748(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x10);
}

void func_0018c778(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 0x40, 0x10);
}

void func_0018c7a8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x18);
}

void func_0018c7d8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x18);
}

void func_0018c808(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x20);
}

void func_0018c838(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x20);
}

void func_0018c868(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 0x20, 0x20);
}

void func_0018c898(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x28);
}

void func_0018c8c8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x28);
}

void func_0018c8f8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x30);
}

void func_0018c928(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x30);
}

void func_0018c958(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x40);
}

void func_0018c988(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x40);
}

void func_0018c9b8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 0x10, 0x40);
}

void func_0018c9e8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0x80);
}

void func_0018ca18(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0x80);
}

void func_0018ca48(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 8, 0x80);
}

void func_0018ca78(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 1, 0xFF);
}

void func_0018caa8(s32 arg0, void *arg1) {
    func_001a8920(arg0 + *M2C_FIELD(arg1, s32 **, 0xC) + 0xA0, 4, 0xFF);
}
