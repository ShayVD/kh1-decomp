/* Types moved from src/hand/text_00110000_h29.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00110000_H29_H
#define KH1_DATA_TYPES_TEXT_00110000_H29_H

#include "common.h"

typedef struct { s32 f, s, m, h; } W29Time;
typedef struct {
    s32 x0, x4, x8, xc, x10, x14, x18, x1c, x20, x24, x28, x2c, x30;
    W29Time t[2];
} W29Clock;

#endif /* KH1_DATA_TYPES_TEXT_00110000_H29_H */
