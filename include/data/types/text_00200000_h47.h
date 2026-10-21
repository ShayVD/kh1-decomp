/* Types moved from src/hand/text_00200000_h47.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00200000_H47_H
#define KH1_DATA_TYPES_TEXT_00200000_H47_H

#include "common.h"

typedef struct { u8 pad[0xcc]; s32 active; } E3530;
typedef struct { E3530 e[3]; u8 pad[0x33c - 0x270]; s32 x33c; } S3530;
typedef struct { u8 pad[0x64]; u16 x64; } S90a0;
typedef struct { u8 pad[0x10]; s32 x10; } S5C30;

#endif /* KH1_DATA_TYPES_TEXT_00200000_H47_H */
