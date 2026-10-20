/* Types moved from src/hand/nostrict/text_00230000_s6_24.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_NOSTRICT_TEXT_00230000_S6_24_H
#define KH1_DATA_TYPES_NOSTRICT_TEXT_00230000_S6_24_H

#include "common.h"

typedef struct { u64 b[24]; } Spr570;
typedef struct { u8 pad[0x40]; Spr570 s0; Spr570 s1; s32 x1c0; u8 pad1c4[0x1d0 - 0x1c4]; } Ob570;
typedef struct { u64 d[24]; } B192;
typedef struct { s32 a, b; } P8;
typedef struct { s32 used, x4, x8, pad; B192 blk; s32 xd0, xd4; P8 xd8; } Slot;

#endif /* KH1_DATA_TYPES_NOSTRICT_TEXT_00230000_S6_24_H */
