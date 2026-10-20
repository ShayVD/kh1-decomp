/* Shared bss names 0062xxxx whose users disagree on the type
 * (phase 4, tools/shift/define_shared.py --mixed). Users that agree include
 * this at their end; the others keep their own extern. */
#ifndef KH1_DATA_BSS_0062_MIXED_H
#define KH1_DATA_BSS_0062_MIXED_H

#include "common.h"

extern u8 D_006202A0[];
extern s32 D_00621308[4];
extern s32 *D_00623210;
extern s32 D_0062321C;
extern s32 D_00625640;
extern s32 D_00625648[];
extern u8 *D_006257D0;
extern s32 D_006297F0;
extern s32 D_006297F4;
extern u8 D_006297F8[];
extern u8 D_0062A130[];
extern s32 D_0062A220;
extern s32 D_0062A224;
extern char D_0062A328[];
extern u8 D_0062A428[];
extern u8 D_0062A630[];
extern u8 D_0062F810[];
extern u8 D_0062F840[];
extern u8 D_0062FA00[];
extern s32 D_0062FB00[];
extern s32 D_0062FF00[];

#endif /* KH1_DATA_BSS_0062_MIXED_H */
