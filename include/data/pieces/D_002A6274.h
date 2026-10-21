/* The data piece D_002A6274 (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002A6274_H
#define KH1_DATA_PIECES_D_002A6274_H

#include "common.h"

typedef struct {
    u8 pad_0[0x10];
    s32 w16;
} Ent20b_2a6274;

extern Ent20b_2a6274 *D_002A6274;

#endif /* KH1_DATA_PIECES_D_002A6274_H */
