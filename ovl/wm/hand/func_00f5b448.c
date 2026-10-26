/* wm.x func_00f5b448: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 id; u8 pad2[6]; } WmEnt12;
typedef struct { u8 pad[0xA4]; u16 n; u8 pad2[0x110 - 0xA6]; WmEnt12 e[1]; } WmTbl;
extern WmTbl *D_00F9B540;
s32 func_001c0310(s32, void (*)(s32), ...);
void func_00f5b048(s32);
void func_00f5b198(s32);
void func_00f5b2f0(s32);

s32 func_00f5b448(s32 which) {
    f32 unused[4][4];
    s32 r = 0;
    s32 i;

    for (i = 0; i < D_00F9B540->n; i++) {
        switch (D_00F9B540->e[i].id - 1) {
        case 61:
            if (which == 0) {
                func_001c0310(-1, func_00f5b048, i);
                r = 1;
            }
            break;
        case 62:
            if (which == 1) {
                func_001c0310(-1, func_00f5b198, i, 0);
                r = 1;
            }
            break;
        case 63:
            if (which == 2) {
                func_001c0310(-1, func_00f5b2f0, i);
                r = 1;
            }
            break;
        }
    }
    return r;
}
