/* The data piece D_002E31A0 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002E31A0_H
#define KH1_DATA_PIECES_D_002E31A0_H

#include "common.h"

typedef struct {
    u8 pad_0[0xc];
    u16 f0c;
    u16 f0e;
} S31a0_2e31a0;

extern S31a0_2e31a0 *D_002E31A0;

#endif /* KH1_DATA_PIECES_D_002E31A0_H */
