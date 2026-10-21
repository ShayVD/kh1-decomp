/* The data piece D_003F4CF0 (src/data/data_003F.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_003F4CF0_H
#define KH1_DATA_PIECES_D_003F4CF0_H

#include "common.h"
#include "data/types/nostrict_text_00210000_s6_22.h"

typedef struct {
    u16 uv[8];
    s16 w;
    s16 h;
} Spr_3f4cf0;

extern Spr_q0 D_003F4CF0[];

#endif /* KH1_DATA_PIECES_D_003F4CF0_H */
