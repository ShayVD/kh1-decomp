/* The data piece D_00362438 (src/data/data_0036.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00362438_H
#define KH1_DATA_PIECES_D_00362438_H

#include "common.h"

typedef struct {
    f32 x, y, z;    /* the segment's start point */
    f32 len;
} Seg_362438;

typedef struct {
    s32 n;
    f32 x4;
    f32 x8;
    f32 xc;
    f32 x10;
    f32 x14;        /* speed (h38: x14 * dt) */
    s32 x18;        /* flags: 1 loops, 0x10 */
    u8 x1c;
    u8 pad_1d[0x3];
    Seg_362438 seg[1];
} Path_362438;

extern Path_362438 *D_00362438;

#endif /* KH1_DATA_PIECES_D_00362438_H */
