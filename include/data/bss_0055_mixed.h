/* Shared bss names 0055xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0055_MIXED_H
#define KH1_DATA_BSS_0055_MIXED_H

#include "common.h"

extern u8 *D_00551600;
extern s32 *D_005516E4;
extern s32 D_005516EC;
extern s32 D_00559DB0;
extern volatile s32 D_00559DB4;
extern s32 D_0055BDE0;
extern u8 D_0055C698[];

#endif /* KH1_DATA_BSS_0055_MIXED_H */
