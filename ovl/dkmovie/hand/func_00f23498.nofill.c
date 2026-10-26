/* dkmovie.x func_00f23498: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DD90]; s32 *p; u8 pad1[0x3DF60 - 0x3DD94]; u8 f; } MovieWork;
extern MovieWork *D_00F28460;
void func_00f23498(void) {
    s32 *p = D_00F28460->p;
    s32 n = *p + 16;
    D_00F28460->p = (s32 *)((u8 *)p + n);
    if (n != 16) {
        D_00F28460->f = 1;
    }
}
