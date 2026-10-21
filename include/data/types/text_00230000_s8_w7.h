/* Types moved from src/hand/text_00230000_s8_w7.c (phase 4, tools/shift/type_move.py). */
#ifndef KH1_DATA_TYPES_TEXT_00230000_S8_W7_H
#define KH1_DATA_TYPES_TEXT_00230000_S8_W7_H

#include "common.h"

typedef struct { s32 x0; s32 x4; u8 pad8[0x3C - 8]; } R60;
typedef struct R64 { u8 pad[0x2D]; u8 x2d; u8 x2e; u8 pad2f[0x40 - 0x2F]; } R64;
typedef struct {
    s32 x0;
    s32 x4;
    u8 pad8[0x38];
    R64 rec[65];
    u8 pad1080[0x10C0 - 0x1080];
    union { R64 *tbl[52][10]; R64 *tbl1[520]; };
    u8 pad[0x1900 - 0x10C0 - 52 * 40];
    s32 flag[99];
    s32 n;
    R60 r[99];
} St;

#endif /* KH1_DATA_TYPES_TEXT_00230000_S8_W7_H */
