/* The data piece D_002E3170 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_002E3170_H
#define KH1_DATA_PIECES_D_002E3170_H

#include "common.h"
#include "data/types/nofill_text_00230000_h49_p2.h"

typedef struct {
    s32 x0;
    u8 pad_4[0x4];
    u32 f8;
    s32 fc;
    s32 n;
    u8 ids[0x20];
    s32 f34;
} Q8_2e3170;

extern Spr *D_002E3170[];

#endif /* KH1_DATA_PIECES_D_002E3170_H */
