/* The data piece D_00308CDC (src/data/data_0030.s): one struct its
 * users share (phase 4: session 26 cast at each use, session 27 folded the users'
 * views into these types; users not folded still cast, and the folded ones cast to it: the declaration
 * keeps its type because other users' code needs it). */
#ifndef KH1_DATA_PIECES_D_00308CDC_H
#define KH1_DATA_PIECES_D_00308CDC_H

#include "common.h"

typedef struct { u8 a, b; } Cfg8Pr_308cdc;
typedef struct { u16 a, b; } Cfg16Pr_308cdc;

typedef struct {
    u8 pad_0[0x10];
    u8 lim0;
    u8 lim1;
    u8 pad_12[0x2];
    u16 h14;
    u16 h16;
    f32 f18;
    u8 pad_1c[0x4];
    f32 f20;
    f32 f24;
    f32 x28;
    f32 x2c;
    f32 x30;
    f32 x34;
    u8 pad_38[0x8];
    Cfg8Pr_308cdc t[10];   /* 0x40: per kind (an actor's x130->x4c), h31 */
    Cfg16Pr_308cdc e[10];  /* 0x54: per kind, c01 */
    u8 x7c[0xc];           /* 0x7c: per kind, h58 (* 60 frames) */
    f32 f88;
    u8 pad_8c[0x4];
    f32 x90;
    u8 f94;
    u8 f95;
    u16 f96;
    u8 pad_98[0x50];
    f32 fe8;
    u8 pad_ec[0x4];
    f32 ff0;
    u16 hF4[1];
    u8 pad_f6[0x8];
    u8 xfe;
} Cfg_308cdc;

extern void *volatile D_00308CDC;

#endif /* KH1_DATA_PIECES_D_00308CDC_H */
