/* Types moved from src/hand/text_00110000_h3.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00110000_H3_H
#define KH1_DATA_TYPES_TEXT_00110000_H3_H

#include "common.h"

typedef struct {
    s32 id;
    s32 x4;
    s32 x8;
    s32 handle;
    s32 x10;
    u8 active;
    u8 x15;
    u8 kind;
    u8 x17;
} SndSlot;
typedef struct {
    s32 x0, x4, x8;
} Slot12;

#endif /* KH1_DATA_TYPES_TEXT_00110000_H3_H */
