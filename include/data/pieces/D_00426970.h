/* The data piece D_00426970 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00426970_H
#define KH1_DATA_PIECES_D_00426970_H

#include "common.h"

typedef struct {
    u8 pad_0[0x4440];
} Tex4440_426970;

extern Tex4440_426970 D_00426970;

#endif /* KH1_DATA_PIECES_D_00426970_H */
