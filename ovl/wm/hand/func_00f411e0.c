/* wm.x func_00f411e0: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; } Q411e0;
extern s32 D_00F9B2B8;
extern s32 D_002BBE04;
extern Q411e0 D_002BC080;
extern s32 D_002BC090;
extern s32 D_002BC094;
extern f32 D_002BC098;
extern s32 D_002BC09C;
extern s32 D_002BC0A0;
extern s32 D_002BC0A4;
void func_00114820(void);
void func_00f309d0(s32);
void func_0011d140(s32, s32);
void func_001c01b0(s32, void (*)(), ...);
void func_00f40fc8();

void func_00f411e0(s32 arg0, s32 arg1, s32 arg2) {
    s32 *flag = &D_00F9B2B8;
    if (*flag != 0) {
        return;
    }
    func_00114820();
    func_00f309d0(1);
    func_0011d140(0xE2F0, 0);
    D_002BBE04 = 4;
    D_002BC080.x0 = 128;
    D_002BC080.x4 = 128;
    D_002BC080.x8 = 128;
    D_002BC080.xc = 112;
    D_002BC090 = 256;
    D_002BC094 = 192;
    D_002BC098 = 0.04f;
    D_002BC09C = 16;
    D_002BC0A0 = 0;
    D_002BC0A4 = 0;
    *flag = 1;
    func_001c01b0(-1, func_00f40fc8, arg0, arg1, arg2);
}
