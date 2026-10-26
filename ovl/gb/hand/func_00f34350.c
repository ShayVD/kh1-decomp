/* gb.x func_00f34350: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[4]; u16 h4; u8 pad6[6]; } Ent;
typedef struct { u8 pad[164]; u16 n; u8 pad166[106]; Ent e[1]; } G;
extern G *D_00F56DC0;
void func_001c0310();
void func_00f33f50(s32);
void func_00f340a0(s32);
void func_00f341f8(s32);
s32 func_00f34350(s32 mode) {
    s32 i;
    s32 r = 0;
    OvlMtx m;
    for (i = 0; i < D_00F56DC0->n; i++) {
        switch (D_00F56DC0->e[i].h4 - 1) {
        case 61:
            if (mode == 0) {
                func_001c0310(-1, func_00f33f50, i);
                r = 1;
            }
            break;
        case 62:
            if (mode == 1) {
                func_001c0310(-1, func_00f340a0, i, 0);
                r = 1;
            }
            break;
        case 63:
            if (mode == 2) {
                func_001c0310(-1, func_00f341f8, i);
                r = 1;
            }
            break;
        }
    }
    return r;
}
