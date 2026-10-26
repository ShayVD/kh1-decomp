/* gb.x func_00f20060: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0xA4]; u16 a4; } GbW;
extern GbW *D_00F56DC0;
void func_00f20030(s32);
s32 func_00f20060(void) {
    GbW *w = D_00F56DC0;
    if (w->a4 == 0) {
        func_00f20030(0xE4);
        return 1;
    }
    return 0;
}
