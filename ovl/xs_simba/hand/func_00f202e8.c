/* xs_simba.x func_00f202e8: matched by hand. */
#include "ovl.h"

void func_00242bc0(void);
void func_00f20270(void);
void func_00f20188(void);
s32 func_00130340(s32, s32, f32);
s32 func_00130578(s32, s32, f32);
void func_00f201d8(void);
void func_0014f658(s32, s32);
void func_00157a30(s32, s32, s32);
void func_0012cab8(s32);
void func_001247e8(s32);
void func_00f202b8(void);
void func_00f20ad8(void);
void func_00f21818(s32);
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern s32 D_00F21C34;
extern s32 D_00F21C38;
extern s32 D_00FA6A94;
void func_00f202e8(s32 arg0) {
    if (D_00FA6A94 != 0) {
        func_00242bc0();
        D_00FA6A94 = 0;
    }
    switch (arg0) {
    case 1:
        func_00f201d8();
        func_00130340(D_00F21C38, 200, 8.0f);
        func_00130578(D_00F21C38, 201, 0.0f);
        func_0014f658(D_00F21C34, 38);
        func_00157a30(D_00F21C34, 15, 0);
        break;
    case 2:
        func_00f20270();
        func_00f20188();
        arg0 = 0;
        func_00130340(D_00F21C38, 0x010000CA, 0.0f);
        func_00130578(D_00F21C38, 0x40000000, 0.0f);
        break;
    case 3:
        func_00f202b8();
        func_00f20ad8();
        D_00304B7C -= D_00304B70[2] * 100.0f;
        break;
    case 100:
        func_0012cab8(0);
        break;
    case 101:
        func_001247e8(D_00F21C38);
        break;
    }
    func_00f21818(arg0);
}
