/* Types moved from src/hand/text_001a0000_h13.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001A0000_H13_H
#define KH1_DATA_TYPES_TEXT_001A0000_H13_H

#include "common.h"
#include "data/types/shared.h"

typedef union GsTag {
    u128 q;
    struct { u32 w0; union GsTag *next; union GsTag *tail; u32 w3; } s;
} GsTag;

#endif /* KH1_DATA_TYPES_TEXT_001A0000_H13_H */
