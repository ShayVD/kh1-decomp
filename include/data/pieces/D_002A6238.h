/* The data piece D_002A6238 (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002A6238_H
#define KH1_DATA_PIECES_D_002A6238_H

#include "common.h"

typedef struct {
    s16 v[4];
    s16 n;
    u8 pad_a[0x2];
    f32 d;
    u32 f;
} Ent20_2a6238;

extern Ent20_2a6238 *D_002A6238;

#endif /* KH1_DATA_PIECES_D_002A6238_H */
