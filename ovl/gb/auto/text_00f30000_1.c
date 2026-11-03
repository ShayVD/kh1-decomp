/* Matched automatically from m2c output (tools/autodecomp.py); not yet
 * cleaned up. Offsets in M2C_FIELD are struct fields still to be named. */
#include "m2c.h"

extern s32 D_00F61F5C;
extern s32 D_00F809C4;
extern s32 D_00F809C8;
s32 func_00f3c178(s8 *);
void func_001c0078(s32);
void func_001c0688(M2C_UNK);
void func_00f28c70();
void func_00f33c70(M2C_UNK);
void func_00f410b8();

void func_00f357b0(void) {
    func_001c0688(1);
    if (D_00F809C4 != 0) {
        func_001c0078(D_00F809C8);
    }
    func_001c0688(2);
    D_00F809C4 = 0;
    func_00f28c70();
    func_00f410b8();
    func_00f33c70(-1);
}

s32 func_00f3c1b0(s8 *arg0) {
    return func_00f3c178(arg0) * D_00F61F5C;
}
