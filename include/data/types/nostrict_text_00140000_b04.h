/* Types moved from src/hand/nostrict/text_00140000_b04.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_B04_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_B04_H

#include "common.h"
#include "platform/math.h"

typedef struct {
    u16 x0; u8 x2; u8 x3; s32 x4; u8 pad8[0x20 - 8]; u64 x20; u8 pad28[8]; u64 x30; u8 pad38[8]; u64 x40;
    u8 pad48[0x60 - 0x48]; union { u64 x; struct { u64 lo:15; u64 r:49; } b; } x60; u8 pad68[8];
    u16 x70; u8 x72; u8 x73; s32 x74; u8 pad78[8];
} B4Pk;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_B04_H */
