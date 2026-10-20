/* Types moved from src/hand/nostrict/text_00150000_h59.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H59_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H59_H

#include "common.h"
#include "platform/math.h"

typedef struct { f32 a[4], b[4], c[3]; u32 par; } S48_59;
typedef struct { f32 m[4][4]; } M64_59;
typedef struct { s16 n; u8 pad2[2]; S48_59 *src; } Mdl59;
typedef struct {
    void *x0;
    u8 pad4[0x150 - 0x4];
    M64_59 *x150;
    M64_59 *x154;
    M64_59 *x158;
    u8 pad15c[0x170 - 0x15c];
    Mdl59 *x170;
    s32 x174;
    s32 x178;
    s32 x17c;
    void *x180;
    u8 pad184[0x190 - 0x184];
} Ent59;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00150000_H59_H */
