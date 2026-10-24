#include "common.h"
#include "data/bss_0066.h"

extern s32 D_0046A558;
extern s32 D_0046A55C;
extern s32 D_0046A560;
extern s32 D_0046A5D8;
extern s16 D_00669A40[8]; /* src/data/bss_0066.c: s16 D_00669A40[0xc] */
extern s32 D_00669A60;
extern s32 D_00669A64;
extern s32 D_00669A7C;
void func_0024c460(void *);
void func_0024be88(void *);
void func_0024c950(void *);
void func_001f8f30(void);
s32 func_0024be58(void);
void func_0011d768(s32);
s32 func_001f3840(void *);
void func_0024cf00(void);
s32 func_001be010(s32);
void func_001be3c0(s32);

void func_0024cfa0(void *a) {
    s32 i;
    func_0024c460(a);
    func_0024be88(a);
    func_0024c950(a);
    func_001f8f30();
    if (D_0046A558 != 0 && (func_0024be58() & 0x2000)) {
        s32 *p = &D_0046A55C;
        if (*p == 0) {
            *p = 1;
            func_0011d768(2);
            func_001f3840(a);
            D_0046A5D8 = 0;
            return;
        }
    }
    if (!(func_0024be58() & 0x2000)) return;
    if (D_0046A55C != 0) return;
    if (D_0046A560 == 0) return;
    for (i = 0; i < 8; i++) {
        if (D_00669A40[i] == -1) continue;
        if (D_00669A40[i] != 0) break;
    }
    if (i == 8) {
        func_0011d768(4);
        return;
    }
    D_0046A5D8 = 1;
    D_0046A55C = 1;
    func_0011d768(2);
    func_001f3840(a);
    if (D_00669A60 < 0) return;
    func_0024cf00();
    if (D_00669A64 != 0) {
        D_00669A7C = func_001be010(D_00669A60);
        return;
    }
    func_001be3c0(D_00669A60);
}

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
