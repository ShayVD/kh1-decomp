/* The data piece D_00425F70 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425F70_H
#define KH1_DATA_PIECES_D_00425F70_H

#include "common.h"

typedef struct {
    u8 pad_0[0x1a0];
    f32 v1a0[4];
    u8 pad_1b0[0x10];
} Cam_425f70;

extern Cam_425f70 *D_00425F70;

#endif /* KH1_DATA_PIECES_D_00425F70_H */
