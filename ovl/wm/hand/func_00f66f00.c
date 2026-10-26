/* wm.x func_00f66f00: the twin of gb.x func_00f3fe08 (tools/ovl/twins.py). */
#include "ovl.h"

typedef struct { void (*fn)(); s32 arg; u16 next; } Node;
extern u16 D_00FB11E8[];
extern Node D_00FB19E8[];
extern s32 D_0108F040;

void func_00f66f00(s32 pri, void (*fn)(), s32 arg) {
    u16 old;
    s32 n;

    if (pri < 0) pri = 0;
    if (pri >= 1024) pri = 1023;
    n = D_0108F040;
    old = D_00FB11E8[pri];
    D_00FB11E8[pri] = D_0108F040 + 1;
    D_00FB19E8[n].fn = fn;
    D_00FB19E8[n].next = old;
    D_00FB19E8[n].arg = arg;
    D_0108F040 = n + 1;
}
