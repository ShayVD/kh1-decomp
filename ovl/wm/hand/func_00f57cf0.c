/* wm.x func_00f57cf0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x4C]; s16 a; u8 pad2[2]; s8 b; u8 pad3[0x31]; s16 c; s16 d; } W57;
void func_0011d768(s32);
void func_00f47340(s32);
void func_00f47388(s32);
void func_00f57738(void);
void func_00f56f30(void);
s32 func_00f4ae48(s32);
s32 func_00f4ad68(s32);
s32 func_00f4aca8(s32);
s32 func_00f4c9c8(s32);
extern W57 *D_00F9B540;

void func_00f57cf0(s32 arg0) {
    s32 v;

    func_0011d768(19);
    func_00f47340(11);
    if (arg0 == 0) {
        func_00f57738();
        D_00F9B540->c = func_00f4ae48(D_00F9B540->c);
    } else {
        func_00f56f30();
        D_00F9B540->c = func_00f4ad68(D_00F9B540->c);
    }
    D_00F9B540->d = func_00f4aca8(D_00F9B540->c);
    v = (u16)(D_00F9B540->a = (u16)D_00F9B540->c + 1);
    D_00F9B540->b = func_00f4c9c8(v - 1);
    func_00f47388(11);
}
