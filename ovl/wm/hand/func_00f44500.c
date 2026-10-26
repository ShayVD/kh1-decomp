/* wm.x func_00f44500: matched by hand. */
#include "ovl.h"

void func_00f43dd0(s32, void *);
extern s32 D_00F87054;
extern s32 D_00FB73A8;
extern s32 D_00FB73B8;
extern s32 D_01080994;
extern s32 D_01080998;

void func_00f44500(void) {
    s32 p = D_00F87054;
    D_01080994 = 0;
    func_00f43dd0(p, &D_00FB73A8);
    D_01080994 = p;
    p += 0x1000;
    D_01080998 = 0;
    func_00f43dd0(p, &D_00FB73B8);
    D_01080998 = p;
}
