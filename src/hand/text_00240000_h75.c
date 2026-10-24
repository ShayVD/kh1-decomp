#include "common.h"
#include "data/bss_0066.h"

/* needs make: uses rodata */
extern void *D_00469FF8[];
extern s32 D_00469FD8[];
extern void *D_0046A018[];

typedef struct { s32 unk0; char *(*unk4)(void); s32 unk8; s32 unkC; s32 unk10; } HddCtx;
extern HddCtx D_0046A688;
extern s32 D_0046A674;
extern s32 D_0046A614;
#include "data/pieces/D_0046A650.h"
void func_0024d9a0(void);
void func_0024d8f0(void);
s32 sprintf(char *, const char *, ...);
s32 func_0025b588(const char *, s32);
s32 func_0025c448(s32, s32, s32, s32, s32, s32);
s32 func_0025ce38(s32);
s32 func_0024dad0(const char *, s32);

#include "data/pieces/D_004919B0.h"

s32 func_0024db78(s32 size) {
    HddCtx *c = &D_0046A688;
    s32 used = 0;
    s32 fd;
    s32 flag;
    s32 n;
    char buf[64];
    flag = c->unk10;
    D_0046A674 = 0;
    if (flag) func_0024d9a0();
    D_0046A614 = 40;
    sprintf(buf, "hdd0:%s,,%s", c->unk4(), D_0046A650);
    fd = func_0025b588(buf, 1);
    if (fd >= 0) {
        used = func_0025c448(fd, 0x6803, 0, 0, 0, 0);
        if (used < 0) used = 0;
        used++;
        func_0025ce38(fd);
    }
    D_0046A614 = 50;
    n = ((((u32)(size + 0xFFFFF) >> 20) + 127) >> 7) + 1;
    if (func_0024dad0(D_004919B0, n - used) == 0) D_0046A674 = -1;
    if (flag) func_0024d8f0();
    D_0046A614 = 80;
    return D_0046A674;
}

#include "data/data_0046.h"
