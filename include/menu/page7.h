/* Page 7 of the menu (docs/modules.md "Session 42"): src/menu/party.c (the
 * party change), save.c / save.nostrict.c (the save and load windows) and
 * page7.c (the page's frame and its list). */
#ifndef KH1_MENU_PAGE7_H
#define KH1_MENU_PAGE7_H

#include "common.h"

/* The TextWin fields (include/text/textwin.h) these windows use, with
 * +0xba / +0xc0 as u16 and +0xd2 as a plain s16. */
typedef struct PtWin {
    u8 pad0[0xc];
    struct PtWin *xc;
    struct PtWin *x10;
    u8 pad14[0x90 - 0x14];
    s32 x90;
    u8 pad94[0xb4 - 0x94];
    s32 xb4;
    u8 padb8[2];
    u16 xba;
    u8 padbc[0xc0 - 0xbc];
    u16 xc0;
    u8 padc2[0xcc - 0xc2];
    s16 xcc, xce;
    u8 padd0[2];
    s16 xd2;
    u8 padd4[0xd8 - 0xd4];
    s16 xd8, xda;
} PtWin;

/* party.c: sets the step of save window D_006436F0 = k (a / b). */
void func_00223980(s32 k, s32 a, s32 b);

#endif /* KH1_MENU_PAGE7_H */
