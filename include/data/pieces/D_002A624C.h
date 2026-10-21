/* The data piece D_002A624C (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_002A624C_H
#define KH1_DATA_PIECES_D_002A624C_H

#include "common.h"
#include "data/types/text_00100000_s7_w6.h"

typedef struct {
    f32 x[3];
} Vec3_2a624c;

extern Vtx *D_002A624C;

#endif /* KH1_DATA_PIECES_D_002A624C_H */
