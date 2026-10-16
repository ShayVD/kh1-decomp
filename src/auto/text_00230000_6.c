/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0011d768(M2C_UNK);
M2C_UNK func_0011d7c0(M2C_UNK);
M2C_UNK func_00141348(s32 *, void *);
M2C_UNK func_001f3840(s32);
M2C_UNK func_00231740(M2C_UNK, s32, M2C_UNK, M2C_UNK);
M2C_UNK func_00231958();
M2C_UNK func_00237018(M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_002370c8(M2C_UNK *);
M2C_UNK func_00238a70();
M2C_UNK func_00246a70(s32, s32, s32, s32);
M2C_UNK func_002499f0();
M2C_UNK func_002672f8(M2C_UNK *, void *, s32);
M2C_UNK func_00267620();
M2C_UNK func_002676c0(void *, void *, f32);
M2C_UNK func_00267768(void *, M2C_UNK *, f32);
M2C_UNK func_00267810(void *, void *, f32);
M2C_UNK func_00267930(s32, M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK sceGsExecLoadImage(void *, M2C_UNK *);
M2C_UNK sceGsSetDefLoadImage(void *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_00425CE0;
extern M2C_UNK D_006480D0;
extern M2C_UNK D_00648230;
extern s32 D_003F7A64;
extern s32 D_0064770C;
extern s32 D_00651E50[];
f32 func_0011d790(M2C_UNK, s32);
s32 func_00122ff8(s32);

void func_00231908(s32 arg0) {
    func_00231740(0, arg0, 0, 0);
}

void func_00231930(s32 arg0) {
    func_00231740(1, arg0, 0, 0);
}

void func_00231980(void) {
    func_00231958();
}

void func_00231998(void) {
    func_00231958();
}

void func_002319b0(void) {
    D_003F7A64 = 0;
}

void func_00232aa8(void) {
    func_001f3840(D_0064770C);
}

void func_00232ac8(void) {

}

void func_00236c68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, void *arg4) {
    s32 sp[28];
    func_00267768(sp, &D_00425CE0, M2C_FIELD(arg4, f32 *, 0));
    func_00267810(sp, sp, M2C_FIELD(arg4, f32 *, 4));
    func_002676c0(sp, sp, M2C_FIELD(arg4, f32 *, 8));
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x40), sp, arg2);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x50), sp, arg3);
    func_002672f8(&M2C_FIELD(sp, M2C_UNK *, 0x60), sp, arg1);
    func_00267930(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x60), &M2C_FIELD(sp, M2C_UNK *, 0x40), &M2C_FIELD(sp, M2C_UNK *, 0x50));
}

void func_00236de8(void *arg0, f32 fparg0) {
    func_00267620();
    M2C_FIELD(arg0, f32 *, 0) = (f32) (M2C_FIELD(arg0, f32 *, 0) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) (M2C_FIELD(arg0, f32 *, 0x14) * fparg0);
    M2C_FIELD(arg0, f32 *, 0x28) = (f32) (M2C_FIELD(arg0, f32 *, 0x28) * fparg0);
}

void func_002372e0(void) {
    func_002370c8(&D_006480D0);
    func_00237018(&D_006480D0, 0x16, 1);
}

void func_00239368(void) {
    s32 sp[24];
    func_00238a70();
    sceGsSetDefLoadImage(sp, 0x3FD8, 1, 0, 0, 0, 0x10, 0x10);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(sp, &D_00648230);
    func_002499f0();
}

void func_0023c1b0(s32 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    if (func_00122ff8(*arg0) != 0) {
        func_00141348(arg0, sp);
        if ((M2C_FIELD(sp, M2C_UNK *, 0x0) != 0) && (M2C_FIELD(sp, M2C_UNK *, 0x0) != 2)) {
            func_00246a70(arg1, arg2, M2C_FIELD(sp, M2C_UNK *, 0x4), M2C_FIELD(sp, M2C_UNK *, 0x8));
        }
    }
}

void func_0023d148(s32 arg0) {
    if (D_00651E50[4168] == 0) {
        func_0011d768(0x2D);
        func_0011d790(0x2D, arg0);
        D_00651E50[4168] = 1;
    }
}

void func_0023d1a0(void) {
    if (D_00651E50[4168] == 1) {
        func_0011d7c0(0x2D);
        D_00651E50[4168] = 0;
    }
}
