/* The display environment, 0x0010fe80-0x00110000: func_0010fee8 sets it
 * (sceGsDefDispEnv, D_004D8EC0), func_0010ffe0 / func_0010ffb8 apply it,
 * func_0010fea0 the frame scale D_002BBDEC, func_0010ff60 a clear packet;
 * src/screen/display.c has the drawing environment. Read from the
 * code, not proved by a boot (docs/modules.md "Session 55"). */
#include "m2c.h"
#include "data/bss_0049.h"
#include "data/bss_004D.h"
#include "data/pieces/D_002A6238.h"
#include "data/pieces/D_002BC070.h"
#include "common.h"
#include "data/types/text_00100000_h2.h"
#include "data/pieces/D_002B677C.h"
#include "data/pieces/D_002B6778.h"
#include "data/types/text_00100000_h2_p.h"
#include "data/pieces/D_002B75A0.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002B7590.h"
#include "data/pieces/D_002BBAA0.h"
#include "data/pieces/D_002BBD48.h"
#include "data/pieces/D_002BBD90.h"
#include "data/pieces/D_002BC720.h"
#include "data/pieces/D_0048C630.h"
#include "data/pieces/D_0048C690.h"
#include "data/pieces/D_002E2700.h"
#include "data/pieces/D_002E2740.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/pieces/D_002BC140.h"
#include "data/pieces/D_002BC144.h"

/* func_0010fe80 (from auto/text_00100000_2.c). */
void func_0010fe80(void) {
    D_004D9240 = 0;
}

/* func_0010fe90 (from auto/text_00100000_2.c). */
void func_0010fe90(void) {
    D_004D9240 = 1;
}

/* func_0010fea0 (from hand/text_00100000_h2.c). */
extern f32 D_002BBDEC;
extern volatile s32 D_004D90F0;
void func_0010fea0(void) {
    if (D_002BBDEC == 1.0f) D_004D90F0 = 0x14996c4;
    else D_004D90F0 = 0x112a84e;
}

/* func_0010fee8 (from hand/text_00100000_h2.c). */
void FlushCache(s32);
s32 sceGsSyncPath(s32, s32);
typedef struct {
    u64 q[2];
    u32 w16;
    u32 pad;
    u64 q3[2];
} DispEnv;
extern u32 D_004D8EC0[];
void sceGsDefDispEnv(DispEnv *, s16, s16, s16, s16, s16);
void func_00265980(DispEnv *);
#define D_004D8EC0 (*(DispEnv (*)) &D_004D8EC0)
void func_0010fee8(s32 w, s32 h) {
    D_004D90FC = 0;
    sceGsDefDispEnv(&D_004D8EC0, 1, w, h, 0, 0);
    D_004D8EC0.w16 &= ~0x1ff;
    FlushCache(0);
    sceGsSyncPath(0, 0);
    func_00265980(&D_004D8EC0);
}
#undef D_004D8EC0

/* func_0010ff60 (from hand/text_00100000_h2.c). */
void func_00106b18(void *);
extern u64 D_002BC918;
extern u8 D_002BC980[];
void func_0010ff60(s32 a) {
    D_002BC918 = (u64)a | ((u64)a << 8) | ((u64)a << 16) | ((u64)1 << 31) | ((u64)1 << 32);
    func_00106b18(D_002BC980);
    func_0010fee8(512, 447);
}

/* func_0010ffb8 (from auto/text_00100000_9.c). */
void func_0010ffb8(s32 *arg0, s32 *arg1) {
    *arg0 = D_004D8EC0[6] & 0xFFF;
    *arg1 = ((u32) D_004D8EC0[6] >> 0xC) & 0x7FF;
}

/* func_0010ffe0 (from hand/text_00100000_h2.c). */
void func_00265350(s32, s32, s32, s32);
#define D_004D8EC0 (*(DispEnv (*)) &D_004D8EC0)
void func_0010ffe0(void) {
    func_00265350(1, 1, 2, 0);
    *(volatile u64 *)0x120000d0 = 0;
    func_00265980(&D_004D8EC0);
}
#undef D_004D8EC0

