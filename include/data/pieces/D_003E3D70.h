/* The data piece D_003E3D70 (src/data/data_003E.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_003E3D70_H
#define KH1_DATA_PIECES_D_003E3D70_H

#include "common.h"

typedef struct { u8 pad[0xe0]; s32 xe0; } S3D70_3E3D70;
typedef struct { u8 b[0xe4]; } E228_3E3D70;
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; s32 x44; s32 x48; u8 pad4c[0xe4 - 0x4c]; } E3D70_3E3D70;
typedef struct { u8 pad[0x40]; s32 x40; u8 p44[4]; s32 x48; s32 x4c; s32 x50; u8 p54[0xE0 - 0x54]; s32 xe0; } Rec_3E3D70;
typedef struct { s32 a, b, c, d; } S4c_3E3D70;
typedef struct { u8 pad[0x40]; S4c_3E3D70 s; u8 pad2[0xe4 - 0x50]; } E3D70c_3E3D70;
typedef struct { s32 a, b, c, d; } S4_3E3D70;
typedef struct { u8 pad0[0x40]; S4_3E3D70 s; u8 pad50[0xe4 - 0x50]; } E3D70_3E3D70_2;
typedef struct {
    u8 pad[0x3c];
    s32 x3c, x40, x44, x48, x4c, x50;
    u8 pad54[0x68 - 0x54];
    s32 x68;
    u8 pad6c[0xe4 - 0x6c];
} E3D70_3E3D70_3;
typedef union { S3D70_3E3D70 s3D70[0xe0 / sizeof(S3D70_3E3D70)]; E228_3E3D70 e228[0xe0 / sizeof(E228_3E3D70)]; E3D70_3E3D70 e3D70[0xe0 / sizeof(E3D70_3E3D70)]; Rec_3E3D70 rec[0xe0 / sizeof(Rec_3E3D70)]; E3D70c_3E3D70 e3D70c[0xe0 / sizeof(E3D70c_3E3D70)]; E3D70_3E3D70_2 e3D70_2[0xe0 / sizeof(E3D70_3E3D70_2)]; E3D70_3E3D70_3 e3D70_3[0xe0 / sizeof(E3D70_3E3D70_3)]; } U003E3D70;

extern U003E3D70 D_003E3D70;

#endif /* KH1_DATA_PIECES_D_003E3D70_H */
