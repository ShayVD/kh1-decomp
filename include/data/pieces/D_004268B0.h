/* The data piece D_004268B0 (src/data/data_0042.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_004268B0_H
#define KH1_DATA_PIECES_D_004268B0_H

#include "common.h"

typedef struct {
    u64 unk18;
} TexBits_4268b0;

typedef struct {
    u8 pad_0[0x18];
    TexBits_4268b0 tb;
    u8 pad_20[0x10];
} Tex_4268b0;

extern Tex_4268b0 D_004268B0;

#endif /* KH1_DATA_PIECES_D_004268B0_H */
