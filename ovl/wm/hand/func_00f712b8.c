/* wm.x func_00f712b8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; s8 state; } WmIcon4;
void func_00f74978(WmIcon4 *, s32);
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s32 D_00FB59E8;
extern s32 D_0108F360[];
extern s32 D_0108F3B0;
extern WmIcon4 *D_0108F3F0[];

void func_00f712b8(s32 col, s32 row) {
    s32 sel;
    s32 i;

    D_00FB59E8 = row;
    sel = row * 2 + col;
    for (i = 0; i < D_0108F3B0; i++) {
        WmIcon4 *o = D_0108F3F0[i];
        if (i == sel) {
            o->state = 1;
            func_00f74978(o, 8);
        } else if (i / 2 == row) {
            o->state = 7;
        } else {
            o->state = 9;
        }
    }
    if (sel >= 0) {
        D_00FB4A58 = D_00FB4A5C = D_0108F360[sel] + 1;
    }
}
