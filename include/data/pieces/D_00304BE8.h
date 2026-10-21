/* The data piece D_00304BE8 (src/data/data_0030.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_00304BE8_H
#define KH1_DATA_PIECES_D_00304BE8_H

#include "common.h"

typedef struct {
    u8 pad_0[0x36];
    u8 x36;
    u8 pad_37[0x457];
    u8 x48e[16];
    u8 pad_49e[0xfb];
    u8 x599[48];
    u8 pad_5c9[0x207];
    s8 f7d0[7];
    u8 pad_7d7[0x67];
    u16 x83e;
    u8 pad_840[0x8];
    u16 cnt[1];
    u8 pad_84a[0x2a];
    u32 f874;
    u8 pad_878[0x8];
    u8 f880;
    u8 pad_881[0x3];
} S4BE8_304be8;

extern S4BE8_304be8 *D_00304BE8;

#endif /* KH1_DATA_PIECES_D_00304BE8_H */
