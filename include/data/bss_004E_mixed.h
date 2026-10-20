/* Shared bss names 004Exxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_004E_MIXED_H
#define KH1_DATA_BSS_004E_MIXED_H

#include "common.h"
#include "m2c.h"

extern M2C_UNK *D_004E0420;
extern void (*D_004E3430)(void);
extern void (*D_004E3434)(void);
extern s32 D_004E3444;
extern u8 D_004E3A48[];
extern s32 D_004E44C0[];
extern s32 D_004E4520;
extern u8 D_004E49E8[];

#endif /* KH1_DATA_BSS_004E_MIXED_H */
