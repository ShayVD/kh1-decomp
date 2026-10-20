/* Types moved from src/hand/nostrict/text_00160000_h60.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_H60_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_H60_H

#include "common.h"
#include "platform/math.h"

typedef struct {
    s32 w0; u8 pad4[0x34];
    union { u64 w; struct { u32 lo; u32 *p3C; } s; } w38;
    u64 *p40; u8 pad44[4]; s32 w48; u8 pad4c[0x44]; s32 w90; s32 w94;
} Wk6F3;
typedef struct Node6F { s32 id; s32 mask; s32 (*cb)(void *, Wk6F3 *, s32, s32); s32 arg; struct Node6F *next; } Node6F;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00160000_H60_H */
