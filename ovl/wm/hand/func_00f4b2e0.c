/* wm.x func_00f4b2e0: matched by hand. */
#include "ovl.h"

typedef struct { u16 id; u8 pad[10]; } E4b;
extern u8 *D_00F9B540;

E4b *func_00f4b2e0(s32 arg0) {
    s32 i;
    E4b *e = (E4b *)(D_00F9B540 + 0x110);

    for (i = 0; i < *(u16 *)(D_00F9B540 + 0xA4); i++, e++) {
        if (e->id == (u16)arg0) {
            return e;
        }
    }
    return NULL;
}
