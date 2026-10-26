/* wm.x func_00f5c0c8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; u8 pad2[6]; } WmEnt12;
typedef struct { u8 pad[0xA4]; u16 n; u8 pad2[0x110 - 0xA6]; WmEnt12 e[1]; } WmTbl;
extern WmTbl *D_00F9B540;
extern s32 D_00F9B568;
void func_00f5ae10(s32 *, s32);
void func_00f5ae98(s32, s32);
s32 func_00f68770(s32, s32, s32 *, s32, s32);

void func_00f5c0c8(void) {
    s32 buf[16];
    s32 i;
    s32 k;

    for (i = 0; i < D_00F9B540->n; i++) {
        k = -1;
        switch (D_00F9B540->e[i].id - 1) {
        case 0x38:
            k = 31;
            break;
        case 0x39:
            k = 32;
            break;
        }
        if (k >= 0) {
            func_00f5ae10(buf, i);
            func_00f5ae98(func_00f68770(k, 1, buf, 0, D_00F9B568), 0);
        }
    }
}
