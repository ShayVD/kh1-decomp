/* The data piece D_003701D0 (src/data/data_0037.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003701D0_H
#define KH1_DATA_PIECES_D_003701D0_H

#include "common.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} FV4_3701d0;

extern FV4_3701d0 D_003701D0;

#endif /* KH1_DATA_PIECES_D_003701D0_H */
