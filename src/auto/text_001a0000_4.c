/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"
#include "ppp.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_001a50d0(M2C_UNK *, s32);
M2C_UNK func_001a5150(M2C_UNK *, s32);
M2C_UNK func_001a51d0(M2C_UNK *, s32);
M2C_UNK func_001a5688(void *);
M2C_UNK func_001a9350(void *);
M2C_UNK func_001aa1f8(s32, u8, u16, s32);
M2C_UNK func_00267328(M2C_UNK *, M2C_UNK *, M2C_UNK *);
M2C_UNK func_00267530(void *, s32, s32);
M2C_UNK func_002675a8(s32, M2C_UNK *);
M2C_UNK func_002675b8(s32, M2C_UNK *);
M2C_UNK sceGsExecLoadImage(void *, s32);
M2C_UNK sceGsSetDefLoadImage(void *, s32, u32, u8, s32, s32, s16, s16);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
extern M2C_UNK D_003701D0;
extern M2C_UNK D_003701F0;
extern M2C_UNK D_00575A00; /* src/data/bss_0057.c: u8 D_00575A00[0x10] */
extern M2C_UNK D_00615E70;
s32 func_001aab98(s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);

void pppRyjDrawMatrixWorldDttCon(s32 arg0, PppEntry *arg1) {
    func_002675b8(arg0 + arg1->offsets[1] + 0xE0, &D_00615E70);
}

void pppRyjDrawMatrixWorldDttFrCon(s32 arg0, PppEntry *arg1) {
    s32 temp_s0;

    temp_s0 = arg0 + arg1->offsets[1];
    func_002675a8(temp_s0 + 0xE0, &D_003701D0);
    func_002675a8(temp_s0 + 0xF0, &D_003701F0);
}

void func_001a5250(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a5150(sp, M2C_FIELD(arg1, s32 *, 4));
    func_001a51d0(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 8));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a50d0(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 0));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

void func_001a52e0(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a50d0(sp, M2C_FIELD(arg1, s32 *, 0));
    func_001a51d0(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 8));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a5150(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 4));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

void func_001a5370(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a51d0(sp, M2C_FIELD(arg1, s32 *, 8));
    func_001a50d0(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 0));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a5150(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 4));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

void func_001a5400(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a5150(sp, M2C_FIELD(arg1, s32 *, 4));
    func_001a50d0(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 0));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a51d0(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 8));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

void func_001a5490(M2C_UNK *arg0, void *arg1) {
    s32 sp[64];
    func_001a50d0(sp, M2C_FIELD(arg1, s32 *, 0));
    func_001a5150(&M2C_FIELD(sp, M2C_UNK *, 0x40), M2C_FIELD(arg1, s32 *, 4));
    func_00267328(&M2C_FIELD(sp, M2C_UNK *, 0x80), sp, &M2C_FIELD(sp, M2C_UNK *, 0x40));
    func_001a51d0(&M2C_FIELD(sp, M2C_UNK *, 0xC0), M2C_FIELD(arg1, s32 *, 8));
    func_00267328(arg0, &M2C_FIELD(sp, M2C_UNK *, 0x80), &M2C_FIELD(sp, M2C_UNK *, 0xC0));
}

void func_001a6518(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    func_001a5688(arg0 + 8);
}

void func_001a6538(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_00575A00;
}

void func_001a93b0(s32 arg0, s32 arg1) {
    s32 sp[4];
    func_00267530(sp, arg0, arg1);
    func_001a9350(sp);
}

void func_001aa388(void *arg0, s32 arg1) {
    s32 sp[24];
    sceGsSetDefLoadImage(sp, M2C_FIELD(arg0, u16 *, 0) & 0x3FFF, (u8) M2C_FIELD(arg0, u8 *, 0xA) >> 2, M2C_FIELD(arg0, u8 *, 0x18), M2C_FIELD(arg0, u8 *, 8) * 0x10, M2C_FIELD(arg0, u8 *, 9) * 0x10, M2C_FIELD(arg0, s16 *, 0xC), M2C_FIELD(arg0, s16 *, 0xE));
    sceGsSyncPath(0, 0);
    FlushCache(0);
    sceGsExecLoadImage(sp, M2C_FIELD(arg0, s32 *, 0x14));
    if (arg1 != 0) {
        sceGsSyncPath(0, 0);
    }
}

void func_001aa420(void *arg0, s32 arg1) {
    func_001aa1f8(M2C_FIELD(arg0, s32 *, 4), M2C_FIELD(arg0, u8 *, 9), M2C_FIELD(arg0, u16 *, 0), arg1);
}

s32 func_001aadb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3, f32 fparg4, f32 fparg5, f32 fparg6, f32 fparg7) {
    return func_001aab98(arg0, arg0 + M2C_FIELD(arg0, s32 *, 0x3C), arg2, arg3, arg4, arg5, arg6, arg7, fparg0, fparg1, fparg2, fparg3, fparg4, fparg5, fparg6, fparg7);
}
