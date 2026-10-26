/* xs_mushu.x func_00f20af8: matched by hand. */
#include "ovl.h"

extern void *D_00F21380, *D_00F21388;
extern void *D_00F21698[5];
void *func_00148968(void *, void *, s32);
void func_00f20af8(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_00F21698[i] = func_00148968(D_00F21388, D_00F21380, i + 6);
    }
}
