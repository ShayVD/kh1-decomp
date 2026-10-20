/* Types moved from src/hand/nostrict/text_00140000_s9_w8.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S9_W8_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S9_W8_H

#include "common.h"

typedef struct {
    u32 used : 1;
    u32 state : 2;
    u32 b3 : 1;
    u32 rest : 28;
    s32 x4;
    s32 x8;
    u8 padc[4];
    s32 x10;
    u8 pad14[8];
    s32 x1c;
} Ent9c;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S9_W8_H */
