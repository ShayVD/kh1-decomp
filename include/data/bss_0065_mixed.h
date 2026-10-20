/* Shared bss names 0065xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0065_MIXED_H
#define KH1_DATA_BSS_0065_MIXED_H

#include "common.h"

extern s32 D_00651200;
extern u8 *D_00651204;
extern u8 *D_006512F0;
extern u8 *D_006512F4;
extern u8 *D_006512F8;
extern u8 *D_006512FC;
extern u8 *D_00651300;
extern s32 D_006560E0;
extern s32 D_00656420;

#endif /* KH1_DATA_BSS_0065_MIXED_H */
