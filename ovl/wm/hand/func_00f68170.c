/* wm.x func_00f68170: the twin of gb.x func_00f41078 (tools/ovl/twins.py). */
#include "ovl.h"

void *func_001bb500(s32, s32);
void *memset(void *, s32, u32);
extern void *D_00FB49E8;
void func_00f68170(void) {
    void **pp = &D_00FB49E8;
    void *p = func_001bb500(0x4800, 0x10);
    *pp = p;
    memset(p, 0, 0x4800);
}
