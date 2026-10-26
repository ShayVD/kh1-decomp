/* gb.x func_00f3e9f0: matched by hand. */
#include "ovl.h"

typedef struct { s32 v; s32 pad4; s32 kind; s32 extra; u8 pad10[0xC]; } E3e9f0;
typedef struct { u8 pad[0xC]; E3e9f0 *e; } O3e9f0;

s32 func_00f3e9f0(O3e9f0 *o, s32 i) {
    E3e9f0 *e = &o->e[i];
    s32 v = e->v / 256;
    switch (e->kind) {
    case 4:
        v += e->extra;
        break;
    case 8:
        v += e->extra * 4;
        break;
    }
    return v;
}
