/* The data piece D_0035BD40 (src/data/data_0035.s): one declaration its users
 * share (phase 4, session 26: a union of the users' views; each user names its member). */
#ifndef KH1_DATA_PIECES_D_0035BD40_H
#define KH1_DATA_PIECES_D_0035BD40_H

#include "common.h"
#include "data/types/nostrict_text_00160000_c04.h"

/* the actor pointers: struct Actor is incomplete here; h37 (objBD40) and r2_1
 * (chrEA) complete it with their own views (session 32, as D_002E26A0). */
struct Actor;

typedef struct { u8 pad[8]; f32 f8; } Sub4E3_35BD40;
typedef struct {
    u8 pad0[4]; Sub4E3_35BD40 *p4; u8 pad8[0x30]; u64 w38; u8 pad40[0x64]; f32 fA4; u8 padA8[0x38];
    V4E3 vE0; V4E3 vF0;
} WkE3_35BD40;
typedef struct {
    u8 pad0[0x10]; V4E3 pos; u8 pad20[0x30]; V4E3 x50; u8 pad60[0x10]; s32 x70; u8 pad74[0x5C]; V4E3 xd0;
    u8 padE0[0x64]; WkE3_35BD40 *p144;
} ChrE3_35BD40;
typedef struct { u8 pad[0x10]; f32 f10; u8 pad14[0x28]; s32 w3C; s32 w40; s32 w44; } ChrHp_35BD40;
typedef struct { u8 pad[0x38]; u64 w38; } Wk144_35BD40;
typedef struct { u32 flags; u8 pad4[0xC]; f32 pos[4]; u8 pad20[0x4C]; ChrHp_35BD40 *p6C; s32 w70; u8 pad74[0xD0]; Wk144_35BD40 *p144; } Chr_35BD40;
typedef struct { u8 pad[0x3C]; s32 w3C; s32 w40; } Hp6C_35BD40;
typedef struct { u32 flags; u8 pad4[0x68]; Hp6C_35BD40 *p6C; s32 w70; } Act6C_35BD40;
typedef struct { u8 pad[0x3c]; s32 x3c; s32 x40; s32 x44; s32 x48; } HpB_35BD40;
typedef struct { u32 x0; u8 pad4[0x68]; HpB_35BD40 *x6c; s32 w70; } EntB_35BD40;
typedef struct { u8 pad[0x10]; f32 pos[4]; } Chr9F_35BD40;
typedef union { s32 i; void *vp[0x4]; ChrE3_35BD40 *chrE3[3]; struct Actor *objBD40[0x10 / sizeof(void *)]; Chr_35BD40 *chr[0x10 / sizeof(void *)]; struct Actor *chrEA[3]; Act6C_35BD40 *act6C[0x10 / sizeof(void *)]; EntB_35BD40 *entB[0x10 / sizeof(void *)]; Chr9F_35BD40 *chr9F[0x10 / sizeof(void *)]; s32 i_2[0x4]; } U0035BD40;

extern U0035BD40 D_0035BD40;

#endif /* KH1_DATA_PIECES_D_0035BD40_H */
