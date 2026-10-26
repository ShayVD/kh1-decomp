/* dkmovie.x func_00f28208: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DD48]; s32 fd; u8 pad1[0x3DF51 - 0x3DD4C]; s8 flag; s8 flag2; } MovieWork;
s32 sceClose(s32);

void func_00f28208(MovieWork *w) {
    if (w->fd >= 0) {
        if (w->flag == 0) {
            sceClose(w->fd);
        }
        w->fd = -1;
    }
}
