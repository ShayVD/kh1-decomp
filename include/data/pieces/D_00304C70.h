/* The data piece D_00304C70 (src/data/data_0030.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00304C70_H
#define KH1_DATA_PIECES_D_00304C70_H

#include "common.h"

typedef struct St6C_304c70 St6C_304c70;
typedef struct S1C8_304c70 S1C8_304c70;

struct St6C_304c70 {
    u32 flags;
    u8 pad_4[0x38];
    s32 w3c;
    s32 w40;
    s32 x44;
    s32 w48;
    u8 pad_4c[0x72];
    u16 xbe;
    u8 pad_c0[0x8];
    S1C8_304c70 *pc8;
};

struct S1C8_304c70 {
    u8 pad_0[0x1];
    u8 b1;
    u8 pad_2[0x1];
    u8 b3;
    u8 pad_4[0x34];
    s16 x38;
};

extern St6C_304c70 D_00304C70;

#endif /* KH1_DATA_PIECES_D_00304C70_H */
