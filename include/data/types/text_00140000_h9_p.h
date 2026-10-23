/* More types moved from src/hand/text_00140000_h9.c (phase 4, session 24, tools/shift/type_pieces.py). */
#ifndef KH1_DATA_TYPES_TEXT_00140000_H9_P_H
#define KH1_DATA_TYPES_TEXT_00140000_H9_P_H

#include "common.h"
#include "data/types/text_00140000_h9.h"

/* A 0x20-byte actor state record (D_00350D88[actor's x70], session 31). */
typedef struct {
    u32 f0;      /* flags: & 3 kind, bit 2, bit 3 */
    s32 f4;      /* enter callback (h9 W9Fn) */
    s32 f8;      /* leave callback */
    u8 padc[0x4];
    void *f10;   /* h56 MvFn */
    void *f14;   /* h56 StFn */
    u8 pad18[0x8];
} W9Tab32;

#endif /* KH1_DATA_TYPES_TEXT_00140000_H9_P_H */
