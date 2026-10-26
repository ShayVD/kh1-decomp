/* dktitle.x func_00f268d8: matched by hand. */
#include "ovl.h"
#include "platform/thread.h"

u8 *func_00f247a0(u8 *, u8 *, s32, s32, s32, s32, s32, u8 *, s32, u64, s32, u64, u8 *, s32);
u8 *func_00f26898(u8 *);
s32 sceDmaGetChan(s32);
void sceDmaSend(s32, u8 *);
s32 sceGsSyncPath(s32, s32);
extern s32 D_00F26E6C;
extern u8 *D_00F2C8B0;
extern u8 *D_00F2C8B4;
extern s32 D_00F2C8D0;
extern s32 D_00F2C8D8;
extern s32 D_00F2C8E0[3];

static inline s32 pixsz(s32 n, s32 w, s32 h, s32 bpp) { return n * w * h * bpp / 8; }

void func_00f268d8(void) {
    u8 rgba[4];
    s32 x, y, ch, i, c, c2;
    u8 *p, *b;

    x = D_00F2C8D8 / 256;
    y = x - 56;
    c = D_00F26E6C / 2;
    rgba[0] = c;
    rgba[1] = c;
    rgba[2] = c;
    rgba[3] = c;
    ch = sceDmaGetChan(2);
    i = D_00F2C8E0[0] / 256;
    p = D_00F2C8B4;
    if (i >= 30) { D_00F2C8E0[0] = 0; i = 0; }
    p = func_00f247a0(D_00F2C8B0 + pixsz(i, 64, 64, 4) + 0x1B000, D_00F2C8B0 + (i << 10) + 0x3BC00, y, 259, 64, 64, 4, rgba, 0, 68, 0, 0x3001D, p, 0x2600);
    i = D_00F2C8E0[1] / 256;
    if (i >= 24) { D_00F2C8E0[1] = 0; i = 0; }
    p = func_00f247a0(D_00F2C8B0 + pixsz(i, 64, 64, 4), D_00F2C8B0 + (i << 10) + 0x2E400, x - 96, 259, 64, 64, 4, rgba, 0, 68, 0, 0x3001D, p, 0x2600);
    i = D_00F2C8E0[2] / 256;
    if (i >= 30) { D_00F2C8E0[2] = 0; i = 0; }
    p = func_00f247a0(D_00F2C8B0 + pixsz(i, 64, 64, 4) + 0xC000, D_00F2C8B0 + (i << 10) + 0x34400, x - 136, 259, 64, 64, 4, rgba, 0, 68, 0, 0x3001D, p, 0x2600);
    b = D_00F2C8B0;
    c2 = D_00F26E6C * 51 / 256;
    rgba[0] = c2;
    rgba[1] = c2;
    rgba[2] = c2;
    rgba[3] = c2;
    p = func_00f247a0(b + 0x2A000, b + 0x2E000, 368, 0, 128, 128, 8, rgba, 0, 72, 0, 0x3001D, p, 0x2600);
    p = func_00f247a0(b + 0x2A000, b + 0x2E000, 368, 0, 128, 128, 8, rgba, 0, 68, 0, 0x3001D, p, 0x2600);
    p = func_00f26898(p);
    if ((s32)p >= (s32)(D_00F2C8B4 + D_00F2C8D0)) PlatBreak();
    sceGsSyncPath(0, 0);
    sceDmaSend(ch, D_00F2C8B4);
    sceGsSyncPath(0, 0);
}
