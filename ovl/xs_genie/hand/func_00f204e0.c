/* xs_genie.x func_00f204e0: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)(void));
s32 func_00123488(s32);
void func_0012cab8(void (*)(void));
s32 func_00130340(s32, s32, f32);
void func_00131500(s32);
void func_001763f0(s32);
void func_00241c00(void *, s32, void *, s32, s32);
void func_00f200a0(s32);
void func_00f20b70(void);
void func_00f214f8(void);
void func_00f21a20(void);
void func_00f22258(void);
void func_00f22ac0(void);
void func_00f20308(void);
void func_00f20480(void);
extern s32 D_002E26A0;
extern s32 D_00304B7C;
extern s32 D_00304B80;
extern s32 D_00F22E90;
extern s32 D_00F22E94;
extern s32 D_00F22E98;
extern s32 D_00FC0F00;
extern s32 D_00FC0F04;
void func_00f204e0(void) {
    func_001763f0(D_00F22E98);
    D_00F22E90 = D_002E26A0;
    func_00131500(D_002E26A0);
    func_00130340(D_00F22E90, 0x40000000, 0.0f);
    D_00F22E94 = func_00123488(0x70002);
    func_00f20b70();
    func_00241c00(&D_00304B7C, 0, &D_00304B80, 0, D_00F22E94);
    func_0012cab8(func_00f20480);
    D_00FC0F04 = 0;
    D_00FC0F00 = 1;
    func_00f200a0(0);
    func_00f21a20();
    func_00f214f8();
    func_00f22258();
    func_00f22ac0();
    func_0011ef10(0xCB20, func_00f20308);
}
