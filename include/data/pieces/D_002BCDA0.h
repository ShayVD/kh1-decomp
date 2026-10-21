/* The data piece D_002BCDA0 (src/data/data_002B.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_002BCDA0_H
#define KH1_DATA_PIECES_D_002BCDA0_H

#include "common.h"
#include "data/types/text_00110000_s8_w7.h"

typedef struct {
    s32 id;
    u8 pad_4[0xc];
    f32 v[3][4];
} Ent40_2bcda0;

extern Room *D_002BCDA0;

#endif /* KH1_DATA_PIECES_D_002BCDA0_H */
