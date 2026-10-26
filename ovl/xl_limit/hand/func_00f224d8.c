/* xl_limit.x func_00f224d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x10]; s8 *p; } Lim10;
extern Lim10 *D_00F23EC0[13];
void func_00f224d8(void) {
    s32 i;
    for (i = 0; i < 13; i++) {
        *D_00F23EC0[i]->p = 1;
    }
}
