/* xs_genie.x func_00f200a0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xCC]; f32 fCC; } Sub;
typedef struct { u8 pad[0x6C]; Sub *f6C; s32 f70; } Pl;
void func_001224c8(s32, void *, void (*)(), f32);
s32 func_001226f0(s32, s32, s32);
void func_001247e8(s32);
void func_0012cab8(s32);
s32 func_00130340(Pl *, s32, f32);
s32 func_00130578(Pl *, s32, f32);
void func_0013aac0(Pl *);
void func_0014cce0(Pl *, f32);
void func_00f20c68(void *);
void func_00f20f58(void);
void func_00f21878(void);
void func_00f22b00(s32);
void func_00122768();
extern s32 D_002C5C60;
extern s32 D_002E31B0;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern s32 D_00F22E80;
extern Pl *D_00F22E90;
extern s32 D_00F22E94;
extern s32 D_00FC0D90;
extern s32 D_00FC0E48;
extern s32 D_00FC0F04;
void func_00f200a0(s32 arg0) {
    if (D_00FC0E48 == 2 && D_00FC0F04 != 0) {
        func_001224c8(D_00FC0F04, &D_002C5C60, func_00122768, 30.0f);
        D_00FC0F04 = 0;
    }
    switch (arg0) {
    case 2:
        func_0013aac0(D_00F22E90);
        switch (D_00F22E90->f70) {
        case 2:
            func_0014cce0(D_00F22E90, 20.0f);
            func_00130340(D_00F22E90, 0x010000C9, 0.0f);
            func_00130578(D_00F22E90, 0x40100006, 8.0f);
            break;
        case 8:
            func_00130340(D_00F22E90, 0x010000C9, 0.0f);
            func_00130578(D_00F22E90, 0x40100075, 8.0f);
            D_00F22E90->f6C->fCC = 0.196349550784f;
            break;
        default:
            func_00130340(D_00F22E90, 0x010000C8, 0.0f);
            func_00130578(D_00F22E90, 0x40100000, 0.0f);
            break;
        }
        D_00FC0D90 = 0;
        D_00FC0F04 = func_001226f0(1, 9, 0);
        func_001224c8(D_00FC0F04, &D_00F22E80, 0, 30.0f);
        D_00304B7C -= D_00304B70[2] * 100.0f;
        break;
    case 1:
        func_00f20f58();
        func_00f20c68(&D_002E31B0);
        break;
    case 100:
        func_00f21878();
        func_0012cab8(0);
        break;
    case 101:
        func_00f21878();
        func_001247e8(D_00F22E94);
        break;
    }
    func_00f22b00(arg0);
}
