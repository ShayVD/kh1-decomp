/* 0x00230000-0x0024FFFF game code by hand (batch 49), delay-slot filling off. */
#include "common.h"
#include "data/bss_0064.h"

typedef struct { u8 pad[0x60]; u64 unk60; u8 pad68[0xE0-0x68]; u64 unkE0; u8 tail[0x160 - 0xE8]; } Q;
#include "data/types/nofill_text_00230000_h49_p2.h"
extern s32 D_00651BD0;
#include "data/types/nofill_text_00230000_h49_p.h"

#include "data/types/nofill_text_00230000_h49.h"
void func_0024aa48(s32, Pkt *, s32);
s32 func_002388b8(Pkt *, s32, s32);
extern u8 D_00454558[], D_00454570[], D_00454580[], D_00454598[], D_004545B0[], D_004545C8[], D_004545E0[], D_004545F8[];
void func_0024afc0(void *, void *, s32);

void func_0023cfe8(u8 *o, s32 k, s32 a) {
    switch (k) {
    case 0:
        break;
    case 1:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        break;
    case 2:
        func_0024afc0(D_004545B0, o + 0x18, a);
        func_0024afc0(D_004545E0, o + 0x28, a);
        func_0024afc0(D_004545C8, o + 0x3C, a);
        break;
    case 3:
        func_0024afc0(D_00454558, o, a);
        func_0024afc0(D_004545F8, o + 0x14, a);
        func_0024afc0(D_00454570, o + 0x18, a);
        func_0024afc0(D_00454580, o + 0x28, a);
        func_0024afc0(D_00454598, o + 0x3C, a);
        break;
    }
}
Pkt D_00651D70 ALIGNED(16);

s32 func_0023d700(s32 a0, s32 a1, s32 x, s32 y, s32 q, f32 s) {
    s32 i;
    s32 *p;
    s32 dx, dy;
    func_0024aa48(a0, &D_00651D70, a1);
    dx = x * 16;
    dy = y * 16;
    p = &D_00651D70.p[0].y;
    for (i = 0; i < 4; i++) {
        p[-1] += dx;
        *p += dy;
        p += 4;
    }
    for (i = 0; i < 4; i++) {
        D_00651D70.c[i].w = D_00651D70.c[i].w * s;
    }
    return func_002388b8(&D_00651D70, 1, q);
}

/* needs make: uses rodata */
extern s32 D_00651BD0;
#include "data/data_002E.h"
#include "data/data_0045.h"
