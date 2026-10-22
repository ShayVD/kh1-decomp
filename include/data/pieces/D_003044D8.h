/* The data piece D_003044D8 (src/data/data_0030.s): the 16-byte collision entries,
 * D_003044D0 of them (phase 4, session 28: one record type its users share; x0 is
 * the entry's matrix, x4 its model data, x8 the owner).  The records run on past
 * the piece (split_check groups). */
#ifndef KH1_DATA_PIECES_D_003044D8_H
#define KH1_DATA_PIECES_D_003044D8_H

#include "common.h"

typedef struct { u32 b0 : 1; u32 mask : 8; u32 rest : 23; } ColFlags_3044d8;
typedef struct { s32 x0; u8 *x4; s32 x8; ColFlags_3044d8 flags; } ColEnt_3044d8;

extern ColEnt_3044d8 D_003044D8[];

#endif /* KH1_DATA_PIECES_D_003044D8_H */
