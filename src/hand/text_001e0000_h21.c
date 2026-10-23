#include "common.h"
#include "vm/script_vm.h"
#include "platform/math.h"
#include "data/bss_0063.h"


typedef struct { f32 x, y, z; } V3;
#include "data/types/text_001e0000_h21.h"

extern volatile u32 D_002C5958;
#include "data/pieces/D_002E26A0.h"


/* func_001e8ed8, func_001e9028, func_001e91c0, func_001e9238, func_001e9288 are in src/event/sound.c. */


/* func_001e97d8 is in src/screen/wave.c. */

/* func_001eac68, func_001eb038, func_001eb0a0, func_001eb140, func_001eb1d8, func_001eb278, func_001eb318, func_001eb380, func_001eb418, func_001eb4b8, func_001eb558, func_001eb910, func_001eb9a8, func_001eb9f8, func_001eba80, func_001ebb10, func_001ebba0, func_001ebc38, func_001ebd48, func_001ebde0, func_001ec040, func_001ec258, func_001ec2c0, func_001ec3f8, func_001ec570, func_001ec610, func_001ec678, func_001ec6f8, func_001ec758 are in src/save/flags.c. */


typedef struct { u8 pad0[4]; s8 b4; u8 pad5[11]; s32 f10; u8 pad14[4]; s32 f18; u8 pad1c[0x2c]; } Ent48;
extern Ent48 D_0063EE40[4];
void FlushCache(s32);
s32 func_001eced0(s32 id) {
    s32 i;
    Ent48 *e;
    FlushCache(0);
    for (e = D_0063EE40, i = 0; i < 4; i++, e++) {
        if (e->b4 != 0 && e->f10 == id) return e->f18;
    }
    return 0;
}

extern s8 D_0063F640[]; /* src/data/bss_0063.c: u8 D_0063F640[256] */
s32 func_001ecf40(s8 *dst) {
    s32 i;
    s8 *p;
    for (i = 0; i < 255; i++) *dst++ = D_0063F640[i];
    D_0063F640[255] = 0;
    if (D_0063F640[0] == 0) return 0;
    p = &D_0063F640[255];
    for (i = 255; i >= 0; i--) *p-- = 0;
    return 1;
}

f32 func_001edc80(V3 *a, V3 *b) {
    V3 d;
    d.x = a->x - b->x;
    d.y = a->y - b->y;
    d.z = a->z - b->z;
    return PlatSqrtf(d.x * d.x + d.y * d.y + d.z * d.z);
}

u32 func_001edd88(u32 c, s32 s) {
    u8 *p = (u8 *)&c;
    u32 a;
    if (s != 128) {
        a = ((c >> 24) * s) >> 7;
        if (a > 255) a = 255;
        p[3] = a;
    }
    return c;
}

u32 func_001edf40(u32 x, u32 y) {
    u32 res;
    u8 *r = (u8 *)&res;
    u8 *p = (u8 *)&x;
    u8 *q = (u8 *)&y;
    res = (res & ~0xff) | ((u32)(p[0] + q[0]) >> 1);
    r[1] = (p[1] + q[1]) >> 1;
    r[2] = (p[2] + q[2]) >> 1;
    r[3] = (p[3] + q[3]) >> 1;
    return res;
}

#include "data/pieces/D_002BBDF4.h"
extern f32 D_002BBDEC;
u32 func_001ee118(void) {
    return *(volatile u32 *)&D_002BBDF4 * D_002BBDEC;
}
#include "data/pieces/D_00389C90.h"
#include "data/pieces/D_002C5958.h"
#include "data/pieces/D_002BBDEC.h"
