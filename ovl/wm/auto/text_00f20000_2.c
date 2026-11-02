/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00FBB7F0;
extern M2C_UNK D_00FBDA80;
extern f32 D_00FBB7D8;
extern s32 D_00F87048;
s32 func_00f2cae8();
void func_001becb8(M2C_UNK *, f32 *, M2C_UNK);
void func_001bf098(s32, M2C_UNK *);
void func_00f68770(M2C_UNK, M2C_UNK, s32, M2C_UNK, s32);
void sceVu0AddVector(f32 *, f32 *, f32 *);
void sceVu0CopyMatrix(M2C_UNK *, s32);
void sceVu0CopyVector(f32 *, M2C_UNK *);
void sceVu0Normalize(f32 *, f32 *);

void func_00f2dad0(s32 arg0) {
    s32 sp[24];    s32 temp_s3;

    temp_s3 = func_00f2cae8(arg0) + 0x20;
    sceVu0CopyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x20), temp_s3);
    sceVu0CopyVector(sp, &M2C_FIELD(sp, M2C_UNK *, 0x50));
    M2C_FIELD(sp, f32 *, 0x8) += 1e+02f;
    sceVu0CopyVector(&M2C_FIELD(sp, f32 *, 0x10), &D_00FBDA80);
    M2C_FIELD(sp, f32 *, 0x0) -= M2C_FIELD(&D_00FBDA80, f32 *, 0) + M2C_FIELD(&D_00FBB7F0, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x4) -= M2C_FIELD(&D_00FBDA80, f32 *, 4) + M2C_FIELD(&D_00FBB7F0, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x8) -= M2C_FIELD(&D_00FBDA80, f32 *, 8) + D_00FBB7D8;
    sceVu0CopyVector(&M2C_FIELD(sp, f32 *, 0x10), &M2C_FIELD(sp, M2C_UNK *, 0x40));
    M2C_FIELD(sp, f32 *, 0x10) = -M2C_FIELD(sp, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0x14) = -M2C_FIELD(sp, f32 *, 0x14);
    M2C_FIELD(sp, f32 *, 0x18) = -M2C_FIELD(sp, f32 *, 0x18);
    sceVu0Normalize(&M2C_FIELD(sp, f32 *, 0x10), &M2C_FIELD(sp, f32 *, 0x10));
    sceVu0Normalize(sp, sp);
    sceVu0AddVector(sp, &M2C_FIELD(sp, f32 *, 0x10), sp);
    sceVu0Normalize(sp, sp);
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    func_001becb8(&M2C_FIELD(sp, M2C_UNK *, 0x20), sp, 1);
    func_001bf098(temp_s3, &M2C_FIELD(sp, M2C_UNK *, 0x20));
    func_00f68770(0x43, 0x7D0, temp_s3, 0, D_00F87048);
}

void func_00f2e390(s32 arg0) {
    s32 sp[24];    s32 temp_s3;

    temp_s3 = func_00f2cae8(arg0) + 0x20;
    sceVu0CopyMatrix(&M2C_FIELD(sp, M2C_UNK *, 0x20), temp_s3);
    sceVu0CopyVector(sp, &M2C_FIELD(sp, M2C_UNK *, 0x50));
    M2C_FIELD(sp, f32 *, 0x8) += 1e+02f;
    sceVu0CopyVector(&M2C_FIELD(sp, f32 *, 0x10), &D_00FBDA80);
    M2C_FIELD(sp, f32 *, 0x0) -= M2C_FIELD(&D_00FBDA80, f32 *, 0) + M2C_FIELD(&D_00FBB7F0, f32 *, 0);
    M2C_FIELD(sp, f32 *, 0x4) -= M2C_FIELD(&D_00FBDA80, f32 *, 4) + M2C_FIELD(&D_00FBB7F0, f32 *, 4);
    M2C_FIELD(sp, f32 *, 0x8) -= M2C_FIELD(&D_00FBDA80, f32 *, 8) + D_00FBB7D8;
    sceVu0CopyVector(&M2C_FIELD(sp, f32 *, 0x10), &M2C_FIELD(sp, M2C_UNK *, 0x40));
    M2C_FIELD(sp, f32 *, 0x10) = -M2C_FIELD(sp, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0x14) = -M2C_FIELD(sp, f32 *, 0x14);
    M2C_FIELD(sp, f32 *, 0x18) = -M2C_FIELD(sp, f32 *, 0x18);
    sceVu0Normalize(&M2C_FIELD(sp, f32 *, 0x10), &M2C_FIELD(sp, f32 *, 0x10));
    sceVu0Normalize(sp, sp);
    sceVu0AddVector(sp, &M2C_FIELD(sp, f32 *, 0x10), sp);
    sceVu0Normalize(sp, sp);
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    func_001becb8(&M2C_FIELD(sp, M2C_UNK *, 0x20), sp, 1);
    func_001bf098(temp_s3, &M2C_FIELD(sp, M2C_UNK *, 0x20));
    func_00f68770(0x46, 0x7D0, temp_s3, 0, D_00F87048);
}
