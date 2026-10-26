/* xs_simba.x func_00f20878: matched by hand. */
#include "ovl.h"

s32 func_0011ef10(s32, void (*)(void));
s32 func_00123488(s32);
void func_0012cab8(void (*)(void));
s32 func_00130340(s32, s32, f32);
void func_00131500(s32);
void func_001763f0(s32);
void func_00241c00(void *, void *, void *, void *, s32);
void func_00f202e8(s32);
void func_00f20fd0(void);
void func_00f21768(void);
void func_00f20490(void);
void func_00f20530(void);
void func_00f20618(void);
extern s32 D_002E26A0;
extern void (*D_002E27D4)(void);
extern f32 D_00304B7C;
extern f32 D_00304B80;
extern s32 D_00F21C34;
extern s32 D_00F21C38;
extern s32 D_00F21C3C;
extern s32 D_00F21C44;
extern f32 D_00F21C48;
extern f32 D_00F21C4C;
extern s32 D_00FA6A80;
extern s32 D_00FA6A94;
void func_00f20878(void) {
    func_001763f0(D_00F21C44);
    D_00F21C34 = D_002E26A0;
    func_00131500(D_002E26A0);
    func_00130340(D_00F21C34, 0x40000000, 0.0f);
    func_00f20fd0();
    D_00F21C38 = func_00123488(0x70005);
    func_00f21768();
    D_00F21C48 = 0.0f;
    D_00F21C4C = (D_00304B80 < 30000.0f) ? D_00304B80 : 30000.0f;
    func_00241c00(&D_00304B7C, &D_00F21C48, &D_00304B80, &D_00F21C4C, D_00F21C38);
    D_00F21C3C = 0;
    D_00FA6A94 = 0;
    D_002E27D4 = func_00f20530;
    func_0012cab8(func_00f20490);
    D_00FA6A80 = 1;
    func_00f202e8(0);
    func_0011ef10(0xCB20, func_00f20618);
}
