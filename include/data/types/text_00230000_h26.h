/* Types moved from src/hand/text_00230000_h26.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00230000_H26_H
#define KH1_DATA_TYPES_TEXT_00230000_H26_H

#include "common.h"

typedef struct { s32 used; s32 age; u8 pad8[0x30 - 8]; u8 a[0xc0]; u8 b[0xc0]; u8 c[0x780]; } Fx; /* a 0x930-byte effect slot (D_0045FAC0[10]; h50 reads a / b / c) */

#endif /* KH1_DATA_TYPES_TEXT_00230000_H26_H */
