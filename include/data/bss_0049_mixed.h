/* Shared bss names 0049xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0049_MIXED_H
#define KH1_DATA_BSS_0049_MIXED_H

#include "common.h"

extern u8 D_00494320[];
extern s32 D_00494410[2];
extern u8 D_004945E0[];
extern u8 D_00494878[];
extern f32 D_00494890;
extern f32 D_004948B0[4][4];
extern f32 D_004948F0[4][4];
extern volatile f32 D_00494A70;
extern f32 D_00494A88;
extern s32 D_00494AA0[32];
extern s32 D_00494B20[32];
extern u8 D_004951D0[];
extern u8 D_00495210[];
extern s32 D_00495250;

#endif /* KH1_DATA_BSS_0049_MIXED_H */
