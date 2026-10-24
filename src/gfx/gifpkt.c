/* GIF packet helpers: func_0011fb38 one A+D register write, func_0011fb48 /
 * func_0011fb78 a packet's tag and end, func_0011fbb0 an image upload (the
 * transfer registers and the image data's tag). Flag mode: default (the
 * other modes are in the sibling files). Read from the code, not proved by a
 * boot (docs/modules.md "Session 54"). */
#include "m2c.h"
#include "data/bss_004D.h"
#include "data/bss_004E.h"
#include "data/pieces/D_002BC0A8.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002BCDAC.h"
#include "data/pieces/D_002BD118.h"
#include "data/pieces/D_002A6C60.h"
#include "data/pieces/D_002AA060.h"
#include "data/pieces/D_002B1C60.h"
#include "data/pieces/D_002A3F50.h"
#include "common.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h53_p.h"

/* func_0011fb38 (from auto/text_00110000.c). */
void *func_0011fb38(s64 arg0, s64 arg1, void *arg2) {
    M2C_FIELD(arg2, s64 *, 0) = arg1;
    M2C_FIELD(arg2, s64 *, 8) = arg0;
    return arg2 + 0x10;
}

/* func_0011fb48 (from auto/text_00110000_13.c). */
void func_0011fb48(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s64 *, 8) = 0xE;
    M2C_FIELD(arg0, s64 *, 0) = (s64) ((((s32) (arg2 - arg0) >> 4) - 1) | ((s64) arg1 << 0xF) | ((s64) 0x8000 << 0x2D));
}

/* func_0011fb78 (from hand/text_00110000_h4.c). */
typedef struct { u64 a, b; } Q128;
void func_0011fb78(Q128 *p, u64 a1, Q128 *end) {
    u64 v = (end - p - 1) | (a1 << 28);
    if ((u32)end > 0x6fffffff) v |= 0x8000000000000000;
    *(u64 *)p = v;
}

/* func_0011fbb0 (from hand/text_00110000_h53.c). */
typedef struct { u64 a, b; } Q53;
#define func_0011fb38 ((Q53 *(*)(s32, u64, Q53 *)) func_0011fb38)
#define func_0011fb48 ((void (*)(Q53 *, s32, Q53 *)) func_0011fb48)
#define func_0011fb78 ((void (*)(Q53 *, s32, Q53 *)) func_0011fb78)
Q53 *func_0011fbb0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, u32 a7, s32 a8, Q53 *buf) {
    Q53 *p, *r, *t;
    t = buf + 1;
    p = func_0011fb38(0x50, (u64)a0 << 32 | (u64)a1 << 48 | (u64)a2 << 56, buf + 2);
    p = func_0011fb38(0x51, (u64)a3 << 32 | (u64)a4 << 48, p);
    p = func_0011fb38(0x52, (u64)a5 | (u64)a6 << 32, p);
    p = func_0011fb38(0x53, 0, p);
    func_0011fb48(t, 0, p);
    t = p;
    p++;
    t->a = (u64)a7 | 0x8000ULL << 44;
    func_0011fb78(buf, 1, p);
    r = p;
    p++;
    r->a = (u64)(a7 | 0x30000000) | (u64)a8 << 32;
    r = p++;
    t = p++;
    p = func_0011fb38(63, 0, p);
    func_0011fb48(t, 1, p);
    func_0011fb78(r, 7, p);
    return r;
}
#undef func_0011fb38
#undef func_0011fb48
#undef func_0011fb78

