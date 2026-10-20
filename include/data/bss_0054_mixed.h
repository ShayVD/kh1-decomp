/* Shared bss names 0054xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0054_MIXED_H
#define KH1_DATA_BSS_0054_MIXED_H

#include "common.h"

extern s32 D_00547BA0;
extern s32 D_00547BA4;
extern s32 D_00547BA8;
extern s32 D_00547BAC;
extern u8 D_0054B808[];
extern s32 D_0054C438;
extern u32 D_0054F440;
extern u8 D_0054F970[];

#endif /* KH1_DATA_BSS_0054_MIXED_H */
