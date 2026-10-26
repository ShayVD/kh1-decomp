/* wm.x func_00f70f40: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x40]; void (*cb)(void); } WmWin;
WmWin *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f70ed0(void);
extern s32 D_00FB4A70;
extern s32 D_00FB4DC8;
extern s32 D_0108F308;
extern s32 D_0108F310[];
extern WmWin *D_0108F338[];

void func_00f70f40(void) {
    s32 c = D_00FB4A70;
    s32 i;

    for (i = 0; i < D_0108F308; i++) {
        WmWin *w = func_00f6b6a0(11, 13, 2, 1, 0, 15, D_0108F310[i] + 52, 1, 0, 0, 0, D_00FB4DC8, 0, 0, 0, 0, 0, 256, c);
        D_0108F338[i] = w;
        w->cb = func_00f70ed0;
    }
}
