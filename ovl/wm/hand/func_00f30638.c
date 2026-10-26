/* wm.x func_00f30638: matched by hand. */
#include "ovl.h"

void func_00f2c7e8(f32);
void func_00f2c1b8(void);
void func_00f2cba8(void);
void func_00f30628(void);
void func_00f2ee10(void);
void func_00f2c330(void);
void func_00f2c3f8(void);
extern f32 D_00F8526C;
extern s32 D_00F8C124;
extern f32 D_00F8C150;
extern s32 D_00F8C1EC;
extern s32 D_00F8C1F0;
extern s32 D_00F8C1F4;
extern s32 D_00F8C1FC;
extern s32 D_00F8C23C;
extern OvlMtx D_00F8C290;
extern s32 D_00F8C2D0;
extern s32 D_00F8C2D4;
extern s32 D_00F8C2D8;
extern s32 D_00F8C2DC;
extern s32 D_00FBB5A8;
extern s32 D_00FBB5AC;
extern s32 D_00FBB5B0;
extern s32 D_00FBB5B4;
extern s32 D_00FBB5B8;
extern s32 D_00FBB5BC;
extern s32 D_00FBB5C0;
extern s32 D_00FBB5C4;
extern s32 D_00FBB5C8;
extern s32 D_00FBB800;
extern s32 D_00FBB850[];
extern s32 D_00FCC3C0;

void func_00f30638(s32 arg0) {
    s32 i;
    if (arg0 == 0) {
        D_00FBB5BC = 0;
        D_00FBB5AC = 0;
        D_00FBB5B0 = 0;
        D_00FBB5B4 = 0;
        D_00FBB5B8 = 0;
        D_00FBB5A8 = 0;
        D_00FBB800 = 0;
    }
    D_00F8C2D0 = -1;
    D_00F8C2D4 = -1;
    D_00F8C2D8 = -1;
    D_00F8C2DC = -1;
    func_00f2c7e8(1.0f);
    D_00FBB5C8 = 0;
    D_00FBB5C0 = 0;
    D_00FBB5C4 = 0;
    D_00F8C23C = 0;
    D_00FCC3C0 = -1;
    D_00F8C124 = -10;
    if (arg0 == 0) {
        func_00f2c1b8();
    }
    D_00F8C1FC = 0;
    D_00F8C1F4 = 0;
    D_00F8C1F0 = 0;
    D_00F8C1EC = 0;
    D_00F8C150 = D_00F8526C / 200.0f;
    func_00f2cba8();
    func_00f30628();
    func_00f2ee10();
    for (i = 127; i >= 0; i--) {
        D_00FBB850[i] = 0;
    }
    PlatVu0UnitMatrix(D_00F8C290);
    if (arg0 == 0) {
        func_00f2c330();
    } else {
        func_00f2c3f8();
    }
}
