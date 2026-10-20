/* Shared bss names 004Fxxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004F_MIXED_H
#define KH1_DATA_BSS_004F_MIXED_H

#include "common.h"

extern char D_004F2A00[];
extern u32 *D_004F6EB8;
extern f32 D_004F7800[];
extern u8 D_004F82D0[];

#endif /* KH1_DATA_BSS_004F_MIXED_H */
