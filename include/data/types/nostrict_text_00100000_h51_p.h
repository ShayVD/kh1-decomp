/* More types moved from src/hand/nostrict/text_00100000_h51.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00100000_H51_P_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00100000_H51_P_H

#include "common.h"
#include "data/types/nostrict_text_00100000_h51.h"

typedef struct { u32 lo:25; u32 f25:1; u32 hi:6; } Bits16;
typedef union { s32 i; u16 h; f32 f; } U12;
typedef struct { u8 pad[12]; U12 u12; Bits16 b16; } Tri20;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00100000_H51_P_H */
