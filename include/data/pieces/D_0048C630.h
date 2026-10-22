/* The data piece D_0048C630 (src/data/data_0048.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types, session 28 declared the piece with it: the auto user reads
 * x20.v[] where it read s32 [8..11]).  D_0048C690 is a second block of this type. */
#ifndef KH1_DATA_PIECES_D_0048C630_H
#define KH1_DATA_PIECES_D_0048C630_H

#include "common.h"
#include "data/types/text_00110000_h52_p.h"

typedef struct {
    u8 pad_0[0x10];
    s32 x10;
    void *x14;
    s32 x18;
    s32 x1c;
    V4i52 x20;
    u8 pad_30[0x30];
} Blk32_48c630;

extern Blk32_48c630 D_0048C630;

#endif /* KH1_DATA_PIECES_D_0048C630_H */
