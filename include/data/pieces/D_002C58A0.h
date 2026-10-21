/* The data piece D_002C58A0 (src/data/data_002C.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002C58A0_H
#define KH1_DATA_PIECES_D_002C58A0_H

#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4_2c58a0;

extern V4_2c58a0 D_002C58A0;

#endif /* KH1_DATA_PIECES_D_002C58A0_H */
