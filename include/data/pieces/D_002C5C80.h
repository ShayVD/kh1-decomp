/* The data piece D_002C5C80 (src/data/data_002C.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002C5C80_H
#define KH1_DATA_PIECES_D_002C5C80_H

#include "common.h"
#include "data/types/fvec.h"

/* 31 light records of 0x40 bytes (session 32: the users' views folded; kind 1
 * ambient, 2 directional, 3 point, 4 spot, 5 ...). */
typedef FVec4 Vec4_2c5c80;

typedef struct {
    s32 kind;
    u32 flags;
    s32 c;
    f32 radius;
    FVec4 pos;
    FVec4 dir;
    Vec4_2c5c80 col;
} Lt64_2c5c80;

extern Lt64_2c5c80 D_002C5C80;

#endif /* KH1_DATA_PIECES_D_002C5C80_H */
