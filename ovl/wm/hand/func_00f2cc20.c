/* wm.x func_00f2cc20: matched by hand. */
#include "ovl.h"

typedef struct { u8 used; u8 pad[2]; u8 flags; u8 pad2[0xA]; u16 id; u8 pad3[0x10]; OvlMtx m0; OvlMtx m1; } O;
O *func_00f2cae8(s32);
void func_00f2cb08(O *);
void func_00f68980(u16, void *);
void func_00f689f0(u16, void *);

void func_00f2cc20(void) {
    s32 i;
    O *o;
    for (i = 0; i < 384; i++) {
        o = func_00f2cae8(i);
        if (o->used == 0) continue;
        if (o->flags & 2) func_00f2cb08(o);
        if (o->id != 0xFFFF) {
            func_00f689f0(o->id, o->m0);
            func_00f68980(o->id, o->m1);
        }
    }
}
