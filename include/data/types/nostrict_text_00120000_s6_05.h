/* Types moved from src/hand/nostrict/text_00120000_s6_05.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_S6_05_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_S6_05_H

#include "common.h"

typedef struct { f32 x, y, z, w; } V4D;
typedef struct { u8 p0[0xc]; u32 fc; u8 p10[0x28 - 0x10]; s32 f28; } PD;
typedef struct QD {
    u32 used:1;
    u32 b1:1;
    u32 k:2;
    u32 b4:28;
    s32 f4;
    union { struct { s32 f8; u32 fc; } w; struct { u32 lo; u32 c0:5; u32 c5:7; u32 n:4; u32 c16:16; } b; u64 d; } u8;
    V4D f10;
    s32 f20;
    s32 seq;
    u32 mask;
    PD *f2c;
    struct QD *next;
    s32 f34;
    s32 f38;
    u8 p3c[4];
} QD;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_S6_05_H */
