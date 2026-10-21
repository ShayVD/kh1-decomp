/* The data piece D_00425F70 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425F70_H
#define KH1_DATA_PIECES_D_00425F70_H

#include "common.h"

typedef f32 Mtx_425f70[4][4];

typedef struct {
    u8 pad_0[0x40];
    Mtx_425f70 m40;
    Mtx_425f70 m80;
    u8 pad_c0[0x40];
    Mtx_425f70 m100;
    u8 pad_140[0x60];
    f32 v1a0[4];
    f32 v1b0[4];
} Cam_425f70;

extern Cam_425f70 *D_00425F70;

#endif /* KH1_DATA_PIECES_D_00425F70_H */
