/* The data piece D_002C1260 (src/data/data_002C.s): one declaration its users
 * share (phase 4: session 26 cast at each use, session 28 folded the users' views). */
#ifndef KH1_DATA_PIECES_D_002C1260_H
#define KH1_DATA_PIECES_D_002C1260_H

#include "common.h"

/* the box the collision queries test against: mn[0..2][0] are its minimum x, y, z
 * and mx[0..2][0] its maximum (each a quadword for the VU0 compares) */
typedef struct { f32 mn[3][4]; f32 mx[3][4]; } Box_2c1260;

extern Box_2c1260 D_002C1260;

#endif /* KH1_DATA_PIECES_D_002C1260_H */
