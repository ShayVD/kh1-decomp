/* score 49 (508 vs 512). xs_dumbo state task (cases 0-3, 100, 101, then the effect update). Logic complete. Left: %hi(D_00F2320C) and %hi(D_00F23214) take s2/s1 the other way round from the original, and case 1's branch has one instruction less. Round 29 wwm2: extern/decl order, a struct of the four globals (106), default: cases, case order, temps for the effect pointer, inverted case 0 and every flag mode do not fix it. */
#include "ovl.h"
s32 func_0013aa60(void);
void func_00f20150(s32);
void func_00f203c8(void);
void func_00f20408(void);
void func_00f20478(void);
void func_0014aab0(void *);
s32 func_00147be0(void *);
void func_0014a0f0(void *);
extern s32 D_002C5960;
extern f32 D_002BBDFC;
extern u8 *D_00304B70;
extern f32 D_00304B7C;
extern s32 D_00F3C9D8;
extern s32 D_00F3CA80;
extern void *D_00F23208;
extern void *D_00F2320C;
extern f32 D_00F23210;
extern s32 D_00F23214;
s32 func_00f20570(void) {
    if (D_002C5960 & 1)
        return 0;
    D_00304B7C -= D_00304B70[1] * D_002BBDFC;
    switch (D_00F3C9D8) {
    case 0:
        if (func_0013aa60())
            func_00f20150(100);
        else if (D_00F23214)
            func_00f203c8();
        break;
    case 1:
        func_00f20408();
        break;
    case 2:
        func_00f20478();
        break;
    case 3:
        D_00F23210 -= D_002BBDFC * 0.05f;
        if (D_00F23210 < 0.0f) {
            D_00F23210 = 0.0f;
            func_0014aab0(D_00F2320C);
            D_00F2320C = 0;
            func_00f20150(0);
        }
        break;
    case 100:
        if (!func_00147be0(D_00F23208))
            func_00f20150(101);
        break;
    case 101:
        D_00F3CA80 = 0;
        return 4;
    }
    if (D_00F2320C)
        func_0014a0f0(D_00F2320C);
    D_00F23214 = 0;
    return 0;
}
