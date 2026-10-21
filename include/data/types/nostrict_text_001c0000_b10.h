/* Types moved from src/hand/nostrict/text_001c0000_b10.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_001C0000_B10_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_001C0000_B10_H

#include "common.h"

typedef struct {
    s32 x0, x4;
    u8 pad8[0x68];
    s8 *code;
    s32 n;
    s32 x78;
    s32 lbl[64];
    s32 pc;
    s32 sp;
    s32 stk[91];
    s32 x2f0;
    s32 x2f4;
    s32 ret[8];
    s32 rsp;
    u8 pad31c[0xc];
    u32 b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1, b8:1, b9:1, brest:22;
    u8 pad32c[0x24];
} __attribute__((aligned(8))) VM;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_001C0000_B10_H */
