/* More types moved from src/hand/text_00170000_h38.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00170000_H38_P_H
#define KH1_DATA_TYPES_TEXT_00170000_H38_P_H

#include "common.h"
#include "data/types/text_00170000_h38.h"

typedef struct { f32 x, y, z, len; } Seg;
typedef struct Path {
    s32 n;          /* 0x00 */
    u8 pad4[4];
    f32 x8;         /* 0x08 */
    u8 padc[8];
    f32 x14;        /* 0x14 */
    s32 flags;      /* 0x18 */
    u8 pad1c[4];
    Seg seg[1];     /* 0x20 */
} Path;

#endif /* KH1_DATA_TYPES_TEXT_00170000_H38_P_H */
