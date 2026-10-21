/* The data piece D_003F2C40 (src/data/data_003F.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_003F2C40_H
#define KH1_DATA_PIECES_D_003F2C40_H

#include "common.h"
#include "m2c.h"

typedef struct { s32 a; s32 b; s32 c; s32 d; u32 e; } S2C40_3F2C40;
typedef struct { u8 pad[16]; s32 x10; } E20_3F2C40;
typedef struct { s32 a; s32 pad[3]; s32 x10; } E20_3F2C40_2;
typedef struct { s32 a; s32 b; s32 c; s32 d; s32 e; } S2C40_3F2C40_2;
typedef union { M2C_UNK i; s8 c; S2C40_3F2C40 s2C40[0x10 / sizeof(S2C40_3F2C40)]; E20_3F2C40 e20[0x10 / sizeof(E20_3F2C40)]; E20_3F2C40_2 e20_2[0x10 / sizeof(E20_3F2C40_2)]; S2C40_3F2C40_2 s2C40_2[0x10 / sizeof(S2C40_3F2C40_2)]; } U003F2C40;

extern U003F2C40 D_003F2C40;

#endif /* KH1_DATA_PIECES_D_003F2C40_H */
