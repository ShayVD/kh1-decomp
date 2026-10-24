/* 0x00230000-0x0024FFFF game code by hand (batch 26), built without
 * strict aliasing. */
#include "common.h"

#include "data/types/nostrict_text_00230000_h26.h"

/* 0xC0-byte records found by index from a header offset. */
typedef struct { u64 a; s32 unk8; u8 pad[0xC0 - 12]; } Blk;
typedef struct { s32 unk0; s32 unk4; s32 off; } Hdr;
extern s32 D_00669A18[8];

void func_0024af40(s32 *idx, Blk *out, Hdr *h) {
    Blk *base = (Blk *)((u8 *)h + h->off);
    for (; *idx != -1; idx++, out++)
        *out = base[*idx];
}

void func_0024afc0(s32 *idx, Blk **out, Hdr *h) {
    Blk *base = (Blk *)((u8 *)h + h->off);
    while (*idx != -1)
        *out++ = &base[*idx++];
}

void func_0024b1f0(void) {
    s32 i;
    for (i = 0; i < 8; i++) D_00669A18[i] = 0;
}
#include "data/bss_0066_mixed.h"
