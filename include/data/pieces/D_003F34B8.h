/* The data piece D_003F34B8 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003F34B8_H
#define KH1_DATA_PIECES_D_003F34B8_H

#include "common.h"

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fc;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 x1c;
    u8 a[10];
    u8 pad_2a[0x2];
    s32 f2c;
    u32 b48[2];
    u32 b56[1];
    u32 b60[1];
    u32 b64[10];
    u32 b104[1];
    u32 b108[1];
    u32 b112[4];
} S34B8_3f34b8;

extern S34B8_3f34b8 *D_003F34B8;

#endif /* KH1_DATA_PIECES_D_003F34B8_H */
