/* wm.x func_00f713c0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s16 h; u8 pad2[0xA]; f32 x; f32 y; } Ob713;
void func_00206130(s32, s32, s32, s32, s32, s32);
extern s32 D_003F2C40[];
extern s32 D_00FB59E8;
extern s32 D_0108F3B0;
extern Ob713 *D_0108F3F0[];
extern s32 D_0108F424;

void func_00f713c0(s32 a0, s32 a1)
{
    s32 i;
    s32 x;
    s32 y;
    s32 w;
    s32 c;

    for (i = 0; i < D_0108F3B0; i += 2) {
        if (D_0108F3F0[i] == 0 || D_0108F3F0[i + 1] == 0) {
            continue;
        }
        x = (s32)D_0108F3F0[i]->x + D_0108F3F0[i]->h;
        y = (s32)D_0108F3F0[i]->y + 12;
        w = (s32)D_0108F3F0[i + 1]->x;
        if (D_00FB59E8 == i / 2) {
            c = D_003F2C40[37];
        } else {
            c = D_003F2C40[47];
        }
        if (i / 2 == D_0108F424) {
            c = D_003F2C40[7];
        } else if (D_00FB59E8 == i / 2 && D_0108F424 == -2) {
            c = 0x80000000;
        }
        func_00206130(a1, x, y, w - x, 2, c);
    }
}
