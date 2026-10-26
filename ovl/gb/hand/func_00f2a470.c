/* gb.x func_00f2a470: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10D4]; s32 flip; s32 ang; } W515;
typedef struct { u8 pad[0x10]; s32 btn; } Pad515;
extern W515 *D_00F56DC0;
extern s8 D_00F56DA8[];
Pad515 *func_001ba488(s32);

void func_00f2a470(s32 *x, s32 *y)
{
    Pad515 *pad;
    s32 k;
    s32 j;

    *x = 0;
    *y = 0;
    pad = func_001ba488(0);
    k = D_00F56DC0->ang / 1024 * 4;
    j = k + 8;
    if (pad->btn & 0x80) {
        *x = -D_00F56DA8[j];
        *y = -D_00F56DA8[k + 10];
    }
    if (pad->btn & 0x20) {
        *x = D_00F56DA8[j];
        *y = D_00F56DA8[k + 10];
    }
    if (pad->btn & 0x10) {
        *x = D_00F56DA8[k + 9];
        *y = D_00F56DA8[k + 11];
        if (D_00F56DC0->flip > 0) {
            *x = -*x;
            *y = -*y;
        }
    }
    if (pad->btn & 0x40) {
        *x = -D_00F56DA8[j + 1];
        *y = -D_00F56DA8[j + 3];
        if (D_00F56DC0->flip > 0) {
            *x = -*x;
            *y = -*y;
        }
    }
}
