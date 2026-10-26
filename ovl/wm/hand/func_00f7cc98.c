/* wm.x func_00f7cc98: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[6]; u16 btn; u8 pad2[8]; s32 rep; } P7c;
void func_00f7cb60(void);
void func_0011d768(s32);
extern s32 D_00FB5EC0;
extern s32 D_00FB6470;
extern P7c D_0108F980;

void func_00f7cc98(void) {
    s32 old;
    s32 moved = 0;
    s32 b;

    old = D_00FB5EC0;
    b = D_0108F980.rep | ((D_00FB6470 ^ D_0108F980.btn) & D_0108F980.btn);
    D_00FB6470 = D_0108F980.btn;
    if (b & 0x10) {
        D_00FB5EC0--;
        moved = 1;
    }
    if (b & 0x40) {
        D_00FB5EC0++;
        moved = 1;
    }
    D_00FB5EC0 &= 1;
    func_00f7cb60();
    if (old != D_00FB5EC0 && moved) {
        func_0011d768(1);
    }
}
