/* The data piece D_003DABD4 (src/data/data_003D.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003DABD4_H
#define KH1_DATA_PIECES_D_003DABD4_H

#include "common.h"

typedef struct {
    u8 pad_0[0x4];
    u8 n;
    u8 pad_5[0x7];
} Tbl_3dabd4;

extern Tbl_3dabd4 *D_003DABD4;

#endif /* KH1_DATA_PIECES_D_003DABD4_H */
