/* The data piece D_003F1E70 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F1E70_H
#define KH1_DATA_PIECES_D_003F1E70_H

#include "common.h"

typedef struct {
    u8 pad_0[0x10];
} Q_3f1e70;

extern Q_3f1e70 D_003F1E70;

#endif /* KH1_DATA_PIECES_D_003F1E70_H */
