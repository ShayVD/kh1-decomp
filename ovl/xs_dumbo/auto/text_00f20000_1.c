/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

M2C_UNK sceVu0AddVector(s32, s32, M2C_UNK *);
M2C_UNK sceVu0CopyVector(void *);
M2C_UNK sceVu0ScaleVectorXYZ(M2C_UNK *, void *, f32);
extern M2C_UNK D_00F2BB20;
extern f32 D_002BBDFC;
extern f32 D_00304B7C;
extern f32 D_00F23210;
extern f32 D_00F3CA84;
extern s32 D_00F23200;
extern s32 D_00F23214;
extern void *D_00304B70;
void func_00157a30(s32, s32, s32);
void func_00f200b0(s32, f32);
void func_00f20100(s32, f32);
void func_00f20150(s32);

void func_00f203c8(void) {
    func_00f200b0(0xC8, 4.0f);
    func_00f20150(1);
    func_00157a30(D_00F23200, 0x11, 0);
}

void func_00f20478(void) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f1;

    temp_f0 = D_00F3CA84 - D_002BBDFC;
    D_00F3CA84 = temp_f0;
    temp_f1 = D_00304B7C - ((f32) M2C_FIELD(D_00304B70, u8 *, 2) * D_002BBDFC);
    D_00304B7C = temp_f1;
    if ((temp_f0 > 0.0f) || ((temp_f1 > 0.0f) && (D_00F23214 != 0))) {
        temp_f0_2 = D_00F23210 + (D_002BBDFC * 0.05f);
        D_00F23210 = temp_f0_2;
        if (temp_f0_2 > 1.0f) {
            D_00F23210 = 1.0f;
            return;
        }
        return;
    }
    func_00f200b0(0xCA, 0.0f);
    func_00f20100(0, 0.0f);
    func_00f20150(3);
}

void func_00f213f8(s32 arg0, f32 fparg0) {
    s32 sp[8];
    sceVu0CopyVector(sp);
    M2C_FIELD(sp, s32 *, 0xC) = 0;
    sceVu0ScaleVectorXYZ(&M2C_FIELD(sp, M2C_UNK *, 0x10), sp, fparg0);
    sceVu0AddVector(arg0, arg0, &M2C_FIELD(sp, M2C_UNK *, 0x10));
}

void func_00f21970(void) {

}

void func_00f22e68(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0xA;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_00F2BB20;
    M2C_FIELD(arg0, void **, 8) = (void *) ((s8 *)&D_00F2BB20 + 0x280);
}
