/* The data piece D_003F34C4 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F34C4_H
#define KH1_DATA_PIECES_D_003F34C4_H

#include "common.h"

typedef struct N_3f34c4 N_3f34c4;

struct N_3f34c4 {
    u8 pad_0[0x10];
    N_3f34c4 *x10;
    u8 pad_14[0x10];
    s32 x24;
    f32 x28;
    u8 pad_2c[0x64];
    s32 x90;
    f32 x94;
    u8 pad_98[0x8];
    f32 xa0;
    u8 pad_a4[0x28];
    s16 xcc;
    u8 pad_ce[0xa];
    s16 xd8;
    u8 pad_da[0x2];
};

extern N_3f34c4 *D_003F34C4;

#endif /* KH1_DATA_PIECES_D_003F34C4_H */
