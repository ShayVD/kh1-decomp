/* wm.x func_00f74978: the twin of gb.x func_00f4d880 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { u8 pad[8]; s16 x; u8 pad2[10]; f32 fx; f32 fy; } Pt;
extern s32 D_0108F194;
extern f32 D_0108F198;
extern s32 D_0108F1A0;
void func_00f74978(Pt *arg0, s32 arg1) {
    D_0108F194 = (s32)arg0->fx + arg0->x;
    *(s32 *)&D_0108F198 = (s32)arg0->fy;
    D_0108F1A0 = arg1;
}
