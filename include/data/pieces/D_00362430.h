/* The data piece D_00362430 (src/data/data_0036.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00362430_H
#define KH1_DATA_PIECES_D_00362430_H

#include "common.h"

typedef struct {
    u8 pad_0[0x20];
    void *x20;
    s32 x24;
    u8 pad_28[0x8];
} E30_362430;

extern E30_362430 *D_00362430;

#endif /* KH1_DATA_PIECES_D_00362430_H */
