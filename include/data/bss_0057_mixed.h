/* Shared bss names 0057xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0057_MIXED_H
#define KH1_DATA_BSS_0057_MIXED_H

#include "common.h"

extern s32 D_005739F8[];
extern u8 D_00573AC0[];
extern s32 D_00575010;
extern f32 D_00575090[40][4];
extern void *D_00575780;
extern void *D_00575784;
extern u8 D_00575788[8];
extern s32 D_00575890;
extern void *D_00575894;
extern f32 D_005758C4;
extern f32 D_005758D0[4];
extern f32 D_005758E0[4];
extern u8 D_00575A00[];

#endif /* KH1_DATA_BSS_0057_MIXED_H */
