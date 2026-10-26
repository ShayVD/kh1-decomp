/* dktitle.x func_00f25848: matched by hand. */
#include "ovl.h"

typedef struct { char *(*f0)(void); s32 (*f4)(void); s32 (*f8)(void); s32 (*fc)(void); } Cfg;
typedef unsigned int size_t;
s32 func_0024d9a0(void);
u32 func_00f25500(void);
s32 sceClose(s32);
s32 sceFormat(const char *, const char *, void *, s32);
s32 sceIoctl2(s32, s32, void *, s32, void *, s32);
s32 sceOpen(const char *, s32, ...);
s32 sceRemove(const char *);
s32 sceSync(const char *, s32);
s32 sprintf(char *, const char *, ...);
size_t strlen(const char *);
extern s32 D_0046A614;
extern Cfg D_0046A688;
extern char D_00F27538[], D_00F27548[], D_00F27560[];
extern s32 D_00F2C890;

s32 func_00f25848(void) {
    char buf[128];
    s32 fmt;
    s32 *st0, *st1, *st2, *st3;
    Cfg *c0, *c1, *c2;
    s32 a, b, fd, i, n, busy, rm;

    st0 = &D_0046A614;
    *st0 = 190;
    func_0024d9a0();
    c0 = &D_0046A688;
    *st0 = 200;
    sprintf(buf, D_00F27538, c0->f4(), c0->f8());
    fd = sceOpen(buf, 2);
    if (fd >= 0) {
        sceIoctl2(fd, 0x6802, 0, 0, 0, 0);
        *st0 = 210;
        sceClose(fd);
        *st0 = 220;
        sceRemove(buf);
    }
    busy = 0;
    *st0 = 230;
    rm = 0;
retry:
    c1 = &D_0046A688;
    sprintf(buf, D_00F27548, c1->f4(), c1->f8(), c1->fc());
    fd = sceOpen(buf, 0x203);
    if (fd < 0) {
        st1 = &D_0046A614;
        *st1 = 240;
        switch (fd) {
        case -16:
            busy++;
            *st1 = 250;
            func_0024d9a0();
            *st1 = 260;
            if (busy >= 5) D_00F2C890 = 1;
            goto retry;
        case -27:
            *st1 = 270;
            func_0024d9a0();
            *st1 = 280;
            return 2;
        case -13:
            *st1 = 290;
            return 1;
        case -19:
            *st1 = 300;
            return 1;
        default:
            D_0046A614 = 310;
            return 1;
        }
    }
    n = func_00f25500() >> 7;
    D_0046A614 = 320;
    for (i = 0; i < n; i++) {
        st2 = &D_0046A614;
        a = (s32)c1->f0();
        if (sceIoctl2(fd, 0x6801, (void *)a, strlen(c1->f0()) + 1, 0, 0) < 0) {
            *st2 = 330;
            sceIoctl2(fd, 0x6802, 0, 0, 0, 0);
            *st2 = 340;
            sceClose(fd);
            *st2 = 350;
            rm++;
            sceRemove(buf);
            *st2 = 360;
            if (rm >= 2) return 2;
            goto retry;
        }
    }
    st3 = &D_0046A614;
    *st3 = 370;
    c2 = &D_0046A688;
    sceClose(fd);
    *st3 = 380;
    fmt = 0x2000;
    sprintf(buf, D_00F27538, c2->f4(), c2->f8());
    if (sceFormat(D_00F27560, buf, &fmt, 4) < 0) {
        *st3 = 390;
        return 1;
    }
    *st3 = 340;
    sceSync(buf, 0);
    *st3 = 350;
    return 0;
}
