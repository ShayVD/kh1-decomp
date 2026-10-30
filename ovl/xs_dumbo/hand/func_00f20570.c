/* xs_dumbo.x func_00f20570: matched by hand. */
#include "ovl.h"

/* xs_dumbo state task (cases 0-3, 100, 101, then the effect update). The zero locals set after the early return and used only in the closing block are the match: gcse's constant propagation folds them away, but they add three insns to its count, which moves the expression hash table from 53 to 55 buckets, so %hi(D_00F2320C) is visited before %hi(D_00F23214), gets the lower pseudo and takes s1 as in the original (wwm2 round 55). */
s32 func_0013aa60(void);
void func_00f20150(s32);
void func_00f203c8(void);
void func_00f20408(void);
CONTEXT_ONLY void func_00f20408() {}
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
    s32 ret;
    s32 clr;
    void *none;

    if (D_002C5960 & 1)
        return 0;
    ret = 0;
    clr = 0;
    none = 0;
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
    if (D_00F2320C != none)
        func_0014a0f0(D_00F2320C);
    D_00F23214 = clr;
    return ret;
}
