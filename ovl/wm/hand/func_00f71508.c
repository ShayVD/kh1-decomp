/* wm.x func_00f71508: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u8 kind; u8 pad2[0x3B]; void (*cb)(void); } WmWin;
WmWin *func_00f6b6a0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f70ed0(void);
void func_00f713c0(void);
extern s32 D_00FB4A70;
extern s32 D_00FB4DC8;
extern s32 D_0108F3B0;
extern s32 D_0108F3C8[];
extern WmWin *D_0108F3F0[];

void func_00f71508(void)
{
    s32 c = D_00FB4A70;
    s32 i;

    for (i = 0; i < D_0108F3B0; i++) {
        D_0108F3F0[i] = func_00f6b6a0(11, 13, 2, 1, 0, 15, D_0108F3C8[i] + 52, 1, 0, 0, 0, D_00FB4DC8, 0, 0, 0, 0, 0, 256, c);
        D_0108F3F0[i]->kind = 6;
        D_0108F3F0[i]->cb = func_00f70ed0;
    }
    func_00f6b6a0(11, 7, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 256, c)->cb = func_00f713c0;
}
