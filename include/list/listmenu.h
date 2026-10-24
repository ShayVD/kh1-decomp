/* The list menu (src/list/listmenu.c, docs/modules.md "Session 44"). */
#ifndef KH1_LIST_LISTMENU_H
#define KH1_LIST_LISTMENU_H

#include "common.h"

/* What func_002329a0 shows (src/list/list.c fills D_003DC498): n entries,
 * their text, the title, and the window's corners in GS coordinates
 * (x0 y0 x1 y1, 16 units a pixel from 0x7000 / 0x7400).  0x684 bytes, as
 * the other files declare it. */
typedef struct {
    s32 n;
    char str[50][32];
    char last[32];          /* 0x644: the title */
    u32 a, b, c, d;         /* 0x664 */
    u8 pad674[0x10];
} ListMenu;

/* The window descriptor D_003F7EA0 (a TextWinDesc, include/text/textwin.h;
 * this view stops at the fields func_002329a0 sets, inside the 0x24-byte
 * data piece). */
typedef struct { u8 pad[0xC]; s16 xc, xe, x10, x12; u8 pad2[4]; s16 x18; } ListMenuDesc;

#endif /* KH1_LIST_LISTMENU_H */
