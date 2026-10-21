/* The data piece D_003E8E28 (src/data/data_003E.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast). */
#ifndef KH1_DATA_PIECES_D_003E8E28_H
#define KH1_DATA_PIECES_D_003E8E28_H

#include "common.h"

typedef struct {
    u16 code;
    u16 f2;
    u16 f4;
    u8 w;
    u8 f7;
} Glyph_3e8e28;

extern Glyph_3e8e28 *D_003E8E28;

#endif /* KH1_DATA_PIECES_D_003E8E28_H */
