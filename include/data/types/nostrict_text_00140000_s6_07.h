/* Types moved from src/hand/nostrict/text_00140000_s6_07.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S6_07_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S6_07_H

#include "common.h"

typedef  struct Nea98 {
    u16 x0;
    u8 pad2[6];
    struct Nea98 *x8;
    s32 (*volatile xc)(struct Nea98 *);
} Nea98;
typedef struct { u8 pad[8]; Nea98 *x8; s32 xc; u8 buf[0x4000]; } Beb78;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00140000_S6_07_H */
