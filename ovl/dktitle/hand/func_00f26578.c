/* dktitle.x func_00f26578: matched by hand. */
#include "ovl.h"

s32 func_001f40c8(void);
void func_0020bc48(s32, s32, s32);
void func_001f82b0(void);
void func_0020b998(void);
void func_0020be10(s32);
void func_001efaf0(void);
void func_00109268(void);
typedef struct { void (*f0)(void); void (*f1)(void); } Ops;
extern Ops *D_00F26E4C;
extern s32 D_00F26E34, D_00F2C894, D_00F2C8B0, D_00F2C8EC, D_00F2C8F0, D_00F2C8F4;
s32 func_00f26578(void) {
    if (func_001f40c8() != 0) {
        func_0020bc48(D_00F2C8F4, D_00F2C8EC, D_00F2C8F0);
        func_001f82b0();
        func_0020b998();
        return 0;
    }
    if (D_00F2C894 < 0) return 0;
    func_0020be10(16);
    if (D_00F26E4C != 0) {
        D_00F26E4C->f1();
        D_00F26E4C = 0;
        D_00F2C8B0 = 0;
    }
    D_00F26E34 = 0;
    func_001efaf0();
    func_00109268();
    return 4;
}
