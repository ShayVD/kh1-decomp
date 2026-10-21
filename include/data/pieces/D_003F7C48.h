/* The data piece D_003F7C48 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_003F7C48_H
#define KH1_DATA_PIECES_D_003F7C48_H

#include "common.h"
#include "data/types/faddr_text_00230000_s7.h"

typedef struct {
    u16 id;
    u8 b2;
    u8 n;
    u8 flag;
    u8 pad_5[0x1];
} T7C48_3f7c48;

extern E6 D_003F7C48[];

#endif /* KH1_DATA_PIECES_D_003F7C48_H */
