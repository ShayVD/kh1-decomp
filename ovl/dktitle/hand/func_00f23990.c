/* dktitle.x func_00f23990: matched by hand. */
#include "ovl.h"

void func_002014a0(void *o, s32 type, s32 mode, s32 px, s32 py, s32 pw, s32 x, s32 *cols, s32 id, s32 sz);
void func_00206130(void *o, s32 px, s32 py, s32 pw, s32 ph, s32 col);
extern s32 D_00F26E50[];

void func_00f23990(void *arg0, s32 arg1, s32 arg2) {
    s32 col = arg2 ? 0x80323296 : 0x80C2726E;
    if (arg1 < 2) {
        func_00206130(arg0, 0, 0, 512, 384, 0x6E000000);
    }
    if (arg1 == 2) {
        func_00206130(arg0, 0, 0, 512, 384, 0x5A000000);
    }
    func_00206130(arg0, 0, 128, 512, 126, 0x30000000);
    func_00206130(arg0, 0, 128, 512, 2, col);
    func_00206130(arg0, 0, 254, 512, 2, col);
    func_002014a0(arg0, 2, 2, 11, 97, 120, 70, D_00F26E50, 1, 16);
}
