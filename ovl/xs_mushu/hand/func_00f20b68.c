/* xs_mushu.x func_00f20b68: matched by hand. */
#include "ovl.h"

extern u8 *D_00F21698[5];
void func_00f20b68(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        **(u8 **)(D_00F21698[i] + 0x10) = 1;
    }
}
