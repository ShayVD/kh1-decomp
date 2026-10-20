/* Shared bss names 0063xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0063_MIXED_H
#define KH1_DATA_BSS_0063_MIXED_H

#include "common.h"

extern u8 D_006303B0[];
extern u8 D_006304E0[];
extern u8 D_00630510[];
extern s32 D_006305CC;
extern char D_006307C8[];
extern char D_00630FC8[];
extern s8 D_006314C8;
extern u32 D_00633640[2048];
extern u8 D_0063F640[256];
extern u8 *D_0063F744;
extern u16 *D_0063F748;

#endif /* KH1_DATA_BSS_0063_MIXED_H */
