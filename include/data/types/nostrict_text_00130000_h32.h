/* Types moved from src/hand/nostrict/text_00130000_h32.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_H32_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_H32_H

#include "common.h"

typedef struct { u64 a, b, c, d; } W32V32;
typedef struct W32Node {
    s32 used;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    W32V32 v;
    u8 pad30[0x50 - 0x30];
    struct W32Node *prev;
    struct W32Node *next;
    u8 pad58[0x60 - 0x58];
} W32Node;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_H32_H */
