/* The data piece D_00449908 (src/data/data_0044.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00449908_H
#define KH1_DATA_PIECES_D_00449908_H

#include "common.h"

typedef struct {
    s32 cur;
    s32 t[6];
    s32 a[6];
    s32 p[12];
    s32 b[6];
    f32 f7c;
    f32 f80;
} Cam_449908;

extern Cam_449908 D_00449908;

#endif /* KH1_DATA_PIECES_D_00449908_H */
