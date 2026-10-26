/* dktitle.x func_00f23de8: matched by hand. */
#include "ovl.h"

s32 func_001f9020(void);
void func_001f9010(s32);
void func_001efb18(s32, s32);
s32 func_001f00d0(s32);
s32 func_001f9438(void *, s32, s32, s32, s32, s32, s32);
void func_001fbcd8(void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_001fade0(void *, s32, s32, s32, s32, s32);
void func_001f3840(void *);
void func_00206130(void *o, s32 px, s32 py, s32 pw, s32 ph, s32 col);
void func_00f23858(void *, s32, s32, s32);
void func_00f23990(void *, s32, s32);
s32 func_00f23aa8(void *, s32, s32);
void func_00f23d28(void *, s32, s32, s32, s32);
s32 func_00f25500(void);
void func_00f268d8(void);
extern s32 D_003E8E08[8];
extern u32 D_00F26E38;
extern u32 D_00F26E3C;
extern s32 D_00F26E64;
extern s32 D_00F26E68;
extern s32 D_00F26E6C;
extern s32 D_00F2C894;
extern s32 D_00F2C89C;
extern s32 D_00F2C8A8;
extern s32 D_00F2C8AC;
extern s32 D_00F2C8B4;
extern s32 D_00F2C8D4;

void func_00f23de8(u8 *o) {
    s32 font = func_001f9020();
    s32 col, save;

    func_001f9010(30);
    func_001efb18(D_00F2C8A8, D_00F2C8AC);
    switch (D_00F2C89C) {
    case 0:
        func_00f23990(o, 0, 0);
        break;
    case 1:
        func_00f23990(o, 0, 0);
        func_001f9438(o, 0, 272 - func_001f00d0(2) / 2, 144, 2, 15, 0x80FFFFFF);
        func_00f23858(o, D_00F26E64, 160, 216);
        if (D_00F26E6C) {
            func_00206130(o, 0, 0, 512, 384, D_00F26E6C << 24);
        }
        break;
    case 2:
        func_00f23d28(o, 6, 0, 1, 1);
        break;
    case 3:
        func_00206130(o, 0, 0, 512, 384, 0x80000000);
        col = func_00f23aa8(o, 0, D_00F26E6C) | 0x80000000;
        func_001f9438(o, 0, 302 - func_001f00d0(7) / 2, 141, 7, 15, 0x40A7F4FF);
        func_001fbcd8(o, 1, 20, 0, 472, 346, (s64)((u64)D_00F26E3C * 100) / D_00F26E38, 0, col);
        func_001fade0(o, 480, 348, 42, 16, col);
        break;
    case 4:
        func_00f23d28(o, 12, 0, 0, 0);
        func_00f23858(o, D_00F26E68, 160, 216);
        break;
    case 5:
        func_00f23d28(o, 13, 0, 0, 1);
        func_00f23858(o, D_00F26E68, 160, 216);
        break;
    case 6:
        func_00206130(o, 0, 0, 512, 384, 0x80000000);
        func_00f23aa8(o, 0, D_00F26E6C);
        func_00f23d28(o, 10, 1, 1, 1);
        break;
    case 7:
        func_00f23d28(o, 9, 0, 1, 1);
        break;
    case 8:
        func_00206130(o, 0, 0, 512, 384, 0x80000000);
        func_00f23aa8(o, 0, D_00F26E6C);
        save = *(s32 *)(o + 0x90);
        func_00f23990(o, 2, 0);
        func_001f9438(o, 2, 256, 183, 5, 15, 0x80FFFFFF);
        *(s32 *)(o + 0x90) = save;
        break;
    case 9:
        D_003E8E08[0] = func_00f25500() + 128;
        func_00f23d28(o, 11, 0, 1, 1);
        break;
    }
    func_001f9010(font);
    if (D_00F2C894 >= 0) {
        func_001f3840(o);
    }
    if (D_00F2C8B4 && D_00F2C8D4) {
        func_00f268d8();
    }
}
