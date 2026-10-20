/* Types moved from src/hand/nostrict/text_00240000_h75.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00240000_H75_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00240000_H75_H

#include "common.h"

typedef struct {
    s32 unk0;
    u8 pad4[4];
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    u8 pad28[0x30 - 0x28];
    u8 unk30[0x300];
    u8 unk330[0x180];
    u8 unk4B0[0x480];
    u8 unk930[0x9F0 - 0x930];
    f32 unk9F0;
    void *unk9F4;
    void *unk9F8;
    u8 pad9FC[4];
} Ent;
typedef struct { s32 cnt[4]; Ent e[3][5]; s32 stamp[3]; s32 frame; } Tbl;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00240000_H75_H */
