/* The data piece D_003DACA0 (src/data/data_003D.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003DACA0_H
#define KH1_DATA_PIECES_D_003DACA0_H

#include "common.h"

typedef struct {
    u8 pad_0[0x4];
    s32 n;
    s32 tbl[1];
} Tbl_3daca0;

extern Tbl_3daca0 *D_003DACA0;

#endif /* KH1_DATA_PIECES_D_003DACA0_H */
