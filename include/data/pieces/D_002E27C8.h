/* The data piece D_002E27C8 (src/data/data_002E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002E27C8_H
#define KH1_DATA_PIECES_D_002E27C8_H

#include "common.h"

typedef struct {
    u32 b0:1;
    u32 b1:1;
    u32 b2:1;
    u32 b3:1;
    u32 b4:1;
    u32 b5:1;
    u32 b6:1;
    u32 b7:1;
    u32 b8:1;
    u32 b9:1;
    u32 b10:3;
    u32 :6;
    u32 b19:3;
    u32 :1;
    u32 b23:1;
    u32 b24:1;
    u32 b25:1;
    u32 b26:1;
    u32 b27:1;
    u32 b28:1;
    u32 b29:1;
    u32 :2;
} C01Flg27C8_2e27c8;

extern C01Flg27C8_2e27c8 D_002E27C8;

#endif /* KH1_DATA_PIECES_D_002E27C8_H */
