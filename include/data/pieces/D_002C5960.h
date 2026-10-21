/* The data piece D_002C5960 (src/data/data_002C.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002C5960_H
#define KH1_DATA_PIECES_D_002C5960_H

#include "common.h"

typedef struct {
    u32 :2;
    u32 b:1;
    u32 :29;
} Fl5960_2c5960;

extern Fl5960_2c5960 D_002C5960;

#endif /* KH1_DATA_PIECES_D_002C5960_H */
