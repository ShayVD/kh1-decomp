#include "common.h"
typedef struct {
    u8 pad0[0x20];
    f32 x20;
    f32 x24;
    f32 x28;
    f32 x2c;
    u8 pad30[0x70 - 0x30];
    s32 x70;
    u8 pad74[0x164 - 0x74];
    s32 x164;
    u8 pad168[0x3d4 - 0x168];
    f32 x3d4;
    u8 pad3d8[0x404 - 0x3d8];
    f32 x404;
    u8 pad408[0x480 - 0x408];
    f32 x480;
} O95;
extern f32 D_002BBDFC;
s32 func_00130340(O95 *, s32, f32);
void *func_00130578(O95 *, s32, f32);
void func_0014f658(O95 *, s32);
void func_001395d8(O95 *o) {
    f32 f;
    f32 g;
    if ((u32)(o->x70 - 22) < 2) {
        f = o->x404 - D_002BBDFC;
        o->x404 = f;
        if (f > 60.0f) {
            o->x24 = 1.0f;
            o->x2c = 40.0f;
            o->x20 = 0.0f;
            o->x28 = 0.0f;
            g = (f - 60.0f) / 15.0f;
            o->x480 = g * 0.9f + 0.1f;
        } else if (f > 0.0f) {
            o->x2c = 0.0f;
            o->x480 = 0.1f;
            if (o->x70 == 22 && o->x3d4 > 0.0f) {
                o->x2c = 40.0f;
                o->x404 = f + D_002BBDFC;
            }
        } else {
            func_00130340(o, 103, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
            switch (o->x70) {
            case 22:
                func_0014f658(o, 0);
                break;
            case 23:
                func_0014f658(o, 4);
                break;
            }
        }
    } else if (o->x164 == 102) {
        f32 h = o->x404 - D_002BBDFC;
        o->x404 = h;
        if (h > 60.0f) {
            g = (h - 60.0f) * 0.125f;
            o->x480 = g * 0.9f + 0.1f;
        } else if (h > 0.0f) {
            o->x480 = 0.1f;
        } else {
            func_00130340(o, 103, 0.0f);
            func_00130578(o, 0x40000000, 8.0f);
        }
    }
    if (o->x164 == 103) o->x480 += (1.0f - o->x480) * 0.3f;
}
