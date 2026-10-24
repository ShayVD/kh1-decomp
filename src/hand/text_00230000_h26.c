/* 0x00230000-0x0024FFFF game code by hand (batch 26). */
#include "common.h"

/* Five 0xD00-byte slots, each with an in-use flag. */
/* The current record, then the queue of pending ones. */

/* Three rows of five 0xA00-byte cells, with a used count per row. */

/* Ten 0x860-byte channels: a free one, else the oldest. */

/* Splits x into five 300-wide steps, halved. */

/* Ten 0x930-byte slots: a free one, else the oldest. */
#include "data/types/text_00230000_h26.h"
void func_002474e8(s32, void *, s32, s32, f32);
void func_002474e8(s32, void *, s32, s32, f32);

/* Needs func_002486c8/func_00248738 defined above it. */

/* Steps a fade by speed*dt (unless paused): 2 when it reaches 0, 1 when it
 * reaches 128. */

typedef struct {
    u64 lo : 20;
    u64 f20 : 6;
    u64 mid : 30;
    u64 f56 : 5;
    u64 f61 : 3;
} Tag;
typedef struct { u8 pad[0x18]; u64 unk18; } Src;
void func_0024a6b8(Tag *, void *, u64);
void func_0024aa48(void *a, Tag *t, Src *s) {
    func_0024a6b8(t, a, s->unk18);
    t->f56 = 0;
    t->f61 = 1;
    t->f20 = 0x13;
}

/* Runs func_0024e0f0 with the globals at 0x0046A03C..0x0046A048 loaded from a
 * parameter block; the ones at +0x40 and +0x48 are restored after. */
typedef struct { s32 unk0, unk4, unk8, unkC, unk10, unk14, unk18; } Prm;
extern Prm *D_00669A18[8]; /* src/data/bss_0066.c: s32 D_00669A18[8] */
#include "data/pieces/D_0046A040.h"
extern s32 D_0046A048;
#include "data/pieces/D_0046A044.h"
#include "data/pieces/D_0046A03C.h"
void func_0024e0f0(s32, s32, s32);
void func_0024b228(s32 i, s32 a, s32 b, s32 c) {
    Prm *p = D_00669A18[i];
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}
void func_0024b6d0(Prm *p, s32 a, s32 b, s32 c) {
    s32 o40, o48, t10, t18;
    D_0046A03C = p->unkC;
    o40 = D_0046A040;
    o48 = D_0046A048;
    t10 = p->unk10;
    (*(s32 *)&D_0046A044) = p->unk14;
    t18 = p->unk18;
    D_0046A040 = t10;
    D_0046A048 = t18;
    func_0024e0f0(a, b, c);
    D_0046A040 = o40;
    D_0046A048 = o48;
}

s32 func_0024b778(s32 n) {
    s32 a = n * 32;
    a += n * 0x10320;
    return (a + 1511) & ~63;
}

/* needs make: uses rodata */
#include "data/data_0046.h"
#include "data/data_0045.h"
