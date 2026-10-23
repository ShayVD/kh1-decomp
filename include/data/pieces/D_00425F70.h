/* The data piece D_00425F70 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00425F70_H
#define KH1_DATA_PIECES_D_00425F70_H

#include "common.h"

typedef f32 Mtx_425f70[4][4];

/* The camera (session 31: h73's names; h47's func_0021ae28 sets 0x140..0x18c). */
typedef struct {
    Mtx_425f70 m0;
    Mtx_425f70 m40;
    Mtx_425f70 m80;
    Mtx_425f70 mc0;
    Mtx_425f70 m100;
    f32 px, py, pz, pw;     /* 0x140: position */
    f32 tx, ty, tz, tw;     /* 0x150: target */
    f32 v160[4];
    f32 v170[4];
    f32 rx, ry, rz, rw;     /* 0x180 */
    f32 v190[4];
    f32 v1a0[4];
    f32 v1b0[4];
    u8 pad_1c0[0x20];
    s32 x1e0;
    f32 dist;
} Cam_425f70;

extern Cam_425f70 *D_00425F70;

#endif /* KH1_DATA_PIECES_D_00425F70_H */
