/* The data piece D_00425B80 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425B80_H
#define KH1_DATA_PIECES_D_00425B80_H

#include "common.h"

typedef struct {
    u8 pad_0[0x8];
    s32 x8;
    s32 xc;
    s32 x10;
    u8 name[0x24];
    s32 x38;
} S5B80_425b80;

extern S5B80_425b80 D_00425B80;

#endif /* KH1_DATA_PIECES_D_00425B80_H */
