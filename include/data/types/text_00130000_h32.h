/* Types moved from src/hand/text_00130000_h32.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00130000_H32_H
#define KH1_DATA_TYPES_TEXT_00130000_H32_H

#include "common.h"

typedef struct {
    s32 id;
    u32 flags;
    s32 x8;
    u8 pad0c[0x4C - 0xC];
    u16 key;
    u8 pad4e[0x58 - 0x4E];
    u8 x58;
    u8 pad59[0x78 - 0x59];
} W32Rec;
typedef struct {
    u8 pad00[0xC];
    s32 n;
    W32Rec *recs;
    s32 x14;
    s32 x18;
    s32 x1c;
    s32 x20;
    s32 x24;
    s32 x28;
    u8 pad2c[0x30 - 0x2C];
} W32Tbl;
typedef struct { s32 x0; s32 x4; s32 x8; } W32E12;

#endif /* KH1_DATA_TYPES_TEXT_00130000_H32_H */
