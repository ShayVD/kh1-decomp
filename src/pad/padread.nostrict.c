/* The pads. Platform code (docs/portability.md: libpad2 and libdbc calls;
 * the Vita build replaces this file): func_0011fa88 opens the two pad
 * sockets (sceDbcInit, scePad2Init, scePad2CreateSocket), func_0011f668
 * reads the buttons each frame (scePad2GetButtonProfile into D_004E44C8),
 * func_0011f370 the analog sticks, func_0011f548 / func_0011f628 the repeat
 * and the stick state, func_0011f988 resets the pad state and the repeat
 * timings D_002C5C20-D_002C5C2C, func_0011fad0 / func_0011fb00 the
 * performance counter (scePcStart). Flag mode: nostrict (the other modes are
 * in the sibling files). Read from the code, not proved by a boot
 * (docs/modules.md "Session 54"). */
#include "common.h"
#include "platform/vu.h"
#include "platform/pad.h"
#include "data/pieces/D_002C5968.h"
#include "data/pieces/D_002C5910.h"
#include "data/bss_004E.h"
#include "data/bss_004F.h"
#include "data/types/nostrict_text_00110000_s6_04_p.h"
#include "data/pieces/D_002C5960.h"
#include "data/pieces/D_002C58B0.h"

/* func_0011f548 (from hand/nostrict/text_00110000_h30.c). */
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
extern s32 D_002C5C28;
extern s32 D_002C5C24;
extern f32 D_002BBDFC;
void func_0011f548(PadState *p, u32 b) {
    u32 old = p->cur;
    u32 x, pr;
    p->rep2 = 0;
    p->rep = 0;
    p->release = 0;
    p->press = 0;
    p->cur = b;
    if (p->active == 0) return;
    pr = (old ^ b) & b;
    p->release = (old ^ b) & ~b;
    p->press = pr;
    if (pr) {
        s32 t = D_002C5C24;
        p->t2 = t;
        p->t1 = t;
        p->rep2 = pr;
        p->rep = pr;
        return;
    }
    if (b == 0) return;
    p->t1 = p->t1 - D_002BBDFC;
    p->t2 = p->t2 - D_002BBDFC;
    if (p->t1 <= 0.0f) {
        s32 t = D_002C5C28;
        p->rep = b;
        p->t1 = t;
    }
    if (p->t2 <= 0.0f) {
        p->rep2 = b;
        p->t2 = 0;
    }
}

/* func_0011f668 (from hand/nostrict/text_00110000_s6_04.c). */
typedef struct { u8 x0[2]; u8 x2; u8 pad[17]; } Prof;
extern s16 D_002C597A;
extern PadSt D_002C5AD0[];
extern PadSt D_002C5BB0;
extern s32 D_004E44C0[];
Prof D_004E44C8[0x2] ALIGNED(8);  /* moved from hand/nostrict/text_00110000_s6_04.c (session 54) */
extern u8 D_002C5A80[];
s32 func_0011f370(PadSt *, u8 *);
u32 func_0011f628(u32);
s32 func_00219348(void);
void func_0011fec0(void);
#define func_0011f548 ((void (*)(PadSt *, s32)) func_0011f548)
void func_0011f668(void) {
    u8 buf[256];
    s32 vib;
    s32 i;
    PadSt *p;
    s32 btn;
    u16 act;
    { s32 m = (*(volatile Sema_2c5968 *)&D_002C5968).mode; if (m) return; }
    (*(volatile Sema_2c5968 *)&D_002C5968).b0 = 0;
    i = 0;
    goto top;
body:
    if (p->active == 0 && PlatPadGetButtonProfile(D_004E44C0[i], &D_004E44C8[i]) < 0) goto join;
    if (PlatPadRead(D_004E44C0[i], buf) >= 0) {
        btn = (buf[0] | (buf[1] << 8)) ^ 0xffff;
        if ((D_004E44C8[i].x2 & 0xf) == 0xf) btn |= func_0011f370(p, buf);
        if (func_00219348() == 0 && !(D_002C597A & 1)) {
            { u32 t = p->b3 << 1; vib = (u32)p->b2 >> 31; vib |= t; }
            PlatVibSetActParam(D_004E44C0[i], 1, D_002C5A80, 2, &vib);
        }
        p->b3 = 0;
        act = 1;
        p->b2 = 0;
    }
    goto join;
top:
    p = &D_002C5AD0[i ^ D_004E4280];
    act = 0;
    btn = 0;
    if (PlatPadGetState(D_004E44C0[i]) == 1) goto body;
join:
    func_0011f548(p, btn);
    i++;
    p->active = act;
    if (i <= 0) goto top;
    if (D_002C5AD0[D_004E4280].active != 1) {
        if (D_004E44F0 >= 31) (*(volatile Sema_2c5968 *)&D_002C5968).b0 = 1;
        else D_004E44F0++;
    } else {
        D_004E44F0 = 0;
    }
    if (D_002C5960.b) {
        D_002C5BB0.active = 0;
        PlatVu0CopyVector(&D_002C5BB0.v[0], &D_002C58B0);
        PlatVu0CopyVector(&D_002C5BB0.v[1], &D_002C58B0);
        PlatVu0CopyVector(&D_002C5BB0.v[2], &D_002C58B0);
        PlatVu0CopyVector(&D_002C5BB0.v[3], &D_002C58B0);
        func_0011f548(&D_002C5BB0, 0);
    } else {
        PlatVu0CopyVector(&D_002C5BB0.v[0], &D_002C5AD0[0].v[0]);
        PlatVu0CopyVector(&D_002C5BB0.v[1], &D_002C5AD0[0].v[1]);
        PlatVu0CopyVector(&D_002C5BB0.v[2], &D_002C5AD0[0].v[2]);
        PlatVu0CopyVector(&D_002C5BB0.v[3], &D_002C5AD0[0].v[3]);
        func_0011f548(&D_002C5BB0, func_0011f628(D_002C5AD0[0].x4));
        D_002C5BB0.active = 1;
    }
    func_0011fec0();
}
#undef func_0011f548

