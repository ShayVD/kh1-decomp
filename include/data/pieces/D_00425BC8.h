/* The data piece D_00425BC8 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425BC8_H
#define KH1_DATA_PIECES_D_00425BC8_H

#include "common.h"

typedef struct {
    u8 pad_0[0x4];
    u32 x4;
    s32 x8;
    u8 pad_c[0x4];
    u32 x10;
} PadSt_425bc8;

extern PadSt_425bc8 *D_00425BC8;

#endif /* KH1_DATA_PIECES_D_00425BC8_H */
