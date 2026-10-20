/* Types moved from src/hand/nostrict/text_00180000_h40.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H40_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H40_H

#include "common.h"
#include "ppp.h"

#include "data/types/shared.h"
typedef struct {
    f32 pos[3];
    f32 dist;   /* +0xC */
    u8 pad10[8];
    u64 flags;  /* +0x18 */
} PppLight;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H40_H */
