/* wm.x func_00f67840: the twin of gb.x func_00f40748 (tools/ovl/twins.py). */
#include "ovl.h"

void func_001bef98(void *, void *);
extern u8 D_00FB88E0[];
extern u8 D_0108F050[];
void *func_00f67840(void) {
    OvlMtx m;
    func_001bef98(D_0108F050, D_00FB88E0);
    return D_0108F050;
}
