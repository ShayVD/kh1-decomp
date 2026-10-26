/* wm.x func_00f2c1d8: matched by hand. */
#include "ovl.h"

s32 func_001ba3d8(void);
void func_001ba358(s32, s32);
s32 func_00232cc0(s32);
extern s32 D_00009B38;
extern s32 D_00009B3C;
extern s32 D_00FBDBB8[];
extern u32 D_00FBDFB8[];

void func_00f2c1d8(void) {
    s32 i;
    s32 neg, pos;
    s32 off;
    for (i = 0; i < func_001ba3d8(); i++) {
        if (D_00FBDBB8[i] != 0) func_001ba358(i, D_00FBDBB8[i]);
    }
    neg = 0;
    pos = 0;
    for (i = 0; i < 128; i++) {
        if (D_00FBDFB8[i] & 0x80000000) {
            neg += D_00FBDFB8[i] & 0xFFFF;
        } else {
            pos += D_00FBDFB8[i] & 0xFFFF;
        }
    }
    off = func_00232cc0(4);
    *(s32 *)((u8 *)&D_00009B38 + off) += neg;
    *(s32 *)((u8 *)&D_00009B3C + off) += pos;
}
