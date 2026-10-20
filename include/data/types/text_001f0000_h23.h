/* Types moved from src/hand/text_001f0000_h23.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001F0000_H23_H
#define KH1_DATA_TYPES_TEXT_001F0000_H23_H

#include "common.h"

typedef struct Obj {
    u8 pad0[12];
    struct Obj *child;
    struct Obj *next;
    u8 pad14[0x40 - 0x14];
    u64 lo:32;
    u64 hi:32;
    u8 pad48[96 - 0x48];
    s32 id;
    u8 pad64[140 - 100];
    s32 state;
    u8 pad90[172 - 144];
    s32 kind;
    s32 pos;
    u8 padb4[184 - 180];
    s16 size;
    u8 padba[240 - 186];
} Obj;

#endif /* KH1_DATA_TYPES_TEXT_001F0000_H23_H */
