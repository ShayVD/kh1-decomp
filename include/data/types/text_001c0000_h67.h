/* Types moved from src/hand/text_001c0000_h67.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_001C0000_H67_H
#define KH1_DATA_TYPES_TEXT_001C0000_H67_H

#include "common.h"

#include "data/pieces/D_002BC0F0.h"
typedef CamS_2BC0F0 CamS;
typedef struct { u8 st[4]; u8 x4[12]; u16 tbl[8][256]; s32 cnt[8]; s8 ids[4]; u8 pad1034[0x3034 - 0x1034]; s32 f3034; s32 f3038; u8 pad303c[0x3070 - 0x303c]; union { u64 x; s32 i[2]; } f3070; union { u64 x; s32 i[2]; } f3078; u8 pad3080[0x14]; s32 f3094; u8 pad3098[0x316c - 0x3098]; s32 f316c; u8 pad3170[0x3460 - 0x3170]; f32 dur; f32 t; u8 pad3468[8]; CamS start; CamS tgt; } Str;

#endif /* KH1_DATA_TYPES_TEXT_001C0000_H67_H */
