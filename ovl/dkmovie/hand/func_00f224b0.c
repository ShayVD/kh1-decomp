/* dkmovie.x func_00f224b0: matched by hand. */
#include "ovl.h"

typedef struct {
    u8 pad[0x3DDD0];
    s32 f3DDD0;
} MovieWork;
extern s32 D_00F28670;
extern s32 D_00F28678;
extern void *D_00F28688;
extern s32 D_00F2868C;
extern u8 D_002C5968;
s32 func_00f21b88(void);
void func_00f21b98(void);
void func_00f21bb8(void);
void func_00f21c80(MovieWork *);
void func_00f23480(void);
s32 sceCdDiskReady(s32);
s32 func_0024b9d0(void);
void FlushCache(s32);
s32 sceCdRead(s32, s32, void *, s32);
s32 sceCdBreak(void);

void func_00f224b0(void *buf, s32 lsn, s32 n, MovieWork *m) {
    s32 i;
    u32 t;
    volatile u8 *cf;
    D_00F28688 = buf;
    D_00F28670 = lsn;
    D_00F28678 = n;
    D_00F2868C = func_00f21b88();
    cf = &D_002C5968;
    for (;;) {
        func_00f21b98();
        for (i = 0; i < 60; i++) {
            t = *cf;
            if (!((t >> 1) & 1) && sceCdDiskReady(1) == 2) {
                if (func_0024b9d0() == 0) {
                    if (m->f3DDD0 & 8) {
                        for (;;) {
                            func_00f23480();
                        }
                    }
                    FlushCache(0);
                    func_00f21bb8();
                    if (sceCdRead(lsn, n, buf, func_00f21b88()) == 1) {
                        return;
                    }
                    func_00f21b98();
                }
            }
            func_00f21c80(m);
            func_00f23480();
        }
        if (m->f3DDD0 & 8) {
            for (;;) {
                func_00f23480();
            }
        }
        sceCdBreak();
        func_00f23480();
    }
}
