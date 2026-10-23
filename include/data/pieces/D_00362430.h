/* The data piece D_00362430 (src/data/data_0036.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00362430_H
#define KH1_DATA_PIECES_D_00362430_H

#include "common.h"
#include "data/types/fvec.h"

/* A 0x30-byte camera box (session 31: b06's Box): the table D_00362430
 * points to, and the current one D_0036243C. */
typedef struct {
    FVec4 min;
    FVec4 max;
    void *x20;      /* the box's camera path */
    s32 x24;
    u8 pad_28[0x8];
} E30_362430;

extern E30_362430 *D_00362430;

#endif /* KH1_DATA_PIECES_D_00362430_H */
