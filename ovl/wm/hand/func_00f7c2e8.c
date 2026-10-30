/* wm.x func_00f7c2e8: matched by hand. */
#include "ovl.h"

typedef struct {
    s32 a[2];
    s32 x8;
    s32 xC;
    s32 x10;
    s32 x14;
    s32 b[2];
    s32 c[2];
} Pal;

typedef struct {
    u8 pad0[0xC];
    s32 xC;
} Ctx;

extern Pal D_00FB6408;
extern Ctx D_00FB6498;
extern s32 D_0108FAA0[];
void func_00f799e0(s32, s32, s32, s32, s32, s32, s32, s32 *, s32, u64, s32, u64);

void func_00f7c2e8(s32 i) {
    s32 b = D_00FB6408.b[i];
    s32 c = D_00FB6408.c[i];
    s32 save;

    save = D_00FB6498.xC;

    D_00FB6498.xC = D_00FB6408.x14;
    func_00f799e0(D_00FB6408.x8, D_00FB6408.x8 + 0x28000, b, c, 128, 128, 8, &D_0108FAA0[i], 0, 68, 0, 0x5001D);
    D_00FB6498.xC = D_00FB6408.x14;
    func_00f799e0(D_00FB6408.x8 + 0x6000, D_00FB6408.x8 + 0x28800, b, c, 128, 64, 8, &D_0108FAA0[i], 0, 68, 0, 0x5001D);
    func_00f799e0(D_00FB6408.x8 + 0x4000, D_00FB6408.x8 + 0x28400, b, c, 128, 128, 4, &D_0108FAA0[i], 0, 0, 0xFFFFFF, 0x50013);
    D_00FB6498.xC = D_00FB6408.a[i];
    func_00f799e0(0, 0, b, c, 128, 128, 32, &D_0108FAA0[i], 0, 136, 0, 0x5C04D);
    D_00FB6498.xC = D_00FB6408.x14;
    func_00f799e0(D_00FB6408.x8 + 0x8000, D_00FB6408.x8 + 0x28800, b, c + 64, 128, 64, 8, &D_0108FAA0[i], 0, 68, 0, 0x5001D);
    D_00FB6498.xC = save;
}
