/* The data piece D_002BC0C0 (src/data/data_002B.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_002BC0C0_H
#define KH1_DATA_PIECES_D_002BC0C0_H

#include "common.h"

typedef union { u64 d[6]; s32 w[12]; } B48_2BC0C0;
typedef struct { f32 a, b, c, d; s32 e, f, g; s32 h; f32 near_, far_; s32 i, j; } __attribute__((aligned(8))) View30_2BC0C0;
typedef union { B48_2BC0C0 b48; View30_2BC0C0 view30; } U002BC0C0;

extern U002BC0C0 D_002BC0C0;

#endif /* KH1_DATA_PIECES_D_002BC0C0_H */
