/* dkmovie.x func_00f25288: near miss (session 141, wwm1), 844 vs 864 bytes (201 words shown, mostly shift): structure complete; left: the 0x10002010 wait loop has its address hoisted in the original (ours recomputes it, so the EE short-loop padding differs), &D_00F28460 is taken after the f3DF55 test in the original, register order of the header loads. */
#include "ovl.h"
typedef struct {
    u8 pad[0x3DD00];
    s32 buf[3];
    s32 f3DD0C;
    s32 f3DD10;
    u8 pad3DD14[4];
    s32 f3DD18;
    s32 f3DD1C;
    s32 f3DD20;
    u8 pad3DD24[4];
    s32 f3DD28;
    u8 pad3DD2C[0x3DEF0 - 0x3DD2C];
    s32 f3DEF0;
    u8 pad3DEF4[0x3DF54 - 0x3DEF4];
    s8 f3DF54;
    s8 f3DF55;
    u8 pad3DF56[0x3DF61 - 0x3DF56];
    s8 f3DF61;
} MovieWork;
typedef struct { s32 f0, f4, f8, fC, f10, f14, f18, f1C, f20, f24, f28; } Blk;
extern MovieWork *D_00F28460;
void sceGsSyncPath(s32, s32);
void func_00f269c0(s32, s32);
void func_00f26a20(s32, s32);
void func_00f22948(Blk *);
void FlushCache(s32);
void func_00f22df8(s32);

void func_00f25288(void) {
    Blk b;
    s32 w, h, fl, fl2, size, cur, prev, started, i, base, cmd, p;
    cur = 1;
    prev = 0;
    started = 0;
    fl2 = 0;
    w = D_00F28460->f3DD18;
    h = D_00F28460->f3DD1C;
    fl = D_00F28460->f3DF54;
    size = w * h * 3 * 128;
    if (fl) {
        fl2 = D_00F28460->f3DF55;
    }
    i = 0;
    base = D_00F28460->f3DEF0;
    b.f24 = fl;
    b.f28 = D_00F28460->f3DF61;
    b.f1C = 4480;
    b.f10 = w * 16;
    b.f20 = 0;
    b.f0 = D_00F28460->f3DD10;
    b.f8 = 0;
    b.f18 = D_00F28460->f3DD20;
    sceGsSyncPath(0, 0);
    func_00f269c0(D_00F28460->f3DD0C, size);
    if (h > 0) {
        cmd = (fl << 27) | w | (fl2 << 26) | 0x70000000;
        w <<= 10;
        p = base - 16;
        do {
            func_00f26a20(D_00F28460->buf[prev], w);
            *(volatile u32 *)0x10002000 = cmd;
            if (started) {
                if (D_00F28460->f3DD28 == 0) {
                    b.f4 = D_00F28460->buf[cur];
                    b.fC = p;
                    b.f14 = 16;
                    sceGsSyncPath(0, 0);
                    func_00f22948(&b);
                }
                FlushCache(0);
                func_00f22df8(D_00F28460->f3DD10);
                sceGsSyncPath(0, 0);
            }
            cur ^= 1;
            prev ^= 1;
            started = 1;
            while (*(volatile s32 *)0x10002010 < 0) {
            }
            while ((*(volatile u32 *)0x1000B000 >> 8) & 1) {
            }
            i++;
            p += 16;
        } while (i < h);
    }
    if (D_00F28460->f3DD28 == 0) {
        b.f4 = D_00F28460->buf[cur];
        b.fC = base + i * 16 - 16;
        b.f14 = 16;
        sceGsSyncPath(0, 0);
        func_00f22948(&b);
    }
    FlushCache(0);
    func_00f22df8(D_00F28460->f3DD10);
    sceGsSyncPath(0, 0);
    while ((*(volatile u32 *)0x1000B400 >> 8) & 1) {
    }
    sceGsSyncPath(0, 0);
}
