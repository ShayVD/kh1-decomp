/* More types moved from src/hand/nostrict/text_00130000_b03.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_B03_P3_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_B03_P3_H

#include "common.h"
#include "data/types/nostrict_text_00130000_b03_p2.h"
#include "data/types/nostrict_text_00130000_b03.h"
#include "data/types/nostrict_text_00130000_b03_p.h"

typedef struct { u8 pad[0xcc]; f32 xcc; } B3Mv;
typedef struct {
    f32 x0[4];
    f32 x10[4];
    f32 x20[4];
    u8 pad30[0x40 - 0x30];
    f32 x40[4];
    f32 x50;
    f32 x54;
    u8 pad58[0x5c - 0x58];
    s32 x5c;
    u8 pad60[0x90 - 0x60];
    s32 x90;
    s32 x94;
    u8 pad98[0xa0 - 0x98];
    f32 xa0[4];
    f32 xb0, xb4, xb8, xbc;
    u8 padc0[0x100 - 0xc0];
    f32 x100;
    u8 pad104[0x170 - 0x104];
    f32 x170;
} B3Wk;
typedef struct { u8 pad[0x4c]; u16 x4c; } B3Inf;
typedef struct B3Ob {
    u32 x0;
    s32 x4;
    u8 pad08[0x10 - 0x8];
    f32 x10[4];
    f32 x20[4];
    f32 x30[3];
    f32 x3c;
    u8 pad40[0x6c - 0x40];
    B3Mv *x6c;
    u32 x70;
    u8 pad74[0x88 - 0x74];
    u32 x88;
    u8 pad8c[0x98 - 0x8c];
    void *x98;
    u32 x9c;
    u8 padA0[0xc0 - 0xa0];
    f32 xc0[3];
    f32 xcc;
    u8 padd0[0x130 - 0xd0];
    B3Inf *x130;
    u8 pad134[0x144 - 0x134];
    s32 x144;
    B3Wk *x148;
    u8 pad14c[0x150 - 0x14c];
    f32 x150;
    u8 pad154[0x164 - 0x154];
    s32 x164;
    u8 pad168[0x16c - 0x168];
    f32 x16c;
    u8 pad170[0x178 - 0x170];
    s32 x178;
    u8 pad17c[0x1cc - 0x17c];
    u32 x1cc;
    u8 pad1d0[0x280 - 0x1d0];
    f32 x280;
    u8 pad284[0x2a0 - 0x284];
    f32 x2a0[4];
    u8 pad2b0[0x2c0 - 0x2b0];
    f32 x2c0;
    u8 pad2c4[0x2cc - 0x2c4];
    s32 x2cc;
    u32 x2d0;
    f32 x2d4;
    u16 x2d8;
    u8 pad2da[0x2de - 0x2da];
    u16 x2de;
    u8 pad2e0[0x30c - 0x2e0];
    u16 x30c;
    u8 pad30e[0x320 - 0x30e];
    f32 x320[4];
    u8 pad330[0x340 - 0x330];
    f32 x340[4];
    s32 x350[4];
    u8 pad360[0x370 - 0x360];
    u64 x370;
    s32 x378;
    u8 pad37c[0x398 - 0x37c];
    struct B3Ob *x398;
    u8 x39c;
    u8 pad39d;
    u8 x39e;
    u8 pad39f[0x3c0 - 0x39f];
    f32 x3c0[4];
    s32 x3d0;
    u8 pad3d4[0x3e4 - 0x3d4];
    f32 x3e4;
    u16 x3e8;
    u8 pad3ea[0x440 - 0x3ea];
    u64 x440;
    s32 x448;
    u8 pad44c[0x490 - 0x44c];
    f32 x490[4];
    u8 pad4a0[0x4ac - 0x4a0];
    f32 x4ac;
} B3Ob;
typedef struct { B3Ob *x0; s32 x4, x8, xc; } B3Tbl;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00130000_B03_P3_H */
