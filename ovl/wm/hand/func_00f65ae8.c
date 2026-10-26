/* wm.x func_00f65ae8: matched by hand. */
#include "ovl.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; u8 pad[0xC]; } E65;
typedef struct { u8 pad[0xC]; E65 *e; } H65;

s32 func_00f65ae8(H65 *h, s32 i) {
    E65 *e = &h->e[i];
    s32 v = e->a / 256;
    switch (e->c) {
    case 4:
        v += e->d;
        break;
    case 8:
        v += e->d * 4;
        break;
    }
    return v;
}
