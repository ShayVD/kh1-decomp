/* Shared bss names 0063xxxx (phase 4, tools/shift/define_shared.py). */
#ifndef KH1_DATA_BSS_0063_H
#define KH1_DATA_BSS_0063_H

#include "common.h"

extern u8 D_00630300_rec[] __asm__("D_00630300"); /* a window record of 0xb0 bytes (MsgWin) */
#define D_00630380 (D_00630300_rec + 0x80) /* its text, MsgWin.f80 */
extern s32 D_006314CC;
extern s32 D_006314D0;
extern s32 D_006314D4;
extern s32 D_006314D8;
extern s32 D_006314DC;
extern s32 D_00631560;
extern s32 D_0063F540;

#endif /* KH1_DATA_BSS_0063_H */
