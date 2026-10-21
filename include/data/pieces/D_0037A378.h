/* The data piece D_0037A378 (src/data/data_0037.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_0037A378_H
#define KH1_DATA_PIECES_D_0037A378_H

#include "common.h"

typedef struct {
    u32 b0:1;
    u32 b1:1;
    u32 b2:1;
    u32 b3:1;
    u32 b4:1;
    u32 b5:1;
    u32 :26;
} Bits_37a378;

extern s32 D_0037A378;

#endif /* KH1_DATA_PIECES_D_0037A378_H */
