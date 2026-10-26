/* dkmovie.x func_00f208b8: matched by hand. */
#include "ovl.h"

M2C_UNK func_001ed8c8(M2C_UNK);                     /* extern */
M2C_UNK func_001ed9e0();                            /* extern */
extern M2C_UNK D_0003DEDC;
extern M2C_UNK D_0003DEE0;
extern M2C_UNK D_0003DEE4;
extern M2C_UNK D_0003DF44;
extern M2C_UNK D_0003DF58;
extern s16 D_00F28610;
extern s32 D_00F28644;

void func_00f208b8(s32 arg0) {
    D_00F28644 = 0;
    if (D_00F28610 != 0) {
        *(M2C_UNK *)((s8 *)&D_0003DEE4 + arg0) = -1;
        *(M2C_UNK *)((s8 *)&D_0003DEE0 + arg0) = 0;
        *(M2C_UNK *)((s8 *)&D_0003DEDC + arg0) = 0;
        *(u8 *)((s8 *)&D_0003DF58 + arg0) = 0;
        *(M2C_UNK *)((s8 *)&D_0003DF44 + arg0) = 2;
        func_001ed9e0();
        func_001ed8c8(-1);
        D_00F28610 = 0;
    }
}
