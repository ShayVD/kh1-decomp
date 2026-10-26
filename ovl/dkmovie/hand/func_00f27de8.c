/* dkmovie.x func_00f27de8: matched by hand. */
#include "ovl.h"

s32 sceOpen(s32, s32);
s32 sceLseek(s32, s32, s32);
s32 sceRead(s32, s32, s32);
s32 sceClose(s32);
void FlushCache(s32);
void func_00f23480(void);
s32 func_00f27de8(s32 arg0, s32 arg1) {
    s32 fd;
    s32 size;
    fd = sceOpen(arg0, 1);
    if (fd < 0) {
        while (1) {
            func_00f23480();
        }
    }
    size = sceLseek(fd, 0, 2);
    if (size < 0 || sceLseek(fd, 0, 0) < 0) {
        goto fail;
    }
    FlushCache(0);
    if (sceRead(fd, arg1, size) != size) {
fail:
        sceClose(fd);
        return 0;
    }
    sceClose(fd);
    return 1;
}
