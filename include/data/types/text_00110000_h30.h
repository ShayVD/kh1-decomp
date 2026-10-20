/* Types moved from src/hand/text_00110000_h30.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00110000_H30_H
#define KH1_DATA_TYPES_TEXT_00110000_H30_H

#include "common.h"

typedef struct { s32 a, b; } Pair;
typedef f32 V4[4] __attribute__((aligned(16)));
typedef struct TNode { u16 flags; u16 mask; s32 key; struct TNode *next; s32 (*fn)(struct TNode *); } TNode;
typedef struct { u16 size; u16 count; u8 *base; TNode *head; TNode *cur; } TPool;

#endif /* KH1_DATA_TYPES_TEXT_00110000_H30_H */
