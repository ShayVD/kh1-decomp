/* dkmovie.x func_00f235d8: matched by hand. */
#include "ovl.h"

typedef struct { u8 pad[0x3DD48]; s32 fd; u8 pad1[0x3DF51 - 0x3DD4C]; s8 flag; s8 flag2; } MovieWork;
s32 sceIoctl(s32, s32, void *);
s32 func_00f235d8(MovieWork *arg0) {
    s32 fd = arg0->fd;
    s32 st = -1;
    if (fd < 0) {
        return 0;
    }
    sceIoctl(fd, 1, &st);
    return st != 0;
}
