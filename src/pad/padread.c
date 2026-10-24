/* The pads. Platform code (docs/portability.md: libpad2 and libdbc calls;
 * the Vita build replaces this file): func_0011fa88 opens the two pad
 * sockets (sceDbcInit, scePad2Init, scePad2CreateSocket), func_0011f668
 * reads the buttons each frame (scePad2GetButtonProfile into D_004E44C8),
 * func_0011f370 the analog sticks, func_0011f548 / func_0011f628 the repeat
 * and the stick state, func_0011f988 resets the pad state and the repeat
 * timings D_002C5C20-D_002C5C2C, func_0011fad0 / func_0011fb00 the
 * performance counter (scePcStart). Flag mode: default (the other modes are
 * in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/thread.h"
#include "platform/pad.h"
#include "data/bss_004F.h"
#include "data/types/text_00110000_h53_p.h"
#include "platform/math.h"
#include "data/pieces/D_002BBDE0.h"
#include "data/types/text_00110000_h4_p.h"
#include "data/pieces/D_002C5968.h"
#include "data/bss_004E.h"
#include "data/types/text_00110000_h30.h"
#include "data/pieces/D_002C5910.h"
#include "data/pieces/D_002BC140.h"
#include "data/types/text_00110000_h30_p.h"
#include "data/pieces/D_002C58D0.h"
#include "data/pieces/D_002C58B0.h"
#include "m2c.h"
#include "data/pieces/D_002BCB60.h"
#include "data/pieces/D_002C1260.h"
#include "data/pieces/D_002BBDF4.h"
#include "vm/script_vm.h"

/* func_0011f370 (from hand/text_00110000_h53.c). */
extern f32 D_002C5980[4];
extern f32 D_002C5C20;
f32 func_00120bf8(void *);
void func_002673b8(void *, void *);
void func_00267560(void *, void *, f32);
s32 func_0011f370(V53 *st, u8 *pad) {
    s32 bits = 0;
    s32 s, j;
    f32 v, len;
    V53 *d = st;
    for (s = 0; s < 2; s++) {
        for (j = 0; j < 2; j++) {
            v = (f32)pad[s * 2 + 2 + j] - 127.5f;
            D_002C5980[j] = v;
            if (v > 0.0f) {
                D_002C5980[j] = v - D_002C5C20;
                if (D_002C5980[j] < 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 1) << (s * 8 + 21 - j);
                }
            } else {
                D_002C5980[j] = v + D_002C5C20;
                if (D_002C5980[j] > 0.0f) {
                    D_002C5980[j] = 0.0f;
                } else {
                    bits |= ((j * 5) ^ 4) << (s * 8 + 21 - j);
                }
            }
            D_002C5980[j] = D_002C5980[j] / (127.5f - D_002C5C20);
        }
        len = func_00120bf8(D_002C5980);
        if (len > 1.0f) len = 1.0f;
        func_002673b8(&d[5], D_002C5980);
        d[5].w = 1.0f;
        func_00267560(&d[3], &d[5], len);
        d++;
    }
    return bits;
}

/* func_0011f628 (from hand/text_00110000_h4.c). */
extern MaskEnt D_002C5990[];
u32 func_0011f628(u32 m) {
    u32 r = 0;
    u32 i;
    for (i = 0; i < 30; i++) {
        if ((m & D_002C5990[i].mask) == D_002C5990[i].mask) r |= D_002C5990[i].val;
    }
    return r;
}

/* func_0011f988 (from hand/text_00110000_h30.c). */
typedef struct {
    u16 active;
    u8 x2;
    u8 x3;
    u32 cur;
    u32 press;
    u32 release;
    u32 rep;
    u32 rep2;
    s32 x18;
    s32 t1;
    s32 t2;
    u8 pad24[12];
    V4 a[2];
    V4 b[2];
} PadState;
extern s32 D_002C5C24;
extern s32 D_002C5C28;
void func_002675a8(f32 *, f32 *);
extern s32 D_002C5C2C;
extern PadState D_002C5AD0[2];
extern PadState D_002C5BB0;
void func_0011f988(void) {
    s32 i, j;
    PadState *p;
    D_002C5C20 = 60.0f;
    D_002C5C24 = 30;
    D_002C5C28 = 4;
    D_002C5C2C = 32;
    for (i = 0; i < 2; i++) {
        p = &D_002C5AD0[i];
        p->rep = 0;
        p->press = 0;
        p->cur = 0;
        p->active = 0;
        p->x3 = 0;
        p->x2 = 0;
        for (j = 0; j < 2; j++) {
            func_002675a8(p->a[j], &D_002C58B0.x);
            func_002675a8(p->b[j], &D_002C58B0.x);
        }
    }
    D_002C5BB0.rep = 0;
    D_002C5BB0.press = 0;
    D_002C5BB0.cur = 0;
    D_004E4280 = 0;
    D_004E44F0 = 0;
}

/* func_0011fa88 (from auto/text_00110000_6.c). */
extern M2C_UNK D_002C5A88;
M2C_UNK D_004E42C0[0x80] ALIGNED(64);
extern u32 D_004E44C0; /* u32: the int socket number converts on the store, as in the original */
void func_0011fa88(void) {
    PlatDbcInit();
    PlatPadInit(0);
    D_004E44C0 = PlatPadCreateSocket(&D_002C5A88, &D_004E42C0);
}

/* func_0011fad0 (from auto/text_00110000_6.c). */
s32 func_0011fad0(void) {
    PlatPcStart(0x8000F8DE, 0, 0);
    return 0;
}

/* func_0011fb00 (from auto/text_00110000_2.c). */
void *func_0011ef10(M2C_UNK, M2C_UNK (*)());
#define func_0011fad0 ((M2C_UNK (*)()) func_0011fad0)
void func_0011fb00(void) {
    func_0011fad0();
    M2C_FIELD(func_0011ef10(0x2710, func_0011fad0), s16 *, 2) = -1;
}
#undef func_0011fad0

