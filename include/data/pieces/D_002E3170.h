/* The data piece D_002E3170 (src/data/data_002E.s): a stack of eight pointers to
 * 0x38-byte menu cursor blocks (D_002E2FD8[7]); D_00524F40 is its top (phase 4:
 * session 26 cast at each use, session 27 folded the users' views of the block,
 * session 28 declared the stack with it; users with another view still cast). */
#ifndef KH1_DATA_PIECES_D_002E3170_H
#define KH1_DATA_PIECES_D_002E3170_H

#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    u32 f8;
    s32 fc;
    s32 n;
    u8 ids[0x20];
    s32 f34;
} Q8_2e3170;

extern Q8_2e3170 *D_002E3170[8];

#endif /* KH1_DATA_PIECES_D_002E3170_H */
