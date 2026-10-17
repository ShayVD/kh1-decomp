/* rodata jtbl 0x48ea00. 4w off (nostrict): case 4/8 inner y<15 test polarity: orig keeps 8.0 block as fallthrough in case 4/8 (bc1f->16.0), ours puts 16.0 first. Test with wqb03_rr.py 0048ea00. */
#include "common.h"
typedef struct { u8 pad[4]; f32 f4; f32 f8; } Spd70;
typedef struct { u8 pad[0x6C]; Spd70 *p6C; s32 w70; } Act70;
typedef struct { u8 pad[0x120]; f32 f120, f124, f128, f12C; } Pad70;

void func_00170170(Act70 *a, Pad70 *p) {
    f32 x = p->f124;
    f32 y = p->f12C;
    switch (a->w70) {
    case 10:
    case 15:
        p->f120 = p->f128 = 0.0f;
        if (x < -5.0f) x = -1.0f;
        else if (x > 5.0f) x = 1.0f;
        else x = 0.0f;
        y = 1.0f;
        break;
    case 13:
        p->f120 = p->f128 = 0.0f;
        if (x < -5.0f) x = -1.0f;
        else if (x > 5.0f) x = 1.0f;
        else x = 0.0f;
        y = 2.0f;
        break;
    case 4:
    case 8:
        if (x < -5.0f) x = -8.0f;
        else if (x > 5.0f) x = 8.0f;
        else x = 0.0f;
        if (y < 5.0f) goto zero;
        else if (y < 15.0f) {
        eight:
            y = 8.0f;
        } else y = 16.0f;
        break;
    case 24:
    case 25:
        if (x < -5.0f) x = -8.0f;
        else if (x > 5.0f) x = 8.0f;
        else x = 0.0f;
        if (y < 5.0f) {
        zero:
            y = 0.0f;
        } else if (y < 15.0f) y = 4.0f;
        else goto eight;
        break;
    case 26:
        y = 0.0f;
        x = 0.0f;
        break;
    default:
        if (y < 5.0f) y = 0.0f;
        else if (y < 15.0f) y = a->p6C->f4;
        else if (y < 25.0f) y = a->p6C->f8;
        else y = a->p6C->f8;
        x = 0.0f;
        break;
    }
    p->f124 = x;
    p->f12C = y;
}
