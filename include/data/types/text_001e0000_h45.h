/* Types moved from src/hand/text_001e0000_h45.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001E0000_H45_H
#define KH1_DATA_TYPES_TEXT_001E0000_H45_H

#include "common.h"

typedef struct {
    s32 x0;
    s16 h4, h6, h8, ha, hc, he;
    u8 pad10[0xc];
    f32 f1c;
    u8 pad20[0x10];
    f32 f30, f34;
    u8 pad38[8];
    f32 f40, f44;
    u8 pad48[0x48];
    u8 b90;
    u8 pad91[3];
    f32 f94;
    u8 pad98[0x18];
} Win;

#endif /* KH1_DATA_TYPES_TEXT_001E0000_H45_H */
