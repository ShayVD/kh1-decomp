/* 001e32d8 2w (hand): pointer decls A,B,C,D, inits in order pA, pD, pC, pB (s6 draft 4w). s-regs all right; left: lui temps hi(B)=a2/hi(D)=v1 swapped (local-alloc takes the hi pseudos in init order with equal lifetimes). Init order A,B,C,D fixes the luis but pD/pC s4/s5 swap (global prio pD .0759 vs pC .0750: pD needs 5 more live insns or pC 1 fewer). 576 decl x init orders and 3 b/one placements tried. */
#include "common.h"
typedef struct { u8 pad[0x44]; f32 f44; } Win;
extern s32 D_003F7A68;
extern s32 D_003DC478;
extern s32 D_003DC47C;
extern s32 D_003DC480;
extern s32 D_003DC48C;
extern s32 D_003DC490;
extern s32 D_003DC494;
extern u8 D_0062F760[];
extern Win D_0062F790;
extern char D_003DC2A8[];
extern char D_003DC2F8[];
extern char D_003DC370[];
typedef struct { s32 f0; s32 f4; s32 f8; } S26A0;
extern S26A0 D_002E26A0;
void func_0010bdd0(Win *, void *);
void func_0010ef70(void *, char *, void *);
void func_0010e3f0(void *);
void func_0011d768(s32);
s32 func_001e2800(s32);
void func_0011ef10(s32, void *);
void func_001e30f8();
void func_001e2810();
void func_001e2920();
void func_001e2d08();
void func_001e32d8(s32 a) {
    s32 v;
    s32 b = a;
    s32 one = 1;
    s32 *pA;
    s32 *pB;
    s32 *pC;
    s32 *pD;
    pA = &D_003F7A68;
    pD = &D_003DC48C;
    pC = &D_003DC480;
    pB = &D_003DC478;
    *pA = 0;
    *pB = 0;
    *pC = a;
    *pD = one;
    func_0011d768(2);
    if (D_003DC494) {
        if (a == -1) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2A8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else if (a == -2) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else if (a == -3) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else if (a == -4) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2F8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
        } else {
            D_0062F790.f44 = 1.5f;
            D_003DC490 = 0;
            func_0010bdd0(&D_0062F790, func_001e30f8);
            return;
        }
    } else if (a == -1) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC2A8, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
    } else if (a == -2 || b == -3 || a == -4) {
        func_0011d768(4);
        func_0010e3f0(D_0062F760);
        func_0010ef70(D_0062F760 - 128, D_003DC370, func_001e2810);
        *pB = one; D_003DC47C = 60; func_0011ef10(0xc350, func_001e2920); *pA = one; *pD = 0;
    } else {
        goto deflt;
    }
    return;
deflt:
    v = func_001e2800(*pC);
    D_0062F790.f44 = 1.5f;
    if (v) D_0062F790.f44 = 2.0f;
    if (D_002E26A0.f4 && v) D_0062F790.f44 = 3.0f;
    if (D_002E26A0.f8 && v) D_0062F790.f44 = 4.0f;
    D_003DC490 = 0;
    func_0010bdd0(&D_0062F790, func_001e2d08);
}
