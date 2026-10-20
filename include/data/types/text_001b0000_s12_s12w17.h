/* Types moved from src/hand/text_001b0000_s12_s12w17.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001B0000_S12_S12W17_H
#define KH1_DATA_TYPES_TEXT_001B0000_S12_S12W17_H

#include "common.h"
#include "platform/math.h"

typedef struct {
    struct {
        s32 w0, w4, w8, wC, w10;
        u8 pad14[0x1C];
        f32 a[4];
        f32 b[4];
        f32 an[2];
        u8 pad58[8];
        f32 bn[2];
        u8 pad68[8];
    } s;
} __attribute__((aligned(8))) Lt;
typedef struct { Lt l[2]; } Lt2;

#endif /* KH1_DATA_TYPES_TEXT_001B0000_S12_S12W17_H */
