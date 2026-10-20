/* Shared bss names 0066xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0066_MIXED_H
#define KH1_DATA_BSS_0066_MIXED_H

#include "common.h"

extern u8 D_00662300[];
extern s32 D_00662940;
extern u8 D_00668040[];
extern s32 D_00668370[];
extern u8 D_00669350[];
extern u8 D_00669358[];
extern s32 D_00669388[2];
extern s32 D_00669390[8];
extern s32 D_006693B0[8];
extern u8 D_006693D0[];
extern s32 D_00669920;
extern void *D_00669A10[];
extern s32 D_00669A18[8];
extern s16 D_00669A40[];

#endif /* KH1_DATA_BSS_0066_MIXED_H */
