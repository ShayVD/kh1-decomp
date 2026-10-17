/* 001e32d8 hand (any non-gcse mode): 4w off. Only the lui temp regs at the top: orig lui v0=%hi(D_003F7A68), a2=%hi(D_003DC48C); ours swapped (they follow the pointer-decl order; decl order D,B,C,A is the only one giving the right s-regs s1=one s2=pB s3=pA s4=pC s5=pD). Key tricks: common tail duplicated in every branch (crossjump merges it), 'b = a' copy defeats fold_range_test on a==-2||b==-3||a==-4. */
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
    s32 *pD = &D_003DC48C;
    s32 *pB = &D_003DC478;
    s32 *pC = &D_003DC480;
    s32 *pA = &D_003F7A68;
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
