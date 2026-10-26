/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern M2C_UNK D_00304B7C;
extern M2C_UNK D_00304B80;
extern M2C_UNK func_00f20570;
extern M2C_UNK func_00f20770;
extern M2C_UNK func_00f212c8;
extern M2C_UNK func_00f21978;
extern f32 D_00F23210;
extern s32 D_00F23204;
extern s32 D_00F2320C;
extern s32 D_00F23214;
extern s32 D_00F3CA80;
extern void *D_002E26A0;
extern void *D_00F23200;
s32 func_0011ef10(s32, s32);
s32 func_00123488(s32);
void func_0012cab8(s32);
void func_00241c00(s32, s32, s32, s32, s32);
void func_00f200b0(s32, f32);
void func_00f20150(s32);
void func_00f209b8(void);
void func_00f21070(s32);
void func_00f21128(void);
void func_00f217e8(s32, s32);

void func_00f20790(void) {
    s32 sp[8];
    D_00F23200 = D_002E26A0;
    D_00F23204 = func_00123488(0x70000);
    func_00f21070(D_00F23200);
    func_00f209b8();
    func_00f200b0(0x40000000, 0);
    func_00241c00(&D_00304B7C, 0, &D_00304B80, 0, D_00F23204);
    D_00F23210 = 0.0f;
    D_00F2320C = 0;
    func_00f20150(0);
    func_0012cab8(&func_00f20770);
    D_00F3CA80 = 1;
    func_0011ef10(0xC350, &func_00f20570);
    M2C_FIELD(sp, f32 *, 0x0) = M2C_FIELD(D_00F23200, f32 *, 0x10);
    M2C_FIELD(sp, f32 *, 0x4) = M2C_FIELD(D_00F23200, f32 *, 0x14) - (M2C_FIELD(D_00F23200, f32 *, 0x414) * 0.5f);
    M2C_FIELD(sp, f32 *, 0x8) = M2C_FIELD(D_00F23200, f32 *, 0x18);
    M2C_FIELD(sp, f32 *, 0xC) = 1.0f;
    M2C_FIELD(sp, f32 *, 0x10) = M2C_FIELD(D_00F23200, f32 *, 0x30);
    M2C_FIELD(sp, f32 *, 0x14) = M2C_FIELD(D_00F23200, f32 *, 0x34);
    M2C_FIELD(sp, f32 *, 0x18) = M2C_FIELD(D_00F23200, f32 *, 0x38);
    M2C_FIELD(sp, f32 *, 0x1C) = 1.0f;
    D_00F23214 = 0;
    func_00f217e8(sp, &M2C_FIELD(sp, f32 *, 0x10));
    func_00f21128();
    func_0011ef10(0x270FF, &func_00f21978);
    func_0011ef10(0x270FF, &func_00f212c8);
}
