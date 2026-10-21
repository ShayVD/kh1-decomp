/* Types moved from src/hand/text_001c0000_b10.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001C0000_B10_H
#define KH1_DATA_TYPES_TEXT_001C0000_B10_H

#include "common.h"
#include "platform/math.h"

typedef f32 Vec[4] __attribute__((aligned(16)));
typedef struct {
    u32 bf0:4, b4:1, b5:1, b6:1, b7:1, b8:1, bf9:23;
    f32 dur[4];
    f32 x14;
    f32 t[4];
    f32 x28;
    u32 mode[4];
    u8 pad3c[4];
    Vec p0[3];
    Vec p1[3];
    f32 amp[3];
    s32 smode;
    f32 sdur;
    f32 st;
    u8 padb8[8];
    Vec base;
    Vec pos;
    Vec rot;
    f32 rx, ry, rz;
    u8 padfc[4];
    Vec v100;
    Vec v110;
    f32 f120;
    f32 f124;
    f32 f128;
} __attribute__((aligned(16))) CamS;

#endif /* KH1_DATA_TYPES_TEXT_001C0000_B10_H */
