/* The data piece D_00362434 (src/data/data_0036.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00362434_H
#define KH1_DATA_PIECES_D_00362434_H

#include "common.h"

typedef struct {
    u8 pad_0[0x10];
    f32 x10;
    f32 x14;
    f32 x18;
} CamPt_362434;

extern CamPt_362434 *D_00362434;

#endif /* KH1_DATA_PIECES_D_00362434_H */
