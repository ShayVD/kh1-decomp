#include "common.h"

typedef struct { union { u64 x; struct { u64 b0:2; u64 b2:2; u64 r:60; } b; } f; u8 pad8[8]; f32 v10[4]; } Q40;
typedef struct { s32 x0; s32 x4; u8 pad8[0x1c - 8]; f32 f1c; u32 x20; u8 pad24[0x40 - 0x24]; Q40 *x40; } P144;
typedef struct { u8 pad[4]; s32 x4; } X40;
typedef struct { u8 pad[0x4c]; u16 x4c; } C130h;
typedef struct {
    u8 pad0[8];
    s32 x8;
    u8 padc[0x30 - 0xc];
    f32 x30;
    u8 pad34[0x70 - 0x34];
    s32 x70;
    u8 pad74[0x90 - 0x74];
    u64 x90;
    u8 pad98[0x130 - 0x98];
    C130h *x130;
    u8 pad134[0x144 - 0x134];
    P144 *x144;
    u8 pad148[0x2cc - 0x148];
    s32 x2cc;
    u8 pad2d0[0x2dc - 0x2d0];
    u16 x2dc;
} Ah;
extern f32 D_002BBDFC;
void func_00152880(Ah *);
void func_0014aab0(Q40 *);
/* CONTEXT_ONLY copy (src/auto/text_00150000_3.c): its REG_EH_REGION 0 lets reorg fill the bnez slot with li a0,204 */
CONTEXT_ONLY void func_00152648(Ah *a) {
    if (a->x144->x40) {
        func_0014aab0(a->x144->x40);
        a->x144->x40 = 0;
    }
}
void func_00145008(Ah *, s32);
void func_001315c0(Ah *, s32, f32, f32 *);
f32 func_00120c88(f32);
void func_00147138(Ah *, s32);
s32 func_00105c18(s32, u16);

/* func_00152928 (hand/nostrict) */
void func_00152928(Ah *a) {
    P144 *p;
    s32 k;

    a->x144->f1c += D_002BBDFC;
    p = a->x144;
    if (300.0f <= p->f1c) {
        func_00152880(a);
        return;
    }
    if (a->x144->x40) {
        if (((X40 *)a->x144->x40)->x4 == 0) {
            if (a->x130->x4c != 204 && a->x144->x20 != 3) goto set;
            p = 0; /* dead set: kills the gcse PRE copy of p (move a1,a2) for CPROP pass 2 */
            if (a->x90 == 0) goto set;
        }
        func_00152648(a);
        func_00145008(a, 1);
        func_00152880(a);
        return;
    set:
        func_001315c0(a, 0x8003, 0.0f, a->x144->x40->v10);
        a->x144->x40->f.b.b2 = 1;
        p = a->x144;
    } else if (a->x130->x4c == 204 && a->x8) {
        func_00152880(a);
        return;
    }
    if (p->x20 == 3) a->x30 = func_00120c88(a->x30 - D_002BBDFC * 0.2617993727f);
    if (a->x70) return;
    func_00152648(a);
    switch (a->x144->x20) {
    case 0:
        k = 3;
        break;
    case 2:
        k = 1;
        break;
    case 3:
        func_00145008(a, 0);
        func_00152880(a);
        return;
    default:
        k = 2;
        break;
    }
    func_00147138(a, k);
    if ((a->x130->x4c == 204 ? 60.0f : 120.0f) <= a->x144->f1c || func_00105c18(a->x2cc, a->x2dc)) func_00152880(a);

    a->x144->x4 = 0;
}
