/* The data piece D_00425B80 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425B80_H
#define KH1_DATA_PIECES_D_00425B80_H

#include "common.h"

/* A 0x3c-byte save header record (session 31): x0 / x4 are the magic
 * 0x5153484B and 0x01317F14 (src/auto/text_00230000_3.c), s6_g2's SvF and
 * s8_w7's R60 records have the same layout. */
typedef struct {
    s32 x0;
    s32 x4;
    s32 x8;
    s32 xc;
    s32 x10;
    u8 name[0x24];
    s32 x38;
} S5B80_425b80;

extern S5B80_425b80 D_00425B80;

#endif /* KH1_DATA_PIECES_D_00425B80_H */
