/* The data piece D_002BC0A8 (src/data/data_002B.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_002BC0A8_H
#define KH1_DATA_PIECES_D_002BC0A8_H

#include "common.h"

typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 b3:1; u32 b4:1; u32 b5:1; u32 rest:26; } Flags_2BC0A8;
typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 b3:1; u32 b4:1; u32 rest:27; } Flags_2BC0A8_2;
typedef struct { u32 b0:1; u32 b1:1; u32 b2:1; u32 rest:29; } Flags_2BC0A8_3;
typedef struct { u32 b0:2; u32 b2:1; u32 b3:1; u32 r:28; } Fl0A8_2BC0A8;
typedef union { s32 i; u32 u; Flags_2BC0A8 flags; Flags_2BC0A8_2 flags_2; Flags_2BC0A8_3 flags_3; Fl0A8_2BC0A8 fl0A8; } U002BC0A8;

extern U002BC0A8 D_002BC0A8;

#endif /* KH1_DATA_PIECES_D_002BC0A8_H */
