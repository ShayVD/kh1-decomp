/* Shared bss names 0061xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0061_MIXED_H
#define KH1_DATA_BSS_0061_MIXED_H

#include "common.h"

extern void *D_00615E60;
extern s32 D_00615E64;
extern u8 D_00615EB0[];
extern f32 D_00615F70[4];
extern u8 D_00616040[];
extern u8 D_00616080[];
extern f32 D_006160C0[4][4];
extern u8 D_006161C0[];
extern s32 D_00616214;
extern s32 D_0061621C;
extern s32 D_0061622C;
extern s32 D_00616234;
extern u8 D_0061E720[];
extern u8 D_0061E730[];

#endif /* KH1_DATA_BSS_0061_MIXED_H */
