/* wm.x func_00f43ae0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x558]; s32 x558; } P43ae0;
typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; f32 f; s32 g; } S43ae0;
void func_001ba708(s32);
void func_00f3f2d0(f32);
void func_00f3f2f8(f32);
void func_00f3b490(void);
void func_001bb480(void);
void func_00f204d8(void);
s32 func_001c00e8(s32, void *, kh1_u128);
s32 func_001bff70(s32);
void func_001bfac8(void);
s32 func_00f3f320(s32);
void func_0011d140(s32, s32);
void func_001ed170(s32);
void func_001c0310(s32, void *);
void func_00f3b418(void);
void func_00f43430(void);
void func_00f436d0(void);
void func_00f43ac0(void);
extern s32 D_010807E0, D_00F850A4, D_010807F0, D_002C5958;
extern s32 D_00F9B1C0, D_00F9B2EC, D_010807E4, D_00F9B1E4, D_00F9B2B8, D_00F85098, D_00F850A0, D_00F850A8, D_00F850F4, D_00F85094, D_00F9B2C0, D_00F9B2F0;
extern s32 D_00F850E0, D_002B6774, D_00F850AC;
extern P43ae0 *D_00F864C0;
extern P43ae0 D_00F86500;
extern S43ae0 D_00454A20;

void func_00f43ae0(void) {
    s32 h;
    S43ae0 tmp;

    D_010807E0 = 0;
    D_00F850A4 = 0;
    D_010807F0 = 0;
    func_001ba708(0);
    D_002C5958 &= ~8;
    D_00F9B2EC = 0;
    D_00F9B2F0 = 0;
    D_00F9B1C0 = -1;
    D_010807E4 = 0;
    D_00F9B1E4 = 0;
    D_00F9B2B8 = 0;
    D_00F85098 = 0;
    D_00F850A0 = 0;
    D_00F850A8 = 0;
    D_00F850F4 = 0;
    D_00F85094 = 0;
    D_00F9B2C0 = 0;
    func_00f3f2d0(1.0f);
    func_00f3f2f8(1.0f);
    func_00f3b490();
    D_00F850E0 = 0;
    D_00F864C0 = &D_00F86500;
    func_001bb480();
    func_00f204d8();
    h = func_001c00e8(-1, func_00f436d0, 0);
    while (func_001bff70(h)) {
        func_001bfac8();
    }
    while (D_002B6774) {
        func_001bfac8();
    }
    if (D_00F864C0 != NULL && D_00F864C0->x558 >= 0) {
        func_0011d140(func_00f3f320(D_00F864C0->x558), 0);
    }
    func_001ed170(50);
    func_001c0310(-1, func_00f43ac0);
    D_00F850AC = 1;
    D_00454A20.a = 22;
    D_00454A20.c = 22;
    D_00454A20.b = 8;
    D_00454A20.d = 8;
    D_00454A20.f = 1.0f;
    D_00454A20.g = 5;
    D_00454A20.e = 3;
    func_00f3b418();
    func_00f43430();
}
