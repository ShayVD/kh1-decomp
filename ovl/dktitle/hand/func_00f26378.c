/* dktitle.x func_00f26378: matched by hand. */
#include "ovl.h"

typedef struct { s32 x0; s32 (*f4)(void); s32 (*f8)(void); s32 (*fc)(void); s32 x10[4]; void (*f20)(s32); } Cfg;
s32 func_0024d8f0(void);
s32 func_0024d9a0(void);
s32 func_00f25528(s32);
s32 func_00f25848(void);
s32 func_00f25c40(void);
s32 sceClose(s32);
s32 sceOpen(const char *, s32, ...);
s32 sprintf(char *, const char *, ...);
extern s32 D_0046A614;
extern Cfg D_0046A688;
extern void (*D_0046A6A8)(s32);
extern char D_00F27548[];
extern s32 D_00F2C890;

void func_00f26378(void) {
    char buf[128];
    s32 *st;
    Cfg *c;
    s32 a, b, fd;

    if (func_00f25848() == 0) {
        st = &D_0046A614;
        *st = 370;
        func_0024d8f0();
        *st = 380;
        a = func_00f25c40();
        *st = 420;
        if (a == 0) {
            func_0024d9a0();
            *st = 430;
            c = &D_0046A688;
            a = c->f4();
            b = c->f8();
            sprintf(buf, D_00F27548, a, b, c->fc());
            fd = sceOpen(buf, 3);
            if (fd >= 0) {
                *st = 440;
                if (func_00f25528(fd) == 0) {
                    c->f20(2);
                    *st = 450;
                } else {
                    c->f20(3);
                    *st = 460;
                }
                sceClose(fd);
                D_0046A614 = 470;
            } else {
                c->f20(3);
                *st = 480;
            }
            func_0024d8f0();
            D_0046A614 = 490;
        } else {
            D_0046A6A8(3);
        }
    } else {
        D_0046A614 = 360;
        D_00F2C890 = 1;
        D_0046A6A8(3);
    }
}
