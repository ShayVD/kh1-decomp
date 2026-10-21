/* The data piece D_003F7ED0 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F7ED0_H
#define KH1_DATA_PIECES_D_003F7ED0_H

#include "common.h"

typedef struct {
    u8 pad_0[0xda];
    s16 xda;
    s16 xdc;
    s16 xde;
    u8 buf[1];
    u8 pad_e1[0x1];
} S7ED0_3f7ed0;

extern S7ED0_3f7ed0 D_003F7ED0;

#endif /* KH1_DATA_PIECES_D_003F7ED0_H */
