/* dktitle.x func_00f26180: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; s32 (*f4)(void); s32 (*f8)(void); s32 (*fc)(void); } Cfg;
void FlushCache(s32);
void func_00f25c28(void);
s32 sceClose(s32);
s32 sceMkdir(const char *, s32);
s32 sceOpen(const char *, s32, ...);
s32 sceSync(const char *, s32);
s32 sceWrite(s32, const void *, s32);
s32 sprintf(char *, const char *, ...);
extern Cfg D_0046A688;
extern char D_00F27538[], D_00F27568[], D_00F27578[], D_00F27590[], D_00F275A8[];
extern void *D_00F2C8B8, *D_00F2C8BC, *D_00F2C8C0;
extern s32 D_00F2C8C4, D_00F2C8C8, D_00F2C8CC;

s32 func_00f26180(void) {
    char buf[64];
    Cfg *c;
    s32 a, fd;

    if (sceMkdir(D_00F27568, 0x11FF) != 0) for (;;) func_00f25c28();
    c = &D_0046A688;
    a = c->f4();
    sprintf(buf, D_00F27538, a, c->f8());
    FlushCache(0);
    fd = sceOpen(D_00F27578, 0x602, 0x1FF);
    if (fd < 0) for (;;) func_00f25c28();
    if (sceWrite(fd, D_00F2C8B8, D_00F2C8C4) < 0) for (;;) func_00f25c28();
    sceClose(fd);
    sceSync(buf, 0);
    fd = sceOpen(D_00F27590, 0x602, 0x1FF);
    if (fd < 0) for (;;) func_00f25c28();
    if (sceWrite(fd, D_00F2C8BC, D_00F2C8C8) < 0) for (;;) func_00f25c28();
    sceClose(fd);
    sceSync(buf, 0);
    fd = sceOpen(D_00F275A8, 0x602, 0x1FF);
    if (fd < 0) for (;;) func_00f25c28();
    if (sceWrite(fd, D_00F2C8C0, D_00F2C8CC) < 0) for (;;) func_00f25c28();
    sceClose(fd);
    sceSync(buf, 0);
    return 0;
}
