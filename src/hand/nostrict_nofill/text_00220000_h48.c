#include "common.h"
#include "data/bss_0065.h"


typedef struct { u8 r, g, b, a; } Rgba;
typedef struct { u8 pad[4]; u16 x4; } Res;
extern f32 D_00650DD0;
extern s32 D_006488F0;
Res *func_001478c8(s32);
s32 func_00147808(s32);
s32 func_001f0638(s32, s32, s32, s32, s32, s32);

void func_00239558(s32 id, s32 x, s32 y, s32 c) {
    Rgba col;
    u8 v = c;
    col.r = v;
    col.g = v;
    col.b = v;
    col.a = D_00650DD0 * 128.0f;
    D_006488F0 = func_001f0638(D_006488F0, 1, *(s32 *)&col, ((x * 16 + 0x7100) >> 4) - 0x700,
                               ((y * 16 + 0x7420) >> 4) - 0x740, func_00147808(func_001478c8(id)->x4));
}
#include "data/bss_0064_mixed.h"
