/* wm.x func_00f71690: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; f32 x; f32 y; } WmIcon;
extern s32 D_00FB4DBC;
extern s32 D_00FB4DC4;
extern s32 D_00FB4DCC;
extern s32 D_0108F3B0;
extern WmIcon *D_0108F3F0[];

void func_00f71690(void) {
    s32 i;

    for (i = 0; i < D_0108F3B0; i++) {
        WmIcon *o = D_0108F3F0[i];
        o->x = D_00FB4DBC + (i & 1) * D_00FB4DCC;
        o->y = D_00FB4DC4 + (i / 2) * 28 - (D_0108F3B0 / 2) * 28 + 28;
    }
}
