/* wm.x func_00f71058: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x14]; f32 x; f32 y; } O71;
extern s32 D_00FB4DBC;
extern s32 D_00FB4DC0;
extern s32 D_00FB4DCC;
extern s32 D_0108F308;
extern O71 *D_0108F338[];

void func_00f71058(void) {
    s32 i;

    for (i = 0; i < D_0108F308; i++) {
        D_0108F338[i]->x = (i & 1) * D_00FB4DCC + D_00FB4DBC;
        D_0108F338[i]->y = D_00FB4DC0 + (i / 2) * 28;
    }
}
