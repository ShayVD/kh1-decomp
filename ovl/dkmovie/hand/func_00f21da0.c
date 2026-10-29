/* dkmovie.x func_00f21da0: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad[0x3DD48];
    s32 f3DD48;
    u8 pad3DD4C[0x3DF52 - 0x3DD4C];
    s8 f3DF52;
} MovieWork;
typedef unsigned int size_t;
void *memcpy(void *, const void *, size_t);
extern s32 D_00F28670;
extern s32 D_00F28674;
extern s32 D_00F28678;
extern s32 D_00F2867C;
extern s8 D_00F28680;
extern u8 *D_00F28684;
extern u8 *D_00F28688;
extern s32 D_00F2868C;
extern char D_00F28548[];
extern char D_00F28558[];
void FlushCache(s32);
s32 sceCdDiskReady(s32);
s32 sceCdRead(s32, s32, void *, s32);
s32 sceCdBreak(void);
void func_0024b9e0(s32);
void func_0024b9f0(s32);
CONTEXT_ONLY void func_00f21b98(void) {
    func_0024b9e0(0);
    func_0024b9f0(0);
}
s32 func_0024b9d0(void);
void func_00f21bd8(MovieWork *);
void func_00f23480(void);
void func_00f255f0(void);
void func_0024b1e8(char *, char *, s32);

void func_00f21da0(s32 lsn, s32 n, u8 *buf, s32 mode, MovieWork *m) {
    s32 i;
    u8 *p;
    D_00F28684 = buf;
    D_00F2868C = mode;
    D_00F28670 = lsn;
    D_00F28678 = n;
    if (D_00F28680 == 0 && lsn == D_00F28674 + D_00F2867C - 1) {
        FlushCache(0);
        memcpy(buf, D_00F28688, 2048);
        buf += 2048;
        n--;
        lsn++;
    }
    D_00F2867C = n;
    D_00F28680 = 1;
    D_00F28674 = lsn;
    if (m->f3DF52) {
        D_00F28688 = buf + n * 2048 - 2048;
        if (m->f3DD48 < 0) {
            do { func_0024b1e8(D_00F28548, D_00F28558, 222); } while (0);
        }
        return;
    }
    p = buf + n * 2048 - 2048;
    for (;;) {
        for (i = 0; i < 60; i++) {
            if (sceCdDiskReady(1) == 2) {
                func_00f21b98();
                D_00F28688 = p;
                if (func_0024b9d0() == 0) {
                    FlushCache(0);
                    if (sceCdRead(lsn, n, buf, mode) == 1) {
                        return;
                    }
                }
            }
            func_00f21bd8(m);
            func_00f23480();
            func_00f255f0();
        }
        sceCdBreak();
        func_00f23480();
        func_00f255f0();
    }
}
