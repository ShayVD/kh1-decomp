/* More types moved from src/hand/text_00130000_h32.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00130000_H32_P_H
#define KH1_DATA_TYPES_TEXT_00130000_H32_P_H

#include "common.h"
#include "data/types/text_00130000_h32.h"

typedef struct {
    u8 pad00[4];
    u32 x4;
} W32Inf;
typedef struct {
    u8 pad000[0x10];
    f32 x10[4];
    u8 pad020[0x50 - 0x20];
    f32 x50[4];
    u8 pad060[0x88 - 0x60];
    u32 x88;
    u8 pad08c[0x130 - 0x8C];
    W32Inf *x130;
    u8 pad134[0x154 - 0x134];
    s32 x154;
    u8 pad158[0x370 - 0x158];
    u64 x370;
} W32Obj3;

#endif /* KH1_DATA_TYPES_TEXT_00130000_H32_P_H */
