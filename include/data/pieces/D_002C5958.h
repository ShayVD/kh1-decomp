/* The data piece D_002C5958 (src/data/data_002C.s) and the names inside it: one
 * declaration per name, the largest a user makes (phase 4, session 24,
 * tools/shift/type_pieces.py). Users that agree include this at their end;
 * the others keep their own extern. */
#ifndef KH1_DATA_PIECES_D_002C5958_H
#define KH1_DATA_PIECES_D_002C5958_H

#include "common.h"

/* s6_02's view of the flag word's bits (session 31); other users test masks. */
typedef struct { u32 b0 : 2; u32 b2 : 1; u32 b3 : 24; u32 b27 : 1; u32 r : 4; } Fl_2c5958;

extern u32 D_002C5958;
extern s16 D_002C595A;

#endif /* KH1_DATA_PIECES_D_002C5958_H */
