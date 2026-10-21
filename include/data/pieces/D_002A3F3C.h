/* The data piece D_002A3F3C (src/data/data_002A.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_002A3F3C_H
#define KH1_DATA_PIECES_D_002A3F3C_H

#include "common.h"

typedef struct {
    s32 o0;
    u32 sz4;
    s32 o8;
    u8 pad_c[0x4];
    s32 o10;
    u8 pad_14[0x4];
    s32 o18;
    u8 pad_1c[0x4];
    s32 o20;
    u32 sz24;
} Hdr_2a3f3c;

extern Hdr_2a3f3c *D_002A3F3C;

#endif /* KH1_DATA_PIECES_D_002A3F3C_H */
