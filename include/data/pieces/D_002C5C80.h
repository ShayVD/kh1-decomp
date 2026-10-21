/* The data piece D_002C5C80 (src/data/data_002C.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002C5C80_H
#define KH1_DATA_PIECES_D_002C5C80_H

#include "common.h"

typedef struct {
    f32 v[4];
} Vec4_2c5c80;

typedef struct {
    s32 kind;
    s32 b;
    s32 c;
    u8 pad_c[0x24];
    Vec4_2c5c80 v;
} Lt64_2c5c80;

extern Lt64_2c5c80 D_002C5C80;

#endif /* KH1_DATA_PIECES_D_002C5C80_H */
