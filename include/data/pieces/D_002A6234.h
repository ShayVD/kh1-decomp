/* The data piece D_002A6234 (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002A6234_H
#define KH1_DATA_PIECES_D_002A6234_H

#include "common.h"

typedef struct {
    f32 x0;
    u8 pad_4[0x4];
    f32 cw;
    s32 nx;
    u8 pad_10[0x10];
    f32 z0;
    u8 pad_24[0x4];
    f32 ch;
    s32 nz;
} Grid_2a6234;

extern Grid_2a6234 *D_002A6234;

#endif /* KH1_DATA_PIECES_D_002A6234_H */
