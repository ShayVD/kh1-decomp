/* wm.x func_00f4a020: the twin of gb.x func_00f22f28 (tools/ovl/twins.py). */
#include "ovl.h"

extern s32 D_003773EC, D_00F9B518, D_00F9B50C, D_00F9B510, D_00F9B514, D_00FA5378, D_00F9B644, D_00F9B640, D_00F9B508, D_00FA5FB4;
extern s32 D_00F9B520, D_00F9B524, D_00F9B500;
extern u8 D_00F9B600[], D_00F9B580[], D_00F9B700[], D_00F9B680[];
void func_00112e98(void);
void func_001bade8(void);
void func_00f640e8(void);
void func_00f4e3e8(s32);
void func_00f47300(void);
void func_00f49df8(void);
void func_001bb858(void *, void *);
void func_001bb438(void);
s32 func_001bfec8(void);
s32 func_001bb500(s32, s32);
void func_001bfe50(s32);
void func_001bfc90(s32);
void func_00f47610(void);
void func_00f68170(void);
void func_00f66e98(void);
s32 func_00f49cf0(void);
void func_00f47428(void);
void func_0011ef10(s32, s32 (*)(void));
s32 func_001c00e8(s32, void (*)(void), kh1_u128);
void func_00f4a020(void) {
    if (D_003773EC) func_00112e98();
    D_003773EC = 0;
    func_001bade8();
    func_00f640e8();
    func_00f4e3e8(0);
    func_00f47300();
    D_00FA5378 = 0;
    D_00F9B644 = 0;
    D_00F9B640 = 0;
    D_00F9B508 = 0;
    D_00FA5FB4 = 0;
    D_00F9B518 = 0;
    D_00F9B50C = 1;
    D_00F9B510 = 0;
    D_00F9B514 = 0;
    func_00f49df8();
    D_00F9B520 = 0;
    D_00F9B524 = 0;
    D_00F9B500 = 1;
    func_001bb858(D_00F9B600, D_00F9B580);
    func_001bb858(D_00F9B700, D_00F9B680);
    func_001bb438();
    func_001bfe50(func_001bb500(func_001bfec8(), 16));
    func_001bfc90(1);
    func_00f47610();
    func_00f68170();
    func_00f66e98();
    func_0011ef10(0x1D4C1, func_00f49cf0);
    func_001c00e8(1, func_00f47428, KH1_Q(0));
}
