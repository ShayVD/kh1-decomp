/* The data piece D_003626C0 (src/data/data_0036.s): one declaration its users
 * share (phase 4, session 26: users whose own type differs cast at each use). */
#ifndef KH1_DATA_PIECES_D_003626C0_H
#define KH1_DATA_PIECES_D_003626C0_H

#include "common.h"
#include "data/types/fvec.h"

/* the camera blend start / end points (h61 func_0017b200 sets them, h11
 * func_0017b170 copies them back once flag is set) */
typedef struct { FVec4 a; FVec4 b; s32 flag; } Blk26C0;

extern Blk26C0 D_003626C0;

#endif /* KH1_DATA_PIECES_D_003626C0_H */
