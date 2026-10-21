/* The data piece D_002E31B0 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002E31B0_H
#define KH1_DATA_PIECES_D_002E31B0_H

#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
} S31b0_2e31b0;

extern S31b0_2e31b0 D_002E31B0;

#endif /* KH1_DATA_PIECES_D_002E31B0_H */
