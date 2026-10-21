/* The data piece D_0037A170 (src/data/data_0037.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_0037A170_H
#define KH1_DATA_PIECES_D_0037A170_H

#include "common.h"

typedef struct {
    u8 *ctx;
    s32 arg;
    s32 w8;
    s32 wc;
} RunQ_37a170;

extern RunQ_37a170 *D_0037A170;

#endif /* KH1_DATA_PIECES_D_0037A170_H */
