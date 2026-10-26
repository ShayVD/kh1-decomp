/* gb.x func_00f4a2c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s16 h; u8 pad2[0xA]; f32 x; f32 y; } Ob713;
void func_00206130(s32, s32, s32, s32, s32, s32);
extern s32 D_003F2C40[];
extern s32 D_00F71268;
extern s32 D_00F82BF0;
extern Ob713 *D_00F82C30[];
extern s32 D_00F82C64;

void func_00f4a2c8(s32 a0, s32 a1)
{
    s32 i;
    s32 x;
    s32 y;
    s32 w;
    s32 c;

    for (i = 0; i < D_00F82BF0; i += 2) {
        if (D_00F82C30[i] == 0 || D_00F82C30[i + 1] == 0) {
            continue;
        }
        x = (s32)D_00F82C30[i]->x + D_00F82C30[i]->h;
        y = (s32)D_00F82C30[i]->y + 12;
        w = (s32)D_00F82C30[i + 1]->x;
        if (D_00F71268 == i / 2) {
            c = D_003F2C40[37];
        } else {
            c = D_003F2C40[47];
        }
        if (i / 2 == D_00F82C64) {
            c = D_003F2C40[7];
        } else if (D_00F71268 == i / 2 && D_00F82C64 == -2) {
            c = 0x80000000;
        }
        func_00206130(a1, x, y, w - x, 2, c);
    }
}
