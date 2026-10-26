/* gb.x func_00f4d880: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[8]; s16 x; u8 pad2[10]; f32 fx; f32 fy; } Pt;
extern s32 D_00F829D4;
extern f32 D_00F829D8;
extern s32 D_00F829E0;
void func_00f4d880(Pt *arg0, s32 arg1) {
    D_00F829D4 = (s32)arg0->fx + arg0->x;
    *(s32 *)&D_00F829D8 = (s32)arg0->fy;
    D_00F829E0 = arg1;
}
