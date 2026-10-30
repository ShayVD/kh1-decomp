/* wm.x func_00f31118: matched by hand (session 141, wwm1 round 17): a CONTEXT_ONLY func_00f2bfb8 above it. A call to a function defined earlier in the file is nothrow, which changes reorg's branch-likely choice (docs/overlays.md, "Branch-likely vs plain branch"). */
#include "ovl.h"
extern s32 D_00F8C23C;
extern s32 D_00FBB828;
extern s32 D_00F9B2EC;
extern s32 D_00F850A0;
extern s32 D_00F8C12C;
extern s32 D_00FBBA60;
extern s32 D_00F8C280;
extern s32 D_00F8C130;
extern s32 D_00FBBA50;
extern s32 D_00FBB5BC;
extern u8 D_00F8C0F0[];
extern u8 D_00F8C0B0[];
extern u8 D_00F8C070[];
s32 func_002193f0(void);
s32 func_00f41448(void);
s32 func_00f40c98(void);
void func_00f2ff70(void);
void func_00176ba8(void *, s32);
void func_00f302e8(s32, s32, s32);
void func_0017f580(s32, f32, f32, f32, f32);
s32 func_00f2bfb8(void);
CONTEXT_ONLY s32 func_00f2bfb8() { return 0; }
void func_00114820(void);
void func_00f30d48(void);
void func_001c0310(s32, void (*)(void));

static inline s32 getm(void) {
    s32 m;
    switch (func_002193f0()) {
    case 0:
        m = 1;
        break;
    default:
    case 1:
        m = 2;
        break;
    case 2:
        m = 4;
        break;
    }
    return m;
}

s32 func_00f31118(s32 a0, s32 a1, s32 a2) {
    s32 m;

    m = getm();
    if (D_00F8C23C != 0) return 0;
    if (func_00f41448() != 0 || func_00f40c98() != 0 || D_00FBB828 != 0
        || (D_00F9B2EC != 0 && D_00F850A0 == 0)) return 0;
    D_00FBB828 = 30;
    if (D_00F8C12C == 0) {
        if (D_00FBBA60 > 0 && ((D_00F8C280 == 1 && D_00F8C130 == 1) || D_00F8C280 == 2)) {
            if (--D_00FBBA60 >= 0) {
                func_00f2ff70();
                return 1;
            }
        } else if (a0 != 0) {
            switch (a0) {
            case 1:
                D_00FBBA50 -= m;
                func_00176ba8(D_00F8C0F0, 0);
                D_00FBB5BC += m;
                break;
            case 2:
                m *= 2;
                D_00FBBA50 -= m;
                func_00176ba8(D_00F8C0B0, 0);
                D_00FBB5BC += m;
                break;
            case 3:
                m *= 4;
                D_00FBBA50 -= m;
                func_00176ba8(D_00F8C070, 0);
                D_00FBB5BC += m;
                break;
            }
            if (a0 != 0) {
                if (a1 == 0) func_00f302e8(a2, a0, 0);
                func_0017f580(1, 30.0f, 5.0f, a0 * 4, a0 * 4);
            }
            if (D_00FBBA50 > 0 || func_00f2bfb8() != 0 || D_00F8C23C != 0) return 1;
            D_00F8C23C = 1;
            if (D_00F850A0 == 0) {
                func_00114820();
                D_00FBBA50 = 0;
                func_001c0310(-1, func_00f30d48);
                return 1;
            }
        }
    } else if (a0 != 0) {
        if (D_00F8C280 != 0) {
            func_00f2ff70();
        } else if (a1 == 0) {
            func_00f302e8(a2, a0, 0);
        }
        func_0017f580(1, 30.0f, 5.0f, a0 * 4, a0 * 4);
    }
    return 1;
}
