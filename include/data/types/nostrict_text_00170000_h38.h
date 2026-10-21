/* Types moved from src/hand/nostrict/text_00170000_h38.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00170000_H38_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00170000_H38_H

#include "common.h"

typedef struct Pkt {
    u16 x0;
    u8 x2;
    u8 x3;
    s32 x4;
    u8 pad8[0x68 - 8];
    u64 x68;
    u8 pad70[8];
    u64 x78;
    u8 pad80[0xf0 - 0x80];
    u64 xf0;
    u8 padf8[8];
    u64 x100;
} Pkt;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00170000_H38_H */
