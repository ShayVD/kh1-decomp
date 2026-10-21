/* The data piece D_002E2780 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_002E2780_H
#define KH1_DATA_PIECES_D_002E2780_H

#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V3_2e2780;

extern f32 D_002E2780[0x4];

#endif /* KH1_DATA_PIECES_D_002E2780_H */
