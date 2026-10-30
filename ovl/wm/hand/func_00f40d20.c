/* wm.x func_00f40d20: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x558]; s32 f558; u8 pad2[0x34]; } P40d20;
typedef struct { s32 x; u8 pad[0x54]; } S40d20;
void func_0011d140(s32, s32);
void func_001bfac8(void);
s32 func_001c0310(s32, void *);
s32 func_00f218d8(void);
void func_00f35970(void);
void func_00f3a4c8(void);
void func_00f3e3a0(void);
void func_00f3f2d0(f32);
void func_00f3f2f8(f32);
s32 func_00f3f320(s32);
void func_00f3f358(void);
void func_00f3f7c8(s32);
void func_00f3fd60(s32, s32, s32);
void func_00f3ff98(s32, s32, s32);
void func_00f46cb8(s32, s32);
void func_00f40ca8();
extern s32 D_00F850E0;
extern P40d20 *D_00F864C0;
extern P40d20 D_00F86500[];
extern S40d20 D_00F87EDC[];
extern s32 D_00F9B2B8;

void func_00f40d20(s32 arg0, s32 arg1, s32 arg2) {
    s32 other;
    s32 t;
    s32 i;

    other = D_00F850E0 ^ 1;
    func_00f3fd60(other, arg0, 0);
    for (i = 0; i < 30; i++) {
        func_00f3f2d0(-(f32)i / 30.0f + 1.0f);
        func_001bfac8();
    }
    D_00F9B2B8 = 2;
    func_00f3f2f8(1.0f);
    func_00f3a4c8();
    func_00f3e3a0();
    func_001bfac8();
    func_00f3f358();
    t = func_00f218d8();
    func_001c0310(-1, func_00f40ca8);
    func_00f3f7c8(D_00F87EDC[arg0].x);
    func_0011d140(func_00f3f320(D_00F864C0->f558), 0);
    func_00f3fd60(other, arg0, 1);
    while (func_00f218d8() < t + 61) {
        func_001bfac8();
    }
    func_00f3ff98(other, 0, arg2);
    D_00F9B2B8 = 3;
    D_00F850E0 = other;
    D_00F864C0 = &D_00F86500[other];
    func_00f3f2f8(1.0f);
    func_00f46cb8(64, 2);
    D_00F9B2B8 = 1;
    for (i = 0; i < 30; i++) {
        func_00f3f2d0((f32)i / 30.0f + 0.0f);
        func_001bfac8();
    }
    D_00F9B2B8 = 0;
    func_00f35970();
}
