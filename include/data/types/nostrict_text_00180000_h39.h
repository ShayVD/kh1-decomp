/* Types moved from src/hand/nostrict/text_00180000_h39.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H39_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H39_H

#include "ppp.h"

typedef struct {
    s32 unk00, unk04;
    s32 off08, off0C;
    s16 unk10, unk12, unk14;
} H39Tex;
typedef struct {
    s32 a, b, c;
    s32 pad0C, pad10;
    void *p14, *p18;
    H39Tex *tex;
    s32 unk20;
} H39Slot;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00180000_H39_H */
