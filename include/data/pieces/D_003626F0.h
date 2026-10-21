/* The data piece D_003626F0 (src/data/data_0036.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003626F0_H
#define KH1_DATA_PIECES_D_003626F0_H

#include "common.h"

typedef struct {
    s32 x0;
    f32 x4;
} S26F0_3626f0;

extern S26F0_3626f0 D_003626F0;

#endif /* KH1_DATA_PIECES_D_003626F0_H */
