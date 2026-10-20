/* Types moved from src/hand/nostrict/text_00140000_h57.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H57_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H57_H

#include "common.h"

typedef struct Slot57_15d0 Slot57_15d0;
typedef struct {
    s32 flags;
    u8 pad4[0x10-4];
    f32 v10[4];
    f32 f20;
    f32 f24;
    f32 f28;
    u8 pad2c[0x40-0x2c];
    f32 f40;
    f32 f44;
    f32 f48;
    u8 pad4c[0x144-0x4c];
    Slot57_15d0 *slot;
} Obj57_15d0;
struct Slot57_15d0 {
    s32 x0;
    Obj57_15d0 *obj;
    void *owner;
    u8 padc[0x20-0xc];
    f32 f20;
    f32 f24;
    s32 age;
    s32 x2c;
    f32 f30;
    s32 x34;
    u8 pad38[0x40-0x38];
};

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_H57_H */
