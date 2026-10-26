/* gb.x func_00f49e48: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[64]; void (*fn)(void); } Obj;
Obj *func_00f445a8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f49dd8(void);
extern s32 D_00F82B48, D_00F702F0, D_00F70648;
extern s32 D_00F82B50[];
extern Obj *D_00F82B78[];
void func_00f49e48(void) {
    s32 i;
    s32 q = D_00F702F0;
    for (i = 0; i < D_00F82B48; i++) {
        Obj *o = func_00f445a8(11, 13, 2, 1, 0, 15, D_00F82B50[i] + 52, 1, 0, 0, 0, D_00F70648, 0, 0, 0, 0, 0, 256, q);
        D_00F82B78[i] = o;
        o->fn = func_00f49dd8;
    }
}
