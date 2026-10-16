/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK FlushCache(M2C_UNK);
M2C_UNK func_0010c040();
M2C_UNK func_0010c4b0();
M2C_UNK func_0010ec08(s32, void *, s32);
M2C_UNK func_0010ed20(s32, s32, s32, void *, void *);
M2C_UNK func_0010fbe0(M2C_UNK *);
M2C_UNK func_0011ef10(M2C_UNK, M2C_UNK *);
M2C_UNK func_0011efa8(M2C_UNK *, M2C_UNK *, M2C_UNK, M2C_UNK);
M2C_UNK func_00120748(void *, s32, M2C_UNK *, M2C_UNK);
M2C_UNK func_00121ee0(void *);
M2C_UNK func_00267328(void *, M2C_UNK *, void *);
M2C_UNK func_00267768(void *, M2C_UNK *, f32);
M2C_UNK memcpy(M2C_UNK *, s32, s32);
M2C_UNK sceGsExecLoadImage(M2C_UNK *, M2C_UNK *);
M2C_UNK sceGsSetDefLoadImage(M2C_UNK *, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK);
M2C_UNK sceGsSyncPath(M2C_UNK, M2C_UNK);
M2C_UNK strcat(void *, M2C_UNK *);
M2C_UNK strcpy(void *, M2C_UNK *);
extern M2C_UNK D_002B7500;
extern M2C_UNK D_002B7590;
extern M2C_UNK D_002BC1B0;
extern M2C_UNK D_002BC210;
extern M2C_UNK D_002BCAF0;
extern M2C_UNK D_002BCCE0;
extern M2C_UNK D_0048CC30;
extern M2C_UNK D_0048CF10;
extern M2C_UNK D_00495190;
extern M2C_UNK D_00495210;
extern M2C_UNK D_004D5B10;
extern M2C_UNK D_00F20000;
extern M2C_UNK func_001012b8;
extern M2C_UNK func_00106b98;
extern M2C_UNK func_00109d98;
extern M2C_UNK func_0010c010;
extern s32 D_002A3F3C;
extern s32 D_00495254;
s32 func_001137c8(s32, M2C_UNK);
s32 func_001205f0(M2C_UNK *, s32);
s32 func_001559f0(M2C_UNK, M2C_UNK);
void *func_00121e28(M2C_UNK, void **);
void *func_0015ed80(s32, M2C_UNK *);

void func_001015a8(void) {
    s32 sp[16];
    s32 temp_v0;
    s32 temp_v0_2;

    strcpy(sp, &D_002BCCE0);
    strcat(sp, &D_0048CC30);
    temp_v0 = func_001559f0(0x34, 8);
    D_002A3F3C = temp_v0;
    temp_v0_2 = func_001137c8(temp_v0, 0x80);
    D_002A3F3C = temp_v0_2;
    func_00120748(sp, temp_v0_2, &func_001012b8, 0);
}

void func_00106bd8(s32 arg0, s32 arg1) {
    M2C_FIELD(func_0015ed80(arg1, &func_00106b98), s32 *, 0x10) = arg0;
}

void func_00109cd0(void) {
    sceGsSetDefLoadImage(&D_002BC1B0, 0xE00, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC1B0, &D_00F20000);
    sceGsSetDefLoadImage(&D_002BC210, 0x1400, 8, 1, 0, 0, 0x200, 0xC0);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    sceGsExecLoadImage(&D_002BC210, (s8 *)&D_00F20000 + 0x48000);
}

void func_00109df8(void) {
    func_0011ef10(0x2E630, &func_00109d98);
}

void func_0010b270(void *arg0, void *arg1) {
    s32 sp[16];
    func_00267768(sp, &D_002BCAF0, M2C_FIELD(arg1, f32 *, 0x20));
    func_00267328(sp, &D_00495190, sp);
    func_00267328(arg0, &D_00495210, sp);
}

void func_0010c078(void) {
    D_00495254 = 0;
    func_0010c040();
    func_0011efa8(&D_002B7590, &D_002B7500, 0x24, 4);
    func_0011ef10(0x2BFE8, &func_0010c010);
}

void func_0010edb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 sp[4];
    M2C_FIELD(sp, void * *, 0x0) = func_00121e28(0x2C, sp);
    M2C_FIELD(sp, void * *, 0x4) = func_00121e28(0x400, &M2C_FIELD(sp, void * *, 0x4));
    func_0010c4b0();
    func_0010ec08(arg5, M2C_FIELD(sp, void * *, 0x4), arg3);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 8);
    func_0010ed20(arg0, arg1, arg4, M2C_FIELD(sp, void * *, 0x4), M2C_FIELD(sp, void * *, 0x0));
    func_0010ec08(arg5, M2C_FIELD(sp, void * *, 0x4), arg3 + 1);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = 0U;
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 4);
    M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) = (u8) (M2C_FIELD(M2C_FIELD(sp, void * *, 0x0), u8 *, 0x13) | 8);
    func_0010ed20(arg0 + arg2, arg1, arg4, M2C_FIELD(sp, void * *, 0x4), M2C_FIELD(sp, void * *, 0x0));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x4));
    func_00121ee0(M2C_FIELD(sp, void * *, 0x0));
}

void func_0010fc38(void) {
    s32 temp_v0;

    temp_v0 = func_001559f0(0x34, 0xC);
    memcpy(&D_004D5B10, temp_v0, func_001205f0(&D_0048CF10, temp_v0));
    func_0010fbe0(&D_004D5B10);
}
