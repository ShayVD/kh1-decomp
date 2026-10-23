/* Types moved from src/hand/nostrict/text_00120000_b02.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_B02_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_B02_H

#include "common.h"
#include "data/types/fvec.h"

typedef FVec4 V4;
typedef struct { u8 p0[0x14]; u32 f14; } G15;
typedef struct { u8 p0[8]; u64 d8; } E15;
typedef struct O15 {
    u32 f0;
    u8 p4[4];
    s32 f8;
    u8 pc[0x2c - 0xc];
    s32 f2c;
    u8 p30[0x88 - 0x30];
    u32 f88;
    s32 f8c;
    u8 p90[0x120 - 0x90];
    V4 f120;
    u8 p130[0x14c - 0x130];
    void *f14c;
    u64 p150[(0x370 - 0x150) / 8];
    u32 w370;
    u32 b32 : 1;
    u32 b33 : 1;
    u32 b34 : 1;
    u32 b35 : 4;
    u32 b39 : 1;
    u32 b40 : 24;
    u8 p378[0x3e4 - 0x378];
    f32 f3e4;
    u8 p3e8[4];
    E15 *f3ec;
    u8 p3f0[0x408 - 0x3f0];
    void (*f408)(struct O15 *, void *);
    u8 p40c[0x440 - 0x40c];
    void *f440;
    u8 p444[0x488 - 0x444];
    G15 *f488;
} O15;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00120000_B02_H */
