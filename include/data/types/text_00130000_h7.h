/* Types moved from src/hand/text_00130000_h7.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00130000_H7_H
#define KH1_DATA_TYPES_TEXT_00130000_H7_H

#include "common.h"

typedef struct {
    u8 pad00[0xC];
    s8 c;
    s8 d;
    s8 e;
    s8 f;
} W7Pad;
typedef struct W7Ob W7Ob;
struct W7Ob {
    u32 flags;
    u8 pad004[0x10 - 0x4];
    f32 x10[4];
    f32 x20[4];
    f32 x30[4];
    u8 pad040[0x6C - 0x40];
    void *x6c;
    s32 x70;
    u8 pad074[0x148 - 0x74];
    void *x148;
    W7Pad *x14c;
    u8 pad150[0x200 - 0x150];
    f32 x200[4];
    u8 pad210[0x2F0 - 0x210];
    f32 x2f0[4];
    f32 x300;
    u8 pad304[0x3B0 - 0x304];
    f32 x3b0;
    f32 x3b4;
    u8 pad3b8[0x3C0 - 0x3B8];
    f32 x3c0[4];
    s32 x3d0;
};
typedef struct {
    s32 (*fn)(W7Ob *, s32);
    u8 pad[0x1C];
} W7Fn;

#endif /* KH1_DATA_TYPES_TEXT_00130000_H7_H */
