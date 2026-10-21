/* The data piece D_003F2270 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F2270_H
#define KH1_DATA_PIECES_D_003F2270_H

#include "common.h"

typedef struct {
    u8 pad_0[0x10];
} Q_3f2270;

extern Q_3f2270 D_003F2270;

#endif /* KH1_DATA_PIECES_D_003F2270_H */
