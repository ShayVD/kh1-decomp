/* wm.x func_00f68bc0: the twin of gb.x func_00f41ac8 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { s32 v[2]; } T2;
extern T2 D_00FB8920;
void func_002078f0(s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_00f68bc0(s32 a, s32 sel, s32 base, s32 y, s32 off) {
    T2 t = D_00FB8920;
    func_002078f0(a, t.v[sel == 0], 2, 2, base, y, 96, base + 48, 77);
    
    func_002078f0(a, t.v[(sel ^ 1) == 0], 2, 2, base + off, y, 96, base + 158, 78);
}
