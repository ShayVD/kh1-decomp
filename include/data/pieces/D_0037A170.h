/* The data piece D_0037A170 (src/data/data_0037.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_0037A170_H
#define KH1_DATA_PIECES_D_0037A170_H

#include "common.h"

typedef struct {
    u8 *ctx;    /* a task slot's context (D_0037A16C[k].ctx), 0 ends the queue */
    s32 arg;    /* the slot index, -1 at the end */
} RunQ_37a170; /* 8 bytes: h14's func_001bxxxx fills the queue in run order */

extern RunQ_37a170 *D_0037A170;

#endif /* KH1_DATA_PIECES_D_0037A170_H */
