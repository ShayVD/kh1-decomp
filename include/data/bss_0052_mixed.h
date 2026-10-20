/* Shared bss names 0052xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0052_MIXED_H
#define KH1_DATA_BSS_0052_MIXED_H

#include "common.h"
#include "m2c.h"

extern void **D_00524F40;
extern u32 D_00524F44;
extern s32 D_00524F48;
extern s32 D_00524F58[];
extern s32 D_00524F74;
extern s32 D_00524F78;
extern s32 D_00525288;
extern s32 D_00525354;
extern s32 D_00525360;
extern s32 D_00525364;
extern M2C_UNK D_00525368;
extern u8 D_00525A30[];
extern u8 D_0052A100[];
extern u8 D_0052AA58[];
extern s32 D_0052ACF0[2];
extern s32 D_0052AE38;
extern s32 D_0052AE54;
extern void *D_0052AE58;
extern void *D_0052AE5C;
extern void *D_0052AE70[];
extern u32 D_0052CB18;
extern u8 D_0052EB60[];

#endif /* KH1_DATA_BSS_0052_MIXED_H */
