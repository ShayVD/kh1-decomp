/* Types moved from src/hand/text_00110000_s8_w7.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00110000_S8_W7_H
#define KH1_DATA_TYPES_TEXT_00110000_S8_W7_H

#include "common.h"

typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 b3:1; u32 b4:2; u32 b6:1; u32 r:25; } RoomFl;
typedef struct { s32 x0; s32 x4; s32 x8; s32 xc; RoomFl fl; s32 x14; s32 x18; s32 x1c; s32 x20; s32 x24; s32 x28; s32 x2c; u8 pad[0x10]; } Room;

#endif /* KH1_DATA_TYPES_TEXT_00110000_S8_W7_H */
