#include "common.h"

typedef struct { s32 x, y; u8 pad[0x18]; } Vtx20;
typedef struct { u8 pad[0x60]; Vtx20 v[4]; } S631620;

extern s32 D_00631560;
extern volatile u32 D_002C5958;
extern u64 D_0038CD00;
extern s32 D_002E26A0;
extern S631620 D_00631620;

s32 func_0011e340(s32);
void func_00146928(s32);
s32 func_0011cdf0(s32, s32, void *);
s32 func_0011ef10(s32, void *);
void func_001e8e68(void);
void func_001e8e38(void);
void func_001557d0(void);
s32 func_00123158(s32, s32);
s32 func_0011c820(void);

s32 func_001e8ed8(s32 a0, s32 a1, s32 a2) {
    D_00631560 = a2;
    if (func_0011e340(0) == 0) {
        func_00146928(-6);
        func_00146928(-7);
        D_002C5958 |= 0x40000;
        return func_0011cdf0(-8, D_00631560, func_001e8e38);
    }
    return func_0011ef10(0xc352, func_001e8e68);
}

s32 func_001e9028(void) {
    return ((s32)(D_0038CD00 >> 55) & 1) ? 4 : 2;
}

s32 func_001e91c0(void) {
    if (func_0011e340(0) == 0) {
        func_001557d0();
        return 2;
    }
    return 4;
}

s32 func_001e9238(void) {
    s32 r = func_00123158(D_002E26A0, 0);
    while (r) r = func_00123158(D_002E26A0, r);
    return 2;
}

s32 func_001e9288(void) {
    return func_0011c820() ? 4 : 2;
}

void func_001e97d8(s32 a0, s32 a1, s32 a2, s32 a3) {
    s32 x0 = (a0 + 0x700) << 4;
    s32 y0 = (a1 + 0x740) << 4;
    s32 x1 = (a0 + a2 + 0x700) << 4;
    s32 y1 = (a1 + a3 + 0x740) << 4;
    D_00631620.v[0].x = x0;
    D_00631620.v[0].y = y0;
    D_00631620.v[1].x = x1;
    D_00631620.v[1].y = y0;
    D_00631620.v[2].x = x0;
    D_00631620.v[2].y = y1;
    D_00631620.v[3].x = x1;
    D_00631620.v[3].y = y1;
}
