/* The data piece D_003E8E08 (src/data/data_003E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_003E8E08_H
#define KH1_DATA_PIECES_D_003E8E08_H

#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} S4_3e8e08;

extern s32 D_003E8E08[0x8];

#endif /* KH1_DATA_PIECES_D_003E8E08_H */
