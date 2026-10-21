/* The data piece D_002C58B0 (src/data/data_002C.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002C58B0_H
#define KH1_DATA_PIECES_D_002C58B0_H

#include "common.h"

typedef struct {
    u8 pad_0[0x4];
    f32 y;
    u8 pad_8[0x4];
    f32 w;
} V4D0_2c58b0;

extern V4D0_2c58b0 D_002C58B0;

#endif /* KH1_DATA_PIECES_D_002C58B0_H */
