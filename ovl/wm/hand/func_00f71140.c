/* wm.x func_00f71140: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; s8 state; } WmIcon4;
void func_00f74978(WmIcon4 *, s32);
extern s32 D_00FB4A58;
extern s32 D_00FB4A5C;
extern s32 D_0108F308;
extern WmIcon4 *D_0108F338[];
extern s32 D_0108F388[];
extern s32 D_0108F418;
extern s32 D_0108F41C;
extern s32 D_0108F420;

void func_00f71140(s32 col, s32 row) {
    s32 sel;
    s32 i;

    for (i = 0; i < D_0108F308; i++) {
        D_0108F338[i]->state = 0;
    }
    sel = row * 2 + col;
    for (i = 0; i < D_0108F308; i++) {
        WmIcon4 *o = D_0108F338[i];
        if (i == sel) {
            o->state = 1;
            func_00f74978(o, 8);
        } else {
            o->state = 0;
        }
        if (i == D_0108F418) {
            if (D_0108F41C != 0) {
                o->state = 7;
            } else if (i != sel) {
                o->state = 9;
            } else {
                o->state = 7;
            }
        }
        if (i == D_0108F420) {
            if (D_0108F41C != 0) {
                o->state = 1;
            } else {
                o->state = 3;
            }
        }
    }
    if (sel >= 0) {
        D_00FB4A58 = D_00FB4A5C = D_0108F388[sel] + 1;
    }
}
