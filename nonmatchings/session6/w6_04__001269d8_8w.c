/* func_001269d8: 8 words off (nostrict). Only the tail: orig reloads D_004F7810 with lui a1 shared + lw %lo(a1) twice (ptr in v0, buf[14] in v1); this version (volatile cast on the [24] read) gets the reload but via addiu a1 full address. */
#include "common.h"
typedef struct { u8 pad[0x29]; u8 x29; } S14c;
typedef struct { u8 pad[0xd0]; u8 xd0; } S6c;
typedef struct { u8 pad[0x6c]; S6c *x6c; u8 pad70[0xdc]; S14c *x14c; u8 pad150[0x14]; s32 x164; } Obj164;
typedef struct { s16 x0; u8 pad[18]; } E20;
typedef struct { u8 a, b; } Pair8;
extern E20 *D_004F7810;
extern Pair8 D_002E27C0[4];
extern f32 D_002E27CC, D_002E27D0;
void func_00126238(Obj164 *, s32, s32 *);
f32 func_0012ed88(Obj164 *, s32 *, f32 *, s32);
u8 func_001269d8(Obj164 *o, s32 *a1, s32 a2) {
    s32 buf[66];
    f32 tmp[4];
    s32 i;
    u32 j;
    f32 d;
    for (i = 65; i >= 0; i--) buf[i] = 0;
    if (o->x14c->x29 >= o->x6c->xd0) buf[8] = 1;
    if (*a1 == 0) {
        func_00126238(o, a2, buf);
    } else {
        d = func_0012ed88(o, a1, tmp, a2);
        if (d < D_002E27D0 && D_002E27CC < d) buf[14] = 1;
        else func_00126238(o, a2, buf);
    }
    for (i = 0; i < 66; i++) {
        for (j = 0; j < 4; j++) {
            if (buf[D_002E27C0[j].a] > 0 && D_004F7810[D_002E27C0[j].b].x0 != o->x164) return D_002E27C0[j].b;
        }
    }
    if (o->x14c->x29 < 2) goto r25;
    if (o->x164 == D_004F7810[26].x0) {
        if (buf[14] > 0) goto r25;
    }
    if (o->x164 != (*(E20 *volatile *)&D_004F7810)[24].x0) return 24;
r25:
    return 25;
}
