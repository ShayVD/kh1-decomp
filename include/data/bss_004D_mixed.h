/* Shared bss names 004Dxxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004D_MIXED_H
#define KH1_DATA_BSS_004D_MIXED_H

#include "common.h"

extern s32 D_004D5AF4;
extern f32 D_004D5AFC;
extern u32 D_004D5B00;
extern u32 D_004D5B08;
extern u8 D_004D6B10[];
extern s32 D_004D8EC0[];
extern volatile s32 D_004D90F0;
extern volatile s32 D_004D90F4;
extern s32 D_004D9250;
extern s32 D_004D9258;
extern s32 D_004D925C;
extern void *D_004D92DC;
extern s32 D_004D9320;
extern u32 D_004D9330;
extern s32 D_004D9364;

#endif /* KH1_DATA_BSS_004D_MIXED_H */
