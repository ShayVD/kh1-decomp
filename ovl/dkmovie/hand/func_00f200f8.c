/* dkmovie.x func_00f200f8: matched by hand. */
#include "ovl.h"

void func_00100ab0(void);
extern s32 D_002BBE14;
extern s32 D_002C5958;
extern s32 D_0035C6F0;

/* the movie ended: the display back to the game's (func_00f20320 set it up) */
void func_00f200f8(void) {
    D_002BBE14 = 0;
    func_00100ab0();
    D_0035C6F0 = 1;
    D_002C5958 &= ~0x40;
}
