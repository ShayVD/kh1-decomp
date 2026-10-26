/* wm.x func_00f348e0: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x12]; u16 hp; } P;
P *func_001bb658(s32);
s32 func_002193f0(void);

s32 func_00f348e0(s32 id) {
    P *p;
    p = func_001bb658(id);
    switch (func_002193f0()) {
    case 0:
        if (id == 141) return 9999;
        return p->hp;
    case 1:
    default:
        return p->hp * 0.6666667f;
    case 2:
        return p->hp * 0.5f;
    }
}
