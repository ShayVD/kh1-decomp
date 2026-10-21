/* The data piece D_002BC0F0 (src/data/data_002B.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_002BC0F0_H
#define KH1_DATA_PIECES_D_002BC0F0_H

#include "common.h"
#include "data/pieces/D_002BC0C0.h"

typedef struct { f32 f0; f32 f4; u8 pad[8]; s32 f10; s32 f14; s32 f18; } Cam_2BC0F0;
typedef struct { f32 f0, f4, f8, fC; s32 w10, w14, w18; } S2BC0F0_2BC0F0;
typedef struct { u8 pad[0x10]; s32 x10, x14, x18; } S2BC0F0_2BC0F0_2;
typedef struct { f32 f0, f4, f8, fc; s32 i10, i14, i18; s32 pad; f32 f20, f24; } Cam0_2BC0F0;
typedef struct { f32 a[4]; s32 b[3]; } CamS_2BC0F0;
typedef union { B48_2BC0C0 b48; s32 i[0xc]; Cam_2BC0F0 cam; S2BC0F0_2BC0F0 s2BC0F0; S2BC0F0_2BC0F0_2 s2BC0F0_2; View30_2BC0C0 view30; Cam0_2BC0F0 cam0; CamS_2BC0F0 camS; f32 f[0xc]; } U002BC0F0;

extern U002BC0F0 D_002BC0F0;

#endif /* KH1_DATA_PIECES_D_002BC0F0_H */
