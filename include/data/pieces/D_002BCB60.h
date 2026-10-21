/* The data piece D_002BCB60 (src/data/data_002B.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002BCB60_H
#define KH1_DATA_PIECES_D_002BCB60_H

#include "common.h"

typedef struct {
    u8 pad_0[0x20];
} V32_2bcb60;

typedef struct {
    f32 m[1][4];
    s32 w10[12];
    s32 w40;
    s32 w44;
    s32 w48;
    V32_2bcb60 blk;
    u8 flags[234];
    u8 pad_156[0x2];
    s32 w158;
    s32 w15c;
} Ctx_2bcb60;

extern Ctx_2bcb60 *D_002BCB60;

#endif /* KH1_DATA_PIECES_D_002BCB60_H */
